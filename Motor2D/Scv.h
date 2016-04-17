#ifndef __SCV_H__
#define __SCV_H__

#include "Unit.h"

class Scv : public Unit
{
public:
	
	Animation	idle_up;
	Animation   idle_right;
	Animation	idle_down;
	Animation	idle_left;
	Animation	walk_up;
	Animation   walk_right_up;
	Animation   walk_right;
	Animation   walk_right_down;
	Animation   walk_down;
	Animation   walk_left_down;
	Animation   walk_left;
	Animation   walk_left_up;

	Animation	repair_up;
	Animation	repair_right_up;
	Animation	repair_right;
	Animation	repair_right_down;
	Animation	repair_down;
	Animation	repair_left_down;
	Animation	repair_left;
	Animation	repair_left_up;

	//SFX-------
	unsigned int scv_repair_fx;

	Scv(iPoint &p)
	{
		// Positions and dimensions
		center = { (float)p.x, (float)p.y };
		tex_width = 72;
		tex_height = 64;
		collider_offset = { -14, -16 };
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);
		// Animations
		tex = app->tex->loadTexture("Units/Blue_Scv.png"); //Sprites/Animations etc..
		scv_repair_fx = app->audio->loadFx("Audio/FX/SCV/Scv_repair.wav");
		#include"Scv_animations.h";
		angle = 225.f;
		//current_animation = &idle_up;
		selection_type = { 28, 9, 32, 19 };
		circle_selection_offset = {-2, 0 };
		offset_life = { -13, 20 };
		// Colliders
		coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 30, 30 }, COLLIDER_UNIT, app->entity_manager);

		// Another stuff
		specialization = SCV;
		state = IDLE;
		faction = PLAYER;
		flying = false;

		max_hp = 40;
		current_hp = 40.0f;
		max_hp_bars = 6;
		range_to_view = 300;
		range_to_attack = 50;

		damage = 5.0f;
		attack_delay = 200.0f;
		time_to_die = 500.0f;

		speed = 10;
		
		direction.create(1, 1, p.x, p.y);
		direction.setAngle(0.f);
	}

	//ROF method to check the orientation of the marine
	void checkAngle()
	{
		if (angle > 360)
		{
			angle -= 360.f;
		}
		// From 0 to 180 degrees
		if (has_target)
		{
			if (angle >= 0.f && angle < 22.5f)
			{
				current_animation = &idle_up;
			}

			else if (angle >= 45.f && angle < 67.5f)
			{
				current_animation = &walk_right_up;
			}

			else if(angle >= 90.f && angle < 112.5f)
			{
				current_animation = &idle_right;
			}

			else if (angle >= 135.f && angle < 157.5f)
			{
				current_animation = &walk_right_down;
			}

			// From 180 to 360 degrees
			else if (angle >= 180.f && angle < 202.5f)
			{
				current_animation = &idle_down;
			}

			else if (angle >= 225.f && angle < 247.5f)
			{
				current_animation = &walk_left_down;
			}

			else if (angle >= 270.f && angle < 292.5f)
			{
				current_animation = &idle_left;
			}

			else if (angle >= 315.f && angle < 337.5f)
			{
				current_animation = &walk_left_up;
			}
				
		}
		else
		{
			if (angle >= 0.f && angle < 22.5f)
			{
				if (state == REPAIR)
				{
					//app->audio->playFx(scv_repair_fx);
					current_animation = &repair_up;
				}
				else
					current_animation = &idle_up;
			}

			else if (angle >= 45.f && angle < 67.5f)
			{
				if (state == REPAIR)
				{
					//app->audio->playFx(scv_repair_fx);
					current_animation = &repair_right_up;
				}
				else
					current_animation = &walk_right_up;
			}

			else if (angle >= 90.f && angle < 112.5f)
			{
				if (state == REPAIR)
				{
					//app->audio->playFx(scv_repair_fx);
					current_animation = &repair_right;
				}
				else
					current_animation = &idle_right;
			}

			else if (angle >= 135.f && angle < 157.5f)
			{
				if (state == REPAIR)
				{
					//app->audio->playFx(scv_repair_fx);
					current_animation = &repair_right_down;
				}
				else
					current_animation = &walk_right_down;
			}

			// From 180 to 360 degrees
			else if (angle >= 180.f && angle < 202.5f)
			{
				if (state == REPAIR)
				{
					//app->audio->playFx(scv_repair_fx);
					current_animation = &repair_down;
				}
				else
					current_animation = &idle_down;
			}

			else if (angle >= 225.f && angle < 247.5f)
			{
				if (state == REPAIR)
				{
					//app->audio->playFx(scv_repair_fx);
					current_animation = &repair_left_down;
				}
				else
					current_animation = &walk_left_down;
			}

			else if (angle >= 270.f && angle < 292.5f)
			{
				if (state == REPAIR)
				{
					//app->audio->playFx(scv_repair_fx);
					current_animation = &repair_left;
				}
				else
					current_animation = &idle_left;
			}

			else if (angle >= 315.f && angle < 337.5f)
			{
				if (state == REPAIR)
				{
					//app->audio->playFx(scv_repair_fx);
					current_animation = &repair_left_up;
				}
				else
				current_animation = &walk_left_up;
			}
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
		case DYING:
			if ((timer_to_check += dt) >= time_to_die)
			{
				to_delete = true;
				coll->to_delete = true;
			}
			break;
		case REPAIR:
			if ((timer_attack_delay += dt) >= attack_delay)
			{
				repair();
				checkUnitDirection();
				timer_attack_delay = 0.0f;
			}
		}
		return true;
	}

	void repair()
	{
		if (target_to_repair != NULL)
		{
			int d = abs(center.x - target_to_repair->center.x) + abs(center.y - target_to_repair->center.y);
			d -= ((coll->rect.w / 2 + coll->rect.h / 2) / 2 + (target_to_repair->coll->rect.w / 2 + target_to_repair->coll->rect.h / 2) / 2);
			if (d <= range_to_attack)
			{
				if ((target_to_repair->current_hp) < target_to_repair->max_hp)
				{
					target_to_repair->current_hp += damage;
				}
				else
				{
					target_to_repair->current_hp = target_to_repair->max_hp;
					state = IDLE;
					target_to_repair = NULL;
					searchNearestEnemy();
					
				}
			}
			else
			{
				state = IDLE;
			}
		}
		else
		{
			state = IDLE;
		}
	}

	void draw()
	{
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}

};

#endif //__SCV_H__