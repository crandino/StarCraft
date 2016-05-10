#include "Bomb.h"

Bomb::Bomb(iPoint &p)
{
	tex_width = 43;
	tex_height = 42;
	collider_offset.set(15, 15);
	// Positions and information
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	center = { (float)p.x, (float)p.y };
	tile_pos = app->map->worldToMap(app->map->data.front(), center.x, center.y);

	// Animations and FX
	tex = app->tex->loadTexture("pikachu_aka_bomb.png"); //Sprites/Animations etc..
	idle.frames.push_back({ 0, 0, 43, 42 });
	idle.speed = 1.0f;
	idle.loop = false;
	current_animation = &idle;
	// Colliders
	coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 43, 42 }, COLLIDER_BOMB);

	// Another stuff
	specialization = BOMB;
	max_hp = 350;
	current_hp = 350.0f;
	max_hp_bars = 10;
	offset_life = { -23, 35 };

	range_of_vision = range_to_attack = 300;
	damage = 5.0f; //we change it according to the amount of marines inside;
	attack_frequency = 200.0f;

	state = IDLE;
	faction = COMPUTER;
	selection_type = { 261, 1, 94, 56 };
	circle_selection_offset = { 0, 25 };
}

Bomb::~Bomb()
{ }

void Bomb::draw()
{
	if (app->fog_of_war->isVisible(pos.x, pos.y))
		app->render->blit(app->entity_manager->bomb_tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
}