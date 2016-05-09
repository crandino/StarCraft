#include "Unit.h"
#include "PathFinding.h"

Unit::Unit()
{
	type = UNIT;
	has_target = false;
};

Unit::~Unit()
{
	SDL_DestroyTexture(tex);
}

void Unit::calculePos()
{
	pos = { (float)center.x - (tex_width / 2), (float)center.y - (tex_height / 2) };
}

Entity* Unit::searchEnemy(bool can_attack_to_flying)
{
	if (has_focus && app->entity_manager->checkFocus(this))
		return target_to_attack;
	else
		return app->entity_manager->searchEnemyToAttack(this, can_attack_to_flying);
}

bool Unit::attack(Entity* target_to_attack)
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

				if (faction == PLAYER)
					app->game_manager->total_units_killed_currentFrame++;
			}
			if (target_to_attack->faction == PLAYER)
				app->gui->lasts_attack_position.push_back(target_to_attack->center);
		}
	}
	return ret;
}

void Unit::attackWithoutRange(Entity* target_to_attack)
{
	if (target_to_attack != NULL && target_to_attack->state != DYING)
	{
		if ((target_to_attack->current_hp -= (damage * damage_multiplier)) <= 0.0f)
		{
			target_to_attack->state = DYING;

			if (faction == PLAYER)
				app->game_manager->total_units_killed_currentFrame++;
		}
	}
}

void Unit::move(float dt)
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


bool Unit::update(float dt)
{
	checkUnitDirection();
	setAnimationFromDirection();   // This sets animation according to their angle direction
	coll->setPos(center.x + collider_offset.x, center.y + collider_offset.y);

	switch (state)
	{
	case IDLE:
		if (timer_to_check.read() >= TIME_TO_CHECK)
		{
			target_to_attack = searchEnemy();
			if (target_to_attack != NULL)
				newEntityFound();
			else if (faction == COMPUTER)
				app->entity_manager->SetEnemyToAttackCommandCenter(this);
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

void Unit::checkUnitDirection()
{
	if (state == ATTACK && target_to_attack != NULL)
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

void Unit::newEntityFound()
{
	has_target = false;
	float distance = abs(center.x - target_to_attack->center.x) + abs(center.y - target_to_attack->center.y);
	distance -= ((coll->rect.w / 2 + coll->rect.h / 2) / 2 + (target_to_attack->coll->rect.w / 2 + target_to_attack->coll->rect.h / 2) / 2);
	if (distance <= range_to_attack) //If the entity isn't in the range of attack it changes the direction and state
	{
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
	else if (path.size() > 0 && path.back() == app->path->findNearestWalkableTile(target_to_attack->tile_pos, tile_pos, 5))//if the tile destination is the same than current path
	{
		has_target = true;
	}
	else if (app->path->createPath(tile_pos, target_to_attack->tile_pos, id) != -1) //the path to the selected entity is constructed
		state = WAITING_PATH_MOVE_ALERT_TO_ATTACK;
}