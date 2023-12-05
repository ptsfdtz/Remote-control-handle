const int buttonPin1 = 4;
const int buttonPin2 = 5;
const int buttonPin3 = 6;
const int buttonPin4 = 9;
const int buttonPin5 = 10;

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
}

void loop() { 
  // 读取按钮状态
  int state1 = digitalRead(buttonPin1);
  int state2 = digitalRead(buttonPin2);
  int state3 = digitalRead(buttonPin3);
  int state4 = digitalRead(buttonPin4);
  int state5 = digitalRead(buttonPin5);

  // 输出按钮状态到串口
  Serial.print("Button 1: ");
  Serial.println(state1);
  Serial.print("Button 2: ");
  Serial.println(state2);
  Serial.print("Button 3: ");
  Serial.println(state3);
  Serial.print("Button 4: ");
  Serial.println(state4);
  Serial.print("Button 5: ");
  Serial.println(state5);

  // 可选：添加适当的延迟，以避免过于频繁的检测
  delay(1000);
}
