#include "GuiMinimap.h"
#include "Entity.h"
#include "Input.h"
#include "p2Log.h"

GuiMinimap::GuiMinimap(SDL_Rect map_rect) : rect(map_rect), GuiElements()
{
	type = MINIMAP;
	interactive = true;
	draw_element = true;
}

bool GuiMinimap::SetAttributes(map<uint, Entity*>* entities, SDL_Texture* texture)
{
	bool ret = true;

	if (ret = (entities != NULL))
		active_entities = entities;

	if (ret && (ret = (texture != NULL)))
		tex = texture;

	//set scale
	calculateScale();

	// set pings
	ping_set.fill(PingInfo(area.w * 2, area.w * 2, area.w, area.h));

	return ret;
}

//Called every frame
void GuiMinimap::update()
{
	// check if using GuiMinimap
	if (app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN || app->input->getMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		iPoint mouse_pos;
		app->input->getMousePosition(mouse_pos);

		if (mouse_pos.x < rect.x + rect.w && mouse_pos.x > rect.x && mouse_pos.y < rect.y + rect.h && mouse_pos.y > rect.y)
			app->render->setCameraOnPosition(minimapToWorld({ mouse_pos.x - rect.x, mouse_pos.y - rect.y }));
	}

	// Ping update
	for (array<PingInfo, 4>::iterator it = ping_set.begin(); it != ping_set.end(); ++it)
	{
		if (!it->ping_active)
			continue;
		it->updatePing();
	}
}

bool GuiMinimap::cleanUp()
{
	bool ret = true;
	// release texture and entities pointer
	return ret;
}

iPoint GuiMinimap::minimapToWorld(const iPoint &mini_map_pos) const
{
	iPoint world_pos;
	world_pos.x = mini_map_pos.x / scale.x;
	world_pos.y = mini_map_pos.y / scale.y;

	// The method will never return the exact corners as world positions.
	if (world_pos.x <= (app->render->camera.w / 2))
		world_pos.x = app->render->camera.w / 2;
	else if (world_pos.x >= (app->map->data.front().tile_width * app->map->data.front().width) - (app->render->camera.w / 2))
		world_pos.x = (app->map->data.front().tile_width * app->map->data.front().width) - (app->render->camera.w / 2);

	if (world_pos.y <= (app->render->camera.h / 2)) 
		world_pos.y = app->render->camera.h / 2;
	else if (world_pos.y >= (app->map->data.front().tile_height * app->map->data.front().height) - (app->render->camera.h / 2))
		world_pos.y = (app->map->data.front().tile_height * app->map->data.front().height) - (app->render->camera.h / 2);

	return world_pos;
}

iPoint GuiMinimap::worldToMinimap(const iPoint &world_pos) const
{
	iPoint mini_map_pos;

	mini_map_pos.x = rect.x + (world_pos.x * scale.x) - app->render->camera.x;
	mini_map_pos.y = rect.y + (world_pos.y * scale.y) - app->render->camera.y;

	return mini_map_pos;
}

//Blitz GuiMinimap
void GuiMinimap::draw() const
{
	//print map
	if (tex != NULL)
		app->render->blit(tex, rect.x - app->render->camera.x, rect.y - app->render->camera.y);

	//print units
	if (active_entities != NULL)
	{
		for (std::map<uint, Entity*>::iterator it = active_entities->begin(); it != active_entities->end(); ++it)
		{
			Entity* entity = it->second;

			// Set drawing quad for each unit
			// Choose quad color
			Uint8 r, g, b;
			switch (entity->faction)
			{
			case FACTION::PLAYER:
				r = 0;
				g = 0;
				b = 255;
				break;

			case FACTION::COMPUTER:
				r = 255;
				g = 0;
				b = 0;
				break;
			}

			// send to render
			iPoint quad_pos = worldToMinimap({ (int)entity->center.x, (int)entity->center.y });
			app->render->DrawQuad({ quad_pos.x, quad_pos.y, 1, 1 }, r, g, b);
		}
	}

	// print area
	iPoint pos = worldToMinimap({ -app->render->camera.x, -app->render->camera.y });
	app->render->DrawQuad({ pos.x, pos.y, area.w, area.h }, 255, 255, 255, 255, false);

	for (array<PingInfo, 4>::const_iterator it = ping_set.begin(); it != ping_set.end(); ++it)
	{
		if (it->ping_active)
			app->render->DrawQuad({ (int)it->ping_position.x - it->current_ping_width / 2,
									(int)it->ping_position.y - it->current_ping_height / 2,
									 it->current_ping_width, it->current_ping_height }, 255, 0, 0, 255, false);
	}
		
}

void GuiMinimap::calculateScale()
{
	scale.x = rect.w / (float)(app->map->data.front().width * app->map->data.front().tile_width);    //map width
	scale.y = rect.h / (float)(app->map->data.front().height * app->map->data.front().tile_height);  //map height;

	area.w = app->render->camera.w * scale.x;
	area.h = app->render->camera.h * scale.y;
}

void GuiMinimap::activePing(iPoint attack_position)
{
	for (array<PingInfo, 4>::iterator it = ping_set.begin(); it != ping_set.end(); ++it)
	{
		if (it->ping_active)
			continue;

		it->ping_position = worldToMinimap(attack_position);
		it->initiate();
		break;
	}
}
