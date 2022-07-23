#pragma once
#include <iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
using namespace std;
using namespace sf;
int grid[5][5];
class Animal : public CircleShape
{
protected:
	int pos_x, pos_y;
public:
	void set_Position(int x, int y)
	{
		this->pos_x = x;
		this->pos_y = y;
	}
	int get_X()
	{
		return pos_x;

	}
	int get_Y()
	{
		return pos_y;
	}	
};
