#include "Bakhraa.h"

Bakhraa::Bakhraa() {}//construtor can be used to draw sfml or display texture of bakhraa

goatstate Bakhraa::getstate() {//just to get state of 'x' goat
	return state;

}
void Bakhraa::setstate(goatstate s) {//to set state of individual goat
	state = s;
}
int Bakhraa::getCount()
{
	return bakhraa_count;
}
void Bakhraa::increaseCount()
{
	bakhraa_count++;
}
int Bakhraa::getDeathToll()
{
	return bakhraa_killed;
}
void Bakhraa::increaseDeathToll()
{
	bakhraa_killed++;
}
