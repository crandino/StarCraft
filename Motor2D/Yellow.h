#ifndef __YELLOW_H__
#define __YELLOW_H__

#include "Building.h"

class Yellow : public Building
{
public:

	Animation					idle;
	list<Entity*>				targets;

	Yellow() {}
	Yellow(iPoint &p);
	~Yellow();

	bool update(float dt);
	void buff();
};

#endif !__YELLOW_H__