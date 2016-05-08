#ifndef __RED_H__
#define __RED_H__

#include "Building.h"

class Red : public Building
{
public:

	Animation					idle;
	list<Entity*>				targets;

	Red() {}
	Red(iPoint &p);
	~Red();

	bool update(float dt);
	void buff();
};

#endif !__RED_H__