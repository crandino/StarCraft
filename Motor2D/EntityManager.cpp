#include "App.h"
#include "EntityManager.h"
#include "Input.h"
#include "Window.h"
#include "p2Log.h"
#include "PathFinding.h"
#include "GameManager.h"

#include "Marine.h"
#include "Firebat.h"
#include "Scv.h"
#include "Medic.h"
#include "Zergling.h"
#include "Mutalisk.h"
#include "Ultralisk.h"
#include "Hydralisk.h"
#include "Tank.h"
#include "JimRaynor.h"
#include "Gui.h"
#include "GuiCursor.h"
#include "FogOfWar.h"

#include "Bomb.h"
#include "CommandCenter.h"
#include "Bunker.h"
#include "Barrack.h"


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
	marine = new Marine();
	list_of_entity_classes.push_back(marine);
	scv = new Scv();
	list_of_entity_classes.push_back(scv);
	medic = new Medic();
	list_of_entity_classes.push_back(medic);
	firebat = new Firebat();
	list_of_entity_classes.push_back(firebat);
	tank = new Tank();
	list_of_entity_classes.push_back(tank);

	zergling = new Zergling();
	list_of_entity_classes.push_back(zergling);
	mutalisk = new Mutalisk();
	list_of_entity_classes.push_back(mutalisk);
	hydralisk = new Hydralisk();
	list_of_entity_classes.push_back(hydralisk);
	ultralisk = new Ultralisk();
	list_of_entity_classes.push_back(ultralisk);

	command_center = new CommandCenter();
	list_of_entity_classes.push_back(command_center);
	bunker = new Bunker();
	list_of_entity_classes.push_back(bunker);
	barrack = new Barrack();
	list_of_entity_classes.push_back(barrack);

	return true;
}

// Called before the first frame
bool EntityManager::start()
{
	next_ID = 0;

	for (list<Entity*>::iterator it = list_of_entity_classes.begin(); it != list_of_entity_classes.end(); ++it)
		(*it)->start();

    building_tile = app->tex->loadTexture("maps/Path_Tiles.png");

	return true;
}

Entity* const EntityManager::addEntity(iPoint &pos, SPECIALIZATION type)
{
	Entity *e = NULL;

	switch (type)
	{
	// UNITS
		// TERRAN
	case(MARINE) :
		LOG("Creating Marine");
		e = new Marine(pos);
		break;
	case(SCV) :
		LOG("Creating SCV");
		e = new Scv(pos);
		break;
	case(TANK) :
		LOG("Creating Tank");
		e = new Tank(pos);
		break;
	case(MEDIC) :
		LOG("Creating Medic");
		e = new Medic(pos);
		break;
	case(JIM_RAYNOR) :
		LOG("Creating Jym Raynor");
		e = new JimRaynor(pos);
		break;
	case(FIREBAT) :
		LOG("Creating Firebat");
		e = new Firebat(pos);
		break;
		// ZERGLINGS
	case(ZERGLING) :
		LOG("Creating Zergling");
		e = new Zergling(pos);
		break;
	case(MUTALISK) :
		LOG("Creating Mutalisk");
		e = new Mutalisk(pos);
		break;
	case(HYDRALISK) :
		LOG("Creating Hydralisk");
		e = new Hydralisk(pos);
		break;
	case(ULTRALISK) :
		LOG("Creating Ultralisk");
		e = new Ultralisk(pos);
		break;
	// TERRAN BUILDINGS
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
	case(BARRACK) :
		LOG("Creating Barrack");
		e = new Barrack(pos);
		building_to_place = (Building*)e;
		building_mode = true;
		create_barrack = false;
		break;
	case(BOMB) :
		LOG("Bomb created");
		e = new Bomb(pos);
		building_to_place = (Building*)e;
		break;
	}

	if (e != NULL && building_mode != true)
	{
		e->id = ++next_ID;
		active_entities.insert(pair<uint, Entity*>(e->id, e));

		// Building creation, special treatment
		if (e->type == COMMANDCENTER || e->type == BOMB)
		{
			app->map->changeLogic(e->coll->rect, NO_WALKABLE);
			recalculatePaths(e->coll->rect, false);
		}
	}

	return e;
}

/*Method that makes the enemyWave attack the commandCenter*/
void EntityManager::SetEnemyToAttackCommandCenter(Entity* e)
{
	if (e->type == UNIT)
	{
		iPoint p = app->game_manager->command_center_position;
		p = app->map->worldToMap(app->map->data.back(), p.x, p.y - 100); // With -100, we avoid a NoWalkable tile

		Unit* unit = (Unit*)e;
		if (unit->flying)
		{
			unit->path.clear();
			unit->path.push_back(p);
			unit->has_target = true;
			unit->state = MOVE_ALERT;
		}
		else if (app->path->createPath(e->tile_pos, p, e->id) != -1)
			unit->state = WAITING_PATH_MOVE_ALERT;
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

			app->path->erase(it->first);

			if (it->second->type == BUILDING)
			{
				if (it->second->specialization == COMMANDCENTER)
					app->game_manager->command_center_destroyed = true;			
				app->map->changeLogic(it->second->coll->rect, LOW_GROUND);
				app->entity_manager->recalculatePaths(it->second->coll->rect, true);
			}

			if (it->second->specialization == JIM_RAYNOR)
				app->game_manager->jim_raynor_dead = true;
			
			// Very disgusting code to mantain Marines inside a bunker // CRZ
			selection.erase(it->first);
			if (it->second->specialization == MARINE)
			{
				if (!((Marine*)it->second)->inside_bunker)
					RELEASE(it->second);
			}
			else
				RELEASE(it->second);
				
			it = active_entities.erase(it);
		}
		else
			++it;
	}

	if (app->game_manager->isGameStarted()) handleSelection();
	entityManualCreation();

	if (create_SCV)
	{
		map<uint, Entity*>::iterator it = active_entities.begin();
		fPoint pos_commander;
		// First, we need to know if any unit has been selected. 
		for (; it != active_entities.end(); ++it)
		{
			if (it->second->specialization == COMMANDCENTER)
			{
				iPoint position;
				pos_commander = it->second->pos;
				app->game_manager->mineral_resources -= 50;
				position.x = pos_commander.x + 20;
				position.y = pos_commander.y + 100;

				addEntity(position, SCV);
				create_SCV = false;
				break;
			}
		}
	}

	if (create_bunker)
	{
		iPoint position;
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		app->game_manager->mineral_resources -= 25;
		app->game_manager->gas_resources -= 50;
		addEntity(position, BUNKER);
	}

	if (create_barrack)
	{
		iPoint position;
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		app->game_manager->mineral_resources -= 250;
		app->game_manager->gas_resources -= 250;
		addEntity(position, BARRACK);
	}

	if (create_factory)
	{
		iPoint position;
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		app->game_manager->mineral_resources -= 300;
		app->game_manager->gas_resources -= 300;
		addEntity(position, FACTORY);
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
			it->second->update(dt);

	//FOG_OF_WAR
	updateFogOfWar();
	return true;
}

// Called each loop iteration
bool EntityManager::postUpdate()
{	
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
	{
			RELEASE(it->second);
	}
	active_entities.clear();
	selection.clear();

	for (list<Entity*>::iterator it = list_of_entity_classes.begin(); it != list_of_entity_classes.end();)
	{
		RELEASE(*it);
		it = list_of_entity_classes.erase(it);
	}
	list_of_entity_classes.clear();		

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

void EntityManager::handleSelection()
{
	// Clicking and holding left button, starts a selection
	if (!building_mode && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		//selection.clear();
		app->input->getMousePosition(initial_selector_pos);
		initial_selector_pos = app->render->screenToWorld(initial_selector_pos.x, initial_selector_pos.y);

		//Click and select unit	
		selector_init = true;
		Entity *e = whichEntityOnMouse();

		if (e != NULL)
		{  	   
           selector = { e->coll->rect.x, e->coll->rect.y, 1, 1 };  
		}		
		else
			selector = { 0, 0, 0, 0 };
	}

	// Holding left button, updates selector dimensions with calculateSelector
	if (selector_init && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		app->input->getMousePosition(final_selector_pos);
		final_selector_pos = app->render->screenToWorld(final_selector_pos.x, final_selector_pos.y);

		calculateSelector();
	}

	// Once released left button, the selection is computed. This selection doesn't take buildings and units
	// there are both present. Or buildings (only one) or units (all of them)
	if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
	{
		selector_init = false;
		bool units_only = false;    // If only one unit is on selection, buildings will be excluded
		map<uint, Entity*>::iterator it = active_entities.begin(); 
		int delete_selection = 0;

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
				if (delete_selection == 0)
				{
						delete_selection++;
				}
				// On debug mode, the player will select all the entities.
				if (it->second->faction == COMPUTER && !debug)
					continue;
				else
				{
					

					if (delete_selection == 1)
					{
						selection.clear();
						delete_selection++;
					}

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
	}

	// Now, we give destination for the entities englobed by selection.
	if (!selection.empty() && app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		// Target position is where the player has clicked to move his units.
		iPoint target_position;
		app->input->getMousePosition(target_position);
		target_position = app->render->screenToWorld(target_position.x, target_position.y);
		target_position = app->map->worldToMap(app->map->data.back(), target_position.x, target_position.y);

		//Bunker and bomb useful method
		Entity* e = whichEntityOnMouse();

		map<uint, Entity*>::iterator it = selection.begin();
		for (; it != selection.end(); ++it)
		{
			if (it->second->type == UNIT && it->second->state != DYING)
			{
				Unit *unit = (Unit*)it->second;
				if (selection.size() == 1)
				{
					if (unit->flying)
					{
						unit->path.clear();
						unit->path.push_back(unit->target_to_attack->tile_pos);
						unit->has_target = true;
						unit->state = MOVE;
					}
					else if (app->path->createPath(unit->tile_pos, target_position, unit->id) != -1)
						unit->state = WAITING_PATH_MOVE;
				}
				else
				{
					iPoint target = target_position + unit->distance_to_center_selector;
					if (app->path->createPath(unit->tile_pos, target, unit->id) != -1)
						unit->state = WAITING_PATH_MOVE;
				}

				if (e != NULL)
				{
					if ((it->second->specialization == MARINE && e->specialization == BUNKER))
					{
						((Marine*)unit)->bunker_to_fill = (Bunker*)e;
						app->gui->bunker_to_leave = (Bunker*)e;
					}

					if (it->second->specialization == JIM_RAYNOR)
					{
						JimRaynor *jim = (JimRaynor*)it->second;
						if (e->specialization == BOMB)
							jim->bomb = (Bomb*)e;
						else if (jim->bomb_taken && e->specialization == COMMANDCENTER)
							jim->bomb_activated = true;
					}

					if (it->second->specialization == SCV && (e->type == BUILDING || e->specialization == TANK))
					{
						((Scv*)unit)->target_to_attack = (Building*)e;
						unit->newEntityFound();
					}
					else if (it->second->faction == PLAYER && it->second->type == UNIT && e->faction != PLAYER)
					{
						unit->target_to_attack = e;
						unit->has_focus = true;
						unit->newEntityFound();
					}
				}
			}
		}
	}

	// When we are in building mode, clicking left mouse button put the building on the clicked position.
	// The logic is modified to not walk over building.
	if (building_mode && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (app->map->isAreaWalkable(building_to_place->coll->rect))
		{
			building_to_place->id = ++next_ID;
			building_to_place->tile_pos = app->map->worldToMap(app->map->data.back(), building_to_place->center.x, building_to_place->center.y);
			active_entities.insert(pair<uint, Entity*>(next_ID, building_to_place));
			building_mode = false;

			app->map->changeLogic(building_to_place->coll->rect, NO_WALKABLE);
			recalculatePaths(building_to_place->coll->rect, false);
		}
	}
}

/*------------------WAVE RELATED METHODS--------------------------*/


Entity* EntityManager::searchNearestEntityInRange(Entity* e, bool search_only_in_same_faction, float range) //The method ONLY search and return the nearest entity
{
	Entity* ret = NULL;
	float value = range;
	if (value == -1.0f)
		value = e->range_of_vision;
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); ++it)
	{
		if (it->second != e && it->second->state != DYING && 
			((!search_only_in_same_faction || e->faction == it->second->faction) && (search_only_in_same_faction || e->faction != it->second->faction)))
		{
			float d = abs(e->center.x - it->second->center.x) + abs(e->center.y - it->second->center.y);
			d -= ((e->coll->rect.w / 2 + e->coll->rect.h / 2) / 2 + (it->second->coll->rect.w / 2 + it->second->coll->rect.h / 2) / 2);
			if (d <= value)
			{
				ret = &(*it->second);
				value = d;
			}
		}
	}
	return ret;
}

list<Entity*> EntityManager::searchEntitiesInRange(Entity* e, bool search_only_in_same_faction, float range) //The method search and return the entity in the area
{
	list<Entity*> ret;
	float value = range;
	if (value == -1.0f)
		value = e->range_of_vision;
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); ++it)
	{
		if (it->second != e && it->second->state != DYING && ((!search_only_in_same_faction || e->faction == it->second->faction) && (search_only_in_same_faction || e->faction != it->second->faction)))
		{
			float d = abs(e->center.x - it->second->center.x) + abs(e->center.y - it->second->center.y);
			d -= ((e->coll->rect.w / 2 + e->coll->rect.h / 2) / 2 + (it->second->coll->rect.w / 2 + it->second->coll->rect.h / 2) / 2);
			if (d <= value)
			{
				ret.push_back(it->second);
			}
		}
	}
	return ret;
}

bool EntityManager::checkFocus(Unit* e)
{
	bool ret = false;
	float value = e->range_of_vision;
	if (e->target_to_attack != NULL && e->target_to_attack->state != DYING)
	{
		float d = abs(e->center.x - e->target_to_attack->center.x) + abs(e->center.y - e->target_to_attack->center.y);
		d -= ((e->coll->rect.w / 2 + e->coll->rect.h / 2) / 2 + (e->target_to_attack->coll->rect.w / 2 + e->target_to_attack->coll->rect.h / 2) / 2);

		if (d <= value)
		{
			ret = true;
		}
	}
	if (!ret)
		e->has_focus = false;
	return ret;
}

Entity* EntityManager::searchEnemyToAttack(Entity* e)
{
	Entity* ret = NULL;
	float value = e->range_of_vision;
	map<uint, Entity*>::iterator it = active_entities.begin();
	uint previousMaxHP = 99999;
	for (; it != active_entities.end(); ++it)
	{
		if (it->second != e && it->second->state != DYING && e->faction != it->second->faction)
		{
			float d = abs(e->center.x - it->second->center.x) + abs(e->center.y - it->second->center.y);
			d -= ((e->coll->rect.w / 2 + e->coll->rect.h / 2) / 2 + (it->second->coll->rect.w / 2 + it->second->coll->rect.h / 2) / 2);
			uint maxHP = it->second->current_hp;

			if (ret == NULL && d <= value && maxHP <= previousMaxHP)
			{
				value = d;
				previousMaxHP = maxHP;
				ret = it->second;
			}
			else if (ret != NULL)
			{
				//Only search entities with same type or if type is building, it search units
				if ((ret->type == it->second->type && d <= value && maxHP <= previousMaxHP) ||
					(ret->type == BUILDING && it->second->type == UNIT && d <= e->range_of_vision && maxHP <= previousMaxHP))
				{
					value = d;
					previousMaxHP = maxHP;
					ret = it->second;
				}
			}
		}
	}
	return ret;
}

Entity* EntityManager::searchAllyToHeal(Entity* e)
{
	Entity* ret = NULL;
	float value = e->range_of_vision;
	map<uint, Entity*>::iterator it = active_entities.begin();
	uint previousMaxHP = 99999;
	for (; it != active_entities.end(); ++it)
	{
		if (it->second != e && it->second->state != DYING && e->faction == it->second->faction && it->second->type == UNIT && 
			it->second->specialization != TANK && it->second->current_hp < it->second->max_hp)
		{
			float d = abs(e->center.x - it->second->center.x) + abs(e->center.y - it->second->center.y);
			d -= ((e->coll->rect.w / 2 + e->coll->rect.h / 2) / 2 + (it->second->coll->rect.w / 2 + it->second->coll->rect.h / 2) / 2);
			uint maxHP = it->second->current_hp;

			if (d <= value && maxHP <= previousMaxHP)
			{
				value = d;
				previousMaxHP = maxHP;
				ret = it->second;
			}
		}
	}
	return ret;
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
	fPoint point_to_draw;

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

void EntityManager::recalculatePaths(const SDL_Rect &rect, bool walkable)
{
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); ++it)
	{
		if (it->second->type == UNIT)
		{
			Unit *unit = (Unit*)it->second;
			if (!unit->flying)
			{
				if ((unit->state == WAITING_PATH_MOVE || unit->state == WAITING_PATH_MOVE_ALERT || unit->state == WAITING_PATH_MOVE_ALERT_TO_ATTACK) && 
					app->path->recalculatePath(it->second->tile_pos, it->first));
				else if (unit->path.size() > 0 && app->path->createPath(it->second->tile_pos, unit->path.back(), it->first) != -1)
				{
					if (unit->state == MOVE)
						unit->state = WAITING_PATH_MOVE;
					else if (unit->state == MOVE_ALERT)
						unit->state = WAITING_PATH_MOVE_ALERT;
					else if (unit->state == MOVE_ALERT_TO_ATTACK)
						unit->state = WAITING_PATH_MOVE_ALERT_TO_ATTACK;
				}
				else if (walkable == false)
				{
					// Right now, there is only one logic map and only one logic layer, so we must not iterate them.
					list<MapLayer*>::iterator layer = app->map->data.back().layers.begin();
					while (layer != app->map->data.back().layers.end())
					{
						iPoint first_tile = app->map->worldToMap(app->map->data.back(), rect.x, rect.y);
						iPoint last_tile = app->map->worldToMap(app->map->data.back(), rect.x + rect.w, rect.y + rect.h);

						for (int y = first_tile.y; y < last_tile.y; ++y)
						{
							for (int x = first_tile.x; x < last_tile.x; ++x)
							{
								if (unit->path.size() > 0)
								{
									if (!app->path->isWalkable(unit->path.back()))//if the origin and the destination isn't walkable
									{
										unit->path.clear();
										unit->path.push_back(app->path->findNearestWalkableTile(unit->tile_pos, app->game_manager->command_center_position, 25));
										unit->has_target = true;
										unit->state = MOVE;
									}
								}
								else if (unit->tile_pos == (iPoint(x, y)))//if without path and they are no walkable tiles
								{
									unit->path.push_back(app->path->findNearestWalkableTile(unit->tile_pos, app->game_manager->command_center_position, 25));
									unit->has_target = true;
									unit->state = MOVE;
								}
							}
						}
						++layer;
					}
				}
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

void EntityManager::entityManualCreation()
{
	iPoint position;
	if (app->input->getKey(SDL_SCANCODE_KP_1) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, MARINE);
	}

	if (app->input->getKey(SDL_SCANCODE_KP_2) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, ZERGLING);
	}

	if (app->input->getKey(SDL_SCANCODE_KP_3) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, SCV);
	}

	if (app->input->getKey(SDL_SCANCODE_KP_4) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, MUTALISK);
	}

	if (app->input->getKey(SDL_SCANCODE_KP_5) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, HYDRALISK);
	}

	if (app->input->getKey(SDL_SCANCODE_KP_9) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, ULTRALISK);
	}

	if (app->input->getKey(SDL_SCANCODE_KP_6) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, TANK);
	}

	if (app->input->getKey(SDL_SCANCODE_KP_7) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, MEDIC);
	}

	if (app->input->getKey(SDL_SCANCODE_KP_8) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, FIREBAT);
	}

	if (app->input->getKey(SDL_SCANCODE_J) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, JIM_RAYNOR);
	}

	if (app->input->getKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		app->input->getMousePosition(position);
		position = app->render->screenToWorld(position.x, position.y);
		addEntity(position, BARRACK);
	}
}

void EntityManager::updateFogOfWar()
{
	//FOG_OF_WAR 2 - "Update Fog of War" function. Called once every frame.
	//Drawing all a circle on the map for each allied unit and building
	
	if (active_entities.empty() == false)
	{
		map<uint, Entity*>::iterator it = active_entities.begin();
		while (it != active_entities.end())
		{
			 if (it->second->faction == PLAYER)
				app->fog_of_war->drawCircle(it->second->center.x, it->second->center.y, it->second->range_of_vision);
			it++;
		}
	}

	/*if (buildingList.empty() == false)
	{
		std::list<Building*>::iterator buildIt = buildingList.begin();
		{
			while (buildIt != buildingList.end())
			{
				if ((*buildIt)->stats.player == PLAYER && (*buildIt)->state != BS_DEAD)
				{
					App->fogOfWar->DrawCircle((*buildIt)->GetCollider().x + (*buildIt)->GetCollider().w / 2, (*buildIt)->GetCollider().y + (*buildIt)->GetCollider().h / 2, 250);
				}
				buildIt++;
			}
		}
	}*/
}