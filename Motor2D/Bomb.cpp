#include "Bomb.h"

Bomb::Bomb(iPoint &p)
{
	tex_width = 47;
	tex_height = 90;
	collider_offset.set(0, 0);
	// Positions and information
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	center = { (float)p.x, (float)p.y };
	tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

	// Animations and FX
	idle.frames.push_back({ 8, 10, 47, 90 });
	idle.frames.push_back({ 68, 10, 47, 90 });
	idle.frames.push_back({ 128, 10, 47, 90 });
	idle.frames.push_back({ 188, 10, 47, 90 });
	idle.frames.push_back({ 248, 10, 47, 90 });
	idle.frames.push_back({ 308, 10, 47, 90 });
	idle.frames.push_back({ 368, 10, 47, 90 });
	idle.frames.push_back({ 428, 10, 47, 90 });
	idle.speed = 0.007f;
	idle.loop = true;
	current_animation = &idle;
	// Colliders
	coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 47, 90 }, COLLIDER_BOMB);

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