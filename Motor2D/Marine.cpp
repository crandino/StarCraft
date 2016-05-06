#include "Marine.h"
#include "Bunker.h"

Marine::Marine(iPoint &p)
{
	//Graphics
	tex = app->tex->loadTexture("Units/Blue_Marine.png");
	tex_width = tex_height = 64;
	//---------------Idle Animation----------------
	idle_right.frames.push_back({ 256, 0, 64, 64 });
	idle_right.frames.push_back({ 256, 64, 64, 64 });
	idle_right.frames.push_back({ 256, 128, 64, 64 });
	idle_right.frames.push_back({ 256, 64, 64, 64 });
	idle_right.frames.push_back({ 256, 0, 64, 64 });
	idle_right.speed = 0.005f;
	idle_animation_pack.push_back(&idle_right);

	idle_right_up.frames.push_back({ 128, 0, 64, 64 });
	idle_right_up.frames.push_back({ 128, 64, 64, 64 });
	idle_right_up.frames.push_back({ 128, 128, 64, 64 });
	idle_right_up.frames.push_back({ 128, 64, 64, 64 });
	idle_right_up.frames.push_back({ 128, 0, 64, 64 });
	idle_right_up.speed = 0.005f;
	idle_animation_pack.push_back(&idle_right_up);

	idle_up.frames.push_back({ 0, 0, 64, 64 });
	idle_up.frames.push_back({ 0, 64, 64, 64 });
	idle_up.frames.push_back({ 0, 128, 64, 64 });
	idle_up.frames.push_back({ 0, 64, 64, 64 });
	idle_up.frames.push_back({ 0, 0, 64, 64 });
	idle_up.speed = 0.005f;
	idle_animation_pack.push_back(&idle_up);

	idle_left_up.frames.push_back({ 960, 0, 64, 64 });
	idle_left_up.frames.push_back({ 960, 64, 64, 64 });
	idle_left_up.frames.push_back({ 960, 128, 64, 64 });
	idle_left_up.frames.push_back({ 960, 64, 64, 64 });
	idle_left_up.frames.push_back({ 960, 0, 64, 64 });
	idle_left_up.speed = 0.005f;
	idle_animation_pack.push_back(&idle_left_up);

	idle_left.frames.push_back({ 768, 0, 64, 64 });
	idle_left.frames.push_back({ 768, 64, 64, 64 });
	idle_left.frames.push_back({ 768, 128, 64, 64 });
	idle_left.frames.push_back({ 768, 64, 64, 64 });
	idle_left.frames.push_back({ 768, 0, 64, 64 });
	idle_left.speed = 0.005f;
	idle_animation_pack.push_back(&idle_left);

	idle_left_down.frames.push_back({ 640, 0, 64, 64 });
	idle_left_down.frames.push_back({ 640, 64, 64, 64 });
	idle_left_down.frames.push_back({ 640, 128, 64, 64 });
	idle_left_down.frames.push_back({ 640, 64, 64, 64 });
	idle_left_down.frames.push_back({ 640, 0, 64, 64 });
	idle_left_down.speed = 0.005f;
	idle_animation_pack.push_back(&idle_left_down);

	idle_down.frames.push_back({ 448, 0, 64, 64 });
	idle_down.frames.push_back({ 448, 64, 64, 64 });
	idle_down.frames.push_back({ 448, 128, 64, 64 });
	idle_down.frames.push_back({ 448, 64, 64, 64 });
	idle_down.frames.push_back({ 448, 0, 64, 64 });
	idle_down.speed = 0.005f;
	idle_animation_pack.push_back(&idle_down);

	idle_right_down.frames.push_back({ 384, 0, 64, 64 });
	idle_right_down.frames.push_back({ 384, 64, 64, 64 });
	idle_right_down.frames.push_back({ 384, 128, 64, 64 });
	idle_right_down.frames.push_back({ 384, 64, 64, 64 });
	idle_right_down.frames.push_back({ 384, 0, 64, 64 });
	idle_right_down.speed = 0.005f;
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
	attack_animation_pack.push_back(&attack_right);

	attack_right_up.frames.push_back({ 128, 128, 64, 64 });
	attack_right_up.frames.push_back({ 128, 192, 64, 64 });
	attack_right_up.speed = 0.01f;
	attack_animation_pack.push_back(&attack_right_up);

	attack_up.frames.push_back({ 0, 128, 64, 64 });
	attack_up.frames.push_back({ 0, 192, 64, 64 });
	attack_up.speed = 0.01f;
	attack_animation_pack.push_back(&attack_up);

	attack_left_up.frames.push_back({ 896, 128, 64, 64 });
	attack_left_up.frames.push_back({ 896, 192, 64, 64 });
	attack_left_up.speed = 0.01f;
	attack_animation_pack.push_back(&attack_left_up);

	attack_left.frames.push_back({ 768, 128, 64, 64 });
	attack_left.frames.push_back({ 768, 192, 64, 64 });
	attack_left.speed = 0.01f;
	attack_animation_pack.push_back(&attack_left);

	attack_left_down.frames.push_back({ 640, 128, 64, 64 });
	attack_left_down.frames.push_back({ 640, 192, 64, 64 });
	attack_left_down.speed = 0.01f;
	attack_animation_pack.push_back(&attack_left_down);

	attack_down.frames.push_back({ 512, 128, 64, 64 });
	attack_down.frames.push_back({ 512, 192, 64, 64 });
	attack_down.speed = 0.01f;
	attack_animation_pack.push_back(&attack_down);

	attack_right_down.frames.push_back({ 384, 128, 64, 64 });
	attack_right_down.frames.push_back({ 384, 192, 64, 64 });
	attack_right_down.speed = 0.01f;
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
	dead.loop = false;
	dead.speed = 0.01f;
	//----------------------------------------------
	current_animation = &idle_up;

	// Positions and information
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	center = { (float)p.x, (float)p.y };
	tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

	// Colliders
	coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 22, 30 }, COLLIDER_UNIT, app->entity_manager);
	collider_offset = { -10, -14 };
	
	// Characterization and behaviour
	faction = PLAYER;
	specialization = MARINE;
	flying = false;

	// Sounds
	fx_attack = app->audio->loadFx("Audio/FX/Units/Terran/Attack.wav");

	// UI paramters
	selection_type = { 3, 4, 22, 13 };
	circle_selection_offset = { 0, -1 };
	offset_life = { -16, 16 };

	// Lifes attributes
	max_hp = 40;
	current_hp = 40.0f;
	max_hp_bars = 6;
	
	// Attack values and properties
	range_of_vision = 300;
	range_to_attack = 100;
	damage = 5.0f;
	attack_frequency = 200.0f;
	
	// PathFinding and movement variables
	speed = 10.0f;	
}

Marine::~Marine()
{
	SDL_DestroyTexture(tex);
}

void Marine::move(float dt)
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
				
					if (bunker_to_fill != NULL) 
						bunker_to_fill->getEntityInside(this);
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

// Method that assign an animation according to its orientation
void Marine::setAnimationFromDirection()
{
	switch (state)
	{
	case(IDLE) :
	{
		int num_animation = angle / (360 / idle_animation_pack.size());
		if (num_animation == idle_animation_pack.size())
			num_animation = 0;
		current_animation = &(*idle_animation_pack.at(num_animation));
		break;
	}
	case(ATTACK) :
	{
		int num_animation = angle / (360 / attack_animation_pack.size());
		if (num_animation == attack_animation_pack.size())
			num_animation = 0;
		current_animation = &(*attack_animation_pack.at(num_animation));
		break;
	}
	case(MOVE) :
	{
		int num_animation = angle / (360 / move_animation_pack.size());
		if (num_animation == move_animation_pack.size())
			num_animation = 0;
		current_animation = &(*move_animation_pack.at(num_animation));
		break;
	}
	case(MOVE_ALERT) :
	{
		int num_animation = angle / (360 / move_animation_pack.size());
		if (num_animation == move_animation_pack.size())
			num_animation = 0;
		current_animation = &(*move_animation_pack.at(num_animation));
		break;
	}
	case(MOVE_ALERT_TO_ATTACK) :
	{
		int num_animation = angle / (360 / move_animation_pack.size());
		if (num_animation == move_animation_pack.size())
			num_animation = 0;
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
		if (num_animation == idle_animation_pack.size())
			num_animation = 0;
		current_animation = &(*idle_animation_pack.at(num_animation));
		break;
	}
	case(WAITING_PATH_MOVE_ALERT) :
	{
		int num_animation = angle / (360 / idle_animation_pack.size());
		if (num_animation == idle_animation_pack.size())
			num_animation = 0;
		current_animation = &(*idle_animation_pack.at(num_animation));
		break;
	}
	case(WAITING_PATH_MOVE_ALERT_TO_ATTACK) :
	{
		int num_animation = angle / (360 / idle_animation_pack.size());
		if (num_animation == idle_animation_pack.size())
			num_animation = 0;
		current_animation = &(*idle_animation_pack.at(num_animation));
		break;
	}

	}
}

