#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "Module.h"

using namespace std;

//Class that manages the game. The win lose cycle, the points earned, the resources, waves etc..
class GameManager : public Module
{
public:

	GameManager()
	{
		
	}


	bool Victory = false;

	bool awake(pugi::xml_node&);
	
	// Called before quitting
	bool cleanUp();


private:


};

#endif