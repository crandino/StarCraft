#ifndef __MINIMAP_H__
#define __MINIMAP_H__

#include "App.h"
#include "Render.h"
#include "EntityManager.h"
#include <map>



class Minimap
{
public:
	//Constructor
	Minimap(SDL_Rect rect);

	//Initializes all remaining data
	bool SetAttributes(map<uint, Entity*>* entities, SDL_Texture* texture, SDL_Texture* square);

	//Called every frame
	bool Update();

	bool CleanUp();

	//Blitz minimap
	bool Print();

private:

	void UpdateScale();

private:

	SDL_Rect rect;
	float scale_x = 0.1f;
	float scale_y = 0.1f;
	int quad_size = 1;

	map<uint, Entity*>* active_entities = NULL;

	SDL_Texture* tex = NULL;
	SDL_Texture* area = NULL;
};










#endif