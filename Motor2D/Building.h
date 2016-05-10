#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "Entity.h"
#include "queue"

class Building : public Entity
{
public:

	queue<Entity*>		queue;
	Timer				creation_timer;
	float			    time_to_create;

	Building() 
	{
		type = BUILDING;
	};

	virtual ~Building()
	{
		SDL_DestroyTexture(tex);
	}
};


#endif __BUILDING_H__