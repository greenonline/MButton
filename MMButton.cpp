/*

Put this file in your libraries folder along with mmButton.h

Written by Mark Fickett
Modified by Julian Loiacono December '14
Further Modification by Greenonline 2017
*/

#include "MMButton.h"


#if defined __Used_MomentaryButton__ 
MMButton::MMButton(int inputPin)
	: MomentaryButton(inputPin)
#elif defined __Use_MButton__
MMButton::MMButton(int inputPin)
	: MButton(inputPin)
#else
MMButton::MMButton(int inputPin)
	: MButton(inputPin)
#endif
{ 
        const int MMpin = inputPin;  // there isn't any need for this, since we can use getPin(), 
                                     // however, it may be quicker to use this const, instead of a function call
}

void MMButton::setPullUpDown(boolean isUp)
{
	isPulledUp = isUp;
        digitalWrite(getPin(), isPulledUp);
}

void MMButton::check()  // Using getters and setters
{
	unsigned long currentTimeMillis = millis();
        boolean isClosed = (digitalRead(getPin()) == !isPulledUp);

//	if (isPulledUp)
//          boolean isClosed = (digitalRead(MMpin) == LOW);
//        else
//          boolean isClosed = (digitalRead(MMpin) == HIGH);


	if (isClosed & !getWasClosed())
	{
		setCloseTimeMillis(currentTimeMillis);
	}
	else if (!isClosed & getWasClosed())
	{
		setHeld((currentTimeMillis - getCloseTimeMillis()) >= getHoldThreshold());
		setClicked((!getHeld() && (currentTimeMillis - getCloseTimeMillis()) >= getBounceThreshold()));
	}

	setWasClosed(isClosed);
}

