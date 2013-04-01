#include "ConsoleOutput.h"
#include "LightsTimer.h"
#include "LightsStatus.h"
#include <cassert>

#include <iostream>
using namespace std;

static HANDLE hConsole;

const char trafficLightFrame[] = "\n - \n|*|\n - \n|*|\n - \n|*|\n - \n";

static void ClearScreen()
{
    COORD coordScreen = {0, 0};    

    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; 
    DWORD conSize;                 
	
	SetConsoleTextAttribute(hConsole, 0);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    conSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ',
       conSize, coordScreen, &cCharsWritten);
  
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
       conSize, coordScreen, &cCharsWritten);

    SetConsoleCursorPosition(hConsole, coordScreen );
}

static void ConfigureLightsAndDisplay(char* lights, int lightSet)
{
	for( unsigned int i = 0; i < strlen(lights); i++ )
	{
		switch(i)
		{
		case 6:
			if( CLightsStatus::StatusDetail()->GetStatusRed(lightSet) )
				SetConsoleTextAttribute(hConsole, RED);
			else
				SetConsoleTextAttribute(hConsole, NULL);
			break;
		case 14:
			if( CLightsStatus::StatusDetail()->GetStatusAmber(lightSet) )
				SetConsoleTextAttribute(hConsole, AMBER); //My exs name :D
			else
				SetConsoleTextAttribute(hConsole, NULL);
			break;
		case 22:
			if( CLightsStatus::StatusDetail()->GetStatusGreen(lightSet) )
				SetConsoleTextAttribute(hConsole, GREEN);
			else
				SetConsoleTextAttribute(hConsole, NULL);
			break;
		default:
			SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
			break;
		}

		putchar(lights[i]);
	}
}

void CConsoleOutput::UpdateDisplay(const int set)
{
	if(CLightsStatus::StatusDetail()->GetStatusRed(set))
	{
		CLightsStatus::StatusDetail()->ClearStatusRed(set);
		CLightsStatus::StatusDetail()->SetStatusGreen(set);
	}

	else if( CLightsStatus::StatusDetail()->GetStatusAmber(set) )
	{
		CLightsStatus::StatusDetail()->ClearStatusAmber(set);
		CLightsStatus::StatusDetail()->SetStatusRed(set);
	}

	else if( CLightsStatus::StatusDetail()->GetStatusAmber(set) && !CLightsStatus::StatusDetail()->GetStatusRed(set) )
	{
		CLightsStatus::StatusDetail()->SetStatusRed(set);
	}

	else if( CLightsStatus::StatusDetail()->GetStatusGreen(set) )
	{
		CLightsStatus::StatusDetail()->ClearStatusGreen(set);
		CLightsStatus::StatusDetail()->SetStatusAmber(set);
	}

}

void CConsoleOutput::OutputDisplay()
{
	ClearScreen();

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	assert( hConsole != NULL );

	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);

	char tmp[MAXBUF] = {0};

	{
		strcpy( (char*)&tmp, (char*)&trafficLightFrame);
		ConfigureLightsAndDisplay(tmp, 0);
	}

	{
		strcpy( (char*)&tmp, (char*)&trafficLightFrame);
		ConfigureLightsAndDisplay(tmp, 1);
	}
}