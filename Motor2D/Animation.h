
#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>
#include "App.h"
#include "SDL\include\SDL.h"

using namespace std;

class Animation
{
private:

	int loops;

public:

	bool				paused;
	float			    current_frame;
	bool			    loop;
	float				speed;
	vector<SDL_Rect>    frames;

	Animation() : speed(1.0f), loop(true), loops(0)
	{ }

	Animation(const Animation& a) : frames(a.frames), speed(a.speed), current_frame(0), loop(a.loop), loops(0), paused(false)
	{ }

	SDL_Rect& getCurrentFrame()
	{
		if (!paused)
		{
			float real_speed =  speed * app->getDt();
			current_frame += real_speed;
			if (current_frame >= frames.size())
			{
				current_frame = (loop) ? 0.0f : frames.size() - 1;
				loops++;
			}
		}		

		return frames[(int)current_frame];
	}

	const SDL_Rect &peekCurrentFrame() const
	{
		return frames[(int)current_frame];
	}

	bool finished()
	{
		return loops > 0;
	}

	void reset()
	{
		loops = 0;
		current_frame = 0;
	}

	void pause()
	{
		paused = true;
	}

	void resume()
	{
		paused = false;
	}

	void setAnimations(int x, int y, int w, int h, int framesPerRow, int framesPerCol, int frameNum)
	{
		for (int i = 0; i < framesPerRow; ++i)
		{
			for (int j = 0; j < framesPerCol; ++j)
			{
				frames.push_back({ x + (w * i), y + (h * j), w, h });
			}
		}
	}

};


#endif // !__ANIMATION_H__