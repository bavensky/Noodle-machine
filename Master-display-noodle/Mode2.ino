//////// Mode 2 admin mode ///////
void mode2() {
  // print mode are in
  Serial.println("admin mode");


  // mode 2 display
  lcd.setCursor(0, 0);
  lcd.print("Admin Login         ");
  lcd.setCursor(0, 1);
  lcd.print(" Password:");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");



  //  get data from keypad
  getKeypad();
  if (pressState == true) {
    pressState = false;
    lcd.setCursor(lcdCol, 1);
    lcd.print(numKey);
    countPass += 1;
    lcdCol += 1;
  }



  // insert password
  if (countPass == 1) numKey1 = numKey;
  if (countPass == 2) numKey2 = numKey;
  if (countPass == 3) numKey3 = numKey;
  if (countPass == 4) {
    numKey4 = numKey;
    String checkPass = String(numKey1) + String(numKey2) + String(numKey3) + String(numKey4);

    // check password
    if (checkPass == password) {
      lcd.setCursor(0, 2);
      lcd.print("   Login Success    ");
      delay(2000);
      lcd.clear();
      lcdCol = 11;
      countPass = 0;

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

      mode = 3;
    } else {
      lcd.setCursor(0, 2);
      lcd.print(" Incorrect Password ");
      delay(2000);
      lcd.clear();
      lcdCol = 11;
      countPass = 0;
      mode = 2;
    }
  }
}
