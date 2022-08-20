#pragma once
#include "Animal.h"
#include <iostream>
class Baagh : public Animal
{
private:
	goatstate state = Free;

public:
	static int tiger_number;
	Baagh();
	goatstate getState();

	void setstate(goatstate s);
};
