#include "Mutalisk.h"
#include "PathFinding.h"

Mutalisk::Mutalisk(iPoint &p)
{
	//Graphics
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

	//------------Mutalisk ATTACK---------------------
	attack_right.setAnimations(512, 0, 128, 128, 1, 5, 5);
	attack_right.speed = 0.01f;
	attack_animation_pack.push_back(&attack_right);

	attack_right_up.setAnimations(256, 0, 128, 128, 1, 5, 5);
	attack_right_up.speed = 0.01f;
	attack_animation_pack.push_back(&attack_right_up);

	attack_up.setAnimations(0, 0, 128, 128, 1, 5, 5);
	attack_up.speed = 0.01f;
	attack_animation_pack.push_back(&attack_up);

	attack_left_up.setAnimations(1792, 0, 128, 128, 1, 5, 5);
	attack_left_up.speed = 0.01f;
	attack_animation_pack.push_back(&attack_left_up);

	attack_left.setAnimations(1536, 0, 128, 128, 1, 5, 5);
	attack_left.speed = 0.01f;
	attack_animation_pack.push_back(&attack_left);

	attack_left_down.setAnimations(1280, 0, 128, 128, 1, 5, 5);
	attack_left_down.speed = 0.01f;
	attack_animation_pack.push_back(&attack_left_down);

	attack_down.setAnimations(1024, 0, 128, 128, 1, 5, 5);
	attack_down.speed = 0.01f;
	attack_animation_pack.push_back(&attack_down);

	attack_right_down.setAnimations(768, 0, 128, 128, 1, 5, 5);
	attack_right_down.speed = 0.01f;
	attack_animation_pack.push_back(&attack_right_down);

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

	//------------Mutalisk spore--------------------
	attack_up_part.anim.setAnimations(0, 0, 36, 36, 1, 10, 10);
	attack_up_part.anim.speed = 0.009f;


	attack_right_up_part.anim.setAnimations(0, 0, 36, 36, 1, 10, 10);
	attack_right_up_part.anim.speed = 0.009f;

	attack_right_part.anim.setAnimations(0, 0, 36, 36, 1, 10, 10);
	attack_right_part.anim.speed = 0.009f;

	attack_right_down_part.anim.setAnimations(0, 0, 36, 36, 1, 10, 10);
	attack_right_down_part.anim.speed = 0.009f;

	attack_down_part.anim.setAnimations(0, 0, 36, 36, 1, 10, 10);
	attack_down_part.anim.speed = 0.009f;

	attack_left_down_part.anim.setAnimations(0, 0, 36, 36, 1, 10, 10);
	attack_left_down_part.anim.speed = 0.009f;

	attack_left_part.anim.setAnimations(0, 0, 36, 36, 1, 10, 10);
	attack_left_part.anim.speed = 0.009f;

	attack_left_up_part.anim.setAnimations(0, 0, 36, 36, 1, 10, 10);
	attack_left_up_part.anim.speed = 0.009f;

	//------------Mutalisk HIT----------------------
	mutalisk_hit.anim.setAnimations(0, 0, 64, 64, 10, 1, 10);
	mutalisk_hit.anim.speed = 0.009f;

	

	current_animation = &walk_down;

	// Positions and information
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	center = { (float)p.x, (float)p.y };
	tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);
	particle_offset = { 0, 0 };

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
	max_hp = current_hp = 120.0f;
	max_hp_bars = 13;

	// Attack values and properties
	range_of_vision = 300;
	range_to_attack = 120;
	damage = 6.0f;
	attack_frequency = 700.0f;
	particle_frequency = 700.0f;

	// PathFinding and movement variables
	speed = 12.0f;
}

Mutalisk::~Mutalisk()
{
	SDL_DestroyTexture(tex);
}

bool Mutalisk::update(float dt)
{
	checkUnitDirection();
	setAnimationFromDirection();   // This sets animation according to their angle direction
	setParticleBehaviour();
	//particleDirection();
	coll->setPos(center.x + collider_offset.x, center.y + collider_offset.y);


	switch (state)
	{
	case IDLE:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchEnemy();
			if (target_to_attack != NULL)
			{
				newEntityFound();
				second_target_to_attack = target_to_attack->searchNearestAlly();
			}
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
			{
				newEntityFound();
				second_target_to_attack = target_to_attack->searchNearestAlly();
			}
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
			{
				newEntityFound();
				second_target_to_attack = target_to_attack->searchNearestAlly();
			}
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
					second_target_to_attack = NULL;
				}
			}
			else
			if (!attack(target_to_attack))
			{
				state = IDLE;
				target_to_attack = NULL;
				second_target_to_attack = NULL;
			}
			timer_attack.start();

			Entity* target = target_to_attack;
			target_to_attack = searchEnemy();
			if (target_to_attack != NULL)
				second_target_to_attack = target_to_attack->searchNearestAlly();
			if (target_to_attack != NULL && (target == NULL || target->center != target_to_attack->center))
			{
				newEntityFound();
			}
		}
		break;
	case DYING:
		if (sound_active == true)
		{
			app->audio->playFx(app->entity_manager->fx_mutalisk_death, 0);
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
void Mutalisk::setAnimationFromDirection()
{
	switch (state)
	{
	case(IDLE) :
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
	case(WAITING_PATH_MOVE) :
	case(WAITING_PATH_MOVE_ALERT) :
	case(WAITING_PATH_MOVE_ALERT_TO_ATTACK) :
	case(ATTACK) :
	{
		int num_animation = angle / (360 / attack_animation_pack.size());
		if (num_animation == attack_animation_pack.size())
			num_animation = 0;
		current_animation = &(*attack_animation_pack.at(num_animation));
		break;
	}
	case(DYING) :
	{
		current_animation = &dead;
		break;
	}
	}
}

bool Mutalisk::attack(Entity* target_to_attack)
{
	bool ret = false;
	if (target_to_attack != NULL && target_to_attack->state != DYING)
	{
		int d = abs(center.x - target_to_attack->center.x) + abs(center.y - target_to_attack->center.y);
		d -= ((coll->rect.w / 2 + coll->rect.h / 2) / 2 + (target_to_attack->coll->rect.w / 2 + target_to_attack->coll->rect.h / 2) / 2);
		if (d <= range_to_attack)
		{
			ret = true;
			if ((target_to_attack->current_hp -= (damage * damage_multiplier)) <= 0.0f)
			{
				ret = false;
				target_to_attack->state = DYING;
			}
			if (target_to_attack->faction == PLAYER)
				app->gui->lasts_attack_position.push_back(target_to_attack->center);
			if (second_target_to_attack != NULL && second_target_to_attack->state != DYING && (second_target_to_attack->current_hp -= (damage * damage_multiplier)) <= 0.0f)
			{
				second_target_to_attack->state = DYING;
			}
		}
	}
	return ret;
}

void Mutalisk::draw()
{
	if (app->fog_of_war->isVisible(pos.x, pos.y))
		app->render->blit(app->entity_manager->mutalisk_tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
}

void Mutalisk::setParticleBehaviour()
{
	switch (state)
	{
	case IDLE:
		resetParticle();
		break;
	case MOVE:
		resetParticle();
		break;
	case MOVE_ALERT:
		resetParticle();
		break;
	case MOVE_ALERT_TO_ATTACK:
		resetParticle();
		break;
	case ATTACK:
		if (current_animation == &attack_up)
		{
			if (particle != NULL && !attack_up_part.on)
			{
				resetParticle();
			}
			if (!attack_up_part.on)
			{
				if (timer_particle.read() >= particle_frequency)
				{
					particle_offset = { 0, -30 };
					particle = app->particle->addParticle(attack_up_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->mutalisk_spore);
					particle->speed.y = -150.0f;
					if (target_to_attack != NULL)
					particle_aux = app->particle->addParticle(mutalisk_hit, target_to_attack->center.x, target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					if (second_target_to_attack != NULL)
						particle_aux2 = app->particle->addParticle(mutalisk_hit, second_target_to_attack->center.x, second_target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					attack_up_part.on = true;
					timer_particle.start();

				}
				attack_up_part.on = false;
			}
		}

		if (current_animation == &attack_right_up)
		{
			if (particle != NULL && !attack_right_up_part.on)
			{
				resetParticle();
			}

			if (!attack_right_up_part.on)
			{
				if (timer_particle.read() >= particle_frequency)
				{
					attack_right_up_part.on = true;
					particle_offset = { 30, -20 };
					particle = app->particle->addParticle(attack_right_up_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->mutalisk_spore);
					particle->speed.x = 150.0f;
					particle->speed.y = -150.0f;
					if (target_to_attack != NULL)
					particle_aux = app->particle->addParticle(mutalisk_hit, target_to_attack->center.x, target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					if (second_target_to_attack != NULL)
						particle_aux2 = app->particle->addParticle(mutalisk_hit, second_target_to_attack->center.x, second_target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					timer_particle.start();
				}
				attack_right_up_part.on = false;
			}

		}

		if (current_animation == &attack_right)
		{
			if (particle != NULL && !attack_right_part.on)
			{
				resetParticle();

			}

			if (!attack_right_part.on)
			{
				if (timer_particle.read() >= particle_frequency)
				{
					attack_right_part.on = true;
					particle_offset = { 30, -10 };
					particle = app->particle->addParticle(attack_right_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->mutalisk_spore);
					particle->speed.x = 150.0f;
					if (target_to_attack != NULL)
					particle_aux = app->particle->addParticle(mutalisk_hit, target_to_attack->center.x, target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					if (second_target_to_attack != NULL)
						particle_aux2 = app->particle->addParticle(mutalisk_hit, second_target_to_attack->center.x, second_target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					timer_particle.start();
				}
				attack_right_part.on = false;
			}

		}

		if (current_animation == &attack_right_down)
		{
			if (particle != NULL && !attack_right_down_part.on)
			{
				resetParticle();
			}

			if (!attack_right_down_part.on)
			{
				if (timer_particle.read() >= particle_frequency)
				{
					attack_right_down_part.on = true;
					particle_offset = { 23, 10 };
					particle = app->particle->addParticle(attack_right_down_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->mutalisk_spore);
					particle->speed.x = 150.0f;
					particle->speed.y = 150.0f;
					if (target_to_attack != NULL)
					particle_aux = app->particle->addParticle(mutalisk_hit, target_to_attack->center.x, target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					if (second_target_to_attack != NULL)
						particle_aux2 = app->particle->addParticle(mutalisk_hit, second_target_to_attack->center.x, second_target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					timer_particle.start();
				}
				attack_right_down_part.on = false;
			}

		}

		if (current_animation == &attack_down)
		{
			if (particle != NULL && !attack_down_part.on)
			{
				resetParticle();
			}

			if (!attack_down_part.on)
			{
				if (timer_particle.read() >= particle_frequency)
				{
					attack_down_part.on = true;
					particle_offset = { 2, 10 };
					particle = app->particle->addParticle(attack_down_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->mutalisk_spore);
					particle->speed.y = 150.0f;
					if (target_to_attack != NULL)
					particle_aux = app->particle->addParticle(mutalisk_hit, target_to_attack->center.x, target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					if (second_target_to_attack != NULL)
						particle_aux2 = app->particle->addParticle(mutalisk_hit, second_target_to_attack->center.x, second_target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					timer_particle.start();
				}
				attack_down_part.on = false;
			}

		}

		if (current_animation == &attack_left_down)
		{
			if (particle != NULL && !attack_left_down_part.on)
			{
				resetParticle();
			}

			if (!attack_left_down_part.on)
			{
				if (timer_particle.read() >= particle_frequency)
				{
					attack_left_down_part.on = true;
					particle_offset = { -17, 15 };
					particle = app->particle->addParticle(attack_left_down_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->mutalisk_spore);
					particle->speed.x = -150.0f;
					particle->speed.y = 150.0f;
					if (target_to_attack != NULL)
					particle_aux = app->particle->addParticle(mutalisk_hit, target_to_attack->center.x, target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					if (second_target_to_attack != NULL)
						particle_aux2 = app->particle->addParticle(mutalisk_hit, second_target_to_attack->center.x, second_target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					timer_particle.start();
				}
				attack_left_down_part.on = false;
			}
		}

		if (current_animation == &attack_left)
		{
			if (particle != NULL && !attack_left_part.on)
			{
				resetParticle();
			}

			if (!attack_left_part.on)
			{
				if (timer_particle.read() >= particle_frequency)
				{
					attack_left_part.on = true;
					particle_offset = { -30, -10 };
					particle = app->particle->addParticle(attack_left_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->mutalisk_spore);
					particle->speed.x = -150.0f;
					if (target_to_attack != NULL)
					particle_aux = app->particle->addParticle(mutalisk_hit, target_to_attack->center.x, target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					if (second_target_to_attack != NULL)
						particle_aux2 = app->particle->addParticle(mutalisk_hit, second_target_to_attack->center.x, second_target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
								
					timer_particle.start();
				}
				attack_left_part.on = false;
			}

		}

		if (current_animation == &attack_left_up)
		{
			if (particle != NULL && !attack_left_up_part.on)
			{
				resetParticle();
			}

			if (!attack_left_up_part.on)
			{
				if (timer_particle.read() >= particle_frequency)
				{
					attack_left_up_part.on = true;
					particle_offset = { -20, -12 };
					particle = app->particle->addParticle(attack_left_up_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->mutalisk_spore);
					particle->speed.x = -150.0f;
					particle->speed.y = -150.0f;
					if (target_to_attack != NULL)
					particle_aux = app->particle->addParticle(mutalisk_hit, target_to_attack->center.x, target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					if (second_target_to_attack != NULL)
						particle_aux2 = app->particle->addParticle(mutalisk_hit, second_target_to_attack->center.x, second_target_to_attack->center.y, 0, 0, 1.0f, app->particle->mutalisk_hit);
					timer_particle.start();
				}
				attack_left_up_part.on = false;
			}
		}
		break;
	case DYING:
		resetParticle();
		break;
	case WAITING_PATH_MOVE:
		resetParticle();
		break;
	case WAITING_PATH_MOVE_ALERT:
		resetParticle();
		break;
	case WAITING_PATH_MOVE_ALERT_TO_ATTACK:
		resetParticle();
		break;
	case SIEGE_MODE_ON:
		resetParticle();
		break;
	case SIEGE_MODE_OFF:
		resetParticle();
		break;
	case IDLE_SIEGE_MODE:
		resetParticle();
		break;
	case ATTACK_SIEGE_MODE:
		resetParticle();
		break;
	}
}

void Mutalisk::resetParticle()
{
	if (attack_up_part.on || attack_right_up_part.on || attack_right_part.on || attack_right_down_part.on || attack_down_part.on || attack_left_down_part.on || attack_left_part.on || attack_left_up_part.on)
	{
		attack_up_part.on = false;
		attack_right_up_part.on = false;
		attack_right_part.on = false;
		attack_right_down_part.on = false;
		attack_down_part.on = false;
		attack_left_down_part.on = false;
		attack_left_part.on = false;
		attack_left_up_part.on = false;
		particle->on = false;
		particle->alive = false;
	}
}

void Mutalisk::particleDirection()
{

}
