#ifndef __GUIINFO_H__
#define __GUIINFO_H__

#include "GuiElements.h"
#include "GuiLabel.h"
#include <queue>

#define MAX_LENGTH_MESSAGE 250

struct Message
{
	char c[MAX_LENGTH_MESSAGE];
	uint display_time;

	Message(const char *tex, uint total_time)
	{
		strcpy_s(c, MAX_LENGTH_MESSAGE, tex);
		display_time = total_time;
	}
};

class GuiInfo : public GuiElements
{
public:
	//Constructor
	GuiInfo(iPoint pos, const char *tex_path) : GuiElements(), info_tex("O", 0)
	{
		queue_loaded = false;
		setLocalPos(pos.x, pos.y);
		info_tex.setLocalPos(28,38);
		text_wrapping = 100;
		info_tex.setText("O", 0, text_wrapping);
		monitor = app->tex->loadTexture(tex_path);
	}

	//Called every frame
	void update()
	{
		if (queue_of_messages.size() > 0)
		{
			Message *m = &queue_of_messages.front();

			if (new_text)
			{
				timer.start();
				info_tex.setText(m->c, 0, text_wrapping);
				new_text = false;
			}				
			
			if (timer.read() > m->display_time)
			{
				queue_of_messages.pop();
				new_text = true;
			}
		}
	}

	bool cleanUp()
	{
		return true;
	}

	//Blitz GuiMinimap
	void draw() const
	{
		if (queue_of_messages.size() > 0)
		{
			app->render->blit(monitor, rect.x, rect.y, NULL, 0.0f);
			info_tex.draw();
		}		
	}

	void newInfo(const char *text, uint _display_time)
	{
		queue_of_messages.push(Message(text, _display_time));
		new_text = true;
		queue_loaded = true;
	}

	bool isLoaded()
	{
		return queue_loaded;
	}

	void unload()
	{
		for (uint i = 0; i < queue_of_messages.size(); ++i)
			queue_of_messages.pop();
		queue_loaded = false;
	}

private:

	SDL_Texture*		  monitor;
	GuiLabel			  info_tex;
	Timer			      timer;
	uint				  display_time;
	uint				  text_wrapping;
	bool				  new_text;
	bool			      queue_loaded;
	queue<Message>		  queue_of_messages;

};
#endif  //__GUIINFO_H__