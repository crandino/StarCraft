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
class JimRaynor;

class Zergling;
class Hydralisk;
class Mutalisk;
class Ultralisk;

class CommandCenter;
class Barrack;
class Bunker;
class Factory;

class Bomb;

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
	ULTRALISK,
	TANK,
	FIREBAT,
	JIM_RAYNOR,
	// Buildings
	COMMANDCENTER, 
	BUNKER,
	BARRACK,
	FACTORY,
	BOMB,
	BLUE,
	YELLOW,
	RED,
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

	Entity* const addEntity(iPoint &pos, SPECIALIZATION type, bool direct_creation = true);
	Entity* getEntity(uint id);
	
	void				SetEnemyToAttackCommandCenter(Entity* e);
	Entity*				searchNearestEntityInRange(Entity* e, bool search_only_in_same_faction = false, float range = -1.0f);
	list<Entity*>		searchEntitiesInRange(Entity* e, bool search_only_in_same_faction = false, float range = -1.0f, bool can_attack_to_flying = true);
	bool				checkFocus(Unit* e);
	Entity*				searchEnemyToAttack(Entity* e, bool can_attack_to_flying = true);
	Entity*				searchAllyToHeal(Entity* e, bool search_only_buildings = false);

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
	bool	create_marine = false;
	bool	create_firebat = false;
	bool	create_medic = false;
	bool	create_tank = false;
	bool    create_barrack = false;
	bool    create_factory = false;

	bool	set_bomb = false;

	bool	create_blue = false;
	bool	create_yellow = false;
	bool	create_red = false;

	bool	selector_init;

	//Sounds (FX)

	//Marine
	unsigned int fx_marine_attack;
	unsigned int fx_marine_death_1;
	unsigned int fx_marine_death_2;

	unsigned int fx_marine_acknowledgement_1;
	unsigned int fx_marine_acknowledgement_2;
	unsigned int fx_marine_acknowledgement_3;
	unsigned int fx_marine_acknowledgement_4;

	unsigned int fx_marine_affirmation_1;
	unsigned int fx_marine_affirmation_2;
	unsigned int fx_marine_affirmation_3;
	unsigned int fx_marine_affirmation_4;

	unsigned int fx_marine_annoyance_1;
	unsigned int fx_marine_annoyance_2;
	unsigned int fx_marine_annoyance_3;
	unsigned int fx_marine_annoyance_4;
	unsigned int fx_marine_annoyance_5;
	unsigned int fx_marine_annoyance_6;
	unsigned int fx_marine_annoyance_7;

	unsigned int fx_marine_ready;

	//Firebat
	unsigned int fx_firebat_attack_1;
	unsigned int fx_firebat_attack_2;
	unsigned int fx_firebat_death_1;
	unsigned int fx_firebat_death_2;
	unsigned int fx_firebat_death_3;

	unsigned int fx_firebat_acknowledgement_1;
	unsigned int fx_firebat_acknowledgement_2;
	unsigned int fx_firebat_acknowledgement_3;
	unsigned int fx_firebat_acknowledgement_4;

	unsigned int fx_firebat_affirmation_1;
	unsigned int fx_firebat_affirmation_2;
	unsigned int fx_firebat_affirmation_3;
	unsigned int fx_firebat_affirmation_4;

	unsigned int fx_firebat_annoyance_1;
	unsigned int fx_firebat_annoyance_2;
	unsigned int fx_firebat_annoyance_3;
	unsigned int fx_firebat_annoyance_4;
	unsigned int fx_firebat_annoyance_5;
	unsigned int fx_firebat_annoyance_6;
	unsigned int fx_firebat_annoyance_7;

	unsigned int fx_firebat_ready;

	//Medic
	unsigned int fx_medic_heal;
	unsigned int fx_medic_death;

	unsigned int fx_medic_acknowledgement_1;
	unsigned int fx_medic_acknowledgement_2;
	unsigned int fx_medic_acknowledgement_3;
	unsigned int fx_medic_acknowledgement_4;

	unsigned int fx_medic_affirmation_1;
	unsigned int fx_medic_affirmation_2;
	unsigned int fx_medic_affirmation_3;
	unsigned int fx_medic_affirmation_4;

	unsigned int fx_medic_annoyance_1;
	unsigned int fx_medic_annoyance_2;
	unsigned int fx_medic_annoyance_3;
	unsigned int fx_medic_annoyance_4;
	unsigned int fx_medic_annoyance_5;
	unsigned int fx_medic_annoyance_6;
	unsigned int fx_medic_annoyance_7;

	unsigned int fx_medic_ready;

	//SiegeTank
	unsigned int fx_tank_sige_mode_on;
	unsigned int fx_tank_sige_mode_off;

	unsigned int fx_tank_death;

	unsigned int fx_tank_missile_none_siege;
	unsigned int fx_tank_missile_siege;

	unsigned int fx_tank_acknowledgement_1;
	unsigned int fx_tank_acknowledgement_2;
	unsigned int fx_tank_acknowledgement_3;
	unsigned int fx_tank_acknowledgement_4;

	unsigned int fx_tank_affirmation_1;
	unsigned int fx_tank_affirmation_2;
	unsigned int fx_tank_affirmation_3;
	unsigned int fx_tank_affirmation_4;

	unsigned int fx_tank_annoyance_1;
	unsigned int fx_tank_annoyance_2;
	unsigned int fx_tank_annoyance_3;
	unsigned int fx_tank_annoyance_4;

	unsigned int fx_tank_ready;


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
	JimRaynor		*Jim_Raynor;

	Zergling		*zergling;
	Mutalisk		*mutalisk;
	Hydralisk		*hydralisk;
	Ultralisk       *ultralisk;

	// Buildings
	CommandCenter	*command_center;
	Bunker			*bunker;
	Barrack         *barrack;
	Factory         *factory;

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

	//Sounds
	bool loadEntityFX();

	void			entityManualCreation();
	void			handleSelection();
	
	//FOG_OF_WAR
	void            updateFogOfWar();
};

#endif // __EntityManager_H__
