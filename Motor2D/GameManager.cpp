#include "App.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "p2Log.h"
#include <time.h>

//Author: RIE code.

bool GameManager::start()
{
	bool ret = true;

	timeBetweenWaves.start();
	GeneralTime.start();
	LOG("LAST HOPE GAME STARTS!");

	app->entity_manager->createWave(size1);
	
	return ret;
}

bool GameManager::update(float dt)
{
	bool ret = true;
	
	if (currentWaves < 2)
	{
		if (timeBetweenWaves.readSec() >= WaveTime1)//We check how much time do we have left before releasing a new wave
		{
			LOG("Wave time is over! prepare for the next wave!!!");
			
				app->entity_manager->createWave(size1);
				timeBetweenWaves.start();

				if (app->entity_manager->getWaveZerglingSize() <= 0)//Not working yet but will finish it tomorrow.
				{
					addPoints(scoreCurrentWave);
					killCount = 0;
				}
				//timer
				//++unitKillCount;
			
		}
		
		if (app->entity_manager->unitKilled == true)//If a unit is killed, frags are added and points too
		{
			killCount++;
			app->entity_manager->unitKilled = false;
		}

		if (isFinished)
		{
			//Victory Text
			//If all waves are defeated/or waves are infinite (we'll see)

			ret = false;
		}

		else if (gameOver)
		{
				//Display message of game over
				//Display Score
				//End game loop
				GeneralTime.start();
				/*1: Whether the player has died*/
				ret = false;
		}

		
	}
	
	return ret;
}

bool GameManager::postUpdate()
{
	return true;
}


void GameManager::addPoints(uint points)
{
	totalScore += scoreCurrentWave;
}