#ifndef __MARINE_H__
#define __MARINE_H__

#include "Unit.h"

class Marine : public Unit
{
public:

	//ROF
	// It must have a review to do spritesheets with render flip into Animation module https://wiki.libsdl.org/SDL_RendererFlip
	Animation	idle_up;
	Animation	idle_right_up;
	Animation   idle_right;
	Animation	idle_right_down;
	Animation	idle_down;
	Animation	idle_left_down;
	Animation	idle_left;
	Animation	idle_left_up;
	
	Animation	walk_up;
	Animation   walk_right_up;
	Animation   walk_right;
	Animation   walk_right_down;
	Animation   walk_down;
	Animation   walk_left_down;
	Animation   walk_left;
	Animation   walk_left_up;

	Animation	attack_up;
	Animation	attack_right_up;
	Animation	attack_right;
	Animation	attack_right_down;
	Animation	attack_down;
	Animation	attack_left_down;
	Animation	attack_left;
	Animation	attack_left_up;

	Animation	dead;

	vector<Animation*>   idle_animation_pack;
	vector<Animation*>   move_animation_pack;
	vector<Animation*>   attack_animation_pack;

	Bunker*			     bunker_to_fill = NULL;
	bool			     inside_bunker = false;

	// SFX
	unsigned int marine_attack_fx;

	Marine(iPoint &p);

	void move(float dt);
	void setAnimationFromDirection();
	
};

#endif __MARINE_H__