#ifndef __TANK_H__
#define __TANK_H__

#include "Unit.h"

class Tank : public Unit
{
public:

	// Turret animation
	Animation   *current_animation_turret;

	// IDLE animations (when tank doesn't move and does attack)
	Animation	idle_up;
	Animation	idle_right_up;
	Animation   idle_right;
	Animation	idle_right_down;
	Animation	idle_down;
	Animation	idle_left_down;
	Animation	idle_left;
	Animation	idle_left_up;
	vector<Animation*>   idle_animation_pack;

	// MOVING animations (when tank moves)
	Animation	walk_up;
	Animation   walk_right_up;
	Animation   walk_right;
	Animation   walk_right_down;
	Animation   walk_down;
	Animation   walk_left_down;
	Animation   walk_left;
	Animation   walk_left_up;
	vector<Animation*>   move_animation_pack;

	// SIEGE_MODE animations (when tank activates or deactivate siege mode)
	Animation   siege_mode_on;
	Animation   siege_mode_on_turret;
	Animation   siege_mode_off;	
	Animation   siege_mode_off_turret;
	
	// IDLE animations for turret (when tank keeps quiet, moves and attacks)
	Animation	idle_up_turret;
	Animation	idle_right_up_turret;
	Animation   idle_right_turret;
	Animation	idle_right_down_turret;
	Animation	idle_down_turret;
	Animation	idle_left_down_turret;
	Animation	idle_left_turret;
	Animation	idle_left_up_turret;
	vector<Animation*>   idle_animation_turret_pack;

	// IDLE animations for turret on SIEGE MODE (when tank keeps quiet, moves and attacks)
	Animation	idle_siege_mode_up_turret;
	Animation	idle_siege_mode_right_up_turret;
	Animation   idle_siege_mode_right_turret;
	Animation	idle_siege_mode_right_down_turret;
	Animation	idle_siege_mode_down_turret;
	Animation	idle_siege_mode_left_down_turret;
	Animation	idle_siege_mode_left_turret;
	Animation	idle_siege_mode_left_up_turret;
	vector<Animation*>   idle_siege_mode_animation_turret_pack;

	// Dead animation
	Animation	dead;

	bool		area_attack;
	float		area_range;

	bool		siege_mode = false;

	//FX
	uint fx_sige_mode_on;
	uint fx_sige_mode_turret;
	uint fx_missile_none_siege;
	uint fx_missile_siege;

	Tank(iPoint &p);
	~Tank();

	bool start();
	bool update(float dt);
	void setAnimationFromDirection();
	void draw();

	void siegeMode(bool siegeModeFlag);
	void checkUnitDirection();
	void newEntityFound();

};

#endif __MARINE_H__