//////// Mode 4 Get noodle ///////
void mode4() { 
  unsigned long curGet = millis();
  if (curGet - preGet >= 5000) {
    preGet = curGet;
    //    mp3_play(4);  // กรุณาหยิบบะหมี่
    if (countGet <= 4) {
      mp3_play(4);  // กรุณาเติมน้ำร้อน
    } else if (countGet >= 5) {
      mp3_play(5);
    }
    countGet = countGet + 1;
  }

  if (countGet > 7) {
    lcd.clear();
    countGet = 0;
    dataNoodle = 0;
    mode = 0;
  }

//  if() {
//    waterState = true;
//  }

  
  getKeypad();
  getTemp();

  lcd.setCursor(0, 0);
  lcd.print("Pick up your noodle!");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("Hot water already...");
  lcd.setCursor(0, 3);
  lcd.print("Boiler temp: ");
  lcd.print(tempC);
  lcd.print("C");
  delay(200);

  //  EEPROM.write(eeAdd, stockNoodle);
}

