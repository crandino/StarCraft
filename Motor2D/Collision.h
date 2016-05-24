#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "Module.h"
#include <list>
#include "SDL\include\SDL.h"

using namespace std;

// I don't know how much colliders we will need...

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,

	COLLIDER_UNIT,
	COLLIDER_BUILDING,
	//COLLIDER_SCREEN_BUTTON,//RIE: Future WARNING, this will be removed and we will be using an UI element in the future
	COLLIDER_BOMB,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete;
	bool active;
	COLLIDER_TYPE type;
	Module *callback;

	Collider(SDL_Rect SDL_Rect, COLLIDER_TYPE type, Module *callback = NULL) : rect(SDL_Rect), type(type), callback(callback), to_delete(false), active(true)
	{ }

	void setPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool checkCollision(SDL_Rect &r) const;

	void enable() { active = true; }
	void disable() { active = false; }

};

class Collision : public Module
{

private:

	list<Collider*> colliders;
	
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;

public:

	Collision(bool enabled);

	//Destructor
	~Collision();

	// Called when before render is available
	bool awake(pugi::xml_node&);

	// Call before first frame
	bool start();

	// Called before all updates
	bool preUpdate();

	// Called each loop iteration
	bool update(float dt);

	// Called before quitting
	bool cleanUp();

	Collider* addCollider(SDL_Rect rect, COLLIDER_TYPE type, Module *callback = NULL);
	void drawDebug(Collider *col);
};

#endif //!__COLLISION_H__