#ifndef __SCV_H__
#define __SCV_H__

#include "Unit.h"
#include "ParticleManager.h"

class Scv : public Unit
{
public:
	// IDLE animations
	Animation	idle_up;
	Animation   idle_right_up;
	Animation   idle_right;
	Animation   idle_right_down;
	Animation   idle_down;
	Animation   idle_left_down;
	Animation   idle_left;
	Animation   idle_left_up;
	vector<Animation*> idle_animation_pack;

	// Walking animations
	Animation	walk_up;
	Animation   walk_right_up;
	Animation   walk_right;
	Animation   walk_right_down;
	Animation   walk_down;
	Animation   walk_left_down;
	Animation   walk_left;
	Animation   walk_left_up;
	vector<Animation*> move_animation_pack;

	//Repair animation
	Animation	repair_up;
	Animation	repair_right_up;
	Animation	repair_right;
	Animation	repair_right_down;
	Animation	repair_down;
	Animation	repair_left_down;
	Animation	repair_left;
	Animation	repair_left_up;
	vector<Animation*> repair_animation_pack;

	//Walking Particles
	Particle	glow_up;
	Particle	glow_right_up;
	Particle	glow_right;
	Particle	glow_right_down;
	Particle	glow_down;
	Particle	glow_left_down;
	Particle	glow_left;
	Particle	glow_left_up;

	//Repair Particles
	Particle	repair_up_part;
	Particle	repair_right_up_part;
	Particle	repair_right_part;
	Particle	repair_right_down_part;
	Particle	repair_down_part;
	Particle	repair_left_down_part;
	Particle	repair_left_part;
	Particle	repair_left_up_part;

	Particle	spark;
	
	//Dead Particle
	Particle	dead;



	unsigned int	scv_repair_fx;
	int				repair_power;

	Scv() {}

	Scv(iPoint &p)
	{
		// Graphics
		tex = app->tex->loadTexture("Units/scv.png");
		glow_up.image = app->tex->loadTexture("Particles/Random/scv_glow.png");
		dead.image = app->tex->loadTexture("Particles/Explosion/Small_Explosion.png");
		spark.image = app->tex->loadTexture("Particles/Random/scvspark.png");
		tex_width = 72;
		tex_height = 72;

		//---------------Idle Animation-----------------
		idle_right.frames.push_back({ 288, 0, 72, 72 });
		idle_animation_pack.push_back(&idle_right);

		idle_right_up.frames.push_back({ 144, 0, 72, 72 });
		idle_animation_pack.push_back(&idle_right_up);

		idle_up.frames.push_back({ 0, 0, 72, 72 });
		idle_animation_pack.push_back(&idle_up);

		idle_left_up.frames.push_back({ 1009, 0, 72, 72 });
		idle_animation_pack.push_back(&idle_left_up);

		idle_left.frames.push_back({ 864, 0, 72, 72 });
		idle_animation_pack.push_back(&idle_left);

		idle_left_down.frames.push_back({ 720, 0, 72, 72 });
		idle_animation_pack.push_back(&idle_left_down);

		idle_down.frames.push_back({ 577, 0, 72, 72 });
		idle_animation_pack.push_back(&idle_down);

		idle_right_down.frames.push_back({ 432, 0, 72, 72 });
		idle_animation_pack.push_back(&idle_right_down);

		//---------------Walking Animation-----------------
		walk_right.frames.push_back({ 288, 0, 72, 72 });
		move_animation_pack.push_back(&walk_right);

		walk_right_up.frames.push_back({ 144, 0, 72, 72 });
		move_animation_pack.push_back(&walk_right_up);

		walk_up.frames.push_back({ 0, 0, 72, 72 });
		move_animation_pack.push_back(&walk_up);

		walk_left_up.frames.push_back({ 1009, 0, 72, 72 });
		move_animation_pack.push_back(&walk_left_up);

		walk_left.frames.push_back({ 864, 0, 72, 72 });
		move_animation_pack.push_back(&walk_left);

		walk_left_down.frames.push_back({ 720, 0, 72, 72 });
		move_animation_pack.push_back(&walk_left_down);

		walk_down.frames.push_back({ 576, 0, 72, 72 });
		move_animation_pack.push_back(&walk_down);

		walk_right_down.frames.push_back({ 432, 0, 72, 72 });
		move_animation_pack.push_back(&walk_right_down);

		//--------------Repair Animations---------------		
		repair_right.setAnimations(288, 72, 72, 72, 1, 2, 2);
		repair_right.speed = 0.01f;
		repair_animation_pack.push_back(&repair_right);

		repair_right_up.setAnimations(144, 72, 72, 72, 1, 2, 2);
		repair_right_up.speed = 0.01f;
		repair_animation_pack.push_back(&repair_right_up);

		repair_up.setAnimations(0, 72, 72, 72, 1, 2, 2);
		repair_up.speed = 0.01f;
		repair_animation_pack.push_back(&repair_up);

		repair_left_up.setAnimations(1009, 72, 72, 72, 1, 2, 2);
		repair_left_up.speed = 0.01f;
		repair_animation_pack.push_back(&repair_left_up);

		repair_left.setAnimations(864, 72, 72, 72, 1, 2, 2);
		repair_left.speed = 0.01f;
		repair_animation_pack.push_back(&repair_left);

		repair_left_down.setAnimations(720, 72, 72, 72, 1, 2, 2);
		repair_left_down.speed = 0.01f;
		repair_animation_pack.push_back(&repair_left_down);

		repair_down.setAnimations(576, 72, 72, 72, 1, 2, 2);
		repair_down.speed = 0.01f;
		repair_animation_pack.push_back(&repair_down);

		repair_right_down.setAnimations(432, 72, 72, 72, 1, 2, 2);
		repair_right_down.speed = 0.01f;
		repair_animation_pack.push_back(&repair_right_down);
		
		// Repair Particle
		spark.anim.setAnimations(0, 0, 48, 48, 1, 10, 10);
		spark.anim.speed = 0.01f;

		//----------------------------------------------
		//-----------Walking (GLOW) PARTICLES-----------
		glow_up.anim.setAnimations(0, 0, 72, 72, 1, 4, 4);
		glow_up.anim.speed = 0.02f;

		glow_right_up.anim.setAnimations(144, 0, 72, 72, 1, 4, 4);
		glow_right_up.anim.speed = 0.02f;

		glow_right.anim.setAnimations(288, 0, 72, 72, 1, 4, 4);
		glow_right.anim.speed = 0.02f;

		glow_right_down.anim.setAnimations(432, 0, 72, 72, 1, 4, 4);
		glow_right_down.anim.speed = 0.02f;

		glow_down.anim.setAnimations(576, 0, 72, 72, 1, 4, 4);
		glow_down.anim.speed = 0.02f;

		glow_left_down.anim.setAnimations(720, 0, 72, 72, 1, 4, 4);
		glow_left_down.anim.speed = 0.02f;

		glow_left.anim.setAnimations(864, 0, 72, 72, 1, 4, 4);
		glow_left.anim.speed = 0.02f;

		glow_left_up.anim.setAnimations(1009, 0, 72, 72, 1, 4, 4);
		glow_left_up.anim.speed = 0.02f;
		//----------------------------------------------
		//--------Dead animation------------------------
		dead.anim.setAnimations(0, 0, 128, 128, 1, 9, 9);
		dead.anim.speed = 0.02f;
		dead.anim.loop = false;
		//----------------------------------------------



		// Positions and information
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		center = { (float)p.x, (float)p.y };		
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);
		particle_offset = { 0, 0 };

		// Colliders
		coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 30, 30 }, COLLIDER_UNIT, app->entity_manager);
		collider_offset = { -14, -16 };
		
		// Characterization and behaviour
		faction = PLAYER;
		specialization = SCV;
		flying = false;		

		// Sounds
		scv_repair_fx = app->audio->loadFx("Audio/FX/Units/Terran/SCV/Repair_1.wav");
			
		// UI paramters
		selection_type = { 28, 9, 32, 19 };
		circle_selection_offset = {-2, 0 };
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
		repair_power = 10;

		// PathFinding and movement variables
		speed = 10.0f;	
	}

	~Scv()
	{
		SDL_DestroyTexture(tex);
	}

	//void setAnimationFromDirection()
	//{
	//	switch (state)
	//	{
	//	case(IDLE) :
	//		//{
	//		//	int num_animation = angle / (360 / idle_animation_pack.size());
	//		//				if (num_animation == idle_animation_pack.size())
	//		//				 num_animation = 0;
	//		//				current_animation = &(*idle_animation_pack.at(num_animation));
	//		//}
	//		//	
	//		AnimationAngle();
	//	break;
	//	
	//	case(MOVE) :
	//	//{
	//	//	/*int num_animation = angle / (360 / move_animation_pack.size());
	//	//	if (num_animation == move_animation_pack.size())
	//	//		num_animation = 0;
	//	//	current_animation = &(*move_animation_pack.at(num_animation));
	//	//	*/

	//	//	break;
	//	//}
	//	AnimationAngle();
	//		break;
	//	case(MOVE_ALERT) :
	///*	{
	//		int num_animation = angle / (360 / move_animation_pack.size());
	//		if (num_animation == move_animation_pack.size())
	//			num_animation = 0;
	//		current_animation = &(*move_animation_pack.at(num_animation));
	//		break;
	//	}*/
	//	AnimationAngle();
	//		break;
	//	case(ATTACK) ://ATTACK == REPAIR for SCV
	///*	{
	//		int num_animation = angle / (360 / repair_animation_pack.size());
	//		if (num_animation == repair_animation_pack.size())
	//			num_animation = 0;
	//		current_animation = &(*repair_animation_pack.at(num_animation));
	//		break;
	//	}*/
	//	AnimationAngle();
	//		break;
	//	// WHERE is this animation?
	//	/*case(DYING) :
	//	{
	//		current_animation = &dead;
	//		break;
	//	}*/
	//	}
	//}
			
	bool update(float dt)
	{
		checkUnitDirection();
		AnimationAngle();
		//setAnimationFromDirection();   // This sets animation according to their angle direction	
		setParticleBehaviour();
		coll->setPos(center.x + collider_offset.x, center.y + collider_offset.y);
		followEntity();

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
				if(!repair())
					state = IDLE;
				timer_attack.start();
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
		}
		return true;
	}

	bool repair()
	{
		bool ret = false;
		if (target_to_attack != NULL)
		{
			float d = abs(center.x - target_to_attack->center.x) + abs(center.y - target_to_attack->center.y);
			d -= ((coll->rect.w / 2 + coll->rect.h / 2) / 2 + (target_to_attack->coll->rect.w / 2 + target_to_attack->coll->rect.h / 2) / 2);
			if (d <= range_to_attack)
			{
				if ((target_to_attack->current_hp += repair_power) >= target_to_attack->max_hp)
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

	void Scv::move(float dt)
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

						if (target_to_attack != NULL) 
							state = ATTACK;//ATTACK == REPAIR for SCV
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

	void setParticleBehaviour()
	{
		switch (state)
		{
		case IDLE:
			resetParticle();
			resetSpark();
			break;
		case MOVE:
			resetSpark();
			if (current_animation == &walk_up)
			{
				if (particle != NULL && !glow_up.on)
				{
					resetParticle();
				}
				if (!glow_up.on)
				{
					particle_offset = { 0, -3 };
					particle = app->particle->addParticle(glow_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_up.on = true;
				}
			}

			if (current_animation == &walk_right_up)
			{
				if (particle != NULL && !glow_right_up.on)
				{
					resetParticle();
				}
				if (!glow_right_up.on)
				{
					particle_offset = { -2, -5 };
					particle = app->particle->addParticle(glow_right_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_right_up.on = true;
				}
			}

			if (current_animation == &walk_right)
			{
				if (particle != NULL && !glow_right.on)
				{
					resetParticle();
				}
				if (!glow_right.on)
				{
					particle_offset = { -3, -9 };
					particle = app->particle->addParticle(glow_right, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_right.on = true;
				}
			}

			if (current_animation == &walk_right_down)
			{
				if (particle != NULL && !glow_right_down.on)
				{
					resetParticle();
				}
				if (!glow_right_down.on)
				{
					particle_offset = { 0, -3 };
					particle = app->particle->addParticle(glow_right_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_right_down.on = true;
				}
			}

			if (current_animation == &walk_down)
			{
				if (particle != NULL && !glow_down.on)
				{
					resetParticle();
				}
				if (!glow_down.on)
				{
					particle_offset = { 0, -3 };
					particle = app->particle->addParticle(glow_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_down.on = true;
				}
			}


			if (current_animation == &walk_left_down)
			{
				if (particle != NULL && !glow_left_down.on)
				{
					resetParticle();
				}
				if (!glow_left_down.on)
				{
					particle_offset = { 3, -5 };
					particle = app->particle->addParticle(glow_left_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_left_down.on = true;
				}
			}

			if (current_animation == &walk_left)
			{
				if (particle != NULL && !glow_left_down.on)
				{
					resetParticle();
				}
				if (!glow_left_down.on)
				{
					particle_offset = { 3, -3 };
					particle = app->particle->addParticle(glow_left_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_left_down.on = true;
				}
			}

			if (current_animation == &walk_left_up)
			{
				if (particle != NULL && !glow_left_up.on)
				{
					resetParticle();
				}
				if (!glow_left_up.on)
				{
					particle_offset = { 3, -5 };
					particle = app->particle->addParticle(glow_left_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_left_up.on = true;
				}
			}

			break;
		case MOVE_ALERT:
			resetParticle();
			resetSpark();
			break;
		case MOVE_ALERT_TO_ATTACK:
			resetSpark();
			if (current_animation == &walk_up)
			{
				if (particle != NULL && !glow_up.on)
				{
					resetParticle();
				}
				if (!glow_up.on)
				{
					particle_offset = { 0, -3 };
					particle = app->particle->addParticle(glow_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_up.on = true;
				}
			}

			if (current_animation == &walk_right_up)
			{
				if (particle != NULL && !glow_right_up.on)
				{
					resetParticle();
				}
				if (!glow_right_up.on)
				{
					particle_offset = { -2, -5 };
					particle = app->particle->addParticle(glow_right_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_right_up.on = true;
				}
			}

			if (current_animation == &walk_right)
			{
				if (particle != NULL && !glow_right.on)
				{
					resetParticle();
				}
				if (!glow_right.on)
				{
					particle_offset = { -3, -9 };
					particle = app->particle->addParticle(glow_right, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_right.on = true;
				}
			}

			if (current_animation == &walk_right_down)
			{
				if (particle != NULL && !glow_right_down.on)
				{
					resetParticle();
				}
				if (!glow_right_down.on)
				{
					particle_offset = { 0, -3 };
					particle = app->particle->addParticle(glow_right_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_right_down.on = true;
				}
			}

			if (current_animation == &walk_down)
			{
				if (particle != NULL && !glow_down.on)
				{
					resetParticle();
				}
				if (!glow_down.on)
				{
					particle_offset = { 0, -3 };
					particle = app->particle->addParticle(glow_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_down.on = true;
				}
			}


			if (current_animation == &walk_left_down)
			{
				if (particle != NULL && !glow_left_down.on)
				{
					resetParticle();
				}
				if (!glow_left_down.on)
				{
					particle_offset = { 3, -5 };
					particle = app->particle->addParticle(glow_left_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_left_down.on = true;
				}
			}

			if (current_animation == &walk_left)
			{
				if (particle != NULL && !glow_left_down.on)
				{
					resetParticle();
				}
				if (!glow_left_down.on)
				{
					particle_offset = { 3, -3 };
					particle = app->particle->addParticle(glow_left_down, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_left_down.on = true;
				}
			}

			if (current_animation == &walk_left_up)
			{
				if (particle != NULL && !glow_left_up.on)
				{
					resetParticle();
				}
				if (!glow_left_up.on)
				{
					particle_offset = { 3, -5 };
					particle = app->particle->addParticle(glow_left_up, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, glow_up.image);
					glow_left_up.on = true;
				}
			}
			break;
		case ATTACK:
			resetParticle();
			if (current_animation == &repair_up)
			{
				if (particle_aux != NULL && !spark.on)
				{
					resetSpark();
				}
				if (!spark.on)
				{
					particle_offset = { 10, -30 };
					particle_aux = app->particle->addParticle(spark, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, spark.image);
					spark.on = true;
				}
			}

			if (current_animation == &repair_right_up)
			{
				if (particle_aux != NULL && !spark.on)
				{
					resetSpark();
				}
				if (!spark.on)
				{
					particle_offset = { 30, -20 };
					particle_aux = app->particle->addParticle(spark, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, spark.image);
					spark.on = true;
				}
			}

			if (current_animation == &repair_right)
			{
				if (particle_aux != NULL && !spark.on)
				{
					resetSpark();
				}
				if (!spark.on)
				{
					particle_offset = { 20, -10 };
					particle_aux = app->particle->addParticle(spark, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, spark.image);
					spark.on = true;
				}
			}

			if (current_animation == &repair_right_down)
			{
				if (particle_aux != NULL && !spark.on)
				{
					resetSpark();
				}
				if (!spark.on)
				{
					particle_offset = { 8, -3 };
					particle_aux = app->particle->addParticle(spark, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, spark.image);
					spark.on = true;
				}
			}

			if (current_animation == &repair_down)
			{
				if (particle_aux != NULL && !spark.on)
				{
					resetSpark();
				}
				if (!spark.on)
				{
					particle_offset = { -10, 10 };
					particle_aux = app->particle->addParticle(spark, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, spark.image);
					spark.on = true;
				}
			}


			if (current_animation == &repair_left_down)
			{
				if (particle_aux != NULL && !spark.on)
				{
					resetSpark();
				}
				if (!spark.on)
				{
					particle_offset = { -10, 10 };
					particle_aux = app->particle->addParticle(spark, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, spark.image);
					spark.on = true;
				}
			}

			if (current_animation == &repair_left)
			{
				if (particle_aux != NULL && !spark.on)
				{
					resetSpark();
				}
				if (!spark.on)
				{
					particle_offset = { -15, -3 };
					particle_aux = app->particle->addParticle(spark, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, spark.image);
					spark.on = true;
				}
			}

			if (current_animation == &repair_left_up)
			{
				if (particle_aux != NULL && !spark.on)
				{
					resetSpark();
				}
				if (!spark.on)
				{
					particle_offset = { -20, -12 };
					particle_aux = app->particle->addParticle(spark, center.x, center.y, particle_offset.x, particle_offset.y, INT_MAX, spark.image);
					spark.on = true;
				}
			}
			break;
		case DYING:
			resetParticle();
			resetSpark();
			particle = app->particle->addParticle(dead, center.x, center.y, 0, 0, 1,dead.image);
		}
	}

	void resetParticle()
	{
		if (glow_up.on || glow_right_up.on || glow_right.on || glow_right_down.on || glow_down.on || glow_left_down.on || glow_left.on || glow_left_up.on)
		{
			glow_up.on = false;
			glow_right_up.on = false;
			glow_right.on = false;
			glow_right_down.on = false;
			glow_down.on = false;
			glow_left_down.on = false;
			glow_left.on = false;
			glow_left_up.on = false;
			particle->on = false;
			particle->alive = false;
		}

	}

	void resetSpark()
	{
		if (spark.on)
		{
			spark.on = false;
			particle_aux->on = false;
			particle_aux->alive = false;
		}
	}

	void followEntity()
	{
		if (glow_up.on || glow_right_up.on || glow_right.on || glow_right_down.on || glow_down.on || glow_left_down.on || glow_left.on || glow_left_up.on)
		{
			particle->followPoint(center.x + particle_offset.x, center.y + particle_offset.y);
		}
	}

	void AnimationAngle()
	{
		switch (state)
		{
		case IDLE:
			if (angle > 360)
			{
				angle -= 360.f;
			}
			// From 0 to 180 degrees
			if (angle >= 0.f && angle < 45.0f)
			{
				current_animation = &idle_right;
			}

			if (angle >= 45.f && angle < 90.0f)
			{
				current_animation = &idle_right_up;
			}

			if (angle >= 90.f && angle < 135.f)
			{
				current_animation = &idle_up;
			}

			if (angle >= 135.f && angle < 180.f)
			{
				current_animation = &idle_left_up;
			}

			// From 180 to 360 degrees
			if (angle >= 180.f && angle < 225.f)
			{
				current_animation = &idle_left;
			}

			if (angle >= 225.f && angle < 270.f)
			{
				current_animation = &idle_left_down;
			}

			if (angle >= 270.f && angle < 315.f)
			{
				current_animation = &idle_down;
			}

			if (angle >= 315.f && angle < 360.f)
			{
				current_animation = &idle_right_down;
			}
			break;
		case MOVE:
			if (angle > 360)
			{
				angle -= 360.f;
			}
			// From 0 to 180 degrees
			if (angle >= 0.f && angle < 45.0f)
			{
				current_animation = &walk_right;
			}

			if (angle >= 45.f && angle < 90.0f)
			{
				current_animation = &walk_right_up;
			}

			if (angle >= 90.f && angle < 135.f)
			{
				current_animation = &walk_up;
			}

			if (angle >= 135.f && angle < 180.f)
			{
				current_animation = &walk_left_up;
			}

			// From 180 to 360 degrees
			if (angle >= 180.f && angle < 225.f)
			{
				current_animation = &walk_left;
			}

			if (angle >= 225.f && angle < 270.f)
			{
				current_animation = &walk_left_down;
			}

			if (angle >= 270.f && angle < 315.f)
			{
				current_animation = &walk_down;
			}

			if (angle >= 315.f && angle < 360.f)
			{
				current_animation = &walk_right_down;
			}
			break;
		case MOVE_ALERT:
			if (angle > 360)
			{
				angle -= 360.f;
			}
			// From 0 to 180 degrees
			if (angle >= 0.f && angle < 45.0f)
			{
				current_animation = &walk_right;
			}

			if (angle >= 45.f && angle < 90.0f)
			{
				current_animation = &walk_right_up;
			}

			if (angle >= 90.f && angle < 135.f)
			{
				current_animation = &walk_up;
			}

			if (angle >= 135.f && angle < 180.f)
			{
				current_animation = &walk_left_up;
			}

			// From 180 to 360 degrees
			if (angle >= 180.f && angle < 225.f)
			{
				current_animation = &walk_left;
			}

			if (angle >= 225.f && angle < 270.f)
			{
				current_animation = &walk_left_down;
			}

			if (angle >= 270.f && angle < 315.f)
			{
				current_animation = &walk_down;
			}

			if (angle >= 315.f && angle < 360.f)
			{
				current_animation = &walk_right_down;
			}
			break;
		case MOVE_ALERT_TO_ATTACK:
			if (angle > 360)
			{
				angle -= 360.f;
			}
			// From 0 to 180 degrees
			if (angle >= 0.f && angle < 45.0f)
			{
				current_animation = &walk_right;
			}

			if (angle >= 45.f && angle < 90.0f)
			{
				current_animation = &walk_right_up;
			}

			if (angle >= 90.f && angle < 135.f)
			{
				current_animation = &walk_up;
			}

			if (angle >= 135.f && angle < 180.f)
			{
				current_animation = &walk_left_up;
			}

			// From 180 to 360 degrees
			if (angle >= 180.f && angle < 225.f)
			{
				current_animation = &walk_left;
			}

			if (angle >= 225.f && angle < 270.f)
			{
				current_animation = &walk_left_down;
			}

			if (angle >= 270.f && angle < 315.f)
			{
				current_animation = &walk_down;
			}

			if (angle >= 315.f && angle < 360.f)
			{
				current_animation = &walk_right_down;
			}
			break;
		case ATTACK:
			if (angle > 360)
			{
				angle -= 360.f;
			}
			// From 0 to 180 degrees
			if (angle >= 0.f && angle < 45.0f)
			{
				current_animation = &repair_right;
			}

			if (angle >= 45.f && angle < 90.0f)
			{
				current_animation = &repair_right_up;
			}

			if (angle >= 90.f && angle < 135.f)
			{
				current_animation = &repair_up;
			}

			if (angle >= 135.f && angle < 180.f)
			{
				current_animation = &repair_left_up;
			}

			// From 180 to 360 degrees
			if (angle >= 180.f && angle < 225.f)
			{
				current_animation = &repair_left;
			}

			if (angle >= 225.f && angle < 270.f)
			{
				current_animation = &repair_left_down;
			}

			if (angle >= 270.f && angle < 315.f)
			{
				current_animation = &repair_down;
			}

			if (angle >= 315.f && angle < 360.f)
			{
				current_animation = &repair_right_down;
			}
			break;
		}
	}

};

#endif //__SCV_H__