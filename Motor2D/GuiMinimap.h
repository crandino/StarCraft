#ifndef __GUIMINIMAP_H__
#define __GUIMINIMAP_H__

#include "App.h"
#include "Render.h"
#include "GuiElements.h"
#include <map>

class GuiMinimap : public GuiElements
{
public:
	//Constructor
	GuiMinimap(SDL_Rect rect);

	//Initializes all remaining data
	bool SetAttributes(map<uint, Entity*>* entities, SDL_Texture* texture, SDL_Texture* square);

	//Called every frame
	void update();

	bool cleanUp();

	//Blitz GuiMinimap
	void draw() const;

private:

	void calculateScale();
	iPoint minimapToWorld(const iPoint &mini_map_pos);

private:

	SDL_Rect rect;
	fPoint scale;
	int quad_size = 1;

	map<uint, Entity*>* active_entities = NULL;

	SDL_Texture* tex = NULL;
	SDL_Texture* area = NULL;
};

#endif  //__GUIMINIMAP_H__