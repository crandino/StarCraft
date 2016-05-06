#ifndef __COMMANDCENTER_H__
#define __COMMANDCENTER_H__

#include "Building.h"

class CommandCenter : public Building
{
public:

	Animation idle;

public:

	CommandCenter() {}

	CommandCenter(iPoint &p)
	{
		// Graphics
		tex_width = 128;
		tex_height = 100;
		tex = app->tex->loadTexture("Building/CommandCenter.png"); //Sprites/Animations etc..
		idle.frames.push_back({ 0, 27, 128, 100 });
		idle.speed = 1.0f;
		idle.loop = false;
		current_animation = &idle;

		// Positions and dimensions
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		center = { (float)p.x, (float)p.y };		
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

		// Colliders
		coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 128, 100 }, COLLIDER_BUILDING);
		collider_offset.setZero();

		// Characterization and behaviour
		faction = PLAYER;
		specialization = COMMANDCENTER;

		// UI paramters
		selection_type = { 226, 66, 146, 88 };
		circle_selection_offset = { 0, 34 };
		offset_life = { -80, 57 };

		// Lifes attributes
		max_hp = 1500;
		current_hp = 1500;
		max_hp_bars = 36;		
	}

	~CommandCenter()
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

#endif !__COMMANDCENTER_H__