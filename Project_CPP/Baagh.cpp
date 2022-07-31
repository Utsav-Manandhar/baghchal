#pragma once

#include"Baagh.h"


Baagh::	Baagh() {}
tigerState Baagh::getState()
	{
		return state;
	}
void Baagh::setState(tigerState s)
	{
		state = s;
	}

