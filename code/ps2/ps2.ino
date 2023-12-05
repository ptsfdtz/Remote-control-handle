const int xPin1 = A7;
const int yPin1 = A6;
const int buttonPin1 = 0;

const int xPin2 = A3;
const int yPin2 = A2;
const int buttonPin2 = 1;

void setup() {
  Serial.begin(9600);
  pinMode(xPin1, INPUT);
  pinMode(yPin1, INPUT);
  pinMode(buttonPin1, INPUT_PULLUP); 

  pinMode(xPin2, INPUT);
  pinMode(yPin2, INPUT);
  pinMode(buttonPin2, INPUT_PULLUP);
}

void loop() {
  int xValue1 = analogRead(xPin1);
  int yValue1 = analogRead(yPin1);
  int buttonState1 = digitalRead(buttonPin1);

  int xValue2 = analogRead(xPin2);
  int yValue2 = analogRead(yPin2);
  int buttonState2 = digitalRead(buttonPin2);

  Serial.print(xPin1);
  Serial.print(" ");
  Serial.print(yPin1);
  Serial.print(" ");
  Serial.print(buttonPin1);
  Serial.print(" ");
  Serial.print(xPin2);
  Serial.print(" ");
  Serial.print(yPin2);
  Serial.print(" ");
  Serial.println(buttonPin2);
  delay(100); 
}
