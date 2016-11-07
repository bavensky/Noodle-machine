/*
 * Slave
 */
 
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(8);                
  Wire.onRequest(requestEvent); 
}

void loop() {
  Serial.println(analogRead(A0)/4);
  delay(100);
}

void requestEvent() {
  Wire.write(analogRead(A0)/4); 
}
