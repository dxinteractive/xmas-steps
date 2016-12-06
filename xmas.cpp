#include "Arduino.h"
#include "xmas.h"

// pwm pins
const int PWM1S = 3;
const int PWM2S = 5;
const int PWM3S = 6;

// sort out these later, not used yet
//const int PWM1R = 9;
//const int PWM2R = 10;
//const int PWM3R = 11;

// button
const int BUTTON = A3;
const int BUTTONLED = 11;

// analog inputs
const int ANALOG1 = A0;
const int ANALOG2 = A1;
const int ANALOG3 = A2;

int woo = 0;

void Xmas::setup()
{
  Serial.begin(9600);
  pinMode(PWM1S, OUTPUT);
  pinMode(PWM2S, OUTPUT);
  pinMode(PWM3S, OUTPUT);
  //pinMode(PWM1R, OUTPUT);
  //pinMode(PWM2R, OUTPUT);
  pinMode(ANALOG1, INPUT);
  //pinMode(PWM3R, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUTTONLED, OUTPUT);
  pinMode(ANALOG2, INPUT);
  pinMode(ANALOG3, INPUT);
}

void Xmas::loop()
{
  analogWrite(PWM1S, 0);
  delay(50);
  //digitalWrite(BUTTONLED, HIGH);

}
