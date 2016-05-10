#ifndef __GUITIMER_H__
#define __GUITIMER_H__

#include "GuiElements.h"
#include "GuiLabel.h"

class GuiTimer : public GuiElements
{
public:
	//Constructor
	GuiTimer();

	void initiate();

	// Sets the timer to control time and the initial_time to countdown
	void changeTimer(Timer &timer, uint initial_time = 0);

	//Called every frame
	void update();

	bool cleanUp();

	//Blitz GuiMinimap
	void draw() const;
	
private:

	GuiLabel    crono;
	bool		active;
	uint		total_time;
	Timer*    	timer_associated;

	uint		seconds, minutes;

	SDL_Texture*  tex = NULL;
};

#endif  //__GUIMINIMAP_H__