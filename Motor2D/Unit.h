#ifndef __UNIT_H__
#define __UNIT_H__

#include "Entity.h"

class Unit: public Entity
{
public:
	bool				flying;
	bool				has_target;
	vector<iPoint>		path;
	iPoint				distance_to_center_selector;
	Vector2D<int>       direction;
	float				speed;
	UNIT_DIRECTION	    unit_direction;

	Unit()
	{
		type = UNIT;
		has_target = false;
	};

	virtual void calculePos()
	{
		pos = { (float)center.x - (tex_width / 2), (float)center.y - (tex_height / 2) };
	}

	virtual void attack()
	{
		if (target_to_attack != NULL && target_to_attack->state != DYING)
		{
			int d = abs(center.x - target_to_attack->center.x) + abs(center.y - target_to_attack->center.y);
			d -= ((coll->rect.w / 2 + coll->rect.h / 2) / 2 + (target_to_attack->coll->rect.w / 2 + target_to_attack->coll->rect.h / 2) / 2);
			if (d <= range_to_attack)
			{
				if ((target_to_attack->current_hp -= damage) <= 0.0f)
				{
					state = IDLE;
					target_to_attack->state = DYING;
					target_to_attack = NULL;

					if (faction == PLAYER)
						app->game_manager->total_units_killed_currentFrame++;
				}
			}
			else
			{
				state = IDLE;
				searchNearestEnemy();
			}
		}
		else
		{
			state = IDLE;
			searchNearestEnemy();
		}
	}

	virtual void move(float dt)
	{
		if (path.size() > 0)
		{
			checkUnitDirection();
			float pixels_to_move = 0;
			float total_pixels_moved = 0;
			float total_pixels_to_move = speed / 100 * dt;

			if (total_pixels_to_move >= 4)
				pixels_to_move = 4;

			do{
				if (total_pixels_moved + 4 > total_pixels_to_move)
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
						//Bunker Stuff
						if (target_to_reach != NULL && target_to_reach->specialization == BUNKER)
						{
							app->entity_manager->GetInsideBunker(this);
							target_to_reach = NULL;
						}
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

	// Depending on its state, the entity obtains the corresponding angle // CRZ
	void checkUnitDirection()
	{
		if (state == ATTACK && target_to_attack != NULL)
		{
			direction = { (target_to_attack->tile_pos.x - tile_pos.x), (target_to_attack->tile_pos.y - tile_pos.y) };
		}
		else if (state == REPAIR)
		{
			direction = { (target_to_repair->tile_pos.x - tile_pos.x), (target_to_repair->tile_pos.y - tile_pos.y) };
		}
		else
		{
			if (path.size() > 0)
			{
				iPoint pos_path = *path.begin();
				direction = { (pos_path.x - tile_pos.x), (pos_path.y - tile_pos.y) };
			}	
		}
		angle = round(direction.getAngle());
	}

	virtual bool update(float dt) 
	{ 
		setAnimationFromDirection();   // This sets animation according to their angle direction
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

				if (state == ATTACK)
					searchNearestEnemy();
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