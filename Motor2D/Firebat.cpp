#include "Firebat.h"
#include "Bunker.h"

Firebat::Firebat(iPoint &p)
{
	//Graphics
	tex = app->tex->loadTexture("Units/firebat.png");
	tex_width = tex_height = 32;
	//---------------Idle Animation----------------
	idle_right.setAnimations(128, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_right);

	idle_right_up.setAnimations(64, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_right_up);

	idle_up.setAnimations(0, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_up);

	idle_left_up.setAnimations(448, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_left_up);

	idle_left.setAnimations(384, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_left);

	idle_left_down.setAnimations(320, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_left_down);

	idle_down.setAnimations(256, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_down);

	idle_right_down.setAnimations(192, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_right_down);
	//----------------------------------------------

	//--------------Walking Animations--------------
	walk_right.setAnimations(128, 96, 32, 32, 1, 7, 7);
	walk_right.speed = 0.02f;
	move_animation_pack.push_back(&walk_right);

	walk_right_up.setAnimations(64, 96, 32, 32, 1, 7, 7);
	walk_right_up.speed = 0.02f;
	move_animation_pack.push_back(&walk_right_up);

	walk_up.setAnimations(0, 96, 32, 32, 1, 7, 7);
	walk_up.speed = 0.02f;
	move_animation_pack.push_back(&walk_up);

	walk_left_up.setAnimations(448, 96, 32, 32, 1, 7, 7);
	walk_left_up.speed = 0.02f;
	move_animation_pack.push_back(&walk_left_up);

	walk_left.setAnimations(384, 96, 32, 32, 1, 7, 7);
	walk_left.speed = 0.02f;
	move_animation_pack.push_back(&walk_left);

	walk_left_down.setAnimations(320, 96, 32, 32, 1, 7, 7);
	walk_left_down.speed = 0.02f;
	move_animation_pack.push_back(&walk_left_down);

	walk_down.setAnimations(256, 96, 32, 32, 1, 7, 7);
	walk_down.speed = 0.02f;
	move_animation_pack.push_back(&walk_down);

	walk_right_down.setAnimations(192, 96, 32, 32, 1, 7, 7);
	walk_right_down.speed = 0.02f;
	move_animation_pack.push_back(&walk_right_down);
	//----------------------------------------------

	//-----------Firebat ATTACK----------------------
	attack_right.setAnimations(128, 0, 32, 32, 1, 2, 2);
	attack_right.speed = 0.002f;
	attack_animation_pack.push_back(&attack_right);

	attack_right_up.setAnimations(64, 0, 32, 32, 1, 2, 2);
	attack_right_up.speed = 0.002f;
	attack_animation_pack.push_back(&attack_right_up);

	attack_up.setAnimations(0, 0, 32, 32, 1, 2, 2);
	attack_up.speed = 0.002f;
	attack_animation_pack.push_back(&attack_up);

	attack_left_up.setAnimations(448, 0, 32, 32, 1, 2, 2);
	attack_left_up.speed = 0.002f;
	attack_animation_pack.push_back(&attack_left_up);

	attack_left.setAnimations(384, 0, 32, 32, 1, 2, 2);
	attack_left.speed = 0.002f;
	attack_animation_pack.push_back(&attack_left);

	attack_left_down.setAnimations(320, 0, 32, 32, 1, 2, 2);
	attack_left_down.speed = 0.002f;
	attack_animation_pack.push_back(&attack_left_down);

	attack_down.setAnimations(256, 0, 32, 32, 1, 2, 2);
	attack_down.speed = 0.002f;
	attack_animation_pack.push_back(&attack_down);

	attack_right_down.frames.push_back({ 384, 128, 64, 64 });
	attack_right_down.frames.push_back({ 384, 192, 64, 64 });
	attack_right_down.speed = 0.002f;
	attack_animation_pack.push_back(&attack_right_down);
	//----------------------------------------------

	//------------Firebat DEAD----------------------
	// It's Explosion Particle
	//----------------------------------------------

	//-----------Firebat Particles------------------

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
	specialization = FIREBAT;
	flying = false;

	// Sounds
	firebat_attack_fx = app->audio->loadFx("Audio/FX/Marine/Marine_attack.wav");

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
	attack_frequency = 800.0f;
	time_to_die = 500.0f;

	// PathFinding and movement variables
	speed = 10.0f;
}

Firebat::~Firebat()
{

}

void Firebat::move(float dt)
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
void Firebat::setAnimationFromDirection()
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
	//case(DYING) :
	//{
	//	current_animation = &dead;
	//	break;
	//}
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

