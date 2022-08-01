#pragma once
#include<iostream>
#include"Animal.h"

//static int bakhraa_count = 0;
//static int bakhraa_killed = 0;
//static int bakhraa_remain = 20;
enum goatstate { Dead, alive };
class Bakhraa : public Animal
{
private:
	goatstate state = Dead;
public:
	Bakhraa();
	//construtor can be used to draw sfml or display texture of bakhraa
	goatstate getstate();//just to get state of 'x
	void setstate(goatstate sate);//to set state of individual 

};
