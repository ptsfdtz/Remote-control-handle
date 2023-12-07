class Motor {
private:
  int L1_IN1;
  int L1_IN2;
  int R1_IN1;
  int R1_IN2;
  int L2_IN1;
  int L2_IN2;
  int R2_IN1;
  int R2_IN2;
  int M1_Speed;
  int M2_Speed;
  int M3_Speed;
  int M4_Speed;

public:
  Motor(int l1_in1, int l1_in2, int r1_in1, int r1_in2, int l2_in1, int l2_in2, int r2_in1, int r2_in2, int m1_speed, int m2_speed, int m3_speed, int m4_speed) {
    L1_IN1 = l1_in1;
    L1_IN2 = l1_in2;
    R1_IN1 = r1_in1;
    R1_IN2 = r1_in2;
    L2_IN1 = l2_in1;
    L2_IN2 = l2_in2;
    R2_IN1 = r2_in1;
    R2_IN2 = r2_in2;
    M1_Speed = m1_speed;
    M2_Speed = m2_speed;
    M3_Speed = m3_speed;
    M4_Speed = m4_speed;
    pinMode(L1_IN1, OUTPUT);
    pinMode(L1_IN2, OUTPUT);
    pinMode(R1_IN1, OUTPUT);
    pinMode(R1_IN2, OUTPUT);
    pinMode(L2_IN1, OUTPUT);
    pinMode(L2_IN2, OUTPUT);
    pinMode(R2_IN1, OUTPUT);
    pinMode(R2_IN2, OUTPUT);
    pinMode(M1_Speed, OUTPUT);
    pinMode(M2_Speed, OUTPUT);
    pinMode(M3_Speed, OUTPUT);
    pinMode(M4_Speed, OUTPUT);
  }

  void speed(int speed) {
    analogWrite(M1_Speed, speed);  //控制电机的速度，不同的车模，代码执行效果不同！
    analogWrite(M2_Speed, speed);  //控制电机的速度，不同的车模，代码执行效果不同！
    analogWrite(M3_Speed, speed);  //控制电机的速度，不同的车模，代码执行效果不同！
    analogWrite(M4_Speed, speed);  //控制电机的速度，不同的车模，代码执行效果不同！
  }

  void stop() {
    digitalWrite(L1_IN1, LOW);
    digitalWrite(L1_IN2, LOW);
    digitalWrite(R1_IN1, LOW);
    digitalWrite(R1_IN2, LOW);
    digitalWrite(L2_IN1, LOW);
    digitalWrite(L2_IN2, LOW);
    digitalWrite(R2_IN1, LOW);
    digitalWrite(R2_IN2, LOW);
  }

  void backward() {
    digitalWrite(L1_IN1, HIGH);
    digitalWrite(L1_IN2, LOW);
    digitalWrite(R1_IN1, HIGH);
    digitalWrite(R1_IN2, LOW);
    digitalWrite(L2_IN1, HIGH);
    digitalWrite(L2_IN2, LOW);
    digitalWrite(R2_IN1, HIGH);
    digitalWrite(R2_IN2, LOW);
  }

  void forward() {
    digitalWrite(L1_IN1, LOW);
    digitalWrite(L1_IN2, HIGH);
    digitalWrite(R1_IN1, LOW);
    digitalWrite(R1_IN2, HIGH);
    digitalWrite(L2_IN1, LOW);
    digitalWrite(L2_IN2, HIGH);
    digitalWrite(R2_IN1, LOW);
    digitalWrite(R2_IN2, HIGH);
  }

  void right() {
    digitalWrite(L1_IN1, LOW);
    digitalWrite(L1_IN2, HIGH);
    digitalWrite(R1_IN1, HIGH);
    digitalWrite(R1_IN2, LOW);
    digitalWrite(L2_IN1, LOW);
    digitalWrite(L2_IN2, HIGH);
    digitalWrite(R2_IN1, HIGH);
    digitalWrite(R2_IN2, LOW);
  }
  
  void left() {
    digitalWrite(L1_IN1, HIGH);
    digitalWrite(L1_IN2, LOW);
    digitalWrite(R1_IN1, LOW);
    digitalWrite(R1_IN2, HIGH);
    digitalWrite(L2_IN1, HIGH);
    digitalWrite(L2_IN2, LOW);
    digitalWrite(R2_IN1, LOW);
    digitalWrite(R2_IN2, HIGH);
  }

  void horizontal_L() {
    digitalWrite(L1_IN1, LOW);
    digitalWrite(L1_IN2, HIGH);
    digitalWrite(R1_IN1, HIGH);
    digitalWrite(R1_IN2, LOW);
    digitalWrite(L2_IN1, HIGH);
    digitalWrite(L2_IN2, LOW);
    digitalWrite(R2_IN1, LOW);
    digitalWrite(R2_IN2, HIGH);
  }

  void horizontal_R() {
    digitalWrite(L1_IN1, HIGH);
    digitalWrite(L1_IN2, LOW);
    digitalWrite(R1_IN1, LOW);
    digitalWrite(R1_IN2, HIGH);
    digitalWrite(L2_IN1, LOW);
    digitalWrite(L2_IN2, HIGH);
    digitalWrite(R2_IN1, HIGH);
    digitalWrite(R2_IN2, LOW);
  }
};