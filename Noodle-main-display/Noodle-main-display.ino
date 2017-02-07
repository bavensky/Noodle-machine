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
#include <Password.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {6, 5, 4, 3};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Password password = Password( "1234" ); // Set your password
LiquidCrystal_I2C lcd(0x38, 20, 4); //  LCD address 0x38

#define COIN  3
int sum = 0;
unsigned long duration;
int count = 0;
byte mode = 0;
byte _lcdcolum = 16;

void keypadEvent(KeypadEvent eKey) {
  switch (keypad.getState()) {
    case PRESSED:
      Serial.print("Pressed: ");
      Serial.println(eKey);
      lcd.setCursor(_lcdcolum, 3);
      lcd.print(eKey);
      _lcdcolum++;

      switch (eKey) {
        case '*': checkPassword(); break;
        //case '#': password.reset(); break;
        default: password.append(eKey);
      }
  }
}

/**   เช็ค password  **/
void checkPassword() {
  if (password.evaluate()) {
    Serial.println("Success");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Pharmacy stock   ");
    lcd.setCursor(0, 1);
    lcd.print("WELCOME...");
    password.reset(); // clear key password
    _lcdcolum = 16; // reset count print colume lcd
    mode = 1;
  } else {
    Serial.println("Wrong");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Pharmacy stock   ");
    lcd.setCursor(0, 1);
    lcd.print("Try Agian...");
    password.reset(); // clear key password
    _lcdcolum = 16; // reset count print colume lcd
    mode = 0;
  }
}

void coin() {
  for (int i = 0; i <= 5; i++)  {
    duration = pulseIn(pin, LOW, 1000000);
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

void mainscreen()  {
  lcd.setCursor(0, 0);
  lcd.print("       Noodle       ");
  lcd.setCursor(0, 1);
  lcd.print("   VendingMachine   ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("RMUTL Senior Project");
}

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  keypad.addEventListener(keypadEvent);


  pinMode(COIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(COIN), coin, LOW);

  mainscreen();
  delay(1000);
  lcd.clear();

}

void loop() {
  Serial.print("Incoming coin = ");
  Serial.println(sum);

  char customKey = keypad.getKey();
  if (customKey == '1') {
    Serial.println(customKey);
  }
  // select mode
  //  if (mode == 0)  {
  //    mainscreen();
  //  } else if (mode == 1)  {
  //    lcd.setCursor(0, 0);
  //    lcd.print("   Done   ");
  //  }


  lcd.setCursor(0, 0);
  lcd.print("       Noodle       ");
  lcd.setCursor(0, 1);
  lcd.print("   VendingMachine   ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("RMUTL Senior Project");

}


