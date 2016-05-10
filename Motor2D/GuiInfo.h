#ifndef __GUIINFO_H__
#define __GUIINFO_H__

#include "GuiElements.h"
#include "GuiLabel.h"

class GuiInfo : public GuiElements
{
public:
	//Constructor
	GuiInfo(iPoint pos, const char *tex_path) : GuiElements(), info_tex("O", 0)
	{
		active = false;
		setLocalPos(pos.x, pos.y);
		info_tex.setLocalPos(28,38);
		text_wrapping = 100;
		info_tex.setText("O", 0, text_wrapping);
		monitor = app->tex->loadTexture(tex_path);
	}

	//Called every frame
	void update()
	{
		if (active && (uint)timer.read() > display_time)
			active = false;
	}

	bool cleanUp()
	{
		return true;
	}

	//Blitz GuiMinimap
	void draw() const
	{
		if (active)
		{
			app->render->blit(monitor, rect.x, rect.y, NULL, 0.0f);
			info_tex.draw();
		}		
	}

	void newInfo(const char *text, uint _display_time)
	{
		info_tex.setText(text, 0, text_wrapping);
		active = true;
		timer.start();
		display_time = _display_time;
	}

private:

	SDL_Texture*		  monitor;
	GuiLabel			  info_tex;
	Timer			      timer;
	uint				  display_time;
	uint				  text_wrapping;
	bool				  active;

};
#endif  //__GUIINFO_H__