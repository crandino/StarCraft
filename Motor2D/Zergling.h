#ifndef __ZERGLING_H__
#define __ZERGLING_H__

#include "Unit.h"

class Zergling : public Unit
{
public:

	// IDLE animations
	Animation idle_up;
	Animation idle_right_up;
	Animation idle_right;
	Animation idle_right_down;
	Animation idle_down;
	Animation idle_left_down;
	Animation idle_left;
	Animation idle_left_up;
	vector<Animation*> idle_animation_pack;

	// MOVING animations
	Animation walk_up;
	Animation walk_right_up;
	Animation walk_right;
	Animation walk_right_down;
	Animation walk_down;
	Animation walk_left_down;
	Animation walk_left;
	Animation walk_left_up;
	vector<Animation*> move_animation_pack;

	// ATTACK animations
	Animation attack_up;
	Animation attack_right_up;
	Animation attack_right;
	Animation attack_right_down;
	Animation attack_down;
	Animation attack_left_down;
	Animation attack_left;
	Animation attack_left_up;
	vector<Animation*> attack_animation_pack;

	// Dead animation
	Animation dead;

	Zergling(iPoint &p)
	{
		// Graphics
		tex = app->tex->loadTexture("Units/New_Zergling64.png");
		tex_width = tex_height = 64;

		//------------------Idle Animation------------------
		idle_right.frames.push_back({ 256, 0, 64, 64 });
		idle_animation_pack.push_back(&idle_right);

		idle_right_up.frames.push_back({ 128, 0, 64, 64 });
		idle_animation_pack.push_back(&idle_right_up);

		idle_up.frames.push_back({ 0, 0, 64, 64 });
		idle_animation_pack.push_back(&idle_up);

		idle_left_up.frames.push_back({ 896, 0, 64, 64 });
		idle_animation_pack.push_back(&idle_left_up);

		idle_left.frames.push_back({ 768, 0, 64, 64 });
		idle_animation_pack.push_back(&idle_left);

		idle_left_down.frames.push_back({ 640, 0, 64, 64 });
		idle_animation_pack.push_back(&idle_left_down);

		idle_down.frames.push_back({ 512, 0, 64, 64 });
		idle_animation_pack.push_back(&idle_down);

		idle_right_down.frames.push_back({ 384, 0, 64, 64 });
		idle_animation_pack.push_back(&idle_right_down);

		//-----------------Walking Animation---------------
		walk_right.frames.push_back({ 256, 256, 64, 64 });
		walk_right.frames.push_back({ 256, 320, 64, 64 });
		walk_right.frames.push_back({ 256, 384, 64, 64 });
		walk_right.frames.push_back({ 256, 448, 64, 64 });
		walk_right.frames.push_back({ 256, 512, 64, 64 });
		walk_right.frames.push_back({ 256, 576, 64, 64 });
		walk_right.frames.push_back({ 256, 640, 64, 64 });
		walk_right.frames.push_back({ 256, 704, 64, 64 });
		walk_right.speed = 0.02f;
		move_animation_pack.push_back(&walk_right);

		walk_right_up.frames.push_back({ 128, 256, 64, 64 });
		walk_right_up.frames.push_back({ 128, 320, 64, 64 });
		walk_right_up.frames.push_back({ 128, 384, 64, 64 });
		walk_right_up.frames.push_back({ 128, 448, 64, 64 });
		walk_right_up.frames.push_back({ 128, 512, 64, 64 });
		walk_right_up.frames.push_back({ 128, 576, 64, 64 });
		walk_right_up.frames.push_back({ 128, 640, 64, 64 });
		walk_right_up.frames.push_back({ 128, 704, 64, 64 });
		walk_right_up.speed = 0.02f;
		move_animation_pack.push_back(&walk_right_up);

		walk_up.frames.push_back({ 0, 256, 64, 64 });
		walk_up.frames.push_back({ 0, 320, 64, 64 });
		walk_up.frames.push_back({ 0, 384, 64, 64 });
		walk_up.frames.push_back({ 0, 448, 64, 64 });
		walk_up.frames.push_back({ 0, 512, 64, 64 });
		walk_up.frames.push_back({ 0, 576, 64, 64 });
		walk_up.frames.push_back({ 0, 640, 64, 64 });
		walk_up.frames.push_back({ 0, 704, 64, 64 });
		walk_up.speed = 0.02f;
		move_animation_pack.push_back(&walk_up);

		walk_left_up.frames.push_back({ 896, 256, 64, 64 });
		walk_left_up.frames.push_back({ 896, 320, 64, 64 });
		walk_left_up.frames.push_back({ 896, 384, 64, 64 });
		walk_left_up.frames.push_back({ 896, 448, 64, 64 });
		walk_left_up.frames.push_back({ 896, 512, 64, 64 });
		walk_left_up.frames.push_back({ 896, 576, 64, 64 });
		walk_left_up.frames.push_back({ 896, 640, 64, 64 });
		walk_left_up.frames.push_back({ 896, 704, 64, 64 });
		walk_left_up.speed = 0.02f;
		move_animation_pack.push_back(&walk_left_up);

		walk_left.frames.push_back({ 768, 256, 64, 64 });
		walk_left.frames.push_back({ 768, 320, 64, 64 });
		walk_left.frames.push_back({ 768, 384, 64, 64 });
		walk_left.frames.push_back({ 768, 448, 64, 64 });
		walk_left.frames.push_back({ 768, 512, 64, 64 });
		walk_left.frames.push_back({ 768, 576, 64, 64 });
		walk_left.frames.push_back({ 768, 640, 64, 64 });
		walk_left.frames.push_back({ 768, 704, 64, 64 });
		walk_left.speed = 0.02f;
		move_animation_pack.push_back(&walk_left);

		walk_left_down.frames.push_back({ 640, 256, 64, 64 });
		walk_left_down.frames.push_back({ 640, 320, 64, 64 });
		walk_left_down.frames.push_back({ 640, 384, 64, 64 });
		walk_left_down.frames.push_back({ 640, 448, 64, 64 });
		walk_left_down.frames.push_back({ 640, 512, 64, 64 });
		walk_left_down.frames.push_back({ 640, 576, 64, 64 });
		walk_left_down.frames.push_back({ 640, 640, 64, 64 });
		walk_left_down.frames.push_back({ 640, 704, 64, 64 });
		walk_left_down.speed = 0.02f;
		move_animation_pack.push_back(&walk_left_down);

		walk_down.frames.push_back({ 512, 256, 64, 64 });
		walk_down.frames.push_back({ 512, 320, 64, 64 });
		walk_down.frames.push_back({ 512, 384, 64, 64 });
		walk_down.frames.push_back({ 512, 448, 64, 64 });
		walk_down.frames.push_back({ 512, 512, 64, 64 });
		walk_down.frames.push_back({ 512, 576, 64, 64 });
		walk_down.frames.push_back({ 512, 640, 64, 64 });
		walk_down.frames.push_back({ 512, 704, 64, 64 });
		walk_down.speed = 0.02f;
		move_animation_pack.push_back(&walk_down);

		walk_right_down.frames.push_back({ 384, 256, 64, 64 });
		walk_right_down.frames.push_back({ 384, 320, 64, 64 });
		walk_right_down.frames.push_back({ 384, 384, 64, 64 });
		walk_right_down.frames.push_back({ 384, 448, 64, 64 });
		walk_right_down.frames.push_back({ 384, 512, 64, 64 });
		walk_right_down.frames.push_back({ 384, 576, 64, 64 });
		walk_right_down.frames.push_back({ 384, 640, 64, 64 });
		walk_right_down.frames.push_back({ 384, 704, 64, 64 });
		walk_right_down.speed = 0.02f;
		move_animation_pack.push_back(&walk_right_down);

		//-----------------Attack Animation---------------
		attack_right.frames.push_back({ 256, 64, 64, 64 });
		attack_right.frames.push_back({ 256, 128, 64, 64 });
		attack_right.frames.push_back({ 256, 192, 64, 64 });
		attack_right.speed = 0.008f;
		attack_animation_pack.push_back(&attack_right);

		attack_right_up.frames.push_back({ 128, 64, 64, 64 });
		attack_right_up.frames.push_back({ 128, 128, 64, 64 });
		attack_right_up.frames.push_back({ 128, 192, 64, 64 });
		attack_right_up.speed = 0.008f;
		attack_animation_pack.push_back(&attack_right_up);

		attack_up.frames.push_back({ 0, 64, 64, 64 });
		attack_up.frames.push_back({ 0, 128, 64, 64 });
		attack_up.frames.push_back({ 0, 192, 64, 64 });
		attack_up.speed = 0.008f;
		attack_animation_pack.push_back(&attack_up);

		attack_left_up.frames.push_back({ 896, 64, 64, 64 });
		attack_left_up.frames.push_back({ 896, 128, 64, 64 });
		attack_left_up.frames.push_back({ 896, 192, 64, 64 });
		attack_left_up.speed = 0.008f;
		attack_animation_pack.push_back(&attack_left_up);

		attack_left.frames.push_back({ 768, 64, 64, 64 });
		attack_left.frames.push_back({ 768, 128, 64, 64 });
		attack_left.frames.push_back({ 768, 192, 64, 64 });
		attack_left.speed = 0.008f;
		attack_animation_pack.push_back(&attack_left);

		attack_left_down.frames.push_back({ 640, 64, 64, 64 });
		attack_left_down.frames.push_back({ 640, 128, 64, 64 });
		attack_left_down.frames.push_back({ 640, 192, 64, 64 });
		attack_left_down.speed = 0.008f;
		attack_animation_pack.push_back(&attack_left_down);

		attack_down.frames.push_back({ 512, 64, 64, 64 });
		attack_down.frames.push_back({ 512, 128, 64, 64 });
		attack_down.frames.push_back({ 512, 192, 64, 64 });
		attack_down.speed = 0.008f;
		attack_animation_pack.push_back(&attack_down);

		attack_right_down.frames.push_back({ 384, 64, 64, 64 });
		attack_right_down.frames.push_back({ 384, 128, 64, 64 });
		attack_right_down.frames.push_back({ 384, 192, 64, 64 });
		attack_right_down.speed = 0.008f;
		attack_animation_pack.push_back(&attack_right_down);

		//-----------------Death Animation---------------
		dead.frames.push_back({ 0, 1088, 64, 64 });
		dead.frames.push_back({ 64, 1088, 64, 64 });
		dead.frames.push_back({ 128, 1088, 64, 64 });
		dead.frames.push_back({ 192, 1088, 64, 64 });
		dead.frames.push_back({ 256, 1088, 64, 64 });
		dead.frames.push_back({ 320, 1088, 64, 64 });
		dead.frames.push_back({ 384, 1088, 64, 64 });
		dead.speed = 0.01f;
		//------------------------------------------------
		current_animation = &idle_down;

		// Positions and information
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		center = { (float)p.x, (float)p.y };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

		// Collider
		coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 24, 26 }, COLLIDER_UNIT, app->entity_manager);
		collider_offset = { -12, -14 };

		// Characterization and behaviour
		faction = COMPUTER;
		specialization = ZERGLING;
		flying = false;

		// UI paramters
		selection_type = { 3, 4, 22, 13 };
		circle_selection_offset = { 0, -1 };
		offset_life = { -19, 16 };

		// Lifes attributes		
		max_hp = 40;
		current_hp = 40.0f;
		max_hp_bars = 6;

		// Attack values and properties
		range_of_vision = 200;
		range_to_attack = 32;
		damage = 3.0f;
		attack_frequency = 500.0f;

		// PathFinding and movement variables
		speed = 12.0f;
	}

	~Zergling()
	{

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
		case(MOVE_ALERT_TO_ATTACK) :
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
		case(WAITING_PATH_MOVE) :
		{
			int num_animation = angle / (360 / idle_animation_pack.size());
			current_animation = &(*idle_animation_pack.at(num_animation));
			break;
		}
		case(WAITING_PATH_MOVE_ALERT) :
		{
			int num_animation = angle / (360 / idle_animation_pack.size());
			current_animation = &(*idle_animation_pack.at(num_animation));
			break;
		}
		case(WAITING_PATH_MOVE_ALERT_TO_ATTACK) :
		{
			int num_animation = angle / (360 / idle_animation_pack.size());
			current_animation = &(*idle_animation_pack.at(num_animation));
			break;
		}
		}
	}
};

#endif !__ZERGLING_H__