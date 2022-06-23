#ifndef STEPPER_H
#define STEPPER_H
#include <Arduino.h>
enum DIRECTION {
    clockwise,
    counterClockwise
};
class Stepper {
    private:
        const int MAX_SPEED = 100;
        float mode = float(1) / 16;
        int enablePin, dirPin, stepPin, rotateSpeed;
    public:
        Stepper(int enablePin, int stepPin, int dirPin);
        int getStepPin();
        int getDirPin();
        void setMode(float mode);
        void setRotateSpeed(int rotateSpeed);
        void startup();
        void rotate(int rolation);
        void run(int numberOfCycles, int direction);
};
#endif
