#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "Building.h"

class Factory : public Building
{
public:

	Animation idle;

public:

	Factory() {}

	Factory(iPoint &p)
	{
		// Graphics
		tex_width = 128;
		tex_height = 108;
		tex = app->tex->loadTexture("Building/factory.png"); //Sprites/Animations etc..
		idle.frames.push_back({ 0, 18, 128, 108 });
		idle.speed = 1.0f;
		idle.loop = false;
		current_animation = &idle;

		// Positions and dimensions
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		center = { (float)p.x, (float)p.y };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

		// Colliders
		coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 128, 108 }, COLLIDER_BUILDING);
		collider_offset.setZero();

		// Characterization and behaviour
		faction = PLAYER;
		specialization = FACTORY;

		// UI paramters
		selection_type = { 226, 66, 146, 88 };
		circle_selection_offset = { 6, 30 };
		offset_life = { -60, 57 };

		// Lifes attributes
		max_hp = 1000;
		current_hp = 1000;
		max_hp_bars = 30;
		range_of_vision = 300;
		app->gui->factoryAlive = true;
	}

	~Factory()
	{
		SDL_DestroyTexture(tex);
	}

	bool update(float dt)
	{
		switch (state)
		{
		case IDLE:
			break;
		case DYING:
			app->gui->factoryAlive = false;
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

#endif !__FACTORY_H__