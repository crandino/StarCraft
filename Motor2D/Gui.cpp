#include "App.h"
#include "p2Log.h"
#include "Render.h"
#include "PathFinding.h"
#include "Input.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Gui.h"
#include "Map.h"
#include "Window.h"
#include "Textures.h"

#include "GuiImage.h"
#include "GuiCursor.h"

using namespace std;

Gui::Gui() : Module()
{
	name.assign("gui");
}

// Destructor
Gui::~Gui()
{}

// Called before render is available
bool Gui::awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name.assign(conf.child("atlas").attribute("file").as_string());

	return ret;
}

// Called before the first frame
bool Gui::start()
{
	atlas = app->tex->loadTexture(atlas_file_name.data());
	//terran_console = app->tex->loadTexture("TerranConsole/tconsole.png");
	
	// HUD
	ui_terran = app->gui->createImage(NULL, { 0, 292, 640, 188 });
	ui_terran->setLocalPos(0, 292);
	ui_terran->interactive = false;
	ui_terran->can_focus = true;

	rectangle_map = app->gui->createImage(NULL, { 0, 0, 132, 132 });
	rectangle_map->setLocalPos(4, 346);
	rectangle_map->interactive = true;
	//rectangle_map->setListener(this);
	rectangle_map->can_focus = true;

	rectangle_command = app->gui->createImage(NULL, { 0, 152, 37, 34 });
	rectangle_command->setLocalPos(505, 358);
	rectangle_command->interactive = true;
	rectangle_command->can_focus = true;

	rectangle_command_2 = app->gui->createImage(NULL, { 48, 152, 37, 34 });
	rectangle_command_2->setLocalPos(551, 358);
	rectangle_command_2->interactive = true;
	rectangle_command_2->can_focus = true;

	// HUD Command Center
	ui_create_bot = app->gui->createImage(NULL, { 256, 28, 37, 34 });
	ui_create_bot->setLocalPos(505, 358);
	ui_create_bot->setListener(this);
	ui_create_bot->interactive = false;
	ui_create_bot->can_focus = true;
	ui_create_bot->draw_element = false;

	ui_create_builds = app->gui->createImage(NULL, { 298, 28, 37, 34 });
	ui_create_builds->setLocalPos(551, 358);
	ui_create_builds->interactive = false;
	ui_create_builds->can_focus = true;
	ui_create_builds->setListener(this);
	ui_create_builds->draw_element = false;

	// CURSOR
	SDL_ShowCursor(SDL_DISABLE);
	cursor = app->gui->createCursor(app->tex->loadTexture("Cursor/StarCraftCursors.png"));
	uint w, h; app->win->getWindowSize(w, h);
	cursor_offset.x = (w * 0.01f); // 10% of map width
	cursor_offset.y = (h * 0.01f); // 10% of map height
	scroll_speed = 1.0f;

	map_limits = { app->map->data.front().width * app->map->data.front().tile_width,
		app->map->data.front().height * app->map->data.front().tile_height };

	// CIRCLES OF SELECTIOM
	circles_of_selection = app->tex->loadTexture("Selection/Selection_circles.png");
	lifes_tex = app->tex->loadTexture("Cursor/StarCraftCursors.png");

	green_life = { 486, 3, 4, 5 };
	yellow_life = { 496, 3, 4, 5 };
	red_life = { 501, 3, 4, 5 };
	white_life = { 491, 3, 4, 5 };	



	// To show walkability on building mode
	path_walkability = app->tex->loadTexture("maps/Path_tiles.png");

	return true;
}

void Gui::onGui(GuiElements* ui, GUI_EVENTS event)
{
	if (ui == ui_create_builds)
	{
		switch (event)
		{

		case(MOUSE_LCLICK_DOWN) :
			app->entity_manager->create_bunker = true;
			break;

		case(MOUSE_LCLICK_DOWN_REPEAT) :
			app->entity_manager->create_bunker = true;
			break;
		}
	}

	if (ui == ui_create_bot)
	{
		switch (event)
		{

		case(MOUSE_LCLICK_DOWN) :
			app->entity_manager->create_SCV = true;
			break;

		case(MOUSE_LCLICK_DOWN_REPEAT) :
			app->entity_manager->create_SCV = true;
			break;
		}
	}
}

void Gui::drawHudSelection(SPECIALIZATION  selection)
{
	switch (selection)
	{
	      case (COMMANDCENTER) :
			  //Desactivate quad background
		      rectangle_command->draw_element = false;
		      rectangle_command->interactive = false;
		      rectangle_command->can_focus = false;
			  rectangle_command_2->draw_element = false;

			  //Activate new images
		      ui_create_bot->draw_element = true; 
			  ui_create_bot->interactive = true;
			  ui_create_builds->draw_element = true;
			  ui_create_builds->interactive = true;


		      break;

		  case (NOTYPE) :
			  //Desactivate all the options of Entities
			  ui_create_bot->draw_element = false;
			  ui_create_bot->interactive = false;
			  ui_create_builds->draw_element = false;
			  ui_create_builds->draw_element = false;

			  //Activate default entities
			  rectangle_command->draw_element = true;
			  rectangle_command_2->draw_element = true;
			  rectangle_command->interactive = true;
			  rectangle_command->can_focus = true;
			  break;
	}
}

// Update all guis
bool Gui::preUpdate()
{
	return true;
}

bool Gui::update(float dt)
{

	if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	// Cursor -> check for camera displacement.
	iPoint pos = cursor->getLocalPos();
	cursor->current_animation = &cursor->idle;
	// Checking displacement for X axis.
	if (pos.x < cursor_offset.x) // Left
	{
		app->render->camera.x += (app->render->camera.x + (scroll_speed * dt) <= 0 ? (scroll_speed * dt) : -app->render->camera.x);
		cursor->current_animation = &cursor->left_disp;
	}
	else if (pos.x > (app->render->camera.w - cursor_offset.x)) // Right
	{
		app->render->camera.x -= (app->render->camera.x - (scroll_speed * dt) >= app->render->camera.w - map_limits.x ? (scroll_speed * dt) : map_limits.x - app->render->camera.w + app->render->camera.x);
		cursor->current_animation = &cursor->right_disp;
	}
	// Checking displacement for Y axis.
	if (pos.y < cursor_offset.y) // Up
	{
		app->render->camera.y += (app->render->camera.y + (scroll_speed * dt) <= 0 ? (scroll_speed * dt) : -app->render->camera.y);
		cursor->current_animation = &cursor->up_disp;
	}
	else if (pos.y > (app->render->camera.h - cursor_offset.y)) // Down
	{
		app->render->camera.y -= (app->render->camera.y - (scroll_speed * dt) >= app->render->camera.h - map_limits.y ? (scroll_speed * dt) : map_limits.y - app->render->camera.h + app->render->camera.y);
		cursor->current_animation = &cursor->down_disp;
	}		

	const GuiElements* mouse_hover = findMouseHover();
	if (mouse_hover &&
		mouse_hover->can_focus == true &&
		app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
		focus = mouse_hover;

	
	
	// Now the iteration for input and update
	for (list<GuiElements*>::iterator node = elements.begin(); node != elements.end(); node++)
	{
		GuiElements* gui_test = *node;
		if (gui_test->interactive == true)
		    gui_test->checkInput(mouse_hover, focus);
	}
		

	for (list<GuiElements*>::iterator node = elements.begin(); node != elements.end(); node++)
	{
		GuiElements* gui_test = *node;
		gui_test->update(mouse_hover, focus);
		if (gui_test->getType() == CURSOR)
		{
			gui_test->update();
		}
	}

	return true;
}



// Called after all Updates
bool Gui::postUpdate()
{
	//Check if we have entities selected
	if (app->entity_manager->selection.size() == 0)
	{
		drawHudSelection(SPECIALIZATION::NOTYPE);
	}
	// Blit of Selection Circles and Lifes
	for (map<uint, Entity*>::iterator it = app->entity_manager->selection.begin(); it != app->entity_manager->selection.end(); ++it)
	{
		// Circle selection blitting
		Entity *e = it->second;
		if (e->specialization == SCV)
			app->render->blit(circles_of_selection, e->center.x - e->selection_type.w / 2 - e->circle_selection_offset.x, e->center.y - e->circle_selection_offset.y, &e->selection_type);
		else
			app->render->blit(circles_of_selection, e->center.x - e->selection_type.w / 2, e->center.y - e->circle_selection_offset.y, &e->selection_type);
	}

	for (map<uint, Entity*>::iterator it = app->entity_manager->active_entities.begin(); it != app->entity_manager->active_entities.end(); ++it)
	{
		it->second->draw();
	}



	for (map<uint, Entity*>::iterator it = app->entity_manager->selection.begin(); it != app->entity_manager->selection.end(); ++it)
	{
		// Life counter blitting
		Entity *e = it->second;
		if (e->current_hp > 0)
		{
			uint bars_to_draw = ceil((e->max_hp_bars * ((float)e->current_hp / (float)e->max_hp)) + 1);
			uint bar = 1;
			for (; bar < bars_to_draw; ++bar)
				app->render->blit(lifes_tex, e->center.x + e->offset_life.x + (bar * green_life.w), e->center.y + e->offset_life.y, &green_life);
			for (; bar <= e->max_hp_bars; ++bar)
				app->render->blit(lifes_tex, e->center.x + e->offset_life.x + (bar * white_life.w), e->center.y + e->offset_life.y, &white_life);
		}


		if (it->second->specialization == SPECIALIZATION::COMMANDCENTER)
			drawHudSelection(COMMANDCENTER);
	}
		
	
	list<GuiElements*>::iterator item;

	for (item = elements.begin(); item != elements.end(); item++)
	{
		GuiElements* gui = *item;
		if (gui->draw_element == true)
		{
			if (gui->getType() != CURSOR)
				gui->draw();
		}

		if (debug == true && gui->draw_element == true)
			gui->debugDraw();
	}

	cursor->draw();

	if (debug)
	{
		iPoint to_draw; app->input->getMousePosition(to_draw);
		to_draw = app->render->screenToWorld(to_draw.x, to_draw.y);

		if (app->path->isWalkable(app->map->worldToMap(app->map->data.back(), to_draw.x, to_draw.y)))
		{
			SDL_Rect r = { 1, 1, 8, 8 };
			app->render->blit(path_walkability, to_draw.x, to_draw.y, &r);
		}
		else
		{
			SDL_Rect r = { 10, 1, 8, 8 };
			app->render->blit(path_walkability, to_draw.x, to_draw.y, &r);
		}
	}	
	
	return true;
}

// Called before quitting
bool Gui::cleanUp()
{
	LOG("Freeing GUI");

	list<GuiElements*>::iterator item;

	for (item = elements.begin(); item != elements.end(); item++)
		RELEASE(*item);

	elements.clear();

	return true;
}

// Create a simple image
GuiImage* Gui::createImage(const char* filename)
{
	GuiImage* ret = NULL;
	SDL_Texture* texture = app->tex->loadTexture(filename);

	if (texture != NULL)
	{
		ret = new GuiImage(texture);
		elements.push_back(ret);
	}

	return ret;
}

// Create a simple image
GuiImage* Gui::createImage(const SDL_Texture* texture, const SDL_Rect& section)
{
	GuiImage* ret = NULL;
	if (texture == NULL)
	{
		texture = atlas;
	}
	ret = new GuiImage(texture, section);
	elements.push_back(ret);

	return ret;
}

//Create cursor
GuiCursor* Gui::createCursor(const SDL_Texture* texture){

	GuiCursor* ret = NULL;

	ret = new GuiCursor(texture);
	elements.push_back(ret);
	
	return ret;
}

//
SDL_Rect Gui::mouseQuad(iPoint init_mouse)
{
	iPoint current_mouse;
	app->input->getMousePosition(current_mouse);
	SDL_Rect rect = { init_mouse.x, init_mouse.y, current_mouse.x - init_mouse.x, current_mouse.y - init_mouse.y };
	app->render->DrawQuad(rect, 65, 105, 225, 100, true, false);
	return rect;
}

// Called after all Updates
const GuiElements* Gui::findMouseHover()
{
	iPoint mouse;
	app->input->getMousePosition(mouse);

	for (list<GuiElements*>::reverse_iterator item = elements.rbegin(); item != elements.rend(); ++item)
	{
		GuiElements* gui_test = *item;
		if (gui_test->interactive == true)
		{
			SDL_Rect r = gui_test->getScreenRect();
			if (mouse.x >= r.x && mouse.x <= r.x + r.w && mouse.y >= r.y && mouse.y <= r.y + r.y)
			{
				elements.reverse();
                return gui_test;
			}
				
		}
	}

	elements.reverse();
	return nullptr;
}

// const getter for atlas
const SDL_Texture* Gui::getAtlas() const
{
	return atlas;
}




