#include "Medic.h"
#include "PathFinding.h"

Medic::Medic(iPoint &p)
{
	// Graphics
	// IDLE
	tex_width = tex_height = 64;

	idle_right.frames.push_back({ 256, 0, 64, 64 });
	idle_right.speed = 0.01f;
	idle_animation_pack.push_back(&idle_right);

	idle_right_up.frames.push_back({ 128, 0, 64, 64 });
	idle_right_up.speed = 0.01f;
	idle_animation_pack.push_back(&idle_right_up);

	idle_up.frames.push_back({ 0, 0, 64, 64 });
	idle_up.speed = 0.01f;
	idle_animation_pack.push_back(&idle_up);

	idle_left_up.frames.push_back({ 896, 0, 64, 64 });
	idle_left_up.speed = 0.01f;
	idle_animation_pack.push_back(&idle_left_up);

	idle_left.frames.push_back({ 768, 0, 64, 64 });
	idle_left.speed = 0.01f;
	idle_animation_pack.push_back(&idle_left);

	idle_left_down.frames.push_back({ 640, 0, 64, 64 });
	idle_left_down.speed = 0.01f;
	idle_animation_pack.push_back(&idle_left_down);

	idle_down.frames.push_back({ 512, 0, 64, 64 });
	idle_down.speed = 0.01f;
	idle_animation_pack.push_back(&idle_down);

	idle_right_down.frames.push_back({ 384, 0, 64, 64 });
	idle_right_down.speed = 0.01f;
	idle_animation_pack.push_back(&idle_right_down);

	// WALKING ANIMATIONS-----------------------------

	walk_right.setAnimations(256, 384, 64, 64, 1, 7, 7);
	walk_right.speed = 0.02f;
	move_animation_pack.push_back(&walk_right);

	//walk_right_up3.setAnimations(192, 384, 64, 64, 1, 7, 7);
	//walk_right_up3.speed = 0.02f;
	//move_animation_pack.push_back(&walk_right_up3);

	walk_right_up2.setAnimations(128, 384, 64, 64, 1, 7, 7);
	walk_right_up2.speed = 0.02f;
	move_animation_pack.push_back(&walk_right_up2);

	//walk_right_up1.setAnimations(64, 384, 64, 64, 1, 7, 7);
	//walk_right_up1.speed = 0.02f;
	//move_animation_pack.push_back(&walk_right_up1);

	walk_up.setAnimations(0, 384, 64, 64, 1, 7, 7);
	walk_up.speed = 0.02f;
	move_animation_pack.push_back(&walk_up);

	//walk_left_up3.setAnimations(960, 384, 64, 64, 1, 7, 7);
	//walk_left_up3.speed = 0.02f;
	//move_animation_pack.push_back(&walk_left_up3);

	walk_left_up2.setAnimations(896, 384, 64, 64, 1, 7, 7);
	walk_left_up2.speed = 0.02f;
	move_animation_pack.push_back(&walk_left_up2);

	//walk_left_up1.setAnimations(832, 384, 64, 64, 1, 7, 7);
	//walk_left.speed = 0.02f;
	//move_animation_pack.push_back(&walk_left_up1);

	walk_left.setAnimations(768, 384, 64, 64, 1, 7, 7);
	walk_left.speed = 0.02f;
	move_animation_pack.push_back(&walk_left);

	//walk_left_down3.setAnimations(704, 384, 64, 64, 1, 7, 7);
	//walk_left_down3.speed = 0.02f;
	//move_animation_pack.push_back(&walk_left_down3);

	walk_left_down2.setAnimations(640, 384, 64, 64, 1, 7, 7);
	walk_left_down2.speed = 0.02f;
	move_animation_pack.push_back(&walk_left_down2);

	//walk_left_down1.setAnimations(576, 384, 64, 64, 1, 7, 7);
	//walk_left_down1.speed = 0.02f;
	//move_animation_pack.push_back(&walk_left_down1);

	walk_down.setAnimations(512, 384, 64, 64, 1, 7, 7);
	walk_down.speed = 0.02f;
	move_animation_pack.push_back(&walk_down);

	//walk_right_down3.setAnimations(448, 384, 64, 64, 1, 7, 7);
	//walk_right_down3.speed = 0.02f;
	//move_animation_pack.push_back(&walk_right_down3);

	walk_right_down2.setAnimations(384, 384, 64, 64, 1, 7, 7);
	walk_right_down2.speed = 0.02f;
	move_animation_pack.push_back(&walk_right_down2);

	//walk_right_down1.setAnimations(320, 384, 64, 64, 1, 7, 7);
	//walk_right_down1.speed = 0.02f;
	//move_animation_pack.push_back(&walk_right_down1);

	//------------------------------------------------

	//-- HEAL ANIMATIONS------------------------------
	heal_right.setAnimations(256, 256, 64, 64, 1, 2, 2);
	heal_right.speed = 0.01f;
	heal_animation_pack.push_back(&heal_right);

	//heal_right_up3.setAnimations(192, 256, 64, 64, 1, 2, 2);
	//heal_right_up3.speed = 0.01f;
	//heal_animation_pack.push_back(&heal_right_up3);

	heal_right_up2.setAnimations(128, 256, 64, 64, 1, 2, 2);
	heal_right_up2.speed = 0.01f;
	heal_animation_pack.push_back(&heal_right_up2);

	//heal_right_up1.setAnimations(64, 256, 64, 64, 1, 2, 2);
	//heal_right_up1.speed = 0.01f;
	//heal_animation_pack.push_back(&heal_right_up1);

	heal_up.setAnimations(0, 256, 64, 64, 1, 2, 2);
	heal_up.speed = 0.01f;
	heal_animation_pack.push_back(&heal_up);

	//heal_left_up3.setAnimations(960, 256, 64, 64, 1, 2, 2);
	//heal_left_up3.speed = 0.01f;
	//heal_animation_pack.push_back(&heal_left_up3);

	heal_left_up2.setAnimations(896, 256, 64, 64, 1, 2, 2);
	heal_left_up2.speed = 0.01f;
	heal_animation_pack.push_back(&heal_left_up2);

	//heal_left_up1.setAnimations(832, 256, 64, 64, 1, 2, 2);
	//heal_left.speed = 0.01f;
	//heal_animation_pack.push_back(&heal_left_up1);

	heal_left.setAnimations(768, 256, 64, 64, 1, 2, 2);
	heal_left.speed = 0.01f;
	heal_animation_pack.push_back(&heal_left);

	//heal_left_down3.setAnimations(704, 256, 64, 64, 1, 2, 2);
	//heal_left_down3.speed = 0.01f;
	//heal_animation_pack.push_back(&heal_left_down3);

	heal_left_down2.setAnimations(640, 256, 64, 64, 1, 2, 2);
	heal_left_down2.speed = 0.01f;
	heal_animation_pack.push_back(&heal_left_down2);

	//heal_left_down1.setAnimations(576, 256, 64, 64, 1, 2, 2);
	//heal_left_down1.speed = 0.01f;
	//heal_animation_pack.push_back(&heal_left_down1);

	heal_down.setAnimations(512, 256, 64, 64, 1, 2, 2);
	heal_down.speed = 0.01f;
	heal_animation_pack.push_back(&heal_down);

	//heal_right_down3.setAnimations(448, 256, 64, 64, 1, 2, 2);
	//heal_right_down3.speed = 0.01f;
	//heal_animation_pack.push_back(&heal_right_down3);

	heal_right_down2.setAnimations(384, 256, 64, 64, 1, 2, 2);
	heal_right_down2.speed = 0.01f;
	heal_animation_pack.push_back(&heal_right_down2);

	//heal_right_down1.setAnimations(320, 256, 64, 64, 1, 2, 2);
	//heal_right_down1.speed = 0.01f;
	//heal_animation_pack.push_back(&heal_right_down1);

	// DEAD ANIMATION---------------------------------
	dead.frames.push_back({ 0, 832, 64, 64 });
	dead.frames.push_back({ 64, 832, 64, 64 });
	dead.frames.push_back({ 128, 832, 64, 64 });
	dead.frames.push_back({ 192, 832, 64, 64 });
	dead.frames.push_back({ 256, 832, 64, 64 });
	dead.frames.push_back({ 320, 832, 64, 64 });
	dead.frames.push_back({ 384, 832, 64, 64 });
	dead.frames.push_back({ 448, 832, 64, 64 });
	dead.loop = false;
	dead.speed = 0.01f;
	//------------------------------------------------

	// Positions and information
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	center = { (float)p.x, (float)p.y };
	tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);
	current_animation = &idle_down;

	// Colliders
	coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 30, 30 }, COLLIDER_UNIT, app->entity_manager);
	collider_offset = { -14, -16 };

	// Characterization and behaviour
	faction = PLAYER;
	specialization = MEDIC;
	flying = false;

	// UI paramters
	selection_type = { 28, 9, 32, 19 };
	circle_selection_offset = { -2, 0 };
	offset_life = { -14, 22 };

	// Lifes attributes
	max_hp = 60;
	current_hp = 60.0f;
	max_hp_bars = 6;

	// Attack values and properties
	range_of_vision = 300;
	range_to_attack = 50;
	damage = 5.0f;
	attack_frequency = 100.0f;
	healing_power = 2;

	// PathFinding and movement variables
	speed = 8.0f;
	angle = 180.0f;
}

Medic::~Medic()
{ }

void Medic::setAnimationFromDirection()
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
		case(ATTACK) ://ATTACK == REPAIR for SCV
		{
			int num_animation = angle / (360 / heal_animation_pack.size());
			if (num_animation == heal_animation_pack.size())
				num_animation = 0;
			current_animation = &(*heal_animation_pack.at(num_animation));
			break;
		}
		case(DYING) :
		{
			current_animation = &dead;
			break;
		}
	}
}

bool Medic::update(float dt)
{
	checkUnitDirection();
	setAnimationFromDirection();   // This sets animation according to their angle direction
	coll->setPos(center.x + collider_offset.x, center.y + collider_offset.y);

	switch (state)
	{
	case IDLE:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchAllyToHeal();
			if (target_to_attack != NULL)
				newEntityFound();
			timer_to_check.start();
		}
		break;
	case MOVE:
		if (has_target) move(dt);
		break;
	case MOVE_ALERT:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchAllyToHeal();
			if (target_to_attack != NULL)
				newEntityFound();
			timer_to_check.start();
		}
		if (has_target) move(dt);
		break;
	case MOVE_ALERT_TO_ATTACK:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchAllyToHeal();
			if (target_to_attack != NULL)
				newEntityFound();
			else
			{
				has_target = false;
				state = IDLE;
			}
			timer_to_check.start();
		}
		if (has_target) move(dt);
		break;
	case ATTACK:
		if (timer_attack.read() >= (attack_frequency * attack_frequency_multiplier))
		{
			app->audio->playFx(app->entity_manager->fx_medic_heal, 0);
			if (!heal())
			{
				state = IDLE;
				target_to_attack = NULL;
			}
			
			timer_attack.start();
		}
		break;
	case DYING:
		if (sound_active == true)
		{
			app->audio->playFx(app->entity_manager->fx_medic_death, 0);
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

	if (grouped && (state != MOVE && state != MOVE_ALERT && state != IDLE))
		grouped = false;

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

void Medic::move(float dt)
{
	if (path.size() > 0)
	{
		float pixels_to_move = 0;
		float total_pixels_moved = 0;
		float total_pixels_to_move;
		if (grouped)
			total_pixels_to_move = (group_speed * speed_multiplier) / 100 * dt;
		else
			total_pixels_to_move = (speed * speed_multiplier) / 100 * dt;

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
						state = ATTACK;
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

void Medic::draw()
{
	app->render->blit(app->entity_manager->medic_tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
}
