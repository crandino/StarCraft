#include "Hydralisk.h"

Hydralisk::Hydralisk(iPoint &p)
{
	//Graphics
	tex = app->tex->loadTexture("Units/Hydralisk.png");
	tex_width = tex_height = 128;

	//--------------Walking Animations--------------
	walk_right.frames.push_back({ 512, 640, 128, 128 });
	walk_right.frames.push_back({ 512, 768, 128, 128 });
	walk_right.frames.push_back({ 512, 896, 128, 128 });
	walk_right.frames.push_back({ 512, 1024, 128, 128 });
	walk_right.frames.push_back({ 512, 1152, 128, 128 });
	walk_right.frames.push_back({ 512, 1280, 128, 128 });
	walk_right.frames.push_back({ 512, 1408, 128, 128 });
	walk_right.speed = 0.01f;
	move_animation_pack.push_back(&walk_right);

	walk_right_up3.frames.push_back({ 384, 640, 128, 128 });
	walk_right_up3.frames.push_back({ 384, 768, 128, 128 });
	walk_right_up3.frames.push_back({ 384, 896, 128, 128 });
	walk_right_up3.frames.push_back({ 384, 1024, 128, 128 });
	walk_right_up3.frames.push_back({ 384, 1152, 128, 128 });
	walk_right_up3.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_up3);

	walk_right_up2.frames.push_back({ 256, 640, 128, 128 });
	walk_right_up2.frames.push_back({ 256, 768, 128, 128 });
	walk_right_up2.frames.push_back({ 256, 896, 128, 128 });
	walk_right_up2.frames.push_back({ 256, 1024, 128, 128 });
	walk_right_up2.frames.push_back({ 256, 1152, 128, 128 });
	walk_right_up2.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_up2);

	walk_up.frames.push_back({ 0, 640, 128, 128 });
	walk_up.frames.push_back({ 0, 768, 128, 128 });
	walk_up.frames.push_back({ 0, 896, 128, 128 });
	walk_up.frames.push_back({ 0, 1024, 128, 128 });
	walk_up.frames.push_back({ 0, 1152, 128, 128 });
	walk_up.speed = 0.01f;
	move_animation_pack.push_back(&walk_up);

	walk_left_up3.frames.push_back({ 1920, 640, 128, 128 });
	walk_left_up3.frames.push_back({ 1920, 768, 128, 128 });
	walk_left_up3.frames.push_back({ 1920, 896, 128, 128 });
	walk_left_up3.frames.push_back({ 1920, 1024, 128, 128 });
	walk_left_up3.frames.push_back({ 1920, 1152, 128, 128 });
	walk_left_up3.frames.push_back({ 1920, 1280, 128, 128 });
	walk_left_up3.frames.push_back({ 1920, 1408, 128, 128 });
	walk_left_up3.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_up3);

	walk_left_up2.frames.push_back({ 1792, 640, 128, 128 });
	walk_left_up2.frames.push_back({ 1792, 768, 128, 128 });
	walk_left_up2.frames.push_back({ 1792, 896, 128, 128 });
	walk_left_up2.frames.push_back({ 1792, 1024, 128, 128 });
	walk_left_up2.frames.push_back({ 1792, 1152, 128, 128 });
	walk_left_up2.frames.push_back({ 1792, 1280, 128, 128 });
	walk_left_up2.frames.push_back({ 1792, 1408, 128, 128 });
	walk_left_up2.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_up2);

	walk_left_up1.frames.push_back({ 1664, 640, 128, 128 });
	walk_left_up1.frames.push_back({ 1664, 768, 128, 128 });
	walk_left_up1.frames.push_back({ 1664, 896, 128, 128 });
	walk_left_up1.frames.push_back({ 1664, 1024, 128, 128 });
	walk_left_up1.frames.push_back({ 1664, 1152, 128, 128 });
	walk_left_up1.frames.push_back({ 1664, 1280, 128, 128 });
	walk_left_up1.frames.push_back({ 1664, 1408, 128, 128 });
	walk_left_up1.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_up1);

	walk_left.frames.push_back({ 1536, 640, 128, 128 });
	walk_left.frames.push_back({ 1536, 768, 128, 128 });
	walk_left.frames.push_back({ 1536, 896, 128, 128 });
	walk_left.frames.push_back({ 1536, 1024, 128, 128 });
	walk_left.frames.push_back({ 1536, 1152, 128, 128 });
	walk_left.frames.push_back({ 1536, 1280, 128, 128 });
	walk_left.frames.push_back({ 1536, 1408, 128, 128 });
	walk_left.speed = 0.01f;
	move_animation_pack.push_back(&walk_left);

	walk_left_down3.frames.push_back({ 1408, 640, 128, 128 });
	walk_left_down3.frames.push_back({ 1408, 768, 128, 128 });
	walk_left_down3.frames.push_back({ 1408, 896, 128, 128 });
	walk_left_down3.frames.push_back({ 1408, 1024, 128, 128 });
	walk_left_down3.frames.push_back({ 1408, 1152, 128, 128 });
	walk_left_down3.frames.push_back({ 1408, 1280, 128, 128 });
	walk_left_down3.frames.push_back({ 1408, 1408, 128, 128 });
	walk_left_down3.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_down3);

	walk_left_down2.frames.push_back({ 1280, 640, 128, 128 });
	walk_left_down2.frames.push_back({ 1280, 768, 128, 128 });
	walk_left_down2.frames.push_back({ 1280, 896, 128, 128 });
	walk_left_down2.frames.push_back({ 1280, 1024, 128, 128 });
	walk_left_down2.frames.push_back({ 1280, 1152, 128, 128 });
	walk_left_down2.frames.push_back({ 1280, 1280, 128, 128 });
	walk_left_down2.frames.push_back({ 1280, 1408, 128, 128 });
	walk_left_down2.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_down2);

	walk_left_down1.frames.push_back({ 1152, 640, 128, 128 });
	walk_left_down1.frames.push_back({ 1152, 768, 128, 128 });
	walk_left_down1.frames.push_back({ 1152, 896, 128, 128 });
	walk_left_down1.frames.push_back({ 1152, 1024, 128, 128 });
	walk_left_down1.frames.push_back({ 1152, 1152, 128, 128 });
	walk_left_down1.frames.push_back({ 1152, 1280, 128, 128 });
	walk_left_down1.frames.push_back({ 1152, 1408, 128, 128 });
	walk_left_down1.speed = 0.01f;
	move_animation_pack.push_back(&walk_left_down1);

	walk_down.frames.push_back({ 1024, 640, 128, 128 });
	walk_down.frames.push_back({ 1024, 768, 128, 128 });
	walk_down.frames.push_back({ 1024, 896, 128, 128 });
	walk_down.frames.push_back({ 1024, 1024, 128, 128 });
	walk_down.frames.push_back({ 1024, 1152, 128, 128 });
	walk_down.frames.push_back({ 1024, 1280, 128, 128 });
	walk_down.frames.push_back({ 1024, 1408, 128, 128 });
	walk_down.speed = 0.01f;
	move_animation_pack.push_back(&walk_down);

	walk_right_down3.frames.push_back({ 896, 640, 128, 128 });
	walk_right_down3.frames.push_back({ 896, 768, 128, 128 });
	walk_right_down3.frames.push_back({ 896, 896, 128, 128 });
	walk_right_down3.frames.push_back({ 896, 1024, 128, 128 });
	walk_right_down3.frames.push_back({ 896, 1152, 128, 128 });
	walk_right_down3.frames.push_back({ 896, 1280, 128, 128 });
	walk_right_down3.frames.push_back({ 896, 1408, 128, 128 });
	walk_right_down3.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_down3);

	walk_right_down2.frames.push_back({ 768, 640, 128, 128 });
	walk_right_down2.frames.push_back({ 768, 768, 128, 128 });
	walk_right_down2.frames.push_back({ 768, 896, 128, 128 });
	walk_right_down2.frames.push_back({ 768, 1024, 128, 128 });
	walk_right_down2.frames.push_back({ 768, 1152, 128, 128 });
	walk_right_down2.frames.push_back({ 768, 1280, 128, 128 });
	walk_right_down2.frames.push_back({ 768, 1408, 128, 128 });
	walk_right_down2.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_down2);

	walk_right_down1.frames.push_back({ 640, 640, 128, 128 });
	walk_right_down1.frames.push_back({ 640, 768, 128, 128 });
	walk_right_down1.frames.push_back({ 640, 896, 128, 128 });
	walk_right_down1.frames.push_back({ 640, 1024, 128, 128 });
	walk_right_down1.frames.push_back({ 640, 1152, 128, 128 });
	walk_right_down1.frames.push_back({ 640, 1280, 128, 128 });
	walk_right_down1.frames.push_back({ 640, 1408, 128, 128 });
	walk_right_down1.speed = 0.01f;
	move_animation_pack.push_back(&walk_right_down1);

	//------------Mutalisk DEAD-----------------------
	dead.frames.push_back({ 0, 1536, 128, 128 });
	dead.frames.push_back({ 128, 1536, 128, 128 });
	dead.frames.push_back({ 256, 1536, 128, 128 });
	dead.frames.push_back({ 384, 1536, 128, 128 });
	dead.frames.push_back({ 512, 1536, 128, 128 });
	dead.frames.push_back({ 640, 1536, 128, 128 });
	dead.frames.push_back({ 768, 1536, 128, 128 });
	dead.frames.push_back({ 896, 1536, 128, 128 });
	dead.speed = 0.01f;
	dead.loop = false;
	//----------------------------------------------

	attack_right.frames.push_back({ 256, 0, 64, 64 });
	attack_right.frames.push_back({ 256, 128, 64, 64 });
	attack_right.frames.push_back({ 256, 256, 64, 64 });
	attack_right.frames.push_back({ 256, 384, 64, 64 });
	attack_right.frames.push_back({ 256, 512, 64, 64 });
	attack_right.frames.push_back({ 256, 640, 64, 64 });
	attack_right.frames.push_back({ 256, 768, 64, 64 });
	attack_right.speed = 0.008f;
	attack_animation_pack.push_back(&attack_right);

	attack_right_up.frames.push_back({ 128, 0, 64, 64 });
	attack_right_up.frames.push_back({ 128, 128, 64, 64 });
	attack_right_up.frames.push_back({ 128, 256, 64, 64 });
	attack_right_up.frames.push_back({ 128, 384, 64, 64 });
	attack_right_up.frames.push_back({ 128, 512, 64, 64 });
	attack_right_up.frames.push_back({ 128, 640, 64, 64 });
	attack_right_up.frames.push_back({ 128, 768, 64, 64 });
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
	specialization = HYDRALISK;
	flying = false;

	// UI paramters
	selection_type = { 28, 9, 32, 19 };
	circle_selection_offset = { 0, -1 };
	offset_life = { -16, 18 };

	// Lifes attributes
	max_hp = current_hp = 75.0f;
	max_hp_bars = 6;

	// Attack values and properties
	range_of_vision = 300;
	range_to_attack = 130;
	damage = 5.0f;
	attack_frequency = 200.0f;
	time_to_die = 500.0f;

	// PathFinding and movement variables
	speed = 8.0f;
}

Hydralisk::~Hydralisk()
{
	SDL_DestroyTexture(tex);
}

// Method that assign an animation according to its orientation
void Hydralisk::setAnimationFromDirection()
{
	switch (state)
	{
	case(IDLE) :
	case(MOVE) :
	case(MOVE_ALERT) :
	case(MOVE_ALERT_TO_ATTACK) :
	case(WAITING_PATH_MOVE) :
	case(WAITING_PATH_MOVE_ALERT) :
	case(WAITING_PATH_MOVE_ALERT_TO_ATTACK) :
	case(ATTACK) :
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
	}
}

