#include "TrafficLight.h"

byte pinRed;
byte pinYellow;
byte pinGreen;

State currentState;
bool isInterrupted;
int timesBlinked;

unsigned long startMillis;
unsigned long currentMillis;

// initializes the traffic light
void TrafficLight::begin(byte pinRed, byte pinYellow, byte pinGreen)
{
	this->pinRed = pinRed;
	this->pinYellow = pinYellow;
	this->pinGreen = pinGreen;

	pinMode(pinRed, OUTPUT);
	pinMode(pinYellow, OUTPUT);
	pinMode(pinGreen, OUTPUT);
	
	this->startMillis = millis();
	this->changeState(State::Red);
}

void TrafficLight::loop()
{
	this->currentMillis = millis();

	if (!this->isInterrupted)
		this->checkStatus(6000, 1000, 3000);
	else
		this->blink(State::Yellow, 10, 250);
}

void TrafficLight::interrupt()
{
	this->isInterrupted = true;
}

void TrafficLight::changeState(State state)
{
	switch (state)
	{
		case State::Red:
			digitalWrite(this->pinRed, HIGH);
			digitalWrite(this->pinYellow, LOW);
			digitalWrite(this->pinGreen, LOW);
			break;
		case State::RedYellow:
			digitalWrite(this->pinRed, HIGH);
			digitalWrite(this->pinYellow, HIGH);
			digitalWrite(this->pinGreen, LOW);
			break;
		case State::Yellow:
			digitalWrite(this->pinRed, LOW);
			digitalWrite(this->pinYellow, HIGH);
			digitalWrite(this->pinGreen, LOW);
			break;
		case State::Green:
			digitalWrite(this->pinRed, LOW);
			digitalWrite(this->pinYellow, LOW);
			digitalWrite(this->pinGreen, HIGH);
			break;
		case State::Off:
			digitalWrite(this->pinRed, LOW);
			digitalWrite(this->pinYellow, LOW);
			digitalWrite(this->pinGreen, LOW);
			break;
	}

	this->currentState = state;
}

void TrafficLight::checkStatus(int redLightDuration, int yellowLightDuration, int greenLightDuration)
{
	State nextStatus;
	int durationUntilChange;

	switch (this->currentState)
	{
		case State::Red:
			nextStatus = State::RedYellow;
			durationUntilChange = redLightDuration;
			break;
		case State::RedYellow:
			nextStatus = State::Green;
			durationUntilChange = greenLightDuration * 0.2;
			break;
		case State::Green:
			nextStatus = State::Yellow;
			durationUntilChange = greenLightDuration * 0.8;
			break;
		case State::Yellow:
			nextStatus = State::Red;
			durationUntilChange = yellowLightDuration;
			break;
	}

	if ((this->currentMillis - this->startMillis) >= durationUntilChange)
	{
		this->changeState(nextStatus);
		this->startMillis = millis();
	}
}

void TrafficLight::blink(State state, int frequency, int speedInMs)
{
	if ((this->currentMillis - this->startMillis) >= speedInMs)
	{
		if (this->currentState != State::Yellow)
			this->changeState(State::Yellow);
		else
			this->changeState(State::Off);

		if (++this->timesBlinked > (frequency * 2))
		{
			this->timesBlinked = 0;
			this->isInterrupted = false;
		}

		this->startMillis = millis();
	}
}
