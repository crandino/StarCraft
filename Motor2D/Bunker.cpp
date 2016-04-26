#include "Bunker.h"
#include "p2Log.h"

Bunker::Bunker(iPoint &p)
{
	// Positions and dimensions
	center = { (float)p.x, (float)p.y };

	tex_width = 96;
	tex_height = 128;
	collider_offset.set(0, 36);
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	tile_pos = app->map->worldToMap(app->map->data.front(), center.x, center.y);

	// Animations and FX
	tex = app->tex->loadTexture("Building/Bunker.png"); //Sprites/Animations etc..
	bunker_attack_fx = app->audio->loadFx("Audio/FX/Marine/Marine_attack.wav");
	idle.frames.push_back({ 0, 0, 96, 128 });
	idle.speed = 1.0f;
	idle.loop = false;
	current_animation = &idle;

	// Colliders
	coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 96, 59 }, COLLIDER_BUILDING);

	// Another stuff
	specialization = BUNKER;
	max_hp = 350;
	current_hp = 350.0f;
	max_hp_bars = 10;
	offset_life = { -23, 35 };
	max_capacity = 4;

	range_of_vision = range_to_attack = 150;
	damage = 0; //we change it according to the amount of marines inside;
	attack_delay = 200.0f;

	state = IDLE;
	faction = PLAYER;
	selection_type = { 261, 1, 94, 56 };
	circle_selection_offset = { 0, 25 };
}

bool Bunker::update(float dt)
{
	switch (state)
	{
	case IDLE:
		if (specialization == BUNKER)
		{
			Bunker* bunker = (Bunker*)this;
			if (bunker->units_inside.size() > 0)
			{
				if (timer_to_check.read() >= TIME_TO_CHECK)
				{
					target_to_attack = searchNearestEnemy();
					if (target_to_attack != NULL)
						state = ATTACK;
					timer_to_check.start();
				}
			}
		}
		break;
	case MOVE:
		break;
	case MOVE_ALERT:
		break;
	case ATTACK:
		if (units_inside.size() > 0)
		{
			app->audio->playFx(bunker_attack_fx);
			damage = units_inside.size() * 4;
			if ((timer_attack_delay.read() >= attack_delay))
			{
				if (!attack())
					state = IDLE;
				timer_attack_delay.start();
				target_to_attack = searchNearestEnemy();
			}
		}

	case DYING:
		//current_animation = &dead;
		if (timer_to_check.read() >= time_to_die)
		{
			//leave_bunker();
			to_delete = true;
			coll->to_delete = true;
		}
		break;
	case WAITING_PATH_MOVE:
		break;
	case WAITING_PATH_MOVE_ALERT:
		break;
	}
	return true;
}

bool Bunker::getEntityInside(Entity* entity)
{
	bool ret = false;

	if (units_inside.size() <= max_capacity)
	{
		units_inside.insert(pair<uint, Entity*>(entity->id, entity));
		Marine *m = (Marine*)entity;
		m->inside_bunker = true;
	}

	return ret;
}

//void leave_bunker() {
//	if (!units_inside.empty())
//	{
//		map<uint, Entity*>::iterator it = units_inside.begin();
//		for (; it != units_inside.end(); ++it)
//		{
//			it->second->inside_bunker = false;
//			it->second->to_delete = false;
//			app->entity_manager->active_entities.insert(pair<uint, Entity*>(it->first, it->second));
//			//++capacity;
//		}
//		units_inside.clear();
//	}
//}

bool Bunker::attack()
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
			}
			ret = true;
		}
	}
	return ret;
}