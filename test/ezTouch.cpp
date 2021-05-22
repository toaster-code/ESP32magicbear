#include "ezTouch.h"
#include <Arduino.h>
ezTouch::ezTouch(int pin): ezTouch(pin, INPUT) {};

ezTouch::ezTouch(int pin, int mode) {
	btnPin = pin;
	debounceTime = 0;
	count = 0;
	countMode = COUNT_FALLING;

	//pinMode(btnPin, mode);

	analogMeasurement = touchRead(btnPin);
    if (analogMeasurement >= buttonThreshold) {
		touchBit = HIGH;
	} else {
		touchBit = LOW;
	}
	previousSteadyState = touchBit;
	lastSteadyState = previousSteadyState;
	lastFlickerableState = previousSteadyState;

	lastDebounceTime = 0;
}

void ezTouch::setTouchThreshold(int threshold) {
	buttonThreshold = threshold;
}

int ezTouch::getStateRaw(void) {
	touchBit = touchRead(btnPin);
    if (analogMeasurement >= buttonThreshold) {
		touchBit = HIGH;
	} else {
		touchBit = LOW;
	}
	return touchBit;
}


void ezTouch::loop(void) {
	// read the state of the touch pin:
	int analogMeasurement = touchRead(btnPin);
    if (analogMeasurement >= buttonThreshold) {
		touchBit = HIGH;
	} else {
		touchBit = LOW;
	}
	int currentState = touchBit;
	unsigned long currentTime = millis();

	// check to see if you just pressed the button
	// (i.e. the input went from LOW to HIGH), and you've waited long enough
	// since the last press to ignore any noise:

	// If the switch/button changed, due to noise or pressing:
	if (currentState != lastFlickerableState) {
		// reset the debouncing timer
		lastDebounceTime = currentTime;
		// save the the last flickerable state
		lastFlickerableState = currentState;
	}

	if ((currentTime - lastDebounceTime) >= debounceTime) {
		// whatever the reading is at, it's been there for longer than the debounce
		// delay, so take it as the actual current state:

		// save the the steady state
		previousSteadyState = lastSteadyState;
		lastSteadyState = currentState;
	}

	if(previousSteadyState != lastSteadyState){
		if(countMode == COUNT_BOTH)
			count++;
		else if(countMode == COUNT_FALLING){
			if(previousSteadyState == HIGH && lastSteadyState == LOW)
				count++;
		}
		else if(countMode == COUNT_RISING){
			if(previousSteadyState == LOW && lastSteadyState == HIGH)
				count++;
		}
	}
}
