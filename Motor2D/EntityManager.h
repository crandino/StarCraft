#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Point2d.h"
#include "Vector2D.h"
#include "SDL\include\SDL_rect.h"
#include "Entity.h"
#include <map>
#include <vector>

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

	Entity* const addEntity(iPoint &pos, ENTITY_TYPE type);
	bool remove(uint id);
	Entity* getEntity(uint id);
	Entity* whichEntityOnMouse();

private:

	map<uint, Entity*>               active_entities;
	map<uint, Entity*>             inactive_entities;
	map<uint, Entity*>                     selection;
	multimap<float, Entity*>       selection_ordered;
	uint next_ID;
	uchar filter;

	//ROF
	Entity* marine;
	float angle;

	SDL_Rect			 selector;
	bool			selector_init;
	iPoint   initial_selector_pos;
	iPoint     final_selector_pos;

	void drawAll();
	void selectAll(uchar filter);
	void selectAvailableEntities(uchar filter);
	void calculateSelector();
	void sortEntities();

	//Textures
	SDL_Texture* circle_characters;

	//TEST
	iPoint tile_start_path;
	bool start_path;
	//------------------
};

#endif // __EntityManager_H__
