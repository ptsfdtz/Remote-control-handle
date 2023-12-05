const int encoderPinA = 2;
const int encoderPinB = 3;

volatile long encoderPosition = 0;

void setup() {
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);
  Serial.begin(9600);
}

void loop() {
  long newPosition = encoderPosition;
  if (newPosition != encoderPosition) {
    Serial.println(newPosition);
    encoderPosition = newPosition;
  }
}

void updateEncoder() {
  static byte encoder_A_prev = 0;

  byte encoder_A = digitalRead(encoderPinA);
  byte encoder_B = digitalRead(encoderPinB);

  if ((encoder_A == HIGH) && (encoder_A_prev == LOW)) {
    if (encoder_B == LOW) {
      encoderPosition++;
    } else {
      encoderPosition--;
    }
  }

  encoder_A_prev = encoder_A;
}
