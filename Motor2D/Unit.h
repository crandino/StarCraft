#ifndef __UNIT_H__
#define __UNIT_H__

#include "Entity.h"
#include "p2Log.h"
#include "queue"

class Unit: public Entity
{
public:

	bool				flying;
	bool				has_target;
	vector<iPoint>		path;
	iPoint				distance_to_center_selector;
	Vector2D<int>       direction;
	float				speed;

	queue<iPoint>		queue;

	Unit();

	virtual void calculePos();

	virtual bool attack();

	virtual void move(float dt);

	virtual bool update(float dt);

	// Depending on its state, the entity obtains the corresponding angle // CRZ
	void checkUnitDirection();

	void newNearestEntityFinded();
};


#endif //__UNIT_H__