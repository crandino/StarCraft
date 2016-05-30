#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "Entity.h"
#include "queue"

#define INFO_STRING_LENTGH 256

class Building : public Entity
{
public:

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