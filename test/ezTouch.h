#ifndef ezTouch_h
#define ezTouch_h

#include "ezButton.h"

class ezTouch: public ezButton {	
	private:
		int btnPin;
		unsigned long debounceTime;
		unsigned long count;
		int countMode;
		int previousSteadyState;  // the previous steady state from the input pin, used to detect pressed and released event
		int lastSteadyState;      // the last steady state from the input pin
		int lastFlickerableState; // the last flickerable state from the input pin
		unsigned long lastDebounceTime; // the last time the output pin was toggled
		int buttonThreshold; //the threshold used in the touch signal
		int analogMeasurement;
		int touchBit;
	public: 
		explicit ezTouch(int pin) : ezButton( pin)	{};
		explicit ezTouch(int pin, int mode) : ezButton( pin, mode){};
		void setTouchThreshold(int threshold);
    	int getStateRaw(void);
    	void loop(void);
};

#endif
