#ifndef __IA_H__
#define __IA_H__

using namespace std;

#include "Module.h"
#include "Timer.h"
/*IA CLASS BASE IMPLEMENTED.*/

#define RANGE_ZERGLING_ATTACK 11

//Author: RIE
enum IA_STATES
{
	IDLE = 0,
	ATTACK = 1,
	FLEEING = 2
};



class AI : public Module
{
public:
	AI();
	
	bool Awake();

	bool start();

	bool preUpdate();

	bool update(float dt);

	void checkForClosestPlayerUnit();

	void checkForClosestPlayerBuilding();

private:

	float timeUpdatesIA = 0.12f;
	float timeNextUpdate = 0;

	map<uint, Entity*> zergArmyWave;

};

#endif






