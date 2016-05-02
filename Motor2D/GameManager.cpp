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


bool GameManager::awake(pugi::xml_node &node) 
{
	bool ret = true;

	/*Game Info load*/

	gameInfo.total_waves = node.child("totalWaves").attribute("value").as_uint();
	gameInfo.time_before_start = node.child("timeBeforeStart").attribute("value").as_uint();
	gameInfo.time_before_waves_phase1 = node.child("timeBetweenWavesPhase1").attribute("value").as_uint();
	gameInfo.time_before_waves_phase2 = node.child("timeBetweenWavesPhase2").attribute("value").as_uint();
	gameInfo.time_before_end = node.child("timeBeforeEnd").attribute("value").as_uint();

	/*Wave Info Load*/

	wave1.zergling_quantity = node.child("SizeWave1").attribute("zerglings").as_uint();
	wave1.hydralisk_quantity = node.child("SizeWave1").attribute("hydralisks").as_uint();
	wave1.mutalisk_quantity = node.child("SizeWave1").attribute("mutalisks").as_uint();
	// CRZ -> list_of_waves.at(current_wave);

	wave2.zergling_quantity = node.child("SizeWave2").attribute("zerglings").as_uint();
	wave2.hydralisk_quantity = node.child("SizeWave2").attribute("hydralisks").as_uint();
	wave2.mutalisk_quantity = node.child("SizeWave2").attribute("mutalisks").as_uint();


	/*Player Info Load*/

	initial_size.marines_quantity = node.child("InitialSizePlayer").attribute("marines").as_uint();
	initial_size.scv_quantity = node.child("InitialSizePlayer").attribute("scv").as_uint();
	//initialSize.marines_quantity = node.child("InitialSizePlayer").attribute("medic").as_uint();


	/*Score data Load*/

	zergling_score = node.child("ZerglingScore").attribute("value").as_uint();
	hydralisk_score = node.child("HydraliskScore").attribute("value").as_uint();
	mutalisk_score = node.child("MutaliskScore").attribute("value").as_uint();
	
	return ret;
}


bool GameManager::start()
{
	bool ret = true;

	LOG("LAST HOPE GAME STARTS!");
	
	fx_click = app->audio->loadFx("Audio/FX/UI/UI_Click.wav");
	start_image = app->tex->loadTexture("Screens/Start_Image.png");

	title_screen = app->gui->createImage(start_image, { 16, 16, 296, 336 });
	title_screen->center();
	title_screen->setLocalPos(title_screen->getLocalPos().x - 5, title_screen->getLocalPos().y - 50);

	start_button = app->gui->createImage(start_image, { 339, 164, 141, 39 });
	start_button->parent = title_screen;
	start_button->center();
	start_button->interactive = true;
	start_button->can_focus = true;
	start_button->setListener(this);

	exit_button = app->gui->createImage(start_image, { 339, 229, 141, 39 });
	exit_button->parent = title_screen;
	exit_button->center();
	exit_button->setLocalPos(exit_button->getLocalPos().x, exit_button->getLocalPos().y + 80);
	exit_button->interactive = true;
	exit_button->can_focus = true;
	exit_button->setListener(this);

	defeat_img = app->tex->loadTexture("Screens/defeat_screen.png");
	defeat_screen = app->gui->createImage(defeat_img, { 0, 0, 640, 480 });
	defeat_screen->center();
	defeat_screen->setLocalPos(defeat_screen->getLocalPos().x, defeat_screen->getLocalPos().y);
	defeat_screen->draw_element = false;
	is_defeat_screen_on = false;
	
	victory_img = app->tex->loadTexture("Screens/victory_screen.png");
	victory_screen = app->gui->createImage(victory_img, { 0, 0, 640, 480 });
	victory_screen->center();
	victory_screen->setLocalPos(victory_screen->getLocalPos().x, victory_screen->getLocalPos().y);
	victory_screen->draw_element = false;
	is_victory_screen_on = false;

	retry_button = app->gui->createImage(defeat_img, { 121, 170, 105, 28 });
	retry_button->parent = victory_screen;
	retry_button->setLocalPos(121, 170);
	retry_button->draw_element = false;
	retry_button->interactive = false;
	retry_button->can_focus = false;
	retry_button->setListener(this);

	close_button = app->gui->createImage(defeat_img, { 121, 213, 105, 28 });
	close_button->parent = victory_screen;
	close_button->setLocalPos(121, 211);
	close_button->draw_element = false;
	close_button->interactive = false;
	close_button->can_focus = false;
	close_button->setListener(this);
	wave_state = WAITING_FOR_WAVE_TO_START;

	optimizationEraseEnemy.start();
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
	case(INITIAL_SETUP) : 
	{
		time_before_starting_game.start();
		game_state = PREPARATION;
		break;
	}

		case(PREPARATION):
		{
			LOG("PREPARATION");
			bool timeElapsed = time_before_starting_game.waitSec(time_before_starting_game, gameInfo.time_before_start);
			// CRZ -> Cambiar a timer como el de abajo.
			// CRZ -> Se mostraría informe de la siguiente oleada.			

			if (timeElapsed != NULL)//Time before starting
			{
				// CRZ -> StartGame() tendría que estar aquí.
				timer_between_waves.start();
				game_state = FIRST_PHASE;
			}
			break;
		}
		case(FIRST_PHASE):
		{	
			LOG("FIRST PHASE");

			switch (wave_state)
			{
				LOG("WAITING WAVE TO START");
				case(WAITING_FOR_WAVE_TO_START) :
				{
					if (timer_between_waves.readSec() > WAVETIME1)
					{
						wave_state = BEGINNING_WAVE;
					}
					break;
				}

				case(BEGINNING_WAVE) :
				{
					LOG("BEGINNING WAVE!!!");
					wave_state = MIDDLE_WAVE;
					app->entity_manager->createWave(wave1.zergling_quantity, wave1.hydralisk_quantity, wave1.mutalisk_quantity, iPoint(1419, 800));
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
					if (current_wave == gameInfo.total_waves)
						game_state = WIN;
					// CRZ-> Es la última wave? Saber que tenemos que saltar a la SECOND_PHASE!
					wave_state = WAITING_FOR_WAVE_TO_START;
					timer_between_waves.start();
					break;
				}
			}
			break;
		}	
		case(WIN) :
		{
			if (!is_victory_screen_on)
				displayVictoryScreen();
			break;
		}
	}



	/*
	if (start_game)
	{
		bool timeElapsed = false;
		//If first_phase is activated it will run the timer and get inside the other code
		if (first_phase == NULL)
			 timeElapsed = time_before_starting_game.waitSec(time_before_starting_game, gameInfo.time_before_start);


		if (timeElapsed != NULL)//Time before starting
		{
			first_phase = true;
		}
		
		if (first_phase)//The game starts. OK
		{
			if (current_wave < total_waves)//If there're remaining waves. OK
			{
				bool time_elapsed = false;
				if (ongoing_wave == false)
					time_elapsed = time_between_waves.waitSec(time_between_waves,gameInfo.time_before_waves_phase1);

				if (time_elapsed && wave_wiped == NULL)//Time passed//Wave is created
					{
						
						//GoWave(current_wave);
						//app->entity_manager->createWave(wave1.zergling_quantity, wave1.hydralisk_quantity, wave1.mutalisk_quantity, iPoint(1419, 800));
						ongoing_wave = true;
						wave_wiped = false;
						
					}
				if (wave_wiped == true) //When the wave is finished
				{
					current_wave++;
					time_between_waves.start();
					//current_wave_info
				}
					
				
					if (wave_wiped != NULL)
						time_between_waves.start();

				if (current_wave >= total_waves)
					first_phase = false;

			}
		}
		*/
		
		
		/*
		else if (second_phase)
		{
			
		}
		else
		{
			if (checkGameOver())
			{
				//Display message of game over
				LOG("GAME OVER");
				//Display Score
				LOG("Score: %d", score_current_wave);
			}
		}

		

	}
		*/
		
		//if (current_waves <= TOTALWAVES)
		//{
		//	//ADRI
		//	//Check if we have killed all the enemies to begin a new wave
		//	if (wave_wiped)
		//	{
		//		//Get Resources
		//		mineral_resources += 75;
		//		gas_resources += 75;
		//		resources++;
		//		wave_wiped = false;
		//	}
		//

		//	if (time_between_waves.readSec() >= WAVETIME1 && sizeWave() <= 0) //We check how much time we do have left before releasing a new wave
		//	{
		//		if (current_waves == 0)
		//		{
		//			LOG("Wave 1 is over get prepared!!!!");

		//			app->entity_manager->createWave(wave1.zergling_quantity,wave1.hydralisk_quantity, wave1.mutalisk_quantity, iPoint(1419, 800));
		//			current_waves++;
		//			resources++;

		//			time_between_waves.start();
		//		}
		//	}

		//	if (current_waves == 1 && sizeWave() <= 0)
		//	{   
		//		//Get Resources
		//		mineral_resources += 150;
		//		gas_resources += 50;
		//		resources ++;
		//		won = true;
		//		start_game = false;
		//	}

	
		//}

		

		

		//ADRI
		//-------------------------UI-----------------------------
		//Change the number of WAVE HUD ingame-----------------------
		char n[20];
		sprintf_s(n, 20, "%d", current_wave);
		app->gui->number_of_wave->setText(n, 1);


		//Change the number of RESOURCES HUD ingame-----------------------
		char n2[20];
		sprintf_s(n2, 20, "%i", mineral_resources);
		app->gui->number_of_minerals->setText(n2, 2);


		//Change the number of RESOURCES HUD ingame-----------------------
		char n3[20];
		sprintf_s(n3, 20, "%i", gas_resources);
		app->gui->number_of_gass->setText(n3, 2);

		//-----------------------------------------------------------
		//}	

	/*if (game_over)
	{
		if (!is_defeat_screen_on)
			displayDefeatScreen();
	}


	if (close)
		ret = false;*/

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

bool GameManager::postUpdate()
{
	return true;
}

void GameManager::addPoints(uint totalUnitsKilledCurrentFrame)
{
	total_score += ZERGLINGSCORE * totalUnitsKilledCurrentFrame;
}

bool GameManager::isWaveClear() 
{
	wave_wiped = (app->entity_manager->current_wave_entities.empty() ? true : false);
	return wave_wiped;
}

bool GameManager::cleanUp()
{
	bool ret = false;

	RELEASE(start_button);
	RELEASE(title_screen);
	RELEASE(exit_button);
	RELEASE(close_button);
	RELEASE(victory_screen);
	RELEASE(retry_button);

	return ret;
}

void GameManager::startGame()
{
		start_game = true;
		game_over = false;
		won = false;
		time_between_waves.start();

		iPoint p = COMMANDCENTERPOSITION;
		app->entity_manager->addEntity(p, COMMANDCENTER);  //BASE CREATION
		
		unsigned int size_marines_x = SIZEMARINESX;
		unsigned int size_marines_y = SIZEMARINESY;

		createMarines({ 1500, 2150 }, size_marines_x, size_marines_y);
		app->render->setCameraOnPosition(p);
		
		time_before_starting_game.start();
}

bool GameManager::checkGameOver()
{
	if (game_over)
	{
		if (!is_defeat_screen_on) displayDefeatScreen();
		start_game = false;
		return true;
	}
	return false;
}


bool GameManager::quitGame()
{
	close = true;
	start_game = false;

	return true;
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
			
			startGame();
			title_screen->draw_element = false;

			start_button->draw_element = false;
			start_button->interactive = false;
			start_button->can_focus = false;

			exit_button->draw_element = false;
			exit_button->interactive = false;
			exit_button->can_focus = false;
			
			app->audio->playFx(fx_click, 0);
			break;
		}
	}

	if (ui == exit_button || ui == close_button)
	{
		switch (event)
		{
		case(MOUSE_LCLICK_DOWN) :
			app->audio->playFx(fx_click, 0);
			break;
		case(MOUSE_LCLICK_UP) :
			quitGame();
			break;
		}
	}

	if (ui == retry_button)
	{
		switch (event)
		{
		case(MOUSE_LCLICK_DOWN) :
			//Restart game
			app->audio->playFx(fx_click, 0);
			exit_button->setSection({ 338, 279, 141, 38 });
			break;
		case(MOUSE_LCLICK_UP) :
			exit_button->setSection({ 339, 229, 141, 39 });	
			restartGame();
			game_state = INITIAL_SETUP;
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
	total_waves = 2;
	score = 0;
	enemy_count = 0;
	kill_count = 0;
	score_current_wave = 0;
	total_score = 0;
	
	resources = 0;
	mineral_resources = 0;
	gas_resources = 0;
	total_units_killed_currentFrame = 0;

	won = false;
	close = false;
	start_game = true;
	game_over = false;

	iPoint p = COMMANDCENTERPOSITION;
	app->render->setCameraOnPosition(p);

	defeat_screen->draw_element = false;
	is_defeat_screen_on = false;

	victory_screen->draw_element = false;
	is_victory_screen_on = false;

	retry_button->draw_element = false;
	retry_button->interactive = false;
	retry_button->can_focus = false;

	close_button->draw_element = false;
	close_button->interactive = false;
	close_button->can_focus = false;

	startGame();
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

	retry_button->draw_element = true;
	retry_button->interactive = true;
	retry_button->can_focus = true;
	
	close_button->draw_element = true;
	close_button->interactive = true;
	close_button->can_focus = true;

}

void GameManager::displayDefeatScreen()
{
	defeat_screen->draw_element = true;
	is_defeat_screen_on = true;
	
	retry_button->draw_element = true;
	retry_button->interactive = true;
	retry_button->can_focus = true;

	close_button->draw_element = true;
	close_button->interactive = true;
	close_button->can_focus = true;
}

bool GameManager::isGameStarted() const
{
	return start_game;
}


void GameManager::eraseEnemiesIfKilled()
{
	if (app->entity_manager->current_wave_entities.size() > 0 && wave_state == MIDDLE_WAVE)
	{
		map<uint, Entity*>::iterator it2 = app->entity_manager->current_wave_entities.begin();
		for (; it2 != app->entity_manager->current_wave_entities.end();)
		{
			if (it2->second->to_delete == true)
			{
				AddPointsEnemy(it2->second);
				it2 = app->entity_manager->current_wave_entities.erase(it2);
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