#ifndef __FIREBAT_H__
#define __FIREBAT_H__

#include "Unit.h"
#include "ParticleManager.h"

class Firebat : public Unit
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

	//Particles
	Particle	fire_up;
	Particle	fire_right_up;
	Particle	fire_right;
	Particle	fire_right_down;
	Particle	fire_down;
	Particle	fire_left_down;
	Particle	fire_left;
	Particle	fire_left_up;

	Particle	    explosion_dead;
	SDL_Texture*	particle_tex;


	Bunker*			     bunker_to_fill = NULL;		// Bunker that can be access by the Firebat
	bool			     inside_bunker = false;		// It's inside?

	bool sound_active = true;

	Firebat(iPoint &p);
	~Firebat();

	void move(float dt);
	void setAnimationFromDirection();
	bool update(float dt);
	void draw();

	void setParticleBehaviour();
	void resetParticle();

};

#endif __FIREBAT_H__