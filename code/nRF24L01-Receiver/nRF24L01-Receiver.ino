#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Motor.h"
#include <Adafruit_PWMServoDriver.h>
#include "FastLED.h" 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int begin1 = 0;
int begin2 = 0;

struct ControlMessage {
  int xValue_R;
  int yValue_R;
  int xValue_L;
  int yValue_L;
  int speed;
};

int speed;
RF24 radio(7, 8);  // CE, CSN
Motor motor(22, 24, 28, 26, 30, 32, 36, 34, 2, 3, 4, 5);

const byte address[6] = "00001";
unsigned long lastReceiveTime = 0;
const unsigned long timeoutPeriod = 1000;  // Set your desired timeout period in milliseconds

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pwm.begin();
  pwm.setPWMFreq(50);
  servos_begin();
}

void loop() {
  if (radio.available()) {
    ControlMessage receivedMessage;
    radio.read(&receivedMessage, sizeof(receivedMessage));
    lastReceiveTime = millis();  // Update last receive time

    Serial.print("Received XR Value: ");
    Serial.print(receivedMessage.xValue_R);
    Serial.print(", YR Value: ");
    Serial.print(receivedMessage.yValue_R);
    Serial.print(", XL Value: ");
    Serial.print(receivedMessage.xValue_L);
    Serial.print(", YL Value: ");
    Serial.print(receivedMessage.yValue_L);
    Serial.print(", Speed: ");
    Serial.println(receivedMessage.speed);

    if (receivedMessage.speed > 500) {
      speed = 250;
    } else {
      speed = receivedMessage.speed / 2;
    }

    if (receivedMessage.xValue_R > 550) {
      motor.speed(speed);
      motor.forward();
    } else if (receivedMessage.xValue_R < 480) {
      motor.speed(speed);
      motor.backward();
    } else if (receivedMessage.yValue_R > 550) {
      motor.speed(speed);
      motor.horizontal_R();
    } else if (receivedMessage.yValue_R < 480) {
      motor.speed(speed);
      motor.horizontal_L();
    } else {
      motor.speed(0);
      motor.stop();
    }

    if (receivedMessage.xValue_L > 550) {
      
    } else if (receivedMessage.xValue_L < 480) {

    } else if (receivedMessage.yValue_L > 530) {
      motor.speed(speed);
      motor.right();
    } else if (receivedMessage.yValue_L < 500) {
      motor.speed(speed);
      motor.left();
    } 
  }

  if (millis() - lastReceiveTime > timeoutPeriod) {
    motor.speed(0);
    motor.stop();
  }
}

void servos_begin()
{
  pwm.setPWM(0, 0, begin1);
  pwm.setPWM(1, 0, begin2);
}