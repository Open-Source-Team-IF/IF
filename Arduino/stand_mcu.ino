// stand_mcu.ino
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include <Servo.h>

String serverName = "http://146.56.166.36:7579/Mobius";
String Name = "stand1";

char* ssid = "iptime";
char* password = "asdf1324";

Servo myservo;  // create servo object to control a servo



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

  Serial.println(state);
  
  return state;
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

  myservo.attach(D7);  // attaches the servo on GIO2 to the servo object
}

void loop() {
  if(sub_get_state() == "run"){
    Serial.println('1');
    myservo.write(200);    
  }
  else{
    Serial.println("0");
    myservo.write(90);
  }
  delay(500);
}
