#ifndef __MARINE_H__
#define __MARINE_H__

#include "Unit.h"

class Marine : public Unit
{
public:

	Animation	idle;

	Marine(iPoint &p)
	{
		// Positions and dimensions
		center = { (float)p.x, (float)p.y };

		tex_width = tex_height = 64;
		collider_offset = { 10, 14 };
		pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

		// Animations
		tex = app->tex->loadTexture("Units/Marine.png"); //Sprites/Animations etc..
		idle.frames.push_back({ 0, 0, 64, 64 });
		/*idle.frames.push_back({ 64, 0, 64, 64 });
		idle.frames.push_back({ 128, 0, 64, 64 });
		idle.frames.push_back({ 192, 0, 64, 64 });
		idle.frames.push_back({ 256, 0, 64, 64 });
		idle.frames.push_back({ 320, 0, 64, 64 });
		idle.frames.push_back({ 384, 0, 64, 64 });
		idle.frames.push_back({ 448, 0, 64, 64 });
		idle.frames.push_back({ 512, 0, 64, 64 });
		idle.frames.push_back({ 576, 0, 64, 64 });
		idle.frames.push_back({ 640, 0, 64, 64 });
		idle.frames.push_back({ 704, 0, 64, 64 });
		idle.frames.push_back({ 768, 0, 64, 64 });
		idle.frames.push_back({ 832, 0, 64, 64 });
		idle.frames.push_back({ 896, 0, 64, 64 });
		idle.frames.push_back({ 960, 0, 64, 64 });*/
		idle.speed = 0.0f;
		idle.loop = false;
		current_animation = &idle;

		// Colliders
		coll = app->collision->addCollider({ center.x - collider_offset.x, center.y - collider_offset.y, 22, 30 }, COLLIDER_BOMB);

		// Another stuff
		
		faction = PLAYER;
		flying = false;

		hp = 6;
		speed = 10;

		direction.create(1, 1, p.x, p.y);
		direction.setAngle(0.f);
	}

	void checkAngle()
	{
		float angle = direction.getAngle();

		if (angle >= 18)
		{
			idle.frames.push_back({ 64, 0, 64, 64 });
		}
	}

	void draw()
	{
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}

	bool update(float dt)
	{
		coll->setPos(center.x - 10, center.y - 14);
		if (has_target) move(dt);
		return true;
	}
};

#endif __MARINE_H__