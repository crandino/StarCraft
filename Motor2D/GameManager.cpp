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

	return ret;
}

bool GameManager::update(float dt)
{
	bool ret = true;

	if (start_game)
	{
		if (current_waves <= TOTALWAVES)
		{
			//ADRI
			//Check if we have killed all the zerlings to begin a new wave
			bool all_zerlings_dead = true;
			for (map<uint, Entity*>::iterator it2 = app->entity_manager->active_entities.begin(); it2 != app->entity_manager->active_entities.end(); ++it2)
			{
				if (it2->second->specialization == ZERGLING)
				{
					all_zerlings_dead = false;			
					break;
				}
			}

			if (time_between_waves.readSec() >= WAVETIME1 && all_zerlings_dead) //We check how much time do we have left before releasing a new wave
			{
				if (current_waves == 0)
				{
					LOG("Wave 1 is over get prepared!!!!");

					app->entity_manager->createWave(SIZE1X, SIZE1Y, { 1500, 1500 });
					current_waves++;
					all_zerlings_dead = false;
					resources++;
				}
			}

			if (current_waves == 1 && all_zerlings_dead && resources == 1)
			{   
				//Get Resources
				mineral_resources += 50;
				gas_resources += 50;
				resources ++;
			}

			if (time_between_waves.readSec() >= WAVETIME2 && all_zerlings_dead)//We check how much time do we have left before releasing a new wave
			{
				if (current_waves == 1)
				{

					LOG("Wave 2 is over prepare for the next wave!!");
					app->entity_manager->createWave(SIZE2X,SIZE2Y, { 1500, 1500 });
					current_waves++;
					all_zerlings_dead = false;

					time_between_waves.start();
				}
				else if (current_waves == 2)
				{

					LOG("Last wave!!!");

					app->entity_manager->createWave(SIZE3X,SIZE3Y, { 1500, 1500 });
					current_waves++;
					all_zerlings_dead = false;

					time_between_waves.start();
				}
			}

			if (current_waves == 2 && all_zerlings_dead && resources == 2)
			{
				//Get Resources
				mineral_resources += 75;
				gas_resources += 75;
				resources++;
			}

			if (current_waves == 3 && all_zerlings_dead && resources == 3)
			{
				//Get Resources
				mineral_resources += 75;
				gas_resources += 75;
				resources++;
			}
		}

		//EACH TIME A UNIT IS KILLED SCORE IS ADDED UP
		if (total_units_killed_currentFrame > 0)
		{
			kill_count += total_units_killed_currentFrame;
			addPoints(kill_count);
			total_units_killed_currentFrame = 0;

			LOG("Score: %d", total_score);

			if (current_waves == 1 && kill_count >= (SIZE1X*SIZE1Y))
			{
				total_kills_game += kill_count;
				kill_count = 0;
				addPoints(kill_count);

				LOG("You successfully wiped the first wave good job! NOW THE NEXT ONE >:]");
				LOG("Total Score: %d", total_score);
			}
			else if (current_waves == 2 && kill_count >= SIZE2X*SIZE2Y)
			{
				total_kills_game += kill_count;
				kill_count = 0;
				addPoints(kill_count);

				LOG("You successfully wiped the second wave good job! NOW THE NEXT ONE >:]");
				LOG("Total Score: %d", total_score);
			}
			else if (current_waves == 3 && kill_count >= SIZE3X*SIZE3Y)
			{
				total_kills_game += kill_count;
				kill_count = 0;
				addPoints(kill_count);

				LOG("You successfully wiped the last wave good job!!!!!");
				LOG("Total Score: %d", total_score);
				current_waves = 4;
			}
		}
		//timer
		//++unitKillCount;

		if (current_waves == 3)
		{
			//Victory Text
			//If all waves are defeated/or waves are infinite (we'll see)
			LOG("VICTORY IS OURS!!! CORAL IS SAVED THUS PLANET EARTH :). GOOD FUCKING JOB!");
			displayVictoryScreen();
			won = true;
			start_game = false;
		}

		if (checkGameOver())
		{
			//Display message of game over
			LOG("GAME OVER");
			//Display Score
			LOG("Score: %d", score_current_wave);
		}

		//ADRI
		//-------------------------UI-----------------------------
		//Change the number of WAVE HUD ingame-----------------------
		char n[20];
		sprintf_s(n, 20, "%d", current_waves);
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
		}	

	if (game_over)
	{
		if (!is_defeat_screen_on)
			displayDefeatScreen();
	}

	if (won)
	{
		if (!is_victory_screen_on)
			displayVictoryScreen();
	}

	if (close)
		ret = false;

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
		app->entity_manager->addEntity(p, COMMANDCENTER);//BASE CREATION

		unsigned int size_marines_x = 5;
		unsigned int size_marines_y = 2;

		createInitialMarines(size_marines_x, size_marines_y);
		uint w, h; app->win->getWindowSize(w, h);
		app->render->camera.x = -p.x + (w/2); 
		app->render->camera.y = -p.y + (h/2);
}

bool GameManager::checkGameOver()
{
	if (game_over)
	{ 
		if(!is_defeat_screen_on) displayDefeatScreen();
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
			quitGame();
			app->audio->playFx(fx_click, 0);
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
	
	current_waves = 0;
	total_waves = 2;
	score = 0;
	enemy_count = 0;
	kill_count = 0;
	score_current_wave = 0;
	total_score = 0;

	mineral_resources = 0;
	gas_resources = 0;
	total_units_killed_currentFrame = 0;

	marineCounterDeath = 0;

	won = false;
	close = false;
	start_game = true;
	game_over = false;

	app->render->start_transition({ 900, 3000 });

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

	app->audio->playFx(fx_click, 0);

	startGame();
}

//unsigned int is intended ask me WHY I do it instead of uint.
void GameManager::createInitialMarines(unsigned int sizex, unsigned int sizey)
{

	for (int i = 0; i < sizex; i++)
	{
		for (int j = 0; j < sizey; j++)
		{
			int posx = 1500 + (sizex * i * 10);
			int posy = 2150 + (sizey * j * 10);

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


