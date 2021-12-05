#include <SoftwareSerial.h>

/*
 * L = left sensor
 * R = right sensor
 * LL = Most Left sensor
 * RR = Most right sensor
 */
int L = 5;
int R = 3;
int LL = 4;
int RR = 6;

// A = left wheel, B = right wheel
int enA = A0;
int enB = A1;
int Ain1 = 8; 
int Ain2 = 9;
int Bin1 = 10; 
int Bin2 = 11;

/*
 * pwm = moter power
 * Delay, Time = Arduino Loop Delay Setting
 * TURN_DELAY = Cross Load Turn Time
 * Forward DELAY = Cross Load Forward Time
 */
int pwm = 128;
int Delay = 30;
float Speed = 0.45;
unsigned long Time = 0;
unsigned long Now = 0;
int TURN_DELAY = 1000;
int FORWARD_DELAY = 750;

/* stat = Cart stat
 * waiting : Cart is waiting for start signal from server. not yet started.
 * stand : Cart is in front of stand and waiting for start signal from server.
 * moving : Cart is moving along the line.
 * get_route : Cart is located on cross road and waiting for direction from server. 
 */
String stat = "waiting";

void get_startSignal(){
  while(1){
    String temp = Serial.readStringUntil("\n");
    //Serial.println("MCU : " + temp);
    temp.trim();
    if(temp.equals("Go")){
      stat = "moving";
      break;
    }
  }
}

void line_trace(char S){
  Time = millis();
  //Serial.println(Time);
  switch(S){
  case 'F':
    if(Time % Delay < Delay * Speed){
      forward();
    }
    else{
      Stop();
    }
    break;
    case 'R':
    if(Time % Delay < Delay * Speed){
      Bright();
    }
    else{
      Stop();
    }
    break;
  case 'L':
    if(Time % Delay < Delay * Speed){
      Bleft();
    }
    else{
      Stop();
    }
    break;
  case 'S':
    Stop();
    break;
  }
}

void forced_line_trace(int Delay){
  unsigned long t_Now = millis();
  unsigned long t_time = t_Now + (unsigned long) Delay;
  while(t_time > t_Now){
      t_Now = millis();
      if (digitalRead(L) == LOW && digitalRead(R) == LOW) {
            line_trace('F');
            //Serial.println("Loop Forward"); //debug
          }
      if (digitalRead(L) == LOW && digitalRead(R) == HIGH) {
        line_trace('R');
        //Serial.println("Loop right turn"); //debug
      }
      if (digitalRead(L) == HIGH && digitalRead(R) == LOW) {
        line_trace('L');
        //Serial.println("Loop left turn"); //debug
      }
 }
}


void forward() {
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(enA, pwm);
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

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  get_startSignal();
  
  Time = millis();
}

void loop(){

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
        Now = millis();
        while(millis() - Now < TURN_DELAY){
          line_trace('L');
        }
        break;
      }
      else if(Direction.equals("RGT")){
        Serial.println("CrossLoad right turn"); //debug
        stat = "moving";
        Now = millis();
        while(millis() - Now < TURN_DELAY){
          line_trace('R');
        }
        break;
      }
      else if(Direction.equals("STR")){
        Serial.println("CrossLoad Straight"); //debug
        stat = "moving";
        forced_line_trace(FORWARD_DELAY);
        break;
      }
    } 
  }
  
  if(stat.equals("moving")){
    Serial.println("I'm in moving");
    // Determine Cross road or Stop
    if(digitalRead(LL) == HIGH || digitalRead(RR) == HIGH){
      //forced_line_trace(500);
      Stop();
      delay(1000);
      if (digitalRead(LL) == HIGH && digitalRead(RR) == HIGH) {
        if(digitalRead(L) == HIGH && digitalRead(R) == HIGH){
          // three way
          stat = "get_route";
        }
        
        else{
          // If Most left and right sensor are activated, It is a stand
          stat = "stand";
        }
      }
      else{
        stat = "get_route";
      }
    }
    else{
      if (digitalRead(L) == LOW && digitalRead(R) == LOW) {
        line_trace('F');
        //Serial.println("Loop Forward"); //debug
      }
      if (digitalRead(L) == LOW && digitalRead(R) == HIGH) {
        line_trace('R');
        //Serial.println("Loop right turn"); //debug
      }
      if (digitalRead(L) == HIGH && digitalRead(R) == LOW) {
        line_trace('L');
        //Serial.println("Loop left turn"); //debug
      }
      if (digitalRead(L) == HIGH && digitalRead(R) == HIGH){
        Stop();
        stat = "get_route";
        //Serial.println("stand");
        //Serial.println("I'm in stop"); //debug
      }
    }
  }
  if(stat.equals("stand")){
    Serial.println("I'm in stand"); //debug
    Serial.println("stand");
    get_startSignal();
    forced_line_trace(FORWARD_DELAY);
  }
}
