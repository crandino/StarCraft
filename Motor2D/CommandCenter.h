#ifndef __COMMANDCENTER_H__
#define __COMMANDCENTER_H__

#include "Building.h"
#include "GuiLabel.h"

class CommandCenter : public Building
{
public:

	Animation	 idle;

	Particle	 explosion;

	//Command Center Info
	char commandCenter_info[20];

public:

	CommandCenter(iPoint &p);
	~CommandCenter();

	bool update(float dt);
	void draw();
	void setParticleBehaviour();
};

#endif !__COMMANDCENTER_H__