#ifndef __Timer_H__
#define __Timer_H__

#include "p2Defs.h"

class Timer
{
public:

	// Constructor
	Timer();

	void start();
	void startWithTimeElapsed(uint time_elapsed);
	uint32 read() const;
	float readSec() const;
	bool waitSec(Timer& timer, float secs)const;

private:

	uint32 started_at;
};

#endif //__Timer_H__
