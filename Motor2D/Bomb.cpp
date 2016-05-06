#include "Bomb.h"


Bomb::Bomb(iPoint &p)
{
	coll = app->collision->addCollider({ center.x + collider_offset.x, center.y + collider_offset.y, 22, 30 }, COLLIDER_BOMB, app->entity_manager);
}

Bomb::~Bomb()
{

}