#include "Hydralisk.h"

Hydralisk::Hydralisk(iPoint &p)
{
	//Graphics
	tex = app->tex->loadTexture("Units/Hydralisk.png");
	tex_width = tex_height = 128;

	//--------------Walking Animations--------------
	walk_right.frames.push_back({ 512, 0, 128, 128 });
	walk_right.frames.push_back({ 512, 128, 128, 128 });
	walk_right.frames.push_back({ 512, 256, 128, 128 });
	walk_right.frames.push_back({ 512, 384, 128, 128 });
	walk_right.frames.push_back({ 512, 512, 128, 128 });
	walk_right.speed = 0.01f;
	move_animation_pack.push_back(&walk_right);

	walk_right_up3.frames.push_back({ 384, 0, 128, 128 });
	walk_right_up3.frames.push_back({ 384, 128, 128, 128 });
	walk_right_up3.frames.push_back({ 384, 256, 128, 128 });
	walk_right_up3.frames.push_back({ 384, 384, 128, 128 });
	walk_right_up3.frames.push_back({ 384, 512, 128, 128 });
	walk_right_up3.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_up3);

	walk_right_up2.frames.push_back({ 256, 0, 128, 128 });
	walk_right_up2.frames.push_back({ 256, 128, 128, 128 });
	walk_right_up2.frames.push_back({ 256, 256, 128, 128 });
	walk_right_up2.frames.push_back({ 256, 384, 128, 128 });
	walk_right_up2.frames.push_back({ 256, 512, 128, 128 });
	walk_right_up2.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_up2);

	walk_up.frames.push_back({ 0, 0, 128, 128 });
	walk_up.frames.push_back({ 0, 128, 128, 128 });
	walk_up.frames.push_back({ 0, 256, 128, 128 });
	walk_up.frames.push_back({ 0, 384, 128, 128 });
	walk_up.frames.push_back({ 0, 512, 128, 128 });
	walk_up.speed = 0.01f;
	move_animation_pack.push_back(&walk_up);

	walk_left_up3.frames.push_back({ 1920, 0, 128, 128 });
	walk_left_up3.frames.push_back({ 1920, 128, 128, 128 });
	walk_left_up3.frames.push_back({ 1920, 256, 128, 128 });
	walk_left_up3.frames.push_back({ 1920, 384, 128, 128 });
	walk_left_up3.frames.push_back({ 1920, 512, 128, 128 });
	walk_left_up3.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_up3);

	walk_left_up2.frames.push_back({ 1792, 0, 128, 128 });
	walk_left_up2.frames.push_back({ 1792, 128, 128, 128 });
	walk_left_up2.frames.push_back({ 1792, 256, 128, 128 });
	walk_left_up2.frames.push_back({ 1792, 384, 128, 128 });
	walk_left_up2.frames.push_back({ 1792, 512, 128, 128 });
	walk_left_up2.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_up2);

	walk_left_up1.frames.push_back({ 1664, 0, 128, 128 });
	walk_left_up1.frames.push_back({ 1664, 128, 128, 128 });
	walk_left_up1.frames.push_back({ 1664, 256, 128, 128 });
	walk_left_up1.frames.push_back({ 1664, 384, 128, 128 });
	walk_left_up1.frames.push_back({ 1664, 512, 128, 128 });
	walk_left_up1.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_up1);

	walk_left.frames.push_back({ 1536, 0, 128, 128 });
	walk_left.frames.push_back({ 1536, 128, 128, 128 });
	walk_left.frames.push_back({ 1536, 256, 128, 128 });
	walk_left.frames.push_back({ 1536, 384, 128, 128 });
	walk_left.frames.push_back({ 1536, 512, 128, 128 });
	walk_left.speed = 0.01f;
	move_animation_pack.push_back(&walk_left);

	walk_left_down3.frames.push_back({ 1408, 0, 128, 128 });
	walk_left_down3.frames.push_back({ 1408, 128, 128, 128 });
	walk_left_down3.frames.push_back({ 1408, 256, 128, 128 });
	walk_left_down3.frames.push_back({ 1408, 384, 128, 128 });
	walk_left_down3.frames.push_back({ 1408, 512, 128, 128 });
	walk_left_down3.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_down3);

	walk_left_down2.frames.push_back({ 1280, 0, 128, 128 });
	walk_left_down2.frames.push_back({ 1280, 128, 128, 128 });
	walk_left_down2.frames.push_back({ 1280, 256, 128, 128 });
	walk_left_down2.frames.push_back({ 1280, 384, 128, 128 });
	walk_left_down2.frames.push_back({ 1280, 512, 128, 128 });
	walk_left_down2.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_down2);

	walk_left_down1.frames.push_back({ 1152, 0, 128, 128 });
	walk_left_down1.frames.push_back({ 1152, 128, 128, 128 });
	walk_left_down1.frames.push_back({ 1152, 256, 128, 128 });
	walk_left_down1.frames.push_back({ 1152, 384, 128, 128 });
	walk_left_down1.frames.push_back({ 1152, 512, 128, 128 });
	walk_left_down1.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_down1);

	walk_down.frames.push_back({ 1024, 0, 128, 128 });
	walk_down.frames.push_back({ 1024, 128, 128, 128 });
	walk_down.frames.push_back({ 1024, 256, 128, 128 });
	walk_down.frames.push_back({ 1024, 384, 128, 128 });
	walk_down.frames.push_back({ 1024, 512, 128, 128 });
	walk_down.speed = 0.01f;
	move_animation_pack.push_back(&walk_down);

	walk_right_down3.frames.push_back({ 896, 0, 128, 128 });
	walk_right_down3.frames.push_back({ 896, 128, 128, 128 });
	walk_right_down3.frames.push_back({ 896, 256, 128, 128 });
	walk_right_down3.frames.push_back({ 896, 384, 128, 128 });
	walk_right_down3.frames.push_back({ 896, 512, 128, 128 });
	walk_right_down3.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_down3);

	walk_right_down2.frames.push_back({ 768, 0, 128, 128 });
	walk_right_down2.frames.push_back({ 768, 128, 128, 128 });
	walk_right_down2.frames.push_back({ 768, 256, 128, 128 });
	walk_right_down2.frames.push_back({ 768, 384, 128, 128 });
	walk_right_down2.frames.push_back({ 768, 512, 128, 128 });
	walk_right_down2.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_down2);

	walk_right_down1.frames.push_back({ 640, 0, 128, 128 });
	walk_right_down1.frames.push_back({ 640, 128, 128, 128 });
	walk_right_down1.frames.push_back({ 640, 256, 128, 128 });
	walk_right_down1.frames.push_back({ 640, 384, 128, 128 });
	walk_right_down1.frames.push_back({ 640, 512, 128, 128 });
	walk_right_down1.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_down1);

	//------------Mutalisk DEAD-----------------------
	dead.frames.push_back({ 0, 640, 128, 128 });
	dead.frames.push_back({ 128, 640, 128, 128 });
	dead.frames.push_back({ 256, 640, 128, 128 });
	dead.frames.push_back({ 384, 640, 128, 128 });
	dead.frames.push_back({ 512, 640, 128, 128 });
	dead.frames.push_back({ 640, 640, 128, 128 });
	dead.frames.push_back({ 768, 640, 128, 128 });
	dead.frames.push_back({ 896, 640, 128, 128 });
	dead.frames.push_back({ 1024, 640, 128, 128 });
	dead.speed = 0.02f;
	dead.loop = false;
	//----------------------------------------------
	current_animation = &walk_down;

	// Positions and information
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	center = { (float)p.x, (float)p.y };
	tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

	// Colliders
	coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 22, 30 }, COLLIDER_UNIT, app->entity_manager);
	collider_offset = { -10, -14 };

	// Characterization and behaviour
	faction = COMPUTER;
	specialization = MUTALISK;
	flying = true;

	// UI paramters
	selection_type = { 28, 9, 32, 19 };
	circle_selection_offset = { 0, -1 };
	offset_life = { -16, 18 };

	// Lifes attributes
	max_hp = current_hp = 60.0f;
	max_hp_bars = 6;

	// Attack values and properties
	range_of_vision = 300;
	range_to_attack = 100;
	damage = 5.0f;
	attack_frequency = 200.0f;
	time_to_die = 500.0f;

	// PathFinding and movement variables
	speed = 12.0f;
}

void Hydralisk::move(float dt)
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
void Hydralisk::setAnimationFromDirection()
{
	switch (state)
	{
	case(IDLE) :
	case(MOVE) :
	case(MOVE_ALERT) :
	case(WAITING_PATH_MOVE) :
	case(WAITING_PATH_MOVE_ALERT) :
	case(ATTACK) :
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

