#ifndef __BOMB_H__
#define __BOMB_H__

#include "Building.h"

class Bomb : public Building
{
public:

	Animation					idle;
	bool						isPicked = false;
	
	Bomb(iPoint &p);
	~Bomb();

	void draw();

};

#endif !__BOMB_H__