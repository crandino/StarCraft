#ifndef __ZERGLING_H__
#define __ZERGLING_H__

#include "Unit.h"

class Zergling : public Unit
{
public:

	Animation idle;

	Zergling(iPoint &p)
	{
		// Positions and dimensions
		center = { (float)p.x, (float)p.y };

		tex_width = tex_height = 128;
		collider_offset = { 12, 14 };
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

		// Animation
		tex = app->tex->loadTexture("Units/Zergling.png");
		idle.frames.push_back({ 0, 0, 128, 128 });
		/*idle.frames.push_back({ 128, 0, 128, 128 });
		idle.frames.push_back({ 256, 0, 128, 128 });
		idle.speed = 0.05f;*/
		idle.loop = false;
		current_animation = &idle;

		// Collider
		coll = app->collision->addCollider({ center.x - collider_offset.x, center.y - collider_offset.y, 24, 26 }, COLLIDER_BOMB);

		// Another stuff
		type = UNIT;
		specialization = ZERGLING;
		state = IDLE;
		faction = COMPUTER;
		max_hp = 40;
		current_hp = 40.0f;
		max_hp_bars = 6;
		selection_type = { 3, 4, 22, 13 };
		circle_selection_offset = -1;
		offset_life = { -19, 16 };
		flying = false;

		speed = 8.0f;
		range_to_view = 200;
		range_to_attack = 64;
		damage = 3.0f;
		attack_delay = 200.0f;
	}
};

#endif !__ZERGLING_H__