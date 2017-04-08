//////// Mode 1 select noodle ///////
void mode1() {
  unsigned long curSelect = millis();
  if (curSelect - preSelect >= 5000) {
    preSelect = curSelect;
    mp3_play(3);
  }

  lcd.setCursor(0, 0);
  lcd.print("Select your noodle: ");
  lcd.setCursor(0, 1);
  lcd.print(" number : ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("'*' back   '#' enter");

  getKeypad();
  if (pressState == true) {
    pressState = false;
    lcd.setCursor(lcdCol, 1);
    lcd.print(numKey);
    dataNoodle = numKey;
    countPass += 1;
    lcdCol += 1;
  }

  if (inChar == '*') {
    eject();
    delay(500);
    eject();
    delay(500);
    eject();
    lcd.clear();
    sum = 0;
    mode = 0;
  }


  if (inChar == '#') {
    updateNoodle();
    sum = 0;
    mode = 4;
  }

  if (countPass == 1) numKey1 = numKey;
  if (countPass == 2) {
    numKey2 = numKey;

    numKey1 = numKey1 * 10;
    numKey2 = numKey1 + numKey2;
    dataNoodle = numKey2;

    if (dataNoodle > 12) {
      dataNoodle = 0;
      Serial.println("qagesrhd");
      mode = 1;
    } else {
      updateNoodle();
      sum = 0;
      mode = 4;
    }
  }
}

void updateNoodle() {
  lcd.clear();
  lcdCol = 11;
  dataNoodle = 0;

  if (dataNoodle == 1) {
    fstock1 = fstock1 - 1;
    EEPROM.write(f_stock1, fstock1);
  } else if (dataNoodle == 2) {
    fstock2 = fstock2 - 1;
    EEPROM.write(f_stock2, fstock2);
  } else if (dataNoodle == 3) {
    fstock3 = fstock3 - 1;
    EEPROM.write(f_stock3, fstock3);
  } else if (dataNoodle == 4) {
    fstock4 = fstock4 - 1;
    EEPROM.write(f_stock4, fstock4);
  } else if (dataNoodle == 5) {
    fstock5 = fstock5 - 1;
    EEPROM.write(f_stock5, fstock5);
  } else if (dataNoodle == 6) {
    fstock6 = fstock6 - 1;
    EEPROM.write(f_stock6, fstock6);
  } else if (dataNoodle == 7) {
    bstock1 = bstock1 - 1;
    EEPROM.write(b_stock1, bstock1);
  } else if (dataNoodle == 8) {
    bstock2 = bstock1 - 2;
    EEPROM.write(b_stock2, bstock2);
  } else if (dataNoodle == 9) {
    bstock3 = bstock3 - 1;
    EEPROM.write(b_stock3, bstock3);
  } else if (dataNoodle == 10) {
    bstock4 = bstock4 - 1;
    EEPROM.write(b_stock4, bstock4);
  } else if (dataNoodle == 11) {
    bstock5 = bstock5 - 1;
    EEPROM.write(b_stock5, bstock5);
  } else if (dataNoodle == 12) {
    bstock6 = bstock6 - 1;
    EEPROM.write(b_stock6, bstock6);
  }

}

