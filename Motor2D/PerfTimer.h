#ifndef __PerfTimer_H__
#define __PerfTimer_H__

#include "p2Defs.h"

class PerfTimer
{
public:

	// Constructor
	PerfTimer();

	void start();
	double readMs() const;
	uint64 readTicks() const;

private:
	uint64	started_at;
	static uint64 frequency;
};

#endif //__PerfTimer_H__
