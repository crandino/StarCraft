#ifndef __MARINE_H__
#define __MARINE_H__

#include "Unit.h"

class Marine : public Unit
{
public:
	//ROF
	// It must have a review to do spritesheets with render flip into Animation module https://wiki.libsdl.org/SDL_RendererFlip
	Animation	idle_up;
	Animation	idle_right_up;
	Animation   idle_right;
	Animation	idle_right_down;
	Animation	idle_down;
	Animation	idle_left_down;
	Animation	idle_left;
	Animation	idle_left_up;
	Animation	walk_up;
	Animation   one;
	Animation   walk_right_up;
	Animation   three;
	Animation   walk_right;
	Animation   five;
	Animation   walk_right_down;
	Animation   seven;
	Animation   walk_down;
	Animation   nine;
	Animation   walk_left_down;
	Animation   eleven;
	Animation   walk_left;
	Animation   thirdteen;
	Animation   walk_left_up;
	Animation   fifteen;

	Animation	attack_up;
	Animation	attack_right_up;
	Animation	attack_right;
	Animation	attack_right_down;
	Animation	attack_down;
	Animation	attack_left_down;
	Animation	attack_left;
	Animation	attack_left_up;

	Animation dead;

	// SFX
	 unsigned int marine_attack_fx;

	Marine(iPoint &p)
	{
		// Positions and dimensions
		center = { (float)p.x, (float)p.y };

		tex_width = tex_height = 64;
		collider_offset = { -10, -14 };
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y); 

		// Animations and FX
		tex = app->tex->loadTexture("Units/Blue_Marine.png"); //Sprites/Animations etc..
		marine_attack_fx = app->audio->loadFx("Audio/FX/Marine/Marine_attack.wav");
		
		#include "Marine_animations.h";
		angle = 0;
		current_animation = &idle_up;
	
		// Colliders
		coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 22, 30 }, COLLIDER_BOMB);

		// Another stuff
		
		state = IDLE;
		faction = PLAYER;
		selection_type = { 3, 4, 22, 13 };
		specialization = MARINE;
		circle_selection_offset = { 0, -1 };
		flying = false;

		max_hp = 40;
		current_hp = 40.0f;
		max_hp_bars = 6;
		offset_life = { -16, 16 };

		range_to_view = 300;
		range_to_attack = 100;
		damage = 5.0f;
		attack_delay = 200.0f;
		time_to_die = 500.0f;
		
		speed = 10.0f;
		
		direction.create(1, 1, p.x, p.y);
		direction.setAngle(0.f);
	}

	//ROF method to check the orientation of the marine
	void checkAngle()
	{
		if (state == DYING)
		{
			current_animation = &dead;
		}
		else
		{
			if (angle > 360)
			{
				angle -= 360.f;
			}

			if (has_target)
			{
				// From 0 to 180 degrees
				if (angle >= 0.f && angle < 22.5f)
				{
					current_animation = &walk_up;
				}
				else if (angle >= 22.5f && angle < 45.f)
				{
					current_animation = &one;
				}
				else if (angle >= 45.f && angle < 67.5f)
				{
					current_animation = &walk_right_up;
				}
				else if (angle >= 67.5f && angle < 90.f)
				{
					current_animation = &three;
				}
				else if (angle >= 90.f && angle < 112.5f)
				{
					current_animation = &walk_right;
				}
				else if (angle >= 112.5f && angle < 135.f)
				{
					current_animation = &five;
				}
				else if (angle >= 135.f && angle < 157.5f)
				{
					current_animation = &walk_right_down;
				}
				else if (angle >= 157.5f && angle < 180.f)
				{
					current_animation = &seven;
				}
				// From 180 to 360 degrees
				else if (angle >= 180.f && angle < 202.5f)
				{
					current_animation = &walk_down;
				}
				else if (angle >= 202.5f && angle < 225.f)
				{
					current_animation = &nine;
				}
				else if (angle >= 225.f && angle < 247.5f)
				{
					current_animation = &walk_left_down;
				}
				else if (angle >= 247.5f && angle < 270.f)
				{
					current_animation = &eleven;
				}
				else if (angle >= 270.f && angle < 292.5f)
				{
					current_animation = &walk_left;
				}
				else if (angle >= 292.5f && angle < 315.f)
				{
					current_animation = &thirdteen;
				}
				else if (angle >= 315.f && angle < 337.5f)
				{
					current_animation = &walk_left_up;
				}
				else if (angle >= 337.5f && angle < 360.f)
				{
					current_animation = &fifteen;
				}
			}
			else
			{ //TODO IPL: ALL ANGLE ATTACK.
				if (angle >= 0.f && angle < 22.5f)
				{
					if (state == ATTACK)
					{
						//app->audio->playFx(marine_attack_fx);
						current_animation = &attack_up;
					}
					else
						current_animation = &idle_up;
				}

				else if (angle >= 45.f && angle < 67.5f)
				{
					if (state == ATTACK)
					{
						//app->audio->playFx(marine_attack_fx);
						current_animation = &attack_right_up;
					}
					else
						current_animation = &idle_right_up;
				}
				else if (angle >= 90.f && angle < 112.5f)
				{
					if (state == ATTACK)
					{
						//app->audio->playFx(marine_attack_fx);
						current_animation = &attack_right;
					}
					else
						current_animation = &idle_right;
				}
				else if (angle >= 135.f && angle < 157.5f)
				{
					if (state == ATTACK)
					{
						//app->audio->playFx(marine_attack_fx);
						current_animation = &attack_right_down;
					}
					else
						current_animation = &idle_right_down;
				}
				else if (angle >= 180.f && angle < 202.5f)
				{
					if (state == ATTACK)
					{
						//app->audio->playFx(marine_attack_fx);
						current_animation = &attack_down;
					}
					else
						current_animation = &idle_down;
				}
				else if (angle >= 225.f && angle < 247.5f)
				{
					if (state == ATTACK)
					{
						//app->audio->playFx(marine_attack_fx);
						current_animation = &attack_left_down;
					}
					else
						current_animation = &idle_left_down;
				}
				else if (angle >= 270.f && angle < 292.5f)
				{
					if (state == ATTACK)
					{
						//app->audio->playFx(marine_attack_fx);
						current_animation = &attack_left;
					}
					else
						current_animation = &idle_left;
				}
				else if (angle >= 315.f && angle < 337.5f)
				{
					if (state == ATTACK)
					{
						//app->audio->playFx(marine_attack_fx);
						current_animation = &attack_left_up;
					}
					else
						current_animation = &idle_left_up;
				}
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

	void draw()
	{
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}
};

#endif __MARINE_H__