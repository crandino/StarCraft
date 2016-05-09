#ifndef __SCV_H__
#define __SCV_H__

#include "Unit.h"
#include "ParticleManager.h"
#include <time.h>
#include <stdlib.h>

class Scv : public Unit
{
public:
	// IDLE animations
	Animation	idle_up;
	Animation   idle_right_up;
	Animation   idle_right;
	Animation   idle_right_down;
	Animation   idle_down;
	Animation   idle_left_down;
	Animation   idle_left;
	Animation   idle_left_up;
	vector<Animation*> idle_animation_pack;

	// Walking animations
	Animation	walk_up;
	Animation   walk_right_up;
	Animation   walk_right;
	Animation   walk_right_down;
	Animation   walk_down;
	Animation   walk_left_down;
	Animation   walk_left;
	Animation   walk_left_up;
	vector<Animation*> move_animation_pack;

	//Repair animation
	Animation	repair_up;
	Animation	repair_right_up;
	Animation	repair_right;
	Animation	repair_right_down;
	Animation	repair_down;
	Animation	repair_left_down;
	Animation	repair_left;
	Animation	repair_left_up;
	vector<Animation*> repair_animation_pack;

	//Walking Particles
	Particle	glow_up;
	Particle	glow_right_up;
	Particle	glow_right;
	Particle	glow_right_down;
	Particle	glow_down;
	Particle	glow_left_down;
	Particle	glow_left;
	Particle	glow_left_up;

	//Repair Particles
	Particle	repair_up_part;
	Particle	repair_right_up_part;
	Particle	repair_right_part;
	Particle	repair_right_down_part;
	Particle	repair_down_part;
	Particle	repair_left_down_part;
	Particle	repair_left_part;
	Particle	repair_left_up_part;

	Particle	spark;

	//Dead Particle
	Particle	dead;
	int			repair_power;

	Scv(iPoint &p);
	~Scv();

	bool update(float dt);
	bool repair();
	void move(float dt);
	void draw();

	void setParticleBehaviour();
	void resetParticle();
	void resetSpark();
	void followEntity();
	void AnimationAngle();

};

#endif //__SCV_H__