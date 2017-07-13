//////// Mode 1 select noodle ///////
void mode1() {
  // print mode are in
  Serial.println("select noodle mode");


  // interval sound speaker
  unsigned long curSelect = millis();
  if (curSelect - preSelect >= 5000) {
    preSelect = curSelect;
    mp3_play(3);  // กรุณาเลือกบะหมี่
  }



  // mode 1 display
  lcd.setCursor(0, 0);
  lcd.print("Select Your Noodles ");
  lcd.setCursor(0, 1);
  lcd.print(" Number : ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("* Clear    # Confirm");


  // get keypad for select noodle
  getKeypad();
  if (pressState == true) {
    pressState = false;
    lcd.setCursor(lcdCol, 1);
    lcd.print(numKey);
    dataNoodle = numKey;
    countPass += 1;
    lcdCol += 1;
  }


  // exit choose noodle and refund 15 baht
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



  //  choose noodle finish
  if (inChar == '#') {
    //    checkStock();
    if (dataNoodle == 0) {
      countPass = 0;
      numKey1 = 0;
      numKey2 = 0;
      dataNoodle = 0;
      lcdCol = 11;

      lcd.setCursor(0, 2);
      lcd.print("   Invalid Number!  ");
      delay(1000);
      lcd.clear();
    } else {
      updateNoodle();

      if (sum > 0) {
        sum = sum / 5;
      }

      if (sum == 1) {
        eject();
        delay(500);
      } else if (sum == 2) {
        eject();
        delay(500);
        eject();
        delay(500);
      } else if (sum == 3) {
        eject();
        delay(500);
        eject();
        delay(500);
        eject();
        delay(500);
      }

      //      sum = 0;
      //      mode = 4;
    }
  }



  if (countPass == 1) numKey1 = numKey;
  if (countPass == 2) {
    numKey2 = numKey;

    numKey1 = numKey1 * 10;
    numKey2 = numKey1 + numKey2;
    dataNoodle = numKey2;

    //    checkStock();
    if (dataNoodle > 12) {
      countPass = 0;
      numKey1 = 0;
      numKey2 = 0;
      dataNoodle = 0;
      lcdCol = 11;
      mode = 1;
      lcd.setCursor(0, 2);
      lcd.print("   Invalid Number!  ");
      delay(1000);
      lcd.clear();
    } else {
      if (sum > 0) {
        sum = sum / 5;
      }

      if (sum == 1) {
        eject();
        delay(500);
      } else if (sum == 2) {
        eject();
        delay(500);
        eject();
        delay(500);
      } else if (sum == 3) {
        eject();
        delay(500);
        eject();
        delay(500);
        eject();
        delay(500);
      }

      updateNoodle();

      //      sum = 0;
      //      mode = 4;
    }
  }
}



// clear data
void clearChoice() {
  countPass = 0;
  numKey1 = 0;
  numKey2 = 0;
  lcdCol = 11;

  lcd.setCursor(0, 0);
  lcd.print("Select Your Noodles ");
  lcd.setCursor(0, 1);
  lcd.print(" Number : ");
  lcd.setCursor(0, 2);
  lcd.print("  Out of Stock !!!  ");
  lcd.setCursor(0, 3);
  lcd.print("* Clear    # Confirm");

  delay(1000);
  lcd.clear();
  dataNoodle = 0;
  mode = 1;
}



// check noodle in stock
//void checkStock() {
//  fstock1 = EEPROM.read(f_stock1);
//  fstock2 = EEPROM.read(f_stock2);
//  fstock3 = EEPROM.read(f_stock3);
//  fstock4 = EEPROM.read(f_stock4);
//  fstock5 = EEPROM.read(f_stock5);
//  fstock6 = EEPROM.read(f_stock6);
//  bstock1 = EEPROM.read(b_stock1);
//  bstock2 = EEPROM.read(b_stock2);
//  bstock3 = EEPROM.read(b_stock3);
//  bstock4 = EEPROM.read(b_stock4);
//  bstock5 = EEPROM.read(b_stock5);
//  bstock6 = EEPROM.read(b_stock6);
//
//  Serial.print("checkStock ");
//  Serial.println(fstock1);
//  delay(2000);
//
//  // if noodle cup out of stock
//  if (fstock1 == 0 && fstock2 == 0 && fstock3 == 0 && fstock4 == 0 && fstock5 == 0 && fstock6 == 0
//      && bstock1 == 0 && bstock2 == 0 && bstock3 == 0 && bstock4 == 0 && bstock5 == 0 && bstock6 == 0) {
//    noodleState = true;
//    Serial.println("noodleState = true");
//    clearChoice();
//  }
//
//  // if your noodle out of stock
//  if (dataNoodle == fstock1 && fstock1 == 0) {
//    Serial.println("clearChoice");
//    clearChoice();
//  } else if (dataNoodle == fstock2 && fstock2 == 0) {
//    clearChoice();
//  } else if (dataNoodle == fstock3 && fstock3 == 0) {
//    clearChoice();
//  } else if (dataNoodle == fstock4 && fstock4 == 0) {
//    clearChoice();
//  } else if (dataNoodle == fstock5 && fstock5 == 0) {
//    clearChoice();
//  } else if (dataNoodle == fstock6 && fstock6 == 0) {
//    clearChoice();
//  } else if (dataNoodle == bstock1 && bstock1 == 0) {
//    clearChoice();
//  } else if (dataNoodle == bstock2 && bstock2 == 0) {
//    clearChoice();
//  } else if (dataNoodle == bstock3 && bstock3 == 0) {
//    clearChoice();
//  } else if (dataNoodle == bstock4 && bstock4 == 0) {
//    clearChoice();
//  } else if (dataNoodle == bstock5 && bstock5 == 0) {
//    clearChoice();
//  } else if (dataNoodle == bstock6 && bstock6 == 0) {
//    clearChoice();
//  }
//}




// update noodle stock and send data to slave mcu
void updateNoodle() {
  if (dataNoodle == 1 && fstock1 == 0) { // if your noodle out of stock
    clearChoice();
  } else if (dataNoodle == 2 && fstock2 == 0) {
    clearChoice();
  } else if (dataNoodle == 3 && fstock3 == 0) {
    clearChoice();
  } else if (dataNoodle == 4 && fstock4 == 0) {
    clearChoice();
  } else if (dataNoodle == 5 && fstock5 == 0) {
    clearChoice();
  } else if (dataNoodle == 6 && fstock6 == 0) {
    clearChoice();
  } else if (dataNoodle == 7 && bstock1 == 0) {
    clearChoice();
  } else if (dataNoodle == 8 && bstock2 == 0) {
    clearChoice();
  } else if (dataNoodle == 9 && bstock3 == 0) {
    clearChoice();
  } else if (dataNoodle == 10 && bstock4 == 0) {
    clearChoice();
  } else if (dataNoodle == 11 && bstock5 == 0) {
    clearChoice();
  } else if (dataNoodle == 12 && bstock6 == 0) {
    clearChoice();
  } else {
    // sent data to slave mcu
    Wire.beginTransmission(8);
    Wire.write(dataNoodle);
    Wire.endTransmission();
    delay(1000);

    updateEEPROM();

    // clear data
    lcd.clear();
    lcdCol = 11;
    dataNoodle = 0;
    sum = 0;
    mode = 4;
  }

}




void updateEEPROM() {
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


  // update noodle in eeprom
  if (dataNoodle == 1) {
    fstock1 = fstock1 - 1;
    if (fstock1 <= 0 || fstock1 > 10) fstock1 = 0;
    EEPROM.write(f_stock1, fstock1);
  } else if (dataNoodle == 2) {
    fstock2 = fstock2 - 1;
    if (fstock2 <= 0 || fstock2 > 10) fstock2 = 0;
    EEPROM.write(f_stock2, fstock2);
  } else if (dataNoodle == 3) {
    fstock3 = fstock3 - 1;
    if (fstock3 <= 0 || fstock3 > 10) fstock3 = 0;
    EEPROM.write(f_stock3, fstock3);
  } else if (dataNoodle == 4) {
    fstock4 = fstock4 - 1;
    if (fstock4 <= 0 || fstock4 > 10) fstock4 = 0;
    EEPROM.write(f_stock4, fstock4);
  } else if (dataNoodle == 5) {
    fstock5 = fstock5 - 1;
    if (fstock5 <= 0 || fstock5 > 10) fstock5 = 0;
    EEPROM.write(f_stock5, fstock5);
  } else if (dataNoodle == 6) {
    fstock6 = fstock6 - 1;
    if (fstock6 <= 0 || fstock6 > 10) fstock6 = 0;
    EEPROM.write(f_stock6, fstock6);
  } else if (dataNoodle == 7) {
    bstock1 = bstock1 - 1;
    if (bstock1 <= 0 || bstock1 > 10) bstock1 = 0;
    EEPROM.write(b_stock1, bstock1);
  } else if (dataNoodle == 8) {
    bstock2 = bstock1 - 1;
    if (bstock2 <= 0 || bstock2 > 10) bstock2 = 0;
    EEPROM.write(b_stock2, bstock2);
  } else if (dataNoodle == 9) {
    bstock3 = bstock3 - 1;
    if (bstock3 <= 0 || bstock3 > 10) bstock3 = 0;
    EEPROM.write(b_stock3, bstock3);
  } else if (dataNoodle == 10) {
    bstock4 = bstock4 - 1;
    if (bstock4 <= 0 || bstock4 > 10) bstock4 = 0;
    EEPROM.write(b_stock4, bstock4);
  } else if (dataNoodle == 11) {
    bstock5 = bstock5 - 1;
    if (bstock5 <= 0 || bstock5 > 10) bstock5 = 0;
    EEPROM.write(b_stock5, bstock5);
  } else if (dataNoodle == 12) {
    bstock6 = bstock6 - 1;
    if (bstock6 <= 0 || bstock6 > 10) bstock6 = 0;
    EEPROM.write(b_stock6, bstock6);
  }
}

