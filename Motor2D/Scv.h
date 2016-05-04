#ifndef __SCV_H__
#define __SCV_H__

#include "Unit.h"

class Scv : public Unit
{
public:

	// IDLE animations
	Animation	walk_up;
	Animation   walk_right_up;
	Animation   walk_right;
	Animation   walk_right_down;
	Animation   walk_down;
	Animation   walk_left_down;
	Animation   walk_left;
	Animation   walk_left_up;
	vector<Animation*> move_animation_pack;

	Animation	repair_up;
	Animation	repair_right_up;
	Animation	repair_right;
	Animation	repair_right_down;
	Animation	repair_down;
	Animation	repair_left_down;
	Animation	repair_left;
	Animation	repair_left_up;
	vector<Animation*> repair_animation_pack;

	unsigned int	scv_repair_fx;
	int				repair_power;

	Scv(iPoint &p)
	{
		// Graphics
		tex = app->tex->loadTexture("Units/Blue_Scv.png");
		tex_width = 72;
		tex_height = 64;
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
		repair_animation_pack.push_back(&repair_right);

		repair_right_up.frames.push_back({ 144, 64, 72, 64 });
		repair_right_up.frames.push_back({ 144, 128, 72, 64 });
		repair_right_up.speed = 0.01f;
		repair_animation_pack.push_back(&repair_right_up);

		repair_up.frames.push_back({ 0, 64, 72, 64 });
		repair_up.frames.push_back({ 0, 128, 72, 64 });
		repair_up.speed = 0.01f;
		repair_animation_pack.push_back(&repair_up);

		repair_left_up.frames.push_back({ 1008, 64, 72, 64 });
		repair_left_up.frames.push_back({ 1008, 128, 72, 64 });
		repair_left_up.speed = 0.01f;
		repair_animation_pack.push_back(&repair_left_up);

		repair_left.frames.push_back({ 864, 64, 72, 64 });
		repair_left.frames.push_back({ 864, 128, 72, 64 });
		repair_left.speed = 0.01f;
		repair_animation_pack.push_back(&repair_left);

		repair_left_down.frames.push_back({ 720, 64, 72, 64 });
		repair_left_down.frames.push_back({ 720, 128, 72, 64 });
		repair_left_down.speed = 0.01f;
		repair_animation_pack.push_back(&repair_left_down);

		repair_down.frames.push_back({ 576, 64, 72, 64 });
		repair_down.frames.push_back({ 576, 128, 72, 64 });
		repair_down.speed = 0.01f;
		repair_animation_pack.push_back(&repair_down);

		repair_right_down.frames.push_back({ 432, 64, 72, 64 });
		repair_right_down.frames.push_back({ 432, 128, 72, 64 });
		repair_right_down.speed = 0.01f;
		repair_animation_pack.push_back(&repair_right_down);
		//----------------------------------------------
		current_animation = &walk_down;

		// Positions and information
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		center = { (float)p.x, (float)p.y };		
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

		// Colliders
		coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 30, 30 }, COLLIDER_UNIT, app->entity_manager);
		collider_offset = { -14, -16 };
		
		// Characterization and behaviour
		faction = PLAYER;
		specialization = SCV;
		flying = false;		

		// Sounds
		scv_repair_fx = app->audio->loadFx("Audio/FX/SCV/Scv_repair.wav");
			
		// UI paramters
		selection_type = { 28, 9, 32, 19 };
		circle_selection_offset = {-2, 0 };
		offset_life = { -14, 22 };
		
		// Lifes attributes
		max_hp = 40;
		current_hp = 40.0f;
		max_hp_bars = 6;

		// Attack values and properties
		range_of_vision = 300;
		range_to_attack = 50;
		damage = 5.0f;
		attack_frequency = 200.0f;
		repair_power = 10;

		// PathFinding and movement variables
		angle = 225.f;
		speed = 10.0f;	
	}

	~Scv()
	{

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
		case(MOVE_ALERT) :
		{
			int num_animation = angle / (360 / move_animation_pack.size());
			current_animation = &(*move_animation_pack.at(num_animation));
			break;
		}
		case(ATTACK) ://ATTACK == REPAIR for SCV
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
			break;
		case MOVE:
			if (has_target) move(dt);
			break;
		case MOVE_ALERT:
			if (has_target) move(dt);
			break;
		case MOVE_ALERT_TO_ATTACK:
			if (has_target) move(dt);
			break;
		case ATTACK://ATTACK == REPAIR for SCV
			if (timer_attack.read() >= attack_frequency)
			{
				if(!repair())
					state = IDLE;
				timer_attack.start();
			}
			break;
		case DYING:
			if (current_animation->finished())
			{
				to_delete = true;
				coll->to_delete = true;
			}
			break;
		case WAITING_PATH_MOVE:
			if (app->path->getPathFound(id, path))
			{
				has_target = true;
				state = MOVE;
			}
			break;
		case WAITING_PATH_MOVE_ALERT:
			if (app->path->getPathFound(id, path))
			{
				has_target = true;
				state = MOVE_ALERT;
			}
			break;
		case WAITING_PATH_MOVE_ALERT_TO_ATTACK:
			if (app->path->getPathFound(id, path))
			{
				has_target = true;
				state = MOVE_ALERT_TO_ATTACK;
			}
			break;
		}
		return true;
	}

	bool repair()
	{
		bool ret = false;
		if (target_to_attack != NULL)
		{
			float d = abs(center.x - target_to_attack->center.x) + abs(center.y - target_to_attack->center.y);
			d -= ((coll->rect.w / 2 + coll->rect.h / 2) / 2 + (target_to_attack->coll->rect.w / 2 + target_to_attack->coll->rect.h / 2) / 2);
			if (d <= range_to_attack)
			{
				if ((target_to_attack->current_hp += repair_power) >= target_to_attack->max_hp)
				{
					target_to_attack->current_hp = target_to_attack->max_hp;
					state = IDLE;
					target_to_attack = NULL;
				}
				ret = true;
			}
		}
		return ret;
	}

	void Scv::move(float dt)
	{
		if (path.size() > 0)
		{
			float pixels_to_move = 0;
			float total_pixels_moved = 0;
			float total_pixels_to_move = speed / 100 * dt;

			if (total_pixels_to_move >= 4)
				pixels_to_move = 4;

			do{
				if (total_pixels_moved + 4 > total_pixels_to_move)
					pixels_to_move = total_pixels_to_move - total_pixels_moved;

				if (path.begin()->x < tile_pos.x && path.begin()->y < tile_pos.y)
				{
					center.x -= pixels_to_move / 2;
					center.y -= pixels_to_move / 2;
				}
				else if (path.begin()->x < tile_pos.x && path.begin()->y > tile_pos.y)
				{
					center.x -= pixels_to_move / 2;
					center.y += pixels_to_move / 2;
				}
				else if (path.begin()->x > tile_pos.x && path.begin()->y > tile_pos.y)
				{
					center.x += pixels_to_move / 2;
					center.y += pixels_to_move / 2;
				}
				else if (path.begin()->x > tile_pos.x && path.begin()->y < tile_pos.y)
				{
					center.x += pixels_to_move / 2;
					center.y -= pixels_to_move / 2;
				}
				else if (path.begin()->y == tile_pos.y)
				{
					if (path.begin()->x < tile_pos.x)
						center.x -= pixels_to_move;
					else
						center.x += pixels_to_move;
				}
				else
				{
					if (path.begin()->y < tile_pos.y)
						center.y -= pixels_to_move;

					else
						center.y += pixels_to_move;
				}
				calculePos();

				if (app->map->worldToMap(app->map->data.back(), center.x, center.y) != tile_pos)
				{
					tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);
					if (tile_pos == path.back())
					{
						path.clear();
						has_target = false;
						state = IDLE;

						if (target_to_attack != NULL) 
							state = ATTACK;//ATTACK == REPAIR for SCV
						break;

					}
					else if (tile_pos.x == path.begin()->x && tile_pos.y == path.begin()->y)
						path.erase(path.begin());
				}
				total_pixels_moved += pixels_to_move;

			} while (total_pixels_moved < total_pixels_to_move);
		}
		else
		{
			state = IDLE;
			has_target = false;
		}
	}

};

#endif //__SCV_H__