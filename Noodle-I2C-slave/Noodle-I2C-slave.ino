/*
   Slave
*/

#include <Wire.h>
int x;
byte data, c;
void setup() {
  Serial.begin(115200);
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
  data = 10;
//  Wire.requestFrom(8, 6);
//  if (Wire.available() > 0)  {
//    c = Wire.read();
//    Serial.println(c);
//  }
  Serial.println(x);
  delay(200);
}

void requestEvent() {
  Wire.write(data);
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  x = Wire.read();    // receive byte as an integer
}
