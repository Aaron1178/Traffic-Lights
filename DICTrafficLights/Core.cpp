#include <windows.h>
#include <iostream>
using namespace std;

#include "ConsoleOutput.h"
#include "LightsStatus.h"
#include "LightsTimer.h"

#define LIGHTSTATUS		CLightsStatus::StatusDetail()
#define LIGHTSDISPLAY	CConsoleOutput::ConsoleInst()

int main()
{
	if( LIGHTSTATUS->SystemIsReset() )
	{
		LIGHTSTATUS->SetStatusAmber(0); //0000 0010
		LIGHTSTATUS->SetStatusRed(1); //0000 1010

		LIGHTSDISPLAY->OutputDisplay(); 
	}

	int lightsSet = 0;

	while(!(GetKeyState(VK_ESCAPE) & 0x80))
	{
		if(TimeElapsed(2))
		{
			LIGHTSDISPLAY->UpdateDisplay(lightsSet);
			LIGHTSDISPLAY->OutputDisplay();

			lightsSet = LIGHTSTATUS->LightsCycled(lightsSet);
		}

	}

	return 0;
}