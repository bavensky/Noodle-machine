/*
 * Master
 */
 
#include <Wire.h>
#define LED     3
#define BUTTON  4

byte c;

void setup() {
  Wire.begin();        
  Serial.begin(115200);  

  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  
}

void loop() {

  if(digitalRead(BUTTON) == 0)  {
    Wire.requestFrom(8, 6);
    if(Wire.available() > 0)  {
      c = Wire.read();
      Serial.println(c);  
    }
  }
  analogWrite(LED, c);
  delay(00);
}
