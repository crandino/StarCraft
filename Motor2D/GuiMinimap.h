#ifndef __GUIMINIMAP_H__
#define __GUIMINIMAP_H__

#include "App.h"
#include "Render.h"
#include "GuiElements.h"
#include <map>
#include <array>

struct PingInfo
{
	iPoint	    ping_position;
	float		initial_ping_width, initial_ping_height;
	float		final_ping_width, final_ping_height;
	float		current_ping_width, current_ping_height;
	float		ping_speed;
	bool        ping_active;
	Timer		ping_timer;
	Uint32		ping_duration;

	PingInfo() {}
	PingInfo(float initial_width, float initial_height, float final_width, float final_height)
	{
		ping_duration = 4000;
		ping_speed = 0.05f;
		ping_active = false;
		initial_ping_width = current_ping_width =  initial_width;
		initial_ping_height = current_ping_height = initial_height;
		final_ping_width = final_width;
		final_ping_height = final_height;
	}

	void initiate()
	{
		ping_active = true;
		current_ping_width = initial_ping_width;
		current_ping_height = initial_ping_height;
		ping_timer.start();
	}

	void updatePing()
	{
		if ((uint)ping_timer.read() < ping_duration)
		{
			if (current_ping_width > final_ping_width && current_ping_height > final_ping_height)
			{
				current_ping_width -= ping_speed * app->getDt();
				current_ping_height -= ping_speed * app->getDt();
			}
		}
		else
			ping_active = false;	
	}
};

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

	array<PingInfo, 4>   ping_set;

	map<uint, Entity*>*   active_entities = NULL;
	SDL_Texture*		  tex = NULL;

	void		calculateScale();
	iPoint		minimapToWorld(const iPoint &mini_map_pos) const;
	iPoint		worldToMinimap(const iPoint &world_pos) const;

	bool		updatePing();
public:

	bool debug = false;
};
#endif  //__GUIMINIMAP_H__