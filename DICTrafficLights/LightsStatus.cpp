#include "LightsStatus.h"

#define SHIFTLEFT(n) (1 << n)

bool CLightsStatus::SystemIsReset()
{
	if(systemStatus)
		return false;

	return true;
}

void CLightsStatus::SetStatusRed(const int lights)
{
	switch(lights)
	{
	case 0:
		systemStatus |= SHIFTLEFT(0); //0000 0001
		break;
	case 1:
		systemStatus |= SHIFTLEFT(3); //0000 1000
		break;
	default:
		break;
	}
}

void CLightsStatus::SetStatusAmber(const int lights)
{
	switch(lights)
	{
	case 0:
		systemStatus |= SHIFTLEFT(1); //0000 0010
		break;
	case 1:
		systemStatus |= SHIFTLEFT(4); //0001 0000
		break;
	default:
		break;
	}
}

void CLightsStatus::SetStatusGreen(const int lights)
{
	switch(lights)
	{
	case 0:
		systemStatus |= SHIFTLEFT(2); //0000 0100
		break;
	case 1:
		systemStatus |= SHIFTLEFT(5); //0010 0000
		break;
	default:
		break;
	}
}

void CLightsStatus::ClearStatusRed(const int lights)
{
	switch(lights)
	{
	case 0:
		systemStatus &= ~SHIFTLEFT(0); //inverts bit at 2^0
		break;
	case 1:
		systemStatus &= ~SHIFTLEFT(3); //inverts bit at 2^3
		break;
	default:
		break;
	}
}

void CLightsStatus::ClearStatusAmber(const int lights)
{
	switch(lights)
	{
	case 0:
		systemStatus &= ~SHIFTLEFT(1); //inverts bit at 2^1
		break;
	case 1:
		systemStatus &= ~SHIFTLEFT(4); //inverts bit at 2^4
		break;
	default:
		break;
	}
}

void CLightsStatus::ClearStatusGreen(const int lights)
{
	switch(lights)
	{
	case 0:
		systemStatus &= ~SHIFTLEFT(2); //inverts bit at 2^2
		break;
	case 1:
		systemStatus &= ~SHIFTLEFT(5); //inverts bit at 2^5
		break;
	default:
		break;
	}
}

bool CLightsStatus::GetStatusRed(const int lights) const
{
	switch(lights)
	{
	case 0:
		if( systemStatus & SHIFTLEFT(0) )
			return true;
		else
			return false;
		break;
	case 1:
		if( systemStatus & SHIFTLEFT(3) )
			return true;
		else
			return false;
		break;
	default:
		return false;
		break;
	}

	return false;
}

bool CLightsStatus::GetStatusAmber(const int lights) const
{
	switch(lights)
	{
	case 0:
		if( systemStatus & SHIFTLEFT(1) )
			return true;
		else
			return false;
		break;
	case 1:
		if( systemStatus & SHIFTLEFT(4) )
			return true;
		else
			return false;
		break;
	default:
		return false;
		break;
	}

	return false;
}

bool CLightsStatus::GetStatusGreen(const int lights) const
{
	switch(lights)
	{
	case 0:
		if( systemStatus & SHIFTLEFT(2) )
			return true;
		else
			return false;
		break;
	case 1:
		if( systemStatus & SHIFTLEFT(5) )
			return true;
		else
			return false;
		break;
	default:
		return false;
		break;
	}

	return false;
}

//Red 0 | 3
//Amber 1 | 4
//Green 2 | 5

int CLightsStatus::LightsCycled(int lSet)
{
	if( systemStatus & SHIFTLEFT(2) )
		lightsCycled |= SHIFTLEFT(2);

	if( (lightsCycled & SHIFTLEFT(2)) && (lSet == 0) )
	{
		if( systemStatus & SHIFTLEFT(1) )
			lightsCycled |= SHIFTLEFT(1);

		if( systemStatus & SHIFTLEFT(0) )
			lightsCycled |= SHIFTLEFT(0);

		if( lightsCycled & SHIFTLEFT(1) && lightsCycled & SHIFTLEFT(0) )
		{
			//Clear the bits
			lightsCycled &= ~SHIFTLEFT(0); //Clear bit at 2^0
			lightsCycled &= ~SHIFTLEFT(1); //Clear bit at 2^1
			lightsCycled &= ~SHIFTLEFT(2); //Clear bit at 2^2

			return 1;
		}
	}

	if( systemStatus & SHIFTLEFT(5) )
		lightsCycled |= SHIFTLEFT(5);

	if( (lightsCycled & SHIFTLEFT(5)) && (lSet == 1) )
	{
		if( systemStatus & SHIFTLEFT(4) )
			lightsCycled |= SHIFTLEFT(4);

		if( systemStatus & SHIFTLEFT(3) )
			lightsCycled |= SHIFTLEFT(3);

		if( lightsCycled & SHIFTLEFT(4) && lightsCycled & SHIFTLEFT(3) )
		{
			//Clear bits
			lightsCycled &= ~SHIFTLEFT(3); //Clear bit at 2^3
			lightsCycled &= ~SHIFTLEFT(4); //Clear bit at 2^4
			lightsCycled &= ~SHIFTLEFT(5); //Clear bit at 2^5

			return 0;
		}
	}

	return lSet;
}