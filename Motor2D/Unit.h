#ifndef __UNIT_H__
#define __UNIT_H__

#include "Entity.h"

class Unit : public Entity
{
public:
	
	bool			flying;
	bool			has_target;
	vector<iPoint>  path;
	iPoint			distance_to_center_selector;
	SDL_Texture     *tile_path;
	Vector2D<int>   direction;
	float			speed;
	SPECIALIZATION  unit_type;

	Unit()
	{
		type = UNIT;
		has_target = false;
		tile_path = app->tex->loadTexture("TemporaryTextures/path_tile.png");
	};

	virtual void calculePos()
	{
		pos = { (float)center.x - (tex_width / 2), (float)center.y - (tex_height / 2) };
	}

	virtual void move(float dt)
	{
		if (path.size() > 0)
		{
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
					}
					else if (tile_pos.x == path.begin()->x && tile_pos.y == path.begin()->y)
						path.erase(path.begin());
				}
				total_pixels_moved += pixels_to_move;

			} while (total_pixels_moved < total_pixels_to_move);
		}
	}
};


#endif __UNIT_H__