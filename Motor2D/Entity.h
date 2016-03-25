#include "SDL\include\SDL_render.h"
#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"

//I worked some today. I will use classes because I can't use inheritance in enums. This will do the trick

class Entity
{

public:

	SDL_Rect		dim;
	int				type;
	SDL_Texture		*tex;
	uint			ID;
	iPoint			tile_pos;

	uchar			behaviour;
	/* Behaviour is being as follow:
	1 -> The entity is completely neutral. Don't attack.
	2 -> The entity attack to any other 1, 2 and above.
	3 -> Entities controled by player.
	4 -> Entities controled by computer;	
	*/

	// Constructors
	Entity(const iPoint &p, uint ID, int type)
	{
		iPoint tmp = app->map->worldToMap(app->map->data.front(), p.x, p.y);
		tile_pos = tmp;
		tmp = app->map->mapToWorld(app->map->data.front(), tmp.x, tmp.y);
		dim.x = tmp.x;
		dim.y = tmp.y;
		this->ID = ID;
		this->type = type;
	};
	// Destructor
	~Entity()
	{
		SDL_DestroyTexture(tex);
	}

	void draw()
	{
		app->render->blit(tex, dim.x, dim.y);
	}

};

//BASE CLASS: ENUM INHERITANCE
class ENTITY_TYPE 
{
public:
	static const int UNIT = 1;
	static const int BUILDING = 2;
	static const int ITEM = 3;
};

//CHILDS CLASS (TIER 1): ENUM INHERITANCE FIRST LEVEL
class UNIT_TYPE : public ENTITY_TYPE
{
public:
	static const int GROUND_UNIT = 11;
	static const int AERIAL_UNIT = 12;
};

class BUILDING_TYPE : public ENTITY_TYPE
{
public:
	static const int FLYING = 13;
	static const int UNIT_PRODUCER = 14;
	static const int BUFF_UPGRAING = 15;
	static const int OTHER_BUILDING = 16;
};

class ITEM_TYPE : public ENTITY_TYPE
{
public:
	static const int BOMB = 17;
	static const int MINERAL = 18;
	static const int GAS = 19;
};


//GRANDCHILDREN CLASS (TIER 2): ENUM INHERITANCE SECOND LEVEL
class GROUND_UNIT_TYPE : public UNIT_TYPE
{
public:
	static const int MARINE = 21;
	static const int ZERGLING = 22;
};


enum FACTION
{
		TERRAN = 0,
		ZERG = 1
};


class Unit : public Entity
{
public:
	int utype;
	FACTION faction;
public:

	Unit(iPoint &p, uint id, FACTION faction, int utype = 11) : Entity(p, id, 0)
	{
		tex; //Sprites/Animations etc..
		SDL_QueryTexture(tex, NULL, NULL, &dim.w, &dim.h);
		behaviour = 2;
		this->faction = faction;
		this->utype = utype;
	}

};

class Marine : public Unit
{
public:
	int utype;
	FACTION faction;
	SDL_Rect coordSpriteSheet;
public:

	Marine(iPoint &p, uint id, FACTION faction, int utype = 11) : Unit(p, id, faction)
	{
		tex = app->tex->loadTexture("temporaryTextures/marineCool.png"); //Sprites/Animations etc..
		
		coordSpriteSheet.x = 0;
		coordSpriteSheet.y = 0;
		coordSpriteSheet.h = 26;
		coordSpriteSheet.w = 19;

		SDL_QueryTexture(tex, NULL, NULL, &coordSpriteSheet.w, &coordSpriteSheet.h);
		//AI = 2;
		this->faction = faction;
		this->utype = utype;
	}

};



/*

class Building : public Entity
{
public:
	BUILDING_TYPE btype;

public:


	Building(iPoint &p, uint id, int btype = 0 ) : Entity(p, id, 0)
	{
		tex = app->tex->loadTexture("textures/lego_1x1_yellow.png");
		SDL_QueryTexture(tex, NULL, NULL, &dim.w, &dim.h);
		behaviour = 2;

		this->btype = btype;
	}

};
*/

/*
class Item : public Entity
{
	ENTITY_TYPE iType;

public:

	Item(iPoint &p, uint id, ITEM_TYPE) : Entity(p,id)
	{
		tex;//Sprites/Animations etc..;
		SDL_QueryTexture(tex, NULL, NULL, &dim.w, &dim.h);
		
		type = iType;
	}

};
*/
