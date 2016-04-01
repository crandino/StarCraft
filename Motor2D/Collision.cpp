#include "App.h"
#include "Collision.h"
#include "Input.h"
#include "Render.h"
#include "p2Log.h"

#define SCALE_FACTOR 100

Collision::Collision() : Module()
{
	name.assign("collision");
	debug = false;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_ATTACK] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_ATTACK] = true;
	matrix[COLLIDER_WALL][COLLIDER_BOMB] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_ATTACK] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BOMB] = true;


	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_ATTACK] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_ATTACK] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BOMB] = false;


	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_ENEMY_ATTACK] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_BOMB] = false;

	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_ENEMY_ATTACK] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_BOMB] = false;

	matrix[COLLIDER_BOMB][COLLIDER_WALL] = false;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BOMB][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_BOMB][COLLIDER_ENEMY_ATTACK] = false;
	matrix[COLLIDER_BOMB][COLLIDER_BOMB] = false;

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
	// IPL: I don't know if that's correct, I let you how it was. 

	// Remove all colliders scheduled for deletion
	//doubleNode<Collider*> *tmp = colliders.getFirst();
	//doubleNode<Collider*> *tmp2;

	//while (tmp != NULL)
	//{
	//	tmp2 = tmp->next;
	//	if (tmp->data->to_delete == true)
	//	{
	//		delete tmp->data;
	//		colliders.del(tmp);
	//	}
	//	tmp = tmp2;
	//}

	list<Collider*>::iterator item = colliders.begin();
	while (item != colliders.end())
	{
		if ((*item)->to_delete == true)
		{
			RELEASE(*item);
			colliders.pop_back();
		}
		++item;
	}

	return true;
}

bool Collision::update(float dt)
{
	if (app->input->getKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	list<Collider*>::iterator tmp = colliders.begin();

	Collider* c1;
	Collider* c2;


	//IPL: I don't know how implement this in STL, I have problems in the second doubleNode<Collider*>*tmp2 = tmp->next

	//while (tmp != colliders.end())
	//{
	//	c1 = (*tmp);
	//	++tmp;
	//	// Debug ---
	//	if (debug)
	//		drawDebug(c1);

	//	list<Collider*> tmp2; // avoid checking collisions already checked
	//	(*tmp) = (tmp2);
	//	while (tmp2 != NULL)
	//	{
	//		c2 = tmp2->data;

	//		if (c1->checkCollision(c2->rect) == true)
	//		{
	//			if (matrix[c1->type][c2->type] && c1->callback)
	//				c1->callback->onCollision(c1, c2);

	//			if (matrix[c2->type][c1->type] && c2->callback)
	//				c2->callback->onCollision(c2, c1);
	//		}
	//		tmp2 = tmp2->next;
	//	}
	//	tmp = tmp->next;
	//}

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
	case COLLIDER_WALL:
		app->render->DrawQuad(col->rect, 0, 0, 255, alpha);
		break;
	case COLLIDER_PLAYER:
		app->render->DrawQuad(col->rect, 255, 0, 0, alpha, false);
		break;
	case COLLIDER_ENEMY:
		app->render->DrawQuad(col->rect, 255, 100, 0, alpha, false);
		break;
	case COLLIDER_PLAYER_ATTACK:
		app->render->DrawQuad(col->rect, 255, 255, 0, alpha, false);
		break;
	case COLLIDER_ENEMY_ATTACK:
		app->render->DrawQuad(col->rect, 0, 255, 255, alpha, false);
		break;
	case COLLIDER_BOMB:
		app->render->DrawQuad(col->rect, 255, 0, 255, alpha, false);
		break;

	}
}

bool Collision::cleanUp()
{
	LOG("Freeing all colliders");
	list<Collider*>::reverse_iterator item = colliders.rbegin(); //IPL: there was a doubleNode<Collider*>*item = colliders.getLast(), I dont know if this is ok 

	while (item != colliders.rend())
	{
		RELEASE(*item);
		item++;
	}

	colliders.clear();
	return true;
}

Collider* Collision::addCollider(SDL_Rect rect, COLLIDER_TYPE type, bool positions_scaled, Module *callback)
{

	if (positions_scaled == false)
	{
		rect.x *= SCALE_FACTOR;
		rect.y *= SCALE_FACTOR;
	}

	rect.w *= SCALE_FACTOR;
	rect.h *= SCALE_FACTOR;

	Collider* ret = new Collider(rect, type, callback);
	colliders.push_back(ret); //put the collider at the end of the list
	return ret;
}

bool Collider::checkCollision(SDL_Rect r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}