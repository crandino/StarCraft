#ifndef __UNIT_H__
#define __UNIT_H__

#include "Entity.h"
#include "p2Log.h"
#include "queue"

class Unit: public Entity
{
public:

	// PathFinding and movement variables
	bool				has_target;						// If has a target, the unit moves.
	vector<iPoint>		path;							// The path returned by the PathFinding that the unit follows...
	float				speed;							// ...at some speed.
	iPoint				distance_to_center_selector;    // Useful for PathFinding for groups of units

	bool				flying;							// Does it flies?
	bool				area_attack = false;			// Can attack in area?
	float				area_range = 0.0f;				// Range of area attack

	Unit();

	virtual void calculePos();

	virtual bool attack(Entity* target_to_attack);
	virtual void attackWithoutRange(Entity* target_to_attack);

	virtual void move(float dt);

	virtual bool update(float dt);

	// Depending on its state, the entity obtains the corresponding angle // CRZ
	void checkUnitDirection();

	void newEntityFound();
};


#endif //__UNIT_H__