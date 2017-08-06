/*

Put this file in your libraries folder along with MButton.h

Written by Mark Fickett
Modified by Julian Loiacono December '14
*/

#include "mButton.h"


MButton::MButton(int inputPin)
	: wasClosed(false), pin(inputPin)
{}

void MButton::setThreshold(unsigned long newThreshold)
{
	holdThreshold = newThreshold;
}

void MButton::setup()
{
	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);
	holdThreshold = 250;
	bounceThreshold = 50;
}

void MButton::check()
{
	unsigned long currentTimeMillis = millis();
	boolean isClosed = (digitalRead(pin) == LOW);

	if (isClosed & !wasClosed)
	{
		closeTimeMillis = currentTimeMillis;
	}
	else if (!isClosed & wasClosed)
	{
		held = (currentTimeMillis - closeTimeMillis) >= holdThreshold;
		clicked = (!held && (currentTimeMillis - closeTimeMillis) >= bounceThreshold);
	}

	wasClosed = isClosed;
}

boolean MButton::wasClicked() {
	if (clicked){
		clicked = false;
		return true;
	}
	else{
		return false;
	}
}

boolean MButton::wasHeld() {
	if (held){
		held = false;
		return true;
	}
	else{
		return false;
	}
}

// Getters
        int MButton::getPin(){return pin;}
        unsigned long MButton::getCloseTimeMillis(){return closeTimeMillis;}
//        boolean MButton::getWasHeld(){return wasHeld;}
        boolean MButton::getWasClosed(){return wasClosed;}
        boolean MButton::getHeld(){return held;}
        boolean MButton::getClicked(){return clicked;}  // Defers from wasClicked(), gives actual variable, no logic involved, differs from MButton.cpp version
        unsigned long MButton::getHoldThreshold(){return holdThreshold;}
        unsigned long MButton::getBounceThreshold(){return bounceThreshold;}
// Setters
        void MButton::setCloseTimeMillis(unsigned long value){closeTimeMillis = value;}
//        void MButton::setWasHeld(boolean value){wasHeld = value;}
        void MButton::setWasClosed(boolean value){wasClosed = value;}
        void MButton::setHeld(boolean value){held = value;}
        void MButton::setClicked(boolean value){clicked = value;}
