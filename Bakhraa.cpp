#pragma once
#include <iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
using namespace std;
using namespace sf;
int grid[5][5];
static int bakhraacount = 20;
static int bakhraakilled = 0;
static int bakhraaremain = 20;
enum goatstate { dead, alive };
class Bakhraa 
{
private:
	goatstate state=dead;
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
	goatstate getstate() {//just to get state of 'x' goat
		return state;

	}
	void setstate(goatstate sate) {//to set state of individual goat
		state =sate;
	}
	void check() {
		if (isbakhraaAlive())
			cout << "place goat";
		if (isbakhraakilled())
			cout << "over";

	}
};


int main() {
	Bakhraa goat[21];
	for (int i = 0; i < 20; i++) {
		//goat[i].check();
		
	}
	cout << "state ";
	goat[0].setstate(dead);

	cout<<goat[0].getstate();
	goat[1].setstate(alive);

	cout<<goat[1].getstate();
	return 0;
}