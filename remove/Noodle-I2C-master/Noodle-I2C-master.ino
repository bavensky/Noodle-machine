/*
   Master
*/

#include <Wire.h>
#define LED     13
#define BUTTON  2

byte c, data = 100;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

}

void loop() {

  if (digitalRead(BUTTON) == 0)  {
    Wire.beginTransmission(8);
    Wire.write("x is ");
    Wire.write(data);
    Wire.endTransmission();
  }
  
  Wire.requestFrom(8, 6);
  if (Wire.available() > 0)  {
    c = Wire.read();
    Serial.println(c);
  }
  analogWrite(LED, c);
  delay(100);
}
