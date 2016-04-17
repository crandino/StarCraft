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
#include "Audio.h"
#include "map.h"

#include "GuiImage.h"

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
	//audio
	fx_click = app->audio->loadFx("Audio/FX/UI/UI_Click.wav");

	//Play Screen
	//----------------------------------------------------------------------
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

	//---------------------------------------------
	
	defeat_img = app->tex->loadTexture("Screens/defeat_screen.png");



	iPoint p = COMMANDCENTERPOSITION;
	app->entity_manager->addEntity(p, COMMANDCENTER);//BASE CREATION

	
	app->entity_manager->addEntity(iPoint({ 1500, 2150 }), MARINE);
	app->entity_manager->addEntity(iPoint({ 1520, 2150 }), MARINE);
	app->entity_manager->addEntity(iPoint({ 1480, 2150 }), MARINE);
	app->entity_manager->addEntity(iPoint({ 1540, 2150 }), MARINE);
	app->entity_manager->addEntity(iPoint({ 1460, 2150 }), MARINE);
	app->entity_manager->addEntity(iPoint({ 1520, 2130 }), MARINE);
	app->entity_manager->addEntity(iPoint({ 1480, 2130 }), MARINE);
	app->entity_manager->addEntity(iPoint({ 1540, 2130 }), MARINE);
	app->entity_manager->addEntity(iPoint({ 1460, 2130 }), MARINE);
	app->entity_manager->addEntity(iPoint({ 1500, 2130 }), MARINE);
	


	return ret;
}

bool GameManager::update(float dt)
{
	bool ret = true;

	if (start_game)
	{

		if (current_waves <= TOTALWAVES)
		{
			
			if (time_between_waves.readSec() >= WAVETIME1)//We check how much time do we have left before releasing a new wave
			{
				if (current_waves == 0)
				{
					LOG("Wave 1 is over get prepared!!!!");

					app->entity_manager->createWave(SIZE1, { 1500, 1500 });

					current_waves++;

				}
			}
			if (time_between_waves.readSec() >= WAVETIME2)//We check how much time do we have left before releasing a new wave
			{
				if (current_waves == 1)
				{

					LOG("Wave 2 is over prepare for the next wave!!");
					app->entity_manager->createWave(SIZE2, { 1500, 1500 });

					current_waves++;

					time_between_waves.start();
				}
				else if (current_waves == 2)
				{

					LOG("Last wave!!!");

					app->entity_manager->createWave(SIZE3, { 1500, 1500 });

					current_waves++;

					time_between_waves.start();
				}
			}
		}

		//EACH TIME A UNIT IS KILLED SCORE IS ADDED UP
		if (total_units_killed_currentFrame > 0)
		{
			kill_count += total_units_killed_currentFrame;
			addPoints(kill_count);
			total_units_killed_currentFrame = 0;

			LOG("Score: %d", total_score);

			if (current_waves == 1 && kill_count >= SIZE1)
			{
				total_kills_game += kill_count;
				kill_count = 0;
				addPoints(kill_count);

				LOG("You successfully wiped the first wave good job! NOW THE NEXT ONE >:]");
				LOG("Total Score: %d", total_score);
			}
			else if (current_waves == 2 && kill_count >= SIZE2)
			{
				total_kills_game += kill_count;
				kill_count = 0;
				addPoints(kill_count);

				LOG("You successfully wiped the second wave good job! NOW THE NEXT ONE >:]");
				LOG("Total Score: %d", total_score);
			}
			else if (current_waves == 3 && kill_count >= SIZE3)
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

		if (current_waves == 4)
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

	
	}
	if (game_over && !start_game)
	{
		if (ending_game.readSec() >= ENDINGTIME)
		{
			if (!is_defeat_screen_on)
				displayDefeatScreen();

			if (close)
				ret = false;
		}
	}

	if (won && !start_game)
	{
		if (winning_game.readSec() >= ENDINGTIME)
		{
			if (!is_defeat_screen_on)
				displayVictoryScreen();

			if (close)
				ret = false;
		}
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
		time_between_waves.start();
}

bool GameManager::checkGameOver()
{
	bool ret = false;

	if (!(ret = game_over))
	{ //game not over
		if (marineCounterDeath == 10)
		{
			ending_game.start();
			start_game = false;
			ret = game_over = true;
		}
	}

	return ret;
}


bool GameManager::quitGame()
{
		close = true;
		start_game = false;

		return false;
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
			start_game = true;
			time_between_waves.start();

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
			restartGame();
			exit_button->setSection({ 338, 279, 141, 38 });
			break;

		case(MOUSE_LCLICK_UP) :
			app->audio->playFx(fx_click, 0);
			exit_button->setSection({ 339, 229, 141, 39 });
			
			game_over = true;
			
			break;
		}
	}

}

void GameManager::restartGame()
{
	current_waves = 0;
	total_waves = 2;
	score = 0;
	enemy_count = 0;
	kill_count = 0;
	game_over = false;
	app->render->start_transition({ 900, 3000 });
	start_game = true;

	defeat_screen->draw_element = false;

	retry_button->draw_element = false;
	retry_button->interactive = false;
	retry_button->can_focus = false;

	close_button->draw_element = false;
	close_button->interactive = false;
	close_button->can_focus = false;
	app->audio->playFx(fx_click, 0);


}

void GameManager::displayVictoryScreen()
{
	
	//Victory Screen
	//----------------------------------------------------------------------

	winning_game.start();

	victory_img = app->tex->loadTexture("Screens/victory screen.png");

	victory_screen = app->gui->createImage(victory_img, { 0, 0, 640, 480 });
	victory_screen->center();
	victory_screen->setLocalPos(victory_screen->getLocalPos().x, victory_screen->getLocalPos().y);

	retry_button = app->gui->createImage(defeat_img, { 121, 170, 105, 28 });
	retry_button->parent = defeat_screen;
	retry_button->setLocalPos(121, 170);
	retry_button->interactive = true;
	retry_button->can_focus = true;
	retry_button->setListener(this);


	close_button = app->gui->createImage(defeat_img, { 121, 213, 105, 28 });
	close_button->parent = defeat_screen;
	close_button->setLocalPos(121, 211);
	close_button->interactive = true;
	close_button->can_focus = true;
	close_button->setListener(this);
	//---------------------------------------------
}

void GameManager::displayDefeatScreen()
{
	is_defeat_screen_on = true;
	//Defeat
	//----------------------------------------------------------------------
	defeat_img = app->tex->loadTexture("Screens/defeat screen.png");

	

	defeat_screen = app->gui->createImage(defeat_img, { 0, 0, 640, 480 });
	defeat_screen->center();
	defeat_screen->setLocalPos(defeat_screen->getLocalPos().x, defeat_screen->getLocalPos().y);

	retry_button = app->gui->createImage(defeat_img, { 121, 170, 105, 28 });
	retry_button->parent = defeat_screen;
	retry_button->setLocalPos(121, 170);
	retry_button->interactive = true;
	retry_button->can_focus = true;
	retry_button->setListener(this);


	close_button = app->gui->createImage(defeat_img, { 121, 213, 105, 28 });
	close_button->parent = defeat_screen;
	close_button->setLocalPos(121, 211);
	close_button->interactive = true;
	close_button->can_focus = true;
	close_button->setListener(this);
	//---------------------------------------------
}


