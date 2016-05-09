#ifndef __MEDIC_H__
#define __MEDIC_H__

#include "Unit.h"

class Medic : public Unit
{
public:
	//IDLE animations
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

	// HEAL animations
	Animation	heal_up;
	Animation   heal_right_up1;
	Animation   heal_right_up2;
	Animation   heal_right_up3;
	Animation   heal_right;
	Animation   heal_right_down1;
	Animation   heal_right_down2;
	Animation   heal_right_down3;
	Animation   heal_down;
	Animation   heal_left_down1;
	Animation   heal_left_down2;
	Animation   heal_left_down3;
	Animation   heal_left;
	Animation   heal_left_up1;
	Animation   heal_left_up2;
	Animation   heal_left_up3;

	vector<Animation*> heal_animation_pack;

	// Dead animation
	Animation	dead;

	int			healing_power;

	////Sounds
	//unsigned int fx_heal;
	//unsigned int fx_death;

	//unsigned int fx_acknowledgement_1;
	//unsigned int fx_acknowledgement_2;
	//unsigned int fx_acknowledgement_3;
	//unsigned int fx_acknowledgement_4;

	//unsigned int fx_affirmation_1;
	//unsigned int fx_affirmation_2;
	//unsigned int fx_affirmation_3;
	//unsigned int fx_affirmation_4;

	//unsigned int fx_annoyance_1;
	//unsigned int fx_annoyance_2;
	//unsigned int fx_annoyance_3;
	//unsigned int fx_annoyance_4;
	//unsigned int fx_annoyance_5;
	//unsigned int fx_annoyance_6;
	//unsigned int fx_annoyance_7;

	//unsigned int fx_ready;

	Medic() {}
	Medic(iPoint &p);

	~Medic();

	//bool start();
	bool update(float dt);

	void setAnimationFromDirection();
	void move(float dt);
	

	bool heal();
};

#endif __MEDIC_H__