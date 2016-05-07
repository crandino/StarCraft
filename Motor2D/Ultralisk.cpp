#include "Ultralisk.h"

Ultralisk::Ultralisk(iPoint &p)
{
	//Graphics
	tex = app->tex->loadTexture("Units/ultralisk2.png");
	tex_width = tex_height = 128;

	//--------------IDLE Animation------------------
	idle_right.setAnimations(512, 0, 128, 128, 1, 1, 1);
	idle_right.speed = 0.01f;
	idle_animation_pack.push_back(&idle_right);

	idle_right_up.setAnimations(256, 0, 128, 128, 1, 1, 1);
	idle_right_up.speed = 0.01f;
	idle_animation_pack.push_back(&idle_right_up);

	idle_up.setAnimations(0, 0, 128, 128, 1, 1, 1);
	idle_up.speed = 0.01f;
	idle_animation_pack.push_back(&idle_up);

	idle_left_up.setAnimations(1792, 0, 128, 128, 1, 1, 1);
	idle_left_up.speed = 0.01f;
	idle_animation_pack.push_back(&idle_left_up);

	idle_left.setAnimations(1536, 0, 128, 128, 1, 1, 1);
	idle_left.speed = 0.01f;
	idle_animation_pack.push_back(&idle_left);

	idle_left_down.setAnimations(1280, 0, 128, 128, 1, 1, 1);
	idle_left_down.speed = 0.01f;
	idle_animation_pack.push_back(&idle_left_down);

	idle_down.setAnimations(1024, 0, 128, 128, 1, 1, 1);
	idle_down.speed = 0.01f;
	idle_animation_pack.push_back(&idle_down);

	idle_right_down.setAnimations(768, 0, 128, 128, 1, 1, 1);
	idle_right_down.speed = 0.01f;
	idle_animation_pack.push_back(&idle_right_down);

	//--------------Walking Animations--------------
	walk_right.setAnimations(512, 128, 128, 128, 1, 9, 9);
	walk_right.speed = 0.01f;
	move_animation_pack.push_back(&walk_right);

	walk_right_up3.setAnimations(384, 128, 128, 128, 1, 9, 9);
	walk_right_up3.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_up3);

	walk_right_up2.setAnimations(256, 128, 128, 128, 1, 9, 9);
	walk_right_up2.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_up2);

	walk_right_up1.setAnimations(128, 128, 128, 128, 1, 9, 9);
	walk_right_up1.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_up1);

	walk_up.setAnimations(0, 128, 128, 128, 1, 9, 9);
	walk_up.speed = 0.01f;
	move_animation_pack.push_back(&walk_up);

	walk_left_up3.setAnimations(1664, 128, 128, 128, 1, 9, 9);
	walk_left_up3.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_up3);

	walk_left_up2.setAnimations(1792, 128, 128, 128, 1, 9, 9);
	walk_left_up2.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_up2);

	walk_left_up1.setAnimations(1920, 128, 128, 128, 1, 9, 9);
	walk_left_up1.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_up1);

	walk_left.setAnimations(1536, 128, 128, 128, 1, 9, 9);
	walk_left.speed = 0.01f;
	move_animation_pack.push_back(&walk_left);

	walk_left_down3.setAnimations(1152, 128, 128, 128, 1, 9, 9);
	walk_left_down3.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_down3);

	walk_left_down2.setAnimations(1280, 128, 128, 128, 1, 9, 9);
	walk_left_down2.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_down2);

	walk_left_down1.setAnimations(1408, 128, 128, 128, 1, 9, 9);
	walk_left_down1.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_down1);

	walk_down.setAnimations(1024, 128, 128, 128, 1, 9, 9);
	walk_down.speed = 0.01f;
	move_animation_pack.push_back(&walk_down);

	walk_right_down3.setAnimations(896, 128, 128, 128, 1, 9, 9);
	walk_right_down3.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_down3);

	walk_right_down2.setAnimations(768, 128, 128, 128, 1, 9, 9);
	walk_right_down2.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_down2);

	walk_right_down1.setAnimations(640, 128, 128, 128, 1, 9, 9);
	walk_right_down1.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_down1);

	//------------Mutalisk DEAD-----------------------
	dead.setAnimations(0, 1920, 128, 128, 10, 1, 10);
	dead.speed = 0.01f;
	dead.loop = false;

	//-------------Attack animation-------------------
	attack_right.setAnimations(512, 1280, 128, 128, 1, 5, 5);
	attack_right.speed = 0.008f;
	attack_animation_pack.push_back(&attack_right);

	attack_right_up.setAnimations(256, 1280, 128, 128, 1, 5, 5);
	attack_right_up.speed = 0.008f;
	attack_animation_pack.push_back(&attack_right_up);

	attack_up.setAnimations(0, 1280, 128, 128, 1, 5, 5);
	attack_up.speed = 0.008f;
	attack_animation_pack.push_back(&attack_up);

	attack_left_up.setAnimations(1792, 1280, 128, 128, 1, 5, 5);
	attack_left_up.speed = 0.008f;
	attack_animation_pack.push_back(&attack_left_up);

	attack_left.setAnimations(1536, 1280, 128, 128, 1, 5, 5);
	attack_left.speed = 0.008f;
	attack_animation_pack.push_back(&attack_left);

	attack_left_down.setAnimations(1280, 1280, 128, 128, 1, 5, 5);
	attack_left_down.speed = 0.008f;
	attack_animation_pack.push_back(&attack_left_down);

	attack_down.setAnimations(1024, 1280, 128, 128, 1, 5, 5);
	attack_down.speed = 0.008f;
	attack_animation_pack.push_back(&attack_down);

	attack_right_down.setAnimations(768, 1280, 128, 128, 1, 5, 5);
	attack_right_down.speed = 0.008f;
	attack_animation_pack.push_back(&attack_right_down);
	

	current_animation = &walk_down;

	// Positions and information
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	center = { (float)p.x, (float)p.y };
	tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

	// Colliders
	coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 64, 48 }, COLLIDER_UNIT, app->entity_manager);
	collider_offset = { -32, -24 };

	// Characterization and behaviour
	faction = COMPUTER;
	specialization = ULTRALISK;
	flying = false;

	// UI paramters
	selection_type = { 28, 9, 32, 19 };
	circle_selection_offset = { 0, -1 };
	offset_life = { -16, 18 };

	// Lifes attributes
	max_hp = current_hp = 500.0f;
	max_hp_bars = 10;

	// Attack values and properties
	range_of_vision = 200;
	range_to_attack = 75;
	damage = 10.0f;
	attack_frequency = 200.0f;
	time_to_die = 500.0f;
	area_attack = true;
	area_range = 40.0f;

	// PathFinding and movement variables
	speed = 5.0f;
}

Ultralisk::~Ultralisk()
{
	SDL_DestroyTexture(tex);
}

// Method that assign an animation according to its orientation
void Ultralisk::setAnimationFromDirection()
{
	switch (state)
	{
	case(IDLE) :
	{
				   int num_animation = angle / (360 / idle_animation_pack.size());
				   if (num_animation == idle_animation_pack.size())
					   num_animation = 0;
				   current_animation = &(*idle_animation_pack.at(num_animation));
				  
	}
			   break;
	case(MOVE) :
	{
		int num_animation = angle / (360 / move_animation_pack.size());
		if (num_animation == move_animation_pack.size())
			num_animation = 0;
		current_animation = &(*move_animation_pack.at(num_animation));
		
	}
			   break;
	case(MOVE_ALERT) :
	{
		int num_animation = angle / (360 / move_animation_pack.size());
		if (num_animation == move_animation_pack.size())
			num_animation = 0;
		current_animation = &(*move_animation_pack.at(num_animation));
		
	}
					 break;
	case(MOVE_ALERT_TO_ATTACK) :
	{
		int num_animation = angle / (360 / move_animation_pack.size());
		if (num_animation == move_animation_pack.size())
			num_animation = 0;
		current_animation = &(*move_animation_pack.at(num_animation));
		
	}
	break;
	case(WAITING_PATH_MOVE) :
	break;
	case(WAITING_PATH_MOVE_ALERT) :
	break;
	case(WAITING_PATH_MOVE_ALERT_TO_ATTACK) :
	break;
	case(ATTACK) :
	{
		int num_animation = angle / (360 / attack_animation_pack.size());
		if (num_animation == attack_animation_pack.size())
			num_animation = 0;
		current_animation = &(*attack_animation_pack.at(num_animation));
		
	}
	break;
	case(DYING) :
	current_animation = &dead;
	break;
	}
}