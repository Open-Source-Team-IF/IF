// loadcell_uno.ino
#include "HX711.h"

// HX711.DOUT  - pin #D3
// HX711.PD_SCK - pin #D4


float avg1;
float avg2;
float tmp1;
float tmp2;

HX711 scale1(5, 6); 

void setup() {
  Serial.begin(38400);
  scale1.set_scale(8000.f); // 1. 7500
  scale1.tare();
  avg1 = (scale1.get_units(10),1);
}

void loop() {
  tmp1 = scale1.get_units();
  
  // 무게변화 감지시
  if(abs(avg1-tmp1) > 1){
    Serial.println("DE");
  }

  avg1 = scale1.get_units(5);

  scale1.power_down();             // put the ADC in sleep mode
  delay(200);
  scale1.power_up();
}