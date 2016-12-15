#include "Arduino.h"
#include "xmas.h"
#include "ResponsiveAnalogRead.h"

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
const int ANALOG1 = A2;
const int ANALOG2 = A1;
const int ANALOG3 = A0;

ResponsiveAnalogRead analog1(ANALOG1, true);
ResponsiveAnalogRead analog2(ANALOG2, true);

int buttonReady = 1;
int mode = 0;
int MODES_TOTAL = 3;

int brightness = 0;
float x = 0;
float maxX;

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

  analog1.setSnapMultiplier(0.001);
  analog2.setSnapMultiplier(0.01);

  maxX = 6.242;
}

void Xmas::loop()
{
  if(digitalRead(BUTTON) == LOW)
  {
    if(buttonReady)
    {
      buttonReady = 0;
      mode++;
      if(mode >= MODES_TOTAL)
        mode = 0;
    }
  } else {
    buttonReady = 1;
  }

  if(mode == 0)
  {
    analogWrite(PWM1S, 0);
    analogWrite(PWM2S, 0);
    analogWrite(PWM3S, 0);
    digitalWrite(BUTTONLED, LOW);
    return;
  }

  analog1.update();
  brightness = analog1.getValue() / 4;
  digitalWrite(BUTTONLED, HIGH);

  if(mode == 1)
  {
    analogWrite(PWM1S, brightness);
    analogWrite(PWM2S, brightness);
    analogWrite(PWM3S, brightness);
  }

  analog2.update();
  
  if(mode == 2)
  {
    float v1 = (sin(x) + 1) * brightness * 0.2 + 1;
    float v2 = (sin(x + (maxX / 3)) + 1) * brightness * 0.2 + 1;
    float v3 = (sin(x - (maxX / 3)) + 1) * brightness * 0.2 + 1;
    
    analogWrite(PWM1S, v1);
    analogWrite(PWM2S, v2);
    analogWrite(PWM3S, v3);

    float dx = ((float)analog2.getValue() / 4096.0) + 0.005;

    x += dx;
    if(x >= maxX)
      x = 0.0;
  }
  
  delay(20);
}
