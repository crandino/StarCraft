#ifndef __UNIT_H__
#define __UNIT_H__

#include "Entity.h"

class Unit: public Entity
{
public:
	bool			flying;
	bool			has_target;
	vector<iPoint>  path;
	iPoint			distance_to_center_selector;
	SDL_Texture     *tile_path;
	Vector2D<int>   direction;
	float			speed;
	UNIT_DIRECTION	unit_direction;

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
			checkUnitDirection();
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
						state = IDLE;
						break;
					}
					else if (tile_pos.x == path.begin()->x && tile_pos.y == path.begin()->y)
						path.erase(path.begin());
				}
				total_pixels_moved += pixels_to_move;

			} while (total_pixels_moved < total_pixels_to_move);
		}
		else
		{
			state = IDLE;
			has_target = false;
		}
	}

	void checkUnitDirection()
	{
		if (state == ATTACK)
		{
			if (target_to_attack->tile_pos.x == tile_pos.x && target_to_attack->tile_pos.y < tile_pos.y)
			{
				unit_direction = UP;
			}
			else if (target_to_attack->tile_pos.x > tile_pos.x && target_to_attack->tile_pos.y < tile_pos.y)
			{
				unit_direction = RIGHT_UP;
			}
			else if (target_to_attack->tile_pos.x > tile_pos.x && target_to_attack->tile_pos.y == tile_pos.y)
			{
				unit_direction = RIGHT;
			}
			else if (target_to_attack->tile_pos.x > tile_pos.x && target_to_attack->tile_pos.y > tile_pos.y)
			{
				unit_direction = RIGHT_DOWN;
			}
			else if (target_to_attack->tile_pos.x == tile_pos.x && target_to_attack->tile_pos.y > tile_pos.y)
			{
				unit_direction = DOWN;
			}
			else if (target_to_attack->tile_pos.x < tile_pos.x && target_to_attack->tile_pos.y > tile_pos.y)
			{
				unit_direction = LEFT_DOWN;
			}
			else if (target_to_attack->tile_pos.x < tile_pos.x && target_to_attack->tile_pos.y == tile_pos.y)
			{
				unit_direction = LEFT;
			}
			else if (target_to_attack->tile_pos.x < tile_pos.x && target_to_attack->tile_pos.y < tile_pos.y)
			{
				unit_direction = LEFT_UP;
			}
		}
		else
		{
			if (path.size()>0)
			{
				iPoint pos_path = *path.begin();
				if (pos_path.x == tile_pos.x && pos_path.y < tile_pos.y)
				{
					unit_direction = UP;
				}
				else if (pos_path.x > tile_pos.x && pos_path.y < tile_pos.y)
				{
					unit_direction = RIGHT_UP;
				}
				else if (pos_path.x > tile_pos.x && pos_path.y == tile_pos.y)
				{
					unit_direction = RIGHT;
				}
				else if (pos_path.x > tile_pos.x && pos_path.y > tile_pos.y)
				{
					unit_direction = RIGHT_DOWN;
				}
				else if (pos_path.x == tile_pos.x && pos_path.y > tile_pos.y)
				{
					unit_direction = DOWN;
				}
				else if (pos_path.x < tile_pos.x && pos_path.y > tile_pos.y)
				{
					unit_direction = LEFT_DOWN;
				}
				else if (pos_path.x < tile_pos.x && pos_path.y == tile_pos.y)
				{
					unit_direction = LEFT;
				}
				else if (pos_path.x < tile_pos.x && pos_path.y < tile_pos.y)
				{
					unit_direction = LEFT_UP;
				}
			}	
		}

		switch (unit_direction)
		{
		case(UP) :
			angle = 0.f;
			break;

		case(RIGHT_UP) :
			angle = 45.f;
			break;

		case(RIGHT) :
			angle = 90.f;
			break;

		case(RIGHT_DOWN) :
			angle = 135.f;
			break;

		case(DOWN) :
			angle = 180.f;
			break;

		case(LEFT_DOWN) :
			angle = 225.f;
			break;

		case(LEFT) :
			angle = 270.f;
			break;

		case(LEFT_UP) :
			angle = 315.f;
			break;
		}
	}

	bool update(float dt)
	{
		checkAngle();   // This sets animation according to their angle direction
		coll->setPos(center.x + collider_offset.x, center.y + collider_offset.y);

		switch (state)
		{
		case IDLE:
			if ((timer_to_check += dt) >= TIME_TO_CHECK)
			{
				if (searchNearestEnemy())
					LOG("Enemy found");
				timer_to_check = 0.0f;
			}
			break;
		case MOVE:
			if (has_target) move(dt);
			break;
		case MOVE_ALERT:
			if ((timer_to_check += dt) >= TIME_TO_CHECK)
			{
				if (searchNearestEnemy())
					LOG("Enemy found");
				timer_to_check = 0.0f;
			}
			if (has_target) move(dt);
			break;
		case ATTACK:
			if ((timer_attack_delay += dt) >= attack_delay)
			{
				attack();
				checkUnitDirection();
				timer_attack_delay = 0.0f;
			}
			break;
		case DYING:
			if ((timer_to_check += dt) >= time_to_die)
			{
				to_delete = true;
				coll->to_delete = true;
			}
			break;
		}
		return true;
	}
};


#endif //__UNIT_H__