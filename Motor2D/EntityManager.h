#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Vector2D.h"
#include "SDL\include\SDL_rect.h"
#include "SDL\include\SDL_render.h"
#include <map>
#include <vector>
#include <list>

class Marine;
class Scv;
class Medic;
class Firebat;
class Tank;

class Zergling;
class Hydralisk;
class Mutalisk;

class CommandCenter;
class Barrack;
class Bunker;

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
	MEDIC,
	ZERGLING,
	MUTALISK,
	HYDRALISK,
	TANK,
	FIREBAT,
	// Buildings
	COMMANDCENTER, 
	BUNKER,
	BARRACK,
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
	Entity* getEntity(uint id);
	
	void	SetEnemyToAttackCommandCenter(Entity* e);
	Entity* searchNearestEntityInRange(Entity* e, bool search_only_in_same_faction = false, float range = -1.0f);
	list<Entity*> searchEntitiesInRange(Entity* e, bool search_only_in_same_faction = false, float range = -1.0f);
	Entity* searchEnemyToAttack(Entity* e);
	Entity* searchAllyToHeal(Entity* e);

	Entity* whichEntityOnMouse();

public:

	/*---Utilities---*/ //Move to Globals when we have more time so it can be used by other modules
	iPoint EntityManager::changeSign(iPoint point);

	void recalculatePaths(const SDL_Rect &rect, bool walkable);//recalculate the paths and move out entities inside the rect
	

public:
	map<uint, Entity*>                  selection; 
	map<uint, Entity*>					active_entities;

	//GUI
	bool	create_bunker = false;
	bool	create_SCV = false;
	bool	selector_init;

	/* -------- Methods for building -----------------------*/
	void choosePlaceForBuilding();

private:
	uint			 next_ID;
	list<Entity*>    list_of_entity_classes;   // Useful to call all start for each entity class.

	// Units
	Marine			*marine;
	Scv				*scv;
	Medic			*medic;
	Firebat			*firebat;
	Tank            *tank;

	Zergling		*zergling;
	Mutalisk		*mutalisk;
	Hydralisk		*hydralisk;

	// Buildings
	CommandCenter	*command_center;
	Bunker			*bunker;
	Barrack         *barrack;

	bool debug = false;

	// CRZ -> Variables to build buildings.
	bool			building_mode;
	Building*		building_to_place;
	SDL_Texture*	building_tile;

	SDL_Rect		selector;

	iPoint			initial_selector_pos;
	iPoint			final_selector_pos;

	void			calculateSelector();
	void			onCollision(Collider* c1, Collider* c2);	

	void			entityManualCreation();
	void			handleSelection();
	
	//FOG_OF_WAR
	void updateFogOfWar();
};

#endif // __EntityManager_H__
