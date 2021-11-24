#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

char* ssid = "SF_LOW";
char* password = "t1v0r20!^";
String serverName = "http://146.56.166.36:7579/Mobius";
String Name = "stand1";

String jsonParse(String str, String findstr){
  int index = str.indexOf(findstr) + findstr.length() + 3;
  int index2 = str.indexOf('"', index);
  return str.substring(index, index2);
}

String jsonParse2(String str, String findstr){
  int index = str.indexOf(findstr) + findstr.length() + 5;
  int index2 = str.indexOf('\'', index);
  return str.substring(index, index2);
}

String sub_get_state(){
  String state;
  
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(serverName + "/stand1" + "/rail/la");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-M2M-RI","/Mobius");
    http.addHeader("X-M2M-Origin","SOrigin");
    int httpResponseCode = http.GET();
    if(httpResponseCode == 200){
      // Serial.println(payload); debug용 
      String payload = http.getString();
      state = jsonParse2(jsonParse(payload, "con"), "state"); 
    }
    else{
      Serial.println("Response Code is not 200 !!");
    } 
    http.end();
  }

  //Serial.print("[Debug] Setted state : ");
  //Serial.println(state);
  
  return state;
}

int sub_get_quantity(){
  int quantity;
  
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(serverName + "/stand1" + "/rail/la");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-M2M-RI","/Mobius");
    http.addHeader("X-M2M-Origin","SOrigin");
    int httpResponseCode = http.GET();
    if(httpResponseCode == 200){
      // Serial.println(payload); debug용 
      String payload = http.getString();
      quantity = jsonParse2(jsonParse(payload, "con"), "quantity").toInt(); 
    }
    else{
      Serial.println("Response Code is not 200 !!");
    } 
    http.end();
  }

  //Serial.print("[Debug] Setted state : ");
  //Serial.println(state);
  
  return quantity;
}


void send_detected(){
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      http.begin(serverName + "/" + Name + "/rail");
      http.addHeader("Content-Type", "application/vnd.onem2m-res+xml;ty=4");
      http.addHeader("X-M2M-RI", "adnae/1234");
      http.addHeader("X-M2M-Origin", Name);
      String httpRequestData = "";
      httpRequestData += "<m2m:cin xmlns:m2m=\"http://www.onem2m.org/xml/protocols\">\n";
      httpRequestData += "<con>" + String("{'state' : 'stop'}") + "</con>";
      httpRequestData += "</m2m:cin>";
      Serial.println(httpRequestData);
          
      int httpResponseCode = http.POST(httpRequestData);
    
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      
      // Free resources
      http.end();
    }
}

void setup() {
  Serial.begin(38400); 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
   
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

}

void loop() {
  String state = sub_get_state();
  Serial.println(state);
  if(sub_get_state() == "run"){
    Serial.println("State : run");

    int quantity = sub_get_quantity();
    int cnt = 0;

    while(cnt != quantity){
      if(Serial.available()){
        String temp = Serial.readStringUntil('\n');

        if(temp[0] == 'D'){
          if(temp[1] == 'E'){
            cnt++;
            Serial.println("D1");
          }
        }
      }
    }

    send_detected();
  }
  delay(500);
}
