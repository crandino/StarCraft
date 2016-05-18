#ifndef __MUTALISK_H__
#define __MUTALISK_H__

#include "Unit.h"

class Mutalisk : public Unit
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

	//ATTACK animations
	Animation	attack_up;
	Animation   attack_right_up;
	Animation   attack_right;
	Animation   attack_right_down;
	Animation   attack_down;
	Animation   attack_left_down;
	Animation   attack_left;
	Animation   attack_left_up;
	vector<Animation*>   attack_animation_pack;

	// Dead animation
	Animation	dead;

	//Particles
	Particle	attack_up_part;
	Particle	attack_right_up_part;
	Particle	attack_right_part;
	Particle	attack_right_down_part;
	Particle	attack_down_part;
	Particle	attack_left_down_part;
	Particle	attack_left_part;
	Particle	attack_left_up_part;

	Particle	mutalisk_hit;

	bool sound_active = true;

	Mutalisk(iPoint &p);
	~Mutalisk();

	bool update(float dt);
	void setAnimationFromDirection();
	bool attack(Entity* target_to_attack);
	void draw();
	void setParticleBehaviour();
	void resetParticle();
	void particleDirection();

};

#endif __MUTALISK_H__