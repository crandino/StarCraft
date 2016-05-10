#ifndef __BARRACK_H__
#define __BARRACK_H__

#include "Building.h"

class Barrack : public Building
{
public:

	Animation idle;

	//Barrack Info
	char barrack_info[20];

public:

	Barrack(iPoint &p);
	~Barrack();

	bool update(float dt);
	void draw();
};

#endif !__BARRACK_H__