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

#include "GuiImage.h"

//Author: RIE code.

//Number to change the number of waves
#define TOTALWAVES 2
#define WAVETIME1 5//120 = 2 minutes per wave in the future or some other game designish number
#define WAVETIME2 10
#define	SIZE1 1 // Changes number of zerglings per wave
#define TOTALUNITSALLWAVES SIZE1*TOTALWAVES
#define ZERGLINGSCORE 20


bool GameManager::start()
{
	bool ret = true;

	LOG("LAST HOPE GAME STARTS!");
	
	//Play Screen
	start_image = app->tex->loadTexture("Screens/Start_Image.png");

	title_screen = app->gui->createImage(start_image, { 0, 0, 296, 336 });
	title_screen->center();
	title_screen->setLocalPos(title_screen->getLocalPos().x - 5, title_screen->getLocalPos().y - 50);

	start_button = app->gui->createImage(start_image, { 296, 0, 141, 39 });
	start_button->parent = title_screen;
	start_button->setLocalPos(75, 164);
	start_button->interactive = true;
	start_button->can_focus = true;
	start_button->setListener(this);
	

	exit_button = app->gui->createImage(start_image, { 296, 0, 141, 39 });
	exit_button->parent = title_screen;
	exit_button->setLocalPos(75, 228);
	exit_button->interactive = true;
	exit_button->can_focus = true;
	exit_button->setListener(this);
	

	return ret;
}

bool GameManager::update(float dt)
{
	bool ret = true;

	if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		start_game = true;
		time_between_waves.start();
	}


	if (start_game)
	{

		if (current_waves <= TOTALWAVES)
		{
			if (time_between_waves.readSec() >= WAVETIME1)//We check how much time do we have left before releasing a new wave
			{
				LOG("Wave time is over! prepare for the next wave!!!");

				app->entity_manager->createWave(SIZE1, { 1500, 500 });
				
				current_waves++;
			}


			//EACH TIME A UNIT IS KILLED SCORE IS ADDED UP
			if (total_units_killed_currentFrame > 0)
			{
				kill_count += total_units_killed_currentFrame;
				addPoints(kill_count);
				total_units_killed_currentFrame = 0;

				LOG("Score: %d", total_score);

				if (kill_count >= SIZE1)
				{
					total_kills_game += kill_count;
					kill_count = 0;
					addPoints(kill_count);

					LOG("You successfully wiped a wave good job! NOW THE NEXT ONE >:]");
					LOG("Total Score: %d", total_score);
				}
			}
			//timer
			//++unitKillCount;

			if (total_kills_game == TOTALUNITSALLWAVES)
			{
				//Victory Text
				//If all waves are defeated/or waves are infinite (we'll see)
				LOG("VICTORY IS OURS!!! CORAL IS SAVED THUS PLANET EARTH :). GOOD FUCKING JOB!");

				ret = false;
			}

			if (game_over)
			{
				//Display message of game over
				LOG("GAME OVER");
				//Display Score
				LOG("Score: %d", score_current_wave);
				//End game loop
				general_time.start();
				/*1: Whether the player has died*/

				start_game = false;
				
				ret = false;
				
			}
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

	return ret;
}

void GameManager::startGame()
{
		start_game = true;
		time_between_waves.start();
}

bool GameManager::quitGame()
{
		game_over = true;
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
			start_game = true;
			title_screen->draw_element = false;
			start_button->draw_element = false;
			exit_button->draw_element = false;
			break;
		}
	}

	if (ui == exit_button)
	{
		switch (event)
		{
		case(MOUSE_LCLICK_DOWN) :
			game_over = true;
			break;
		}
	}
}