#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

const int buttonPin1 = 4;
const int buttonPin2 = 5;
const int buttonPin3 = 6;
const int buttonPin4 = 9;
const int buttonPin5 = 10;
const int switchPin1 = 2;
const int switchPin2 = 3;

const int xPin_L = A7;
const int yPin_L = A6;
const int buttonPin_L = 0;
const int xPin_R = A3;
const int yPin_R = A2;
const int buttonPin_R = 1;

const int potPin_L = A0;
const int potPin_R = A1; 

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);

  pinMode(switchPin1, INPUT);  
  pinMode(switchPin2, INPUT);

  pinMode(xPin_L, INPUT);
  pinMode(yPin_L, INPUT);
  pinMode(buttonPin_L, INPUT_PULLUP);

  pinMode(xPin_R, INPUT);
  pinMode(yPin_R, INPUT);
  pinMode(buttonPin_R, INPUT_PULLUP);

  begin_cartoon();
}

void loop() {
  int state1 = digitalRead(buttonPin1);
  int state2 = digitalRead(buttonPin2);
  int state3 = digitalRead(buttonPin3);
  int state4 = digitalRead(buttonPin4);
  int state5 = digitalRead(buttonPin5);

  int xValue_L = analogRead(xPin_L);
  int yValue_l = analogRead(yPin_L);
  int buttonValue_L = analogRead(buttonPin_L);

  int xValue_R = analogRead(xPin_R);
  int yValue_R = analogRead(yPin_R);
  int buttonValue_R = analogRead(buttonPin_R);

  int potValue_L = analogRead(potPin_L);
  int potValue_R = analogRead(potPin_R);
  int angle_L = map(potValue_L, 0, 1023, 0, 360);
  int angle_R = map(potValue_R, 0, 1023, 0, 360);

  if (digitalRead(switchPin1) == HIGH && digitalRead(switchPin2) == LOW) {
    show_bottom(state1, state2, state3, state4, state5);
    }

  if (digitalRead(switchPin2) == HIGH && digitalRead(switchPin1) == LOW) {
    show_XYB( xValue_L, yValue_l, buttonValue_L, xValue_R, yValue_R, buttonValue_R);
    }

  if (digitalRead(switchPin2) == HIGH && digitalRead(switchPin1) == HIGH){
      show_angle(angle_L,angle_R);
    }
  if (digitalRead(switchPin1) == LOW && digitalRead(switchPin2) == LOW){
      show_direction();
  }
}

void show_bottom(int state1, int state2, int state3, int state4, int state5) {
  if (state1 == 0 || state2 == 0 || state3 == 0 || state4 == 0 || state5 == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mod Selection:");
    lcd.setCursor(0, 1);
    lcd.print(String(state1) + " " + String(state2) + " " + String(state3) +
              " " + String(state4) + " " + String(state5));
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mod Selection:");
    lcd.setCursor(0, 1);
    lcd.print("No button pressed");
  }
  delay(1000);
}

void show_XYB(int xValue_L, int yValue_l, int buttonValue_L, int xValue_R, int yValue_R,int buttonValue_R){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X Y Bottom value:");
  lcd.setCursor(0, 1);
  lcd.print(String(xValue_L) + " " + String(yValue_l) + " " + String(buttonValue_L) +
              " " + String(xValue_R) + " " + String(yValue_R)+ " " + String(buttonValue_R));
  delay(1000);
}

void show_angle(int angle_L, int angle_R){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("potent angle:");
  lcd.setCursor(0, 1);
  lcd.print(String(angle_L) + "       " + String(angle_R));
  delay(1000);
}

void show_direction(){
  int xValue_R;
  if(xValue_R>510){
    int speed = xValue_R - 508;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("direction speed");
    lcd.setCursor(0, 1);
    lcd.print("forward"+String(speed));
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
