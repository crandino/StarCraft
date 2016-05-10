#ifndef __COMMANDCENTER_H__
#define __COMMANDCENTER_H__

#include "Building.h"
#include "GuiLabel.h"

class CommandCenter : public Building
{
public:

	Animation idle;

	//Command Center Info
	char commandCenter_info[20];

public:

	CommandCenter(iPoint &p);
	~CommandCenter();

	bool update(float dt);
	void draw();
};

#endif !__COMMANDCENTER_H__