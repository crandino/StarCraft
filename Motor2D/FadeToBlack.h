#ifndef __FADETOBLACK_H__
#define __FADETOBLACK_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class FadeToBlack : public Module
{
public:

	FadeToBlack(bool enabled);
	~FadeToBlack();

	bool start();
	bool update(float dt);
	bool postUpdate();
	bool fadeToBlack(Module* module_off, Module* module_on, float time = 1.0f);
	bool isFading() const;

private:

	enum FADE_STEP
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = FADE_STEP::none;

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
	float normalized;
	Module* to_enable = nullptr;
	Module* to_disable = nullptr;
};

#endif //__FADETOBLACK_H__