#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "Building.h"

class Factory : public Building
{
public:

	Animation idle;

	//Factory Info
	char factory_info[20];

public:

	Factory(iPoint &p);
	~Factory();

	bool update(float dt);
	void draw();
};

#endif !__FACTORY_H__