#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "Entity.h"

class Building : public Entity
{
public:

	bool storage;

	Building() 
	{
		type = BUILDING;
	};

	virtual bool update(float dt)
	{
		switch (state)
		{
		case IDLE:
			break;
		case MOVE:
			break;
		case MOVE_ALERT:
			break;
		case ATTACK:
			break;
		case DYING:
			//current_animation = &dead;
			if (timer_to_check.read() >= time_to_die)
			{
				to_delete = true;
				coll->to_delete = true;
			}
			break;
		case REPAIR:
			break;
		}
		return true;
	}
};


#endif __BUILDING_H__