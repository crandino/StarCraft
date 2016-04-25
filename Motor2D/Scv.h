#ifndef __SCV_H__
#define __SCV_H__

#include "Unit.h"

class Scv : public Unit
{
public:

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

	vector<Animation*> move_animation_pack;
	vector<Animation*> repair_animation_pack;

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
		
		//---------------Idle and Walking Animation-----------------
		walk_right.frames.push_back({ 288, 0, 72, 64 });
		move_animation_pack.push_back(&walk_right);

		walk_right_up.frames.push_back({ 144, 0, 72, 64 });
		move_animation_pack.push_back(&walk_right_up);

		walk_up.frames.push_back({ 0, 0, 72, 64 });
		move_animation_pack.push_back(&walk_up);

		walk_left_up.frames.push_back({ 1008, 0, 72, 64 });
		move_animation_pack.push_back(&walk_left_up);

		walk_left.frames.push_back({ 864, 0, 72, 64 });
		move_animation_pack.push_back(&walk_left);

		walk_left_down.frames.push_back({ 720, 0, 72, 64 });
		move_animation_pack.push_back(&walk_left_down);

		walk_down.frames.push_back({ 576, 0, 72, 64 });
		move_animation_pack.push_back(&walk_down);

		walk_right_down.frames.push_back({ 432, 0, 72, 64 });
		move_animation_pack.push_back(&walk_right_down);

		//--------------Repair Animations---------------		
		repair_right.frames.push_back({ 288, 64, 72, 64 });
		repair_right.frames.push_back({ 288, 128, 72, 64 });
		repair_right.speed = 0.01f;
		repair_right.loop = true;
		repair_animation_pack.push_back(&repair_right);

		repair_right_up.frames.push_back({ 144, 64, 72, 64 });
		repair_right_up.frames.push_back({ 144, 128, 72, 64 });
		repair_right_up.speed = 0.01f;
		repair_right_up.loop = true;
		repair_animation_pack.push_back(&repair_right_up);

		repair_up.frames.push_back({ 0, 64, 72, 64 });
		repair_up.frames.push_back({ 0, 128, 72, 64 });
		repair_up.speed = 0.01f;
		repair_up.loop = true;
		repair_animation_pack.push_back(&repair_up);

		repair_left_up.frames.push_back({ 1008, 64, 72, 64 });
		repair_left_up.frames.push_back({ 1008, 128, 72, 64 });
		repair_left_up.speed = 0.01f;
		repair_left_up.loop = true;
		repair_animation_pack.push_back(&repair_left_up);

		repair_left.frames.push_back({ 864, 64, 72, 64 });
		repair_left.frames.push_back({ 864, 128, 72, 64 });
		repair_left.speed = 0.01f;
		repair_left.loop = true;
		repair_animation_pack.push_back(&repair_left);

		repair_left_down.frames.push_back({ 720, 64, 72, 64 });
		repair_left_down.frames.push_back({ 720, 128, 72, 64 });
		repair_left_down.speed = 0.01f;
		repair_left_down.loop = true;
		repair_animation_pack.push_back(&repair_left_down);

		repair_down.frames.push_back({ 576, 64, 72, 64 });
		repair_down.frames.push_back({ 576, 128, 72, 64 });
		repair_down.speed = 0.01f;
		repair_down.loop = true;
		repair_animation_pack.push_back(&repair_down);

		repair_right_down.frames.push_back({ 432, 64, 72, 64 });
		repair_right_down.frames.push_back({ 432, 128, 72, 64 });
		repair_right_down.speed = 0.01f;
		repair_right_down.loop = true;
		repair_animation_pack.push_back(&repair_right_down);		
		//----------------------------------------------

		angle = 225.f;
		current_animation = &walk_down;
		selection_type = { 28, 9, 32, 19 };
		circle_selection_offset = {-2, 0 };
		offset_life = { -14, 22 };
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
		range_of_vision = 300;
		range_to_attack = 50;

		damage = 5.0f;
		attack_delay = 200.0f;
		time_to_die = 500.0f;

		speed = 10;
		//AleixBV Research
		time_to_create = 5.0f;
		
		direction.create(1, 1, p.x, p.y);
		direction.setAngle(0.f);
	}

	void setAnimationFromDirection()
	{
		switch (state)
		{
		case(IDLE) :
		case(MOVE) :
		{
			int num_animation = angle / (360 / move_animation_pack.size());
			current_animation = &(*move_animation_pack.at(num_animation));
			break;
		}
		case(REPAIR) :
		{
			int num_animation = angle / (360 / repair_animation_pack.size());
			current_animation = &(*repair_animation_pack.at(num_animation));
			break;
		}
		// WHERE is this animation?
		/*case(DYING) :
		{
			current_animation = &dead;
			break;
		}*/
		}
	}
			
	bool update(float dt)
	{
		checkUnitDirection();
		setAnimationFromDirection();   // This sets animation according to their angle direction
		coll->setPos(center.x + collider_offset.x, center.y + collider_offset.y);

		switch (state)
		{
		case IDLE:
			if (timer_to_check.read() >= TIME_TO_CHECK)
			{
				if (searchNearestEnemy())
					LOG("Enemy found");
				timer_to_check.start();
			}
			break;
		case MOVE:
			if (has_target) move(dt);
			break;
		case REPAIR:
			if (timer_attack_delay.read() >= attack_delay)
			{
				repair();
				timer_attack_delay.start();

			}
			break;
		case DYING:
			if (timer_to_check.read() >= time_to_die)
			{
				to_delete = true;
				coll->to_delete = true;
			}
			break;
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

};

#endif //__SCV_H__