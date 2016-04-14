#ifndef __ZERGLING_H__
#define __ZERGLING_H__

#include "Unit.h"

class Zergling : public Unit
{
public:

	Animation idle_up;
	Animation idle_right_up;
	Animation idle_right;
	Animation idle_right_down;
	Animation idle_down;
	Animation idle_left_down;
	Animation idle_left;
	Animation idle_left_up;

	Animation walk_up;
	Animation walk_right_up;
	Animation walk_right;
	Animation walk_right_down;
	Animation walk_down;
	Animation walk_left_down;
	Animation walk_left;
	Animation walk_left_up;

	Animation attack_up;
	Animation attack_right_up;
	Animation attack_right;
	Animation attack_right_down;
	Animation attack_down;
	Animation attack_left_down;
	Animation attack_left;
	Animation attack_left_up;

	

	Zergling(iPoint &p)
	{
		// Positions and dimensions
		center = { (float)p.x, (float)p.y };

		tex_width = tex_height = 128;
		collider_offset = { 12, 14 };
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

		// Animation
		tex = app->tex->loadTexture("Units/Zergling.png");
		#include"Zergling_animations.h";
		current_animation = &idle_up;

		// Collider
		coll = app->collision->addCollider({ center.x - collider_offset.x, center.y - collider_offset.y, 24, 26 }, COLLIDER_BOMB);

		// Another stuff
		type = UNIT;
		specialization = ZERGLING;
		state = IDLE;
		faction = COMPUTER;
		max_hp = 40;
		current_hp = 40.0f;
		max_hp_bars = 6;
		selection_type = { 3, 4, 22, 13 };
		circle_selection_offset = -1;
		offset_life = { -19, 16 };
		flying = false;

		speed = 8.0f;
		range_to_view = 200;
		range_to_attack = 32;
		damage = 3.0f;
		attack_delay = 200.0f;
	}

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

			if (angle >= 45.f && angle < 67.5f)
			{
				current_animation = &walk_right_up;
			}

			if (angle >= 90.f && angle < 112.5f)
			{
				current_animation = &walk_right;
			}

			if (angle >= 135.f && angle < 157.5f)
			{
				current_animation = &walk_right_down;
			}

			// From 180 to 360 degrees
			if (angle >= 180.f && angle < 202.5f)
			{
				current_animation = &walk_down;
			}

			if (angle >= 225.f && angle < 247.5f)
			{
				current_animation = &walk_left_down;
			}

			if (angle >= 270.f && angle < 292.5f)
			{
				current_animation = &walk_left;
			}

			if (angle >= 315.f && angle < 337.5f)
			{
				current_animation = &walk_left_up;
			}

		}
		else
		{
			if (angle >= 0.f && angle < 22.5f)
			{
				if (state == ATTACK)
					current_animation = &attack_up;
				else
					current_animation = &idle_up;
			}

			else if (angle >= 45.f && angle < 67.5f)
			{
				if (state == ATTACK)
					current_animation = &attack_right_up;
				else
					current_animation = &idle_right_up;
			}
			else if (angle >= 90.f && angle < 112.5f)
			{
				if (state == ATTACK)
					current_animation = &attack_right;
				else
					current_animation = &idle_right;
			}
			else if (angle >= 135.f && angle < 157.5f)
			{
				if (state == ATTACK)
					current_animation = &attack_right_down;
				else
					current_animation = &idle_right_down;
			}
			else if (angle >= 180.f && angle < 202.5f)
			{
				if (state == ATTACK)
					current_animation = &attack_down;
				else
					current_animation = &idle_down;
			}
			else if (angle >= 225.f && angle < 247.5f)
			{
				if (state == ATTACK)
					current_animation = &attack_left_down;
				else
					current_animation = &idle_left_down;
			}
			else if (angle >= 270.f && angle < 292.5f)
			{
				if (state == ATTACK)
					current_animation = &attack_left;
				else
					current_animation = &idle_left;
			}
			else if (angle >= 315.f && angle < 337.5f)
			{
				if (state == ATTACK)
					current_animation = &attack_left_up;
				else
					current_animation = &idle_left_up;
			}

		}
	}

	void draw()
	{
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}
};

#endif !__ZERGLING_H__