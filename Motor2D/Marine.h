#ifndef __MARINE_H__
#define __MARINE_H__

#include "Unit.h"

class Marine : public Unit
{
public:
	//ROF
	// It must have a review to do spritesheets with render flip into Animation module https://wiki.libsdl.org/SDL_RendererFlip
	Animation	idle;
	Animation	idle_up;

	Animation   one;
	Animation   idle_right_up;
	Animation   three;

	Animation   right;
	Animation   five;
	Animation   idle_right_down;
	Animation   seven;

	Animation   down;
	Animation   nine;
	Animation   idle_left_down;
	Animation   eleven;

	Animation   left;
	Animation   thirdteen;
	Animation   idle_left_up;
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
		idle.frames.push_back({ 0, 0, 64, 64 });


		idle_up.frames.push_back({ 0, 0, 64, 64 });
		idle_up.frames.push_back({ 0, 256, 64, 64 });
		idle_up.frames.push_back({ 0, 320, 64, 64 });
		idle_up.frames.push_back({ 0, 384, 64, 64 });
		idle_up.frames.push_back({ 0, 448, 64, 64 });
		idle_up.frames.push_back({ 0, 512, 64, 64 });
		idle_up.frames.push_back({ 0, 576, 64, 64 });
		idle_up.frames.push_back({ 0, 640, 64, 64 });
		idle_up.frames.push_back({ 0, 704, 64, 64 });
		idle_up.frames.push_back({ 0, 768, 64, 64 });
		idle_up.speed = 0.05f;
		//one.frames.push_back({ 64, 0, 64, 64 });
		idle_right_up.frames.push_back({ 128, 0, 64, 64 });
		//three.frames.push_back({ 192, 0, 64, 64 });
		right.frames.push_back({ 256, 0, 64, 64 });
		//five.frames.push_back({ 320, 0, 64, 64 });
		idle_right_down.frames.push_back({ 384, 0, 64, 64 });
		//seven.frames.push_back({ 448, 0, 64, 64 });
		down.frames.push_back({ 512, 0, 64, 64 });
		//nine.frames.push_back({ 576, 0, 64, 64 });
		idle_left_down.frames.push_back({ 640, 0, 64, 64 });
		//eleven.frames.push_back({ 704, 0, 64, 64 });
		left.frames.push_back({ 768, 0, 64, 64 });
		//thirdteen.frames.push_back({ 832, 0, 64, 64 });
		idle_left_up.frames.push_back({ 896, 0, 64, 64 });
		//fifteen.frames.push_back({ 960, 0, 64, 64 });

		angle = -1;

		current_animation = &idle;

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
		// From 0 to 180 degrees

		if (angle >= 0.f && angle < 22.5f)
		{
			current_animation = &idle_up;
		}
		if (angle >= 22.5f && angle < 45.f)
		{
			current_animation = &one;
		}
		if (angle >= 45.f && angle < 67.5f)
		{
			current_animation = &idle_right_up;
		}
		if (angle >= 67.5f && angle < 90.f)
		{
			current_animation = &three;
		}
		if (angle >= 90.f && angle < 112.5f)
		{
			current_animation = &right;
		}
		if (angle >= 112.5f && angle < 135.f)
		{
			current_animation = &five;
		}
		if (angle >= 135.f && angle < 157.5f)
		{
			current_animation = &idle_right_down;
		}
		if (angle >= 157.5f && angle < 180.f)
		{
			current_animation = &seven;
		}
		// From 180 to 360 degrees
		if (angle >= 180.f && angle < 202.5f)
		{
			current_animation = &down;
		}
		if (angle >= 202.5f && angle < 225.f)
		{
			current_animation = &nine;
		}
		if (angle >= 225.f && angle < 247.5f)
		{
			current_animation = &idle_left_down;
		}
		if (angle >= 247.5f && angle < 270.f)
		{
			current_animation = &eleven;
		}
		if (angle >= 270.f && angle < 292.5f)
		{
			current_animation = &left;
		}
		if (angle >= 292.5f && angle < 315.f)
		{
			current_animation = &thirdteen;
		}
		if (angle >= 315.f && angle < 337.5f)
		{
			current_animation = &idle_left_up;
		}
		if (angle >= 337.5f && angle < 360.f)
		{
			current_animation = &fifteen;
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