#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "Entity.h"

class Building : public Entity
{
public:

	uint capacity;
	bool storage;
	SPECIALIZATION  building_type;

	Building() 
	{
		type = BUILDING;
	};
};


#endif __BUILDING_H__