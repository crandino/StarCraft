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

	//ATTACK animations for turret
	Animation	attack_up_turret;
	Animation	attack_right_up_turret;
	Animation   attack_right_turret;
	Animation	attack_right_down_turret;
	Animation	attack_down_turret;
	Animation	attack_left_down_turret;
	Animation	attack_left_turret;
	Animation	attack_left_up_turret;
	vector<Animation*>   attack_animation_turret_pack;

	//ATTACK animations for turret on SIEGE MODE
	Animation	attack_siege_mode_up_turret;
	Animation	attack_siege_mode_right_up_turret;
	Animation   attack_siege_mode_right_turret;
	Animation	attack_siege_mode_right_down_turret;
	Animation	attack_siege_mode_down_turret;
	Animation	attack_siege_mode_left_down_turret;
	Animation	attack_siege_mode_left_turret;
	Animation	attack_siege_mode_left_up_turret;
	vector<Animation*>   attack_siege_mode_animation_turret_pack;


	// Attack Particle
	Particle	attack_up_part;
	Particle	attack_right_up_part;
	Particle	attack_right_part;
	Particle	attack_right_down_part;
	Particle	attack_down_part;
	Particle	attack_left_down_part;
	Particle	attack_left_part;
	Particle	attack_left_up_part;

	Particle	attack_siege_mode_up_part;
	Particle	attack_siege_mode_right_up_part;
	Particle	attack_siege_mode_right_part;
	Particle	attack_siege_mode_right_down_part;
	Particle	attack_siege_mode_down_part;
	Particle	attack_siege_mode_left_down_part;
	Particle	attack_siege_mode_left_part;
	Particle	attack_siege_mode_left_up_part;

	Particle	tank_hit;

	// Dead animation
	Particle	dead;

	bool		area_attack;
	float		area_range;
	float		min_area_range;

	bool		siege_mode = false;
	bool		sound_active = true;
	bool		sound_dying = true;

	Tank(iPoint &p);
	~Tank();

	bool update(float dt);
	void setAnimationFromDirection();
	void draw();

	void siegeMode(bool siegeModeFlag);
	void checkUnitDirection();
	void newEntityFound();
	void setParticleBehaviour();
	void resetParticle();

};

#endif __MARINE_H__