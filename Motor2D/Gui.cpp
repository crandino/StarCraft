#include "App.h"
#include "p2Log.h"
#include "Render.h"
#include "PathFinding.h"
#include "Input.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "Entity.h"
#include "Gui.h"
#include "Map.h"
#include "ShortcutsManager.h"
#include "Window.h"
#include "Textures.h"
#include "MenuScene.h"

#include "GuiImage.h"
#include "GuiPortrait.h"
#include "GuiCursor.h"
#include "GuiLabel.h"
#include "GuiMinimap.h"
#include "GuiTimer.h"
#include "GuiResources.h"
#include "GuiInfo.h"

#include "Bunker.h"
#include "Tank.h"

using namespace std;

Gui::Gui(bool enabled) : Module(enabled)
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
	raynor_indicator = app->gui->createImage("UI/Cursor/raynor_indicator.png");
	raynor_indicator->disable_element();
	raynor_indicator->static_image = true;

	//Portraits
	hide_portrait = app->gui->createImage(NULL, { 544, 166, 58, 50 });
	hide_portrait->setLocalPos(414, 412);
	hide_portrait->interactive = false;
	hide_portrait->can_focus = false;
	hide_portrait->disable_element();

	//Marine Portrait
	marine_portrait_tex = app->tex->loadTexture("UI/TerranConsole/portrait_marine.png");
	marine_portrait_anim.setAnimations(0, 0, 60, 56, 9, 5, 45);
	marine_portrait_anim.speed = 0.002f;
	marine_portrait_anim.loop = true;

	marine_portrait = app->gui->createPortrait(marine_portrait_tex, marine_portrait_anim);
	marine_portrait->setLocalPos(412, 410);
	marine_portrait->interactive = false;
	marine_portrait->can_focus = false;
	marine_portrait->current_animation = &marine_portrait_anim;
	marine_portrait->disable_element();

	//Medic Portrait

	medic_portrait_tex = app->tex->loadTexture("UI/TerranConsole/portrait_medic.png");
	medic_portrait_anim.setAnimations(0, 0, 60, 56, 9, 5, 45);
	medic_portrait_anim.speed = 0.002f;
	medic_portrait_anim.loop = true;

	medic_portrait = app->gui->createPortrait(medic_portrait_tex, medic_portrait_anim);
	medic_portrait->setLocalPos(412, 410);
	medic_portrait->interactive = false;
	medic_portrait->can_focus = false;
	medic_portrait->current_animation = &medic_portrait_anim;
	medic_portrait->disable_element();

	//Firebat Portrait

	firebat_portrait_tex = app->tex->loadTexture("UI/TerranConsole/portrait_firebat.png");
	firebat_portrait_anim.setAnimations(0, 0, 60, 56, 9, 5, 45);
	firebat_portrait_anim.speed = 0.002f;
	firebat_portrait_anim.loop = true;
	
	firebat_portrait = app->gui->createPortrait(firebat_portrait_tex, firebat_portrait_anim);
	firebat_portrait->setLocalPos(412, 410);
	firebat_portrait->interactive = false;
	firebat_portrait->can_focus = false;
	firebat_portrait->current_animation = &firebat_portrait_anim;
	firebat_portrait->disable_element();

	//SCV Portrait

	scv_portrait_tex = app->tex->loadTexture("UI/TerranConsole/portrait_SCV.png");
	scv_portrait_anim.setAnimations(0, 0, 60, 56, 9, 5, 45);
	scv_portrait_anim.speed = 0.002f;
	scv_portrait_anim.loop = true;
	
	scv_portrait = app->gui->createPortrait(scv_portrait_tex, scv_portrait_anim);
	scv_portrait->setLocalPos(412, 410);
	scv_portrait->interactive = false;
	scv_portrait->can_focus = false;
	scv_portrait->current_animation = &scv_portrait_anim;
	scv_portrait->disable_element();

	//Tank Portrait

	tank_portrait_tex = app->tex->loadTexture("UI/TerranConsole/portrait_tank.png");
	tank_portrait_anim.setAnimations(0, 0, 60, 56, 9, 5, 45);
	tank_portrait_anim.speed = 0.002f;
	tank_portrait_anim.loop = true;
	
	tank_portrait = app->gui->createPortrait(tank_portrait_tex, tank_portrait_anim);
	tank_portrait->setLocalPos(412, 410);
	tank_portrait->interactive = false;
	tank_portrait->can_focus = false;
	tank_portrait->current_animation = &tank_portrait_anim;
	tank_portrait->disable_element();

	
	
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

	//Create factory
	ui_create_factory = app->gui->createImage(NULL, { 377, 64, 37, 34 });//Disabled section { 561, 125, 37, 34 }
	ui_create_factory->setLocalPos(597, 358);
	ui_create_factory->interactive = false;
	ui_create_factory->can_focus = true;
	ui_create_factory->setListener(this);
	ui_create_factory->draw_element = false;

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
	number_of_wave = app->gui->createLabel("0");
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
	number_of_minerals = app->gui->createLabel("0", 1);
	number_of_minerals->setLocalPos(508, 4);
	number_of_minerals->interactive = false;
	
	//Image
	ui_gas = app->gui->createImage(NULL, { 27, 202, 15, 13 });
	ui_gas->setLocalPos(550, 6);

	//Label gass
	number_of_gass = app->gui->createLabel("0", 1);
	number_of_gass->setLocalPos(568, 4);
	number_of_gass->interactive = false;

	//HUD Info about cost production ------------------------------------
	info_bunker2 = app->gui->createResourceInfo("Bunker", app->entity_manager->bunker_mineral_cost, app->entity_manager->bunker_gas_cost, { 505, 290 });
	info_bunker2->interactive = false;
	info_bunker2->draw_element = false;

	info_barraks = app->gui->createResourceInfo("Barrak", app->entity_manager->barrack_mineral_cost, app->entity_manager->barrack_gas_cost, { 505, 290 });
	info_barraks->interactive = false;
	info_barraks->draw_element = false;

	info_factory = app->gui->createResourceInfo("Factory", app->entity_manager->factory_mineral_cost, app->entity_manager->factory_gas_cost, { 505, 290 });
	info_factory->interactive = false;
	info_factory->draw_element = false;

	info_scv2 = app->gui->createResourceInfo("SCV", app->entity_manager->scv_mineral_cost, app->entity_manager->scv_gas_cost, { 505, 290 });
	info_scv2->interactive = false;
	info_scv2->draw_element = false;

	info_marine = app->gui->createResourceInfo("Marine", app->entity_manager->marine_mineral_cost, app->entity_manager->marine_gas_cost, { 505, 290 });
	info_marine->interactive = false;
	info_marine->draw_element = false;

	info_medic = app->gui->createResourceInfo("Medic", app->entity_manager->medic_mineral_cost, app->entity_manager->medic_gas_cost, { 505, 290 });
	info_medic->interactive = false;
	info_medic->draw_element = false;

	info_firebat = app->gui->createResourceInfo("Firebat", app->entity_manager->firebat_mineral_cost, app->entity_manager->firebat_gas_cost, { 505, 290 });
	info_firebat->interactive = false;
	info_firebat->draw_element = false;

	info_tank = app->gui->createResourceInfo("Tank", app->entity_manager->tank_mineral_cost, app->entity_manager->tank_gas_cost, { 505, 290 });
	info_tank->interactive = false;
	info_tank->draw_element = false;

	//Buttons info

	info_building_menu = app->gui->createResourceInfo("Open buildings menu", { 505, 290 }, true);
	info_building_menu->disable_element();

	info_close_building_menu = app->gui->createResourceInfo("Close buildings menu", { 505, 290 }, true);
	info_close_building_menu->disable_element();

	info_tank_to_siege = app->gui->createResourceInfo("Enable siege mode", { 505, 290 }, true);
	info_tank_to_siege->disable_element();

	info_tank_to_move = app->gui->createResourceInfo("Disable siege mode", { 505, 290 }, true);
	info_tank_to_move->disable_element();
	
	// CURSOR-----------------------------------------------------------------
	SDL_ShowCursor(SDL_DISABLE);
	cursor = app->gui->createCursor(app->tex->loadTexture("UI/Cursor/StarCraftCursors.png"));
	uint w, h; app->win->getWindowSize(w, h);
	cursor_offset.x = (w * 0.01f); // 10% of map width
	cursor_offset.y = (h * 0.01f); // 10% of map height
	scroll_speed = 1.0f;

	map_limits = { app->map->data.front().width * app->map->data.front().tile_width,
		app->map->data.front().height * app->map->data.front().tile_height };

	// CIRCLES OF SELECTIOM----------------------------------------------------
	circles_of_selection = app->tex->loadTexture("UI/Selection/Selection_circles.png");
	lifes_tex = app->tex->loadTexture("UI/Cursor/StarCraftCursors.png");

	green_life = { 486, 3, 4, 5 };
	yellow_life = { 496, 3, 4, 5 };
	red_life = { 501, 3, 4, 5 };
	white_life = { 491, 3, 4, 5 };	

	// To show walkability on building mode-------------------------
	path_walkability = app->tex->loadTexture("maps/Path_tiles.png");

	// Create the GuiMinimap
	mini_map = createMinimap({ 6, 348, 128, 128 }, "UI/Minimap/finalminimap.png");
	mini_map->setLocalPos(6, 348);

	//Sounds
	fx_click_1 = app->audio->loadFx("Audio/FX/UI/Click_1.wav");
	fx_click_error = app->audio->loadFx("Audio/FX/UI/Click_Error.wav");
	fx_not_enough_minerales = app->audio->loadFx("Audio/FX/InoffVoice/NotEnoughMinerals.wav");

	//Wireframes and Info-------------------------------------------------------------------
	atlas_wireframes = app->tex->loadTexture("UI/TerranConsole/wireframes.png");

	//Bunker Wireframe-----------------------
	bunkerWireframe = app->gui->createImage(atlas_wireframes, { 796, 222, 66, 45 });
	bunkerWireframe->setLocalPos(186, 407);
	bunkerWireframe->can_focus = false;
	bunkerWireframe->disable_element();
	//Info 
	bunkerInfo = app->gui->createLabel("a", 1);
	bunkerInfo->setLocalPos(280, 417);
	bunkerInfo->disable_element();
	bunkerInfo->can_focus = false;
	//Name
	bunkerName = app->gui->createLabel("Bunker", 1);
	bunkerName->setLocalPos(280, 391);
	bunkerName->disable_element();
	bunkerName->can_focus = false;

	//CommandCenter Wireframe-----------------------
	commandCenterWireframe = app->gui->createImage(atlas_wireframes, {4, 213, 65, 60 });
	commandCenterWireframe->setLocalPos(186, 393);
	commandCenterWireframe->can_focus = false;
	commandCenterWireframe->disable_element();
	//Info
	commandCenterInfo = app->gui->createLabel("a", 1);
	commandCenterInfo->setLocalPos(190, 455);
	commandCenterInfo->disable_element();
	commandCenterInfo->can_focus = false;
	//Name
	commandCenterName = app->gui->createLabel("Command Center", 1);
	commandCenterName->setLocalPos(265, 391);
	commandCenterName->disable_element();
	commandCenterName->can_focus = false;

	//Factory Wireframe--------------------------
	factoryWireframe = app->gui->createImage(atlas_wireframes, { 4, 312, 66, 65 });
	factoryWireframe->setLocalPos(187, 390);
	factoryWireframe->can_focus = false;
	factoryWireframe->disable_element();
	//Info
	factoryInfo = app->gui->createLabel("a", 1);
	factoryInfo->setLocalPos(190, 455);
	factoryInfo->disable_element();
	factoryInfo->can_focus = false;
	//Name
	factoryName = app->gui->createLabel("Factory", 1);
	factoryName->setLocalPos(280, 391);
	factoryName->disable_element();
	factoryName->can_focus = false;

	//Barrack Wireframe--------------------------
	barrackWireframe = app->gui->createImage(atlas_wireframes, { 443, 211, 66, 63 });
	barrackWireframe->setLocalPos(187, 390);
	barrackWireframe->can_focus = false;
	barrackWireframe->disable_element();
	//Info
	barrackInfo = app->gui->createLabel("a", 1);
	barrackInfo->setLocalPos(190, 455);
	barrackInfo->disable_element();
	barrackInfo->can_focus = false;
	//Name
	barrackName = app->gui->createLabel("Barrack", 1);
	barrackName->setLocalPos(280, 391);
	barrackName->disable_element();
	barrackName->can_focus = false;

	//Small Wireframes for Selection------------------------------------------
	//Marine
	smallMarineWireframe = app->gui->createImage(atlas_wireframes, { 261, 444, 29, 31 });
	smallMarineWireframe->can_focus = false;
	smallMarineWireframe->disable_element();
	//Medic
	smallMedicWireframe = app->gui->createImage(atlas_wireframes, { 336, 444, 29, 31 });
	smallMedicWireframe->can_focus = false;
	smallMedicWireframe->disable_element();
	//Firebat
	smallFirebatWireframe = app->gui->createImage(atlas_wireframes, { 297, 444, 29, 31 });
	smallFirebatWireframe->can_focus = false;
	smallFirebatWireframe->disable_element();
	//Tank
	smallTankWireframe = app->gui->createImage(atlas_wireframes, { 376, 444, 29, 31 });
	smallTankWireframe->can_focus = false;
	smallTankWireframe->disable_element();
	//Raynor
	smallRaynorWireframe = app->gui->createImage(atlas_wireframes, { 408, 444, 29, 31 });
	smallRaynorWireframe->can_focus = false;
	smallRaynorWireframe->disable_element();
	//SCV
	smallScvWireframe = app->gui->createImage(atlas_wireframes, { 225, 444, 29, 31 });
	smallScvWireframe->can_focus = false;
	smallScvWireframe->disable_element();
	//------------------------------------------------------------------------

	// UI interface for Scene Menu
	SDL_Texture *initial_menu = app->tex->loadTexture("UI/Screens/Menu_Starcraft.png");
	
	background = app->gui->createImage(initial_menu, { 0, 0, 641, 480 });
	background->center();	

	start_button = app->gui->createImage(initial_menu, { 35, 493, 166, 43 });
	start_button->parent = background;
	start_button->setLocalPos(240, 315);
	start_button->can_focus = true;
	start_button->setListener(app->menu);

	close_button = app->gui->createImage(initial_menu, { 35, 593, 166, 43 });
	close_button->parent = background;
	close_button->setLocalPos(240, 415);
	close_button->can_focus = true;
	close_button->setListener(app->menu);

	controls_button = app->gui->createImage(initial_menu, { 35, 543, 166, 43 });
	controls_button->parent = background;
	controls_button->setLocalPos(240, 365);
	controls_button->can_focus = true;
	controls_button->setListener(app->menu);

	controls_panel = app->gui->createImage(initial_menu, { 753, 68, 344, 262 });
	controls_panel->center();
	controls_panel->setLocalPos(controls_panel->getLocalPos().x, controls_panel->getLocalPos().y - 65);

	ok_controls_button = app->gui->createImage(initial_menu, { 665, 369, 143, 41 });
	ok_controls_button->parent = controls_panel;
	ok_controls_button->center();
	ok_controls_button->setLocalPos(ok_controls_button->getLocalPos().x, ok_controls_button->getLocalPos().y + 130);
	ok_controls_button->can_focus = true;
	ok_controls_button->setListener(app->menu);

	return true;
}

GuiInfo* Gui::createInfo(iPoint pos, const char *tex_path)
{
	GuiInfo* ret = nullptr;
	ret = new GuiInfo(pos, tex_path);

	elements.push_back(ret);

	return ret;
}

GuiTimer* Gui::createTimer(iPoint pos, const char *path_tex, Timer &timer_associated)
{
	GuiTimer* ret = nullptr;
	ret = new GuiTimer(pos, path_tex);

	ret->changeTimer(timer_associated);

	elements.push_back(ret);

	return ret;
}

GuiResources* Gui::createResourceInfo(const char* _entity_name, int _mineral, int _gas, iPoint pos, bool draw_element)
{
	GuiResources* ret = nullptr;

	char mineral[5];
	char gas[5];

	sprintf_s(mineral, 5, "%d", _mineral);
	sprintf_s(gas, 5, "%d", _gas);

	ret = new GuiResources(_entity_name, mineral, gas, pos, draw_element);

	elements.push_back(ret);

	return ret;
}

GuiResources* Gui::createResourceInfo(const char* _entity_name, iPoint pos, bool only_info, bool draw_element)
{
	GuiResources* ret = nullptr;

	ret = new GuiResources(_entity_name, pos, only_info, draw_element);

	elements.push_back(ret);

	return ret;
}

GuiPortrait* Gui::createPortrait(const SDL_Texture* texture, Animation animation)
{
	GuiPortrait* ret = nullptr;
	ret = new GuiPortrait(texture, animation);

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

		case(MOUSE_ENTERS) :
			if (ui_create_builds->getLocalPos().x == 505 && ui_create_builds->getLocalPos().y == 398)
				info_close_building_menu->draw_element = true;
			else 
				info_building_menu->draw_element = true;
			break;

		case(MOUSE_LEAVES) :
			info_building_menu->draw_element = false;
			info_close_building_menu->draw_element = false;
			break;

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
			//info_scv->draw_element = true;
			info_scv2->draw_element = true;
			break;

		case(MOUSE_LEAVES) :
			//info_scv->draw_element = false;
			info_scv2->draw_element = false;
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			if (app->game_manager->mineral_resources >= app->entity_manager->scv_mineral_cost)
			{
				app->entity_manager->create_SCV = true;
				app->audio->playFx(app->entity_manager->fx_scv_ready, 0);
				info_scv2->draw_element = false;
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
			info_bunker2->draw_element = true;
			break;

		case(MOUSE_LEAVES) :
			info_bunker2->draw_element = false;
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->entity_manager->create_bunker = true;
			app->audio->playFx(fx_click_1, 0);
			info_bunker2->draw_element = false;
			break;
		}
	}

	if (ui == ui_create_barraks)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			info_barraks->draw_element = true;
			break;

		case(MOUSE_LEAVES) :
			info_barraks->draw_element = false;
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			app->entity_manager->create_barrack = true;
			info_barraks->draw_element = false;
			break;

		}
	}

	if (ui == ui_create_factory)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			info_factory->draw_element = true;
			break;

		case(MOUSE_LEAVES) :
			info_factory->draw_element = false;
			break;

		case(MOUSE_LCLICK_DOWN) :
			//app->audio->playFx(fx_click_1, 0);
			app->entity_manager->create_factory = true;
			info_factory->draw_element = false;
			break;

		}
	}

	if (ui == ui_create_marine)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			info_marine->draw_element = true;
			break;

		case(MOUSE_LEAVES) :
			info_marine->draw_element = false;
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			if (app->game_manager->gas_resources >= app->entity_manager->marine_gas_cost && app->game_manager->mineral_resources >= app->entity_manager->marine_mineral_cost)
			{
				app->entity_manager->create_marine = true;
				app->audio->playFx(app->entity_manager->fx_marine_ready, 0);
				info_marine->draw_element = false;
			}
			else
			{
				app->audio->playFx(fx_click_error, 0);
				app->audio->playFx(fx_not_enough_minerales, 0);
				info_marine->draw_element = false;
			}
			break;
		}
	}

	if (ui == ui_create_medic)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			info_medic->draw_element = true;
			break;

		case(MOUSE_LEAVES) :
			info_medic->draw_element = false;
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			if (app->game_manager->gas_resources >= app->entity_manager->medic_gas_cost && app->game_manager->mineral_resources >= app->entity_manager->medic_mineral_cost)
			{
				app->entity_manager->create_medic = true;
				app->audio->playFx(app->entity_manager->fx_medic_ready, 0);
				info_medic->draw_element = false;
			}
			else
			{
				app->audio->playFx(fx_click_error, 0);
				app->audio->playFx(fx_not_enough_minerales, 0);
				info_medic->draw_element = false;
			}
			break;

		}
	}

	if (ui == ui_create_firebat)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			info_firebat->draw_element = true;
			break;

		case(MOUSE_LEAVES) :
			info_firebat->draw_element = false;
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			if (app->game_manager->gas_resources >= app->entity_manager->firebat_gas_cost && app->game_manager->mineral_resources >= app->entity_manager->firebat_mineral_cost)
			{
				app->entity_manager->create_firebat = true;
				app->audio->playFx(app->entity_manager->fx_firebat_ready, 0);
				info_firebat->draw_element = false;
			}
			else
			{
				app->audio->playFx(fx_click_error, 0);
				app->audio->playFx(fx_not_enough_minerales, 0);
				info_firebat->draw_element = false;
			}
			break;
		}
	}

	if (ui == ui_create_tank)
	{
		switch (event)
		{

		case(MOUSE_ENTERS) :
			info_tank->draw_element = true;
			break;

		case(MOUSE_LEAVES) :
			info_tank->draw_element = false;
			break;

		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click_1, 0);
			if (app->game_manager->gas_resources >= app->entity_manager->tank_gas_cost && app->game_manager->mineral_resources >= app->entity_manager->tank_mineral_cost)
			{
				app->entity_manager->create_tank = true;
				app->audio->playFx(app->entity_manager->fx_tank_ready, 0);
				info_tank->draw_element = false;
			}
			else
			{
				app->audio->playFx(fx_click_error, 0);
				app->audio->playFx(fx_not_enough_minerales, 0);
				info_tank->draw_element = false;
			}
			break;

		}
	}

	if (ui == app->gui->ui_siege_tank)
	{
		switch (event)
		{
			case(MOUSE_ENTERS) :
				info_tank_to_siege->draw_element = true;
				break;

			case(MOUSE_LEAVES) :
				info_tank_to_siege->draw_element = false;
				break;

			case(MOUSE_LCLICK_DOWN) :
			{
				for (map<uint, Entity*>::iterator it = app->entity_manager->selection.begin(); it != app->entity_manager->selection.end(); ++it)
				{
					if (it->second->specialization == TANK)
					{
						((Tank*)it->second)->siegeMode(true);
						info_tank_to_siege->draw_element = false;
					}
						
				}
				break;
			}
		}

	}

	if (ui == app->gui->ui_normal_tank)
	{
		switch (event)
		{
			case(MOUSE_ENTERS) :
				info_tank_to_move->draw_element = true;
				break;

			case(MOUSE_LEAVES) :
				info_tank_to_move->draw_element = false;
				break;
			case(MOUSE_LCLICK_DOWN) :
			{
				for (map<uint, Entity*>::iterator it = app->entity_manager->selection.begin(); it != app->entity_manager->selection.end(); ++it)
				{
					if (it->second->specialization == TANK)
					{
						((Tank*)it->second)->siegeMode(false);
						info_tank_to_move->draw_element = false;
					}
						
				}
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

				  //Portraits

				  hide_portrait->enable_element();
				  marine_portrait->disable_element();
				  medic_portrait->disable_element();
				  firebat_portrait->disable_element();
				  scv_portrait->disable_element();
				  tank_portrait->disable_element();
			  }
			  
			  enableWireframesSelection(false);

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

			  enableWireframesSelection(false);

			  //Activate new images
			  ui_leave_bunker->enable_element();

			  //Portraits
			  hide_portrait->enable_element();
			  marine_portrait->disable_element();
			  medic_portrait->disable_element();
			  firebat_portrait->disable_element();
			  scv_portrait->disable_element();
			  tank_portrait->disable_element();


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

			  enableWireframesSelection(false);

			  //Portraits
			  hide_portrait->enable_element();
			  marine_portrait->disable_element();
			  medic_portrait->disable_element();
			  firebat_portrait->disable_element();
			  scv_portrait->disable_element();
			  tank_portrait->disable_element();

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

			  enableWireframesSelection(false);

			  //Portraits
			  hide_portrait->enable_element();
			  marine_portrait->disable_element();
			  medic_portrait->disable_element();
			  firebat_portrait->disable_element();
			  scv_portrait->disable_element();
			  tank_portrait->disable_element();

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

			  enableWireframesSelection(true);

			  //Portraits
			  hide_portrait->disable_element();
			  marine_portrait->enable_element();
			  medic_portrait->disable_element();
			  firebat_portrait->disable_element();
			  scv_portrait->disable_element();
			  tank_portrait->disable_element();

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

			  enableWireframesSelection(true);

			  //Portraits
			  hide_portrait->disable_element();
			  marine_portrait->disable_element();
			  medic_portrait->enable_element();
			  firebat_portrait->disable_element();
			  scv_portrait->disable_element();
			  tank_portrait->disable_element();

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

			  enableWireframesSelection(true);

			  //Portraits
			  hide_portrait->disable_element();
			  marine_portrait->disable_element();
			  medic_portrait->disable_element();
			  firebat_portrait->enable_element();
			  scv_portrait->disable_element();
			  tank_portrait->disable_element();

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

			  enableWireframesSelection(true);

			  //Portraits
			  hide_portrait->disable_element();
			  marine_portrait->disable_element();
			  medic_portrait->disable_element();
			  firebat_portrait->disable_element();
			  scv_portrait->disable_element();
			  tank_portrait->enable_element();

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

			  enableWireframesSelection(true);

			  //Portraits
			  hide_portrait->disable_element();
			  marine_portrait->enable_element();
			  medic_portrait->disable_element();
			  firebat_portrait->disable_element();
			  scv_portrait->disable_element();
			  tank_portrait->disable_element();

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

				enableWireframesSelection(true);

				//Portraits
				hide_portrait->disable_element();
				marine_portrait->disable_element();
				medic_portrait->disable_element();
				firebat_portrait->disable_element();
				scv_portrait->enable_element();
				tank_portrait->disable_element();

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

				  //Portraits
				  hide_portrait->enable_element();
				  marine_portrait->disable_element();
				  medic_portrait->disable_element();
				  firebat_portrait->disable_element();
				  scv_portrait->disable_element();
				  tank_portrait->disable_element();

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

	if (app->game_manager->isGameStarted())
	{
		if (app->shortcuts->isCommandActive(LOCATE_LAST_ATTACK_POSITION))
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
		//gui_test->update(mouse_hover, focus);
		if (gui_test->getType() != IMAGE || gui_test->getType() != LABEL )
		{
			gui_test->update();
		}
	}

	//Icons Control 
	controlIconsSprite();

	//wireframes selection
	showWireframesSelection();

	//Clean Hud when buildings are destroyed
	if (!barrackAlive)
	{
		info_marine->draw_element = false;
		info_medic->draw_element = false;
		info_firebat->draw_element = false;
	}

	if (!factoryAlive)
	{
		info_tank->draw_element = false;
	}
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

	for (list<Particle*>::reverse_iterator it2 = app->particle->particleList.rbegin(); it2 != app->particle->particleList.rend();++it2)
	{
		(*it2)->draw();
	}

	for (list<GuiElements*>::iterator item = elements.begin(); item != elements.end(); item++)
	{
		GuiElements* gui = *item;
		if (gui->draw_element == true)
		{
			if (gui->getType() != CURSOR)
			{
				if (gui->getType() == IMAGE && gui->static_image)
					gui->draw_static();
				else if (gui->getType() == MINIMAP)
				{
					if (debug)
					{
						mini_map->debug = debug;
					}
					gui->draw();
					mini_map->debug = false;
				}
				else
					gui->draw();
			}

		}

		if (debug == true && gui->draw_element == true)
			gui->debugDraw();
	}

	for (list<GuiImage>::iterator item = selection_wireframes.begin(); item != selection_wireframes.end(); item++)
	{
		GuiImage gui = *item;
		if (gui.draw_element == true)
		{
			gui.draw();
		}
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
	selection_wireframes.clear();

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

// Create a simple image
GuiImage Gui::createImage(GuiImage* image, iPoint position)
{
	GuiImage ret = NULL;
	ret = GuiImage(image, position);

	return ret;
}
// Create a simple label
/*GuiLabel* Gui::createLabel(const char* text, const int x, const int y)
{
	GuiLabel* label = new GuiLabel(text, x, y);
	elements.push_back(label);

	return label;
}*/

GuiLabel* Gui::createLabel(const char* text, int kind_of_font) //1 for default Starcrfat font
{                                                              //2 for resources font
	GuiLabel* ret = NULL;                                      //3 for default sans font
	                                                           //change the size of those fonts at the config.xml
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
		if (app->game_manager->mineral_resources < app->entity_manager->bunker_mineral_cost || app->game_manager->gas_resources < app->entity_manager->bunker_gas_cost)
		{
			ui_create_bunker->setSection({ 440, 125, 37, 34 });
			ui_create_bunker->draw_element;
		}
		else
		{
			ui_create_bunker->setSection({ 256, 64, 37, 34 });
			ui_create_bunker->enable_element();
		}
		//Barracks 
		if (!barrackAlive && app->game_manager->mineral_resources >= app->entity_manager->barrack_mineral_cost && app->game_manager->gas_resources >= app->entity_manager->barrack_gas_cost)
		{
			ui_create_barraks->setSection({ 298, 64, 37, 34 });
			ui_create_barraks->enable_element();
		}
		else
		{
			ui_create_barraks->setSection({ 482, 125, 37, 34 });
			ui_create_barraks->draw_element;
		}
		//Factory
		if (!factoryAlive && app->game_manager->mineral_resources >= app->entity_manager->factory_mineral_cost && app->game_manager->gas_resources >= app->entity_manager->factory_gas_cost)
		{
			ui_create_factory->setSection({ 377, 64, 37, 34 });
			ui_create_factory->enable_element();
		}
		else
		{
			ui_create_factory->setSection({ 561, 125, 37, 34 });
			ui_create_factory->draw_element;
		}
	}

	if (commandCenterOpened)
	{
		if (!buildingMenuOpened && !factoryMenuOpened)
		{
			if (app->game_manager->mineral_resources < app->entity_manager->scv_mineral_cost)
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
		if (app->game_manager->gas_resources < app->entity_manager->marine_gas_cost || app->game_manager->mineral_resources < app->entity_manager->marine_mineral_cost)
		{
			ui_create_marine->setSection({ 338, 192, 37, 34 });
			ui_create_marine->draw_element;
		}
		else
		{
			ui_create_marine->setSection({ 338, 152, 37, 34 });
			ui_create_marine->enable_element();
		}

		//Create Medic
		if (app->game_manager->gas_resources < app->entity_manager->medic_gas_cost || app->game_manager->mineral_resources < app->entity_manager->medic_mineral_cost)
		{
			ui_create_medic->setSection({ 381, 192, 37, 34 });
			ui_create_medic->draw_element;
		}
		else
		{
			ui_create_medic->setSection({ 381, 152, 37, 34 });
			ui_create_medic->enable_element();
		}

		//Create Firebat
		if (app->game_manager->gas_resources < app->entity_manager->firebat_gas_cost || app->game_manager->mineral_resources < app->entity_manager->firebat_mineral_cost)
		{
			ui_create_firebat->setSection({ 293, 192, 37, 34 });
			ui_create_firebat->draw_element;
		}
		else
		{
			ui_create_firebat->setSection({ 293, 152, 37, 33 });
			ui_create_firebat->enable_element();
		}
	}

	if (factoryMenuOpened) 
	{
		if (app->game_manager->gas_resources < app->entity_manager->tank_gas_cost || app->game_manager->mineral_resources < app->entity_manager->tank_mineral_cost)
		{
			ui_create_tank->setSection({ 297, 234, 36, 33 });
			ui_create_tank->draw_element;
		}
		else
		{
			ui_create_tank->setSection({ 255, 234, 36, 33 });
			ui_create_tank->enable_element();
		}
	}
}

bool Gui::findBunkerToLeave(Bunker* bunker)
{
	bool ret = false;
	for (list<Bunker*>::iterator it = bunker_to_leave.begin(); it != bunker_to_leave.end(); it++)
	{
		if (bunker == it._Ptr->_Myval)
			ret = true;
	}
	return ret;
}

void Gui::disableHUDelements()
{
	barrackAlive = false;
	factoryAlive = false;
	buildingMenuOpened = false;
	commandCenterOpened = false;
	barrackMenuOpened = false;
	factoryMenuOpened = false;

	info_bunker2->draw_element = false;
	info_barraks->draw_element = false;
	info_factory->draw_element = false;
	info_scv2->draw_element = false;
	info_marine->draw_element = false;
	info_firebat->draw_element = false;
	info_medic->draw_element = false;
	info_tank->draw_element = false;

	rectangle_command->draw_element = true;
	rectangle_command_2->draw_element = true;
	rectangle_command_3->draw_element = true;
	rectangle_command_4->draw_element = true;
	rectangle_command_5->draw_element = true;
	rectangle_command_6->draw_element = true;
	rectangle_command_7->draw_element = true;
	rectangle_command_8->draw_element = true;
	rectangle_command_9->draw_element = true;

	ui_leave_bunker->disable_element();
	raynor_indicator->disable_element();

	ui_create_bot->disable_element();
	ui_create_builds->disable_element();
	ui_create_builds->setSection({ 298, 28, 37, 34 });  // Very wierd but necessary because the element also use the cancel symbol... :(
	ui_create_builds->setLocalPos(551, 358);			// UI element very versatile!!
	ui_create_bunker->disable_element();
	ui_create_barraks->disable_element();
	ui_create_factory->disable_element();
	ui_create_marine->disable_element();
	ui_create_firebat->disable_element();
	ui_create_medic->disable_element();
	ui_create_tank->disable_element();
	ui_normal_tank->disable_element();
	ui_siege_tank->disable_element();
}

bool Gui::load(pugi::xml_node &node)
{
	bunker_to_leave.clear();
	barrackAlive = node.child("gui_status").attribute("barrackAlive").as_bool();
	factoryAlive = node.child("gui_status").attribute("factoryAlive").as_bool();
	buildingMenuOpened = node.child("gui_status").attribute("buildingMenuOpened").as_bool();
	commandCenterOpened = node.child("gui_status").attribute("commandCenterOpened").as_bool();
	barrackMenuOpened = node.child("gui_status").attribute("barrackMenuOpeneed").as_bool();
	factoryMenuOpened = node.child("gui_status").attribute("factoryMenuOpened").as_bool();

	return true;
}

bool Gui::save(pugi::xml_node &node) const
{
	pugi::xml_node gui_status = node.append_child("gui_status");
	gui_status.append_attribute("buildingMenuOpened") = buildingMenuOpened;
	gui_status.append_attribute("commandCenterOpened") = commandCenterOpened;
	gui_status.append_attribute("barrackMenuOpened") = barrackMenuOpened;
	gui_status.append_attribute("factoryMenuOpened") = factoryMenuOpened;
	gui_status.append_attribute("barrackAlive") = barrackAlive;
	gui_status.append_attribute("factoryAlive") = factoryAlive;

	return true;
}


void Gui::showWireframesSelection()
{
	enableWireframesSelection(false);
	if (!app->entity_manager->selection.empty())
	{
		map<uint, Entity*>::iterator it = app->entity_manager->selection.begin();

		if (it->second->type != BUILDING)
		{
			if (app->entity_manager->selection.size() > 12)
			{
				//Draw a single wireframe with a side number that shows type of unit u have
				for (; it != app->entity_manager->selection.end(); ++it)
				{

				}
			}
			else if (app->entity_manager->selection.size() <= 12)
			{
				//Draw 14 wireframes for every type of unit
				for (uint i = 1; it != app->entity_manager->selection.end(); ++it, ++i)
				{
					switch (it->second->specialization)
					{
					case MARINE:
						wireframeType(MARINE, i);
						break;
					case MEDIC:
						wireframeType(MEDIC, i);
						break;
					case FIREBAT:
						wireframeType(FIREBAT, i);
						break;
					case TANK:
						wireframeType(TANK, i);
						break;
					case JIM_RAYNOR:
						wireframeType(JIM_RAYNOR, i);
						break;
					case SCV:
						wireframeType(SCV, i);
						break;
					}
				}
			}
		}
	}
}

void Gui::wireframeType(SPECIALIZATION type, uint position)
{
	iPoint coords;
	coords.setZero();

	switch (position)
	{
	case 1:
		coords.set(161, 397);
		break;
	case 2:
		coords.set(200, 397);
		break;
	case 3:
		coords.set(239, 397);
		break;
	case 4:
		coords.set(278, 397);
		break;
	case 5:
		coords.set(317, 397);
		break;
	case 6:
		coords.set(356, 397);
		break;
	case 7:
		coords.set(161, 436);
		break;
	case 8:
		coords.set(200, 436);
		break;
	case 9:
		coords.set(239, 436);
		break;
	case 10:
		coords.set(278, 436);
		break;
	case 11:
		coords.set(317, 436);
		break;
	case 12:
		coords.set(356, 436);
		break;
	}

	GuiImage wire = nullptr;

	switch (type)
	{
	case MARINE:
		wire = createImage(smallMarineWireframe, coords);
		break;
	case MEDIC:
		wire = createImage(smallMedicWireframe, coords);
		break;
	case FIREBAT:
		wire = createImage(smallFirebatWireframe, coords);
		break;
	case TANK:
		wire = createImage(smallTankWireframe, coords);
		break;
	case JIM_RAYNOR:
		wire = createImage(smallRaynorWireframe, coords);
		break;
	case SCV:
		wire = createImage(smallScvWireframe, coords);
		break;
	}

	wire.disable_element();
	selection_wireframes.push_back(wire);
}

void Gui::enableWireframesSelection(bool active)
{
	if (active)
	{
		if (!selection_wireframes.empty())
		{
			for (list<GuiImage>::iterator it = selection_wireframes.begin(); it != selection_wireframes.end(); ++it)
			{
				it._Ptr->_Myval.enable_element();
			}
		}
	}
	else if (!active)
	{
		if (!selection_wireframes.empty())
		{
			for (list<GuiImage>::iterator it = selection_wireframes.begin(); it != selection_wireframes.end(); ++it)
			{
				it._Ptr->_Myval.disable_element();
			}
		selection_wireframes.clear();
		}
	}
}
