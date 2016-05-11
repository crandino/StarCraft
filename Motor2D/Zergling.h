#ifndef __ZERGLING_H__
#define __ZERGLING_H__

#include "Unit.h"

class Zergling : public Unit
{
public:

	// IDLE animations
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
	Animation walk_up;
	Animation walk_right_up;
	Animation walk_right;
	Animation walk_right_down;
	Animation walk_down;
	Animation walk_left_down;
	Animation walk_left;
	Animation walk_left_up;
	vector<Animation*> move_animation_pack;

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

	// Dead animation
	Animation dead;

	bool sound_active = true;

	Zergling(iPoint &p);
	~Zergling();

	bool update(float dt);

	// Method that assign an animation according to its orientation
	void setAnimationFromDirection();
	void draw();
};

#endif !__ZERGLING_H__