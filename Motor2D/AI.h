#ifndef __IA_H__
#define __IA_H__

using namespace std;

#include "Module.h"
#include "Timer.h"
/*IA CLASS BASE IMPLEMENTED. ADD STUFF HERE ALEIX*/

class AI : public Module
{
	bool Awake();

	bool preUpdate();

	bool update(float dt);

private:

	float timeItUpdatesIA = 0.12f;
	float timeNextUpdate = 0;
	
};

#endif






