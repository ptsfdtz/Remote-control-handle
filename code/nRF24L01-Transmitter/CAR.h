#include "Motor.h"
#include <PS2X_lib.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define PS2_DAT 13
#define PS2_CMD 11
#define PS2_SEL 10
#define PS2_CLK 12
#define pressures true
#define rumble true

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Motor motor(22, 24, 28, 26, 30, 32, 36, 34, 2, 3, 4, 5);

int speedPinA = 8;
int speedPinB = 9;

PS2X ps2x;

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
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  pwm.begin();
  pwm.setPWMFreq(50);
  servos_begin();
}

void loop()
{
  if (error == 1)
    return;

  if (type == 2)
  {
    return;
  }
  else
  {
    ps2x.read_gamepad(false, vibrate);

    byte LY = ps2x.Analog(PSS_LY);
    byte LX = ps2x.Analog(PSS_LX);
    byte RY = ps2x.Analog(PSS_RY);
    byte RX = ps2x.Analog(PSS_RX);

    if (LY < 110)
    {
      motor.speed(250 - LY);
      motor.forward();
      delay(50);
    }

    if (LY > 140)
    {
      motor.speed(LY - 10);
      motor.backward();
      delay(50);
    }

    if (LX < 110)
    {
      motor.speed(255);
      motor.left();
      delay(50);
    }

    if (LX > 140)
    {
      motor.speed(255);
      motor.right();
      delay(50);
    }

    if (LY >= 110 && LY <= 140 && LX >= 110 && LX <= 140)
    {
      motor.stop();
      delay(50);
    }

    if (RY < 110)
    {
      begin1 = begin1 - 5;
      pwm.setPWM(0, 0, begin1);
      if (begin1 < 76)
      {
        begin1 = 75;
      }
    }

    if (RY > 140)
    {
      begin1 = begin1 + 5;
      pwm.setPWM(0, 0, begin1);
      if (begin1 > 451)
      {
        begin1 = 450;
      }
    }

    if (RX < 110)
    {
      begin2 = begin2 + 5;
      pwm.setPWM(1, 0, begin2);
      if (begin2 > 421)
      {
        begin2 = 420;
      }
    }

    if (RX > 140)
    {
      begin2 = begin2 - 5;
      pwm.setPWM(1, 0, begin2);
      if (begin2 < 101)
      {
        begin2 = 100;
      }
    }

    if (ps2x.Button(PSB_L2))
    {
      begin3 = begin3 + 5;
      pwm.setPWM(2, 0, begin3);
      if (begin3 > 351)
      {
        begin3 = 350;
      }
    }

    if (ps2x.Button(PSB_R2))
    {
      begin3 = begin3 - 5;
      pwm.setPWM(2, 0, begin3);
      if (begin3 < 81)
      {
        begin3 = 75;
      }
    }

    if (ps2x.Button(PSB_L1))
    {
      begin4 = begin4 + 5;
      pwm.setPWM(3, 0, begin4);
      if (begin4 > 405)
      {
        begin4 = 405;
      }
    }

    if (ps2x.Button(PSB_R1))
    {
      begin4 = begin4 - 5;
      pwm.setPWM(3, 0, begin4);
      Serial.print(begin4);
      if (begin4 < 245) // 限位
      {
        begin4 = 245;
      }
    }
  }
}

void servos_begin()
{
  pwm.setPWM(0, 0, begin1);
  pwm.setPWM(1, 0, begin2);
  pwm.setPWM(2, 0, begin3);
  pwm.setPWM(3, 0, begin4);
}