#ifndef __BUNKER_H__
#define __BUNKER_H__

#include "Building.h"

class Bunker : public Building
{
public:

	Animation idle;

public:

	Bunker(iPoint &p)
	{
		// Positions and dimensions
		center = { (float)p.x, (float)p.y };

		tex_width = 126;
		tex_height = 59;
		collider_offset.setZero();
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.front(), center.x, center.y);

		// Animations
		tex = app->tex->loadTexture("Building/Bunker.png"); //Sprites/Animations etc..
		idle.frames.push_back({ 0, 27, 126, 59 });
		idle.speed = 1.0f;
		idle.loop = false;
		current_animation = &idle;

		// Colliders
		coll = app->collision->addCollider({ pos.x - collider_offset.x, pos.y - collider_offset.y, 126, 69 }, COLLIDER_BOMB);

		// Another stuff
		specialization = BUNKER;
		max_hp = 350;
		current_hp = 350.0f;
		capacity = 4;

		faction = PLAYER;
		selection_type = { 226, 66, 146, 88 };
		circle_selection_offset = 34;
	}
};

#endif !__COMMANDCENTER_H__