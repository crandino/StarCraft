#ifndef __COMMANDCENTER_H__
#define __COMMANDCENTER_H__

#include "Entity.h"

class CommandCenter : public Entity
{
public:
	FACTION faction;
	Animation idle;

public:

	CommandCenter(iPoint &p)
	{
		// Positions and dimensions
		center = { (float)p.x, (float)p.y };

		tex_width = 128;
		tex_height = 100;
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.front(), center.x, center.y);

		// Animations
		tex = app->tex->loadTexture("temporaryTextures/commandCenter.png"); //Sprites/Animations etc..
		idle.frames.push_back({ 0, 27, 128, 100 });
		idle.speed = 1.0f;
		idle.loop = false;
		current_animation = &idle;

		// Colliders
		coll = app->collision->addCollider({ center.x, center.y, 128, 100 }, COLLIDER_BOMB);

		// Another stuff
		type = COMMANDCENTER;
		hp = 50;

		faction = PLAYER;
	}

};

#endif !__COMMANDCENTER_H__