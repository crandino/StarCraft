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
	bool SetAttributes(map<uint, Entity*>* entities, SDL_Texture* texture);

	//Called every frame
	void update();

	bool cleanUp();

	//Blitz GuiMinimap
	void draw() const;
	void activePing(iPoint ping_position);

private:

	SDL_Rect	rect;
	SDL_Rect	area;
	fPoint		scale;

	uint		max_ping_width, max_ping_height;
	iPoint	    ping_position;
	float		ping_width, ping_height;
	float		ping_speed;
	bool        ping_active;
	Timer		ping_timer;
	Uint32		ping_duration;			// On miliseconds

	map<uint, Entity*>*   active_entities = NULL;
	SDL_Texture*		  tex = NULL;

	void		calculateScale();
	iPoint		minimapToWorld(const iPoint &mini_map_pos) const;
	iPoint		worldToMinimap(const iPoint &world_pos) const;

	bool		updatePing();
};

#endif  //__GUIMINIMAP_H__