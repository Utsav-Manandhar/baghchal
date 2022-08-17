#pragma once

#include"Baagh.h"


Baagh::Baagh() {}
goatstate Baagh::getState()
{
	return state;
}
void Baagh::setstate(goatstate s)
{
	state = s;
}
