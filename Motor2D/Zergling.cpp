#include "Zergling.h"
#include "PathFinding.h"

Zergling::Zergling(iPoint &p)
{
	// Graphics
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
	max_hp = 35;
	current_hp = 35.0f;
	max_hp_bars = 6;

	// Attack values and properties
	range_of_vision = 200;
	range_to_attack = 25;
	damage = 5.0f;
	attack_frequency = 80.0f;

	// PathFinding and movement variables
	speed = 12.5f;
}

Zergling::~Zergling()
{ }

bool Zergling::update(float dt)
{
	checkUnitDirection();
	setAnimationFromDirection();   // This sets animation according to their angle direction
	coll->setPos(center.x + collider_offset.x, center.y + collider_offset.y);

	switch (state)
	{
	case IDLE:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchEnemy();
			if (target_to_attack != NULL)
				newEntityFound();
			else if (faction == COMPUTER && target_pos.x != -1 && target_pos.y != -1 &&
				(range_of_vision / 2) < (abs(center.x - target_pos.x) + abs(center.y - target_pos.y) - (coll->rect.w / 2 + coll->rect.h / 2) / 2))
				app->entity_manager->SetEnemyToPos(this, target_pos);
			timer_to_check.start();
		}
		break;
	case MOVE:
		if (has_target)
			move(dt);
		break;
	case MOVE_ALERT:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchEnemy();
			if (target_to_attack != NULL)
				newEntityFound();
			timer_to_check.start();
		}
		if (has_target)
			move(dt);
		break;
	case MOVE_ALERT_TO_ATTACK:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchEnemy();
			if (target_to_attack != NULL)
				newEntityFound();
			else
			{
				has_target = false;
				state = IDLE;
			}
			timer_to_check.start();
		}
		if (has_target)
			move(dt);
		break;
	case ATTACK:
		if (timer_attack.read() >= (attack_frequency * attack_frequency_multiplier))
		{
			if (area_attack)
			{
				list<Entity*> targets = searchEntitiesInRange(target_to_attack, area_range);
				while (targets.begin() != targets.end())
				{
					attackWithoutRange(targets.front());
					targets.pop_front();
				}
				if (!attack(target_to_attack))
				{
					state = IDLE;
					target_to_attack = NULL;
				}
			}
			else
				if (!attack(target_to_attack))
				{
					state = IDLE;
					target_to_attack = NULL;
				}
			timer_attack.start();

			Entity* target = target_to_attack;
			target_to_attack = searchEnemy();
			if (target_to_attack != NULL && (target == NULL || target->center != target_to_attack->center))
				newEntityFound();
		}
		break;
	case DYING:
		if (sound_active == true)
		{
			app->audio->playFx(app->entity_manager->fx_zergling_death, 0);
			sound_active = false;
		}
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
			timer_to_check.start();
		}
		break;
	case WAITING_PATH_MOVE_ALERT:
		if (app->path->getPathFound(id, path))
		{
			has_target = true;
			state = MOVE_ALERT;
			timer_to_check.start();
		}
		break;
	case WAITING_PATH_MOVE_ALERT_TO_ATTACK:
		if (app->path->getPathFound(id, path))
		{
			has_target = true;
			state = MOVE_ALERT_TO_ATTACK;
			timer_to_check.start();
		}
		break;
	}

	if (grouped && (state != MOVE && state != MOVE_ALERT && state != WAITING_PATH_MOVE && state != WAITING_PATH_MOVE_ALERT && state != IDLE))
		grouped = false;

	return true;
}

// Method that assign an animation according to its orientation
void Zergling::setAnimationFromDirection()
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

void Zergling::draw()
{
	if (app->fog_of_war->isVisible(pos.x, pos.y))
		app->render->blit(app->entity_manager->zergling_tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
}
