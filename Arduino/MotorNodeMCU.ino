#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

char* ssid = "iptime";
char* password = "asdf1324";

//Your Domain name with URL path or IP address with path
String serverName = "http://146.56.166.36:7579/Mobius";
String Name = "/cart1";

String stat = "waiting";

String jsonParse(String str, String findstr){
  int index = str.indexOf(findstr) + findstr.length() + 3;
  int index2 = str.indexOf('"', index);
  return str.substring(index, index2);
}

void sendStopSignal(){
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;  
    int httpResponseCode = 400;
    while(httpResponseCode != 201){
      http.begin(serverName + Name + "/status");
      http.addHeader("Content-Type", "application/vnd.onem2m-res+xml;ty=4");
      http.addHeader("X-M2M-RI", "adnae/1234");
      http.addHeader("X-M2M-Origin", Name);
      String httpRequestData = "";
      httpRequestData += "<m2m:cin xmlns:m2m=\"http://www.onem2m.org/xml/protocols\">\n";
      httpRequestData += "<con>stand</con>";
      httpRequestData += "</m2m:cin>";
      //Serial.println(httpRequestData);
      httpResponseCode = http.POST(httpRequestData);
      // Free resources
      http.end();
    }
  }
}

void sendCrossRoadSignal(){
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;  
    int httpResponseCode = 400;
    while(httpResponseCode != 201){
      http.begin(serverName + Name + "/status");
      http.addHeader("Content-Type", "application/vnd.onem2m-res+xml;ty=4");
      http.addHeader("X-M2M-RI", "adnae/1234");
      http.addHeader("X-M2M-Origin", Name);
      String httpRequestData = "";
      httpRequestData += "<m2m:cin xmlns:m2m=\"http://www.onem2m.org/xml/protocols\">\n";
      httpRequestData += "<con>get_route</con>";
      httpRequestData += "</m2m:cin>";
      //Serial.println(httpRequestData);
      httpResponseCode = http.POST(httpRequestData);
      // Free resources
      http.end();
    }
  }
}

void getDirection(){
  String Direction;
  int httpResponseCode = 400;
  Serial.println("getting Direction");
  if(WiFi.status() == WL_CONNECTED){
    do{
      HTTPClient http;
      http.begin(serverName + Name + "/status/la");
      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-M2M-RI","/Mobius");
      http.addHeader("X-M2M-Origin","SOrigin");
      http.GET();
      String payload = http.getString();
      stat = jsonParse(payload, "con");
      http.end();
      if(stat.equals("moving")){
        http.begin(serverName + Name + "/direction/la");
        http.addHeader("Content-Type", "application/json");
        http.addHeader("X-M2M-RI","/Mobius");
        http.addHeader("X-M2M-Origin","SOrigin");
        httpResponseCode = http.GET();
        if(httpResponseCode == 200){
          String payload = http.getString();
          Direction = jsonParse(payload, "con");
          Serial.println(Direction);
          http.end();
        }
      }
      delay(1000);
    } while(!(stat.equals("moving") && httpResponseCode == 200));
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
      if(stat.equals("moving")){
        //Serial.println("");
        Serial.println("Go");
      }
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
  if(stat.equals("moving")){
    if(Serial.available()){
      String temp = Serial.readStringUntil('\n');
      temp.trim();
      if(temp.equals("get_route")){
        sendCrossRoadSignal();
        getDirection();
      }
      if(temp.equals("stand")){
        stat = "stand";
        sendStopSignal();
      }
    }
  }
  else{
    startSignal();
    delay(1000);
  }
}
