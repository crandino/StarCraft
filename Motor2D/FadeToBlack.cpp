#include "App.h"
#include "FadeToBlack.h"
#include "Window.h"
#include "Render.h"
#include "p2Log.h"

FadeToBlack::FadeToBlack(bool enabled) : Module(enabled)
{
	name.assign("fade_to_black");
}

FadeToBlack::~FadeToBlack()
{ }

// Load assets
bool FadeToBlack::start()
{
	LOG("Preparing Fade Screen");
	uint w, h;
	app->win->getWindowSize(w, h);
	screen = { 0, 0, w, h };
	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

// Update: draw background
bool FadeToBlack::update(float dt)
{
	if (current_step == FADE_STEP::none)
		return true;

	Uint32 now = SDL_GetTicks() - start_time;
	normalized = MIN(1.0f, (float)now / (float)total_time);

	switch(current_step)
	{
		case FADE_STEP::fade_to_black:
		{
			if(now >= total_time)
			{
				to_disable->disable();
				to_enable->enable();
				total_time += total_time;
				start_time = SDL_GetTicks();
				current_step = FADE_STEP::fade_from_black;
			}
		} break;

		case FADE_STEP::fade_from_black:
		{
			normalized = 1.0f - normalized;

			if(now >= total_time)
				current_step = FADE_STEP::none;
		} break;
	}

	return true;
}

bool FadeToBlack::postUpdate()
{
	if (current_step != FADE_STEP::none)
	{
		// Finally render the black square with alpha on the screen
		SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(app->render->renderer, &screen);
	}
	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool FadeToBlack::fadeToBlack(Module* module_off, Module* module_on, float time)
{
	bool ret = false;

	if (current_step == FADE_STEP::none)
	{
		current_step = FADE_STEP::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		to_enable = module_on;
		to_disable = module_off;
		ret = true;
	}

	return ret;
}

bool FadeToBlack::isFading() const
{
	return current_step != FADE_STEP::none;
}