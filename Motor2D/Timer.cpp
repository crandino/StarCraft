// ----------------------------------------------------
// Timer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "Timer.h"
#include "SDL\include\SDL_timer.h"

// ---------------------------------------------
Timer::Timer()
{
	start();
}

// ---------------------------------------------
void Timer::start()
{
	started_at = SDL_GetTicks();
}

void Timer::startWithTimeElapsed(uint time_elapsed)
{
	started_at = SDL_GetTicks() - time_elapsed;
}

// ---------------------------------------------
uint32 Timer::read() const
{
	return (SDL_GetTicks() - started_at);
}

// ---------------------------------------------
float Timer::readSec() const
{
	return read() / 1000.f;
}

bool Timer::waitSec(Timer& timer, float secs)const
{
	if (timer.readSec() >= secs)
	{
		return true;
	}

	return false;
}