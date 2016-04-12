#include "App.h"
#include "EntityManager.h"
#include "Input.h"
#include "Window.h"
#include "p2Log.h"
#include "PathFinding.h"
#include "Marine.h"
#include "Zergling.h"
#include "CommandCenter.h"

EntityManager::EntityManager() : Module()
{
	name.assign("EntityManager");
}

// Destructor
EntityManager::~EntityManager()
{ }

// Called before render is available
bool EntityManager::awake(pugi::xml_node &node)
{
	return true;
}

// Called before the first frame
bool EntityManager::start()
{
	next_ID = 0;
    circle_characters = app->tex->loadTexture("Selection/Selection_circles.png");
	hp_tex = app->tex->loadTexture("Cursor/StarCraftCursors.png");
	building_tile = app->tex->loadTexture("maps/Path_Tiles.png");

	return true;
}

Entity* const EntityManager::addEntity(iPoint &pos, SPECIALIZATION type)
{
	Entity *e = NULL;

	switch (type)
	{
	case(MARINE) :
		LOG("Creating Marine");
		e = new Marine(pos);
		break;
	case(COMMANDCENTER) :
		LOG("Creating Command Center");
		e = new CommandCenter(pos);
		building_to_place = (Building*)e;
		building_mode = true;
		break;
	case(ZERGLING) :
		LOG("Creating Zergling");
		e = new Zergling(pos);
		addInEnemyContainer(e);
		AddEntityToWave(e->id, e);
		break;
	}

	if (e != NULL && e->type == UNIT)
	{
		e->id = ++next_ID;
		active_entities.insert(pair<uint, Entity*>(next_ID, e));
	}

	return e;
}

uint EntityManager::getWaveZerglingSize()
{
	return waveZerglings.size();
}

Entity* const EntityManager::addInEnemyContainer(Entity* e)//Maybe return type should be void?
{
	waveZerglings.push_back(e);
	LOG("Enemy added in wave. Number of enemies %d", waveZerglings.size());
	return e;
}
/*Method that adds zerglings into a map called enemyWave 
(where all zerglings of the wave are stored)*/
void EntityManager::AddEntityToWave(uint id,Entity* e)
{
	enemyWave.insert(pair<uint, Entity*>(id, e));
}

// Called each loop iteration
bool EntityManager::preUpdate()
{

	if (app->input->getKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		Marine *m = (Marine*)marine;
		//m->angle += 0.5f;
		m->current_hp -= 1.0f;

		LOG("Marine angle: %f", m->angle);
		LOG("Marine hp: %f", m->current_hp);
	}
		
	//ROF Iterate all entities to check their angle
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); ++it)
	{	
		it->second->checkAngle();
	}

	iPoint position;
	
	if (app->input->getKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		//addEntity(position, MARINE);

		marine = addEntity(position, MARINE);
		//if (e != NULL) remove(e->id);		
	}		

	if (app->input->getKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, COMMANDCENTER);
	}

	if (app->input->getKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, ZERGLING);
	}

	if (app->input->getKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
		deleteAllEntities();

	if (app->input->getKey(SDL_SCANCODE_0) == KEY_DOWN)
		deleteEntity(selection);
	
	if (building_mode && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (app->map->isAreaWalkable(building_to_place->coll->rect))
		{
			building_to_place->id = ++next_ID;
			active_entities.insert(pair<uint, Entity*>(next_ID, building_to_place));
			building_mode = false;

			app->map->changeLogic(building_to_place->coll->rect, NO_WALKABLE);
			int w, h;
			uchar *buffer = NULL;
			if (app->map->createWalkabilityMap(w, h, &buffer))
			{
				app->path->setMap(w, h, buffer);

				map<uint, Entity*>::iterator it = active_entities.begin();
				for (; it != active_entities.end(); ++it)
				{
					if (it->second->type == UNIT)
					{
						Unit *unit = (Unit*)it->second;

						if (unit->path.size() > 0)
							if (app->path->createPath(it->second->tile_pos, unit->path.back()) != -1)
								unit->path = app->path->getLastPath();
					}
				}
			}
		}
	}		

	// Clicking and holding left button, starts a selection
	if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		selection.clear();
		app->input->getMousePosition(initial_selector_pos);
		initial_selector_pos = app->render->screenToWorld(initial_selector_pos.x, initial_selector_pos.y);
		
		//Click and select unit	
		selector_init = true;
		Entity *e = whichEntityOnMouse();
		if (e != NULL)
			selector = { e->coll->rect.x, e->coll->rect.y, 1, 1 };
		else
			selector = { 0, 0, 0, 0 };		
	}

	// Holding left button, updates selector dimensions
	if (selector_init && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		app->input->getMousePosition(final_selector_pos);
		final_selector_pos = app->render->screenToWorld(final_selector_pos.x, final_selector_pos.y);

		calculateSelector();
	}		

	// Once released left button, the selection is computed
	if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
	{
		selector_init = false;
		map<uint, Entity*>::iterator it = active_entities.begin();
		for (; it != active_entities.end(); ++it)
		{
			if (it->second->coll->checkCollision(selector))
			{
				switch (it->second->type)
				{
				case(UNIT) :
				{
					Unit *u = (Unit*)it->second;
					u->distance_to_center_selector = u->tile_pos - app->map->worldToMap(app->map->data.back(), selector.x + (selector.w / 2), selector.y + (selector.h / 2));
					break;
				}
				}
				selection.insert(pair<uint, Entity*>(it->first, it->second));
			}			
		}
	}		

	if (!selection.empty() && app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		// Target position is where the player has clicked to move his units.
		iPoint target_position;
		app->input->getMousePosition(target_position);
		target_position = app->render->screenToWorld(target_position.x, target_position.y);
		target_position = app->map->worldToMap(app->map->data.back(), target_position.x, target_position.y);

		map<uint, Entity*>::iterator it = selection.begin();
		for (; it != selection.end(); ++it)
		{
			if (it->second->type == UNIT)
			{
				Unit *unit = (Unit*)it->second;
				unit->has_target = true;
				if (selection.size() == 1)
				{	
					if (app->path->createPath(unit->tile_pos, target_position) != -1)
						unit->path = app->path->getLastPath();
				}
				else
				{
					iPoint target = target_position + unit->distance_to_center_selector;
					if (app->path->createPath(unit->tile_pos, target) != -1)
						unit->path = app->path->getLastPath();					
				}					
			}
		}
	}

	//------------------------ATTACK MECHANICS------------------------------------//

	if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		Entity* e = whichEntityOnMouse();
		LOG("Hostility ON");
		if (!selection.empty())
		{
			if (e != NULL && e->type == ZERGLING)
			{
				KillEntity(e);			
			}
		}
	}

	return true;
} 

// Called each loop iteration
bool EntityManager::update(float dt)
{
	// Debug ---
	if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); ++it)
	{
		it->second->update(dt);

		//Debug: To draw the path finding that the entity is following
		/*if (app->entity_manager->debug)
		{
			Unit *unit = (Unit*)it->second;
			if (unit->path.size() > 0)
			{
				for (vector<iPoint>::iterator it2 = unit->path.begin(); it2 != unit->path.end(); ++it2)
				{
					iPoint p = app->map->mapToWorld(app->map->data.back(), it2->x, it2->y);
					app->render->blit(unit->tile_path, p.x, p.y);
				}
			}
		}*/
	}

	return true;
}

// Called each loop iteration
bool EntityManager::postUpdate()
{
	// Basic selection. Entities surrounded by black SDL_Rects.
	map<uint, Entity*>::iterator it2 = selection.begin();
	for (; it2 != selection.end(); ++it2)
	{
		if (it2->second->type == MARINE)
		{
			SDL_Rect section_circle = { 0, 62, 22, 13 };
			app->render->blit(circle_characters, it2->second->pos.x + 21, it2->second->pos.y + 34, (SDL_Rect*)&section_circle, 1.0f);
		}
		else if (it2->second->type == ZERGLING)
		{
			SDL_Rect section_circle = { 0, 62, 22, 13 };
			app->render->blit(circle_characters, it2->second->pos.x + 53, it2->second->pos.y + 55, (SDL_Rect*)&section_circle, 1.0f);
		}		
	}
	
	for (it2 = selection.begin(); it2 != selection.end(); ++it2)
	{
		//MSC provisional method that calculates current HP bars
		ceil(it2->second->current_hp_bars = it2->second->current_hp * it2->second->max_hp_bars / it2->second->max_hp);
		//app->render->DrawQuad({ it2->second->pos.x, it2->second->pos.y, 64, 64 }, 35, 114, 48, 255, false, true);
		SDL_Rect section_life = { 496, 20, 25, 8 };
		app->render->blit(hp_tex, it2->second->pos.x + 21, it2->second->pos.y + 48, (SDL_Rect*)&section_life, 1.0f);
		for (int i = 0, a = 0; i < it2->second->current_hp_bars; i++)
		{
			SDL_Rect greenquadlife = { 497, 32, 3, 4 };
			app->render->blit(hp_tex, it2->second->pos.x + 22 + a, it2->second->pos.y + 50, (SDL_Rect*)&greenquadlife, 1.0f);
			greenquadlife.x += 4;
			a += 4;
		}

		//app->render->DrawCircle(it2->second->pos.x + 32, it2->second->pos.y + 32, it2->second->tex_height/5, 35, 114, 48, 255, false);
	}
	
	// Entities Drawing
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); ++it)
	{
		if (it->second->type == ZERGLING)
		{
			SDL_Rect section_circle = { 0, 81, 23, 15 };
			app->render->blit(circle_characters, it->second->coll->rect.x + 1, it->second->coll->rect.y + 12, (SDL_Rect*)&section_circle, 1.0f);

			SDL_Rect section_life = { 536, 20, 41, 8 };
			app->render->blit(hp_tex, it->second->coll->rect.x - 7, it->second->coll->rect.y + 27, (SDL_Rect*)&section_life, 1.0f);
			for (int i = 0, a = 0; i < it->second->current_hp_bars; i++)
			{
				SDL_Rect greenquadlife = { 537, 32, 3, 4 };
				app->render->blit(hp_tex, it->second->coll->rect.x - 6 + a , it->second->coll->rect.y + 29, (SDL_Rect*)&greenquadlife, 1.0f);
				greenquadlife.x += 4;
				a += 4;
			}
		}
       it->second->draw();
	}
		
	// Drawing selector (green SDL_Rect)
	if (selector_init && selector.w > 1 && selector.h > 1) app->render->DrawQuad(selector, 35, 114, 48, 255, false, true);

	if (building_mode)
		choosePlaceForBuilding();

	return true;
}

// Called before quitting
bool EntityManager::cleanUp()
{
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); it++)
		delete it->second;

	active_entities.clear();
	selection.clear();

	return true;
}

// Return ID for the corresponding entity
Entity *EntityManager::getEntity(uint id)
{
	map<uint, Entity*>::iterator it = active_entities.find(id);
	return (it != active_entities.end() ? it->second : NULL);
}

// WhichEntityOnMouse: Returns an entity under the mouse cursor
Entity *EntityManager::whichEntityOnMouse()
{
	iPoint p; app->input->getMousePosition(p);

	map<uint, Entity*>::reverse_iterator rit = active_entities.rbegin();
	for (; rit != active_entities.rend(); ++rit)
	{
		if (p.x >= rit->second->coll->rect.x &&
			p.x <= rit->second->coll->rect.x + rit->second->coll->rect.w &&
			p.y >= rit->second->coll->rect.y &&
			p.y <= rit->second->coll->rect.y + rit->second->coll->rect.h)
			return rit->second;
	}
	return NULL;
}

// CalculateSelector: Method that computes the dimensions of the green SDL_Rect selector.
void EntityManager::calculateSelector()
{
	// If dimensions of the selector are less than 1/1 (for width/height), it sets 1. Eliminates 0 width/height to proper alone selection. 
	int selector_width = abs(final_selector_pos.x - initial_selector_pos.x) > 1 ? abs(final_selector_pos.x - initial_selector_pos.x) : 1;
	int selector_height = abs(final_selector_pos.y - initial_selector_pos.y) > 1 ? abs(final_selector_pos.y - initial_selector_pos.y) : 1;
	int selector_pos_x = (initial_selector_pos.x < final_selector_pos.x ? initial_selector_pos.x : final_selector_pos.x);
	int selector_pos_y = (initial_selector_pos.y < final_selector_pos.y ? initial_selector_pos.y : final_selector_pos.y);
	selector = { selector_pos_x, selector_pos_y, selector_width, selector_height };
}

/*------------------WAVE RELATED METHODS--------------------------*/

void EntityManager::createWave(uint size/*zergling num, hidralisk....num*/)
{


	for (int i = 0; i < size; i++)
	{
		createZergling();
	}
}

void EntityManager::createZergling()
{

	//Point to check if the cursor is on a walkable tile

	iPoint position = { 100, 450 };

	addEntity(position, ZERGLING);
}


//Deletes all units SELECTED
void EntityManager::deleteEntity(map<uint, Entity*> selection)
{
	vector<Entity* const> unitsToDelete;
	map<uint, Entity*>::iterator it;

	vector <Entity* const>::iterator itdel;
	bool must_delete = true;

	for (auto it = selection.cbegin(); it != selection.cend() /* not hoisted */; it++)
	{
		/*Stores entities in a vector that is going to be erased later
		(add into the .h to become accessible to erase them at another
		time*/

		std::map<uint, Entity*>::iterator itdel;
		itdel = active_entities.find(it->first);
		active_entities.erase(itdel);
	}

	selection.clear();
}

/*Method that deletes an entity*/
void EntityManager::deleteEntityKilled(Entity* e)
{
	vector <Entity* const>::iterator itdel;

	/*Deletes enemy in the enemy wave*/
	active_entities.erase(e->id);
	/*RIE: When a lot of zerglings are added they don't die in the order they should don't know why*/
	LOG("ZERGLING KILLED! Enemies remaining in the wave: ");
}

void EntityManager::KillEntity(map<uint, Entity*> selection)
{
	deleteEntity(selection);
}

void EntityManager::KillEntity(Entity* e)
{
	deleteEntityKilled(e);
}

//Deletes all the units in the screen (DEBUG PURPOSES ONLY)
void EntityManager::deleteAllEntities()
{
	active_entities.clear();
	selection.clear();
}

void EntityManager::choosePlaceForBuilding()
{
	iPoint p; app->input->getMousePosition(p);
	building_to_place->pos = { (float)p.x - building_to_place->tex_width / 2, (float)p.y - building_to_place->tex_height / 2 };
	building_to_place->coll->setPos(building_to_place->pos.x - building_to_place->collider_offset.x, building_to_place->pos.y - building_to_place->collider_offset.y);

	iPoint first_tile = app->map->worldToMap(app->map->data.back(), building_to_place->coll->rect.x, building_to_place->coll->rect.y);
	iPoint last_tile = app->map->worldToMap(app->map->data.back(), building_to_place->coll->rect.x + building_to_place->coll->rect.w, building_to_place->coll->rect.y + building_to_place->coll->rect.h);
	iPoint point_to_draw;

	for (int y = first_tile.y; y < last_tile.y; ++y)
	{
		for (int x = first_tile.x; x < last_tile.x; ++x)
		{
			point_to_draw = app->map->mapToWorld(app->map->data.back(), x, y);
			if (app->path->isWalkable({ x, y }))
			{
				SDL_Rect r = { 1, 1, 8, 8 };
				app->render->blit(building_tile, point_to_draw.x, point_to_draw.y, &r);
			}
			else
			{
				SDL_Rect r = { 10, 1, 8, 8 };
				app->render->blit(building_tile, point_to_draw.x, point_to_draw.y, &r);
			}
		}
	}
	app->render->blit(building_to_place->tex, building_to_place->pos.x, building_to_place->pos.y, &building_to_place->current_animation->getCurrentFrame());
}