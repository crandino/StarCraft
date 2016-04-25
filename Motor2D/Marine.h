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
	Animation   walk_right_up;
	Animation   walk_right;
	Animation   walk_right_down;
	Animation   walk_down;
	Animation   walk_left_down;
	Animation   walk_left;
	Animation   walk_left_up;

	Animation	attack_up;
	Animation	attack_right_up;
	Animation	attack_right;
	Animation	attack_right_down;
	Animation	attack_down;
	Animation	attack_left_down;
	Animation	attack_left;
	Animation	attack_left_up;

	Animation	dead;

	vector<Animation*> idle_animation_pack;
	vector<Animation*> move_animation_pack;
	vector<Animation*> attack_animation_pack;

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
		
		//#include "Marine_animations.h";
		//---------------Idle Animation----------------
		idle_right.frames.push_back({ 256, 0, 64, 64 });
		idle_right.frames.push_back({ 256, 64, 64, 64 });
		idle_right.frames.push_back({ 256, 128, 64, 64 });
		idle_right.frames.push_back({ 256, 64, 64, 64 });
		idle_right.frames.push_back({ 256, 0, 64, 64 });
		idle_right.speed = 0.005f;
		idle_right.loop = true;
		idle_animation_pack.push_back(&idle_right);

		idle_right_up.frames.push_back({ 128, 0, 64, 64 });
		idle_right_up.frames.push_back({ 128, 64, 64, 64 });
		idle_right_up.frames.push_back({ 128, 128, 64, 64 });
		idle_right_up.frames.push_back({ 128, 64, 64, 64 });
		idle_right_up.frames.push_back({ 128, 0, 64, 64 });
		idle_right_up.speed = 0.005f;
		idle_right_up.loop = true;
		idle_animation_pack.push_back(&idle_right_up);

		idle_up.frames.push_back({ 0, 0, 64, 64 });
		idle_up.frames.push_back({ 0, 64, 64, 64 });
		idle_up.frames.push_back({ 0, 128, 64, 64 });
		idle_up.frames.push_back({ 0, 64, 64, 64 });
		idle_up.frames.push_back({ 0, 0, 64, 64 });
		idle_up.speed = 0.005f;
		idle_up.loop = true;
		idle_animation_pack.push_back(&idle_up);

		idle_left_up.frames.push_back({ 960, 0, 64, 64 });
		idle_left_up.frames.push_back({ 960, 64, 64, 64 });
		idle_left_up.frames.push_back({ 960, 128, 64, 64 });
		idle_left_up.frames.push_back({ 960, 64, 64, 64 });
		idle_left_up.frames.push_back({ 960, 0, 64, 64 });
		idle_left_up.speed = 0.005f;
		idle_left_up.loop = true;
		idle_animation_pack.push_back(&idle_left_up);

		idle_left.frames.push_back({ 768, 0, 64, 64 });
		idle_left.frames.push_back({ 768, 64, 64, 64 });
		idle_left.frames.push_back({ 768, 128, 64, 64 });
		idle_left.frames.push_back({ 768, 64, 64, 64 });
		idle_left.frames.push_back({ 768, 0, 64, 64 });
		idle_left.speed = 0.005f;
		idle_left.loop = true;
		idle_animation_pack.push_back(&idle_left);

		idle_left_down.frames.push_back({ 640, 0, 64, 64 });
		idle_left_down.frames.push_back({ 640, 64, 64, 64 });
		idle_left_down.frames.push_back({ 640, 128, 64, 64 });
		idle_left_down.frames.push_back({ 640, 64, 64, 64 });
		idle_left_down.frames.push_back({ 640, 0, 64, 64 });
		idle_left_down.speed = 0.005f;
		idle_left_down.loop = true;
		idle_animation_pack.push_back(&idle_left_down);

		idle_down.frames.push_back({ 448, 0, 64, 64 });
		idle_down.frames.push_back({ 448, 64, 64, 64 });
		idle_down.frames.push_back({ 448, 128, 64, 64 });
		idle_down.frames.push_back({ 448, 64, 64, 64 });
		idle_down.frames.push_back({ 448, 0, 64, 64 });
		idle_down.speed = 0.005f;
		idle_down.loop = true;
		idle_animation_pack.push_back(&idle_down);

		idle_right_down.frames.push_back({ 384, 0, 64, 64 });
		idle_right_down.frames.push_back({ 384, 64, 64, 64 });
		idle_right_down.frames.push_back({ 384, 128, 64, 64 });
		idle_right_down.frames.push_back({ 384, 64, 64, 64 });
		idle_right_down.frames.push_back({ 384, 0, 64, 64 });
		idle_right_down.speed = 0.005f;
		idle_right_down.loop = true;
		idle_animation_pack.push_back(&idle_right_down);
		//----------------------------------------------

		//--------------Walking Animations--------------
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
		walk_right.speed = 0.02f;
		move_animation_pack.push_back(&walk_right);

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
		walk_right_up.speed = 0.02f;
		move_animation_pack.push_back(&walk_right_up);

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
		walk_up.speed = 0.02f;
		move_animation_pack.push_back(&walk_up);

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
		walk_left_up.speed = 0.02f;
		move_animation_pack.push_back(&walk_left_up);

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
		walk_left.speed = 0.02f;
		move_animation_pack.push_back(&walk_left);

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
		walk_left_down.speed = 0.02f;
		move_animation_pack.push_back(&walk_left_down);

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
		walk_down.speed = 0.02f;
		move_animation_pack.push_back(&walk_down);

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
		walk_right_down.speed = 0.02f;
		move_animation_pack.push_back(&walk_right_down);
		//----------------------------------------------

		//-----------MARINE ATTACK----------------------
		attack_right.frames.push_back({ 256, 128, 64, 64 });
		attack_right.frames.push_back({ 256, 192, 64, 64 });
		attack_right.speed = 0.01f;
		attack_right.loop = true;
		attack_animation_pack.push_back(&attack_right);

		attack_right_up.frames.push_back({ 128, 128, 64, 64 });
		attack_right_up.frames.push_back({ 128, 192, 64, 64 });
		attack_right_up.speed = 0.01f;
		attack_right_up.loop = true;
		attack_animation_pack.push_back(&attack_right_up);

		attack_up.frames.push_back({ 0, 128, 64, 64 });
		attack_up.frames.push_back({ 0, 192, 64, 64 });
		attack_up.speed = 0.01f;
		attack_up.loop = true;
		attack_animation_pack.push_back(&attack_up);

		attack_left_up.frames.push_back({ 896, 128, 64, 64 });
		attack_left_up.frames.push_back({ 896, 192, 64, 64 });
		attack_left_up.speed = 0.01f;
		attack_left_up.loop = true;
		attack_animation_pack.push_back(&attack_left_up);		

		attack_left.frames.push_back({ 768, 128, 64, 64 });
		attack_left.frames.push_back({ 768, 192, 64, 64 });
		attack_left.speed = 0.01f;
		attack_left.loop = true;
		attack_animation_pack.push_back(&attack_left);

		attack_left_down.frames.push_back({ 640, 128, 64, 64 });
		attack_left_down.frames.push_back({ 640, 192, 64, 64 });
		attack_left_down.speed = 0.01f;
		attack_left_down.loop = true;
		attack_animation_pack.push_back(&attack_left_down);

		attack_down.frames.push_back({ 512, 128, 64, 64 });
		attack_down.frames.push_back({ 512, 192, 64, 64 });
		attack_down.speed = 0.01f;
		attack_down.loop = true;
		attack_animation_pack.push_back(&attack_down);

		attack_right_down.frames.push_back({ 384, 128, 64, 64 });
		attack_right_down.frames.push_back({ 384, 192, 64, 64 });
		attack_right_down.speed = 0.01f;
		attack_right_down.loop = true;
		attack_animation_pack.push_back(&attack_right_down);
		//----------------------------------------------

		//------------MARINE DEAD-----------------------
		dead.frames.push_back({ 0, 832, 64, 64 });
		dead.frames.push_back({ 64, 832, 64, 64 });
		dead.frames.push_back({ 128, 832, 64, 64 });
		dead.frames.push_back({ 192, 832, 64, 64 });
		dead.frames.push_back({ 256, 832, 64, 64 });
		dead.frames.push_back({ 320, 832, 64, 64 });
		dead.frames.push_back({ 384, 832, 64, 64 });
		dead.frames.push_back({ 448, 832, 64, 64 });
		dead.speed = 0.01f;
		//----------------------------------------------

		angle = 0;
		current_animation = &idle_up;
	
		// Colliders
		coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 22, 30 }, COLLIDER_UNIT, app->entity_manager);

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

		range_of_vision = 300;
		range_to_attack = 100;
		damage = 5.0f;
		attack_delay = 200.0f;
		time_to_die = 500.0f;
		
		speed = 10.0f;
		
		direction.create(1, 1, p.x, p.y);
		direction.setAngle(0.f);
	}

	// Method that assign an animation according to its orientation
	void setAnimationFromDirection()
	{
		switch (state)
		{
		case(IDLE) :
			{
				int num_animation = angle / (360 / idle_animation_pack.size());
				current_animation = &(*idle_animation_pack.at(num_animation));
				break;
			}
		case(ATTACK) :
			{
				int num_animation = angle / (360 / attack_animation_pack.size());
				current_animation = &(*attack_animation_pack.at(num_animation));
				break;
			}
		case(MOVE) :
		case(MOVE_ALERT) :
			{
				int num_animation = angle / (360 / move_animation_pack.size());
				current_animation = &(*move_animation_pack.at(num_animation));
				break;
			}
		case(DYING) :
			{
				current_animation = &dead;
				break;
			}
		}
	}
};

#endif __MARINE_H__