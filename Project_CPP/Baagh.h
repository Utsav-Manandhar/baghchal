#pragma once
#include"Animal.h"
#include<iostream>
enum tigerState { Free, trapped };
class Baagh : public Animal
{
private:
	tigerState state = Free;
public:
	Baagh();
	tigerState getState();

	void setState(tigerState s);


};
