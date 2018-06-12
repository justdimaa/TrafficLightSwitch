/*
Name:    Ampel.ino
Created: 6/6/2018 12:24:01 PM
Author:  Dimaa
*/

#include "TrafficLight.h"

const byte PIN_RED = D0;
const byte PIN_YELLOW = D1;
const byte PIN_GREEN = D2;
const byte PIN_SWITCH = D5;

TrafficLight trafficLight;

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(115200);
	trafficLight.begin(PIN_RED, PIN_YELLOW, PIN_GREEN);

	pinMode(PIN_SWITCH, INPUT);
	attachInterrupt(digitalPinToInterrupt(PIN_SWITCH), interrupt, RISING);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	trafficLight.loop();
}

// the interrupt function interrupts the process of the traffic light
void interrupt()
{
	trafficLight.interrupt();
}
