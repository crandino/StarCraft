#ifndef __BUNKER_H__
#define __BUNKER_H__

#include "Building.h"

class Bunker : public Building
{
public:

	Animation idle;
	map<uint, Entity*>					units_inside;

public:

	Bunker(iPoint &p)
	{
		// Positions and dimensions
		center = { (float)p.x, (float)p.y };

		tex_width = 96;
		tex_height = 128;
		collider_offset.set(0, 36);
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.front(), center.x, center.y);

		// Animations
		tex = app->tex->loadTexture("Building/Bunker.png"); //Sprites/Animations etc..
		idle.frames.push_back({ 0, 0, 96, 128 });
		idle.speed = 1.0f;
		idle.loop = false;
		current_animation = &idle;

		// Colliders
		coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 96, 59 }, COLLIDER_BOMB);

		// Another stuff
		specialization = BUNKER;
		max_hp = 350;
		current_hp = 350.0f;
		max_hp_bars = 10;
		offset_life = { -23, 35 };
		capacity = 4;

		state = IDLE;
		faction = PLAYER;
		selection_type = { 261, 1, 94, 56 };
		circle_selection_offset = { 0, 25 };
	}

	void leave_bunker() {
		if (!units_inside.empty())
		{
			map<uint, Entity*>::iterator it = units_inside.begin();
			for (; it != units_inside.end(); ++it)
			{
				app->entity_manager->active_entities.insert(pair<uint, Entity*>(it->first, it->second));
				it->second->to_delete = true;
				++capacity;
			}
		}

	}
};

#endif !__BUNKER_H__