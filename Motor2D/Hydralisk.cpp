#include "Hydralisk.h"
#include "PathFinding.h"
#include "ParticleManager.h"

Hydralisk::Hydralisk(iPoint &p)
{
	//Graphics
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

	attack_right.setAnimations(512, 0, 128, 128, 1, 5, 5);
	attack_right.speed = 0.008f;
	attack_animation_pack.push_back(&attack_right);

	attack_right_up.setAnimations(256, 0, 128, 128, 1, 5, 5);
	attack_right_up.speed = 0.008f;
	attack_animation_pack.push_back(&attack_right_up);

	attack_up.setAnimations(0, 0, 128, 128, 1, 5, 5);
	attack_up.speed = 0.008f;
	attack_animation_pack.push_back(&attack_up);

	attack_left_up.setAnimations(1792, 0, 128, 128, 1, 5, 5);
	attack_left_up.speed = 0.008f;
	attack_animation_pack.push_back(&attack_left_up);

	attack_left.setAnimations(1536, 0, 128, 128, 1, 5, 5);
	attack_left.speed = 0.008f;
	attack_animation_pack.push_back(&attack_left);

	attack_left_down.setAnimations(1280, 0, 128, 128, 1, 5, 5);
	attack_left_down.speed = 0.008f;
	attack_animation_pack.push_back(&attack_left_down);

	attack_down.setAnimations(1024, 0, 128, 128, 1, 5, 5);
	attack_down.speed = 0.008f;
	attack_animation_pack.push_back(&attack_down);

	attack_right_down.setAnimations(768, 0, 128, 128, 1, 5, 5);
	attack_right_down.speed = 0.008f;
	attack_animation_pack.push_back(&attack_right_down);

	// Attack Particle
	attack_up_part.anim.setAnimations(0, 0, 88, 124, 1, 7, 7);
	attack_up_part.anim.speed = 0.008f;


	attack_right_up_part.anim.setAnimations(88, 0, 88, 124, 1, 7, 7);
	attack_right_up_part.anim.speed = 0.008f;

	attack_right_part.anim.setAnimations(176, 0, 88, 124, 1, 7, 7);
	attack_right_part.anim.speed = 0.008f;

	attack_right_down_part.anim.setAnimations(264, 0, 88, 124, 1, 7, 7);
	attack_right_down_part.anim.speed = 0.008f;

	attack_down_part.anim.setAnimations(352, 0, 88, 124, 1, 7, 7);
	attack_down_part.anim.speed = 0.008f;

	attack_left_down_part.anim.setAnimations(440, 0, 88, 124, 1, 7, 7);
	attack_left_down_part.anim.speed = 0.008f;

	attack_left_part.anim.setAnimations(528, 0, 88, 124, 1, 7, 7);
	attack_left_part.anim.speed = 0.008f;

	attack_left_up_part.anim.setAnimations(616, 0, 88, 124, 1, 7, 7);
	attack_left_up_part.anim.speed = 0.008f;

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
	specialization = HYDRALISK;
	flying = false;

	// UI paramters
	selection_type = { 28, 9, 32, 19 };
	circle_selection_offset = { 0, -1 };
	offset_life = { -16, 18 };

	// Lifes attributes
	max_hp = current_hp = 80.0f;
	max_hp_bars = 6;

	// Attack values and properties
	range_of_vision = 300;
	range_to_attack = 100;
	damage = 10.0f;
	attack_frequency = 625.0f;
	particle_frequency = 625.0f;
	time_to_die = 500.0f;

	// PathFinding and movement variables
	speed = 8.35f;
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

bool Hydralisk::update(float dt)
{
	checkUnitDirection();
	setAnimationFromDirection();// This sets animation according to their angle direction
	setParticleBehaviour();
	coll->setPos(center.x + collider_offset.x, center.y + collider_offset.y);
	if (app->game_manager->game_state == WIN || app->game_manager->game_state == LOSE)
	{
		resetParticle();
	}

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
			app->audio->playFx(app->entity_manager->fx_hydralisk_attack, 0);
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
			app->audio->playFx(app->entity_manager->fx_hydralisk_death, 0);
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

void Hydralisk::setParticleBehaviour()
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
						particle_offset = { 15, -30 };
						particle = app->particle->addParticle(attack_up_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->hydralisk_particle);
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
					particle = app->particle->addParticle(attack_right_up_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->hydralisk_particle);
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
				particle = app->particle->addParticle(attack_right_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->hydralisk_particle);
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
				particle_offset = { 30, -10 };
				particle = app->particle->addParticle(attack_right_down_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->hydralisk_particle);
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
				particle_offset = { 25, 10 };
				particle = app->particle->addParticle(attack_down_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->hydralisk_particle);
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
				particle_offset = { -17, 5 };
				particle = app->particle->addParticle(attack_left_down_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->hydralisk_particle);
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
				particle = app->particle->addParticle(attack_left_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->hydralisk_particle);
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
				particle = app->particle->addParticle(attack_left_up_part, center.x, center.y, particle_offset.x, particle_offset.y, 0.5f, app->particle->hydralisk_particle);
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
	}
}

void Hydralisk::resetParticle()
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
void Hydralisk::draw()
{
	if (app->fog_of_war->isVisible(pos.x, pos.y))
		app->render->blit(app->entity_manager->hydralisk_tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
}

