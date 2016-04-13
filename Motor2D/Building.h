#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "Entity.h"

class Building : public Entity
{
public:

	uint capacity;
	bool storage;

	Building() 
	{
		type = BUILDING;
		capacity = 0;
		storage = false;
	};
};


#endif __BUILDING_H__