#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"
#include "Animation.h"
#include "Collision.h"

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
	
	SDL_Texture		*tex;   
	Animation		*current_animation;
	uint			id;
	
	unsigned int    max_hp;
	float           current_hp;
	unsigned int    max_hp_bars;
	float           current_hp_bars;

	Collider*       coll;

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