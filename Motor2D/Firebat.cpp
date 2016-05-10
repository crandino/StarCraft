#include "Firebat.h"
#include "Bunker.h"
#include "PathFinding.h"
#include "GameManager.h"

Firebat::Firebat(iPoint &p)
{
	//Graphics
	tex_width = tex_height = 32;
	//---------------Idle Animation----------------
	idle_right.setAnimations(128, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_right);

	idle_right_up.setAnimations(64, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_right_up);

	idle_up.setAnimations(0, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_up);

	idle_left_up.setAnimations(448, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_left_up);

	idle_left.setAnimations(384, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_left);

	idle_left_down.setAnimations(320, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_left_down);

	idle_down.setAnimations(256, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_down);

	idle_right_down.setAnimations(192, 64, 32, 32, 1, 1, 1);
	idle_animation_pack.push_back(&idle_right_down);
	//----------------------------------------------

	//--------------Walking Animations--------------
	walk_right.setAnimations(128, 96, 32, 32, 1, 7, 7);
	walk_right.speed = 0.02f;
	move_animation_pack.push_back(&walk_right);

	walk_right_up.setAnimations(64, 96, 32, 32, 1, 7, 7);
	walk_right_up.speed = 0.02f;
	move_animation_pack.push_back(&walk_right_up);

	walk_up.setAnimations(0, 96, 32, 32, 1, 7, 7);
	walk_up.speed = 0.02f;
	move_animation_pack.push_back(&walk_up);

	walk_left_up.setAnimations(448, 96, 32, 32, 1, 7, 7);
	walk_left_up.speed = 0.02f;
	move_animation_pack.push_back(&walk_left_up);

	walk_left.setAnimations(384, 96, 32, 32, 1, 7, 7);
	walk_left.speed = 0.02f;
	move_animation_pack.push_back(&walk_left);

	walk_left_down.setAnimations(320, 96, 32, 32, 1, 7, 7);
	walk_left_down.speed = 0.02f;
	move_animation_pack.push_back(&walk_left_down);

	walk_down.setAnimations(256, 96, 32, 32, 1, 7, 7);
	walk_down.speed = 0.02f;
	move_animation_pack.push_back(&walk_down);

	walk_right_down.setAnimations(192, 96, 32, 32, 1, 7, 7);
	walk_right_down.speed = 0.02f;
	move_animation_pack.push_back(&walk_right_down);
	//----------------------------------------------

	//-----------Firebat ATTACK----------------------
	attack_right.setAnimations(128, 0, 32, 32, 1, 2, 2);
	attack_right.speed = 0.002f;
	attack_animation_pack.push_back(&attack_right);

	attack_right_up.setAnimations(64, 0, 32, 32, 1, 2, 2);
	attack_right_up.speed = 0.002f;
	attack_animation_pack.push_back(&attack_right_up);

	attack_up.setAnimations(0, 0, 32, 32, 1, 2, 2);
	attack_up.speed = 0.003f;
	attack_animation_pack.push_back(&attack_up);

	attack_left_up.setAnimations(448, 0, 32, 32, 1, 2, 2);
	attack_left_up.speed = 0.002f;
	attack_animation_pack.push_back(&attack_left_up);

	attack_left.setAnimations(384, 0, 32, 32, 1, 2, 2);
	attack_left.speed = 0.002f;
	attack_animation_pack.push_back(&attack_left);

	attack_left_down.setAnimations(320, 0, 32, 32, 1, 2, 2);
	attack_left_down.speed = 0.002f;
	attack_animation_pack.push_back(&attack_left_down);

	attack_down.setAnimations(256, 0, 32, 32, 1, 2, 2);
	attack_down.speed = 0.002f;
	attack_animation_pack.push_back(&attack_down);

	attack_right_down.setAnimations(192, 0, 32, 32, 1, 2, 2);
	attack_right_down.speed = 0.002f;
	attack_animation_pack.push_back(&attack_right_down);
	//----------------------------------------------

	//------------Firebat DEAD----------------------
	explosion_dead.anim.setAnimations(0, 0, 128, 128, 1, 9, 9);
	explosion_dead.anim.speed = 0.02f;
	explosion_dead.anim.loop = false;
	//----------------------------------------------
	
	//-----------Firebat Particles------------------
	fire_up.anim.setAnimations(0, 0, 80, 72, 1, 13, 13);
	fire_up.anim.speed = 0.02f;
	fire_up.anim.loop = true;

	fire_right_up.anim.setAnimations(324, 0, 80, 72, 1, 13, 13);
	fire_right_up.anim.speed = 0.02f;
	fire_right_up.anim.loop = true;

	fire_right.anim.setAnimations(163, 0, 80, 72, 1, 13, 13);
	fire_right.anim.speed = 0.02f;
	fire_right.anim.loop = true;

	fire_right_down.anim.setAnimations(487, 0, 80, 72, 1, 13, 13);
	fire_right_down.anim.speed = 0.02f;
	fire_right_down.anim.loop = true;

	fire_down.anim.setAnimations(80, 0, 80, 72, 1, 13, 13);
	fire_down.anim.speed = 0.02f;
	fire_down.anim.loop = true;

	fire_left_down.anim.setAnimations(569, 0, 80, 72, 1, 13, 13);
	fire_left_down.anim.speed = 0.02f;
	fire_left_down.anim.loop = true;

	fire_left.anim.setAnimations(245, 0, 80, 72, 1, 13, 13);
	fire_left.anim.speed = 0.02f;
	fire_left.anim.loop = true;

	fire_left_up.anim.setAnimations(409, 0, 80, 72, 1, 13, 13);
	fire_left_up.anim.speed = 0.02f;
	fire_left.anim.loop = true;

	//----------------------------------------------
	current_animation = &idle_up;

	// Positions and information
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	center = { (float)p.x, (float)p.y };
	tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);
	particle_offset = { 0, 0 };

	fire_up.image = app->tex->loadTexture("Particles/Shots/firebat_particles.png");
	explosion_dead.image = app->tex->loadTexture("Particles/Explosion/Small_Explosion.png");

	// Colliders
	coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 22, 30 }, COLLIDER_UNIT, app->entity_manager);
	collider_offset = { -10, -14 };

	// Characterization and behaviour
	faction = PLAYER;
	specialization = FIREBAT;
	flying = false;

	// UI paramters
	selection_type = { 3, 4, 22, 13 };
	circle_selection_offset = { 0, -1 };
	offset_life = { -16, 16 };

	// Lifes attributes
	max_hp = 40;
	current_hp = 40.0f;
	max_hp_bars = 6;

	// Attack values and properties
	range_of_vision = 300;
	range_to_attack = 100;
	damage = 5000.0f;
	attack_frequency = 800.0f;
	time_to_die = 500.0f;

	// PathFinding and movement variables
	speed = 10.0f;
}

Firebat::~Firebat()
{ }

void Firebat::move(float dt)
{
	if (path.size() > 0)
	{
		float pixels_to_move = 0;
		float total_pixels_moved = 0;
		float total_pixels_to_move = (speed * speed_multiplier) / 100 * dt;

		if (total_pixels_to_move >= 4)
			pixels_to_move = 4;

		do{
			if (total_pixels_moved + 4 > total_pixels_to_move)
				pixels_to_move = total_pixels_to_move - total_pixels_moved;

			if (path.begin()->x < tile_pos.x && path.begin()->y < tile_pos.y)
			{
				center.x -= pixels_to_move / 2;
				center.y -= pixels_to_move / 2;
			}
			else if (path.begin()->x < tile_pos.x && path.begin()->y > tile_pos.y)
			{
				center.x -= pixels_to_move / 2;
				center.y += pixels_to_move / 2;
			}
			else if (path.begin()->x > tile_pos.x && path.begin()->y > tile_pos.y)
			{
				center.x += pixels_to_move / 2;
				center.y += pixels_to_move / 2;
			}
			else if (path.begin()->x > tile_pos.x && path.begin()->y < tile_pos.y)
			{
				center.x += pixels_to_move / 2;
				center.y -= pixels_to_move / 2;
			}
			else if (path.begin()->y == tile_pos.y)
			{
				if (path.begin()->x < tile_pos.x)
					center.x -= pixels_to_move;
				else
					center.x += pixels_to_move;
			}
			else
			{
				if (path.begin()->y < tile_pos.y)
					center.y -= pixels_to_move;

				else
					center.y += pixels_to_move;
			}
			calculePos();

			if (app->map->worldToMap(app->map->data.back(), center.x, center.y) != tile_pos)
			{
				tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);
				if (tile_pos == path.back())
				{
					path.clear();
					has_target = false;
					state = IDLE;

					if (bunker_to_fill != NULL)
						bunker_to_fill->getEntityInside(this);
					break;

				}
				else if (tile_pos.x == path.begin()->x && tile_pos.y == path.begin()->y)
					path.erase(path.begin());
			}
			total_pixels_moved += pixels_to_move;

		} while (total_pixels_moved < total_pixels_to_move);
	}
	else
	{
		state = IDLE;
		has_target = false;
	}
}

// Method that assign an animation according to its orientation
void Firebat::setAnimationFromDirection()
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
		int num_animation = angle / (360 / idle_animation_pack.size());
		if (num_animation == idle_animation_pack.size())
			num_animation = 0;
		current_animation = &(*idle_animation_pack.at(num_animation));
	}

		break;
	
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

bool Firebat::update(float dt)
{
	checkUnitDirection();
	setAnimationFromDirection();   // This sets animation according to their angle direction
	setParticleBehaviour(); //IPL: well idk what happened... seems like is working well... we will do more tests... 
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
			target_to_attack = searchEnemy(false);
			if (target_to_attack != NULL)
				newEntityFound();
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
			static uint fx;
			fx = rand() % 2 + 1;
			if (fx == 1)
			{
				app->audio->playFx(app->entity_manager->fx_firebat_attack_1, 0);
			}
			if (fx == 2)
			{
				app->audio->playFx(app->entity_manager->fx_firebat_attack_2, 0);
			}
			
			if (area_attack)
			{
				list<Entity*> targets = searchEntitiesInRange(target_to_attack, area_range, false, false);
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
	{
		static uint fx;
		fx = rand() % 3 + 1;
		if (fx == 1)
		{
			app->audio->playFx(app->entity_manager->fx_firebat_death_1, 0);
		}
		if (fx == 2)
		{
			app->audio->playFx(app->entity_manager->fx_firebat_death_2, 0);
		}
		if (fx == 3)
		{
			app->audio->playFx(app->entity_manager->fx_firebat_death_3, 0);
		}

		if (current_animation->finished())
		{
			to_delete = true;
			coll->to_delete = true;
		}
		break;
	}
		
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
	return true;
}

void Firebat::resetParticle()
{
	if (fire_up.on || fire_right_up.on || fire_right.on || fire_right_down.on || fire_down.on || fire_left_down.on || fire_left.on || fire_left_up.on)
	{
		fire_up.on = false;
		fire_right_up.on = false;
		fire_right.on = false;
		fire_right_down.on = false;
		fire_down.on = false;
		fire_left_down.on = false;
		fire_left.on = false;
		fire_left_up.on = false;
		particle->on = false;
		particle->alive = false;

	}
}

void Firebat::setParticleBehaviour()
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
			if (particle != NULL && !fire_up.on)
			{
				resetParticle();
			}
			if (!fire_up.on)
			{

				particle_offset = { 5, -45 };
				particle = app->particle->addParticle(fire_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, fire_up.image);
				fire_up.on = true;

			}

		}

		if (current_animation == &attack_right_up)
		{
			if (particle != NULL && !fire_right_up.on)
			{
				resetParticle();

			}

			if (!fire_right_up.on)
			{
				fire_right_up.on = true;
				particle_offset = { 45, -40 };
				particle = app->particle->addParticle(fire_right_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, fire_up.image);
			}

		}

		if (current_animation == &attack_right)
		{
			if (particle != NULL && !fire_right.on)
			{
				resetParticle();

			}

			if (!fire_right.on)
			{
				fire_right.on = true;
				particle_offset = { 60, -5 };
				particle = app->particle->addParticle(fire_right, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, fire_up.image);
			}

		}

		if (current_animation == &attack_right_down)
		{
			if (particle != NULL && !fire_right_down.on)
			{
				resetParticle();
			}

			if (!fire_right_down.on)
			{
				fire_right_down.on = true;
				particle_offset = { 46, 30 };
				particle = app->particle->addParticle(fire_right_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, fire_up.image);
			}

		}

		if (current_animation == &attack_down)
		{
			if (particle != NULL && !fire_down.on)
			{
				resetParticle();
			}

			if (!fire_down.on)
			{
				fire_down.on = true;
				particle_offset = { 2, 40 };
				particle = app->particle->addParticle(fire_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, fire_up.image);
			}

		}

		if (current_animation == &attack_left_down)
		{
			if (particle != NULL && !fire_left_down.on)
			{
				resetParticle();
			}

			if (!fire_left_down.on)
			{
				fire_left_down.on = true;
				particle_offset = { -45, 30 };
				particle = app->particle->addParticle(fire_left_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, fire_up.image);
			}
		}

		if (current_animation == &attack_left)
		{
			if (particle != NULL && !fire_left.on)
			{
				resetParticle();
			}

			if (!fire_left.on)
			{
				fire_left.on = true;
				particle_offset = { -60, -5 };
				particle = app->particle->addParticle(fire_left, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, fire_up.image);
			}

		}

		if (current_animation == &attack_left_up)
		{
			if (particle != NULL && !fire_left_up.on)
			{
				resetParticle();
			}

			if (!fire_left_up.on)
			{
				fire_left_up.on = true;
				particle_offset = { -45, -40 };
				particle = app->particle->addParticle(fire_left_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, fire_up.image);
			}

		}
		break;
	case DYING:
		resetParticle();
		particle = app->particle->addParticle(explosion_dead, center.x, center.y, 0, 0, 1, explosion_dead.image);
		break;
	}
}

void Firebat::draw()
{
	//FOG_OF_WAR 4 - "Draw" function of a unit. Called each frame for each unit.
	//Rendering the unit only if it is visible
	if (app->fog_of_war->isVisible(pos.x, pos.y))
		app->render->blit(app->entity_manager->firebat_tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
}



