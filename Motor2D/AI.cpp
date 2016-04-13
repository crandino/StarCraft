#include "AI.h"
#include "EntityManager.h"



bool AI::Awake()
{
	return true;

}


bool AI::preUpdate()
{
	return true;
}


bool AI::update(float dt)
{
	if (timeNextUpdate >= timeItUpdatesIA)
	{
		timeNextUpdate = 0;
	}

	timeNextUpdate += dt;

	return true;
}