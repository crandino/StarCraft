#include "SDL\include\SDL_render.h"
#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"
#include "Vector2D.h"
#include "Animation.h"
#include "Collision.h"

enum ENTITY_TYPE
{
	//Units
	MARINE,
	ZERGLING,
	//Buildings
	COMMANDCENTER
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

	Vector2D<int> direction;

	unsigned int    hp;

	Collider*        coll;

	vector<iPoint>  path;


	// Constructors
	Entity(const iPoint &p)
	{

		//iPoint tmp = app->map->worldToMap(app->map->data.front(), p.x, p.y);
		tile_pos = p;
		//tmp = app->map->mapToWorld(app->map->data.front(), tmp.x, tmp.y);
		dim.x = p.x;
		dim.y = p.y;
		coll = app->collision->addCollider(dim, COLLIDER_BOMB);

	};

	// Destructor
	~Entity()
	{
		SDL_DestroyTexture(tex);
	}

	virtual void draw()
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
	unsigned int hp = 10;

	Marine(iPoint &p) : Entity(p)
	{
		
		tex = app->tex->loadTexture("Units/Marine.png"); //Sprites/Animations etc..
		SDL_QueryTexture(tex, NULL, NULL, &dim.w, &dim.h);
		//--TEST TO TRY THE ANIMATION MODULE----
		idle.frames.push_back({ 0, 0, 64, 64 });
		/*idle.frames.push_back({ 64, 0, 64, 64 });
		idle.frames.push_back({ 128, 0, 64, 64 });
		idle.frames.push_back({ 192, 0, 64, 64 });
		idle.frames.push_back({ 256, 0, 64, 64 });
		idle.frames.push_back({ 320, 0, 64, 64 });
		idle.frames.push_back({ 384, 0, 64, 64 });
		idle.frames.push_back({ 448, 0, 64, 64 });
		idle.frames.push_back({ 512, 0, 64, 64 });
		idle.frames.push_back({ 576, 0, 64, 64 });
		idle.frames.push_back({ 640, 0, 64, 64 });
		idle.frames.push_back({ 704, 0, 64, 64 });
		idle.frames.push_back({ 768, 0, 64, 64 });
		idle.frames.push_back({ 832, 0, 64, 64 });
		idle.frames.push_back({ 896, 0, 64, 64 });
		idle.frames.push_back({ 960, 0, 64, 64 });*/
		idle.speed = 0.0f;
		idle.loop = true; // IPL: if you put this true, the animation doesn't work well, try it!


		current_animation = &idle;

		//-------------------------------------
		dim.w = current_animation->getCurrentFrame().w;
		dim.h = current_animation->getCurrentFrame().h;
		type = MARINE;
		faction = PLAYER;

		hp = 10;

		direction.create(1, 1, p.x, p.y);
		direction.setAngle(0.f);
	}

	void checkAngle()
	{
		float angle = direction.getAngle();

		if (angle >= 18)
		{
			idle.frames.push_back({ 64, 0, 64, 64 });
		}

	}

	void draw()
	{
		app->render->blit(tex, dim.x, dim.y, &(current_animation->getCurrentFrame()));
	}

};



class CommandCenter : public Entity
{
public:
	FACTION faction;
	Animation idle;
	SDL_Rect section;
	unsigned int hp = 1000;

public:


	CommandCenter(iPoint &p) : Entity(p)
	{
		
		SDL_QueryTexture(tex, NULL, NULL, &dim.w, &dim.h);
		
		tex = app->tex->loadTexture("temporaryTextures/commandCenter.png"); //Sprites/Animations etc..
		//--TEST TO TRY THE ANIMATION MODULE----
		idle.frames.push_back({ 0, 27, 128, 100});
		
		idle.speed = 1.0f;
		idle.loop = false; // IPL: if you put this true, the animation doesn't work well, try it!
		current_animation = &idle;
		//-------------------------------------
		dim.w = current_animation->getCurrentFrame().w;
		dim.h = current_animation->getCurrentFrame().h;
		
		type = COMMANDCENTER;

		faction = PLAYER;
	}

};

class Zergling : public Entity
{
public:

	Animation idle;
	SDL_Rect section;
	FACTION faction;
	unsigned int hp = 10;

	Zergling(iPoint &p) : Entity(p)
	{

		tex = app->tex->loadTexture("Unit/Zergling.png"); //Sprites/Animations etc..

		//--TEST TO TRY THE ANIMATION MODULE----
		idle.frames.push_back({ 0, 0, 128, 128 });
		idle.frames.push_back({ 128, 0, 128, 128 });
		idle.frames.push_back({ 256, 0, 128, 128 });

		idle.speed = 0.05f;
		idle.loop = false; // IPL: if you put this true, the animation doesn't work well, try it!

		current_animation = &idle;
		//-------------------------------------
		dim.w = current_animation->getCurrentFrame().w;
		dim.h = current_animation->getCurrentFrame().h;
		type = ZERGLING;
		faction = COMPUTER;

	}
};


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
