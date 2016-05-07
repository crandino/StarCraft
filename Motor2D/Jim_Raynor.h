#ifndef __JYM_RAYNOR_H__
#define __JYM_RAYNOR_H__

#include "Unit.h"

class Jym_Raynor : public Unit
{
public:

	// IDLE animations
	Animation	idle_up;
	Animation	idle_right_up;
	Animation   idle_right;
	Animation	idle_right_down;
	Animation	idle_down;
	Animation	idle_left_down;
	Animation	idle_left;
	Animation	idle_left_up;
	vector<Animation*>   idle_animation_pack;

	// MOVING animations
	Animation	walk_up;
	Animation   walk_right_up;
	Animation   walk_right;
	Animation   walk_right_down;
	Animation   walk_down;
	Animation   walk_left_down;
	Animation   walk_left;
	Animation   walk_left_up;
	vector<Animation*>   move_animation_pack;

	// ATTACK animations
	Animation	attack_up;
	Animation	attack_right_up;
	Animation	attack_right;
	Animation	attack_right_down;
	Animation	attack_down;
	Animation	attack_left_down;
	Animation	attack_left;
	Animation	attack_left_up;
	vector<Animation*>   attack_animation_pack;

	

	// Dead animation
	Animation	dead;

	Bunker*			     bunker_to_fill = NULL;		// Bunker that can be access by the Jym_Raynor
	bool			     inside_bunker = false;		// It's inside?

	bool				 taking_bomb = false;
	Entity*				 bomb;
	unsigned int		 fx_attack;

	Jym_Raynor() {};
	Jym_Raynor(iPoint &p);
	~Jym_Raynor();

	bool start();
	void move(float dt);
	void setAnimationFromDirection();
	void GetBomb();
};

#endif __JYM_RAYNOR_H__