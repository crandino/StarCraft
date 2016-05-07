#ifndef __BOMB_H__
#define __BOMB_H__

//#include "JimRaynor.h"
#include "Building.h"

class Bomb : public Building
{
public:

	Animation					idle;
	bool						isPicked = false;
	
	
	Bomb() {}
	Bomb(iPoint &p);
	~Bomb();

};

#endif !__BOMB_H__