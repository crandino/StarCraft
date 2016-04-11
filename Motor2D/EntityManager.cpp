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
	filter = 0;
    circle_characters = app->tex->loadTexture("Selection/Selection_circles.png");
	hp_tex = app->tex->loadTexture("Cursor/StarCraftCursors.png");

	return true;
}

Entity* const EntityManager::addEntity(iPoint &pos, ENTITY_TYPE type)
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
		break;
	case(ZERGLING) :
		LOG("Creating Zergling");
		e = new Zergling(pos);
		addInEnemyContainer(e);
		AddEntityToWave(e->id, e);
		break;
	}

	if (app->map->isAreaWalkable(e->coll->rect))
		LOG("No problem!");
	else
		LOG("Problem");

	if (e != NULL)
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

	if (app->input->getKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->getKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		marine->angle += 0.5f;

		LOG("Marine angle: %f", marine->angle);
	}
		
	//ROF Iterate all entities to check their angle
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); ++it)
	{	
		it->second->checkAngle();
	}
 
	//Point to check if the cursor is on a walkable tile
	iPoint position; 
	app->input->getMousePosition(position);
	position = app->render->screenToWorld(position.x, position.y);
	position = app->map->worldToMap(app->map->data.back(), position.x, position.y);

	if (app->path->isWalkable(position))
	{
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
		{
			deleteAllEntities();
		}

		if (app->input->getKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			deleteEntity(selection);
		}
	}
	


	// Clicking and holding left button, starts a selection
	if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		selector_init = true;
		selector = { 0, 0, 0, 0 };
		selection.clear();
		app->input->getMousePosition(initial_selector_pos);
		initial_selector_pos = app->render->screenToWorld(initial_selector_pos.x, initial_selector_pos.y);
		
		//Click and select unit
		if (whichEntityOnMouse() != NULL)
		{
			Entity* e = whichEntityOnMouse();

			pair<uint, Entity*>unitSelected(1, e);
			if (unitSelected.second->type != ZERGLING)
			{
               unitSelected.second->distance_to_center_selector = unitSelected.second->tile_pos - app->map->worldToMap(app->map->data.back(), selector.x + (selector.w / 2), selector.y + (selector.h / 2));
		       selection.insert(pair<uint, Entity*>(unitSelected.first, unitSelected.second));
			}
			
		}
		else
		{
			selection.clear();
		}
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
			if (it->second->type == MARINE)
			{
				if (it->second->coll->checkCollision(selector))
				{
					it->second->distance_to_center_selector = it->second->tile_pos - app->map->worldToMap(app->map->data.back(), selector.x + (selector.w / 2), selector.y + (selector.h / 2));
					selection.insert(pair<uint, Entity*>(it->first, it->second));
				}
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
			if (it->second->type == MARINE)
			{
				if (selection.size() > 1)
				{	
						it->second->has_target = true;
						iPoint target = target_position + it->second->distance_to_center_selector;
						if (app->path->createPath(it->second->tile_pos, target) != -1)
						it->second->path = app->path->getLastPath();
				}
				else
				{
					it->second->has_target = true;
					if (app->path->createPath(it->second->tile_pos, target_position) != -1)
						it->second->path = app->path->getLastPath();
				}
			}
		}
	}

	//------------------------ATTACK MECHANICS------------------------------------//

	if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		Entity* e = whichEntityOnMouse();
		LOG("Hostility ON");
		if (selection.empty() == FALSE)
		{
			if (e != NULL && e->type == ZERGLING)
				KillEntity(e);
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
		if (app->entity_manager->debug && it->second->path.size() > 0)
		{
			for (vector<iPoint>::iterator it2 = it->second->path.begin(); it2 != it->second->path.end(); ++it2)
			{
				iPoint p = app->map->mapToWorld(app->map->data.back(), it2->x, it2->y);
				app->render->blit(it->second->tile_path, p.x, p.y);
			}
		}
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
		//app->render->DrawQuad({ it2->second->pos.x, it2->second->pos.y, 64, 64 }, 35, 114, 48, 255, false, true);
		SDL_Rect section_life = { 496, 20, 25, 8 };
		app->render->blit(hp_tex, it2->second->pos.x + 21, it2->second->pos.y + 48, (SDL_Rect*)&section_life, 1.0f);
		for (int i = 0, a = 0; i < it2->second->hp; i++)
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
			for (int i = 0, a = 0; i < it->second->hp; i++)
			{
				SDL_Rect greenquadlife = { 537, 32, 3, 4 };
				app->render->blit(hp_tex, it->second->coll->rect.x - 6 + a , it->second->coll->rect.y + 29, (SDL_Rect*)&greenquadlife, 1.0f);
				greenquadlife.x += 4;
				a += 4;
			}
		}
       it->second->draw();
	}
		

	// Drawing selector (white SDL_Rect)
	if (selector_init) app->render->DrawQuad(selector, 35, 114, 48, 255, false, true);

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
		if (p.x >= rit->second->pos.x &&
			p.x <= rit->second->pos.x + rit->second->tex_width &&
			p.y >= rit->second->pos.y &&
			p.y <= rit->second->pos.y + rit->second->tex_height)
			return rit->second;
	}
	return NULL;
}

// CalculateSelector: Method that computes the dimensions of the white SDL_Rect selector.
void EntityManager::calculateSelector()
{
	int selector_width = abs(final_selector_pos.x - initial_selector_pos.x);
	int selector_height = abs(final_selector_pos.y - initial_selector_pos.y);
	int selector_pos_x = (initial_selector_pos.x < final_selector_pos.x ? initial_selector_pos.x : final_selector_pos.x);
	int selector_pos_y = (initial_selector_pos.y < final_selector_pos.y ? initial_selector_pos.y : final_selector_pos.y);
	selector = { selector_pos_x, selector_pos_y, selector_width, selector_height };
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