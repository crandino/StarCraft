#ifndef __GUIINFO_H__
#define __GUIINFO_H__

#include "GuiElements.h"
#include "GuiLabel.h"
#include <queue>

#define MAX_LENGTH_MESSAGE 250

struct Message
{
	char		c[MAX_LENGTH_MESSAGE];
	uint		display_time;
	bool		beap_play;

	Message(const char *tex, uint total_time, bool beap)
	{
		strcpy_s(c, MAX_LENGTH_MESSAGE, tex);
		display_time = total_time;
		beap_play = beap;
	}
};

class GuiInfo : public GuiElements
{
public:

	deque<Message>		  queue_of_messages;

	//Constructor
	GuiInfo(iPoint pos, const char *tex_path) : GuiElements(), info_tex("O", 0)
	{
		queue_loaded = false;

		setLocalPos(pos.x, pos.y);
		info_tex.setLocalPos(28,38);

		text_wrapping = 100;
		info_tex.setText("O", 1, text_wrapping);

		monitor = app->tex->loadTexture(tex_path);
		no_highlighted = { 0, 0, 204, 144 };
		highlighted = { 0, 144, 204, 144 };
		blink_time = 2000;

		transmission_fx = app->audio->loadFx("Audio/FX/UI/transmission.wav");
	}

	//Called every frame
	void update()
	{
		// There are messages to show?
		if (queue_of_messages.size() > 0)
		{
			Message *m = &queue_of_messages.front();

			// Its the first time that this message will appear?
			if (new_text)
			{
				// Text creation
				timer.start();
				info_tex.setText(m->c, 1, text_wrapping);
				new_text = false;
				if (m->beap_play)
					app->audio->playFx(transmission_fx);
			}				
			
			if (timer.read() > m->display_time)
			{
				// When the time is over, eliminated this message.
				queue_of_messages.pop_front();
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
			if (timer.read() % blink_time < blink_time / 2)
				app->render->blit(monitor, rect.x, rect.y, &highlighted, 0.0f);
			else
				app->render->blit(monitor, rect.x, rect.y, &no_highlighted, 0.0f);
			info_tex.draw();
		}		
	}

	void newInfo(const char *text, uint _display_time, bool beap_play = false)
	{
		queue_of_messages.push_back(Message(text, _display_time, beap_play));
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
			queue_of_messages.pop_front();
		queue_loaded = false;
	}

	uint timeElapsed() const
	{
		return timer.read();
	}

private:

	SDL_Texture*		  monitor;
	SDL_Rect			  highlighted;
	SDL_Rect			  no_highlighted;

	uint				  transmission_fx;

	GuiLabel			  info_tex;
	Timer			      timer;
	uint				  display_time;
	uint				  blink_time;
	uint				  text_wrapping;
	bool				  new_text;
	bool			      queue_loaded;

};
#endif  //__GUIINFO_H__