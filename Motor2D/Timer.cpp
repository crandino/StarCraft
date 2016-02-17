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

// ---------------------------------------------
uint32 Timer::read() const
{
	return SDL_GetTicks() - started_at;
}

// ---------------------------------------------
float Timer::readSec() const
{
	return read() / 1000.f;
}