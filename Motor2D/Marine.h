#ifndef __MARINE_H__
#define __MARINE_H__

#include "Unit.h"

class Marine : public Unit
{
public:
	//ROF
	// It must have a review to do spritesheets with render flip into Animation module https://wiki.libsdl.org/SDL_RendererFlip
	Animation	idle_up;
	Animation   idle_right;
	Animation	idle_down;
	Animation	idle_left;
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

	Marine(iPoint &p)
	{
		// Positions and dimensions
		center = { (float)p.x, (float)p.y };

		tex_width = tex_height = 64;
		collider_offset = { 10, 14 };
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y); 
		// Animations
		tex = app->tex->loadTexture("Units/Marine.png"); //Sprites/Animations etc..
		#include "Marine_animations.h";
		angle = -1;
		current_animation = &idle_up;


		// Colliders
		coll = app->collision->addCollider({ center.x - collider_offset.x, center.y - collider_offset.y, 22, 30 }, COLLIDER_BOMB);

		// Another stuff
		
		state = IDLE;
		faction = PLAYER;
		selection_type = { 3, 4, 22, 13 };
		circle_selection_offset = -1;
		flying = false;

		max_hp = 40;
		current_hp = 40.0f;
		max_hp_bars = 6;
		offset_life = { -19, 16 };

		range_to_view = 200;
		range_to_attack = 100;
		damage = 5.0f;
		attack_delay = 200.0f;
		
		//current_hp_bars = 6;
		
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

		if (has_target)
		{
			// From 0 to 180 degrees
			if (angle >= 0.f && angle < 22.5f)
			{
				current_animation = &walk_up;
			}
			if (angle >= 22.5f && angle < 45.f)
			{
				current_animation = &one;
			}
			if (angle >= 45.f && angle < 67.5f)
			{
				current_animation = &walk_right_up;
			}
			if (angle >= 67.5f && angle < 90.f)
			{
				current_animation = &three;
			}
			if (angle >= 90.f && angle < 112.5f)
			{
				current_animation = &walk_right;
			}
			if (angle >= 112.5f && angle < 135.f)
			{
				current_animation = &five;
			}
			if (angle >= 135.f && angle < 157.5f)
			{
				current_animation = &walk_right_down;
			}
			if (angle >= 157.5f && angle < 180.f)
			{
				current_animation = &seven;
			}
			// From 180 to 360 degrees
			if (angle >= 180.f && angle < 202.5f)
			{
				current_animation = &walk_down;
			}
			if (angle >= 202.5f && angle < 225.f)
			{
				current_animation = &nine;
			}
			if (angle >= 225.f && angle < 247.5f)
			{
				current_animation = &walk_left_down;
			}
			if (angle >= 247.5f && angle < 270.f)
			{
				current_animation = &eleven;
			}
			if (angle >= 270.f && angle < 292.5f)
			{
				current_animation = &walk_left;
			}
			if (angle >= 292.5f && angle < 315.f)
			{
				current_animation = &thirdteen;
			}
			if (angle >= 315.f && angle < 337.5f)
			{
				current_animation = &walk_left_up;
			}
			if (angle >= 337.5f && angle < 360.f)
			{
				current_animation = &fifteen;
			}
		}
		else 
		{
			if (angle >= 0.f && angle < 22.5f)
			{
				current_animation = &idle_up;
			}
			if (angle >= 90.f && angle < 112.5f)
			{
				current_animation = &idle_right;
			}
			if (angle >= 180.f && angle < 202.5f)
			{
				current_animation = &idle_down;
			}
			if (angle >= 270.f && angle < 292.5f)
			{
				current_animation = &idle_left;
			}
			
		}		
		
	}

	void draw()
	{
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}

	bool update(float dt)
	{
		coll->setPos(center.x - 10, center.y - 14);

		switch (state)
		{
		case IDLE:
			if ((timer_to_check += dt) >= TIME_TO_CHECK)
			{
				if(searchNearestEnemy())
					LOG("Enemy found");
				timer_to_check = 0.0f;
			}
			break;
		case MOVE:
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
				timer_attack_delay = 0.0f;
			}
			break;
		}
		return true;
	}
};

#endif __MARINE_H__