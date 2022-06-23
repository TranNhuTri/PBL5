#include "stepper.h"

Stepper::Stepper(int enablePin, int stepPin, int dirPin) {
    this->dirPin = dirPin;
    this->stepPin = stepPin;
    this->enablePin = enablePin;
    this->rotateSpeed = this->MAX_SPEED;

    pinMode(this->enablePin, OUTPUT);
    pinMode(this->dirPin, OUTPUT);
    pinMode(this->stepPin, OUTPUT);

    digitalWrite(this->enablePin, HIGH);
}

int Stepper::getStepPin() {
  return this->stepPin;
}

int Stepper::getDirPin() {
  return this->dirPin;
}

void Stepper::setMode(float mode)  {
    this->mode = mode;
}

void Stepper::setRotateSpeed(int rotateSpeed) {
    this->rotateSpeed = rotateSpeed;
}

void Stepper::rotate(int rolation) {
    int direct = clockwise;
    if(rolation < 0) {
      direct = counterClockwise;
    }
    
    int numberOfCycles = abs(rolation) / 1.8 / this->mode;
    this->run(numberOfCycles, direct);
}

void Stepper::startup() {
  digitalWrite(this->enablePin, LOW);
}

void Stepper::run(int numberOfCycles, int direct) {
    switch (direct)
    {
        case clockwise:
            digitalWrite(this->dirPin, HIGH);
            break;
        case counterClockwise:
            digitalWrite(this->dirPin, LOW);
            break;
        
        default:
            break;
    }
    delay(50);

    for(int i = 0; i < numberOfCycles; i++) {
        digitalWrite(this->stepPin, HIGH);
        delayMicroseconds(this->rotateSpeed);
        digitalWrite(this->stepPin, LOW);
        delayMicroseconds(this->rotateSpeed);
    }
}
