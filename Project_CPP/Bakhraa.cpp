#include "Bakhraa.h"

	Bakhraa::Bakhraa(){}//construtor can be used to draw sfml or display texture of bakhraa

	goatstate Bakhraa::getstate() {//just to get state of 'x' goat
		return state;

	}
	void Bakhraa::setstate(goatstate sate) {//to set state of individual goat
		state = sate;
	}

