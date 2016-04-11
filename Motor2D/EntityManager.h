#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Vector2D.h"
#include "SDL\include\SDL_rect.h"
#include "SDL\include\SDL_render.h"
#include <map>
#include <vector>

enum ENTITY_TYPE
{
	UNIT,
	BUILDING
};

enum FACTION
{
	PLAYER,
	COMPUTER
};

enum SPECIALIZATION
{
	// Units
	MARINE,
	ZERGLING,

	// Buildings
	COMMANDCENTER
};

class Entity;
class Unit;
class Building;
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

	/*---------Methods for attacking other units------------*/
	//Method that Kills entities Used for the kill of zerglings and other units
	void KillEntity(map<uint, Entity*> selection);
	void KillEntity(Entity* e);
	Entity* whichEntityOnMouse();
	map<uint, Entity*>     selection;

	/*---------------Creating Waves-------------------*/
	void createZergling();
	void createWave(uint size/*zergling num, hidralisk....num*/);

public:

	bool unitsKilled = false;

	/* -------- Methods for building -----------------------*/
	void choosePlaceForBuilding();

private:

	map<uint, Entity*>               active_entities;
	vector<Entity*>					   waveZerglings;
	//map<uint, Entity*>                     selection;
	map<uint, Entity*>						ToDelete;
	map<uint, Entity*>					   enemyWave;
	uint next_ID;	

	bool debug = false;

	// CRZ -> Variables to build buildings.
	bool building_mode;
	Building* building_to_place;
	SDL_Texture* building_tile;

	//ROF
	Entity* marine;
	float angle;

	SDL_Rect			 selector;
	bool			selector_init;
	iPoint   initial_selector_pos;
	iPoint     final_selector_pos;

	void	  calculateSelector();

	//Textures
	SDL_Texture* circle_characters;
	SDL_Texture* hp_tex;
	
};

#endif // __EntityManager_H__
