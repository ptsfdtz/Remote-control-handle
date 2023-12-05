const int potPin_L = A0;
const int potPin_R = A1; 
void setup() {
  Serial.begin(9600);
}

void loop() {
  int potValue_L = analogRead(potPin_L);
  int potValue_R = analogRead(potPin_R);

  int angle_L = map(potValue_L, 0, 1023, 0, 360);
  int angle_R = map(potValue_R, 0, 1023, 0, 360);

  Serial.println(angle_L);
  Serial.println(angle_R);

  delay(100);
}
