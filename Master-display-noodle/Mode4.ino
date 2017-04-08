//////// Mode 4 Get noodle ///////
void mode4() {
  unsigned long curGet = millis();
  if (curGet - preGet >= 5000) {
    preGet = curGet;
    mp3_play(4);
    countGet = countGet + 1;
  }

  getKeypad();
  //  stockNoodle = stockNoodle - 1;
  lcd.setCursor(0, 0);
  lcd.print("Pick up your noodle!");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(200);

  //  EEPROM.write(eeAdd, stockNoodle);
  if (countGet >= 3) {
    dataNoodle = 0;
    mode = 0;
  }

}

