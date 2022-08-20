#pragma once
#include<iostream>
#include"Animal.h"

//static int bakhraa_count = 0;
//static int bakhraa_killed = 0;
//static int bakhraa_remain = 20;
//enum goatstate { Dead, alive };
class Bakhraa : public Animal
{
private:
	static int bakhraa_count;
	static int bakhraa_killed;
	goatstate state = Dead;
public:
	static int goat_number;
	Bakhraa();
	//construtor can be used to draw sfml or display texture of bakhraa
	goatstate getstate();//just to get state of 'x
	void setstate(goatstate s);//to set state of individual
	
	static int getCount();
	static void increaseCount();
	static int getDeathToll();
	static void increaseDeathToll();
};


