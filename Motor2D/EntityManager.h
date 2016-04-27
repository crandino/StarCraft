#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Vector2D.h"
#include "SDL\include\SDL_rect.h"
#include "SDL\include\SDL_render.h"
#include <map>
#include <vector>

// Some enums to separate behaviour, UI, ...

enum FACTION   // Controlled by player or computer
{
	PLAYER,
	COMPUTER
};

enum ENTITY_TYPE  // First specialization: unit or building
{
	UNIT,
	BUILDING
};

enum SPECIALIZATION  // Second specialization
{
	// Units
	NOTYPE,
	MARINE,
	SCV,
	ZERGLING,


	// Buildings
	COMMANDCENTER, 
	BUNKER,
};

class Entity;
class Unit;
class Building;
class Bunker;
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
	bool update(float dt);

	// Called each loop iteration
	bool postUpdate();

	// Called before quitting
	bool cleanUp();

	Entity* const addEntity(iPoint &pos, SPECIALIZATION type);
	Entity* const addEntity(Entity* e);
	Entity* const createUnit(iPoint &pos, SPECIALIZATION type);
	Entity* getEntity(uint id);
	
	void deleteEntity(map<uint, Entity*> selection);
	void deleteEntityKilled(Entity* e);
	void deleteAllEntities();

	void handleSelection();

	void SetEnemyToAttackCommandCenter(Entity* e);

	/*--------Methods for interact with buildings----------*/
	void GetInsideBunker(Entity* e);	
	void repairBuilding(Entity* e);
	Entity* searchNearestEntityInRange(Entity* e, bool search_in_same_faction = false);


	/*---------Methods for attacking other units------------*/
	//Method that Kills entities Used for the kill of zerglings and other units
	void KillEntity(map<uint, Entity*> selection);
	void KillEntity(Entity* e);
	Entity* whichEntityOnMouse();

	/*---------------Creating Waves-------------------*/
	void createWave(uint sizex, uint sizey, iPoint position = { 250, 250 }/*/*zergling num, hidralisk....num*/);


public:

	/*---Utilities---*/ //Move to Globals when we have more time so it can be used by other modules
	iPoint EntityManager::changeSign(iPoint point);

	void recalculatePaths();

public:
	//Frag count
	bool enemyJustDied = false;

	//GUI
	bool create_bunker = false;
	bool create_SCV = false;

	/* -------- Methods for building -----------------------*/
	void choosePlaceForBuilding();

public:
	map<uint, Entity*>                  selection; 
	map<uint, Entity*>					active_entities;
	map<uint, Entity*>					current_wave_entities;
private:


	map<uint, Entity*>					to_delete;
	uint								next_ID;	

	bool debug = false;

	// CRZ -> Variables to build buildings.
	bool			building_mode;
	Building*		building_to_place;
	SDL_Texture*	building_tile;

	SDL_Rect		selector;
	bool			selector_init;
	iPoint			initial_selector_pos;
	iPoint			final_selector_pos;

	void			calculateSelector();
	void			onCollision(Collider* c1, Collider* c2);	
	
};

#endif // __EntityManager_H__
