#include "Motor.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define pressures true
#define rumble true

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Motor motor(22, 24, 28, 26, 30, 32, 36, 34, 2, 3, 4, 5);

int speedPinA = 8;
int speedPinB = 9;

int error = 0;
byte type = 0;
byte vibrate = 0;
int servoMin = 10;
int servoMax = 500;
int begin1 = 250;
int begin2 = 250;
int begin3 = 80;
int begin4 = 280;

void setup()
{
  motor.speed(100);
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
  servos_begin();
}

void loop()
{
}

void servos_begin()
{
  pwm.setPWM(0, 0, begin1);
  pwm.setPWM(1, 0, begin2);
}