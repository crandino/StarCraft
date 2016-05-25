#include "App.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "Input.h"
#include "p2Log.h"
#include <time.h>
#include "SDL\include\SDL_mouse.h"
#include "Render.h"
#include "Gui.h"
#include "Textures.h"
#include "Window.h"
#include "Audio.h"
#include "map.h"
#include <map>
#include "Entity.h"
#include "Scene.h"
#include "MenuScene.h"
#include "Bomb.h"
#include "Unit.h"
#include "GuiMinimap.h"
#include "PathFinding.h"
#include "FadeToBlack.h"

#include "GuiImage.h"
#include "GuiInfo.h"
#include "GuiTimer.h"
#include "GuiCursor.h"

#include <sstream>
using namespace std;

//Author: RIE code.

/*
//Number to change the number of waves
#define TOTALWAVES 2
#define WAVETIME1 5//120 = 2 minutes per wave in the future or some other game designish number // 5 was the original value! CRZ
#define WAVETIME2 10
#define	SIZE1 5 // Changes number of zerglings per wave //IPL: CHANGED FOR RELEASE 0.4
#define TOTALUNITSALLWAVES SIZE1*TOTALWAVES
#define ZERGLINGSCORE 20
#define COMMANDCENTERPOSITION {1500, 2250}
*/

/*To Put into xml*/
struct wave_position
{
	// /O . O\  
	iPoint north_west = { 877, 716 };
	iPoint north_east = { 3557, 905 };
	iPoint south_west = { 911, 3021 };
	iPoint south_east = { 2606, 3056 };
};

enum wave_positions_enum
{
	NORTHWEST,
	NORTHEAST,
	SOUTHWEST,
	SOUTHEAST
} wave_pos_enum;

enum bomb_position_enum
{
	BOMBPOS1,
	BOMBPOS2,
	BOMBPOS3,
	BOMBPOS4
};

// ---- GAME MANAGER -----

GameManager::GameManager(bool enabled) : Module(enabled)
{
	name.assign("game_manager");
}

bool GameManager::awake(pugi::xml_node &node) 
{
	bool ret = true;

	/*Game Info load*/
	gameInfo.total_waves = node.child("totalWaves").attribute("value").as_uint();
	gameInfo.time_before_game_starts = node.child("timeBeforeGameStarts").attribute("value").as_uint();
	gameInfo.time_before_start = node.child("timeBeforeStart").attribute("value").as_uint();
	gameInfo.time_before_waves_phase1 = node.child("timeBetweenWavesPhase1").attribute("value").as_uint();
	gameInfo.time_before_waves_phase2 = node.child("timeBetweenWavesPhase2").attribute("value").as_uint();
	gameInfo.time_before_waves_phase3 = node.child("timeBetweenWavesPhase3").attribute("value").as_uint();
	gameInfo.time_before_end = node.child("timeBeforeEnd").attribute("value").as_uint();
	gameInfo.time_while_bomb_landing = node.child("timeBeforeWhileBombLanding").attribute("value").as_uint();
	gameInfo.time_bomb_detonation = node.child("timeBomb").attribute("value").as_uint();

	/*Player Info Load*/
	initial_size.marines_quantityX = node.child("InitialSizePlayer").attribute("marinesX").as_int();
	initial_size.marines_quantityY = node.child("InitialSizePlayer").attribute("marinesY").as_int();
	initial_size.scv_quantity = node.child("InitialSizePlayer").attribute("scv").as_int();
	//initialSize.marines_quantity = node.child("InitialSizePlayer").attribute("medic").as_uint();
	command_center_position.x = node.child("CommandCenterPosition").attribute("coordx").as_int();
	command_center_position.y = node.child("CommandCenterPosition").attribute("coordy").as_int();
	factory_position.x = command_center_position.x + 175;
	factory_position.y = command_center_position.y + 20;
	barrack_position.x = command_center_position.x - 175;
	barrack_position.y = command_center_position.y + 20;

	/*Score data Load*/
	zergling_score = node.child("ZerglingScore").attribute("value").as_uint();
	hydralisk_score = node.child("HydraliskScore").attribute("value").as_uint();
	mutalisk_score = node.child("MutaliskScore").attribute("value").as_uint();
	ultralisk_score = node.child("UltraliskScore").attribute("value").as_uint();


	/*Wave Info Load*/
	for (pugi::xml_node tempNode = node.child("SizeWave"); tempNode; tempNode = tempNode.next_sibling("SizeWave"))
	{
			 num_zergling = tempNode.attribute("zerglings").as_uint();
			 num_hydralisk = tempNode.attribute("hydralisks").as_uint();
			 num_mutalisk = tempNode.attribute("mutalisks").as_uint();
			 num_ultralisk = tempNode.attribute("ultralisks").as_uint();

			SizeWave* wave = new SizeWave(num_zergling, num_hydralisk, num_mutalisk, num_ultralisk);
			waves_info.push_back(wave);
	}

	/*Wave2 Info Load*/
	for (pugi::xml_node tempNode = node.child("SizeWave2"); tempNode; tempNode = tempNode.next_sibling("SizeWave2"))
	{
		original_zergling_num = tempNode.attribute("zerglings").as_uint();
		original_hydra_num = tempNode.attribute("hydralisks").as_uint();
		original_muta_num = tempNode.attribute("mutalisks").as_uint();
		original_ultra_num = tempNode.attribute("ultralisks").as_uint();

		SizeWave* wave = new SizeWave(original_zergling_num, original_hydra_num, original_muta_num, original_ultra_num);
		waves2_info.push_back(wave);
	}

	/*Wave3 Info Load*/
	for (pugi::xml_node tempNode = node.child("SizeWave3"); tempNode; tempNode = tempNode.next_sibling("SizeWave3"))
	{
		original_zergling_num = tempNode.attribute("zerglings").as_uint();
		original_hydra_num = tempNode.attribute("hydralisks").as_uint();
		original_muta_num = tempNode.attribute("mutalisks").as_uint();
		original_ultra_num = tempNode.attribute("ultralisks").as_uint();

		SizeWave* wave = new SizeWave(original_zergling_num, original_hydra_num, original_muta_num, original_ultra_num);
		waves3_info.push_back(wave);
	}

	game_state = HOLD;
	if (node.child("hold").attribute("value").as_bool())
		start_game = true;		

	multiplier_hydra = node.child("multiplierHydra").attribute("value").as_int();
	multiplier_muta = node.child("multiplierMuta").attribute("value").as_int();
	multiplier_ultra = node.child("multiplierUltra").attribute("value").as_int();

	power_hydra = node.child("powerHydra").attribute("value").as_int();
	power_muta = node.child("powerrMuta").attribute("value").as_int();
	power_ultra = node.child("powerUltra").attribute("value").as_int();

	return ret;
}

bool GameManager::start()
{
	bool ret = true;

	LOG("LAST HOPE GAME STARTS!");

	fx_win = app->audio->loadFx("Audio/FX/UI/YouWin.wav");
	fx_lose = app->audio->loadFx("Audio/FX/UI/YouLose.wav");
	fx_click = app->audio->loadFx("Audio/FX/UI/Click_2.wav");
	fx_wave_incoming = app->audio->loadFx("Audio/FX/InoffVoice/Wave_incoming.wav");

	//Backgorund audio (DEBUG include)
	app->audio->playMusic("Audio/Music/Background_Music.mp3", 0.f);

	SDL_Texture *win_image = app->tex->loadTexture("UI/Screens/Win_Starcraft.png");
	is_victory_screen_on = false;
	victory_screen = app->gui->createImage(win_image, { 0, 0, 296, 225 });
	victory_screen->center();
	victory_screen->setLocalPos(victory_screen->getLocalPos().x, victory_screen->getLocalPos().y - 70);
	victory_screen->draw_element = false;	

	ok_win_button = app->gui->createImage(win_image, { 37, 242, 62, 19 });
	ok_win_button->parent = victory_screen;
	ok_win_button->setLocalPos(119, 214);
	ok_win_button->draw_element = false;
	ok_win_button->interactive = false;
	ok_win_button->can_focus = false;
	ok_win_button->setListener(this);

	SDL_Texture *jim_screen = app->tex->loadTexture("UI/Screens/Lose_JimRaynor_Starcraft.png");
	SDL_Texture *command_screen = app->tex->loadTexture("UI/Screens/Lose_CommandCenter_Starcraft.png");
	is_defeat_screen_on = false;

	defeat_by_jim_screen = app->gui->createImage(jim_screen, { 0, 0, 296, 225 });
	defeat_by_jim_screen->center();
	defeat_by_jim_screen->setLocalPos(defeat_by_jim_screen->getLocalPos().x, defeat_by_jim_screen->getLocalPos().y - 70);
	defeat_by_jim_screen->draw_element = false;

	defeat_by_command_screen = app->gui->createImage(command_screen, { 0, 0, 296, 225 });
	defeat_by_command_screen->center();
	defeat_by_command_screen->setLocalPos(defeat_by_command_screen->getLocalPos().x, defeat_by_command_screen->getLocalPos().y - 70);
	defeat_by_command_screen->draw_element = false;

	ok_lose_button = app->gui->createImage(jim_screen, { 30, 241, 65, 19 });
	ok_lose_button->parent = defeat_by_jim_screen;
	ok_lose_button->setLocalPos(119, 214);
	ok_lose_button->draw_element = false;
	ok_lose_button->interactive = false;
	ok_lose_button->can_focus = false;
	ok_lose_button->setListener(this);

	// GUI
	// Create Graphic Timers
	graphic_wave_timer = app->gui->createTimer({ 211, 320 }, "UI/Panels/UI_Countdown_Message.png", timer_between_game_states);
	// Info messages
	info_message = app->gui->createInfo({ -54, 0 }, "UI/Panels/UI_Panel_Messages_edit.png");

	return ret;
}

bool GameManager::preUpdate()
{
	eraseEnemiesIfKilled();	
	return true;
}

bool GameManager::update(float dt)
{
	bool ret = true;
	iPoint wave_pos;	

	switch (game_state)
	{
	case(INITIAL_SCREEN) :
	{
		startGame();
		break;
	}
	case(PREPARATION) :
	{
		if (!app->fade_to_black->isFading())
		{
			LOG("PREPARATION");
			if (!info_message->isLoaded())
			{
				info_message->newInfo("The last Terran base must be defend! Don't let it be destroyed!", (gameInfo.time_before_game_starts * 1000) / 2, true);
				info_message->newInfo("Jim Raynor must survive (the yellow one)!", (gameInfo.time_before_game_starts * 1000) / 2);
			}
		}		
	
		if (timer_between_waves.readSec() > gameInfo.time_before_game_starts)
		{
			game_state = FIRST_PHASE;
			info_message->unload();			
		}
		break;
	}
	case(FIRST_PHASE) :
	{
		switch (wave_state)
		{
		case(WAITING_FOR_WAVE_TO_START) :
		{
			LOG("WAITING WAVE TO START - PHASE 1");
			if (!info_message->isLoaded())
			{
				graphic_wave_timer->changeTimer(timer_between_waves, gameInfo.time_before_waves_phase1 * 1000);
				graphic_wave_timer->initiate();
				createWaveInfo(waves_info[current_wave], gameInfo.time_before_waves_phase1);
			}				

			if (timer_between_waves.readSec() > gameInfo.time_before_waves_phase1)
			{
				wave_state = BEGINNING_WAVE;
				info_message->unload();
			}
				
			break;
		}
		case(BEGINNING_WAVE) :
		{
			LOG("BEGINNING WAVE - PHASE 1!!!");
			int random = rand() % 4;
			wave_pos = positionRandomizerWave(random, wave_pos);
			app->audio->playFx(fx_wave_incoming, 0);
			createWave(waves_info[current_wave], wave_pos);
			app->gui->mini_map->activePing(wave_pos);
			wave_state = MIDDLE_WAVE;
			break;
		}
		case(MIDDLE_WAVE) :
		{
			LOG("MIDDLE WAVE - PHASE 1!!!");
			if (isWaveClear())
			{
				LOG("WAVE CLEARED - PHASE 1!!!");
				wave_state = END_WAVE;
			}
			break;
		}

		case(END_WAVE) :
		{
			LOG("WAVE FINISHED - PHASE 1");
			current_wave++;
			wave_state = WAITING_FOR_WAVE_TO_START;
			timer_between_waves.start();
			break;
		}

		}
		checkingGameConditions();
		break;
	}

	case(BOMB_LANDING) :
	{
		//BOMB CREATION GOES HERE
		if(!info_message->isLoaded())
		{
			info_message->newInfo("The BOMB is here! Find it and use against these fucking bastards!", (gameInfo.time_while_bomb_landing * 1000) / 3, true);
			info_message->newInfo("Pick it up with Jim...", (gameInfo.time_while_bomb_landing * 1000) / 3);
			info_message->newInfo("...and return to the base to activate it!", (gameInfo.time_while_bomb_landing * 1000) / 3);

			app->gui->mini_map->activePing(bomb_position.north_east, gameInfo.time_while_bomb_landing * 1000, BOMB);
			app->gui->mini_map->activePing(bomb_position.north_west, gameInfo.time_while_bomb_landing * 1000, BOMB);
			app->gui->mini_map->activePing(bomb_position.south_east, gameInfo.time_while_bomb_landing * 1000, BOMB);
			app->gui->mini_map->activePing(bomb_position.south_west, gameInfo.time_while_bomb_landing * 1000, BOMB);
		}

		if (timer_between_game_states.readSec() > gameInfo.time_while_bomb_landing)
		{
			info_message->unload();

			int random = rand() % 4;
			iPoint bomb_pos = positionRandomizerBomb(random, bomb_pos);
			createEnemiesBombPhase();
			app->entity_manager->addEntity(bomb_pos, BOMB);
			timer_between_waves.start();
			game_state = SECOND_PHASE;
			current_wave = 0;
		}
		break;
	}

	//Second Phase
	case(SECOND_PHASE):
	{
		switch (wave_state)
		{
	
		case(WAITING_FOR_WAVE_TO_START) :
		{
			LOG("WAITING WAVE TO START - PHASE 2");
			if (!info_message->isLoaded())
			{
				graphic_wave_timer->changeTimer(timer_between_waves, gameInfo.time_before_waves_phase2 * 1000);
				graphic_wave_timer->initiate();
				createWaveInfo(waves2_info[0], gameInfo.time_before_waves_phase2);
			}

			if (timer_between_waves.readSec() > gameInfo.time_before_waves_phase2)
			{
				info_message->unload();
				wave_state = BEGINNING_WAVE;
			}				
			break;
		}

		case(BEGINNING_WAVE) :
		{
			LOG("BEGINNING WAVE - PHASE 2 !!!");

			int random = rand() % 4;
			wave_pos = positionRandomizerWave(random, wave_pos);
			app->audio->playFx(fx_wave_incoming, 0);
			createWave(waves2_info[0], wave_pos);
			app->gui->mini_map->activePing(wave_pos);
			wave2_power_counter += incrementPhase2WavePower();
			wave_state = MIDDLE_WAVE;
			break;
		}

		case(MIDDLE_WAVE) :
		{
			LOG("MIDDLE WAVE - PHASE 2 !!!");
			if (isWaveClear())
			{
				LOG("WAVE CLEARED - PHASE 2!!!");
				wave_state = END_WAVE;
			}
			break;
		}
		case(END_WAVE) :
		{
			LOG("WAVE FINISHED - PHASE 2");
			current_wave++;
			wave_state = WAITING_FOR_WAVE_TO_START;
			timer_between_waves.start();

			//Remember bomb positions
			app->gui->mini_map->activePing(bomb_position.north_east, gameInfo.time_while_bomb_landing * 1000, BOMB);
			app->gui->mini_map->activePing(bomb_position.north_west, gameInfo.time_while_bomb_landing * 1000, BOMB);
			app->gui->mini_map->activePing(bomb_position.south_east, gameInfo.time_while_bomb_landing * 1000, BOMB);
			app->gui->mini_map->activePing(bomb_position.south_west, gameInfo.time_while_bomb_landing * 1000, BOMB);
			break;
		}
		}

		checkingGameConditions();
		break;
	}

	case(BOMB_ACTIVATION) :
	{
		//BOMB CREATION GOES HERE
		info_message->unload();
		app->audio->stopMusic();
		info_message->newInfo("The bomb is activated!", (gameInfo.time_while_bomb_landing * 1000) / 2, true);
		info_message->newInfo("Resist Commander, we almost got it!", (gameInfo.time_while_bomb_landing * 1000) / 2);
		info_message->newInfo("Next wave\n", 2500);
		info_message->newInfo("Next wave ---\n", 1000);
		info_message->newInfo("Next wave ---\nError\n(SIGNAL_LOST)", 3000);
		info_message->newInfo("Next wave ---\nError\n(SIGNAL_LOST)\n---", 500);
		info_message->newInfo("Next wave ---\nError\n(SIGNAL_LOST)\n-------", 500);
		info_message->newInfo("Next wave ---\nError\n(SIGNAL_LOST)\n-------Ultralisks=", 3000);
		info_message->newInfo("Next wave ---\nError\n(SIGNAL_LOST)\n-------Ultralisks=\n9999999999....", 10000);

		graphic_wave_timer->changeTimer(timer_between_game_states, gameInfo.time_bomb_detonation * 1000);
		graphic_wave_timer->initiate();
		timer_between_game_states.start();

		app->gui->mini_map->activePing(command_center_position, 8000, BOMB);
		game_state = FINAL_PHASE;
		timer_between_waves.start();
		
		break;
	}

	//Final Phase
	case(FINAL_PHASE) :
	{
		switch (wave_state)
		{

		case(WAITING_FOR_WAVE_TO_START) :
		{
			LOG("WAITING WAVE TO START - PHASE 3");
			if (timer_between_waves.readSec() > gameInfo.time_before_waves_phase3)
				wave_state = BEGINNING_WAVE;
			break;
		}

		case(BEGINNING_WAVE):
		{
			LOG("BEGINNING WAVE - PHASE 3 !!!");
			if (final_music == false)
			{
				app->audio->playMusic("Audio/Music/Our_Last_Hope.mp3");
				final_music = true;
			}
			int random = rand() % 4;
			wave_pos = positionRandomizerWave(random, wave_pos);
			app->audio->playFx(fx_wave_incoming, 0);
			
			createWave(waves3_info[0], { 877, 716 });
			createWave(waves3_info[0], { 3557, 905 });
			createWave(waves3_info[0], { 911, 3021 });
			createWave(waves3_info[0], { 2606, 3056 });
			
			app->gui->mini_map->activePing(wave_pos);
			wave3_power_counter += incrementPhase3WavePower();
			wave_state = MIDDLE_WAVE;
			break;
		}

		case(MIDDLE_WAVE) :
		{
			LOG("MIDDLE WAVE - PHASE 3!!!");
			if (isWaveClear())
			{
				LOG("WAVE CLEARED - PHASE 3!!!");
				wave_state = END_WAVE;
			}
			break;
		}
		case(END_WAVE) :
		{
			LOG("WAVE FINISHED - PHASE 3");
			current_wave++;
			wave_state = WAITING_FOR_WAVE_TO_START;
			timer_between_waves.start();
			break;
		}
		}

		checkingGameConditions();
		break;
	}

	case(WIN):
	{
		if (!is_victory_screen_on)
		{
			app->audio->stopMusic();
			restartGame();
			displayVictoryScreen();
			app->audio->playFx(fx_win, 0);
		}
		break;
	}
	case(LOSE):
	{
		if (!is_defeat_screen_on)
		{
			app->audio->stopMusic();
			restartGame();
			displayDefeatScreen();
			app->audio->playFx(fx_lose, 0);
		}				
		break;
	}
	case(HOLD) :
	{
		//Do nothing. Game cycle frozen.
		break;
	}	
	case(QUIT): 
	{
		// Game is stopped and we return to the initial screen.
		if(!app->fade_to_black->isFading())
			app->fade_to_black->fadeToBlack(app->scene, app->menu, 1.0f);
		break;
	}
	}

	//ADRI
	//-------------------------UI-----------------------------
	//Change the number of WAVE HUD ingame-----------------------
	char n[20];
	sprintf_s(n, 20, "%d", current_wave + 1);
	app->gui->number_of_wave->setText(n, 1);


	//Change the number of RESOURCES HUD ingame-----------------------
	char n2[20];
	sprintf_s(n2, 20, "%i", mineral_resources);
	app->gui->number_of_minerals->setText(n2, 3);


	//Change the number of RESOURCES HUD ingame-----------------------
	char n3[20];
	sprintf_s(n3, 20, "%i", gas_resources);
	app->gui->number_of_gass->setText(n3, 3);

	// Debug ---
	if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	//ROGER: Add resources
	if (debug && app->input->getKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		mineral_resources += 100;
		gas_resources += 100;
	}

	//Delete resources
	if (debug && app->input->getKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		mineral_resources = 0;
		gas_resources = 0;
	}

	//Find Jim
	if (app->input->getKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		if (jim_raynor != NULL)
		{
			app->render->camera.x = -jim_raynor->center.x + (app->render->camera.w / 2);
			app->render->camera.y = -jim_raynor->center.y + (app->render->camera.h / 2);
			app->entity_manager->selection.clear();
			app->entity_manager->selection.insert(pair<uint, Entity*>(jim_raynor->id, jim_raynor));
		}
	}

	//Find COMMANDCENTER
	if (app->input->getKey(SDL_SCANCODE_Y) == KEY_DOWN)
	{
		app->render->camera.x = -command_center_position.x + (app->render->camera.w / 2);
		app->render->camera.y = -command_center_position.y + (app->render->camera.h / 2);
	}
	
	return ret;
}

int GameManager::incrementPhase2WavePower()
{
	waves2_info[0]->zergling_quantity += 2;
	
	if((current_wave + 1) % multiplier_hydra == 0)
		waves2_info[0]->hydralisk_quantity += 1;

	if ((current_wave + 1) % multiplier_muta == 0)
		waves2_info[0]->mutalisk_quantity += 1;
	
	return 1;
	/*REST OF UNITS*/
	//The wave 0 holds all the information of all entities
}

int GameManager::incrementPhase3WavePower()
{
//	waves3_info[0]->zergling_quantity += 3;

	//waves3_info[0]->mutalisk_quantity += 1;

	//waves3_info[0]->hydralisk_quantity += 1;

	//waves3_info[0]->ultralisk_quantity += 1;

	//if (current_wave % multiplier_hydra == 0)
	//	waves2_info[0]->hydralisk_quantity += 1;

	//if (current_wave % multiplier_muta == 0)
	//	waves2_info[0]->mutalisk_quantity += 1;

	//if (current_wave % multiplier_ultra == 0)
	//	waves2_info[0]->ultralisk_quantity += 1;

	return 1;
	/*REST OF UNITS*/
	//The wave 0 holds all the information of all entities
}


void GameManager::checkingGameConditions()
{
	// Finishing Phase 1, bomb lands to somewhere.
	if (game_state == FIRST_PHASE && current_wave == gameInfo.total_waves)
	{
		timer_between_game_states.start();
		game_state = BOMB_LANDING;
	}

	if (command_center_destroyed || jim_raynor_dead)
		game_state = LOSE;

	if (game_state == FINAL_PHASE && timer_between_game_states.readSec() > gameInfo.time_bomb_detonation)
		game_state = WIN;
}

void GameManager::createWave(SizeWave* wave, iPoint position)
{
	float speed = 20.0f;
	Entity *entity_to_add;
	for (uint i = 0; i < wave->zergling_quantity; i++)
	{
		int posx = position.x + (i * 8) - (wave->zergling_quantity * 4);
		int posy = position.y + (i * 8) - (wave->zergling_quantity * 4);

		iPoint position = { posx, posy };

		entity_to_add = app->entity_manager->addEntity(position, ZERGLING);
		current_wave_entities.insert(pair<uint, Entity*>(entity_to_add->id, entity_to_add));
		int dx = i - (wave->zergling_quantity / 2);
		int dy = i - (wave->zergling_quantity / 2);
		Unit* unit = (Unit*)entity_to_add;
		unit->target_pos = command_center_position;
		unit->distance_to_center_selector = { dx, dy };
		if (!app->path->isWalkable(unit->tile_pos))
		{
			unit->path.push_back(app->path->findNearestWalkableTile(unit->tile_pos, app->game_manager->command_center_position, 50));
			unit->has_target = true;
			unit->state = MOVE;
		}
		if (unit->speed < speed)
			speed = unit->speed;
	}

	for (uint i = 0; i < wave->hydralisk_quantity; i++)
	{
		int posx = position.x + (i * 8) - (wave->hydralisk_quantity * 4);
		int posy = position.y + (i * 8) - (wave->hydralisk_quantity * 4);

		iPoint position = { posx, posy };

		entity_to_add = app->entity_manager->addEntity(position, HYDRALISK);
		current_wave_entities.insert(pair<uint, Entity*>(entity_to_add->id, entity_to_add));
		int dx = i - (wave->hydralisk_quantity / 2);
		int dy = i - (wave->hydralisk_quantity / 2);
		Unit* unit = (Unit*)entity_to_add;
		unit->target_pos = command_center_position;
		unit->distance_to_center_selector = { dx, dy };
		if (!app->path->isWalkable(unit->tile_pos))
		{
			unit->path.push_back(app->path->findNearestWalkableTile(unit->tile_pos, app->game_manager->command_center_position, 50));
			unit->has_target = true;
			unit->state = MOVE;
		}
		if (unit->speed < speed)
			speed = unit->speed;
	}

	for (uint i = 0; i < wave->mutalisk_quantity; i++)
	{
		int posx = position.x + (i * 8) - (wave->mutalisk_quantity * 4);
		int posy = position.y + (i * 8) - (wave->mutalisk_quantity * 4);

		iPoint position = { posx, posy };

		entity_to_add = app->entity_manager->addEntity(position, MUTALISK);
		current_wave_entities.insert(pair<uint, Entity*>(entity_to_add->id, entity_to_add));
		int dx = i - (wave->mutalisk_quantity / 2);
		int dy = i - (wave->mutalisk_quantity / 2);
		Unit* unit = (Unit*)entity_to_add;
		unit->target_pos = command_center_position;
		unit->distance_to_center_selector = { dx, dy };
		if (!app->path->isWalkable(unit->tile_pos))
		{
			unit->path.push_back(app->path->findNearestWalkableTile(unit->tile_pos, app->game_manager->command_center_position, 50));
			unit->has_target = true;
			unit->state = MOVE;
		}
		if (unit->speed < speed)
			speed = unit->speed;
	}

	for (uint i = 0; i < wave->ultralisk_quantity; i++)
	{
		int posx = position.x + (i * 8) - (wave->ultralisk_quantity * 4);
		int posy = position.y + (i * 8) - (wave->ultralisk_quantity * 4);

		iPoint position = { posx, posy };

		entity_to_add = app->entity_manager->addEntity(position, ULTRALISK);
		current_wave_entities.insert(pair<uint, Entity*>(entity_to_add->id, entity_to_add));
		int dx = i - (wave->ultralisk_quantity / 2);
		int dy = i - (wave->ultralisk_quantity / 2);
		Unit* unit = (Unit*)entity_to_add;
		unit->target_pos = command_center_position;
		unit->distance_to_center_selector = { dx, dy };
		if (!app->path->isWalkable(unit->tile_pos))
		{
			unit->path.push_back(app->path->findNearestWalkableTile(unit->tile_pos, app->game_manager->command_center_position, 50));
			unit->has_target = true;
			unit->state = MOVE;
		}
		if (unit->speed < speed)
			speed = unit->speed;
	}

	for (map<uint, Entity*>::iterator it = current_wave_entities.begin(); it != current_wave_entities.end(); it++)
	{
		if (it->second->type == UNIT)
		{
			Unit* unit = (Unit*)it->second;
			unit->grouped = true;
			unit->group_speed = speed;
			if (unit->flying)
				unit->flying = false;
		}
	}
}

void GameManager::createWaveInfo(SizeWave* wave, uint display_time)
{
	char c[200];
	sprintf_s(c, "Next wave!\n  Zerglings = %d\n  Hydralisks = %d\n  Mutalisks = %d\n  Ultralisks = %d\n",
		wave->zergling_quantity, wave->hydralisk_quantity, wave->mutalisk_quantity, wave->ultralisk_quantity);
	info_message->newInfo(c, display_time * 1000, true);
}

bool GameManager::postUpdate()
{
	return true;
}

bool GameManager::isWaveClear() 
{
	return current_wave_entities.empty();
}

bool GameManager::cleanUp()
{
	for (vector<SizeWave*>::iterator it = waves_info.begin(); it != waves_info.end(); it++)
		RELEASE(*it);

	for (vector<SizeWave*>::iterator it = waves2_info.begin(); it != waves2_info.end(); it++)
		RELEASE(*it);
	

	waves_info.clear();
	waves2_info.clear();

	return true;
}

void GameManager::startGame()
{
	wave_state = WAITING_FOR_WAVE_TO_START;
	//game_state = FIRST_PHASE;

	game_state = PREPARATION;

	app->entity_manager->addEntity(command_center_position, COMMANDCENTER);
	app->entity_manager->addEntity(factory_position, FACTORY);
	app->entity_manager->addEntity(barrack_position, BARRACK);
	command_center_destroyed = false;
	jim_raynor_dead = false;

	start_game = true;

	defeat_by_jim_screen->disable_element();
	defeat_by_command_screen->disable_element();
	is_defeat_screen_on = false;

	victory_screen->disable_element();
	is_victory_screen_on = false;

	ok_win_button->disable_element();
	ok_lose_button->disable_element();

	unsigned int size_marines_x = initial_size.marines_quantityX * 2;
	unsigned int size_marines_y = initial_size.marines_quantityY ;

	//---- Initial units ----
	createMarines({ command_center_position.x - 100, command_center_position.y - 120 }, size_marines_x, size_marines_y);
	iPoint pos = { command_center_position.x - 70, command_center_position.y - 140 };
	jim_raynor = app->entity_manager->addEntity(pos, JIM_RAYNOR);
	//--------
	
	app->render->setCameraOnPosition(command_center_position);
	
	current_wave = 0;
	mineral_resources = 0;
	gas_resources = 0;
	final_music = false;

	timer_between_waves.start();
}

void GameManager::stopGame()
{
	game_state = HOLD; // Cycle of game_manager is frozen...
	start_game = false;
	restartGame();	   // Reset all values to a possible new game.
}

void GameManager::initiateGame()
{
	game_state = INITIAL_SCREEN;
	timer_between_waves.start();
}

void GameManager::onGui(GuiElements* ui, GUI_EVENTS event)
{
	if (ui == ok_win_button)
	{
		switch (event)
		{
		case(MOUSE_ENTERS) :
			ok_win_button->setSection({ 198, 242, 62, 19 });
			break;
		case(MOUSE_LEAVES) :			
			ok_win_button->setSection({ 37, 242, 62, 19 });
			break;
		case(MOUSE_LCLICK_DOWN) :
			ok_win_button->setSection({ 120, 242, 62, 19 });
			break;
		case(MOUSE_LCLICK_UP) :
			app->audio->playFx(fx_click, 0);
			ok_win_button->setSection({ 37, 242, 62, 19 });
			game_state = QUIT;

			ok_win_button->disable_element();
			victory_screen->disable_element();
			break;
		}
	}

	if (ui == ok_lose_button)
	{
		switch (event)
		{
		case(MOUSE_ENTERS) :
			ok_lose_button->setSection({ 200, 241, 65, 19 });
			break;
		case(MOUSE_LEAVES) :
			ok_lose_button->setSection({ 30, 241, 65, 19 });
			break;
		case(MOUSE_LCLICK_DOWN) :
			ok_lose_button->setSection({ 117, 241, 65, 19 });
			break;
		case(MOUSE_LCLICK_UP) :
			app->audio->playFx(fx_click, 0);
			ok_win_button->setSection({ 30, 241, 65, 19 });
			app->audio->playMusic("Audio/Music/Background_Music.mp3", 0.f);
			game_state = QUIT;

			ok_lose_button->disable_element();
			defeat_by_command_screen->disable_element();
			defeat_by_jim_screen->disable_element();

			break;
		}
	}
}

void GameManager::restartGame()
{
	map<uint, Entity*>::iterator it = app->entity_manager->active_entities.begin();
	for (; it != app->entity_manager->active_entities.end(); ++it)
	{
		it->second->coll->to_delete = true;
		it->second->to_delete = true;
	}

	start_game = false;

	waves3_info[0]->zergling_quantity = num_zergling;
	waves3_info[0]->hydralisk_quantity = num_hydralisk;
	waves3_info[0]->mutalisk_quantity = num_mutalisk;
	waves3_info[0]->ultralisk_quantity = num_ultralisk;

	// GUI information reset
	info_message->unload();
	graphic_wave_timer->deactivate();	
	app->gui->cursor->backToIdle();
}

//unsigned int is intended ask me WHY I do it instead of uint.
void GameManager::createMarines(iPoint position,unsigned int sizex, unsigned int sizey)
{
	for (int i = 0; i < sizex; i++)
	{
		for (int j = 0; j < sizey; j++)
		{
			int posx = position.x + (sizex * i * 10);
			int posy = position.y + (sizey * j * 10);

			app->entity_manager->addEntity(iPoint({ posx, posy }), MARINE);
		}
	}
}

void GameManager::displayVictoryScreen()
{
	is_victory_screen_on = true;
	victory_screen->draw_element = true;

	ok_win_button->enable_element();
}

void GameManager::displayDefeatScreen()
{
	is_defeat_screen_on = true;

	if (jim_raynor_dead)
		defeat_by_jim_screen->draw_element = true;

	if (command_center_destroyed)	{
		defeat_by_command_screen->draw_element = true;
	}
	ok_lose_button->enable_element();
}

bool GameManager::isGameStarted() const
{
	return start_game;
}

void GameManager::eraseEnemiesIfKilled()
{
	if (current_wave_entities.size() > 0 && (wave_state == MIDDLE_WAVE))
	{
		map<uint, Entity*>::iterator it2 = current_wave_entities.begin();
		for (; it2 != current_wave_entities.end();)
		{
			if (it2->second->to_delete == true)
			{
				AddPointsEnemy(it2->second);
				it2 = current_wave_entities.erase(it2);
				//Score is added up when an enemy is killed
				
			}
			else
			{
				it2++;
			}
		}
	}
}


void GameManager::AddPointsEnemy(Entity* e)
{

	switch (e->specialization)
	{
	case(ZERGLING) :
		updateResources(app->entity_manager->zergling_mineral_cost, app->entity_manager->zergling_gas_cost);
		break;
	case(HYDRALISK) :
		updateResources(app->entity_manager->hydralisk_mineral_cost, app->entity_manager->hydralisk_gas_cost);
		break;
	case(MUTALISK) :
		updateResources(app->entity_manager->mutalisk_mineral_cost, app->entity_manager->mutalisk_gas_cost);
		break;
	case(ULTRALISK) :
		updateResources(app->entity_manager->ultralisk_mineral_cost, app->entity_manager->ultralisk_gas_cost);
		break;
	}
}

void GameManager::updateResources(int mineral, int gas)
{
	mineral_resources += mineral;
	gas_resources += gas;
}

iPoint GameManager::positionRandomizerBomb(int random, iPoint bomb_pos)
{
	switch (random)
	{
	case(BOMBPOS1) :
		bomb_pos = bomb_position.north_west;
		break;

	case(BOMBPOS2) :
		bomb_pos = bomb_position.north_east;
		break;

	case(BOMBPOS3) :
		bomb_pos = bomb_position.south_west;
		break;

	case(BOMBPOS4) :
		bomb_pos = bomb_position.south_east;
		break;
	}

	return bomb_pos;
}

void GameManager::createEnemiesBombPhase()
{
	Unit* entity_added;
	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.north_east, HYDRALISK);
	entity_added->target_pos = bomb_position.north_east;
	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.north_east, MUTALISK);
	entity_added->target_pos = bomb_position.north_east;
	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.north_east, HYDRALISK);
	entity_added->target_pos = bomb_position.north_east;

	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.north_west, ULTRALISK);
	entity_added->target_pos = bomb_position.north_west;
	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.north_west, MUTALISK);
	entity_added->target_pos = bomb_position.north_west;

	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.south_east, HYDRALISK);
	entity_added->target_pos = bomb_position.south_east;
	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.south_east, HYDRALISK);
	entity_added->target_pos = bomb_position.south_east;
	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.south_east, MUTALISK);
	entity_added->target_pos = bomb_position.south_east;

	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.south_west, HYDRALISK);
	entity_added->target_pos = bomb_position.south_west;
	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.south_west, MUTALISK);
	entity_added->target_pos = bomb_position.south_west;
	entity_added = (Unit*)app->entity_manager->addEntity(bomb_position.south_west, ULTRALISK);
	entity_added->target_pos = bomb_position.south_west;
}

iPoint GameManager::positionRandomizerWave(int random, iPoint wave_pos)
{
	switch (random)
	{
	case(NORTHWEST) :
		wave_pos = wave_position().north_west;
		break;

	case(NORTHEAST) :
		wave_pos = wave_position().north_east;
		break;

	case(SOUTHWEST) :
		wave_pos = wave_position().south_west;
		break;

	case(SOUTHEAST) :
		wave_pos = wave_position().south_east;
		break;
	}

	return wave_pos;
}

// Load / Save
bool GameManager::load(pugi::xml_node &node)
{
	info_message->unload();
	graphic_wave_timer->deactivate();

	mineral_resources = node.child("resources").attribute("mineral").as_int();
	gas_resources = node.child("resources").attribute("gas").as_int();
	
    game_state = (GAME_STATE)node.child("phases").attribute("game_phase").as_int();
	wave_state = (WAVE_STATE)node.child("phases").attribute("wave_phase").as_int();
	current_wave = node.child("phases").attribute("current_wave").as_int();
	start_game = node.child("phases").attribute("start_game").as_bool();

	list_ids_enemies.clear();
	istringstream in(string(node.child("list_ids_enemies").attribute("ids").as_string()));
	uint id;
	while (in >> id)
		list_ids_enemies.push_back(id);

	return true;
}

bool GameManager::save(pugi::xml_node &node) const
{
	pugi::xml_node resources = node.append_child("resources");
	resources.append_attribute("mineral") = mineral_resources;
	resources.append_attribute("gas") = gas_resources;

	pugi::xml_node phases = node.append_child("phases");
	phases.append_attribute("game_phase") = game_state;
	phases.append_attribute("wave_phase") = wave_state;
	phases.append_attribute("current_wave") = current_wave;
	phases.append_attribute("start_game") = start_game;

	pugi::xml_node list_ids_enemies = node.append_child("list_ids_enemies");
	
	// Here I save the ids of the zergs that conforms the current wave.
	stringstream ss;
	for (map<uint, Entity*>::const_iterator it = current_wave_entities.begin(); it != current_wave_entities.end(); ++it)
		ss << it->second->id << ' ';
	string ids;
	getline(ss, ids);	
	list_ids_enemies.append_attribute("ids") = ids.data();

	return true;
}