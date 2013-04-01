#include <stdio.h>
#include <time.h>
#include "LightsTimer.h"

static time_t lastTime = 0;
static time_t currentTime = 0;

static time_t GetTimeDiff()
{
	currentTime = time(0);

	return currentTime - lastTime;
}

int TimeElapsed(time_t secs)
{
	if( GetTimeDiff() >= secs )
	{
		lastTime = currentTime;
		return 1;
	}

	return 0;
}