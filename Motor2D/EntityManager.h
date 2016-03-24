#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Point2d.h"
#include "SDL\include\SDL_rect.h"
#include <map>
#include <vector>

class ENTITY_TYPE;
class UNITS;
enum FACTION;
class BUILDING_TYPE;
class UNIT_TYPE;

class Entity;
using namespace std;

class EntityManager : public Module
{

public:

	EntityManager();

	// Destructor
	virtual ~EntityManager();

	// Called before render is available
	bool awake(pugi::xml_node&);

	// Called before the first frame
	bool start();

	// Called each loop iteration
	bool preUpdate();

	// Called each loop iteration
	bool postUpdate();

	// Called before quitting
	bool cleanUp();

	Entity *add(iPoint &pos, ENTITY_TYPE type);
	bool remove(uint id);
	Entity* getEntity(uint id);

	Entity *whichEntityOnMouse();

private:

	map<uint, Entity*>               active_entities;
	map<uint, Entity*>             inactive_entities;
	map<uint, Entity*>                     selection;
	multimap<float, Entity*>       selection_ordered;
	uint next_ID;
	uchar filter;

	SDL_Rect			 selector;
	bool			selector_init;
	iPoint   initial_selector_pos;
	iPoint     final_selector_pos;

	void drawAll();
	void selectAll(uchar filter);
	void selectAvailableEntities(uchar filter);
	void calculateSelector();
	void sortEntities();

};

#endif // __EntityManager_H__
