#include "CommandCenter.h"

CommandCenter::CommandCenter(iPoint &p)
{
	// Graphics
	tex_width = 128;
	tex_height = 100;
	idle.frames.push_back({ 0, 27, 128, 100 });
	idle.speed = 1.0f;
	idle.loop = false;

	//Explosion

	explosion.anim.setAnimations(0, 0, 128, 128, 1, 9, 9);
	explosion.anim.speed = 0.009f;
	explosion.anim.loop = false;

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
	max_hp = current_hp = 1500;
	max_hp_bars = 36;

	range_of_vision = 300;
}

CommandCenter::~CommandCenter()
{ }

bool CommandCenter::update(float dt)
{
	sprintf_s(commandCenter_info, INFO_STRING_LENTGH, "%d / %d", current_hp, max_hp);
	app->gui->commandCenterInfo->setText(commandCenter_info, 1);
	setParticleBehaviour();

	switch (state)
	{
	case IDLE:
		break;
	case DYING:
		if (timer_to_check.read() >= time_to_die)
		{
			current_hp = 0;
			to_delete = true;
			coll->to_delete = true;
		}
		break;
	}
	return true;
}

void CommandCenter::draw()
{
	app->render->blit(app->entity_manager->command_center_tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
}

void CommandCenter::setParticleBehaviour()
{
	switch (state)
	{
	case DYING:
		particle = app->particle->addParticle(explosion, center.x, center.y, 0, 0, 1, app->particle->explosion_small);
		break;
	}
}