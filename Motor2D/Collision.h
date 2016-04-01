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

	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_ATTACK,
	COLLIDER_ENEMY_ATTACK,
	COLLIDER_BOMB,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete;
	COLLIDER_TYPE type;
	Module *callback;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module *callback = NULL) : rect(rectangle), type(type), callback(callback), to_delete(false)
	{ }

	void setPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool checkCollision(SDL_Rect r) const;
};

class Collision : public Module
{

private:

	list<Collider*> colliders;
	
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug;

public:

	Collision();

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

	Collider* addCollider(SDL_Rect rect, COLLIDER_TYPE type, bool positions_scaled = true, Module *callback = NULL);
	void drawDebug(Collider *col);
};

#endif //!__COLLISION_H__