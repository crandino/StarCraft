#ifndef __GUITIMER_H__
#define __GUITIMER_H__

#include "GuiElements.h"
#include "GuiLabel.h"

class GuiTimer : public GuiElements
{
public:
	//Constructor
	GuiTimer(iPoint pos, const char *path_tex);

	void initiate();
	void deactivate();

	// Sets the timer to control time and the initial_time to countdown
	void changeTimer(Timer &timer, uint initial_time = 0);

	//Called every frame
	void update();

	bool cleanUp();

	//Blitz GuiMinimap
	void draw() const;

	// Tools
	bool isActive() const;
	uint timeElapsed() const;
	uint totalTime() const;
	
private:

	GuiLabel      crono;
	bool		  active;
	uint		  total_time;
	Timer*    	  timer_associated;

	uint		  seconds, minutes;
	SDL_Texture*  monitor;
};

#endif  //__GUIMINIMAP_H__