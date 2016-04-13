#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"
#include "Animation.h"
#include "Collision.h"
#include "SDL\include\SDL.h"

#define TIME_TO_CHECK 100.0f

enum STATE
{
	IDLE,
	MOVE,
	MOVE_ALERT,
	ATTACK
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
	float			timer_to_check = 0.0f;

	// UI paramters
	SDL_Rect        selection_type;
	int				circle_selection_offset;
	
	SDL_Texture		*tex;   
	Animation		*current_animation;
	uint			id;
	
	Vector2D<int>   direction;
	float			angle;
	float			speed;

	// Lifes attributes
	uint			max_hp;
	int             current_hp;
	uint            max_hp_bars;
	iPoint			offset_life;

	Entity			*target_to_attack;
	unsigned int	range_to_attack;
	unsigned int	range_to_view;
	float			damage;
	float			attack_delay;
	float			timer_attack_delay = 0.0f;
	

	Collider*       coll;
	
	bool			has_target;
	iPoint			distance_to_center_selector;
	SDL_Texture     *tile_path;
	bool            end_path = false;

	bool			markedToDelete = false;

	// Constructors
	Entity()
	{};

	// Destructor
	~Entity()
	{
		SDL_DestroyTexture(tex);
	}

	virtual bool update(float dt)
	{
		return true;
	}

	//This name could be changed
	virtual void checkAngle()
	{

	}

	virtual bool searchNearestEnemy()
	{
		return app->entity_manager->searchNearEntity(this);
	}

	virtual void attack()
	{
		if ((abs(center.x - target_to_attack->center.x) + abs(center.y - target_to_attack->center.y)) <= range_to_attack)
		{
			if ((target_to_attack->current_hp -= damage) <= 0.0f)
			{
				state = IDLE;
				target_to_attack->markToDelete();
				target_to_attack = NULL;
				has_target = false;
			}
		}
		else
		{
			state = IDLE;
			if (type == UNIT)
			{
				app->entity_manager->searchNearEntity(this);
			}
		}

	}

	virtual void draw()
	{
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}

	void markToDelete()
	{
		markedToDelete = true;
	}

};

#endif !__ENTITY_H__