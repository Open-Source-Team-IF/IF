#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

char* ssid = "SF_LOW";
char* password = "t1v0r20!^";

//Your Domain name with URL path or IP address with path
String serverName = "http://146.56.166.36:7579/Mobius";
String Name = "/cart1";

unsigned long lastTime = 0;

unsigned long timerDelay = 5000;

unsigned long Next_Setted_Time = 0;

String stat = "waiting";

String jsonParse(String str, String findstr){
  int index = str.indexOf(findstr) + findstr.length() + 3;
  int index2 = str.indexOf('"', index);
  return str.substring(index, index2);
}


void getDirection(){
  String Direction;
  Serial.println("getting Direction");
  if(WiFi.status() == WL_CONNECTED){
    while(1){
      HTTPClient http;
      http.begin(serverName + Name + "/direction/la");
      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-M2M-RI","/Mobius");
      http.addHeader("X-M2M-Origin","SOrigin");
      int httpResponseCode = http.GET();
      if(httpResponseCode == 200){
        String payload = http.getString();
        Direction = jsonParse(payload, "con");
        if(Direction.equals("LFT") || Direction.equals("RGT") || Direction.equals("STR")){
          Serial.println(Direction);
          http.end();
          break;
        }
      }
      else{
        Serial.println("Response Code is not 200 !!");
      }
     http.end();
    }
  }
}

int startSignal(){
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(serverName + Name + "/status/la");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-M2M-RI","/Mobius");
    http.addHeader("X-M2M-Origin","SOrigin");
    int httpResponseCode = http.GET();
    if(httpResponseCode == 200){
      String payload = http.getString();
      stat = jsonParse(payload, "con");
      if(stat.equals("moving"))
        Serial.println("Go");
    }
    else{
      Serial.println("Response Code is not 200 !!");
    }
    http.end();
  }   

  
}

void setup() {
  Serial.begin(9600); 

  WiFi.begin(ssid, password);
  //Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  /* debug
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  */
}

void loop() {
      if(stat == "moving"){
        if(Serial.available()){
          String temp = Serial.readStringUntil('\n');
          temp.trim();
          if(temp.equals("CrossRoad")) getDirection();
          if(temp.equals("Stop")) stat = "stop";
          }
        }
      }
      else{
        startSignal();
        delay(1000);
      }
}
