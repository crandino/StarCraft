#include "Mutalisk.h"

Mutalisk::Mutalisk(iPoint &p)
{
	//Graphics
	tex = app->tex->loadTexture("Units/Mutalisk.png");
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

Mutalisk::~Mutalisk()
{

}

// Method that assign an animation according to its orientation
void Mutalisk::setAnimationFromDirection()
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

bool Mutalisk::attack()
{
	bool ret = false;
	if (target_to_attack != NULL && target_to_attack->state != DYING)
	{
		int d = abs(center.x - target_to_attack->center.x) + abs(center.y - target_to_attack->center.y);
		d -= ((coll->rect.w / 2 + coll->rect.h / 2) / 2 + (target_to_attack->coll->rect.w / 2 + target_to_attack->coll->rect.h / 2) / 2);
		if (d <= range_to_attack)
		{
			if ((target_to_attack->current_hp -= damage) <= 0.0f)
			{
				state = IDLE;
				target_to_attack->state = DYING;
				target_to_attack = NULL;
				app->game_manager->total_units_killed_currentFrame++;
			}
			Entity* second_target_to_attack = target_to_attack->searchNearestAlly();
			if (second_target_to_attack != NULL && (second_target_to_attack->current_hp -= damage) <= 0.0f)
			{
				second_target_to_attack->state = DYING;
				app->game_manager->total_units_killed_currentFrame++;
			}
			ret = true;
		}
	}
	return ret;
}