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
		
	    //---------------Idle Animation-----------------
		idle_up.frames.push_back({ 0, 0, 64, 64 });
		idle_up.frames.push_back({ 0, 64, 64, 64 });
		idle_up.frames.push_back({ 0, 128, 64, 64 });
		idle_up.frames.push_back({ 0, 64, 64, 64 });
		idle_up.frames.push_back({ 0, 0, 64, 64 });
		idle_up.speed = 0.02f;
		idle_up.loop = true;

		idle_right.frames.push_back({ 256, 0, 64, 64 });
		idle_right.frames.push_back({ 256, 64, 64, 64 });
		idle_right.frames.push_back({ 256, 128, 64, 64 });
		idle_right.frames.push_back({ 256, 64, 64, 64 });
		idle_right.frames.push_back({ 256, 0, 64, 64 });
		idle_right.speed = 0.02f;
		idle_right.loop = true;

		idle_down.frames.push_back({ 448, 0, 64, 64 });
		idle_down.frames.push_back({ 448, 64, 64, 64 });
		idle_down.frames.push_back({ 448, 128, 64, 64 });
		idle_down.frames.push_back({ 448, 64, 64, 64 });
		idle_down.frames.push_back({ 448, 0, 64, 64 });
		idle_down.speed = 0.02f;
		idle_down.loop = true;

		idle_left.frames.push_back({ 768, 0, 64, 64 });
		idle_left.frames.push_back({ 768, 64, 64, 64 });
		idle_left.frames.push_back({ 768, 128, 64, 64 });
		idle_left.frames.push_back({ 768, 64, 64, 64 });
		idle_left.frames.push_back({ 768, 0, 64, 64 });
		idle_left.speed = 0.02f;
		idle_left.loop = true;
		//----------------------------------------------

		//--------------Walking Animations--------------
		walk_up.frames.push_back({ 0, 0, 64, 64 });
		walk_up.frames.push_back({ 0, 256, 64, 64 });
		walk_up.frames.push_back({ 0, 320, 64, 64 });
		walk_up.frames.push_back({ 0, 384, 64, 64 });
		walk_up.frames.push_back({ 0, 448, 64, 64 });
		walk_up.frames.push_back({ 0, 512, 64, 64 });
		walk_up.frames.push_back({ 0, 576, 64, 64 });
		walk_up.frames.push_back({ 0, 640, 64, 64 });
		walk_up.frames.push_back({ 0, 704, 64, 64 });
		walk_up.frames.push_back({ 0, 768, 64, 64 });
		walk_up.speed = 0.05f;

		//one.frames.push_back({ 64, 0, 64, 64 });
		walk_right_up.frames.push_back({ 128, 0, 64, 64 });
		walk_right_up.frames.push_back({ 128, 256, 64, 64 });
		walk_right_up.frames.push_back({ 128, 320, 64, 64 });
		walk_right_up.frames.push_back({ 128, 384, 64, 64 });
		walk_right_up.frames.push_back({ 128, 448, 64, 64 });
		walk_right_up.frames.push_back({ 128, 512, 64, 64 });
		walk_right_up.frames.push_back({ 128, 576, 64, 64 });
		walk_right_up.frames.push_back({ 128, 640, 64, 64 });
		walk_right_up.frames.push_back({ 128, 704, 64, 64 });
		walk_right_up.frames.push_back({ 128, 768, 64, 64 });
		walk_right_up.speed = 0.05f;

		//three.frames.push_back({ 192, 0, 64, 64 });
		walk_right.frames.push_back({ 256, 0, 64, 64 });
		walk_right.frames.push_back({ 256, 256, 64, 64 });
		walk_right.frames.push_back({ 256, 320, 64, 64 });
		walk_right.frames.push_back({ 256, 384, 64, 64 });
		walk_right.frames.push_back({ 256, 448, 64, 64 });
		walk_right.frames.push_back({ 256, 512, 64, 64 });
		walk_right.frames.push_back({ 256, 576, 64, 64 });
		walk_right.frames.push_back({ 256, 640, 64, 64 });
		walk_right.frames.push_back({ 256, 704, 64, 64 });
		walk_right.frames.push_back({ 256, 768, 64, 64 });
		walk_right.speed = 0.05f;

		//five.frames.push_back({ 320, 0, 64, 64 });
		walk_right_down.frames.push_back({ 384, 0, 64, 64 });
		walk_right_down.frames.push_back({ 384, 256, 64, 64 });
		walk_right_down.frames.push_back({ 384, 320, 64, 64 });
		walk_right_down.frames.push_back({ 384, 384, 64, 64 });
		walk_right_down.frames.push_back({ 384, 448, 64, 64 });
		walk_right_down.frames.push_back({ 384, 512, 64, 64 });
		walk_right_down.frames.push_back({ 384, 576, 64, 64 });
		walk_right_down.frames.push_back({ 384, 640, 64, 64 });
		walk_right_down.frames.push_back({ 384, 704, 64, 64 });
		walk_right_down.frames.push_back({ 384, 768, 64, 64 });
		walk_right_down.speed = 0.05f;

		//seven.frames.push_back({ 448, 0, 64, 64 });
		walk_down.frames.push_back({ 512, 0, 64, 64 });
		walk_down.frames.push_back({ 512, 256, 64, 64 });
		walk_down.frames.push_back({ 512, 320, 64, 64 });
		walk_down.frames.push_back({ 512, 384, 64, 64 });
		walk_down.frames.push_back({ 512, 448, 64, 64 });
		walk_down.frames.push_back({ 512, 512, 64, 64 });
		walk_down.frames.push_back({ 512, 576, 64, 64 });
		walk_down.frames.push_back({ 512, 640, 64, 64 });
		walk_down.frames.push_back({ 512, 704, 64, 64 });
		walk_down.frames.push_back({ 512, 768, 64, 64 });
		walk_down.speed = 0.05f;
		//nine.frames.push_back({ 576, 0, 64, 64 });
		walk_left_down.frames.push_back({ 640, 0, 64, 64 });
		walk_left_down.frames.push_back({ 640, 256, 64, 64 });
		walk_left_down.frames.push_back({ 640, 320, 64, 64 });
		walk_left_down.frames.push_back({ 640, 384, 64, 64 });
		walk_left_down.frames.push_back({ 640, 448, 64, 64 });
		walk_left_down.frames.push_back({ 640, 512, 64, 64 });
		walk_left_down.frames.push_back({ 640, 576, 64, 64 });
		walk_left_down.frames.push_back({ 640, 640, 64, 64 });
		walk_left_down.frames.push_back({ 640, 704, 64, 64 });
		walk_left_down.frames.push_back({ 640, 768, 64, 64 });
		walk_left_down.speed = 0.05f;
		//eleven.frames.push_back({ 704, 0, 64, 64 });
		walk_left.frames.push_back({ 768, 0, 64, 64 });
		walk_left.frames.push_back({ 768, 256, 64, 64 });
		walk_left.frames.push_back({ 768, 320, 64, 64 });
		walk_left.frames.push_back({ 768, 384, 64, 64 });
		walk_left.frames.push_back({ 768, 448, 64, 64 });
		walk_left.frames.push_back({ 768, 512, 64, 64 });
		walk_left.frames.push_back({ 768, 576, 64, 64 });
		walk_left.frames.push_back({ 768, 640, 64, 64 });
		walk_left.frames.push_back({ 768, 704, 64, 64 });
		walk_left.frames.push_back({ 768, 768, 64, 64 });
		walk_left.speed = 0.05f;
		//thirdteen.frames.push_back({ 832, 0, 64, 64 });
		walk_left_up.frames.push_back({ 896, 0, 64, 64 });
		walk_left_up.frames.push_back({ 896, 256, 64, 64 });
		walk_left_up.frames.push_back({ 896, 320, 64, 64 });
		walk_left_up.frames.push_back({ 896, 384, 64, 64 });
		walk_left_up.frames.push_back({ 896, 448, 64, 64 });
		walk_left_up.frames.push_back({ 896, 512, 64, 64 });
		walk_left_up.frames.push_back({ 896, 576, 64, 64 });
		walk_left_up.frames.push_back({ 896, 640, 64, 64 });
		walk_left_up.frames.push_back({ 896, 704, 64, 64 });
		walk_left_up.frames.push_back({ 896, 768, 64, 64 });
		walk_left_up.speed = 0.05f;
		//fifteen.frames.push_back({ 960, 0, 64, 64 });
		//----------------------------------------------

		angle = -1;
		current_animation = &idle_up;

		// Colliders
		coll = app->collision->addCollider({ center.x - collider_offset.x, center.y - collider_offset.y, 22, 30 }, COLLIDER_BOMB);

		// Another stuff
		
		faction = PLAYER;
		flying = false;

		max_hp = 40;
		current_hp = 40.0f;
		max_hp_bars = 6;
		
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

		if (path.size() > 0)
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
		if (has_target) move(dt);
	


		return true;
	}
};

#endif __MARINE_H__