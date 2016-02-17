#ifndef __LEVELMANAGER_H__
#define __LEVELMANAGER_H__

#include "Module.h"

struct LevelData
{
	uint fire_ratio, ice_ratio, grass_ratio;
};

class LevelManager : public Module
{
private:

	uint num_of_levels;

public:

	LevelManager();

	// Destructor
	virtual ~LevelManager();

	// Called before render is available
	bool awake(pugi::xml_node&);

	// Called each loop iteration
	bool preUpdate();
	bool update(float dt);
	bool postUpdate();

	// Called before quitting
	bool cleanUp();


	// Utils
	const LevelData *load_level(uint number_level);
};

#endif // __LEVELMANAGER_H__
