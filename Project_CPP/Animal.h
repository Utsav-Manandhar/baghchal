#pragma once
#include <iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
using namespace std;
using namespace sf;
class Animal : public CircleShape
{
protected:
	int pos_x, pos_y;
public:
	void set_Position(int x, int y);
	int get_X();
	int get_Y();
};