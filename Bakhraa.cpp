#pragma once
#include <iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
using namespace std;
using namespace sf;
int grid[5][5];
static int bakhraacount = 20;
static int bakhraakilled = 4;
static int bakhraaremain = 20;
class Bakhraa 
{
private:
	
public:
	Bakhraa() {}//construtor can be used to draw sfml or display texture of bakhraa
	bool isbakhraaAlive() {
		if (bakhraacount <= 20)//gives bakhraa to place 20 goats on board
			return true;
		else
			return false;
	}
	bool isbakhraakilled() {
		if (bakhraakilled > 3)//bakhraa loses if 3 goats are killed
			return true;
		else
			return false;
	}
	void check() {
		if (isbakhraaAlive())
			cout << "place fkin goat";
		if (isbakhraakilled())
			cout << "over";

	}
};


int main() {
	Bakhraa x;
	x.check();
	return 0;
}