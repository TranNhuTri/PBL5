#include "stepper.h"

Stepper Right(16, 15, 14), Left(3, 4, 5), Front(6, 7, 8), Back(9, 10, 11), RightLeft(51, 52, 53), FrontBack(47, 48, 49);
#define delta 6 * 180

enum AXIS {
    RL,
    FB
};

void rotateAxis(int type, int rolation)
{
  int stepPinA, stepPinB, dirPinA, dirPinB;
  Stepper *p;
  switch(type) {
    case RL:
        p = &RightLeft;
        stepPinA = Right.getStepPin();
        stepPinB = Left.getStepPin();

        dirPinA = Right.getDirPin();
        dirPinB = Left.getDirPin();
        break;
    case FB:
        p = &FrontBack;
        stepPinA = Front.getStepPin();
        stepPinB = Back.getStepPin();

        dirPinA = Front.getDirPin();
        dirPinB = Back.getDirPin();
        break;
    
    default:
        break;
  }
  p->rotate(-delta);
  delay(100);
  if(rolation < 0) {
    digitalWrite(dirPinA, LOW);
    digitalWrite(dirPinB, HIGH);
  }
  else {
    digitalWrite(dirPinA, HIGH);
    digitalWrite(dirPinB, LOW);
  }
  for(int i = 0; i < abs(rolation) / 1.8 * 16; i++) {
      digitalWrite(stepPinA, HIGH);
      digitalWrite(stepPinB, HIGH);
      delayMicroseconds(300);
      digitalWrite(stepPinA, LOW);
      digitalWrite(stepPinB, LOW);
      delayMicroseconds(300);
  }
  delay(200);
  p->rotate(delta);
}

void rotateMotor(char direct, int rolation) {
  int dirPin, stepperPin;
  switch(direct) {
    case 'R': {
      Right.rotate(rolation);
      break;
    }
    case 'L': {
      Left.rotate(rolation);
      break;
    }
    case 'F': {
      Front.rotate(rolation);
      break;
    }
    case 'B': {
      Back.rotate(rolation);
      break;
    }
    case 'U': {
      rotateAxis(RL, 90);
      
      delay(100);
      Front.rotate(-1*rolation);
      delay(100);

      rotateAxis(RL, -90);
      delay(100);
      break;
    }
    case 'D': {
      rotateAxis(RL, -90);
      
      delay(100);
      Front.rotate(rolation);
      delay(100);

      rotateAxis(RL, 90);
      delay(100);
      break;
    }
    default: {
      return;
    }
  }
}

void solve(String s)
{
  char direct;
  bool isClockwise = true, isNewStep = true;
  int times = 1;
  for(int i = 0; i < s.length(); i++)
  {
    if(isNewStep)
    {
      direct = s[i];
      isNewStep = false;
      continue;
    }
    if(s[i] != ' ')
    {
      if(s[i] > '1' && s[i] <= '9')
      {
        times = int(s[i]) - 48;
      }
      else
      {
        isClockwise = false;
      }
      continue;
    }
    else
    {
//      for(int j = 0; j < times; j++)
//      {
        int rolation = -90;
        if(isClockwise)
          rolation = 90;
        rotateMotor(direct, times * rolation);
//        delay(100);
//      }
      delay(100);
      isNewStep = true;
      times = 1;
      isClockwise = true;
    }
  }
}

void setup()
{
  Serial.begin(9600);
  delay(5000);
  RightLeft.startup();
  RightLeft.setRotateSpeed(60);
  FrontBack.startup();
  FrontBack.setRotateSpeed(60);
  Right.startup();
  delay(100);
  Left.startup();
  delay(100);
  Front.startup();
  delay(100);
  Back.startup();
  delay(100);
}

void loop()
{
//  solve("L2 F2 R' L F D2 F B' U2 F L U' F2 R' U' L D2 F R L2 ");
//  delay(5000);
//  solve("L'2 R' F' D'2 L' U R F'2 U L' F' U'2 B F' D'2 F' L' R F'2 L'2 ");
//  delay(5000);
//  solve("B2 B'2 ");
//  solve("R2 R'2 B2 B'2 L2 L'2 ");
//    testRotate(90);
//    delay(1000);
//    testRotate(-90);
//    delay(1000);
//  solve("D'2 ");
//  delay(1000);
//  rotateAxis(RL, 90);
//  delay(500);
//  rotateAxis(RL, -90);
//  delay(500);
//  rotateAxis(FB, 90);
//  delay(500);
//  rotateAxis(FB, -90);
//  delay(500);
  String data;
  data = Serial.readString();
  Serial.println(data);
  if(data == "") {
    return;
  }
  if(data == "DF" || data == "DU" || data == "DB" || data == "DD") {
    Serial.println("case 1");
    rotateAxis(RL, 90);
    return;
  }
  if(data == "DR") {
    rotateAxis(FB, 90);
    return;
  }
  if(data == "DL") {
    rotateAxis(FB, -180);
    return;
  }
  rotateAxis(FB, 90);
  solve(data);
}
