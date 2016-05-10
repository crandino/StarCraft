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
	
	//Particles Bunker
	Particle	attack_up;
	Particle	attack_right_up;
	Particle	attack_right;
	Particle	attack_right_down;
	Particle	attack_down;
	Particle	attack_left_down;
	Particle	attack_left;
	Particle	attack_left_up;

	Particle	explosion;

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

	void checkDirection();
	void resetParticle();
	void setParticleBehaviour();

	bool raynor_inside = false;

	//Bunker Info
	char bunker_info[16];

};

#endif !__BUNKER_H__