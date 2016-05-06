#ifndef __BUNKER_H__
#define __BUNKER_H__

#include "Building.h"
#include "Marine.h"
#include "Firebat.h"

class Bunker : public Building
{
public:

	Animation					idle;
	map<uint, Unit*>			units_inside;
	uint						max_capacity;
	float						damage_increase_ratio;

	// SFX
	unsigned int fx_attack;
	unsigned int fx_entering;
	unsigned int fx_leaving;

	Bunker(iPoint &p);
	~Bunker();
	bool update(float dt);
	bool getEntityInside(Unit* entity);
	bool getEntitiesOutside();
	bool attack();

};

#endif !__BUNKER_H__