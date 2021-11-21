#include <SoftwareSerial.h>


int L = 4; // left sensor
int R = 3; // right sensor
int LL = 5; // most left sensor
int RR = 6; // most right sensor

int enA = A0;
int enB = A1;

int Ain1 = 8; 
int Ain2 = 9; 
int Bin1 = 10; 
int Bin2 = 11; 
// A = left, B = right
int pwm = 130;
int Delay = 10;
int Time = 0;
char ward;
void setup(){
  Serial.begin(9600);
  Serial.println("Start Receive");

  pinMode(L, INPUT);
  pinMode(LL, INPUT);
  pinMode(R, INPUT);
  pinMode(RR, INPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);

  pinMode(enA, OUTPUT); //오른쪽 모터 속도제어
  pinMode(enB, OUTPUT); //왼쪽 모터 속도제어

  
}
// L과 R은 미감지시 HIGH, 검정색 감지 시 LOW
// LL과 RR은 감지시 HIGH, 미감지시 LOW
void loop(){
  //Serial.println("L : " + L);
  //Serial.println("R : " + R);

  unsigned long Now = millis();
    
  
  Stop();
  if(Now >= Time){
    // 교차로 추가
    
    if(digitalRead(LL) == HIGH || digitalRead(RR) == HIGH){
      Stop();
      delay(1000);
      Serial.println("Cross Road Signal Waiting");
      if(digitalRead(LL) == LOW && digitalRead(RR) == HIGH){
        curveRight();
        delay(400);
      }
      else if(digitalRead(LL) == HIGH && digitalRead(RR) == LOW){
        Bleft();
        delay(400);
      }
    }
    
    // 라인트레이싱 코드
    if (digitalRead(L) == LOW && digitalRead(R) == LOW) {
      //직진
      forward();
    }
    if (digitalRead(L) == LOW && digitalRead(R) == HIGH) {
      //우회전
      Bright();
    }
    if (digitalRead(L) == HIGH && digitalRead(R) == LOW) {
      //좌회전
      Bleft();
    }
    if (digitalRead(L) == HIGH && digitalRead(R) == HIGH && digitalRead(LL) == HIGH && digitalRead(RR) == HIGH) {
      //스탑
      Stop();
    }
    if(Now >= Time+Delay){
      Time += Delay*3;
    }
  }
}

void forward() {
  Serial.println("forward");
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, pwm);   //오른쪽 모터 속도, 숫자로 속도 제어가능
  analogWrite(enB, pwm);
}

void Bright() {
  Serial.println("right");
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, pwm);

}
void Bleft() {
  Serial.println("left");
  digitalWrite(Ain1, HIGH); 
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, pwm);
  analogWrite(enB, 0);

}
void Stop() {
  Serial.println("Stop");
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);

}

void curveRight(){
  Serial.println("right");
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, pwm-50);
  analogWrite(enB, pwm);
}
