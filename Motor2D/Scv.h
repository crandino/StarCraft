//#ifndef __SCV_H__
//#define __SCV_H__
//
//#include "Unit.h"
//
//class Unit;
//class Scv : public Unit
//{
//public:
//	
//	Animation	idle_up;
//	Animation   idle_right;
//	Animation	idle_down;
//	Animation	idle_left;
//	Animation	walk_up;
//	Animation   one;
//	Animation   walk_right_up;
//	Animation   three;
//	Animation   walk_right;
//	Animation   five;
//	Animation   walk_right_down;
//	Animation   seven;
//	Animation   walk_down;
//	Animation   nine;
//	Animation   walk_left_down;
//	Animation   eleven;
//	Animation   walk_left;
//	Animation   thirdteen;
//	Animation   walk_left_up;
//	Animation   fifteen;
//
//	Scv(iPoint &p)
//	{
//		// Positions and dimensions
//		center = { (float)p.x, (float)p.y };
//		tex_width = 72;
//		tex_height = 64;
//		collider_offset = { 10, 14 };
//		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
//		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);
//		// Animations
//		tex = app->tex->loadTexture("Units/Scv2.png"); //Sprites/Animations etc..
//
//		//---------------Idle Animation-----------------
//		idle_up.frames.push_back({ 0, 0, 72, 64 });
//		idle_right.frames.push_back({ 288, 0, 72, 64 });
//		idle_down.frames.push_back({ 576, 0, 72, 64 });
//		idle_left.frames.push_back({ 864, 0, 72, 64 });
//		//----------------------------------------------
//
//		//--------------Walking Animations--------------
//		walk_right_up.frames.push_back({ 144, 0, 72, 64 });
//		walk_right_down.frames.push_back({ 432, 0, 72, 64 });
//		walk_left_down.frames.push_back({ 720, 0, 72, 64 });
//		walk_left_up.frames.push_back({ 1008, 0, 72, 64 });
//		//----------------------------------------------
//
//		angle = -1;
//		current_animation = &idle_up;
//
//		// Colliders
//		coll = app->collision->addCollider({ center.x - collider_offset.x, center.y - collider_offset.y, 22, 30 }, COLLIDER_BOMB);
//
//		// Another stuff
//
//		faction = PLAYER;
//		flying = false;
//
//		max_hp = 40;
//		current_hp = 40.0f;
//		max_hp_bars = 6;
//
//		//current_hp_bars = 6;
//
//		speed = 10;
//
//
//		direction.create(1, 1, p.x, p.y);
//		direction.setAngle(0.f);
//	}
//
//	//ROF method to check the orientation of the marine
//	void checkAngle()
//	{
//
//		if (angle > 360)
//		{
//			angle -= 360.f;
//		}
//
//		if (path.size() > 0)
//		{
//			// From 0 to 180 degrees
//
//			if (angle >= 0.f && angle < 22.5f)
//			{
//				current_animation = &idle_up;
//			}
//		/*	if (angle >= 22.5f && angle < 45.f)
//			{
//				current_animation = &one;
//			}*/
//			if (angle >= 45.f && angle < 67.5f)
//			{
//				current_animation = &walk_right_up;
//			}
//		/*	if (angle >= 67.5f && angle < 90.f)
//			{
//				current_animation = &three;
//			}*/
//			if (angle >= 90.f && angle < 112.5f)
//			{
//				current_animation = &walk_right;
//			}
//		/*	if (angle >= 112.5f && angle < 135.f)
//			{
//				current_animation = &five;
//			}*/
//			if (angle >= 135.f && angle < 157.5f)
//			{
//				current_animation = &walk_right_down;
//			}
//			//if (angle >= 157.5f && angle < 180.f)
//			//{
//			//	current_animation = &seven;
//			//}
//			// From 180 to 360 degrees
//			if (angle >= 180.f && angle < 202.5f)
//			{
//				current_animation = &walk_down;
//			}
//		/*	if (angle >= 202.5f && angle < 225.f)
//			{
//				current_animation = &nine;
//			}*/
//			if (angle >= 225.f && angle < 247.5f)
//			{
//				current_animation = &walk_left_down;
//			}
//	/*		if (angle >= 247.5f && angle < 270.f)
//			{
//				current_animation = &eleven;
//			}*/
//			if (angle >= 270.f && angle < 292.5f)
//			{
//				current_animation = &walk_left;
//			}
//		/*	if (angle >= 292.5f && angle < 315.f)
//			{
//				current_animation = &thirdteen;
//			}*/
//			if (angle >= 315.f && angle < 337.5f)
//			{
//				current_animation = &walk_left_up;
//			}
//			/*if (angle >= 337.5f && angle < 360.f)
//			{
//				current_animation = &fifteen;
//			}*/
//		}
//	/*	else
//		{
//			if (angle >= 0.f && angle < 22.5f)
//			{
//				current_animation = &idle_up;
//			}
//			if (angle >= 90.f && angle < 112.5f)
//			{
//				current_animation = &idle_right;
//			}
//			if (angle >= 180.f && angle < 202.5f)
//			{
//				current_animation = &idle_down;
//			}
//			if (angle >= 270.f && angle < 292.5f)
//			{
//				current_animation = &idle_left;
//			}
//
//		}*/
//
//	}
//
//	void draw()
//	{
//		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
//	}
//
//	bool update(float dt)
//	{
//		coll->setPos(center.x - 10, center.y - 14);
//		if (has_target) move(dt);
//
//
//
//		return true;
//	}
//};
//
//#endif __SCV_H__