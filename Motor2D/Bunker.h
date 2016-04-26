#ifndef __BUNKER_H__
#define __BUNKER_H__

#include "Building.h"
#include "Marine.h"

class Bunker : public Building
{
public:

	Animation					idle;
	map<uint, Entity*>			units_inside;
	uint						max_capacity;

	// SFX
	unsigned int bunker_attack_fx;

	Bunker(iPoint &p);
	bool update(float dt);
	bool getEntityInside(Entity* entity);

};

#endif !__BUNKER_H__