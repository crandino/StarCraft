#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"
#include "Animation.h"
#include "Collision.h"
#include "SDL\include\SDL.h"

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

	// UI paramters
	SDL_Rect        selection_type;
	int				circle_selection_offset;
	
	SDL_Texture		*tex;   
	Animation		*current_animation;
	uint			id;
	
	Vector2D<int>   direction;
	float angle;
	float speed;
	
	// Lifes attributes
	uint			max_hp;
	int             current_hp;
	uint            max_hp_bars;
	iPoint			offset_life;

	Collider*       coll;
	
	bool			has_target;
	iPoint			distance_to_center_selector;
	SDL_Texture     *tile_path;
	bool            end_path = false;

	bool markedToDelete = false;

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