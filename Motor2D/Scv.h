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
		tex = app->tex->loadTexture("Units/Scv2.png"); //Sprites/Animations etc..
		scv_repair_fx = app->audio->loadFx("Audio/FX/SCV/Scv_repair.wav");

		//---------------Idle Animation-----------------
		idle_up.frames.push_back({ 0, 0, 72, 64 });
		idle_right.frames.push_back({ 288, 0, 72, 64 });
		idle_down.frames.push_back({ 576, 0, 72, 64 });
		idle_left.frames.push_back({ 864, 0, 72, 64 });
		//----------------------------------------------

		//--------------Walking Animations--------------
		walk_right_up.frames.push_back({ 144, 0, 72, 64 });
		walk_right_down.frames.push_back({ 432, 0, 72, 64 });
		walk_left_down.frames.push_back({ 720, 0, 72, 64 });
		walk_left_up.frames.push_back({ 1008, 0, 72, 64 });
		//----------------------------------------------

		//--------------Repair Animations---------------		
		repair_up.frames.push_back({ 0, 64, 72, 64 });
		repair_up.frames.push_back({ 0, 128, 72, 64 });
		repair_up.speed = 0.01f;
		repair_up.loop = true;

		repair_right_up.frames.push_back({ 144, 64, 72, 64 });
		repair_right_up.frames.push_back({ 144, 128, 72, 64 });
		repair_right_up.speed = 0.01f;
		repair_right_up.loop = true;

		repair_right.frames.push_back({ 288, 64, 72, 64 });
		repair_right.frames.push_back({ 288, 128, 72, 64 });
		repair_right.speed = 0.01f;
		repair_right.loop = true;

		repair_right_down.frames.push_back({ 432, 64, 72, 64 });
		repair_right_down.frames.push_back({ 432, 128, 72, 64 });
		repair_right_down.speed = 0.01f;
		repair_right_down.loop = true;

		repair_down.frames.push_back({ 576, 64, 72, 64 });
		repair_down.frames.push_back({ 576, 128, 72, 64 });
		repair_down.speed = 0.01f;
		repair_down.loop = true;

		repair_left_down.frames.push_back({ 720, 64, 72, 64 });
		repair_left_down.frames.push_back({ 720, 128, 72, 64 });
		repair_left_down.speed = 0.01f;
		repair_left_down.loop = true;

		repair_left.frames.push_back({ 864, 64, 72, 64 });
		repair_left.frames.push_back({ 864, 128, 72, 64 });
		repair_left.speed = 0.01f;
		repair_left.loop = true;

		repair_left_up.frames.push_back({ 1008, 64, 72, 64 });
		repair_left_up.frames.push_back({ 1008, 128, 72, 64 });
		repair_left_up.speed = 0.01f;
		repair_left_up.loop = true;
		//----------------------------------------------


		angle = 225.f;
		//current_animation = &idle_up;
		selection_type = { 28, 9, 32, 19 };
		circle_selection_offset = {-2, 0 };
		offset_life = { -13, 20 };
		// Colliders
		coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 30, 30 }, COLLIDER_BOMB);

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
						app->audio->playFx(scv_repair_fx);
						current_animation = &repair_up;
					}
					else
						current_animation = &idle_up;
				}

				else if (angle >= 45.f && angle < 67.5f)
				{
					if (state == REPAIR)
					{
						app->audio->playFx(scv_repair_fx);
						current_animation = &repair_right_up;
					}
					else
						current_animation = &walk_right_up;
				}

				else if (angle >= 90.f && angle < 112.5f)
				{
					if (state == REPAIR)
					{
						app->audio->playFx(scv_repair_fx);
						current_animation = &repair_right;
					}
					else
						current_animation = &idle_right;
				}

				else if (angle >= 135.f && angle < 157.5f)
				{
					if (state == REPAIR)
					{
						app->audio->playFx(scv_repair_fx);
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
						app->audio->playFx(scv_repair_fx);
						current_animation = &repair_down;
					}
					else
						current_animation = &idle_down;
				}

				else if (angle >= 225.f && angle < 247.5f)
				{
					if (state == REPAIR)
					{
						app->audio->playFx(scv_repair_fx);
						current_animation = &repair_left_down;
					}
					else
						current_animation = &walk_left_down;
				}

				else if (angle >= 270.f && angle < 292.5f)
				{
					if (state == REPAIR)
					{
						app->audio->playFx(scv_repair_fx);
						current_animation = &repair_left;
					}
					else
						current_animation = &idle_left;
				}

				else if (angle >= 315.f && angle < 337.5f)
				{
					if (state == REPAIR)
					{
						app->audio->playFx(scv_repair_fx);
						current_animation = &repair_left_up;
					}
					else
					current_animation = &walk_left_up;
				}
			}	
		}
			
		

	void draw()
	{
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}

};

#endif //__SCV_H__