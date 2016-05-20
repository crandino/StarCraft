#include <math.h>
#include "App.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "ModuleFadeToBlack.h"
#include "Render.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

ModuleFadeToBlack::ModuleFadeToBlack()
{
	screen = {0, 0, 640, 480};
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{}

// Load assets
bool ModuleFadeToBlack::start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

// Update: draw background
bool ModuleFadeToBlack::update(float dt)
{
	if(current_step == fade_step::none)
		return true;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch(current_step)
	{
		case fade_step::fade_to_black:
		{
			if(now >= total_time)
			{
				to_disable->disable();
				to_enable->enable();
				total_time += total_time;
				start_time = SDL_GetTicks();
				current_step = fade_step::fade_from_black;
			}
		} break;

		case fade_step::fade_from_black:
		{
			normalized = 1.0f - normalized;

			if(now >= total_time)
				current_step = fade_step::none;
		} break;
	}

	// Finally render the black square with alpha on the screen
	SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(app->render->renderer, &screen);

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool ModuleFadeToBlack::fadeToBlack(Module* module_off, Module* module_on, float time)
{
	bool ret = false;

	if(current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		to_enable = module_on;
		to_disable = module_off;
		ret = true;
	}

	return ret;
}

bool ModuleFadeToBlack::IsFading() const
{
	return current_step != fade_step::none;
}