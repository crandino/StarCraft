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
#include "GuiMinimap.h"
#include "GuiTimer.h"

#include "Bunker.h"
#include "Tank.h"

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

	last_attack_position.x = app->game_manager->command_center_position.x;
	last_attack_position.y = app->game_manager->command_center_position.y;

	//Raynor indicator Image
	raynor_indicator = app->gui->createImage("raynor_indicator.png");
	raynor_indicator->disable_element();
	raynor_indicator->static_image = true;

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
	ui_create_bunker = app->gui->createImage(NULL, { 256, 64, 37, 34 }); //Disabled section { 440, 125, 37, 34 }
	ui_create_bunker->setLocalPos(505, 358);
	ui_create_bunker->interactive = false;
	ui_create_bunker->can_focus = true;
	ui_create_bunker->setListener(this);
	ui_create_bunker->draw_element = false;

	//Create Barraks
	ui_create_barraks = app->gui->createImage(NULL, { 298, 64, 37, 34 });//Disabled section { 482, 125, 37, 34 }
	ui_create_barraks->setLocalPos(551, 358);
	ui_create_barraks->interactive = false;
	ui_create_barraks->can_focus = true;
	ui_create_barraks->setListener(this);
	ui_create_barraks->draw_element = false;

	//Create Turrets
	//ui_create_turrets = app->gui->createImage(NULL, { 338, 64, 37, 34 });//Disabled section { 522, 125, 37, 34 }
	//ui_create_turrets->setLocalPos(597, 358);
	//ui_create_turrets->interactive = false;
	//ui_create_turrets->can_focus = true;
	//ui_create_turrets->setListener(this);
	//ui_create_turrets->draw_element = false;

	//Create factory
	ui_create_factory = app->gui->createImage(NULL, { 377, 64, 37, 34 });//Disabled section { 561, 125, 37, 34 }
	ui_create_factory->setLocalPos(597, 358);
	ui_create_factory->interactive = false;
	ui_create_factory->can_focus = true;
	ui_create_factory->setListener(this);
	ui_create_factory->draw_element = false;
	
	//Create starport
	//ui_create_starport = app->gui->createImage(NULL, { 256, 101, 37, 34 });//Disabled section { 440, 162, 37, 34 }
	//ui_create_starport->setLocalPos(551, 398);
	//ui_create_starport->interactive = false;
	//ui_create_starport->can_focus = true;
	//ui_create_starport->setListener(this);
	//ui_create_starport->draw_element = false;

	//SCV Button
	ui_create_bot = app->gui->createImage(NULL, { 256, 28, 37, 34 });//Disabled section { 440, 89, 37, 34 }
	ui_create_bot->setLocalPos(505, 358);
	ui_create_bot->setListener(this);
	ui_create_bot->interactive = false;
	ui_create_bot->can_focus = true;
	ui_create_bot->draw_element = false;

	//Create tank
	ui_create_tank = app->gui->createImage(NULL, { 255, 234, 36, 33 });//Disabled section { 297, 234, 36, 33 }
	ui_create_tank->setLocalPos(505, 358);
	ui_create_tank->setListener(this);
	ui_create_tank->interactive = false;
	ui_create_tank->can_focus = true;
	ui_create_tank->draw_element = false;

	//Tank Button Normal
	ui_normal_tank = app->gui->createImage(NULL, { 255, 234, 36, 33 });
	ui_normal_tank->setLocalPos(505, 358);
	ui_normal_tank->setListener(this);
	ui_normal_tank->disable_element();
	ui_normal_tank->can_focus = true;
	
	//Tank Button Siege
	ui_siege_tank = app->gui->createImage(NULL, { 338, 234, 36, 33 });
	ui_siege_tank->setLocalPos(505, 358);
	ui_siege_tank->setListener(this);
	ui_siege_tank->can_focus = true;
	ui_siege_tank->disable_element();
	
	//Bunker buttons------------------------------------------------------------
	ui_leave_bunker = app->gui->createImage(NULL, { 255, 152, 36, 33 });//Disabled section { 254, 192, 37, 34 }
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

	//HUD Units

	//Marine button-----------------------------------------------------------
	ui_create_marine = app->gui->createImage(NULL, { 339, 152, 37, 33 });//Disabled section { 338, 192, 37, 34 }
	ui_create_marine->setLocalPos(505, 358);
	ui_create_marine->setListener(this);
	ui_create_marine->interactive = false;
	ui_create_marine->can_focus = true;
	ui_create_marine->draw_element = false;
	//Medic button------------------------------------------------------------
	ui_create_medic = app->gui->createImage(NULL, { 382, 152, 37, 33 });//Disabled section { 381, 89, 37, 34 }
	ui_create_medic->setLocalPos(551, 358);
	ui_create_medic->setListener(this);
	ui_create_medic->interactive = false;
	ui_create_medic->can_focus = true;
	ui_create_medic->draw_element = false;
	//Firebat button----------------------------------------------------------
	ui_create_firebat = app->gui->createImage(NULL, { 294, 152, 37, 33 });//Disabled section { 293, 192, 37, 34 }
	ui_create_firebat->setLocalPos(597, 358);
	ui_create_firebat->setListener(this);
	ui_create_firebat->interactive = false;
	ui_create_firebat->can_focus = true;
	ui_create_firebat->draw_element = false;

	ui_set_bomb = app->gui->createImage(NULL, { 339, 152, 37, 34 });//Disabled section { 338, 192, 37, 34 }
	ui_set_bomb->setLocalPos(597, 358);
	ui_set_bomb->setListener(this);
	ui_set_bomb->interactive = false;
	ui_set_bomb->can_focus = true;
	ui_set_bomb->draw_element = false;

	//HUD  Mineral and Gass-------------------------------------------------
	//Image
	ui_mineral = app->gui->createImage(NULL, { 7, 202, 15, 13 });
	ui_mineral->setLocalPos(490, 6);

	//Number of minerals
	number_of_minerals = app->gui->createLabel("0", 2);
	number_of_minerals->setLocalPos(508, 4);
	number_of_minerals->interactive = false;
	
	//Text Messages
	preparation_message = app->gui->createLabel("Welcome to Last Hope!", 2, TEXTMESSAGES);
	preparation_message->setLocalPos(10,240);
	preparation_message->interactive = false;
	preparation_message->getType();


	preparation_message2 = app->gui->createLabel("Destroy each wave. Keep Raynor alive (yellow marine)", 2, TEXTMESSAGES);
	preparation_message2->setLocalPos(10, 240);
	preparation_message2->interactive = false;
	preparation_message2->getType();

	second_phase_message1 = app->gui->createLabel("The bomb has landed. Find it and take it to the command center", 2, TEXTMESSAGES);
	second_phase_message1->setLocalPos(10, 240);
	second_phase_message1->interactive = false;
	second_phase_message1->getType();

	second_phase_message2 = app->gui->createLabel("A bigger zerg combat force has been detected. Be fast.", 2, TEXTMESSAGES);
	second_phase_message2->setLocalPos(10, 240);
	second_phase_message2->interactive = false;
	second_phase_message2->getType();

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

	// Create the GuiMinimap
	mini_map = createMinimap({ 6, 348, 127, 127 }, "Minimap/finalminimap.png");
	mini_map->setLocalPos(6, 348);

	//Sounds
	fx_click_1 = app->audio->loadFx("Audio/FX/UI/Click_1.wav");
	fx_click_error = app->audio->loadFx("Audio/FX/UI/Click_Error.wav");
	fx_not_enough_minerales = app->audio->loadFx("Audio/FX/InoffVoice/NotEnoughMinerals.wav");

	//Wireframes and Info-------------------------------------------------------------------
	atlas_wireframes = app->tex->loadTexture("wireframes.png");

	//Bunker Wireframe-----------------------
	bunkerWireframe = app->gui->createImage(atlas_wireframes, { 796, 222, 66, 45 });
	bunkerWireframe->setLocalPos(186, 407);
	bunkerWireframe->can_focus = false;
	bunkerWireframe->disable_element();
	//Info 
	bunkerInfo = app->gui->createLabel("a", 2);
	bunkerInfo->setLocalPos(280, 417);
	bunkerInfo->disable_element();
	bunkerInfo->can_focus = false;
	//Name
	bunkerName = app->gui->createLabel("Bunker", 2);
	bunkerName->setLocalPos(280, 391);
	bunkerName->disable_element();
	bunkerName->can_focus = false;

	//CommandCenter Wireframe-----------------------
	commandCenterWireframe = app->gui->createImage(atlas_wireframes, {4, 213, 65, 60 });
	commandCenterWireframe->setLocalPos(186, 393);
	commandCenterWireframe->can_focus = false;
	commandCenterWireframe->disable_element();
	//Info
	commandCenterInfo = app->gui->createLabel("a", 2);
	commandCenterInfo->setLocalPos(190, 455);
	commandCenterInfo->disable_element();
	commandCenterInfo->can_focus = false;
	//Name
	commandCenterName = app->gui->createLabel("Command Center", 2);
	commandCenterName->setLocalPos(265, 391);
	commandCenterName->disable_element();
	commandCenterName->can_focus = false;

	//Factory Wireframe--------------------------
	factoryWireframe = app->gui->createImage(atlas_wireframes, { 4, 312, 66, 65 });
	factoryWireframe->setLocalPos(187, 390);
	factoryWireframe->can_focus = false;
	factoryWireframe->disable_element();
	//Info
	factoryInfo = app->gui->createLabel("a", 2);
	factoryInfo->setLocalPos(190, 455);
	factoryInfo->disable_element();
	factoryInfo->can_focus = false;
	//Name
	factoryName = app->gui->createLabel("Factory", 2);
	factoryName->setLocalPos(280, 391);
	factoryName->disable_element();
	factoryName->can_focus = false;

	//Barrack Wireframe--------------------------
	barrackWireframe = app->gui->createImage(atlas_wireframes, { 443, 211, 66, 63 });
	barrackWireframe->setLocalPos(187, 390);
	barrackWireframe->can_focus = false;
	barrackWireframe->disable_element();
	//Info
	barrackInfo = app->gui->createLabel("a", 2);
	barrackInfo->setLocalPos(190, 455);
	barrackInfo->disable_element();
	barrackInfo->can_focus = false;
	//Name
	barrackName = app->gui->createLabel("Barrack", 2);
	barrackName->setLocalPos(280, 391);
	barrackName->disable_element();
	barrackName->can_focus = false;

	return true;
}

GuiTimer* Gui::createTimer(iPoint pos, const char *path_tex, Timer &timer_associated)
{
	GuiTimer* ret = nullptr;
	ret = new GuiTimer();

	ret->setLocalPos(pos.x, pos.y);
	ret->changeTimer(timer_associated);

	if (path_tex != NULL)
		SDL_Texture* texture = app->tex->loadTexture(path_tex);// cargar textura

	elements.push_back(ret);

	return ret;
}

GuiMinimap* Gui::createMinimap(SDL_Rect rect, const char *pathTex)
{
	GuiMinimap* ret = nullptr;

	ret = new GuiMinimap(rect);

	SDL_Texture* texture = app->tex->loadTexture(pathTex);// cargar textura

	if (texture)
	{
		ret->SetAttributes(&app->entity_manager->active_entities, texture);
	}
	else
	{
		ret->cleanUp();
		ret = NULL;
	}

	elements.push_back(ret);

	return ret;
}

void Gui::onGui(GuiElements* ui, GUI_EVENTS event)
{
	if (ui == ui_create_builds)
	{
		switch (event)
		{

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			if (!buildingMenuOpened)
				openBuildingMenu();
			else
			{
				buildingMenuOpened = false;
				ui_create_builds->setSection({ 298, 28, 37, 34 });
				ui_create_builds->setLocalPos(551, 358);

			}
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
			app->audio->playFx(fx_click_1, 0);
			if (app->game_manager->mineral_resources >= 50)
			{
				app->entity_manager->create_SCV = true;
				app->audio->playFx(app->entity_manager->fx_scv_ready, 0);
				info_scv->draw_element = false;
			}
			else
			{
				app->audio->playFx(fx_click_error, 0);
				app->audio->playFx(fx_not_enough_minerales, 0);
			}
			break;

			/*case(MOUSE_LCLICK_DOWN_REPEAT) :
				app->entity_manager->create_SCV = true;
				break;*/
		}
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
			app->entity_manager->create_bunker = true;
			app->audio->playFx(fx_click_1, 0);
			info_bunker->draw_element = false;
			break;

				/*case(MOUSE_LCLICK_DOWN_REPEAT) :
				app->entity_manager->create_bunker = true;
				break;*/
		}
	}

	if (ui == ui_create_barraks)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			break;

		case(MOUSE_LEAVES) :
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			app->entity_manager->create_barrack = true;
			break;

		}
	}

	if (ui == ui_create_factory)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			break;

		case(MOUSE_LEAVES) :
			break;

		case(MOUSE_LCLICK_DOWN) :
			//app->audio->playFx(fx_click_1, 0);
			app->entity_manager->create_factory = true;
			break;

		}
	}

	if (ui == ui_create_marine)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			break;

		case(MOUSE_LEAVES) :
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			if (app->game_manager->gas_resources >= 50 && app->game_manager->mineral_resources >= 75)
			{
				app->entity_manager->create_marine = true;
				app->audio->playFx(app->entity_manager->fx_marine_ready, 0);
			}
			else
			{
				app->audio->playFx(fx_click_error, 0);
				app->audio->playFx(fx_not_enough_minerales, 0);
			}
			break;

		}
	}

	if (ui == ui_create_medic)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			break;

		case(MOUSE_LEAVES) :
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			if (app->game_manager->gas_resources >= 100 && app->game_manager->mineral_resources >= 75)
			{
				app->entity_manager->create_medic = true;
				app->audio->playFx(app->entity_manager->fx_medic_ready, 0);
			}
			else
			{
				app->audio->playFx(fx_click_error, 0);
				app->audio->playFx(fx_not_enough_minerales, 0);
			}
			break;

		}
	}

	if (ui == ui_create_firebat)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			break;

		case(MOUSE_LEAVES) :
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			if (app->game_manager->gas_resources >= 200 && app->game_manager->mineral_resources >= 50)
			{
				app->entity_manager->create_firebat = true;
				app->audio->playFx(app->entity_manager->fx_firebat_ready, 0);
			}
			else
			{
				app->audio->playFx(fx_click_error, 0);
				app->audio->playFx(fx_not_enough_minerales, 0);
			}
			break;

		}
	}

	if (ui == ui_create_tank)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			break;

		case(MOUSE_LEAVES) :
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			if (app->game_manager->gas_resources >= 300 && app->game_manager->mineral_resources >= 200)
			{
				app->entity_manager->create_tank = true;
				app->audio->playFx(app->entity_manager->fx_tank_ready, 0);
			}
			else
			{
				app->audio->playFx(fx_click_error, 0);
				app->audio->playFx(fx_not_enough_minerales, 0);
			}
			break;

		}
	}

	if (ui == app->gui->ui_siege_tank)
	{
		switch (event)
		{
			case(MOUSE_LCLICK_DOWN) :
			{
				for (map<uint, Entity*>::iterator it = app->entity_manager->selection.begin(); it != app->entity_manager->selection.end(); ++it)
				{
					if (it->second->specialization == TANK)
						((Tank*)it->second)->siegeMode(true);
				}
				siegeMode = true;
			break;
			}
		}

	}

	if (ui == app->gui->ui_normal_tank)
	{
		switch (event)
		{
			case(MOUSE_LCLICK_DOWN) :
			{
				for (map<uint, Entity*>::iterator it = app->entity_manager->selection.begin(); it != app->entity_manager->selection.end(); ++it)
				{
					if (it->second->specialization == TANK)
						((Tank*)it->second)->siegeMode(false);
				}
				siegeMode = false;
			break;
			}
		}
	}

	if (ui == ui_set_bomb)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			break;

		case(MOUSE_LEAVES) :
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			app->entity_manager->set_bomb = true;
			break;

		}

	}

	if (ui == ui_leave_bunker)
	{
		switch (event)
		{
			//Method to leave the bunker
		case(MOUSE_LCLICK_DOWN) :
			for (list<Bunker*>::iterator it = bunker_to_leave.begin(); it != bunker_to_leave.end();)
			{
				if (app->entity_manager->selection.begin()->first == it._Ptr->_Myval->id)
				{
					it._Ptr->_Myval->getEntitiesOutside();
					it = bunker_to_leave.erase(it);
				}
				else
					it++;
			}
			break;
		}
	}
	
}

void Gui::drawHudSelection(SPECIALIZATION  selection)
{
	switch (selection)
	{
	case (COMMANDCENTER) :
		commandCenterOpened = true;
		barrackMenuOpened = false;
		factoryMenuOpened = false;
			  if(!buildingMenuOpened)
			  {
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

				  ui_leave_bunker->disable_element();

				  ui_leave_bunker->disable_element();
				  ui_create_bunker->disable_element();
				  ui_create_barraks->disable_element();
				  ui_create_factory->disable_element();
				
				  ui_create_marine->disable_element();
				  ui_create_medic->disable_element();
				  ui_create_firebat->disable_element();

				  ui_create_tank->disable_element();
				  ui_normal_tank->disable_element();
				  ui_siege_tank->disable_element();

				  //Activate new images
				  ui_create_bot->enable_element();
				  ui_create_builds->enable_element();

				  //Wireframes
				  bunkerWireframe->disable_element();
				  bunkerInfo->disable_element();
				  bunkerName->disable_element();

				  commandCenterWireframe->enable_element();
				  commandCenterInfo->enable_element();
				  commandCenterName->enable_element();

				  factoryWireframe->disable_element();
				  factoryInfo->disable_element();
				  factoryName->disable_element();

				  barrackWireframe->disable_element();
				  barrackInfo->disable_element();
				  barrackName->disable_element();
			  }
			  
		      break;
			  
		  case (BUNKER) :

			  if (buildingMenuOpened)
			  {
				  buildingMenuOpened = false;
				  ui_create_builds->setSection({ 298, 28, 37, 34 });
				  ui_create_builds->setLocalPos(551, 358);
			  }

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

			  ui_create_bot->disable_element();
			  ui_create_builds->disable_element();
			  ui_leave_bunker->disable_element();
			  ui_create_bunker->disable_element();
			  ui_create_barraks->disable_element();
			  ui_create_factory->disable_element();


			  ui_create_marine->disable_element();
			  ui_create_medic->disable_element();
			  ui_create_firebat->disable_element();

			  ui_create_tank->disable_element();
			  ui_normal_tank->disable_element();
			  ui_siege_tank->disable_element();

			  //Wireframe 
			  bunkerWireframe->enable_element();
			  bunkerInfo->enable_element();
			  bunkerName->enable_element();

			  commandCenterWireframe->disable_element();
			  commandCenterInfo->disable_element();
			  commandCenterName->disable_element();

			  factoryWireframe->disable_element();
			  factoryInfo->disable_element();
			  factoryName->disable_element();

			  barrackWireframe->disable_element();
			  barrackInfo->disable_element();
			  barrackName->disable_element();


			  //Activate new images
			  ui_leave_bunker->enable_element();

			  break;

		  case (BARRACK) :
			  barrackMenuOpened = true;
			  commandCenterOpened = false;
			  factoryMenuOpened = false;
			  if (buildingMenuOpened)
			  {
				  buildingMenuOpened = false;
				  ui_create_builds->setSection({ 298, 28, 37, 34 });
				  ui_create_builds->setLocalPos(551, 358);
			  }

			  //Activate default entities
			  rectangle_command->draw_element = false;
			  rectangle_command_2->draw_element = false;
			  rectangle_command_3->draw_element = false;
			  rectangle_command_4->draw_element = true;
			  rectangle_command_5->draw_element = true;
			  rectangle_command_6->draw_element = true;
			  rectangle_command_7->draw_element = true;
			  rectangle_command_8->draw_element = true;
			  rectangle_command_9->draw_element = true;

			  ui_create_bot->disable_element();
			  ui_create_builds->disable_element();
			  ui_leave_bunker->disable_element();
			  ui_create_bunker->disable_element();
			  ui_create_barraks->disable_element();
			  ui_create_factory->disable_element();


			  ui_create_marine->enable_element();
			  ui_create_medic->enable_element();
			  ui_create_firebat->enable_element();

			  ui_create_tank->disable_element();
			  ui_normal_tank->disable_element();
			  ui_siege_tank->disable_element();

			  //Wireframes
			  bunkerWireframe->disable_element();
			  bunkerInfo->disable_element();
			  bunkerName->disable_element();

			  commandCenterWireframe->disable_element();
			  commandCenterInfo->disable_element();
			  commandCenterName->disable_element();

			  factoryWireframe->disable_element();
			  factoryInfo->disable_element();
			  factoryName->disable_element();

			  barrackWireframe->enable_element();
			  barrackInfo->enable_element();
			  barrackName->enable_element();

			  break;

		  case (FACTORY) :
			  factoryMenuOpened = true;
			  barrackMenuOpened = false;
			  commandCenterOpened = false;

			  if (buildingMenuOpened)
			  {
				  buildingMenuOpened = false;
				  ui_create_builds->setSection({ 298, 28, 37, 34 });
				  ui_create_builds->setLocalPos(551, 358);
			  }

			  //Activate default entities
			  rectangle_command->draw_element = false;
			  rectangle_command_2->draw_element = true;
			  rectangle_command_3->draw_element = true;
			  rectangle_command_4->draw_element = true;
			  rectangle_command_5->draw_element = true;
			  rectangle_command_6->draw_element = true;
			  rectangle_command_7->draw_element = true;
			  rectangle_command_8->draw_element = true;
			  rectangle_command_9->draw_element = true;

			  ui_create_bot->disable_element();
			  ui_create_builds->disable_element();
			  ui_leave_bunker->disable_element();
			  ui_create_bunker->disable_element();
			  ui_create_barraks->disable_element();
			  ui_create_factory->disable_element();


			  ui_create_marine->disable_element();
			  ui_create_medic->disable_element();
			  ui_create_firebat->disable_element();

			  ui_create_tank->enable_element();
			  ui_normal_tank->disable_element();
			  ui_siege_tank->disable_element();

			  //Wireframes
			  bunkerWireframe->disable_element();
			  bunkerInfo->disable_element();
			  bunkerName->disable_element();

			  commandCenterWireframe->disable_element();
			  commandCenterInfo->disable_element();
			  commandCenterName->disable_element();

			  factoryWireframe->enable_element();
			  factoryInfo->enable_element();
			  factoryName->enable_element();

			  barrackWireframe->disable_element();
			  barrackInfo->disable_element();
			  barrackName->disable_element();

			  break;

		  case (MARINE) :
			  if (buildingMenuOpened)
			  {
		     	  buildingMenuOpened = false;
				  ui_create_builds->setSection({ 298, 28, 37, 34 });
				  ui_create_builds->setLocalPos(551, 358);
			  }

			 
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

			  ui_create_bot->disable_element();
			  ui_create_builds->disable_element();
			  ui_leave_bunker->disable_element();
			  ui_create_bunker->disable_element();
			  ui_create_barraks->disable_element();
			  ui_create_factory->disable_element();

			  ui_create_marine->disable_element();
			  ui_create_medic->disable_element();
			  ui_create_firebat->disable_element();

			  ui_create_tank->disable_element();
			  ui_normal_tank->disable_element();
			  ui_siege_tank->disable_element();

			  //Wireframes
			  bunkerWireframe->disable_element();
			  bunkerInfo->disable_element();
			  bunkerName->disable_element();

			  commandCenterWireframe->disable_element();
			  commandCenterInfo->disable_element();
			  commandCenterName->disable_element();

			  factoryWireframe->disable_element();
			  factoryInfo->disable_element();
			  factoryName->disable_element();

			  barrackWireframe->disable_element();
			  barrackInfo->disable_element();
			  barrackName->disable_element();

			  break;
			  
		  case (MEDIC) :
			  if (buildingMenuOpened)
			  {
				  buildingMenuOpened = false;
				  ui_create_builds->setSection({ 298, 28, 37, 34 });
				  ui_create_builds->setLocalPos(551, 358);
			  }


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
			  
			  ui_create_bot->disable_element();
			  ui_create_builds->disable_element();
			  ui_leave_bunker->disable_element();
			  ui_create_bunker->disable_element();
			  ui_create_barraks->disable_element();
			  ui_create_factory->disable_element();
			  
			  ui_create_marine->disable_element();
			  ui_create_medic->disable_element();
			  ui_create_firebat->disable_element();

			  ui_create_tank->disable_element();
			  ui_normal_tank->disable_element();
			  ui_siege_tank->disable_element();

			  //Wireframes
			  bunkerWireframe->disable_element();
			  bunkerInfo->disable_element();
			  bunkerName->disable_element();

			  commandCenterWireframe->disable_element();
			  commandCenterInfo->disable_element();
			  commandCenterName->disable_element();

			  factoryWireframe->disable_element();
			  factoryInfo->disable_element();
			  factoryName->disable_element();

			  barrackWireframe->disable_element();
			  barrackInfo->disable_element();
			  barrackName->disable_element();

			  break;

		  case (FIREBAT) :
			  if (buildingMenuOpened)
			  {
				  buildingMenuOpened = false;
				  ui_create_builds->setSection({ 298, 28, 37, 34 });
				  ui_create_builds->setLocalPos(551, 358);
			  }


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
			  
			  ui_create_bot->disable_element();
			  ui_create_builds->disable_element();
			  ui_leave_bunker->disable_element();
			  ui_create_bunker->disable_element();
			  ui_create_barraks->disable_element();
			  ui_create_factory->disable_element();
			  
			  ui_create_marine->disable_element();
			  ui_create_medic->disable_element();
			  ui_create_firebat->disable_element();

			  ui_create_tank->disable_element();
			  ui_normal_tank->disable_element();
			  ui_siege_tank->disable_element();

			  //Wireframes
			  bunkerWireframe->disable_element();
			  bunkerInfo->disable_element();
			  bunkerName->disable_element();

			  commandCenterWireframe->disable_element();
			  commandCenterInfo->disable_element();
			  commandCenterName->disable_element();

			  factoryWireframe->disable_element();
			  factoryInfo->disable_element();
			  factoryName->disable_element();

			  barrackWireframe->disable_element();
			  barrackInfo->disable_element();
			  barrackName->disable_element();

			  break;

		  case (TANK) :
			  if (buildingMenuOpened)
			  {
				  buildingMenuOpened = false;
				  ui_create_builds->setSection({ 298, 28, 37, 34 });
				  ui_create_builds->setLocalPos(551, 358);
			  }

			  //Activate default entities
			  rectangle_command->draw_element = false;
			  rectangle_command_2->draw_element = true;
			  rectangle_command_3->draw_element = true;
			  rectangle_command_4->draw_element = true;
			  rectangle_command_5->draw_element = true;
			  rectangle_command_6->draw_element = true;
			  rectangle_command_7->draw_element = true;
			  rectangle_command_8->draw_element = true;
			  rectangle_command_9->draw_element = true;

			  ui_create_bot->disable_element();
			  ui_create_builds->disable_element();
			  ui_leave_bunker->disable_element();
			  ui_create_bunker->disable_element();
			  ui_create_barraks->disable_element();
			  ui_create_factory->disable_element();

			  ui_create_marine->disable_element();
			  ui_create_medic->disable_element();
			  ui_create_firebat->disable_element();

			  ui_create_tank->disable_element();

			  for (map<uint, Entity*>::iterator it = app->entity_manager->selection.begin(); it != app->entity_manager->selection.end(); ++it)
			  {
				  if (it->second->specialization == TANK)
				  {
					  if (!((Tank*)it->second)->siege_mode)
					  {
						  ui_siege_tank->enable_element();
						  ui_normal_tank->disable_element();
					  }
					  else
					  {
						  ui_siege_tank->disable_element();
						  ui_normal_tank->enable_element();
					  }
				  }
			  }
			  

			  //Wireframes
			  bunkerWireframe->disable_element();
			  bunkerInfo->disable_element();
			  bunkerName->disable_element();

			  commandCenterWireframe->disable_element();
			  commandCenterInfo->disable_element();
			  commandCenterName->disable_element();

			  factoryWireframe->disable_element();
			  factoryInfo->disable_element();
			  factoryName->disable_element();

			  barrackWireframe->disable_element();
			  barrackInfo->disable_element();
			  barrackName->disable_element();

			  break;

		  case (JIM_RAYNOR) :
			  if (buildingMenuOpened)
			  {
				  buildingMenuOpened = false;
				  ui_create_builds->setSection({ 298, 28, 37, 34 });
				  ui_create_builds->setLocalPos(551, 358);
			  }


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
			  
			  ui_create_bot->disable_element();
			  ui_create_builds->disable_element();
			  ui_leave_bunker->disable_element();
			  ui_create_bunker->disable_element();
			  ui_create_barraks->disable_element();
			  ui_create_factory->disable_element();
			  
			  ui_create_marine->disable_element();
			  ui_create_medic->disable_element();
			  ui_create_firebat->disable_element();

			  ui_create_tank->disable_element();
			  ui_normal_tank->disable_element();
			  ui_siege_tank->disable_element();

			  //Wireframes
			  bunkerWireframe->disable_element();
			  bunkerInfo->disable_element();
			  bunkerName->disable_element();

			  commandCenterWireframe->disable_element();
			  commandCenterInfo->disable_element();
			  commandCenterName->disable_element();
			  
			  factoryWireframe->disable_element();
			  factoryInfo->disable_element();
			  factoryName->disable_element();

			  barrackWireframe->disable_element();
			  barrackInfo->disable_element();
			  barrackName->disable_element();

			  break;

		  case (SCV) :
			  if (buildingMenuOpened)
			  {
				  buildingMenuOpened = false;
				  ui_create_builds->setSection({ 298, 28, 37, 34 });
				  ui_create_builds->setLocalPos(551, 358);
			  }


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

				ui_create_bot->disable_element();
				ui_create_builds->disable_element();
				ui_leave_bunker->disable_element();
				ui_create_bunker->disable_element();
				ui_create_barraks->disable_element();
				ui_create_factory->disable_element();
				

				ui_create_marine->disable_element();
				ui_create_medic->disable_element();
				ui_create_firebat->disable_element();

				ui_set_bomb->disable_element();

				ui_create_tank->disable_element();
				ui_normal_tank->disable_element();
				ui_siege_tank->disable_element();

				//Wireframes
				bunkerWireframe->disable_element();
				bunkerInfo->disable_element();
				bunkerName->disable_element();

				commandCenterWireframe->disable_element();
				commandCenterInfo->disable_element();
				commandCenterName->disable_element();

				factoryWireframe->disable_element();
				factoryInfo->disable_element();
				factoryName->disable_element();

				barrackWireframe->disable_element();
				barrackInfo->disable_element();
				barrackName->disable_element();

				break;

		  case (NOTYPE) :
				  //Desactivate all the options of Entities
				  ui_create_bot->disable_element();
				  ui_create_builds->disable_element();
				  ui_leave_bunker->disable_element();
				  ui_create_bunker->disable_element();
				  ui_create_barraks->disable_element();											
				  ui_create_factory->disable_element();
				 
				  
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

				  ui_create_marine->disable_element();
				  ui_create_medic->disable_element();
				  ui_create_firebat->disable_element();

				  ui_create_tank->disable_element();
				  ui_normal_tank->disable_element();
				  ui_siege_tank->disable_element();

				  //Wireframes
				  bunkerWireframe->disable_element();
				  bunkerInfo->disable_element();
				  bunkerName->disable_element();

				  commandCenterWireframe->disable_element();
				  commandCenterInfo->disable_element();
				  commandCenterName->disable_element();

				  factoryWireframe->disable_element();
				  factoryInfo->disable_element();
				  factoryName->disable_element();

				  barrackWireframe->disable_element();
				  barrackInfo->disable_element();
				  barrackName->disable_element();

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

	if (app->input->getKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		if (lasts_attack_position.size() > 0)
			last_attack_position = lasts_attack_position.back();
		app->render->camera.x = (app->render->camera.w / 2) - last_attack_position.x;
		app->render->camera.y = (app->render->camera.h / 2) - last_attack_position.y;
		if (app->render->camera.x >= 0)
			app->render->camera.x = 0;
		else if ((app->render->camera.x - app->render->camera.w) <= -map_limits.x)
			app->render->camera.x = -map_limits.x + app->render->camera.w;
		if (app->render->camera.y >= 0)
			app->render->camera.y = 0;
		else if ((app->render->camera.y - app->render->camera.h) <= -map_limits.y)
			app->render->camera.y = -map_limits.y + app->render->camera.h;
	}

	if (timer_to_ping_attack.readSec() >= 1.0f)
	{
		timer_to_ping_attack.start();
		if (lasts_attack_position.size() > 0)
		{
			iPoint first_ping = { -1, -1 };
			iPoint second_ping = { -1, -1 };
			for (list<fPoint>::iterator it = lasts_attack_position.begin(); it != lasts_attack_position.end(); it++)
			{
				if ((it._Ptr->_Myval.x < (-app->render->camera.x) || it._Ptr->_Myval.x >((-app->render->camera.x) + app->render->camera.w)) &&
					(it._Ptr->_Myval.y < (-app->render->camera.y) || it._Ptr->_Myval.y >((-app->render->camera.y) + app->render->camera.h)))
				{
					if (first_ping.x == -1 && first_ping.y == -1)
					{
						first_ping.x = it._Ptr->_Myval.x;
						first_ping.y = it._Ptr->_Myval.y;
						mini_map->activePing(first_ping);
					}
					else if ((first_ping.x - 250 > it._Ptr->_Myval.x || first_ping.x + 250 < it._Ptr->_Myval.x) &&
						(first_ping.y - 250 > it._Ptr->_Myval.y || first_ping.y + 250 < it._Ptr->_Myval.y))
					{
						second_ping.x = it._Ptr->_Myval.x;
						second_ping.y = it._Ptr->_Myval.y;
						mini_map->activePing(second_ping);
					}
				}
			}
			last_attack_position = lasts_attack_position.back();
			lasts_attack_position.clear();
		}
	}

	// Cursor -> check for camera displacement.
	iPoint pos = cursor->getLocalPos();
	cursor->current_animation = &cursor->idle;

	if (app->entity_manager->selector_init) // Left
	{
		cursor->current_animation = &cursor->selection_anim;
	}

	Entity* entity_on_mouse = app->entity_manager->whichEntityOnMouse();
	if (entity_on_mouse != NULL && app->fog_of_war->isVisible(entity_on_mouse->center.x, entity_on_mouse->center.y))
	{
		if (entity_on_mouse->faction == PLAYER)
		{
			if (entity_on_mouse->type == UNIT)
				cursor->current_animation = &cursor->allie;
			else if (entity_on_mouse->type == BUILDING)
				cursor->current_animation = &cursor->building;
		}
		else if (entity_on_mouse->faction == COMPUTER)
			cursor->current_animation = &cursor->enemy;
	}

	// Checking displacement for X axis.
	if (pos.x < cursor_offset.x) // Left
	{
		app->render->camera.x += (app->render->camera.x + (scroll_speed * dt) <= 0 ? (scroll_speed * dt) : -app->render->camera.x);
		cursor->current_animation = &cursor->left_disp;
	}
	else if (app->input->getKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && app->input->getKey(SDL_SCANCODE_RIGHT) != KEY_REPEAT)
		app->render->camera.x += (app->render->camera.x + (scroll_speed * dt) <= 0 ? (scroll_speed * dt) : -app->render->camera.x);
	else if (pos.x >(app->render->camera.w - cursor_offset.x)) // Right
	{
		app->render->camera.x -= (app->render->camera.x - (scroll_speed * dt) >= app->render->camera.w - map_limits.x ? (scroll_speed * dt) : map_limits.x - app->render->camera.w + app->render->camera.x);
		cursor->current_animation = &cursor->right_disp;
	}
	else if (app->input->getKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && app->input->getKey(SDL_SCANCODE_LEFT) != KEY_REPEAT)
		app->render->camera.x -= (app->render->camera.x - (scroll_speed * dt) >= app->render->camera.w - map_limits.x ? (scroll_speed * dt) : map_limits.x - app->render->camera.w + app->render->camera.x);

	// Checking displacement for Y axis.
	if (pos.y < cursor_offset.y) // Up
	{
		app->render->camera.y += (app->render->camera.y + (scroll_speed * dt) <= 0 ? (scroll_speed * dt) : -app->render->camera.y);
		cursor->current_animation = &cursor->up_disp;
	}
	else if (app->input->getKey(SDL_SCANCODE_UP) == KEY_REPEAT && app->input->getKey(SDL_SCANCODE_DOWN) != KEY_REPEAT)
		app->render->camera.y += (app->render->camera.y + (scroll_speed * dt) <= 0 ? (scroll_speed * dt) : -app->render->camera.y);
	else if (pos.y >(app->render->camera.h - cursor_offset.y)) // Down
	{
		app->render->camera.y -= (app->render->camera.y - (scroll_speed * dt) >= app->render->camera.h - map_limits.y ? (scroll_speed * dt) : map_limits.y - app->render->camera.h + app->render->camera.y);
		cursor->current_animation = &cursor->down_disp;
	}
	else if (app->input->getKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && app->input->getKey(SDL_SCANCODE_UP) != KEY_REPEAT)
		app->render->camera.y -= (app->render->camera.y - (scroll_speed * dt) >= app->render->camera.h - map_limits.y ? (scroll_speed * dt) : map_limits.y - app->render->camera.h + app->render->camera.y);
	

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
		if (gui_test->getType() == CURSOR || gui_test->getType() == MINIMAP || gui_test->getType() == TIMER)
		{
			gui_test->update();
		}
	}

	//Icons Control 
	controlIconsSprite();

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
		if (itm->second->specialization == SPECIALIZATION::BARRACK)
			drawHudSelection(BARRACK);
		if (itm->second->specialization == SPECIALIZATION::FACTORY)
			drawHudSelection(FACTORY);
		if (itm->second->specialization == SPECIALIZATION::MARINE)
			drawHudSelection(MARINE);
		if (itm->second->specialization == SPECIALIZATION::MEDIC)
			drawHudSelection(MEDIC);
		if (itm->second->specialization == SPECIALIZATION::FIREBAT)
			drawHudSelection(FIREBAT);
		if (itm->second->specialization == SPECIALIZATION::SCV)
			drawHudSelection(SCV);
		if (itm->second->specialization == SPECIALIZATION::TANK)
			drawHudSelection(TANK);
		if (itm->second->specialization == SPECIALIZATION::JIM_RAYNOR)
			drawHudSelection(JIM_RAYNOR);
	}
	
	// CRZ -> A possible option of blitting according to Y value.
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
			{
				if (gui->getType() == IMAGE && gui->static_image)
					gui->draw_static();
				else
					gui->draw();
			}
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

GuiLabel* Gui::createLabel(const char* text, int kind_of_font, GUI_TYPES type)
{
	GuiLabel* ret = NULL;

	if (text != NULL)
	{
		ret = new GuiLabel(text, kind_of_font, type);
		app->game_manager->labels.push_back(ret);
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
			if (mouse.x >= r.x && mouse.x <= r.x + r.w && mouse.y >= r.y && mouse.y <= r.y + r.h)
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

void Gui::openBuildingMenu() 
{
	buildingMenuOpened = true;

	//Desactivate quad background
	rectangle_command->draw_element = false;
	rectangle_command_2->draw_element = false;
	rectangle_command_3->draw_element = false;
	rectangle_command_4->draw_element = false;
	rectangle_command_5->draw_element = true;
	rectangle_command_6->draw_element = true;
	rectangle_command_7->draw_element = true;
	rectangle_command_8->draw_element = true;
	rectangle_command_9->draw_element = true;

	ui_leave_bunker->disable_element();

	//Activate new images
	ui_create_bot->disable_element();
	ui_create_builds->setLocalPos(505, 398);
	ui_create_builds->setSection({ 338, 28, 37, 34 });
	ui_create_builds->enable_element();

	ui_create_bunker->enable_element();
	ui_create_barraks->enable_element();
	ui_create_factory->enable_element();
	
}

void Gui::controlIconsSprite()
{
	if (buildingMenuOpened)
	{
		//Bunker
		if (app->game_manager->gas_resources < 75 || app->game_manager->mineral_resources < 100)
		{
			ui_create_bunker->setSection({ 440, 125, 37, 34 });
			ui_create_bunker->unable_element();
		}
		else
		{
			ui_create_bunker->setSection({ 256, 64, 37, 34 });
			ui_create_bunker->enable_element();
		}
		//Barracks 
		if (!barrackAlive && app->game_manager->gas_resources >= 250 && app->game_manager->mineral_resources >= 250)
		{
			ui_create_barraks->setSection({ 298, 64, 37, 34 });
			ui_create_barraks->enable_element();
		}
		else
		{
			ui_create_barraks->setSection({ 482, 125, 37, 34 });
			ui_create_barraks->unable_element();
		}
		//Factory
		if (!factoryAlive && app->game_manager->gas_resources >= 300 && app->game_manager->mineral_resources >= 300)
		{
			ui_create_factory->setSection({ 377, 64, 37, 34 });
			ui_create_factory->enable_element();
		}
		else
		{
			ui_create_factory->setSection({ 561, 125, 37, 34 });
			ui_create_factory->unable_element();
		}
	}

	if (commandCenterOpened)
	{
		if (!buildingMenuOpened && !factoryMenuOpened)
		{
			if (app->game_manager->mineral_resources < 50)
			{
				ui_create_bot->setSection({ 440, 89, 37, 34 });
				ui_create_bot->unable_element();
			}
			else
			{
				ui_create_bot->setSection({ 256, 28, 37, 34 });
				ui_create_bot->enable_element();
			}
		}
	}

	if (barrackMenuOpened)
	{
		//Create Marine
		if (app->game_manager->gas_resources < 50 || app->game_manager->mineral_resources < 75)
		{
			ui_create_marine->setSection({ 338, 192, 37, 34 });
			ui_create_marine->unable_element();
		}
		else
		{
			ui_create_marine->setSection({ 338, 152, 37, 34 });
			ui_create_marine->enable_element();
		}

		//Create Medic
		if (app->game_manager->gas_resources < 100 || app->game_manager->mineral_resources < 75)
		{
			ui_create_medic->setSection({ 381, 192, 37, 34 });
			ui_create_medic->unable_element();
		}
		else
		{
			ui_create_medic->setSection({ 381, 152, 37, 34 });
			ui_create_medic->enable_element();
		}

		//Create Firebat
		if (app->game_manager->gas_resources < 200 || app->game_manager->mineral_resources < 50)
		{
			ui_create_firebat->setSection({ 293, 192, 37, 34 });
			ui_create_firebat->unable_element();
		}
		else
		{
			ui_create_firebat->setSection({ 293, 152, 37, 33 });
			ui_create_firebat->enable_element();
		}
	}

	if (factoryMenuOpened) 
	{
		if (app->game_manager->gas_resources < 300 || app->game_manager->mineral_resources < 200)
		{
			ui_create_tank->setSection({ 297, 234, 36, 33 });
			ui_create_tank->unable_element();
		}
		else
		{
			ui_create_tank->setSection({ 255, 234, 36, 33 });
			ui_create_tank->enable_element();
		}
	}
}