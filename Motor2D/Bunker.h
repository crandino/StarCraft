#ifndef __BUNKER_H__
#define __BUNKER_H__

#include "Building.h"
#include "Marine.h"
#include "Firebat.h"
#include "JimRaynor.h"

class Bunker : public Building
{
public:

	Animation					idle;
	map<uint, Unit*>			units_inside;
	uint						max_capacity;

	// SFX
	unsigned int fx_attack;
	unsigned int fx_entering;
	unsigned int fx_leaving;

	Bunker() {}
	Bunker(iPoint &p);
	~Bunker();

	bool update(float dt);
	bool getEntityInside(Unit* entity);
	bool getEntitiesOutside();
	bool attack();

};

#endif !__BUNKER_H__