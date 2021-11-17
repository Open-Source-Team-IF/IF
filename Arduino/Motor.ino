#include <SoftwareSerial.h>


int L = 4; // left sensor
int R = 3; // right sensor
int LL = 5; // Most Left Sensor
int RR = 6; // Most Right Sensor

int enA = A0;
int enB = A1;

int Ain1 = 9; 
int Ain2 = 8; 
int Bin1 = 10; 
int Bin2 = 11; 
// A = left, B = right

char Cross_signal = 'R' // should remove it.

void setup(){
  Serial.begin(9600);
  Serial.println("Start Receive");
  
  pinMode(L, INPUT);
  pinMode(R, INPUT);
  pinMode(LL, INPUT);
  pinMode(RR, INPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);

  pinMode(enA, OUTPUT); //오른쪽 모터 속도제어
  pinMode(enB, OUTPUT); //왼쪽 모터 속도제어
}

void loop(){
  // 감지되면 HIGH 일걸 ... ?
  
  if (digitalRead(LL) == HIGH || digitalRead(RR) == HIGH){
      Serial.println("Cross road Stop")
      Stop();
      if(digitalRead(LL) == HIGH && digitalRead(RR) == HIGH){
        Stop();
      }
      else{
        // Cross_signal = get_signal(); not implement
        if(Cross_signal == 'L'){ // get left signal from server
          while(digitalRead(L) == HIGH && digitalRead(R) == LOW){
            Serial.println("left");
            Bleft();
          }
        }
        else if (Cross_signal == 'R'){ // get right signal from server
          while(digitalRead(L) == LOW && digitalRead(R) == HIGH){
            Serial.println("right");
            Bright();
          }
        }
      }
  }
  if (digitalRead(L) == LOW && digitalRead(R) == LOW) {
    //직진
    Serial.println("forward");
    forward();
  }
  if (digitalRead(L) == LOW && digitalRead(R) == HIGH) {
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
  analogWrite(enA, 50);   //오른쪽 모터 속도, 숫자로 속도 제어가능
  analogWrite(enB, 50);
}

void Bright() {
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 50);

}
void Bleft() {
  digitalWrite(Ain1, HIGH); 
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, 50);
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
