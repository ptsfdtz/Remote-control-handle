#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Motor.h"

struct ControlMessage {
  char direction[10];
  int speed;
};

int speed;
RF24 radio(7, 8);  // CE, CSN
Motor motor(22, 24, 28, 26, 30, 32, 36, 34, 2, 3, 4, 5);

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    ControlMessage receivedMessage;
    radio.read(&receivedMessage, sizeof(receivedMessage));
    Serial.print("Received Direction: ");
    Serial.print(receivedMessage.direction);
    Serial.print(", Speed: ");
    Serial.println(receivedMessage.speed);
    if (receivedMessage.speed > 500) {
      speed = 250;
    } else {
      speed = receivedMessage.speed / 2;
    }
    if (strcmp(receivedMessage.direction, "stop") == 0) {
      motor.speed(0);
      motor.stop();
      Serial.println();
    } else if (strcmp(receivedMessage.direction, "Forward") == 0) {
      motor.speed(speed);
      motor.forward();
    } else if (strcmp(receivedMessage.direction, "Backward") == 0) {
      motor.speed(speed);
      motor.backward();
    } else if (strcmp(receivedMessage.direction, "Right") == 0) {
      motor.speed(speed);
      motor.right();
    } else if (strcmp(receivedMessage.direction, "Left") == 0) {
      motor.speed(speed);
      motor.left();
    } else if (strcmp(receivedMessage.direction, "Shift_R") == 0) {
      motor.speed(speed);
      motor.horizontal_R();
    } else if (strcmp(receivedMessage.direction, "Shift_L") == 0) {
      motor.speed(speed);
      motor.horizontal_L();
    } else if (strcmp(receivedMessage.direction, "L_up") == 0) {
      motor.speed(speed);
      motor.forward();
    } else if (strcmp(receivedMessage.direction, "L_down") == 0) {
      motor.speed(speed);
      motor.backward();
    }
  }
}
