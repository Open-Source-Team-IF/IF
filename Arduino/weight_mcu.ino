#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

char* ssid = "SF_LOW";
char* password = "t1v0r20!^";
String serverName = "http://146.56.166.36:7579/Mobius";
String Name = "stand1";


void send_detected(){
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      http.begin(serverName + "/" + Name + "/rail");
      http.addHeader("Content-Type", "application/vnd.onem2m-res+xml;ty=4");
      http.addHeader("X-M2M-RI", "adnae/1234");
      http.addHeader("X-M2M-Origin", Name);
      String httpRequestData = "";
      httpRequestData += "<m2m:cin xmlns:m2m=\"http://www.onem2m.org/xml/protocols\">\n";
      httpRequestData += "<con>" + String(2) + "</con>";
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
      if(Serial.available()){
        Serial.println("node MCU");
        String temp = Serial.readStringUntil('\n');
        Serial.println("temp : " + temp);
        String test = "detected\n";
        if(temp[0] == 'D'){
          if(temp[1] == 'E'){
            Serial.println("Send Server");
            send_detected();
          }  
        }
      }
}
