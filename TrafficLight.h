#include <Arduino.h>
#include "State.h"

#pragma once
class TrafficLight
{
	byte pinRed;
	byte pinYellow;
	byte pinGreen;

	State currentState;
	bool isInterrupted;
	int timesBlinked;

	unsigned long startMillis;
	unsigned long currentMillis;

	public:
		void begin(byte pinRed, byte pinYellow, byte pinGreen);
		void loop(void);
		void interrupt(void);
	private:
		void changeState(State state);
		void checkStatus(int redLightDuration, int yellowLightDuration, int greenLightDuration);
		void blink(State state, int frequency, int speedInMs);
};

