#include "App.h"
#include "Collision.h"
#include "Input.h"
#include "Render.h"
#include "p2Log.h"

Collision::Collision() : Module()
{
	name.assign("collision");

	matrix[COLLIDER_UNIT][COLLIDER_UNIT] = true; 
	matrix[COLLIDER_UNIT][COLLIDER_BUILDING] = false;

	matrix[COLLIDER_BUILDING][COLLIDER_UNIT] = false;
	matrix[COLLIDER_BUILDING][COLLIDER_BUILDING] = false;	
}

Collision::~Collision()
{}

bool Collision::awake(pugi::xml_node&)
{
	return true;
}

bool Collision::start()
{
	return true;
}


bool Collision::preUpdate()
{
	//Remove all colliders scheduled for deletion
	list<Collider*>::iterator tmp = colliders.begin();
	
	while (tmp != colliders.end())
	{
		if ((*tmp)->to_delete == true)
		{
			RELEASE(*tmp);
			tmp = colliders.erase(tmp);
		}			
		else
			++tmp;
	}

	return true;
}

bool Collision::update(float dt)
{
	// Debug ---
	if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	list<Collider*>::iterator it1 = colliders.begin();
	list<Collider*>::iterator it2;

	Collider *c1;
	Collider *c2;

	while (it1 != colliders.end())
	{
		c1 = (*it1);
		if (!c1->active)
		{
			++it1; continue;
		}

		// Debug ---
		if (debug && c1->active)
			drawDebug(c1);

		it2 = next(it1);				 //avoid checking collisions already checked
		while (it2 != colliders.end())
		{
			c2 = (*it2);
			if (!c2->active)
			{
				++it2; continue;
			}

			if (c1->checkCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->onCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->onCollision(c2, c1);
			}
			++it2;
		}
		++it1;
	}

	return true;
}

void Collision::drawDebug(Collider *col)
{
	Uint8 alpha = 80;
	switch (col->type)
	{
	case COLLIDER_NONE:
		app->render->DrawQuad(col->rect, 255, 255, 255, alpha, false);
		break;
	case COLLIDER_BUILDING:
		app->render->DrawQuad(col->rect, 0, 255, 255, alpha, false);
		break;
	case COLLIDER_UNIT:
		app->render->DrawQuad(col->rect, 255, 0, 255, alpha, false);
		break;
	}
}

bool Collision::cleanUp()
{
	LOG("Freeing all colliders");
	list<Collider*>::reverse_iterator item = colliders.rbegin(); 

	while (item != colliders.rend())
	{
		RELEASE(*item);
		++item;
	}

	colliders.clear();
	return true;
}

Collider* Collision::addCollider(SDL_Rect rect, COLLIDER_TYPE type, Module *callback)
{
	Collider* ret = new Collider(rect, type, callback);
	colliders.push_back(ret); //put the collider at the end of the list
	return ret; 
}

bool Collider::checkCollision(SDL_Rect &r) const
{
	return (bool)SDL_HasIntersection(&rect, &r);
}