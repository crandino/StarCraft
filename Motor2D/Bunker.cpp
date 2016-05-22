#include "Bunker.h"
#include "PathFinding.h"
#include "p2Log.h"
#include "GuiImage.h"
#include "GuiLabel.h"
#include "EntityManager.h"

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
	fx_attack = app->audio->loadFx("Audio/FX/Marine/Marine_attack.wav");
	fx_entering = app->audio->loadFx("Audio/FX/Buildings/BunkerOpenDoor.wav");
	fx_leaving = app->audio->loadFx("Audio/FX/Buildings/BunkerCloseDoor.wav");

	//IDLE Animations
	idle.frames.push_back({ 0, 0, 96, 128 });
	idle.speed = 1.0f;
	idle.loop = false;

	//Particle Animations
	attack_up.anim.setAnimations(0, 0, 64, 64, 2, 1, 2);
	attack_up.anim.speed = 0.009f;
	attack_up.anim.loop = true;

	attack_right_up.anim.setAnimations(128, 0, 64, 64, 2, 1, 2);
	attack_right_up.anim.speed = 0.009f;
	attack_right_up.anim.loop = true;

	attack_right.anim.setAnimations(128, 0, 64, 64, 2, 1, 2);
	attack_right.anim.speed = 0.009f;
	attack_right.anim.loop = true;

	attack_right_down.anim.setAnimations(256, 0, 64, 64, 2, 1, 2);
	attack_right_down.anim.speed = 0.009f;
	attack_right_down.anim.loop = true;

	attack_down.anim.setAnimations(384, 0, 64, 64, 2, 1, 2);
	attack_down.anim.speed = 0.009f;
	attack_down.anim.loop = true;

	attack_left_down.anim.setAnimations(640, 0, 64, 64, 2, 1, 2);
	attack_left_down.anim.speed = 0.009f;
	attack_left_down.anim.loop = true;

	attack_left.anim.setAnimations(512, 0, 64, 64, 2, 1, 2);
	attack_left.anim.speed = 0.009f;
	attack_left.anim.loop = true;

	attack_left_up.anim.setAnimations(512, 0, 64, 64, 2, 1, 2);
	attack_left_up.anim.speed = 0.009f;
	attack_left_up.anim.loop = true;

	//Explosion

	explosion.anim.setAnimations(0, 0, 128, 128, 1, 9, 9);
	explosion.anim.speed = 0.009f;
	explosion.anim.loop = false;



	current_animation = &idle;

	// Colliders
	coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 96, 59 }, COLLIDER_BUILDING);

	// Another stuff
	specialization = BUNKER;
	max_hp = 200;

	current_hp = 200.0f;
	max_hp_bars = 10;
	offset_life = { -23, 35 };
	max_capacity = 4;

	range_of_vision = 400;
	range_to_attack = 300;
	damage = 0.0f; //we change it according to the amount of marines inside;
	attack_frequency = 625.0f;

	state = IDLE;
	faction = PLAYER;
	selection_type = { 261, 1, 94, 56 };
	circle_selection_offset = { 0, 25 };
}

Bunker::~Bunker()
{
	SDL_DestroyTexture(tex);
}

bool Bunker::update(float dt)
{

	//Bunker info for gui----------------------------------------------
	if (this != NULL)
	{
		for (map<uint, Entity*>::iterator it = app->entity_manager->selection.begin(); it != app->entity_manager->selection.end();++it)
		{
			if (it->second == this)
			{
				sprintf_s(bunker_info, 16, "Soldiers: %u / 4", units_inside.size());
				app->gui->bunkerInfo->setText(bunker_info, 3);
			}
		}
	}
	//------------------------------------------------------------------

	checkDirection();
	setParticleBehaviour();
	if (app->game_manager->game_state == WIN || app->game_manager->game_state == LOSE)
	{
		resetParticle();
		app->gui->raynor_indicator->draw_element = false;
	}

	switch (state)
	{
	case IDLE:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchEnemy();
			if (target_to_attack != NULL)
				state = ATTACK;
			timer_to_check.start();
		}
		break;
	case MOVE:
		break;
	case MOVE_ALERT:
		break;
	case MOVE_ALERT_TO_ATTACK:
		break;
	case ATTACK:
		if (units_inside.size() > 0)
		{
			app->audio->playFx(fx_attack);
			if (timer_attack.read() >= (attack_frequency * attack_frequency_multiplier))
			{
				if (!attack())
					state = IDLE;
				timer_attack.start();
				target_to_attack = searchEnemy();
			}
		}
		break;
	case DYING:
		//current_animation = &dead;
		if (timer_to_check.read() >= time_to_die)
		{
			getEntitiesOutside();
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

bool Bunker::getEntityInside(Unit* entity)
{

	if (units_inside.size() < max_capacity)
	{
		app->audio->playFx(fx_entering, 0);
		units_inside.insert(pair<uint, Unit*>(entity->id, entity));
		entity->to_delete = true;
		if (entity->specialization == MARINE)
		{
			Marine *u = (Marine*)entity;
			u->inside_bunker = true;
			u->coll->disable();
			u->bunker_to_fill = NULL;
		}
		else if (entity->specialization == FIREBAT)
		{
			Firebat *u = (Firebat*)entity;
			u->inside_bunker = true;
			u->coll->disable();
			u->bunker_to_fill = NULL;
		}
		else if (entity->specialization == JIM_RAYNOR)
		{
			JimRaynor *u = (JimRaynor*)entity;
			u->inside_bunker = true;
			u->coll->disable();
			u->bunker_to_fill = NULL;
			raynor_inside = true;
			app->gui->raynor_indicator->setLocalPos(center.x - 16, pos.y);
			app->gui->raynor_indicator->enable_element();
		}

		return true;
	}

	return false;
}

bool Bunker::getEntitiesOutside()
{
	bool ret = false;
	if (this != NULL && !units_inside.empty())
	{
		for (map<uint, Unit*>::iterator it = units_inside.begin(); it != units_inside.end();)
		{
			app->audio->playFx(fx_leaving, 0);
			if (!app->path->isWalkable(it->second->tile_pos))
			{
				it->second->tile_pos = app->path->findNearestWalkableTile(it->second->tile_pos, app->game_manager->command_center_position, 25);
				it->second->center = app->map->mapToWorld(app->map->data.back(), it->second->tile_pos.x, it->second->tile_pos.y);
				it->second->calculePos();
			}

			app->entity_manager->active_entities.insert(pair<uint, Unit*>(it->second->id, it->second));
			
			if (it->second->specialization == JIM_RAYNOR)
			{
				app->gui->raynor_indicator->disable_element();
				raynor_inside = false;
			}
				
			Marine *m = (Marine*)it->second;
			m->coll->enable();
			m->to_delete = false;
			m->inside_bunker = false;
			it = units_inside.erase(it);
			ret = true;
		}
	}
	return ret;
}

bool Bunker::attack()
{
	bool ret = false;
	if (target_to_attack != NULL && target_to_attack->state != DYING)
	{
		int d = abs(center.x - target_to_attack->center.x) + abs(center.y - target_to_attack->center.y);
		d -= ((coll->rect.w / 2 + coll->rect.h / 2) / 2 + (target_to_attack->coll->rect.w / 2 + target_to_attack->coll->rect.h / 2) / 2);
		if (d <= range_to_attack)
		{
			damage = 0.0f;
			for (map<uint, Unit*>::iterator it = units_inside.begin(); it != units_inside.end(); it++)
				damage += it->second->damage / 2;
			if ((target_to_attack->current_hp -= (damage * damage_multiplier)) <= 0.0f)
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
void Bunker::checkDirection()
{
	if (state == ATTACK && target_to_attack != NULL)
	{
		direction = { (target_to_attack->tile_pos.x - tile_pos.x), (target_to_attack->tile_pos.y - tile_pos.y) };
	}
	angle = round(direction.getAngle());
}

void Bunker::setParticleBehaviour()
{
	switch (state)
	{
	case IDLE:
		resetParticle();
		break;
	case ATTACK:
		if (units_inside.size() > 0)
		{
			if (angle > 360)
			{
				angle -= 360.f;
			}
			// From 0 to 180 degrees
			if (angle >= 0.f && angle < 45.0f)
			{
				if (particle != NULL && !attack_right.on)
				{
					resetParticle();
				}

				if (!attack_right.on)
				{

					particle_offset = { 21, -12 };
					particle = app->particle->addParticle(attack_right, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, app->particle->bunker_attack);
					attack_right.on = true;
				}
			}

			if (angle >= 45.f && angle < 90.0f)
			{
				if (particle != NULL && !attack_right_up.on)
				{
					resetParticle();
				}

				if (!attack_right_up.on)
				{

					particle_offset = { 21, -12 };
					particle = app->particle->addParticle(attack_right_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, app->particle->bunker_attack);
					attack_right_up.on = true;
				}
			}

			if (angle >= 90.f && angle < 135.f)
			{
				if (particle != NULL && !attack_up.on)
				{
					resetParticle();
				}

				if (!attack_up.on)
				{

					particle_offset = { 0, -25 };
					particle = app->particle->addParticle(attack_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, app->particle->bunker_attack);
					attack_up.on = true;
				}
			}

			if (angle >= 135.f && angle < 180.f)
			{
				if (particle != NULL && !attack_left_up.on)
				{
					resetParticle();
				}

				if (!attack_left_up.on)
				{

					particle_offset = { -12, -19 };
					particle = app->particle->addParticle(attack_left_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, app->particle->bunker_attack);
					attack_left_up.on = true;
				}
			}

			// From 180 to 360 degrees
			if (angle >= 180.f && angle < 225.f)
			{
				if (particle != NULL && !attack_left.on)
				{
					resetParticle();
				}

				if (!attack_left.on)
				{

					particle_offset = { -12, -19 };
					particle = app->particle->addParticle(attack_left, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, app->particle->bunker_attack);
					attack_left.on = true;
				}
			}

			if (angle >= 225.f && angle < 270.f)
			{
				if (particle != NULL && !attack_left_down.on)
				{
					resetParticle();
				}

				if (!attack_left_down.on)
				{

					particle_offset = { -14, -7 };
					particle = app->particle->addParticle(attack_left_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, app->particle->bunker_attack);
					attack_left_down.on = true;
				}
			}

			if (angle >= 270.f && angle < 315.f)
			{
				if (particle != NULL && !attack_down.on)
				{
					resetParticle();
				}

				if (!attack_down.on)
				{

					particle_offset = { 0, -5 };
					particle = app->particle->addParticle(attack_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, app->particle->bunker_attack);
					attack_down.on = true;
				}
			}

			if (angle >= 315.f && angle < 360.f)
			{
				if (particle != NULL && !attack_right_down.on)
				{
					resetParticle();
				}

				if (!attack_right_down.on)
				{

					particle_offset = { 18, -6 };
					particle = app->particle->addParticle(attack_right_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, app->particle->bunker_attack);
					attack_right_down.on = true;
				}
			}
		}
		break;
	case DYING:
		resetParticle();
		particle = app->particle->addParticle(explosion, center.x, center.y, 0, 0, 1, app->particle->explosion_small);
		break;
	}
}
void Bunker::resetParticle()
{
	if (attack_up.on || attack_right_up.on || attack_right.on || attack_right_down.on || attack_down.on || attack_left_down.on || attack_left.on || attack_left_up.on)
	{
		attack_up.on = false;
		attack_right_up.on = false;
		attack_right.on = false;
		attack_right_down.on = false;
		attack_down.on = false;
		attack_left_down.on = false;
		attack_left.on = false;
		attack_left_up.on = false;
		particle->on = false;
		particle->alive = false;
	}
}

void Bunker::draw()
{
	app->render->blit(app->entity_manager->bunker_tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
}