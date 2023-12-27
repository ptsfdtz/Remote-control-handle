#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Motor.h"
#include <Servo.h>
Servo servo1;  // 创建一个Servo对象来控制第一个舵机
Servo servo2;  // 创建一个Servo对象来控制第二个舵机
struct ControlMessage {
  int xValue_R;
  int yValue_R;
  int xValue_L;
  int yValue_L;
  int speed;
  int angle_L;
  int angle_R;
};
int angle1;
int angle2;
int speed;
RF24 radio(7, 8);  // CE, CSN
Motor motor(22, 24, 28, 26, 30, 32, 36, 34, 2, 3, 4, 5);

const byte address[6] = "00001";
unsigned long lastReceiveTime = 0;
const unsigned long timeoutPeriod = 1000;  // Set your desired timeout period in milliseconds

void setup() {
  Serial.begin(9600);
  servo1.attach(9);
  servo2.attach(10);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  servo_begin();
}

void loop() {
  if (radio.available()) {
    ControlMessage receivedMessage;
    radio.read(&receivedMessage, sizeof(receivedMessage));
    lastReceiveTime = millis();  // Update last receive time
    servo1.write(receivedMessage.angle_L);
    servo2.write(receivedMessage.angle_R);
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
      motor.horizontal_L();
    } else if (receivedMessage.yValue_R < 480) {
      motor.speed(speed);
      motor.horizontal_R();
    } else {
      motor.speed(0);
      motor.stop();
    }

    if (receivedMessage.xValue_L > 550) {
      
    } else if (receivedMessage.xValue_L < 480) {

    } else if (receivedMessage.yValue_L > 530) {
      motor.speed(speed/2);
      motor.right();
    } else if (receivedMessage.yValue_L < 500) {
      motor.speed(speed/2);
      motor.left();
    } 
  }

  if (millis() - lastReceiveTime > timeoutPeriod) {
    motor.speed(0);
    motor.stop();
  }
}

void servo_begin(){
  servo1.write(0);
  servo2.write(0);
}