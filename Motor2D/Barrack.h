#ifndef __BARRACK_H__
#define __BARRACK_H__

#include "Building.h"

class Barrack : public Building
{
public:

	Animation	idle;

	Particle	explosion;

	//Barrack Info
	char barrack_info[INFO_STRING_LENTGH];

public:

	Barrack(iPoint &p);
	~Barrack();

	bool update(float dt);
	void draw();
	void setParticleBehaviour();
};

#endif !__BARRACK_H__