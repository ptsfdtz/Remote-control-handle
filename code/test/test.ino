#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

const int buttonPins[] = {4, 5, 6, 9, 10};
const int switchPins[] = {2, 3};
const int analogPinsL[] = {A7, A6, 0, A0};
const int analogPinsR[] = {A3, A2, 1, A1};

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(9600);
  
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
  int state1 = digitalRead(buttonPins[0]);
  int state2 = digitalRead(buttonPins[1]);
  int state3 = digitalRead(buttonPins[2]);
  int state4 = digitalRead(buttonPins[3]);
  int state5 = digitalRead(buttonPins[4]);

  int xValue_L = analogRead(analogPinsL[0]);
  int yValue_L = analogRead(analogPinsL[1]);
  int buttonValue_L = analogRead(analogPinsL[2]);

  int xValue_R = analogRead(analogPinsR[0]);
  int yValue_R = analogRead(analogPinsR[1]);
  int buttonValue_R = analogRead(analogPinsR[2]);

  int potValue_L = analogRead(analogPinsL[3]);
  int potValue_R = analogRead(analogPinsR[3]);
  int angle_L = map(potValue_L, 0, 1023, 0, 360);
  int angle_R = map(potValue_R, 0, 1023, 0, 360);

  if (digitalRead(switchPins[0]) == HIGH && digitalRead(switchPins[1]) == LOW) {
    show_bottom(state1, state2, state3, state4, state5);
  } else if (digitalRead(switchPins[1]) == HIGH && digitalRead(switchPins[0]) == LOW) {
    show_XYB(xValue_L, yValue_L, buttonValue_L, xValue_R, yValue_R, buttonValue_R);
  } else if (digitalRead(switchPins[1]) == HIGH && digitalRead(switchPins[0]) == HIGH) {
    show_angle(angle_L, angle_R);
  } else {
    show_direction(xValue_R);
  }
}

void show_bottom(int state1, int state2, int state3, int state4, int state5) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mod Selection:");
  lcd.setCursor(0, 1);
  lcd.print(String(state1) + " " + String(state2) + " " + String(state3) +
            " " + String(state4) + " " + String(state5));
  delay(1000);
}

void show_XYB(int xValue_L, int yValue_L, int buttonValue_L, int xValue_R, int yValue_R, int buttonValue_R) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X Y Bottom value:");
  lcd.setCursor(0, 1);
  lcd.print(String(xValue_L) + " " + String(yValue_L) + " " + String(buttonValue_L) +
            " " + String(xValue_R) + " " + String(yValue_R) + " " + String(buttonValue_R));
  delay(1000);
}

void show_angle(int angle_L, int angle_R) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Potent angle:");
  lcd.setCursor(0, 1);
  lcd.print(String(angle_L) + "       " + String(angle_R));
  delay(1000);
}

void show_direction(int xValue_R) {
  if (xValue_R > 510) {
    int speed = xValue_R - 508;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Direction speed");
    lcd.setCursor(0, 1);
    lcd.print("Forward " + String(speed));
  }
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
