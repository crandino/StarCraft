#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Vector2D.h"
#include "SDL\include\SDL_rect.h"
#include "SDL\include\SDL_render.h"
//#include "Window.h"
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

enum UNIT_DIRECTION
{
	UP,
	RIGHT_UP_22,
	RIGHT_UP,
	RIGHT_UP_66,
	RIGHT,
	RIGHT_DOWN_112,
	RIGHT_DOWN,
	RIGHT_DOWN_157,
	DOWN,
	LEFT_DOWN_202,
	LEFT_DOWN,
	LEFT_DOWN_247,
	LEFT,
	LEFT_UP_292,
	LEFT_UP,
	LEFT_UP_337
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
	Entity* const addInEnemyContainer(Entity* e);
	Entity* getEntity(uint id);
	
	void deleteEntity(map<uint, Entity*> selection);
	void deleteEntityKilled(Entity* e);
	void deleteAllEntities();
	uint getWaveZerglingSize();

	void AddEntityToWave(uint n, Entity* e);
	/*--------Methods for interact with buildings----------*/
	void GetInsideBunker(Bunker* e);	
	void repairBuilding(Entity* e);
	bool searchNearEntity(Entity* e);


	/*---------Methods for attacking other units------------*/
	//Method that Kills entities Used for the kill of zerglings and other units
	void KillEntity(map<uint, Entity*> selection);
	void KillEntity(Entity* e);
	Entity* whichEntityOnMouse();

	/*---------------Creating Waves-------------------*/
	void createZergling(iPoint position, iPoint radius);
	void createWave(uint size, iPoint position = { 250, 250 }/*/*zergling num, hidralisk....num*/);

public:

	/*---Utilities---*/ //Move to Globals when we have more time so it can be used by other modules
	iPoint EntityManager::changeSign(iPoint point);

	void logicChanged();

public:
	//Frag count
	bool enemyJustDied = false;

	//GUI
	bool create_bunker = false;
	bool create_SCV = false;



	/* -------- Methods for building -----------------------*/
	void choosePlaceForBuilding();

public:
	map<uint, Entity*>					waveZerglings;
	map<uint, Entity*>                  selection; 
	map<uint, Entity*>					active_entities;

private:


	map<uint, Entity*>					to_delete;
	map<uint, Entity*>					enemyWave;
	uint								next_ID;	

	bool debug = false;

	// CRZ -> Variables to build buildings.
	bool			building_mode;
	Building*		building_to_place;
	SDL_Texture*	building_tile;

	//ROF
	Entity* marine;
	float	angle;

	SDL_Rect		selector;
	bool			selector_init;
	iPoint			initial_selector_pos;
	iPoint			final_selector_pos;

	void			calculateSelector();

	//Textures
	SDL_Texture* hp_tex;

	
	
};

#endif // __EntityManager_H__
