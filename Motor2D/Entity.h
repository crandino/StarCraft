#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"
#include "Animation.h"
#include "Collision.h"
#include "Marine.h"
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
	
	SDL_Texture		*tex;   
	Animation		*current_animation;
	uint			id;
	
	Vector2D<int>   direction;
	float angle;
	float speed;
	

	unsigned int    max_hp;
	float           current_hp;
	unsigned int    max_hp_bars;
	float           current_hp_bars;

	Collider*       coll;
	
	bool			has_target;
	vector<iPoint>  path;
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

	virtual void calculePos()
	{
		pos = { (float)center.x - (tex_width / 2), (float)center.y - (tex_height / 2) };
	}

	virtual void move(float dt)
	{
		if (path.size() > 0)
		{
			iPoint pos_path = *path.begin();
			if (tile_pos == path.back())
			{
				angle = -1.0f;
			}
			
			if (pos_path.x == tile_pos.x && pos_path.y < tile_pos.y)
			{
				angle = 0.f;
			}
		    else if (pos_path.x > tile_pos.x && pos_path.y < tile_pos.y)
			{
				angle = 45.f;
			}
			else if (pos_path.x > tile_pos.x && pos_path.y == tile_pos.y)
			{
				angle = 90.f;
			}
			
			else if (pos_path.x > tile_pos.x && pos_path.y > tile_pos.y)
			{
				angle = 135.f;
			}
			else if (pos_path.x == tile_pos.x && pos_path.y > tile_pos.y)
			{
				angle = 180.f;
			}
			else if (pos_path.x < tile_pos.x && pos_path.y > tile_pos.y)
			{
				angle = 225.f;
			}
			else if (pos_path.x < tile_pos.x && pos_path.y == tile_pos.y)
			{
				angle = 270.f;
			}
			else if (pos_path.x < tile_pos.x && pos_path.y < tile_pos.y)
			{
				angle = 315.f;
			}
			

			float pixels_to_move = 0;
			float total_pixels_moved = 0;
			float total_pixels_to_move = speed / 100 * dt;

			if (total_pixels_to_move > 8)
				pixels_to_move = total_pixels_to_move / 8;
			do{
				if (total_pixels_moved + 8 > total_pixels_to_move)
					pixels_to_move = total_pixels_to_move - total_pixels_moved;

				if (path.begin()->x < tile_pos.x && path.begin()->y < tile_pos.y)
				{
					center.x -= pixels_to_move / 2;
					center.y -= pixels_to_move / 2;
				}
				else if (path.begin()->x < tile_pos.x && path.begin()->y > tile_pos.y)
				{
					center.x -= pixels_to_move / 2;
					center.y += pixels_to_move / 2;

				}
				else if (path.begin()->x > tile_pos.x && path.begin()->y > tile_pos.y)
				{
					center.x += pixels_to_move / 2;
					center.y += pixels_to_move / 2;

				}
				else if (path.begin()->x > tile_pos.x && path.begin()->y < tile_pos.y)
				{
					center.x += pixels_to_move / 2;
					center.y -= pixels_to_move / 2;

				}
				else if (path.begin()->y == tile_pos.y)
				{
					if (path.begin()->x < tile_pos.x)
						center.x -= pixels_to_move;

					else
						center.x += pixels_to_move;
				}
				else
				{
					if (path.begin()->y < tile_pos.y)
						center.y -= pixels_to_move;

					else
						center.y += pixels_to_move;
				}
				calculePos();

				if (app->map->worldToMap(app->map->data.back(), center.x, center.y) != tile_pos)
				{
					tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);
					if (tile_pos == path.back())
					{
						path.clear();
						has_target = false;
						end_path = true;
					}						
					else if (tile_pos.x == path.begin()->x && tile_pos.y == path.begin()->y)
						path.erase(path.begin());
				}
				total_pixels_moved += pixels_to_move;

			} while (total_pixels_moved < total_pixels_to_move);
		}
		
	}

	void markToDelete()
	{
		markedToDelete = true;
	}

};

#endif !__ENTITY_H__