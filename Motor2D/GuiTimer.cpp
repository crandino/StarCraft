#include "GuiTimer.h"

//Constructor
GuiTimer::GuiTimer() : crono("00 : 00", 0)
{
	crono.setLocalPos(rect.x, rect.y);
	type = TIMER;
	active = false;
	seconds = minutes = 0;
}

//Called every frame
void GuiTimer::update()
{
	if (active)
	{
		int time = timer_associated->read();
		time = total_time - time;

		// If countdown has not finished...
		if (time >= 0)
		{
			seconds = (time / 1000) % 60;
			minutes = (time / 60000);

			char c[15];
			sprintf_s(c, "%.2d : %.2d", minutes, seconds);
			crono.setText(c, 0);
		}
		else
			active = false;		
	}	
}

bool GuiTimer::cleanUp()
{
	return true;
}

//Blitz GuiMinimap
void GuiTimer::draw() const
{
	if(active) crono.draw();
}

void GuiTimer::initiate()
{
	active = true;
}

void GuiTimer::changeTimer(Timer &timer, uint initial_time)
{
	timer_associated = &timer;
	total_time = initial_time;
}
