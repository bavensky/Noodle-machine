/*
   Instant Noodle Vending Machine (Master Display)
   RMUTL Senior Project
   Coder  : ArduinoSiam
   Date   : 08/04/2560

   ---pin Connecting---
    I2C slave  :
      GND     GND
      SDA     A4
      SCL     A5

    LCD i2c :
      GND     GND
      VCC     5V
      SDA     A4
      SCL     A5

    RTC i2c :
      GND     GND
      VCC     5V
      SDA     A4
      SCL     A5

    Keypad 4x4 :
      from left to right
      1-4 Row
      5-8 Column

    MP3  :
      TX      10 RX Software Serial
      RX      11 TX Software Serial

    Coin vending:
      Signal  2

    Heater  :
      Trig    A0

    Coin feeder :
      Signal  A1

     Flow sensor :
      Signal  A2

    Light  :
      Trig    A3

    mp3 list
      1) welcome
      2) insert coin
      3) choose noodle cup
      4) pick your noodle
      5) hot water
*/


/*************** Include Library ***************/
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


/*************** Initail variable ***************/
// define pin
#define PINSG9  2   //  coin vending 
#define heater  A0  
#define flow    A2  
#define light   A3
#define ONE_WIRE_BUS 13 //  ds18b20 temperature sensor

// init onewire comminication
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;
float tempC = 0.0;


// init real time clock
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"   Sunday", "   Monday", "  Tuesday", "Wednesday", "Thursday ", "   Friday", " Saturday"};


// init keypad 4x4
#define password  "1111"
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


// init lcd display 20 x 4
LiquidCrystal_I2C lcd(0x38, 20, 4); //  LCD address 0x38


//init mp3 module
SoftwareSerial mp3(10, 11);  // RX, TX
SoftwareServo myservo;
#define pinServo A1


// global variable

// get keypad
byte numKey, numKey1, numKey2, numKey3, numKey4;
char inChar;

// loop status
byte countPass = 0, mode = 0, lcdCol = 11;
boolean pressState = false;

// Get noodle count
byte countGet;
byte dataNoodle;


// detect coin vending
int sum;
int count = 0;
float cal_coin;

// stock noodle
byte stock = 12;  //  for caribation stock
byte fstock1, fstock2, fstock3, fstock4, fstock5, fstock6;
byte bstock1, bstock2, bstock3, bstock4, bstock5, bstock6;

// EEPROM address for stock noodle
byte f_stock1 = 1;
byte f_stock2 = 2;
byte f_stock3 = 3;
byte f_stock4 = 4;
byte f_stock5 = 5;
byte f_stock6 = 6;
byte b_stock1 = 7;
byte b_stock2 = 8;
byte b_stock3 = 9;
byte b_stock4 = 10;
byte b_stock5 = 11;
byte b_stock6 = 12;


// interval variable
unsigned long preCoin = 0;
unsigned long preSelect = 0;
unsigned long preGet = 0;

/*************** Sub function ***************/
// read coin vending
void coin() {
  unsigned long duration;
  for (int i = 0; i <= 5; i++)  {
    duration = pulseIn(PINSG9, LOW, 1000000);
    cal_coin = duration / 1000.00;
    Serial.print("DelT=");
    Serial.print(cal_coin);
    Serial.println(" ms");
    if (cal_coin > 2) {
      count = count + 1;
    }
  }

  if (cal_coin == 0) {
    if (count > 0 && count < 7) {
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


// get data form keypad
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

// get data form 18b20
void getTemp() {
  sensors.requestTemperatures();
  tempC = sensors.getTempC(insideThermometer);
}

// eject coin
void eject() {
  for (int i = 0; i <= 2000; i++) {
    myservo.write(0);
    SoftwareServo::refresh();
  }
  for (int i = 0; i <= 2000; i++) {
    myservo.write(180);
    SoftwareServo::refresh();
  }
  for (int i = 0; i <= 2000; i++) {
    myservo.write(0);
    SoftwareServo::refresh();
  }
}



/*************** setup program ***************/
void setup() {
  // Serial
  Serial.begin(9600);

  //  mp3
  mp3.begin (9600);
  mp3_set_serial (mp3);
  mp3_set_volume (25);

  //  i2c
  Wire.begin();

  // sofeware servo
  myservo.attach(pinServo);

  // output control
  pinMode(heater, OUTPUT);
  pinMode(light, OUTPUT);
  digitalWrite(heater, HIGH);
  digitalWrite(light, HIGH);
  
  // ds18b20
  sensors.begin();
  sensors.getAddress(insideThermometer, 0);
  sensors.setResolution(insideThermometer, 9);


  // rtc 1307
  rtc.begin();  // i2c address 0x68
  //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));


  //  first time caribation noodle in stock
  //  stock = 12;
  //  EEPROM.write(f_stock1, stock);
  //  EEPROM.write(f_stock2, stock);
  //  EEPROM.write(f_stock3, stock);
  //  EEPROM.write(f_stock4, stock);
  //  EEPROM.write(f_stock5, stock);
  //  EEPROM.write(f_stock6, stock);
  //  EEPROM.write(b_stock1, stock);
  //  EEPROM.write(b_stock2, stock);
  //  EEPROM.write(b_stock3, stock);
  //  EEPROM.write(b_stock4, stock);
  //  EEPROM.write(b_stock5, stock);
  //  EEPROM.write(b_stock6, stock);
  //  delay(1000);

  //  read EEPROM stock Noodle
  fstock1 = EEPROM.read(f_stock1);
  fstock2 = EEPROM.read(f_stock2);
  fstock3 = EEPROM.read(f_stock3);
  fstock4 = EEPROM.read(f_stock4);
  fstock5 = EEPROM.read(f_stock5);
  fstock6 = EEPROM.read(f_stock6);
  bstock1 = EEPROM.read(b_stock1);
  bstock2 = EEPROM.read(b_stock2);
  bstock3 = EEPROM.read(b_stock3);
  bstock4 = EEPROM.read(b_stock4);
  bstock5 = EEPROM.read(b_stock5);
  bstock6 = EEPROM.read(b_stock6);
  delay(500);


  // interrupt coin vending
  pinMode(PINSG9, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PINSG9), coin, LOW);

  // first display
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


/*************** loop program ***************/
void loop() {
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.print("   Noodle Vending   ");
  lcd.setCursor(0, 1);
  lcd.print("    15baht/1cup     ");
  lcd.setCursor(0, 2);
  if (sum == 0) {
    lcd.print(" Insert coin 5 / 10 ");
  } else {
    lcd.print("   Coin = ");
    lcd.print(sum);
    lcd.print(" baht   ");
  }

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

  if (sum >= 15) {
    lcd.clear();
    mode = 1;
  }

  if (sum >= 5) {
    unsigned long curCoin = millis();
    if (curCoin - preCoin >= 5000) {
      preCoin = curCoin;
      mp3_play(2);
    }
  }

  if (customKey == 'A') {
    eject();
  }
  if (customKey == 'B') {
    for (int i = 0; i <= 2000; i++) {
      myservo.write(0);
      SoftwareServo::refresh();
    }
  }
  if (customKey == 'C') {
    for (int i = 0; i <= 2000; i++) {
      myservo.write(80);
      SoftwareServo::refresh();
    }
  }

  if (customKey == 'D') {
    // goto admin mode
    lcd.clear();
    mode = 2;
    delay(200);
  }

  //////// All Mode ////////

  while (mode == 1) {
    // select noodle
    mode1();
  }

  while (mode == 2) {
    // admin mode
    mode2();
  }

  while (mode == 3) {
    // System monitor
    mode3();
  }
  while (mode == 4) {
    // get noodle
    mode4();
  }
}
