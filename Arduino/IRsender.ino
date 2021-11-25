#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.


void setup() {
  irsend.begin();

}

void loop() {
  //Serial.println("NEC");
  irsend.sendNEC(0x00000001); // Send Data
  delay(100);
}
