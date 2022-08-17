#pragma once
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
using namespace std;
using namespace sf;
enum goatstate { Dead, alive,Free =0,trapped =1 };

class Animal : public CircleShape
{
protected:
	int pos_x, pos_y;
public:
	void set_Position(int x, int y);
	int get_X();
	int get_Y();
	virtual void setstate(goatstate s) = 0;
};
