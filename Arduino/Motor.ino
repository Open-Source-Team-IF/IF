#include <SoftwareSerial.h>


int L = 4; // left sensor
int R = 3; // right sensor

int enA = A0;
int enB = A1;

int Ain1 = 8; 
int Ain2 = 9; 
int Bin1 = 10; 
int Bin2 = 11; 
// A = left, B = right

void setup(){
  Serial.begin(9600);
  Serial.println("Start Receive");
  
  pinMode(L, INPUT);
  pinMode(R, INPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);

  pinMode(enA, OUTPUT); //오른쪽 모터 속도제어
  pinMode(enB, OUTPUT); //왼쪽 모터 속도제어
}

void loop(){
 
  if (digitalRead(L) == LOW && digitalRead(R) == LOW) {
    //직진
    Serial.println("forward");
    forward();
  }
  if (digitalRead(L) == LOW && digitalRead(R) == HIGH) {
    //우회전
    Serial.println("right");
    Bright();
  }
  if (digitalRead(L) == HIGH && digitalRead(R) == LOW) {
    //좌회전
    Serial.println("left");
    Bleft();
  }

  if (digitalRead(L) == HIGH && digitalRead(R) == HIGH) {
    //스탑
    Serial.println("stop");
    Stop();
  }


}

void forward() {
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, 145);   //오른쪽 모터 속도, 숫자로 속도 제어가능
  analogWrite(enB, 145);
}

void Bright() {
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 145);

}
void Bleft() {
  digitalWrite(Ain1, HIGH); 
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, 145);
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
