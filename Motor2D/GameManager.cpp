#include "App.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "p2Log.h"
#include <time.h>

//Author: RIE code.

//Number to change the number of waves
#define TOTALWAVES 2
#define TOTALUNITSALLWAVES SIZE1*TOTALWAVES
#define WAVETIME1 5//120 = 2 minutes per wave in the future or some other game designish number
#define WAVETIME2 10
#define	SIZE1 1 // Changes number of zerglings per wave
#define ZERGLINGSCORE 20


bool GameManager::start()
{
	bool ret = true;

	timeBetweenWaves.start();
	GeneralTime.start();
	LOG("LAST HOPE GAME STARTS!");

	//app->entity_manager->createWave(size1);//First wave that is created
	
	return ret;
}

bool GameManager::update(float dt)
{
	bool ret = true;
	
	if (currentWaves <= TOTALWAVES)
	{
		if (timeBetweenWaves.readSec() >= WAVETIME1)//We check how much time do we have left before releasing a new wave
		{
			LOG("Wave time is over! prepare for the next wave!!!");
			
				app->entity_manager->createWave(SIZE1);
				timeBetweenWaves.start();
				currentWaves++;
		}
		

		//EACH TIME A UNIT IS KILLED SCORE IS ADDED UP
		if (totalUnitsKilledCurrentFrame > 0)
		{
			killCount += totalUnitsKilledCurrentFrame;
			addPoints(killCount);
			totalUnitsKilledCurrentFrame = 0;

			LOG("Score: %d", totalScore);
			
			if (killCount >= SIZE1)
			{
				totalKillsGame += killCount;
				killCount = 0;
				addPoints(killCount);

				LOG("You successfully wiped a wave good job! NOW THE NEXT ONE >:]");
				LOG("Total Score: %d", totalScore);
			}
		}
		//timer
		//++unitKillCount;
	
		if (totalKillsGame == TOTALUNITSALLWAVES)
		{
			//Victory Text
			//If all waves are defeated/or waves are infinite (we'll see)
			LOG("VICTORY IS OURS!!! CORAL IS SAVED THUS PLANET EARTH :). GOOD FUCKING JOB!");

			ret = false;
		}

		else if (gameOver)
		{
				//Display message of game over
				LOG("GAME OVER");
				//Display Score
				LOG("Score: %d", scoreCurrentWave);
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


void GameManager::addPoints(uint totalUnitsKilledCurrentFrame)
{
	totalScore += ZERGLINGSCORE * totalUnitsKilledCurrentFrame;
}