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

	//virtual bool update(float dt)
	//{
	//	switch (state)
	//	{
	//	case IDLE:
	//		//AleixBV Research
	//		if (queue.size() > 0 && creation_timer.readSec() >= queue.front()->time_to_create)
	//		{
	//			Entity *e = queue.front();
	//			app->entity_manager->addEntity(e);
	//			queue.pop();
	//			creation_timer.start();
	//		}
	//		break;
	//	case MOVE:
	//		break;
	//	case MOVE_ALERT:
	//		break;
	//	case ATTACK:
	//		break;
	//	case DYING:
	//		//current_animation = &dead;
	//		if (timer_to_check.read() >= time_to_die)
	//		{
	//			to_delete = true;
	//			coll->to_delete = true;
	//		}
	//		break;
	//	}
	//	return true;
	//}
};


#endif __BUILDING_H__