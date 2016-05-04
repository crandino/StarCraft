#include "Tank.h"

Tank::Tank(iPoint &p)
{
	//Graphics
	tex = app->tex->loadTexture("Units/Blue_tank.png");
	tex_width = tex_height = 128;

	//---------------Idle Animation----------------
	idle_right.frames.push_back({ 512, 0, 128, 128 });
	idle_right.loop = false;
	idle_animation_pack.push_back(&idle_right);

	idle_right_up.frames.push_back({ 256, 0, 128, 128 });
	idle_right_up.loop = false;
	idle_animation_pack.push_back(&idle_right_up);

	idle_up.frames.push_back({ 0, 0, 128, 128 });
	idle_up.loop = false;
	idle_animation_pack.push_back(&idle_up);

	idle_left_up.frames.push_back({ 1792, 0, 128, 128 });
	idle_left_up.loop = false;
	idle_animation_pack.push_back(&idle_left_up);

	idle_left.frames.push_back({ 1536, 0, 128, 128 });
	idle_left.loop = false;
	idle_animation_pack.push_back(&idle_left);

	idle_left_down.frames.push_back({ 1280, 0, 128, 128 });
	idle_left_down.loop = false;
	idle_animation_pack.push_back(&idle_left_down);

	idle_down.frames.push_back({ 1024, 0, 128, 128 });
	idle_down.loop = false;
	idle_animation_pack.push_back(&idle_down);

	idle_right_down.frames.push_back({ 768, 0, 128, 128 });
	idle_right_down.loop = false;
	idle_animation_pack.push_back(&idle_right_down);
	//----------------------------------------------

	//--------------Walking Animations--------------
	walk_right.frames.push_back({ 512, 0, 128, 128 });
	walk_right.frames.push_back({ 512, 128, 128, 128 });
	walk_right.frames.push_back({ 512, 256, 128, 128 });
	walk_right.loop = true;
	walk_right.speed = 0.01f;
	move_animation_pack.push_back(&walk_right);

	walk_right_up.frames.push_back({ 256, 0, 128, 128 });
	walk_right_up.frames.push_back({ 256, 128, 128, 128 });
	walk_right_up.frames.push_back({ 256, 256, 128, 128 });
	walk_right_up.loop = true;
	walk_right_up.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_up);

	walk_up.frames.push_back({ 0, 0, 128, 128 });
	walk_up.frames.push_back({ 0, 128, 128, 128 });
	walk_up.frames.push_back({ 0, 256, 128, 128 });
	walk_up.loop = true;
	walk_up.speed = 0.01f;
	move_animation_pack.push_back(&walk_up);

	walk_left_up.frames.push_back({ 1792, 0, 128, 128 });
	walk_left_up.frames.push_back({ 1792, 128, 128, 128 });
	walk_left_up.frames.push_back({ 1792, 256, 128, 128 });
	walk_left_up.loop = true;
	walk_left_up.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_up);

	walk_left.frames.push_back({ 1536, 0, 128, 128 });
	walk_left.frames.push_back({ 1536, 128, 128, 128 });
	walk_left.frames.push_back({ 1536, 256, 128, 128 });
	walk_left.loop = true;
	walk_left.speed = 0.01f;
	move_animation_pack.push_back(&walk_left);

	walk_left_down.frames.push_back({ 1280, 0, 128, 128 });
	walk_left_down.frames.push_back({ 1280, 128, 128, 128 });
	walk_left_down.frames.push_back({ 1280, 256, 128, 128 });
	walk_left_down.loop = true;
	walk_left_down.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_down);

	walk_down.frames.push_back({ 1024, 0, 128, 128 });
	walk_down.frames.push_back({ 1024, 128, 128, 128 });
	walk_down.frames.push_back({ 1024, 256, 128, 128 });
	walk_down.loop = true;
	walk_down.speed = 0.01f;
	move_animation_pack.push_back(&walk_down);

	walk_right_down.frames.push_back({ 768, 0, 128, 128 });
	walk_right_down.frames.push_back({ 768, 128, 128, 128 });
	walk_right_down.frames.push_back({ 768, 256, 128, 128 });
	walk_right_down.loop = true;
	walk_right_down.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_down);	
	
	current_animation = &idle_down;

	// Positions and information
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	center = { (float)p.x, (float)p.y };
	tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

	// Colliders
	coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 64, 48 }, COLLIDER_UNIT, app->entity_manager);
	collider_offset = { -32, -24 };

	// Characterization and behaviour
	faction = PLAYER;
	specialization = TANK;
	flying = false;

	// UI paramters
	selection_type = { 116, 2, 62, 37 };
	circle_selection_offset = { -1, 10 };
	offset_life = { -22, 30 };

	// Lifes attributes
	max_hp = 250;
	current_hp = 250.0f;
	max_hp_bars = 10;

	// Attack values and properties
	range_of_vision = 300;
	range_to_attack = 100;
	damage = 5.0f;
	attack_frequency = 200.0f;
	time_to_die = 500.0f;
	area_attack = true;
	area_range = 50.0f;

	// PathFinding and movement variables
	speed = 12.0f;
}

Tank::~Tank()
{

}

void Tank::move(float dt)
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
void Tank::setAnimationFromDirection()
{
	switch (state)
	{
	case(IDLE) :
	{
		int num_animation = angle / (360 / idle_animation_pack.size());
		current_animation = &(*idle_animation_pack.at(num_animation));
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

