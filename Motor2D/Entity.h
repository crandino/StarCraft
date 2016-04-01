#include "SDL\include\SDL_render.h"
#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"
#include "Animation.h"

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
	Animation*		current_animation;
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
		app->render->blit(tex, dim.x, dim.y, &(current_animation->getCurrentFrame()));
	}

};

class Marine : public Entity
{
public:
	
	Animation idle;
	SDL_Rect section;
	FACTION faction;

	Marine(iPoint &p) : Entity(p)
	{
		
		tex = app->tex->loadTexture("temporaryTextures/marine.png"); //Sprites/Animations etc..
		//--TEST TO TRY THE ANIMATION MODULE----
		idle.frames.push_back({ 0, 0, 64, 64 });
		idle.frames.push_back({ 192, 0, 64, 64 });
		idle.frames.push_back({ 256, 0, 64, 64 });
		idle.frames.push_back({ 192, 0, 64, 64 });
		idle.frames.push_back({ 0, 0, 64, 64 });
		idle.speed = 0.04f;
		idle.loop = false; // IPL: if you put this true, the animation doesn't work well, try it!
		current_animation = &idle;
		//-------------------------------------
		dim.w = current_animation->getCurrentFrame().w;
		dim.h = current_animation->getCurrentFrame().h;
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
