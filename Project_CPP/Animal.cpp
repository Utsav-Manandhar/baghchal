
#pragma once
#include"Animal.h"
using namespace std;
using namespace sf;
void Animal::set_Position(int x = 0, int y = 0)
{
	this->pos_x = x;
	this->pos_y = y;
}
int Animal::get_X()
{
	return pos_x;
}
int Animal::get_Y()
{
	return pos_y;
}
