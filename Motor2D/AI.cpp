#include "AI.h"
#include "EntityManager.h"
#include "App.h"
#include "Entity.h"

AI::AI() :Module()
{
	name.assign("AI");
}


bool AI::Awake()
{
	return true;
}


bool AI::preUpdate()
{
	return true;
}

bool AI::start()
{
	zergArmyWave = app->entity_manager->waveZerglings;
}

void AI::checkForClosestPlayerUnit()
{
	map<uint, Entity*>::iterator it = zergArmyWave.begin();
	
	it->second->pos.distanceTo();
}

void AI::checkForClosestPlayerBuilding()
{

}

bool AI::update(float dt)
{
	if (timeNextUpdate >= timeUpdatesIA)
	{
		checkForClosestPlayerUnit();
		checkForClosestPlayerBuilding();
		
		timeNextUpdate = 0;
	}

	timeNextUpdate += dt;

	return true;
}