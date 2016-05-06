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

#include "GuiImage.h"
#include "GuiLabel.h"

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

GameManager::GameManager()
{
	name.assign("game_manager");
}

bool GameManager::awake(pugi::xml_node &node) 
{
	bool ret = true;

	/*Game Info load*/
	gameInfo.total_waves = node.child("totalWaves").attribute("value").as_uint();
	gameInfo.time_before_start = node.child("timeBeforeStart").attribute("value").as_uint();
	gameInfo.time_before_waves_phase1 = node.child("timeBetweenWavesPhase1").attribute("value").as_uint();
	gameInfo.time_before_waves_phase2 = node.child("timeBetweenWavesPhase2").attribute("value").as_uint();
	gameInfo.time_before_end = node.child("timeBeforeEnd").attribute("value").as_uint();

	/*Player Info Load*/
	initial_size.marines_quantity = node.child("InitialSizePlayer").attribute("marines").as_int();
	initial_size.scv_quantity = node.child("InitialSizePlayer").attribute("scv").as_int();
	//initialSize.marines_quantity = node.child("InitialSizePlayer").attribute("medic").as_uint();
	command_center_position.x = node.child("CommandCenterPosition").attribute("coordx").as_int();
	command_center_position.y = node.child("CommandCenterPosition").attribute("coordy").as_int();




	/*Score data Load*/
	zergling_score = node.child("ZerglingScore").attribute("value").as_uint();
	hydralisk_score = node.child("HydraliskScore").attribute("value").as_uint();
	mutalisk_score = node.child("MutaliskScore").attribute("value").as_uint();



	/*Wave Info Load*/
	for (pugi::xml_node tempNode = node.child("SizeWave"); tempNode; tempNode = tempNode.next_sibling("SizeWave"))
	{
			uint num_zergling = tempNode.attribute("zerglings").as_uint();
			uint num_hydralisk = tempNode.attribute("hydralisks").as_uint();
			uint num_mutalisk = tempNode.attribute("mutalisks").as_uint();

			SizeWave* wave = new SizeWave(num_zergling, num_hydralisk, num_mutalisk);
			waves_info.push_back(wave);
	}

	/*Wave2 Info Load*/
	for (pugi::xml_node tempNode = node.child("SizeWave2"); tempNode; tempNode = tempNode.next_sibling("SizeWave2"))
	{
		uint num_zergling = tempNode.attribute("zerglings").as_uint();
		uint num_hydralisk = tempNode.attribute("hydralisks").as_uint();
		uint num_mutalisk = tempNode.attribute("mutalisks").as_uint();

		SizeWave* wave = new SizeWave(num_zergling, num_hydralisk, num_mutalisk);
		waves2_info.push_back(wave);
	}


	return ret;
}


bool GameManager::start()
{
	bool ret = true;

	LOG("LAST HOPE GAME STARTS!");

	fx_win = app->audio->loadFx("Audio/FX/UI/YouWin.wav");
	fx_lose = app->audio->loadFx("Audio/FX/UI/YouLose.wav");
	fx_click = app->audio->loadFx("Audio/FX/UI/Click_1.wav");

	//Backgorund audio (DEBUG include)
	app->audio->playMusic("Audio/Music/Background_Music.mp3", 0.f);
	for (unsigned int i = 0; i <= 3; i++)
	{
		app->audio->volumeDown();
	}

	start_image = app->tex->loadTexture("Screens/Start_Image.png");

	start_screen = app->gui->createImage(start_image, { 16, 16, 296, 336 });
	start_screen->center();
	start_screen->setLocalPos(start_screen->getLocalPos().x - 5, start_screen->getLocalPos().y - 50);

	start_button = app->gui->createImage(start_image, { 339, 164, 141, 39 });
	start_button->parent = start_screen;
	start_button->center();
	start_button->interactive = true;
	start_button->can_focus = true;
	start_button->setListener(this);

	close_button = app->gui->createImage(start_image, { 339, 229, 141, 39 });
	close_button->parent = start_screen;
	close_button->center();
	close_button->setLocalPos(close_button->getLocalPos().x, close_button->getLocalPos().y + 80);
	close_button->interactive = true;
	close_button->can_focus = true;
	close_button->setListener(this);

	defeat_atlas = app->tex->loadTexture("Screens/Defeat_Screen_Atlas.png");
	defeat_screen = app->gui->createImage(defeat_atlas, { 0, 0, 384, 256 });
	defeat_screen->center();
	defeat_screen->setLocalPos(defeat_screen->getLocalPos().x, defeat_screen->getLocalPos().y - 70);
	defeat_screen->draw_element = false;
	is_defeat_screen_on = false;

	victory_atlas = app->tex->loadTexture("Screens/Victory_Screen_Atlas.png");
	victory_screen = app->gui->createImage(victory_atlas, { 0, 0, 384, 256 });
	victory_screen->center();
	victory_screen->setLocalPos(victory_screen->getLocalPos().x, victory_screen->getLocalPos().y - 70);
	victory_screen->draw_element = false;
	is_victory_screen_on = false;

	retry_button = app->gui->createImage(defeat_atlas, { 384, 0, 104, 28 });
	retry_button->parent = victory_screen;
	retry_button->setLocalPos(265, 150);
	retry_button->draw_element = false;
	retry_button->interactive = false;
	retry_button->can_focus = false;
	retry_button->setListener(this);

	exit_button = app->gui->createImage(defeat_atlas, { 384, 28, 104, 28 });
	exit_button->parent = victory_screen;
	exit_button->setLocalPos(265, 190);
	exit_button->draw_element = false;
	exit_button->interactive = false;
	exit_button->can_focus = false;
	exit_button->setListener(this);

	game_state = INITIAL_SCREEN;

	return ret;
}

bool GameManager::preUpdate()
{
	eraseEnemiesIfKilled();
	isWaveClear();
	return true;
}

bool GameManager::update(float dt)
{
	bool ret = true;

	switch (game_state)
	{
	case(INITIAL_SCREEN) : 
	{
		break;
	}
	case(PREPARATION):
	{
		LOG("PREPARATION");
		startGame();		
		break;
	}
	case(FIRST_PHASE):
	{	
		switch (wave_state)
		{
			case(WAITING_FOR_WAVE_TO_START) :
			{
				// CRZ -> Se mostraría informe de la siguiente oleada.
				LOG("WAITING WAVE TO START");
				if (timer_between_waves.readSec() > gameInfo.time_before_waves_phase1)
					wave_state = BEGINNING_WAVE;
				break;
			}

			case(BEGINNING_WAVE) :
			{
				LOG("BEGINNING WAVE!!!");
				wave_state = MIDDLE_WAVE;
				createWave(waves_info[current_wave], iPoint(1419, 800));
				wave_wiped = false;
				break;
			}
			case(MIDDLE_WAVE) :
			{
				LOG("MIDDLE WAVE !!!");
				if (wave_wiped)
				{
					LOG("WAVE CLEARED!!!");
					wave_state = END_WAVE;
				}						
				break;
			}


			case(END_WAVE):
			{
				current_wave++;	
				if (current_wave > gameInfo.total_waves)
					current_wave = 0;
				// CRZ-> Es la última wave? Saber que tenemos que saltar a la SECOND_PHASE!
				wave_state = WAITING_FOR_WAVE_TO_START;
				timer_between_waves.start();
				break;
			}
			case(PHASE1_END) : 
			{
				LOG("PHASE 1 ENDED");
				break;
			}
			
		}	
		checkingGameConditions();
		break;
	}

	//Second Phase
	case(SECOND_PHASE) :
	{
		

		switch (wave2_state)
		{
			case(WAITING_FOR_PHASE2_TO_START) :
			{
				LOG("The bomb has landed look for it.");//Audio voice
				
					wave2_state = BEGINNING_WAVE_2;
				
				break;
			}

			case(BEGINNING_WAVE_2) :
			{
				LOG("BEGINNING WAVE 2!!!");
				
				wave2_state = MIDDLE_WAVE_2;
				createWave(waves2_info[0], iPoint(1419, 800));
				wave2_power_counter += incrementPhase2WavePower();
				current_wave = 0;
				timer_phase2_wave.start();
				break;
			}

			case(MIDDLE_WAVE_2) :
			{
				LOG("MIDDLE WAVE2 !!!");
				if (timer_phase2_wave.readSec() > gameInfo.time_before_waves_phase2)
				{
					LOG("Wave Creation!!!");
					wave2_state = END_WAVE_2;
					wave_wiped = false;
					timer_phase2_wave.start();
				}
				break;
			}
			case(END_WAVE_2) :
			{
				LOG("WAVE 2 FINISH");

				wave2_state = BEGINNING_WAVE_2;
				break;
			}
		}
		checkingGameConditions();

		break;
	}
		

	case(WIN) :
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
	
	case(QUIT): //When close button is pressed
	{
		return false;
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
	app->gui->number_of_minerals->setText(n2, 2);


	//Change the number of RESOURCES HUD ingame-----------------------
	char n3[20];
	sprintf_s(n3, 20, "%i", gas_resources);
	app->gui->number_of_gass->setText(n3, 2);

	//ROGER: Add resources
	if (app->input->getKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		mineral_resources = mineral_resources + 100;
		gas_resources = gas_resources + 100;
	}
	//Delete resources
	if (app->input->getKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		mineral_resources = 0;
		gas_resources = 0;
	}
	
	return ret;
}

int GameManager::incrementPhase2WavePower()
{
	waves2_info[0]->zergling_quantity += 2;
	waves2_info[0]->hydralisk_quantity += 1;
	waves2_info[0]->mutalisk_quantity += 1;
	
	return 1;
	/*REST OF UNITS*/
	//The wave 0 holds all the information of all entities
}


void GameManager::checkingGameConditions()
{
	if (current_wave == gameInfo.total_waves)
	{
		game_state = SECOND_PHASE;
	}
	
	/*PHASE 3
	if (current_wave2 == bombPlanted)
	{
		
	}
	*/

	if (command_center_destroyed)
	{
		game_state = LOSE;
		start_game = false;
	}
}

void GameManager::createWave(SizeWave* wave, iPoint position)
{
	Entity *entity_to_add;
	for (uint i = 0; i < wave->zergling_quantity; i++)
	{
		int posx = position.x + (wave->zergling_quantity * i * 2);
		int posy = position.y + (wave->zergling_quantity * i * 2);

		iPoint position = { posx, posy };

		entity_to_add = app->entity_manager->addEntity(position, ZERGLING);
		current_wave_entities.insert(pair<uint, Entity*>(entity_to_add->id, entity_to_add));
	}

	for (uint i = 0; i < wave->hydralisk_quantity; i++)
	{
		int posx = position.x + (wave->hydralisk_quantity * i * 2);
		int posy = position.y + (wave->hydralisk_quantity * i * 2);

		iPoint position = { posx, posy };

		entity_to_add = app->entity_manager->addEntity(position, HYDRALISK);
		current_wave_entities.insert(pair<uint, Entity*>(entity_to_add->id, entity_to_add));
	}

	for (uint i = 0; i < wave->mutalisk_quantity; i++)
	{
		int posx = position.x + (wave->mutalisk_quantity * i * 2);
		int posy = position.y + (wave->mutalisk_quantity * i * 2);

		iPoint position = { posx, posy };

		entity_to_add = app->entity_manager->addEntity(position, MUTALISK);
		current_wave_entities.insert(pair<uint, Entity*>(entity_to_add->id, entity_to_add));
	}
}

bool GameManager::postUpdate()
{
	return true;
}

void GameManager::addPoints(uint totalUnitsKilledCurrentFrame)
{
	total_score += zergling_score * totalUnitsKilledCurrentFrame;
}

bool GameManager::isWaveClear() 
{
	wave_wiped = current_wave_entities.empty() ? true : false;
	
	if (wave_wiped == true)
		LOG("WAVE_WIPED");

	return wave_wiped;
}

bool GameManager::cleanUp()
{
	for (vector<SizeWave*>::iterator it = waves_info.begin(); it != waves_info.end(); it++)
		RELEASE(*it);

	waves_info.clear();

	return true;
}

void GameManager::startGame()
{
	current_wave = 0;
	wave_state = WAITING_FOR_WAVE_TO_START;
	game_state = FIRST_PHASE;

	iPoint p = command_center_position;
	app->entity_manager->addEntity(p, COMMANDCENTER);  //BASE CREATION
	command_center_destroyed = false;
	start_game = true;

	defeat_screen->draw_element = false;
	is_defeat_screen_on = false;

	victory_screen->draw_element = false;
	is_victory_screen_on = false;

	retry_button->disable_element();
	exit_button->disable_element();

	unsigned int size_marines_x = SIZEMARINESX * 3;
	unsigned int size_marines_y = SIZEMARINESY ;

	createMarines({ 1500, 2150 }, size_marines_x, size_marines_y);
	app->render->setCameraOnPosition(p);

	timer_between_waves.start();
}

void GameManager::onGui(GuiElements* ui, GUI_EVENTS event)
{
	if (ui == start_button)
	{
		switch (event)
		{

		case(MOUSE_LCLICK_DOWN) :
			start_button->setSection({ 339, 103, 141, 38 });
			break;

		case(MOUSE_LCLICK_UP) :

			start_button->setSection({ 339, 229, 141, 39 });			
			
			start_screen->draw_element = false;
			start_button->disable_element();
			close_button->disable_element();

			time_before_starting_game.start();	
			game_state = PREPARATION;
			app->audio->playFx(fx_click, 0);
			break;
		}
	}

	if (ui == exit_button)
	{
		switch (event)
		{
		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click, 0);
			exit_button->setSection({ 384, 84, 104, 28 });
			break;
		case(MOUSE_LCLICK_UP) :
			exit_button->setSection({ 384, 28, 104, 28 });
			game_state = QUIT;
			break;
		}
	}

	if (ui == close_button)
	{
		switch (event)
		{
		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click, 0);
			close_button->setSection({ 339, 278, 145, 40 });
			break;
		case(MOUSE_LCLICK_UP) :
			close_button->setSection({ 339, 229, 145, 40 });
			game_state = QUIT;
			break;
		}
	}

	if (ui == retry_button)
	{
		switch (event)
		{
		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click, 0);
			retry_button->setSection({ 384, 56, 104, 28 });
			break;
		case(MOUSE_LCLICK_UP) :
			retry_button->setSection({ 384, 0, 104, 28 });
			app->audio->playMusic("Audio/Music/Background_Music.mp3", 0.f);
			for (unsigned int i = 0; i <= 3; i++)
			{
				app->audio->volumeDown();
			}
			game_state = PREPARATION;			
			break;
		}
	}
}

void GameManager::restartGame()
{
	//CRZ: 
	map<uint, Entity*>::iterator it = app->entity_manager->active_entities.begin();
	for (; it != app->entity_manager->active_entities.end(); ++it)
	{
		it->second->coll->to_delete = true;
		it->second->to_delete = true;
	}
	//---------------------------------------------------------

	current_wave = 0;
	score = 0;
	enemy_count = 0;
	kill_count = 0;
	score_current_wave = 0;
	total_score = 0;
	
	resources = 0;
	mineral_resources = 0;
	gas_resources = 0;

	time_before_starting_game.start();
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

	retry_button->enable_element();
	exit_button->enable_element();

}

void GameManager::displayDefeatScreen()
{
	defeat_screen->draw_element = true;
	is_defeat_screen_on = true;
	
	retry_button->enable_element();
	exit_button->enable_element();
}

bool GameManager::isGameStarted() const
{
	return start_game;
}

void GameManager::eraseEnemiesIfKilled()
{
	if (current_wave_entities.size() > 0 && (wave_state == MIDDLE_WAVE || wave2_state == MIDDLE_WAVE))
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
	if (e->specialization == ZERGLING)
	{
		mineral_resources += 50;
		gas_resources += 0;
	}

	/*
	else if (e->specialization == HYDRALISK)
	{
		mineral_resources += 50;
		gas_resources += 0;
	}
	.
	.
	.
	.
	*/

}