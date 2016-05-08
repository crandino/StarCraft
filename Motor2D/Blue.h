#ifndef __BLUE_H__
#define __BLUE_H__

#include "Building.h"

class Blue : public Building
{
public:

	Animation					idle;
	list<Entity*>				targets;

	Blue() {}
	Blue(iPoint &p);
	~Blue();

	bool update(float dt);
	void buff();
};

#endif !__BLUE_H__