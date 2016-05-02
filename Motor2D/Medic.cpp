#include "Medic.h"
#include "PathFinding.h"

Medic::Medic(iPoint &p)
{
	// Graphics

	//------------------------------------------------

	// Positions and information
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	center = { (float)p.x, (float)p.y };
	tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

	// Colliders
	coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 30, 30 }, COLLIDER_UNIT, app->entity_manager);
	collider_offset = { -14, -16 };

	// Characterization and behaviour
	faction = PLAYER;
	specialization = MEDIC;
	flying = false;

	// Sounds
	

	// UI paramters
	selection_type = { 28, 9, 32, 19 };
	circle_selection_offset = { -2, 0 };
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
	time_to_die = 500.0f;
	healing_power = 10;

	// PathFinding and movement variables
	angle = 225.f;
	speed = 10.0f;
}

void Medic::setAnimationFromDirection()
{
	/*switch (state)
	{
	case(IDLE) :
	case(MOVE) :
	case(MOVE_ALERT) :
	case(WAITING_PATH_MOVE) :
	case(WAITING_PATH_MOVE_ALERT) :
	case(ATTACK) ://ATTACK == REPAIR for SCV
	case(DYING) :
	}*/
}

bool Medic::update(float dt)
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
			if (!heal())
				state = IDLE;
			timer_attack.start();
		}
		break;
	case DYING:
		if (timer_to_check.read() >= time_to_die)
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

bool Medic::heal()
{
	bool ret = false;
	if (target_to_attack != NULL)
	{
		float d = abs(center.x - target_to_attack->center.x) + abs(center.y - target_to_attack->center.y);
		d -= ((coll->rect.w / 2 + coll->rect.h / 2) / 2 + (target_to_attack->coll->rect.w / 2 + target_to_attack->coll->rect.h / 2) / 2);
		if (d <= range_to_attack)
		{
			if ((target_to_attack->current_hp += healing_power) >= target_to_attack->max_hp)
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