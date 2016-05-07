#include "Bomb.h"


Bomb::Bomb(iPoint &p)
{
	tex_width = 30;
	tex_height = 30;
	collider_offset.set(15, 15);
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	tile_pos = app->map->worldToMap(app->map->data.front(), center.x, center.y);

	// Animations and FX
	tex = app->tex->loadTexture("Building/Bunker.png"); //Sprites/Animations etc..
	idle.frames.push_back({ 0, 0, 96, 128 });
	idle.speed = 1.0f;
	idle.loop = false;
	current_animation = &idle;
	// Colliders
	coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 30,30 }, COLLIDER_BOMB);

	// Another stuff
	specialization = BOMB;
	max_hp = 350;
	current_hp = 350.0f;
	max_hp_bars = 10;
	offset_life = { -23, 35 };


	range_of_vision = range_to_attack = 150;
	damage = 5.0f; //we change it according to the amount of marines inside;
	attack_frequency = 200.0f;


	state = IDLE;
	faction = PLAYER;
	selection_type = { 261, 1, 94, 56 };
	circle_selection_offset = { 0, 25 };
}



Bomb::~Bomb()
{

}