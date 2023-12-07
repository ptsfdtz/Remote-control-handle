#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

RF24 radio(7, 8);
const byte address[6] = "00001";

const int buttonPins[] = {4, 5, 6, 9, 10};
const int switchPins[] = {2, 3};
const int analogPinsL[] = {A7, A6, 0, A0};
const int analogPinsR[] = {A3, A2, 1, A1};

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  for (int pin : buttonPins)
    pinMode(pin, INPUT_PULLUP);

  for (int pin : switchPins)
    pinMode(pin, INPUT_PULLUP);

  for (int pin : analogPinsL)
    pinMode(pin, INPUT);

  for (int pin : analogPinsR)
    pinMode(pin, INPUT);

  begin_cartoon();
}

void loop() {
  int state[5];
  int xValue_L, yValue_L, buttonValue_L, xValue_R, yValue_R, buttonValue_R, potValue_L, potValue_R, angle_L, angle_R;

  for (int i = 0; i < 5; ++i)
    state[i] = digitalRead(buttonPins[i]);

  xValue_L = analogRead(analogPinsL[0]);
  yValue_L = analogRead(analogPinsL[1]);
  buttonValue_L = analogRead(analogPinsL[2]);

  xValue_R = analogRead(analogPinsR[0]);
  yValue_R = analogRead(analogPinsR[1]);
  buttonValue_R = analogRead(analogPinsR[2]);

  potValue_L = analogRead(analogPinsL[3]);
  potValue_R = analogRead(analogPinsR[3]);
  angle_L = map(potValue_L, 0, 1023, 0, 360);
  angle_R = map(potValue_R, 0, 1023, 0, 360);

  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));

  if (digitalRead(switchPins[0]) == HIGH && digitalRead(switchPins[1]) == LOW)
    show_bottom(state[0], state[1], state[2], state[3], state[4]);
  else if (digitalRead(switchPins[1]) == HIGH && digitalRead(switchPins[0]) == LOW)
    show_XYB(xValue_L, yValue_L, buttonValue_L, xValue_R, yValue_R, buttonValue_R);
  else if (digitalRead(switchPins[1]) == HIGH && digitalRead(switchPins[0]) == HIGH)
    show_angle(angle_L, angle_R);
  else
    show_direction(xValue_R, yValue_R, yValue_L);
}

void show_bottom(int state1, int state2, int state3, int state4, int state5) {
  show_lcd("Bottom Selection:", (String(state1) + " " + String(state2) + " " + String(state3) + " " + String(state4) + " " + String(state5)).c_str());
}

void show_XYB(int xValue_L, int yValue_L, int buttonValue_L, int xValue_R, int yValue_R, int buttonValue_R) {
  show_lcd("X Y Bottom value:", (String(xValue_L) + " " + String(yValue_L) + " " + String(xValue_R) + " " + String(yValue_R) + " " +String(buttonValue_L) + " " + String(buttonValue_R)).c_str());
}

void show_angle(int angle_L, int angle_R) {
  show_lcd("Potent angle:", (String(angle_L) + "       " + String(angle_R)).c_str());
}

void show_direction(int xValue_R, int yValue_R, int yValue_L) {
  int speed;
  if (xValue_R > 510) {
    speed = xValue_R - 508;
    show_lcd("Direction speed", ("Forward   " + String(speed)).c_str());
  } else if (xValue_R < 506) {
    speed = 508 - xValue_R;
    show_lcd("Direction speed", ("Backward  " + String(speed)).c_str());
  } else if (yValue_R > 510) { 
    speed = yValue_R - 508;
    show_lcd("Direction speed", ("Right     " + String(speed)).c_str());
  } else if (yValue_R < 506) {
    speed = 508 - yValue_R;
    show_lcd("Direction speed", ("Left      " + String(speed)).c_str());
  } else if (yValue_L > 518) {
    speed = yValue_L - 508;
    show_lcd("Direction speed", ("Shift_R   " + String(speed)).c_str());
  } else if (yValue_L < 510) {
    speed = 508 - yValue_L;
    show_lcd("Direction speed", ("Shift_L   " + String(speed)).c_str());
  }
  delay(50);
}

void show_lcd(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(250);
}

void begin_cartoon() {
  lcd.begin();
  lcd.clear();
  for (int i = 0; i < LCD_COLUMNS; ++i) {
    lcd.setCursor(i, 0);
    lcd.print("$");
    lcd.setCursor(LCD_COLUMNS - i - 1, 1);
    lcd.print("$");
    delay(150);
  }
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("  Your Device");
}
