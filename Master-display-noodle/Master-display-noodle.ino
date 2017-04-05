/*
   Noodle Vending Machine (Master Display)
   BY RMUTL Senior Project
   ---pin Connecting---
    LCD i2c :
      GND     GND
      VCC     5V
      SDA     A4
      SCL     A5
    Keypad 4x4 :
      from left to right
      1-4 Row
      5-8 Column
*/


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "RTClib.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <SoftwareServo.h>
#include <DFPlayer_Mini_Mp3.h>
#include <EEPROM.h>
int eeAdd = 9;

#define PINSG9  2

#define ONE_WIRE_BUS 13
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;
float tempC = 0.0;

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"   Sunday", "   Monday", "  Tuesday", "Wednesday", "Thursday ", "   Friday", " Saturday"};

#define password  "1234"
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {12, 9, 8, 7};
byte colPins[COLS] = {6, 5, 4, 3};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x38, 20, 4); //  LCD address 0x38

SoftwareSerial mp3(10, 11);  // RX, TX
SoftwareServo myservo;
#define pinServo A1

byte numKey, numKey1, numKey2, numKey3, numKey4;
byte countPass = 0, mode = 0, lcdCol = 11;
boolean pressState = false;
char inChar;
byte data;
int noodle = 0;
int sum = 0;
int count = 0;


void coin() {
  unsigned long duration;
  for (int i = 0; i <= 5; i++)  {
    duration = pulseIn(PINSG9, LOW, 1000000);
    float time = duration / 1000.00;
    //    Serial.print("DelT=");
    //    Serial.print(time);
    //    Serial.println(" ms");

    if (time > 2) {
      count = count + 1;
    }

    if (time == 0) {
      if (count > 0 && count < 3) {
        sum = sum + 1;
        //        Serial.println("1 Bath");
      }
      if (count > 3 && count < 7) {
        sum = sum + 5;
        //        Serial.println("5 Bath");
      }
      if (count > 7) {
        sum = sum + 10;
        //        Serial.println("10 Bath");
      }
      count = 0;
    }
  }
}

void getKeypad() {
  inChar = keypad.getKey();
  switch (inChar) {
    case '1': numKey = 1; pressState = true;  break;
    case '2': numKey = 2; pressState = true;  break;
    case '3': numKey = 3; pressState = true;  break;
    case '4': numKey = 4; pressState = true;  break;
    case '5': numKey = 5; pressState = true;  break;
    case '6': numKey = 6; pressState = true;  break;
    case '7': numKey = 7; pressState = true;  break;
    case '8': numKey = 8; pressState = true;  break;
    case '9': numKey = 9; pressState = true;  break;
    case '0': numKey = 0; pressState = true;  break;
    case '#': lcdCol = 11;  lcd.clear(); countPass = 0;  mode = 0; pressState = false; break;
  }
}

void setup() {
  Serial.begin(9600);
  mp3.begin (9600);
  mp3_set_serial (mp3);
  mp3_set_volume (25);

  EEPROM.write(eeAdd, noodle);
  noodle = EEPROM.read(eeAdd);

  Wire.begin();

  pinMode(PINSG9, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PINSG9), coin, LOW);

  myservo.attach(pinServo);

  sensors.begin();
  sensors.getAddress(insideThermometer, 0);
  sensors.setResolution(insideThermometer, 9);

  rtc.begin();  // i2c address 0x68
  //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("       Noodle       ");
  lcd.setCursor(0, 1);
  lcd.print("   VendingMachine   ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("RMUTL Senior Project");
  delay(1000);
  lcd.clear();

}

void getTemp() {
  sensors.requestTemperatures();
  tempC = sensors.getTempC(insideThermometer);
}

void loop() {
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.print("   Noodle Vending   ");
  lcd.setCursor(0, 1);
  lcd.print("    15baht/1cup     ");
  lcd.setCursor(0, 2);
  lcd.print(" Insert coin 5 / 10 ");
  lcd.setCursor(0, 3);
  lcd.print(" ");
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.setCursor(12, 3);
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() <= 9) lcd.print("0");
  lcd.print(now.minute());
  lcd.print("   ");

  char customKey = keypad.getKey();
  Serial.println(customKey);

  if (customKey == 'A') {
    myservo.write(0);
    SoftwareServo::refresh();
  }
  if (customKey == 'B') {
    myservo.write(90);
    SoftwareServo::refresh();
  }
  if (customKey == 'C') {
    myservo.write(180);
    SoftwareServo::refresh();
  }
  if (customKey == 'D') {
    Wire.beginTransmission(8);
    Wire.write(1);
    Wire.endTransmission();
    Serial.println("key = A");
  }

  if (customKey == '#') {
    lcd.clear();
    mode = 1;
    delay(200);
    Serial.println("mode = 1");
  }

  //////// Mode 1 ////////
  while (mode == 1) {
    Serial.print("mode 1 : ");
    Serial.print(countPass);
    Serial.print(" ");
    Serial.print(numKey1);
    Serial.print(" ");
    Serial.print(numKey2);
    Serial.print(" ");
    Serial.print(numKey3);
    Serial.print(" ");
    Serial.println(numKey4);

    lcd.setCursor(0, 0);
    lcd.print("Admin Login         ");
    lcd.setCursor(0, 1);
    lcd.print(" password:");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");

    getKeypad();
    if (pressState == true) {
      pressState = false;
      lcd.setCursor(lcdCol, 1);
      lcd.print(numKey);
      countPass += 1;
      lcdCol += 1;
    }

    if (countPass == 1) numKey1 = numKey;
    if (countPass == 2) numKey2 = numKey;
    if (countPass == 3) numKey3 = numKey;
    if (countPass == 4) {
      numKey4 = numKey;
      String checkPass = String(numKey1) + String(numKey2) + String(numKey3) + String(numKey4);
      if (checkPass == password) {
        lcd.setCursor(0, 2);
        lcd.print("      Suuccess.     ");
        delay(2000);
        lcd.clear();
        lcdCol = 11;
        countPass = 0;
        mode = 2;
      } else {
        lcd.setCursor(0, 2);
        lcd.print("   Fail try again.  ");
        delay(2000);
        lcd.clear();
        lcdCol = 11;
        countPass = 0;
        mode = 1;
      }
    }
  }

  //////// Mode 2 ////////
  while (mode == 2) {
    Serial.println("mode 2");
    Serial.println(inChar);
    lcd.setCursor(0, 0);
    lcd.print("System check        ");
    lcd.setCursor(0, 1);
    lcd.print("Noodle in stock : ");
    lcd.setCursor(17, 1);
    if (noodle <= 9) lcd.print("0");
    lcd.print(noodle);
    lcd.setCursor(0, 2);
    lcd.print("Play song : ");
    lcd.print(inChar);
    lcd.setCursor(0, 3);
    lcd.print("Temp : ");
    lcd.print(tempC);
    lcd.print(" C");
    delay(200);

    getKeypad();
    getTemp();

    if (inChar == '1') {
      mp3_play(1);
      delay(500);
    } else if (inChar == '2') {
      mp3_play(2);
      delay(500);
    } else if (inChar == '3') {
      mp3_play(3);
      delay(500);
    } else if (inChar == '4') {
      mp3_play(4);
      delay(500);
    } else if (inChar == '5') {
      mp3_play(5);
      delay(500);
    } else if (inChar == '6') {
      mp3_play(6);
      delay(500);
    } else if (inChar == '*') {
      mp3_stop();
      delay(500);
    }
  }
}
