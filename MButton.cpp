/**
 * Encapsulate tracking pushes on a normally-open momentary button.
 *
 * After a call to check(), the button may report that it:
 *  - wasClicked(): tapped briefly
 *  - wasHeld(): pressed for a longer period of time (and perhaps still closed)
 * The next call to check() will not report on that previous event.
 *
 *
 * Put this file in your libraries folder along with MButton.h
 *
 *
 * Written by Mark Fickett
 * Modified by Julian Loiacono December '14
 * Further Modification by Greenonline 2017
 */

#include "MButton.h"


MButton::MButton(int inputPin)
	: wasClosed(false), pin(inputPin)
{}

void MButton::setThreshold(unsigned long newThreshold)
{
	holdThreshold = newThreshold;
}

void MButton::setHoldThreshold(unsigned long newThreshold)
{
	setThreshold(newThreshold);
}

void MButton::setBounceThreshold(unsigned long newThreshold)
{
	bounceThreshold = newThreshold;
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
