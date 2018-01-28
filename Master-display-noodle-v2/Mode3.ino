//////// Mode 3 System monitor ///////
void mode3() {
  // clear Status for make sure is repair
  noodleState = false;
  tempState = false;
  waterState = false;



  // get data from keypad
  getKeypad();


  // mode 3 display
  lcd.setCursor(0, 0);
  lcd.print("Noodles In Stock :");

  lcd.setCursor(0, 1);
  lcd.print("  ");
  if (fstock1 <= 9)   lcd.print("0");
  lcd.print(fstock1); lcd.print(" ");
  if (fstock2 <= 9)   lcd.print("0");
  lcd.print(fstock2); lcd.print(" ");
  if (fstock3 <= 9)   lcd.print("0");
  lcd.print(fstock3); lcd.print(" ");
  if (fstock4 <= 9)   lcd.print("0");
  lcd.print(fstock4); lcd.print(" ");
  if (fstock5 <= 9)   lcd.print("0");
  lcd.print(fstock5); lcd.print(" ");
  if (fstock6 <= 9)   lcd.print("0");
  lcd.print(fstock6); lcd.print(" ");

  lcd.setCursor(0, 2);
  lcd.print("  ");
  if (bstock1 <= 9)   lcd.print("0");
  lcd.print(bstock1); lcd.print(" ");
  if (bstock2 <= 9)   lcd.print("0");
  lcd.print(bstock2); lcd.print(" ");
  if (bstock3 <= 9)   lcd.print("0");
  lcd.print(bstock3); lcd.print(" ");
  if (bstock4 <= 9)   lcd.print("0");
  lcd.print(bstock4); lcd.print(" ");
  if (bstock5 <= 9)   lcd.print("0");
  lcd.print(bstock5); lcd.print(" ");
  if (bstock6 <= 9)   lcd.print("0");
  lcd.print(bstock6); lcd.print(" ");


  // exit admin mode
  if (inChar == '#') {
    stateAdmin = 0;
    mode = 0;
  }



  // press for clear noodle stock
  if (inChar == '*') {
    stateAdmin += 1;
  }

  if (stateAdmin == 1) {
    lcd.setCursor(0, 3);
    lcd.print("Restock? *:Ok #:Back");
  } else {
    lcd.setCursor(0, 3);
    lcd.print("* Clear    # Confirm");
  }

  // ensure for clear data noodle stock
  if (inChar == '*' && stateAdmin == 2) {
    // Clear noodle in stock
    stock = 10;
    EEPROM.write(f_stock1, stock);
    EEPROM.write(f_stock2, stock);
    EEPROM.write(f_stock3, stock);
    EEPROM.write(f_stock4, stock);
    EEPROM.write(f_stock5, stock);
    EEPROM.write(f_stock6, stock);
    EEPROM.write(b_stock1, stock);
    EEPROM.write(b_stock2, stock);
    EEPROM.write(b_stock3, stock);
    EEPROM.write(b_stock4, stock);
    EEPROM.write(b_stock5, stock);
    EEPROM.write(b_stock6, stock);
    delay(1000);
    stateAdmin = 0;

    // กระโดดไปโหมด 0 หน้าหลัก
    mode = 0;
  }
}

