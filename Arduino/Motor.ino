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
int TURN_DELAY = 400;

String stat = "waiting";

void get_startSignal(){
  while(1){
    String temp = Serial.readStringUntil("\n");
    temp.trim();
    //Serial.println("temp" + temp); //debug
    if(temp.equals("Go")){
      stat = "moving";
      break;
    }
  }
}

void forward() {
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, pwm);   //오른쪽 모터 속도, 숫자로 속도 제어가능
  analogWrite(enB, pwm);
}

void Bright() {
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, pwm);

}
void Bleft() {
  digitalWrite(Ain1, HIGH); 
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, pwm);
  analogWrite(enB, 0);

}
void Stop() {
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);   
  analogWrite(enA, 0);
  analogWrite(enB, 0);

}

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

  get_startSignal();
}

void loop(){
  unsigned long Now = millis();
  // cross = 교차로 도달, moving = 라인 트레이싱, stand = 멈춤 : 세 가지 상태에 따른 동작 구현
  if(stat.equals("get_route")){
    Stop();
    Serial.println("I'm in Cross"); //debug
    Serial.println("get_route"); 
    String Direction = "CrossWaiting"; // init
    while(1){
      Direction = Serial.readStringUntil('\n');
      Direction.trim();
      if(Direction.equals("LFT")){
        Serial.println("CrossLoad Left turn"); //debug
        stat = "moving";
        Bleft();
        delay(TURN_DELAY);
        break;
      }
      else if(Direction.equals("RGT")){
        Serial.println("CrossLoad right turn"); //debug
        stat = "moving";
        Bright();
        delay(TURN_DELAY);
        break;
      }
      else if(Direction.equals("STR")){
        Serial.println("CrossLoad Straight"); //debug
        stat = "moving";
        forward();
        delay(100);
        break;
      }
    } 
  }
  if(stat.equals("moving")){
    Serial.println("I'm in moving");
    // 스탑 또는 교차로 판단
    if(digitalRead(LL) == HIGH || digitalRead(RR) == HIGH){
      Stop();
      if (digitalRead(LL) == HIGH && digitalRead(RR) == HIGH) {
        stat = "stand";
        Serial.println("Stop Mark"); // 가장 왼쪽/오른쪽 센서 동시에 활성화 시 진열대로 간주하고 스탑으로 인식 //debug
      }
      else{
      // 가장 왼쪽 또는 오른쪽 센서 활성화 시 교차로로 인식 
        stat = "get_route";
      }
    }  
    // 라인트레이싱 코드
    if (digitalRead(L) == LOW && digitalRead(R) == LOW) {
      //직진
      forward();
      Serial.println("Loop Forward"); //debug
    }
    if (digitalRead(L) == LOW && digitalRead(R) == HIGH) {
      //우회전
      Bright();
      Serial.println("Loop right turn"); //debug
    }
    if (digitalRead(L) == HIGH && digitalRead(R) == LOW) {
      //좌회전
      Bleft();
      Serial.println("Loop left turn"); //debug
    }
    if (digitalRead(L) == HIGH && digitalRead(R) == HIGH){
      // 중앙 두 센서만 활성화 시 완전 가동 중지
      Stop();
      stat = "stop";
    }
  }
  if(stat.equals("stand")){
    Serial.println("I'm in stand"); //debug
    Serial.println("stand");
    get_startSignal();
  }
}
