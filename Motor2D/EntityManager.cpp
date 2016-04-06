#include "App.h"
#include "EntityManager.h"
#include "Input.h"
#include "Window.h"
#include "p2Log.h"
#include <algorithm>
#include "PathFinding.h"

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
    circle_characters = app->tex->loadTexture("StarCraftCursors.png");

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
		break;
	}

	if (e != NULL)
	{
		e->id = ++next_ID;
		active_entities.insert(pair<uint, Entity*>(next_ID, e));
	}

	return e;
}
 
// Called each loop iteration
bool EntityManager::preUpdate()
{
	//Marine Creation
	if (app->input->getKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		iPoint p;
		app->input->getMousePosition(p);
		p = app->render->screenToWorld(p.x, p.y);
		addEntity(p, MARINE);

		//marine = addEntity(p, MARINE);
		//if (e != NULL) remove(e->id);		
	}

	if (app->input->getKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		angle = marine->direction.getAngle();
		angle += 18.f;
		marine->direction.setAngle(angle);

		LOG("Marine angle: %f", marine->direction.getAngle());
	}

	if (app->input->getKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		iPoint p;
		app->input->getMousePosition(p);
		p = app->render->screenToWorld(p.x, p.y);
		addEntity(p, COMMANDCENTER);
		//if (e != NULL) remove(e->id);		
	}

	if (app->input->getKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		iPoint p;
		app->input->getMousePosition(p);
		p = app->render->screenToWorld(p.x, p.y);
		addEntity(p, ZERGLING);
		//if (e != NULL) remove(e->id);		
	}
		

	// Clicking and holding left button, starts a selection
	if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		selector_init = true;
		selection.clear();
		selection_ordered.clear();
		app->input->getMousePosition(initial_selector_pos);
	}

	// Holding left button, updates selector dimensions
	if (selector_init && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		app->input->getMousePosition(final_selector_pos);
		calculateSelector();

	    map<uint, Entity*>::iterator it = active_entities.begin();
		for (; it != active_entities.end(); ++it)
			if (it->second->pos.x <= selector.x + selector.w &&  it->second->pos.x >= selector.x
				&& it->second->pos.y <= selector.y + selector.h &&  it->second->pos.y >= selector.y)
				selection.insert(pair<uint, Entity*>(it->first, it->second));  

	}		

	// Once released left button, the selection is computed
	if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
		selector_init = false;

	//Selection
	if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		selector_init = true;
		selection.clear();
		selection_ordered.clear();
		app->input->getMousePosition(initial_selector_pos);
		initial_selector_pos = app->render->screenToWorld(initial_selector_pos.x, initial_selector_pos.y);
	}

	// Holding left button, updates selector dimensions
	if (selector_init && app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		app->input->getMousePosition(final_selector_pos);
		final_selector_pos = app->render->screenToWorld(final_selector_pos.x, final_selector_pos.y);
		calculateSelector();
		/*iPoint cursor_pos = app->render->screenToWorld(final_selector_pos.x, final_selector_pos.y);
		selector.x = cursor_pos.x;
		selector.y = cursor_pos.y;*/


		map<uint, Entity*>::iterator it = active_entities.begin();
		for (; it != active_entities.end(); ++it)
		{
			if (it->second->pos.x + 32  <= selector.x + selector.w &&  it->second->pos.x + 32 >= selector.x
				&& it->second->pos.y + 32 <= selector.y + selector.h &&  it->second->pos.y + 32 >= selector.y)
				selection.insert(pair<uint, Entity*>(it->first, it->second));
		}

	}

	////TEST
	//if (app->input->getKey(SDL_SCANCODE_S) == KEY_UP)
	//{
	//	app->input->getMousePosition(tile_start_path);
	//	start_path = true;
	//}
	//------------------------------

	if (app->input->getMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_DOWN /*&& selection.begin() != selection.end()*/)
	{
		iPoint tmp_mouse_position;
		app->input->getMousePosition(tmp_mouse_position);
		tmp_mouse_position = app->render->screenToWorld(tmp_mouse_position.x, tmp_mouse_position.y);
		tmp_mouse_position = app->map->worldToMap(app->map->data.back(), tmp_mouse_position.x, tmp_mouse_position.y);
		map<uint, Entity*>::iterator it = selection.begin();
		for (; it != selection.end(); ++it)
		{
			if (it->second->type == MARINE)
			{
				app->path->createPath(it->second->tile_pos, tmp_mouse_position);
				it->second->path = app->path->getLastPath();
				if (it->second->path.size() != 0)
					it->second->path.erase(it->second->path.begin());
			}
		}
	}

	return true;
} 

// Called each loop iteration
bool EntityManager::update(float dt)
{
	map<uint, Entity*>::iterator it = selection.begin();
	for (; it != selection.end(); ++it)
	{
		it->second->move(dt);
	}

	return true;
}

// Called each loop iteration
bool EntityManager::postUpdate()
{
	// Info about the bricks
	static char title[256];
	sprintf_s(title, 256, "Active units: %d  Inactive units: %d",
	active_entities.size(), inactive_entities.size());
	//app->win->setTitle(title);	

	// Basic selection. Entities surrounded by black rectangles.
	map<uint, Entity*>::iterator it2 = selection.begin();
	for (; it2 != selection.end(); ++it2)
	{
		if (it2->second->type == MARINE)
		{
			rectangle section_circle = { 52, 56, 27, 17 };
			app->render->blit(circle_characters, it2->second->pos.x + 19, it2->second->pos.y + 32, (SDL_Rect*)&section_circle, 1.0f);
		}
		else if (it2->second->type == ZERGLING)
		{
			rectangle section_circle = { 52, 56, 27, 17 };
			app->render->blit(circle_characters, it2->second->pos.x + 50, it2->second->pos.y + 55, (SDL_Rect*)&section_circle, 1.0f);
		}		
	}
	
	for (it2 = selection.begin(); it2 != selection.end(); ++it2)
	{
		//app->render->DrawQuad({ it2->second->pos.x, it2->second->pos.y, 64, 64 }, 35, 114, 48, 255, false, true);
		rectangle section_life = { 46, 79, 26, 8 };
		app->render->blit(circle_characters, it2->second->pos.x + 20.5, it2->second->pos.y + 48, (SDL_Rect*)&section_life, 1.0f);
		for (int i = 0, a = 0; i < it2->second->hp; i++)
		{
			rectangle greenquadlife = { 225, 32, 3, 4 };
			app->render->blit(circle_characters, it2->second->pos.x + 22 + a, it2->second->pos.y + 50, (SDL_Rect*)&greenquadlife, 1.0f);
			greenquadlife.x += 4;
			a += 4;
		}

		//app->render->DrawCircle(it2->second->pos.x + 32, it2->second->pos.y + 32, it2->second->tex_height/5, 35, 114, 48, 255, false);
	}
	
	// Entities Drawing
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); ++it)
		it->second->draw();

	// Drawing selector (white rectangle)
	if (selector_init) app->render->DrawQuad(selector, 35, 114, 48, 255, false, false);

	return true;
}

// Called before quitting
bool EntityManager::cleanUp()
{
	map<uint, Entity*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); it++)
		delete it->second;

	it = inactive_entities.begin();
	for (; it != inactive_entities.end(); it++)
		delete it->second;

	active_entities.clear();
	inactive_entities.clear();
	selection.clear();
	selection_ordered.clear();

	return true;
}

// Remove an entity using its ID
bool EntityManager::remove(uint id)
{
	if (active_entities.erase(id) > 0)
	{
		Entity *e = getEntity(id);
		inactive_entities.insert(pair<uint, Entity*>(id, e));

		selection.erase(id);
		selection_ordered.clear();
		return true;
	}
	return false;
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

// CalculateSelector: Method that computes the dimensions of the white rectangle selector.
void EntityManager::calculateSelector()
{
	int selector_width = abs(final_selector_pos.x - initial_selector_pos.x);
	int selector_height = abs(final_selector_pos.y - initial_selector_pos.y);
	int selector_pos_x = (initial_selector_pos.x < final_selector_pos.x ? initial_selector_pos.x : final_selector_pos.x);
	int selector_pos_y = (initial_selector_pos.y < final_selector_pos.y ? initial_selector_pos.y : final_selector_pos.y);
	selector = { selector_pos_x, selector_pos_y, selector_width, selector_height };
}