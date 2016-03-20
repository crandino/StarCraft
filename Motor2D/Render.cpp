#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "Window.h"
#include "Render.h"
#include "Map.h"
#include "Input.h"

Render::Render() : Module()
{
	name.insert(0,"renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

// Destructor
Render::~Render()
{}

// Called before render is available
bool Render::awake(pugi::xml_node &node)
{
	LOG("Create SDL rendering context");
	bool ret = true;
	// load flags
	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if (node.attribute("vsync").as_bool())
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(app->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		camera.w = app->win->screen_surface->w;
		camera.h = app->win->screen_surface->h;
		camera.x = 0;
		camera.y = 0;
	}

	return ret;
}

// Called before the first frame
bool Render::start()
{
	LOG("render start");
	// back background
	SDL_RenderGetViewport(renderer, &viewport);

	// Camera offset movement activation
	uint w, h; app->win->getWindowSize(w, h);
	cursor_offset.x = (w * 0.1f); // 10% of map width
	cursor_offset.y = (h * 0.1f); // 10% of map height
	scroll_speed = 1.0f;

	map_limits = { app->map->data.width * app->map->data.tile_width,
				   app->map->data.height * app->map->data.tile_height};

	return true;
}

// Called each loop iteration
bool Render::preUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool Render::update(float dt)
{
	if (transition_active == true)
		transition_active = transitioning();
	
	moveCamera(dt);

	return true;
}

bool Render::postUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

// MoveCamera check where the mouse is and acts accordingly, moving the map on that direction.
void Render::moveCamera(float dt)
{
	iPoint mouse_position;
	app->input->getMousePosition(mouse_position);

	// Two zones are implemented. The inner one, near the center, has a specific velocity.
	// The outer one, near the window frame, has double velocity than the previous one.
	int map_displacement = scroll_speed * dt;

	// Checking displacement for X axis.
	if (mouse_position.x < cursor_offset.x) // Left
	{
		camera.x += (camera.x + map_displacement <= 0 ? map_displacement : 0);
		if (mouse_position.x < cursor_offset.x / 2)
			camera.x += (camera.x + map_displacement <= 0 ? map_displacement : 0);
	}
	else if (mouse_position.x > (camera.w - cursor_offset.x)) // Right
	{
		camera.x -= (camera.x - map_displacement >= camera.w - map_limits.x ? map_displacement : 0);
		if (mouse_position.x > (camera.w - cursor_offset.x / 2))
			camera.x -= (camera.x - map_displacement >= camera.w - map_limits.x ? map_displacement : 0);
	}

	// Checking displacement for Y axis.
	if (mouse_position.y < cursor_offset.y) // Up
	{
		camera.y += (camera.y + map_displacement <= 0 ? map_displacement : 0);
		if (mouse_position.y < cursor_offset.y / 2)
			camera.y += (camera.y + map_displacement <= 0 ? map_displacement : 0);
	}
	else if (mouse_position.y > (camera.h - cursor_offset.y)) // Down
	{
		camera.y -= (camera.y - map_displacement >= camera.h - map_limits.y ? map_displacement : 0);
		if (mouse_position.y > (camera.h - cursor_offset.y / 2))
			camera.y -= (camera.y - map_displacement >= camera.h - map_limits.y ? map_displacement : 0);
	}
}

// Called before quitting
bool Render::cleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

iPoint Render::screenToWorld(int x, int y) const
{
	iPoint ret;
	int scale = app->win->getScale();

	ret.x = (x - camera.x / scale);
	ret.y = (y - camera.y / scale);

	return ret;
}

void Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

// Load / Save
bool Render::load(pugi::xml_node &node)
{
	camera.x = node.child("camera").attribute("x").as_int();
	camera.y = node.child("camera").attribute("y").as_int();

	return true;
}

bool Render::save(pugi::xml_node &node) const
{
	pugi::xml_node cam = node.append_child("camera");

	cam.append_attribute("x") = camera.x;
	cam.append_attribute("y") = camera.y;

	return true;
}

// Blit to screen
bool Render::blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, double angle, int pivot_x, int pivot_y) const
{
	bool ret = true;
	uint scale = app->win->getScale();

	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * scale;
	rect.y = (int)(camera.y * speed) + y * scale;

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= scale;
	rect.h *= scale;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if(pivot_x != INT_MAX && pivot_y != INT_MAX)
	{
		pivot.x = pivot_x;
		pivot.y = pivot_y;
		p = &pivot;
	}

	if(SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera) const
{
	bool ret = true;
	uint scale = app->win->getScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if(use_camera)
	{
		rec.x = (int)(camera.x + rect.x * scale);
		rec.y = (int)(camera.y + rect.y * scale);
		rec.w *= scale;
		rec.h *= scale;
	}

	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = app->win->getScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;

	if(use_camera)
		result = SDL_RenderDrawLine(renderer, camera.x + x1 * scale, camera.y + y1 * scale, camera.x + x2 * scale, camera.y + y2 * scale);
	else
		result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = app->win->getScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for(uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor));
		points[i].y = (int)(y + radius * sin(i * factor));
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void Render::start_transition(iPoint dest_pos)
{
	transition_active = true;
	this->dest_pos.set(-(dest_pos.x + camera.w / 2), -(dest_pos.y + camera.y / 2)); // Origin on upper_left corner
	middle_pos.set((dest_pos.x + camera.x) / 2, (dest_pos.y + camera.y) / 2);
	lerp_value = 0.0f;
}

bool Render::transitioning()
{
	bool ret = true;
	iPoint curr_pos = { camera.x, camera.y };
	float incr = 0.00001;	
	
	/*if (lerp_value < 1.0f) lerp_value += 0.00001;
	LOG("%f", lerp_value);*/

	if (curr_pos == dest_pos)
		ret = false;
	else
	{
		if (curr_pos == middle_pos)
			incr = -incr;

		lerp_value += incr;
		
		camera.x = (dest_pos.x * lerp_value) + ((1 - lerp_value) * curr_pos.x);
		camera.y = (dest_pos.y * lerp_value) + ((1 - lerp_value) * curr_pos.y);
	}

	return ret;

}