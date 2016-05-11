#include "GuiTimer.h"
#include "Textures.h"

//Constructor
GuiTimer::GuiTimer(iPoint pos, const char *tex_path) : crono("00 : 00", 0)
{
	setLocalPos(pos.x, pos.y);
	crono.setLocalPos(pos.x + 50, pos.y + 25);
	type = TIMER;
	active = false;
	seconds = minutes = 0;
	monitor = app->tex->loadTexture(tex_path);
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
	if (active)
	{
		app->render->blit(monitor, rect.x, rect.y, NULL, 0.0f);
		crono.draw();
	}
}

void GuiTimer::initiate()
{
	active = true;
}

void GuiTimer::deactivate()
{
	active = false;
}

void GuiTimer::changeTimer(Timer &timer, uint initial_time)
{
	timer_associated = &timer;
	total_time = initial_time;
}
