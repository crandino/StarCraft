#include "Red.h"
#include "p2Log.h"

Red::Red(iPoint &p)
{
	// Positions and dimensions
	center = { (float)p.x, (float)p.y };

	tex_width = 145;
	tex_height = 145;
	collider_offset.set(25, 86);
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

	// Animations and FX
	tex = app->tex->loadTexture("Building/Red.png"); //Sprites/Animations etc..
	idle.setAnimations(0, 0, 145, 145, 15, 1, 15);
	idle.speed = 0.009f;
	idle.loop = true;
	current_animation = &idle;

	// Colliders
	coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 96, 59 }, COLLIDER_BUILDING);

	// Another stuff
	specialization = RED;
	max_hp = 350;
	current_hp = 350.0f;
	max_hp_bars = 10;
	offset_life = { -23, 35 };

	range_of_vision = range_to_attack = 150;
	damage = 0.0f; //we change it according to the amount of marines inside;
	attack_frequency = 200.0f;

	state = IDLE;
	faction = PLAYER;
	selection_type = { 261, 1, 94, 56 };
	circle_selection_offset = { 0, 25 };
}

Red::~Red()
{
	SDL_DestroyTexture(tex);
}

bool Red::update(float dt)
{
	switch (state)
	{
	case IDLE:
		if (timer_attack.read() >= (attack_frequency * attack_frequency_multiplier))
		{
			buff();
			timer_attack.start();
		}
		break;
	case MOVE:
		break;
	case MOVE_ALERT:
		break;
	case MOVE_ALERT_TO_ATTACK:
		break;
	case ATTACK:
		break;
	case DYING:
		//current_animation = &dead;
		if (targets.size() > 0)
		{
			for (list<Entity*>::iterator it = targets.begin(); it != targets.end(); it++)
			{
				it._Ptr->_Myval->damage_multiplier /= 1.2f;
			}
			targets.clear();
		}
		if (timer_to_check.read() >= time_to_die)
		{
			to_delete = true;
			coll->to_delete = true;
		}
		break;
	case WAITING_PATH_MOVE:
		break;
	case WAITING_PATH_MOVE_ALERT:
		break;
	case WAITING_PATH_MOVE_ALERT_TO_ATTACK:
		break;
	}
	return true;
}

void Red::buff()
{
	list<Entity*> last_targets = targets;
	for (list<Entity*>::iterator it = last_targets.begin(); it != last_targets.end(); it++)
	{
		it._Ptr->_Myval->damage_multiplier /= 1.2f;
	}

	targets = searchEntitiesInRange(this, range_to_attack);
	for (list<Entity*>::iterator it = targets.begin(); it != targets.end(); it++)
	{
		it._Ptr->_Myval->damage_multiplier *= 1.2f;
	}
}