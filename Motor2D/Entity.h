#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"
#include "Animation.h"
#include "Audio.h"
#include "Collision.h"
#include "GameManager.h"
#include "SDL\include\SDL.h"

#define TIME_TO_CHECK 100.0f

enum STATE
{
	IDLE,
	MOVE,
	MOVE_ALERT,
	ATTACK,
	REPAIR,
	DYING
};

class Entity
{

public:

	fPoint			pos;						// World position of Entity. Upper_left corner.
	fPoint			center;						// World positoin of Entity. Center
	iPoint			tile_pos;					// Map position (tiles) of Entity
	iPoint			collider_offset;			// Useful to correctly place the collider rect
	
	int		     	tex_width, tex_height;

	FACTION			faction;
	ENTITY_TYPE		type;
	SPECIALIZATION  specialization;
	STATE			state;

	Timer			timer_to_check;
	float			time_to_create;

	// UI paramters
	SDL_Rect        selection_type;				// Section of the texture that contains circle selections
	iPoint		    circle_selection_offset;
	
	SDL_Texture		*tex;   
	Animation		*current_animation;
	uint			id;
	
	Vector2D<int>   direction;
	float			angle;
	float			speed;
	float			time_to_die = 500.0f;

	// Lifes attributes
	uint			max_hp;
	int             current_hp;
	uint            max_hp_bars;
	iPoint			offset_life;

	Entity			*target_to_attack = nullptr;
	Entity			*target_to_repair = nullptr;
	Entity			*target_to_reach = nullptr;
	int				range_to_attack;
	int				range_of_vision;
	float			damage;
	int				repair_power = 10;

	Collider*       coll;
	
	bool			to_delete;
	bool            inside_bunker = false;
	
	// Constructors
	Entity()
	{
		to_delete = false;
		timer_to_check.start();
	};

	// Destructor
	~Entity()
	{
		SDL_DestroyTexture(tex);
	}

	virtual void setAnimationFromDirection()
	{ }

	virtual bool update(float dt)
	{
 		return true;
	}

	virtual bool searchNearestEnemy()
	{
		return app->entity_manager->searchNearEntity(this);
	}

	virtual void draw()
	{
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}

};

#endif !__ENTITY_H__