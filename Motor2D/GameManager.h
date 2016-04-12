#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "Module.h"
#include "Timer.h"


using namespace std;

//Class that manages the game. The win lose cycle, the points earned, the resources, waves etc..

/*
Place a timer, entity manager communicate zerg list/map etc..
*/
class GameManager : public Module
{
public:
	int currentWaves = 0;
	int totalWaves = 2;
	int score = 0;
	int enemyCount = 0;
	uint killCount;
	bool isFinished = false;
	bool gameOver = false;

	/*---- Wave Creation ----*/
	int center;
	int radiusSpawnOffset = 30;


public:

	GameManager()
	{
		
	}


	bool Victory = false;

	void addPoints(uint points);

	bool start();

	bool update(float dt);
	
	bool postUpdate();

//Time Management
public:
	Timer GeneralTime;
	Timer timeBetweenWaves;
	Timer RandomGenerator;
	uint scoreCurrentWave;
	uint totalScore = 0;
	uint32 WaveTime1 = 30000;//120.000 = 2 minutes per wave in the future or some other game designish number
	uint size1 = 5;
};

#endif