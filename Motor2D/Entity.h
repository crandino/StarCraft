#include "SDL\include\SDL_render.h"
#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"

enum ENTITY_TYPE
{
	MARINE,
	ZERGLING
};

enum FACTION
{
	PLAYER,
	COMPUTER
};

class Entity
{

public:

	SDL_Rect		dim;
	SDL_Rect		spritesheet_section;
	ENTITY_TYPE		type;
	SDL_Texture		*tex;
	uint			id;
	iPoint			tile_pos;

	// Constructors
	Entity(const iPoint &p)
	{
		iPoint tmp = app->map->worldToMap(app->map->data.front(), p.x, p.y);
		tile_pos = tmp;
		tmp = app->map->mapToWorld(app->map->data.front(), tmp.x, tmp.y);
		dim.x = tmp.x;
		dim.y = tmp.y;
	};

	// Destructor
	~Entity()
	{
		SDL_DestroyTexture(tex);
	}

	void draw()
	{
		app->render->blit(tex, dim.x, dim.y, &spritesheet_section);
	}

};

class Marine : public Entity
{
public:

	SDL_Rect section;
	FACTION faction;

	Marine(iPoint &p) : Entity(p)
	{
		tex = app->tex->loadTexture("temporaryTextures/marine.png"); //Sprites/Animations etc..
		spritesheet_section = { 0, 0, 64, 64 };
		dim.w = section.w;
		dim.h = section.h;
		type = MARINE;
		faction = PLAYER;
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
