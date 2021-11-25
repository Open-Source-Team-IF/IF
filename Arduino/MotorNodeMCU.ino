#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>

char* ssid = "SF_LOW";
char* password = "t1v0r20!^";

//Your Domain name with URL path or IP address with path
String serverName = "http://146.56.166.36:7579/Mobius";
String Name = "/cart1";

unsigned long lastTime = 0;

unsigned long timerDelay = 5000;

unsigned long Next_Setted_Time = 0;

String jsonParse(String str, String findstr){
  int index = str.indexOf(findstr) + findstr.length() + 3;
  int index2 = str.indexOf('"', index);
  return str.substring(index, index2);
}


void getWard(){
  String ward;
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(serverName + Name + "/direction/la");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-M2M-RI","/Mobius");
    http.addHeader("X-M2M-Origin","SOrigin");
    int httpResponseCode = http.GET();
    if(httpResponseCode == 200){
      String payload = http.getString();
      ward = jsonParse(payload, "con");
      Serial.println(ward); //debug용 
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
      
      if(Serial.available()){
        String temp = Serial.readString();
        //Serial.println("temp : " + temp);
        if(temp == "Cross Road Signal Waiting\n") getWard();  
      }
      
      
}
