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
#include "GuiLabel.h"


#include "Bunker.h"

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
	
	// HUD---------------------------------------------------------------------
	ui_terran = app->gui->createImage(NULL, { 0, 292, 640, 188 });
	ui_terran->setLocalPos(0, 292);
	ui_terran->interactive = false;
	ui_terran->can_focus = true;

	rectangle_map = app->gui->createImage(NULL, { 0, 0, 132, 132 });
	rectangle_map->setLocalPos(4, 346);
	rectangle_map->interactive = true;
	rectangle_map->can_focus = true;

	rectangle_command = app->gui->createImage(NULL, { 0, 152, 37, 34 });
	rectangle_command->setLocalPos(505, 358);
	rectangle_command->interactive = false;
	rectangle_command->can_focus = false;

	rectangle_command_2 = app->gui->createImage(NULL, { 48, 152, 37, 34 });
	rectangle_command_2->setLocalPos(551, 358);
	rectangle_command_2->interactive = false;
	rectangle_command_2->can_focus = false;

	rectangle_command_3 = app->gui->createImage(NULL, { 96, 152, 37, 34 });
	rectangle_command_3->setLocalPos(597, 358);
	rectangle_command_3->interactive = false;
	rectangle_command_3->can_focus = false;

	rectangle_command_4 = app->gui->createImage(NULL, { 141, 152, 37, 34 });
	rectangle_command_4->setLocalPos(505, 398);
	rectangle_command_4->interactive = false;
	rectangle_command_4->can_focus = false;

	rectangle_command_5 = app->gui->createImage(NULL, { 186, 152, 37, 34 });
	rectangle_command_5->setLocalPos(551, 398);
	rectangle_command_5->interactive = false;
	rectangle_command_5->can_focus = false;

	rectangle_command_6 = app->gui->createImage(NULL, { 48, 195, 37, 34 });
	rectangle_command_6->setLocalPos(597, 398);
	rectangle_command_6->interactive = false;
	rectangle_command_6->can_focus = false;

	rectangle_command_7 = app->gui->createImage(NULL, { 96, 195, 37, 34 });
	rectangle_command_7->setLocalPos(505, 438);
	rectangle_command_7->interactive = false;
	rectangle_command_7->can_focus = false;

	rectangle_command_8 = app->gui->createImage(NULL, { 141, 195, 37, 34 });
	rectangle_command_8->setLocalPos(551, 438);
	rectangle_command_8->interactive = false;
	rectangle_command_8->can_focus = false;

	rectangle_command_9 = app->gui->createImage(NULL, { 186, 195, 37, 34 });
	rectangle_command_9->setLocalPos(597, 438);
	rectangle_command_9->interactive = false;
	rectangle_command_9->can_focus = false;

	// HUD Command Center------------------------------------------------------
	//Buildings Button
	ui_create_builds = app->gui->createImage(NULL, { 298, 28, 37, 34 });
	ui_create_builds->setLocalPos(551, 358);
	ui_create_builds->interactive = false;
	ui_create_builds->can_focus = true;
	ui_create_builds->setListener(this);
	ui_create_builds->draw_element = false;

	//Create Bunkers
	ui_create_bunker = app->gui->createImage(NULL, { 256, 64, 37, 34 });
	ui_create_bunker->setLocalPos(505, 358);
	ui_create_bunker->interactive = false;
	ui_create_bunker->can_focus = true;
	ui_create_bunker->setListener(this);
	ui_create_bunker->draw_element = false;

	//Create Barraks
	ui_create_barraks = app->gui->createImage(NULL, { 298, 64, 37, 34 });
	ui_create_barraks->setLocalPos(551, 358);
	ui_create_barraks->interactive = false;
	ui_create_barraks->can_focus = true;
	ui_create_barraks->setListener(this);
	ui_create_barraks->draw_element = false;

	//Create Turrets
	ui_create_turrets = app->gui->createImage(NULL, { 338, 64, 37, 34 });
	ui_create_turrets->setLocalPos(597, 358);
	ui_create_turrets->interactive = false;
	ui_create_turrets->can_focus = true;
	ui_create_turrets->setListener(this);
	ui_create_turrets->draw_element = false;

	//Create factory
	ui_create_factory = app->gui->createImage(NULL, { 377, 64, 37, 34 });
	ui_create_factory->setLocalPos(505, 398);
	ui_create_factory->interactive = false;
	ui_create_factory->can_focus = true;
	ui_create_factory->setListener(this);
	ui_create_factory->draw_element = false;

	//Create starport
	ui_create_starport = app->gui->createImage(NULL, { 256, 101, 37, 34 });
	ui_create_starport->setLocalPos(551, 398);
	ui_create_starport->interactive = false;
	ui_create_starport->can_focus = true;
	ui_create_starport->setListener(this);
	ui_create_starport->draw_element = false;

	//SCV Button
	ui_create_bot = app->gui->createImage(NULL, { 256, 28, 37, 34 });
	ui_create_bot->setLocalPos(505, 358);
	ui_create_bot->setListener(this);
	ui_create_bot->interactive = false;
	ui_create_bot->can_focus = true;
	ui_create_bot->draw_element = false;
	
	//Bunker buttons------------------------------------------------------------
	ui_leave_bunker = app->gui->createImage(NULL, { 256, 94, 36, 33 });
	ui_leave_bunker->setLocalPos(505, 358);
	ui_leave_bunker->setListener(this);
	ui_leave_bunker->interactive = false;
	ui_leave_bunker->can_focus = true;
	ui_leave_bunker->draw_element = false;

	//HUD Label---------------------------------------------------------------
	number_of_wave = app->gui->createLabel("0", 1);
	number_of_wave->center();
	number_of_wave->setLocalPos(number_of_wave->getScreenPos().x, number_of_wave->getScreenPos().y - 220);
	number_of_wave->interactive = false;


	//HUD  Mineral and Gass-------------------------------------------------
	//Image
	ui_mineral = app->gui->createImage(NULL, { 7, 202, 15, 13 });
	ui_mineral->setLocalPos(490, 6);

	//Number of minerals
	number_of_minerals = app->gui->createLabel("0", 2);
	number_of_minerals->setLocalPos(508, 4);
	number_of_minerals->interactive = false;

	//Image
	ui_gas = app->gui->createImage(NULL, { 27, 202, 15, 13 });
	ui_gas->setLocalPos(550, 6);

	//Label gass
	number_of_gass = app->gui->createLabel("0", 2);
	number_of_gass->setLocalPos(568, 4);
	number_of_gass->interactive = false;


	//HUD Info SCV and Bunker------------------------------------------------
	info_scv = app->gui->createImage(NULL, { 440, 4, 77, 36 });
	info_scv->setLocalPos(505, 320);
	info_scv->interactive = false;
	info_scv->draw_element = false;

	info_bunker = app->gui->createImage(NULL, { 440, 43, 126, 33 });
	info_bunker->setLocalPos(545, 323);
	info_bunker->interactive = false;
	info_bunker->draw_element = false;

	
	// CURSOR-----------------------------------------------------------------
	SDL_ShowCursor(SDL_DISABLE);
	cursor = app->gui->createCursor(app->tex->loadTexture("Cursor/StarCraftCursors.png"));
	uint w, h; app->win->getWindowSize(w, h);
	cursor_offset.x = (w * 0.01f); // 10% of map width
	cursor_offset.y = (h * 0.01f); // 10% of map height
	scroll_speed = 1.0f;

	map_limits = { app->map->data.front().width * app->map->data.front().tile_width,
		app->map->data.front().height * app->map->data.front().tile_height };

	// CIRCLES OF SELECTIOM----------------------------------------------------
	circles_of_selection = app->tex->loadTexture("Selection/Selection_circles.png");
	lifes_tex = app->tex->loadTexture("Cursor/StarCraftCursors.png");

	green_life = { 486, 3, 4, 5 };
	yellow_life = { 496, 3, 4, 5 };
	red_life = { 501, 3, 4, 5 };
	white_life = { 491, 3, 4, 5 };	

	// To show walkability on building mode-------------------------
	path_walkability = app->tex->loadTexture("maps/Path_tiles.png");

	// Create the Minimap
	minimap = createMinimap({ 6, 348, 127, 127 }, "Minimap/minimap.png", "Minimap/area.png");

	return true;
}

Minimap* Gui::createMinimap(SDL_Rect rect, const char *pathTex, const char *pathArea)
{
	Minimap* ret = nullptr;

	ret = new Minimap(rect);

	SDL_Texture* texture = app->tex->loadTexture(pathTex);// cargar textura
	SDL_Texture* area = app->tex->loadTexture(pathArea);// cargar area

	if (texture)
	{
		ret->SetAttributes(&app->entity_manager->active_entities, texture, area);
	}
	else
	{
		ret->CleanUp();
		ret = NULL;
	}

	return ret;
}




void Gui::onGui(GuiElements* ui, GUI_EVENTS event)
{
	if (ui == ui_create_builds)
	{
		switch (event)
		{

		case(MOUSE_LCLICK_DOWN) :
			openBuildingMenu();
			break;
		}
	}

	if (ui == ui_create_bot)
	{
		switch (event)
		{
		case(MOUSE_ENTERS) :
			info_scv->draw_element = true;
			break;

		case(MOUSE_LEAVES) :
			info_scv->draw_element = false;
			break;

		case(MOUSE_LCLICK_DOWN) :
			if (app->game_manager->mineral_resources >= 50)
			app->entity_manager->create_SCV = true;
			info_scv->draw_element = false;
			break;

		/*case(MOUSE_LCLICK_DOWN_REPEAT) :
			app->entity_manager->create_SCV = true;
			break;*/
		}

		if (ui == ui_create_bunker)
		{
			switch (event)
			{

			case(MOUSE_ENTERS) :
				info_bunker->draw_element = true;
				break;

			case(MOUSE_LEAVES) :
				info_bunker->draw_element = false;
				break;

			case(MOUSE_LCLICK_DOWN) :
				if (app->game_manager->gas_resources >= 50 && app->game_manager->mineral_resources >= 25)
					app->entity_manager->create_bunker = true;
				info_bunker->draw_element = false;
				break;

				/*case(MOUSE_LCLICK_DOWN_REPEAT) :
				app->entity_manager->create_bunker = true;
				break;*/
			}
		}
	}
	
	if (ui == ui_leave_bunker)
	{
		switch (event)
		{
			//Method to leave the bunker
		case(MOUSE_LCLICK_DOWN) :
			
			bunker_to_leave->getEntitiesOutside();
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
			  rectangle_command_2->draw_element = false;
			  rectangle_command_3->draw_element = true;
			  rectangle_command_4->draw_element = true;
			  rectangle_command_5->draw_element = true;
			  rectangle_command_6->draw_element = true;
			  rectangle_command_7->draw_element = true;
			  rectangle_command_8->draw_element = true;
			  rectangle_command_9->draw_element = true;
			  ui_leave_bunker->draw_element = false;
			  ui_leave_bunker->interactive = false;

			  //Activate new images
		      ui_create_bot->draw_element = true; 
			  ui_create_bot->interactive = true;
			  ui_create_builds->draw_element = true;
			  ui_create_builds->interactive = true;
			  
		      break;
			  
		  case (BUNKER) :
			  //Desactivate quad background
			  rectangle_command->draw_element = false;
			  rectangle_command_2->draw_element = true;
			  rectangle_command_3->draw_element = true;
			  rectangle_command_4->draw_element = true;
			  rectangle_command_5->draw_element = true;
			  rectangle_command_6->draw_element = true;
			  rectangle_command_7->draw_element = true;
			  rectangle_command_8->draw_element = true;
			  rectangle_command_9->draw_element = true;
			  ui_create_bot->draw_element = false;
			  ui_create_bot->interactive = false;
			  ui_create_builds->draw_element = false;
			  ui_create_builds->interactive = false;

			  //Activate new images
			  ui_leave_bunker->draw_element = true;
			  ui_leave_bunker->interactive = true;

			  break;
			  
		  case (NOTYPE) :
			  //Desactivate all the options of Entities
			  ui_create_bot->draw_element = false;
			  ui_create_bot->interactive = false;
			  ui_create_builds->draw_element = false;
			  ui_create_builds->interactive = false;
			  ui_leave_bunker->draw_element = false;
			  ui_leave_bunker->interactive = false;

			  //Activate default entities
			  rectangle_command->draw_element = true;
			  rectangle_command_2->draw_element = true;
			  rectangle_command_3->draw_element = true;
			  rectangle_command_4->draw_element = true;
			  rectangle_command_5->draw_element = true;
			  rectangle_command_6->draw_element = true;
			  rectangle_command_7->draw_element = true;
			  rectangle_command_8->draw_element = true;
			  rectangle_command_9->draw_element = true;

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

	minimap->Update();

	return true;
}

// Called after all Updates
bool Gui::postUpdate()
{
	//Check if we have entities selected
	if (app->entity_manager->selection.size() == 0)
		drawHudSelection(SPECIALIZATION::NOTYPE);

	multimap<float, Entity*> to_draw_selection;
	for (map<uint, Entity*>::iterator it = app->entity_manager->selection.begin(); it != app->entity_manager->selection.end(); ++it)
		to_draw_selection.insert(pair<float, Entity*>(it->second->center.y, it->second));

	// Blit of Selection Circles and Lifes
	for (multimap<float, Entity*>::iterator itm = to_draw_selection.begin(); itm != to_draw_selection.end(); ++itm)
	{
		// Circle selection blitting
		Entity *e = itm->second;
		app->render->blit(circles_of_selection, e->center.x - e->selection_type.w / 2, e->center.y - e->circle_selection_offset.y, &e->selection_type);

		// Life selection blitting
		if (e->current_hp > 0)
		{
			uint bars_to_draw = ceil((e->max_hp_bars * ((float)e->current_hp / (float)e->max_hp)) + 1);
			uint bar = 1;
			for (; bar < bars_to_draw; ++bar)
				app->render->blit(lifes_tex, e->center.x + e->offset_life.x + (bar * green_life.w), e->center.y + e->offset_life.y, &green_life);
			for (; bar <= e->max_hp_bars; ++bar)
				app->render->blit(lifes_tex, e->center.x + e->offset_life.x + (bar * white_life.w), e->center.y + e->offset_life.y, &white_life);
		}

		if (itm->second->specialization == SPECIALIZATION::COMMANDCENTER)
			drawHudSelection(COMMANDCENTER);
		if (itm->second->specialization == SPECIALIZATION::BUNKER)
			drawHudSelection(BUNKER);
	}
	
	// CRZ -> possibilty of blitting according to Y value.
	// Entity drawing
	multimap<float, Entity*> to_draw;
	for (map<uint, Entity*>::iterator it = app->entity_manager->active_entities.begin(); it != app->entity_manager->active_entities.end(); ++it)
		to_draw.insert(pair<float, Entity*>(it->second->center.y, it->second));	

	for (multimap<float, Entity*>::iterator itm = to_draw.begin(); itm != to_draw.end(); ++itm)
		itm->second->draw();

	for (list<GuiElements*>::iterator item = elements.begin(); item != elements.end(); item++)
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

	if (minimap != NULL)
		minimap->Print();

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
// Create a simple label
/*GuiLabel* Gui::createLabel(const char* text, const int x, const int y)
{
	GuiLabel* label = new GuiLabel(text, x, y);
	elements.push_back(label);

	return label;
}*/

GuiLabel* Gui::createLabel(const char* text, int kind_of_font)
{
	GuiLabel* ret = NULL;

	if (text != NULL)
	{
		ret = new GuiLabel(text,kind_of_font);
		elements.push_back(ret);
	}

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
				//elements.reverse();
                return gui_test;
			}	
		}
	}

	//elements.reverse();
	return nullptr;
}

// const getter for atlas
const SDL_Texture* Gui::getAtlas() const
{
	return atlas;
}

void Gui::openBuildingMenu() {

}




