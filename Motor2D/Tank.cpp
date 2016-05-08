#include "Tank.h"
#include "PathFinding.h"
#include "Input.h"

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
	
	siege_mode_on.frames.push_back({ 0, 384, 128, 128 });
	siege_mode_on.frames.push_back({ 128, 384, 128, 128 });
	siege_mode_on.frames.push_back({ 256, 384, 128, 128 });
	siege_mode_on.frames.push_back({ 384, 384, 128, 128 });
	siege_mode_on.frames.push_back({ 512, 384, 128, 128 });
	siege_mode_on.frames.push_back({ 640, 384, 128, 128 });
	siege_mode_on.loop = false;
	siege_mode_on.speed = 0.005f;

	siege_mode_off.frames.push_back({ 640, 384, 128, 128 });
	siege_mode_off.frames.push_back({ 512, 384, 128, 128 });
	siege_mode_off.frames.push_back({ 384, 384, 128, 128 });
	siege_mode_off.frames.push_back({ 256, 384, 128, 128 });
	siege_mode_off.frames.push_back({ 128, 384, 128, 128 });
	siege_mode_off.frames.push_back({ 0, 384, 128, 128 });
	siege_mode_off.loop = false;
	siege_mode_off.speed = 0.005f;
	siege_mode_off.paused = true;

	current_animation = &idle_down;

	// ---------- Idle Turret Animation --------
	idle_right_turret.frames.push_back({ 512, 512, 128, 128 });
	idle_right_turret.loop = false;
	idle_animation_turret_pack.push_back(&idle_right_turret);

	idle_right_up_turret.frames.push_back({ 256, 512, 128, 128 });
	idle_right_up_turret.loop = false;
	idle_animation_turret_pack.push_back(&idle_right_up_turret);

	idle_up_turret.frames.push_back({ 0, 512, 128, 128 });
	idle_up_turret.loop = false;
	idle_animation_turret_pack.push_back(&idle_up_turret);

	idle_left_up_turret.frames.push_back({ 1792, 512, 128, 128 });
	idle_left_up_turret.loop = false;
	idle_animation_turret_pack.push_back(&idle_left_up_turret);

	idle_left_turret.frames.push_back({ 1536, 512, 128, 128 });
	idle_left_turret.loop = false;
	idle_animation_turret_pack.push_back(&idle_left_turret);

	idle_left_down_turret.frames.push_back({ 1280, 512, 128, 128 });
	idle_left_down_turret.loop = false;
	idle_animation_turret_pack.push_back(&idle_left_down_turret);

	idle_down_turret.frames.push_back({ 1024, 512, 128, 128 });
	idle_down_turret.loop = false;
	idle_animation_turret_pack.push_back(&idle_down_turret);

	idle_right_down_turret.frames.push_back({ 768, 512, 128, 128 });
	idle_right_down_turret.loop = false;
	idle_animation_turret_pack.push_back(&idle_right_down_turret);

	siege_mode_on_turret.frames.push_back({ 768, 384, 128, 128 });
	siege_mode_on_turret.frames.push_back({ 896, 384, 128, 128 });
	siege_mode_on_turret.frames.push_back({ 1024, 384, 128, 128 });
	siege_mode_on_turret.frames.push_back({ 1152, 384, 128, 128 });
	siege_mode_on_turret.frames.push_back({ 1280, 384, 128, 128 });
	siege_mode_on_turret.loop = false;
	siege_mode_on_turret.speed = 0.005f;
	siege_mode_on_turret.paused = true;

	siege_mode_off_turret.frames.push_back({ 1280, 384, 128, 128 });
	siege_mode_off_turret.frames.push_back({ 1152, 384, 128, 128 });
	siege_mode_off_turret.frames.push_back({ 1024, 384, 128, 128 });
	siege_mode_off_turret.frames.push_back({ 896, 384, 128, 128 });
	siege_mode_off_turret.frames.push_back({ 768, 384, 128, 128 });	
	siege_mode_off_turret.loop = false;
	siege_mode_off_turret.speed = 0.005f;

	idle_siege_mode_right_turret.frames.push_back({ 512, 640, 128, 128 });
	idle_siege_mode_right_turret.loop = false;
	idle_animation_turret_pack.push_back(&idle_siege_mode_right_turret);

	idle_siege_mode_right_up_turret.frames.push_back({ 256, 640, 128, 128 });
	idle_siege_mode_right_up_turret.loop = false;
	idle_animation_turret_pack.push_back(&idle_siege_mode_right_up_turret);

	idle_siege_mode_up_turret.frames.push_back({ 0, 640, 128, 128 });
	idle_siege_mode_up_turret.loop = false;
	idle_siege_mode_animation_turret_pack.push_back(&idle_siege_mode_up_turret);

	idle_siege_mode_left_up_turret.frames.push_back({ 1792, 640, 128, 128 });
	idle_siege_mode_left_up_turret.loop = false;
	idle_siege_mode_animation_turret_pack.push_back(&idle_siege_mode_left_up_turret);

	idle_siege_mode_left_turret.frames.push_back({ 1536, 640, 128, 128 });
	idle_siege_mode_left_turret.loop = false;
	idle_siege_mode_animation_turret_pack.push_back(&idle_siege_mode_left_turret);

	idle_siege_mode_left_down_turret.frames.push_back({ 1280, 640, 128, 128 });
	idle_siege_mode_left_down_turret.loop = false;
	idle_siege_mode_animation_turret_pack.push_back(&idle_siege_mode_left_down_turret);

	idle_siege_mode_down_turret.frames.push_back({ 1024, 640, 128, 128 });
	idle_siege_mode_down_turret.loop = false;
	idle_siege_mode_animation_turret_pack.push_back(&idle_siege_mode_down_turret);

	idle_siege_mode_right_down_turret.frames.push_back({ 768, 640, 128, 128 });
	idle_siege_mode_right_down_turret.loop = false;
	idle_siege_mode_animation_turret_pack.push_back(&idle_siege_mode_right_down_turret);

	current_animation_turret = &idle_down_turret;

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
	area_attack = false;
	area_range = 50.0f;

	// PathFinding and movement variables
	speed = 12.0f;
}

Tank::~Tank()
{
	SDL_DestroyTexture(tex);
}

bool Tank::update(float dt)
{
	checkUnitDirection();
	setAnimationFromDirection();   // This sets animation according to their angle direction
	coll->setPos(center.x + collider_offset.x, center.y + collider_offset.y);

	if (app->input->getKey(SDL_SCANCODE_Q) == KEY_DOWN)
		siegeMode(true);
	if (app->input->getKey(SDL_SCANCODE_A) == KEY_DOWN)
		siegeMode(false);

	switch (state)
	{
	case IDLE:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchEnemy(false);
			if (target_to_attack != NULL)
				newEntityFound();
			timer_to_check.start();
		}
		break;
	case IDLE_SIEGE_MODE:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchEnemy(false);
			if (target_to_attack != NULL)
				newEntityFound();
			timer_to_check.start();
		}
		break;
	case ATTACK_SIEGE_MODE:
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
					state = IDLE_SIEGE_MODE;
					target_to_attack = NULL;
				}
			}
			else
				if (!attack(target_to_attack))
				{
					state = IDLE_SIEGE_MODE;
					target_to_attack = NULL;
				}
			timer_attack.start();

			Entity* target = target_to_attack;
			target_to_attack = searchEnemy(false);
			if (target_to_attack != NULL && (target == NULL || target->center != target_to_attack->center))
				newEntityFound();
		}
		break;
	case MOVE:
		if (has_target)
			move(dt);
		break;
	case MOVE_ALERT:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchEnemy(false);
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
			target_to_attack = searchEnemy(false);
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
				list<Entity*> targets = searchEntitiesInRange(target_to_attack, area_range, false);
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
			target_to_attack = searchEnemy(false);
			if (target_to_attack != NULL && (target == NULL || target->center != target_to_attack->center))
				newEntityFound();
		}
		break;
	case DYING:
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
	case SIEGE_MODE_ON:
		if (current_animation->finished())
		{
			current_animation_turret->resume();
			if (current_animation_turret->finished())
			{
				state = IDLE_SIEGE_MODE;
				area_attack = true;
				damage *= 2;
				path.clear();
				has_target = false;
				app->path->erase(id);
				range_to_attack *= 2;
			}
		}
		break;
	case SIEGE_MODE_OFF:
		if (current_animation_turret->finished())
		{
			current_animation->resume();
			if (current_animation->finished())
			{
				state = IDLE;
				area_attack = false;
				damage /= 2;
				range_to_attack /= 2;
			}
		}
		break;
	}
	return true;

}

// Method that assign an animation according to its orientation
void Tank::setAnimationFromDirection()
{
	switch (state)
	{
	case(IDLE) :
	{
		int num_animation = angle / (360 / idle_animation_pack.size());
		if (num_animation == idle_animation_pack.size())
			num_animation = 0;
		current_animation = &(*idle_animation_pack.at(num_animation));
		current_animation_turret = &(*idle_animation_turret_pack.at(num_animation));
		break;
	}
	case(IDLE_SIEGE_MODE):
	case(ATTACK_SIEGE_MODE):
	{
		int num_animation = angle / (360 / idle_siege_mode_animation_turret_pack.size());
		if (num_animation == idle_siege_mode_animation_turret_pack.size())
			num_animation = 0;
		current_animation_turret = &(*idle_siege_mode_animation_turret_pack.at(num_animation));
		break;
	}
	case(MOVE) :
	{
		int num_animation = angle / (360 / move_animation_pack.size());
		if (num_animation == move_animation_pack.size())
			num_animation = 0;
		current_animation = &(*move_animation_pack.at(num_animation));
		current_animation_turret = &(*idle_animation_turret_pack.at(num_animation));
		break;
	}
	case(MOVE_ALERT) :
	{
		int num_animation = angle / (360 / move_animation_pack.size());
		if (num_animation == move_animation_pack.size())
			num_animation = 0;
		current_animation = &(*move_animation_pack.at(num_animation));
		current_animation_turret = &(*idle_animation_turret_pack.at(num_animation));
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

bool Tank::start()
{
	//Sounds (file names must be changed)
	fx_sige_mode_on = app->audio->loadFx("Audio/FX/Units/Terran/SiegeTank/SiegeMode_Off.wav");
	fx_sige_mode_turret = app->audio->loadFx("Audio/FX/Units/Terran/SiegeTank/SiegeMode_On.wav");
	fx_missile_none_siege = app->audio->loadFx("Audio/FX/Units/Terran/SiegeTank/TankMissileNoneSiege.wav");
	fx_missile_siege = app->audio->loadFx("Audio/FX/Units/Terran/SiegeTank/TankMissileSiege.wav");

	return true;
}

void Tank::draw()
{
	app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	// The turret must be corrected by some pixels, but it will be done in a future, after alpha presentation.
	app->render->blit(tex, pos.x, pos.y - 10, &(current_animation_turret->getCurrentFrame()));
}

void Tank::siegeMode(bool siege_mode_flag)
{
	if (siege_mode != siege_mode_flag)
	{
		if (siege_mode_flag)
		{
			siege_mode_on.reset();
			siege_mode_on_turret.reset();
			siege_mode_on_turret.pause();
			current_animation = &siege_mode_on;
			current_animation_turret = &siege_mode_on_turret;
			state = SIEGE_MODE_ON;
		}
		else
		{
			siege_mode_off_turret.reset();
			siege_mode_off.reset();
			siege_mode_off.pause();
			current_animation = &siege_mode_off;
			current_animation_turret = &siege_mode_off_turret;
			state = SIEGE_MODE_OFF;
		}
		siege_mode = siege_mode_flag;
	}
}

void Tank::checkUnitDirection()
{
	if ((state == ATTACK || state == ATTACK_SIEGE_MODE) && target_to_attack != NULL)
	{
		direction = { (target_to_attack->tile_pos.x - tile_pos.x), (target_to_attack->tile_pos.y - tile_pos.y) };
	}
	else
	{
		if (path.size() > 0)
		{
			iPoint pos_path = *path.begin();
			direction = { (pos_path.x - tile_pos.x), (pos_path.y - tile_pos.y) };
		}
	}
	angle = round(direction.getAngle());
}

void Tank::newEntityFound()
{
	has_target = false;
	float distance = abs(center.x - target_to_attack->center.x) + abs(center.y - target_to_attack->center.y);
	distance -= ((coll->rect.w / 2 + coll->rect.h / 2) / 2 + (target_to_attack->coll->rect.w / 2 + target_to_attack->coll->rect.h / 2) / 2);
	if (distance <= range_to_attack) //If the entity isn't in the range of attack it changes the direction and state
	{
		if (siege_mode)
			state = ATTACK_SIEGE_MODE;
		else
			state = ATTACK;
		timer_attack.start();
	}
	else if (flying)
	{
		if (path.size() > 0 && path.back() == target_to_attack->tile_pos)//if the tile destination is the same than current path
		{
			has_target = true;
		}
		else
		{
			path.clear();
			path.push_back(target_to_attack->tile_pos);
			has_target = true;
			state = MOVE_ALERT_TO_ATTACK;
		}
	}
	else if (siege_mode)
	{
		state = IDLE_SIEGE_MODE;
	}
	else if (path.size() > 0 && path.back() == app->path->findNearestWalkableTile(target_to_attack->tile_pos, tile_pos, 5))//if the tile destination is the same than current path
	{
		has_target = true;
	}
	else if (app->path->createPath(tile_pos, target_to_attack->tile_pos, id) != -1) //the path to the selected entity is constructed
		state = WAITING_PATH_MOVE_ALERT_TO_ATTACK;
}