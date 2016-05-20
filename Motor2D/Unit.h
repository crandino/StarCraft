#ifndef __UNIT_H__
#define __UNIT_H__

#include "Entity.h"
#include "p2Log.h"
#include "queue"

class Unit: public Entity
{
public:

	//---COLOR OF THE TERRAN UNITS
	// H -> 221
	// S -> 68
	// B -> -1

	//---COLOR OF THE ZERG UNITS
	// H -> 0
	// S -> 76
	// B -> -5

	// PathFinding and movement variables
	bool				has_target;						// If has a target, the unit moves.
	bool				has_focus = false;						// If the unit make focus
	vector<iPoint>		path;							// The path returned by the PathFinding that the unit follows...
	float				speed;							// ...at some speed.
	float				group_speed;
	bool				grouped;
	iPoint				distance_to_center_selector = { 0, 0 };    // Useful for PathFinding for groups of units
	iPoint				target_pos = { -1, -1 };

	bool				flying;							// Does it flies?
	bool				area_attack = false;			// Can attack in area?
	float				area_range = 0.0f;				// Range of area attack

	Unit();
	virtual ~Unit();

	virtual void calculePos();
	virtual Entity* searchEnemy(bool can_attack_to_flying = true, float min_area_range = -999.0f);

	virtual bool attack(Entity* target_to_attack, float min_range = -999.0f);
	virtual void attackWithoutRange(Entity* target_to_attack);

	virtual void move(float dt);

	virtual bool update(float dt);

	// Depending on its state, the entity obtains the corresponding angle // CRZ
	void checkUnitDirection();

	void newEntityFound();
};


#endif //__UNIT_H__