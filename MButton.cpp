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
