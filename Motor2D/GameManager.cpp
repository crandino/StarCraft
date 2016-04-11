#include "App.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "p2Log.h"


bool GameManager::start()
{
	bool ret = true;

	timeBetweenWaves.start();
	GeneralTime.start();
	LOG("LAST HOPE GAME STARTS!");

	app->entity_manager->createWave(size1/*zergling, hidralisk*/);
	
	return ret;
}

bool GameManager::update(float dt)
{
	bool ret = true;
	
	if (currentWaves < 2)//Before all waves finish the game isn't finished or the player dies.
	{
		if (timeBetweenWaves.readSec() > WaveTime1)//We check how much time do we have left before releasing a new wave
		{
			LOG("Wave time is over! prepare for the next wave!!!");
			if (app->entity_manager->unitsKilled == true)//
			{
				killCount++;

				
				
				if (app->entity_manager->getWaveZerglingSize() < 0)
				{
					addPoints(scoreCurrentWave);
					killCount = 0;
					timeBetweenWaves.start();
				}
				//timer
				//++unitKillCount;
			}

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