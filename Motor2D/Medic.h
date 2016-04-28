#ifndef __MEDIC_H__
#define __MEDIC_H__

#include "Unit.h"

class Medic : public Unit
{
public:

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

	int			healing_power;

	Medic(iPoint &p);

	void setAnimationFromDirection();

	bool update(float dt);

	bool heal();
};

#endif __MEDIC_H__