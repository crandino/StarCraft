#include "App.h"
#include "EntityManager.h"
#include "Input.h"
#include "Window.h"
#include "p2Log.h"
#include "PathFinding.h"
#include "Marine.h"
#include "Zergling.h"
#include "Scv.h"
#include "CommandCenter.h"
#include "Bunker.h"
#include "GameManager.h"


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
		break;
	case(BUNKER) :
		LOG("Creating Bunker");
		e = new Bunker(pos);
		building_to_place = (Building*)e;
		building_mode = true;
		create_bunker = false;
		break;
	case(ZERGLING) :
		LOG("Creating Zergling");
		e = new Zergling(pos);
		break;
	case(SCV) :
		LOG("Creating SCV");
		e = new Scv(pos);
		create_SCV = false;
		break;
	}

	if (e != NULL && building_mode != true)
	{
		e->id = ++next_ID;
		active_entities.insert(pair<uint, Entity*>(e->id, e));

		// Command center creation, special treatment
		if (e->specialization == COMMANDCENTER)
		{
			app->map->changeLogic(e->coll->rect, NO_WALKABLE);
			logicChanged();
		}

		if (e->specialization == MARINE)
		{
			player_units.insert(pair<uint, Entity*>(e->id, e));
		}
	}

	return e;
}

/*Method that makes the enemyWave attack the commandCenter*/
void EntityManager::SetEnemyToAttackCommandCenter(Entity* e)
{
	if (e->type == UNIT)
	{
		iPoint p = COMMANDCENTERPOSITION;
		p = app->map->worldToMap(app->map->data.back(), p.x, p.y - 100); // With -100, we avoid a NoWalkable tile

		Unit* unit = (Unit*)e;
		if (app->path->createPath(e->tile_pos, p) != -1)
		{
			unit->path = app->path->getLastPath();
			unit->has_target = true;
			unit->state = MOVE_ALERT;
		}
	}
}

// Called each loop iteration
bool EntityManager::preUpdate()
{
	// We delete the entities marked with to_delete
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end();)
	{
		if (it->second->to_delete)
		{
			// Maybe, the entity removed is someone's entity_to_attack. Now, it's not.  CRZ
			for (map<uint, Entity*>::iterator it2 = active_entities.begin(); it2 != active_entities.end(); ++it2)
			{
				if (it->second == it2->second->target_to_attack)
					it2->second->target_to_attack = NULL;
			}

			if (it->second->specialization == MARINE)
				app->game_manager->marineCounterDeath++;

			selection.erase(it->first);
			if(!it->second->inside_bunker)
				RELEASE(it->second);

			it = active_entities.erase(it);
		}
		else
			++it;
	}

	iPoint position;

	if (app->input->getKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, MARINE);		
	}

	if (create_SCV && app->game_manager->mineral_resources >= 50)
	{
		map<uint, Entity*>::iterator it = active_entities.begin();
		fPoint pos_commander;
		// First, we need to know if any unit has been selected. 
		for (; it != active_entities.end(); ++it)
		{
			if (it->second->specialization == COMMANDCENTER)
			{
				pos_commander = it->second->pos;
				break;
			}
		}

		app->game_manager->mineral_resources -= 50;
		position.x = pos_commander.x + 20;
		position.y = pos_commander.y + 100;

		addEntity(position, SCV);
	}

	if (app->input->getKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, COMMANDCENTER);
	}

	if (create_bunker && app->game_manager->gas_resources >= 50 && app->game_manager->mineral_resources >= 25)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		app->game_manager->mineral_resources -= 25;
		app->game_manager->gas_resources -= 50;
		addEntity(position, BUNKER);
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

	// Clicking and holding left button, starts a selection
	if (!building_mode && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
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
		bool units_only = false;    // If only one unit is on selection, buildings will be excluded
		map<uint, Entity*>::iterator it = active_entities.begin();

		// First, we need to know if any unit has been selected. 
		for (; it != active_entities.end(); ++it)
		{
			if (it->second->coll->checkCollision(selector))
			{
				if (it->second->type == UNIT)
					units_only = true;
			}
		}

		// Now, we include the entities according to the only_units boolean variable.
		for (it = active_entities.begin(); it != active_entities.end(); ++it)
		{
			if (it->second->coll->checkCollision(selector))
			{
				if (it->second->type == UNIT)
				{
					Unit *u = (Unit*)it->second;
					u->distance_to_center_selector = u->tile_pos - app->map->worldToMap(app->map->data.back(), selector.x + (selector.w / 2), selector.y + (selector.h / 2));
					selection.insert(pair<uint, Entity*>(it->first, it->second));
				}

				if (!units_only && it->second->type == BUILDING)
				{
					selection.insert(pair<uint, Entity*>(it->first, it->second));
					break;
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

		//Bunker stuff
		Entity* e = whichEntityOnMouse();

		map<uint, Entity*>::iterator it = selection.begin();
		for (; it != selection.end(); ++it)
		{
			if (it->second->type == UNIT)
			{
				Unit *unit = (Unit*)it->second;
				if (selection.size() == 1)
				{
					if (app->path->createPath(unit->tile_pos, target_position) != -1)
					{
						unit->path = app->path->getLastPath();
						unit->has_target = true;
						unit->state = MOVE;
						if (e != NULL && e->specialization == BUNKER)
						{
							unit->target_to_reach = e;
							app->gui->bunker_to_leave = (Bunker*)e;
						}
						else
							unit->target_to_reach = nullptr;
					}
				}
				else
				{
					iPoint target = target_position + unit->distance_to_center_selector;
					if (app->path->createPath(unit->tile_pos, target) != -1)
					{
						unit->path = app->path->getLastPath();
						unit->has_target = true;
						unit->state = MOVE;
						if (e != NULL && e->specialization == BUNKER)
						{
							unit->target_to_reach = e;
							app->gui->bunker_to_leave = (Bunker*)e;
						}
						else
							unit->target_to_reach = nullptr;

					}
				}
			}
		}
	}

	if (building_mode && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (app->map->isAreaWalkable(building_to_place->coll->rect))
		{
			building_to_place->id = ++next_ID;
			building_to_place->tile_pos = app->map->worldToMap(app->map->data.back(), building_to_place->center.x, building_to_place->center.y);
			active_entities.insert(pair<uint, Entity*>(next_ID, building_to_place));
			building_mode = false;

			app->map->changeLogic(building_to_place->coll->rect, NO_WALKABLE);
			logicChanged();
		}
	}


	//------------------------ATTACK MECHANICS------------------------------------//
	/*if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
	Entity* e = whichEntityOnMouse();
	LOG("Hostility ON");
	if (!selection.empty())
	{
	if (e != NULL && e->specialization == ZERGLING)
	{
	KillEntity(e);
	enemyJustDied = true;
	}
	}
	}*/
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
	/*Resetting bool for Game Manager*/
	enemyJustDied = false;

	// Entities Drawing
	// Look on Gui postUpdate()!

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
	p = app->render->screenToWorld(p.x, p.y);

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

void EntityManager::createWave(uint sizex, uint sizey, iPoint position)
{

		for (int i = 0; i < sizex; i++)
		{
			for (int j = 0; j < sizey; j++)
			{
				int posx = 1500 + (sizex * i * 10);
				int posy = 2150 + (sizey * j * 10);

				iPoint position = {posx, posy};

				createZergling(position);
			}
		}
	Timer test;
	test.start();



	LOG("Creating this wave has taken %d", test.read());

}


bool EntityManager::searchNearEntity(Entity* e)
{
	bool ret = false;

	e->target_to_attack = NULL;
	float value = e->range_to_view;
	map<uint, Entity*>::iterator it = active_entities.begin();
	uint previousMaxHP = 10000;

	for (; it != active_entities.end(); ++it) //First and foremost the unit looks for the closest and weakest enemy
	{
		if (it->second != e && e->faction != it->second->faction && it->second->to_delete == false)
		{
			float d = abs(e->center.x - it->second->center.x) + abs(e->center.y - it->second->center.y);
			uint maxHP = it->second->current_hp;
			
			d -= ((e->coll->rect.w / 2 + e->coll->rect.h / 2) / 2 + (it->second->coll->rect.w / 2 + it->second->coll->rect.h / 2) / 2);

			if (d <= value && maxHP <= previousMaxHP)//If the a unit is low on health it attacks it :). It is possible to kite zerglings now. However too dumb yet :D!
			{
				(e->target_to_attack) = &(*it->second);
				LOG("BUG NET");
				value = d;
				previousMaxHP = maxHP;
				ret = true;
			}
		}

		if (e->specialization == SCV && it->second != NULL && it->second->type == BUILDING && (it->second->current_hp < it->second->max_hp))// we check if we are a SCV, the objective is a building and needs to be repared
		{
			float d = abs(e->center.x - it->second->center.x) + abs(e->center.y - it->second->center.y);
			d -= ((e->coll->rect.w / 2 + e->coll->rect.h / 2) / 2 + (it->second->coll->rect.w / 2 + it->second->coll->rect.h / 2) / 2);
			if (d <= value)
			{
				(e->target_to_repair) = &(*it->second);
				value = d;
				ret = true;
			}
		}
	}

	if (e->target_to_attack != NULL) //Second it does the calculus and changes the IA states
	{
		if (e->type == UNIT)
		{
			Unit* unit = (Unit*)e;
			unit->has_target = false;
			if (value <= e->range_to_attack) //If the entity isn't in the range of attack it changes the direction and state
			{
				unit->checkUnitDirection();
				e->state = ATTACK;
			}
			else
			{
				if (e->type == UNIT && app->path->createPath(e->tile_pos, e->target_to_attack->tile_pos) != -1) //the path to the selected entity is constructed
				{
					unit->has_target = true;
					unit->path = app->path->getLastPath();
					e->state = MOVE_ALERT;
				}
			}
		}
		else
		{
			if (value <= e->range_to_attack)
				e->state = ATTACK;

			else
				e->state = IDLE;
		}
	}

	if (e->target_to_repair != NULL)// if we have a building that needs to be repaired
	{
		Unit* unit = (Unit*)e;
		unit->has_target = false;
		if (value <= e->range_to_attack)
		{
			unit->checkUnitDirection();
			e->state = REPAIR;
		}
		//else
		//{
		//	if (e->type == UNIT && app->path->createPath(e->tile_pos, e->target_to_attack->tile_pos) != -1)
		//	{
		//		unit->has_target = true;
		//		unit->path = app->path->getLastPath();
		//		e->state = MOVE_ALERT;
		//	}
		//}
	}

	return ret;
}



void EntityManager::createZergling(iPoint position)
{
	addEntity(position, ZERGLING);
}



//Deletes all units SELECTED
void EntityManager::deleteEntity(map<uint, Entity*> selection)
{
	vector<Entity* const> unitsto_delete;
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

	e->coll->to_delete = true;
	active_entities.erase(e->id);
	enemyJustDied = true;
	if (e->faction == COMPUTER)
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

void EntityManager::GetInsideBunker(Entity* e)
{
	Bunker* bunker = (Bunker*)e->target_to_reach;
	if (bunker->capacity != 0)
	{
		if (e->specialization == MARINE)
		{
			bunker->units_inside.insert(pair<uint, Entity*>(e->id, e));
			e->inside_bunker = true;
			e->to_delete = true;
			selection.erase(e->id);
			--bunker->capacity;
		}
	}
	else if(bunker->capacity == 0)
	{
		for (map<uint, Entity*>::iterator it2 = active_entities.begin(); it2 != active_entities.end(); ++it2)
		{
			if (bunker == it2->second->target_to_reach)
				it2->second->target_to_reach = nullptr;
		}
	}
}

void EntityManager::repairBuilding(Entity* e)
{
	map<uint, Entity*>::iterator it = selection.begin();
	for (; it != selection.end(); it++)
	{
		if (it->second->specialization == SCV)
		{
			e->current_hp += e->repair_power;
			if (e->current_hp >= e->max_hp)
			{
				e->current_hp = e->max_hp;
			}
		}
	}
}

//Deletes all the units in the screen (DEBUG PURPOSES ONLY)
void EntityManager::deleteAllEntities()
{
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); it++)
	{
		it->second->coll->to_delete = true;
		delete it->second;
	}	

	active_entities.clear();
	selection.clear();
}

void EntityManager::choosePlaceForBuilding()
{
	iPoint p; app->input->getMousePosition(p);
	iPoint pos = app->render->screenToWorld( p.x - building_to_place->tex_width / 2, p.y - building_to_place->tex_height / 2 );
	building_to_place->pos = { (float)pos.x, (float)pos.y };
	
	iPoint center = app->render->screenToWorld(p.x, p.y);
	building_to_place->center = { (float)center.x, (float)center.y };
	
	building_to_place->coll->setPos(building_to_place->pos.x + building_to_place->collider_offset.x, building_to_place->pos.y + building_to_place->collider_offset.y);

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

void EntityManager::logicChanged()
{
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
				if (unit->path.size() > 0 && app->path->createPath(it->second->tile_pos, unit->path.back()) != -1)
					unit->path = app->path->getLastPath();
			}
		}
	}
}

void EntityManager::onCollision(Collider* c1, Collider* c2)
{
	Entity *e1, *e2;
	e1 = e2 = NULL;

	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); ++it)
	{
		if (it->second->coll == c1) e1 = it->second;
		else if (it->second->coll == c2) e2 = it->second;
	}
	
	if (e1 != NULL && e2 != NULL && e1->type == UNIT && e1->state == IDLE && e2->type == UNIT && e2->state == IDLE)
	{
		if (app->path->createPathToAdjacent(e2->tile_pos, 2) != -1)
		{
			Unit *unit = (Unit*)e2;
			unit->path = app->path->getLastPath();
			unit->has_target = true;
			unit->state = MOVE;
		}
	}
}