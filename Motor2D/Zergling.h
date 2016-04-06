#ifndef __ZERGLING_H__
#define __ZERGLING_H__

#include "Entity.h"

class Zergling : public Entity
{
public:

	Animation idle;
	FACTION faction;

	Zergling(iPoint &p)
	{
		// Positions and dimensions
		center = { (float)p.x, (float)p.y };

		tex_width = tex_height = 128;
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
		coll = app->collision->addCollider({ center.x, center.y, 24, 24 }, COLLIDER_BOMB);

		// Another stuff
		type = ZERGLING;
		faction = COMPUTER;
		hp = 10;
	}
};

#endif !__ZERGLING_H__