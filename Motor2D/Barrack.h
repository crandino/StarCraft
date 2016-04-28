#ifndef __BARRACK_H__
#define __BARRACK_H__

#include "Building.h"

class Barrack : public Building
{
public:

	Animation idle;

public:

	Barrack(iPoint &p)
	{
		// Graphics
		tex_width = 125;
		tex_height = 110;
		tex = app->tex->loadTexture("Building/barracks.png"); //Sprites/Animations etc..
		idle.frames.push_back({ 34, 20, 125, 110 });
		idle.speed = 1.0f;
		idle.loop = false;
		current_animation = &idle;

		// Positions and dimensions
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		center = { (float)p.x, (float)p.y };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

		// Colliders
		coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 125, 110 }, COLLIDER_BUILDING);
		collider_offset.setZero();

		// Characterization and behaviour
		faction = PLAYER;
		specialization = BARRACK;

		// UI paramters
		selection_type = { 226, 66, 146, 88 };
		circle_selection_offset = { 0, 34 };
		offset_life = { -80, 57 };

		// Lifes attributes
		max_hp = 1000;
		current_hp = 1000;
		max_hp_bars = 30;
	}

	bool update(float dt)
	{
		switch (state)
		{
		case IDLE:
			break;
		case DYING:
			if (timer_to_check.read() >= time_to_die)
			{
				to_delete = true;
				coll->to_delete = true;
			}
			break;
		}
		return true;
	}
};

#endif !__BARRACK_H__