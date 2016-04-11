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

	bool isFinished = false;
	bool gameOver = false;
public:

	GameManager()
	{
		
	}


	bool Victory = false;


	bool start();

	bool update();
	
	bool postUpdate();

//Time Management
public:
	Timer timeBetweenWaves;

};

#endif