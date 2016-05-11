#ifndef __ULTRALISK_H__
#define __ULTRALISK_H__

#include "Unit.h"

class Ultralisk : public Unit
{
public:
	//IDLE animation
	Animation idle_up;
	Animation idle_right_up;
	Animation idle_right;
	Animation idle_right_down;
	Animation idle_down;
	Animation idle_left_down;
	Animation idle_left;
	Animation idle_left_up;

	vector<Animation*> idle_animation_pack;

	// MOVING animations
	Animation	walk_up;
	Animation   walk_right_up1;
	Animation   walk_right_up2;
	Animation   walk_right_up3;
	Animation   walk_right;
	Animation   walk_right_down1;
	Animation   walk_right_down2;
	Animation   walk_right_down3;
	Animation   walk_down;
	Animation   walk_left_down1;
	Animation   walk_left_down2;
	Animation   walk_left_down3;
	Animation   walk_left;
	Animation   walk_left_up1;
	Animation   walk_left_up2;
	Animation   walk_left_up3;

	vector<Animation*>   move_animation_pack;

	// Dead animation
	Animation	dead;

	// ATTACK animations
	Animation attack_up;
	Animation attack_right_up;
	Animation attack_right;
	Animation attack_right_down;
	Animation attack_down;
	Animation attack_left_down;
	Animation attack_left;
	Animation attack_left_up;
	vector<Animation*> attack_animation_pack;

	bool sound_active = true;

	Ultralisk(iPoint &p);
	~Ultralisk();

	bool update(float dt);
	void setAnimationFromDirection();
	void draw();

};

#endif __ULTRALISK_H__