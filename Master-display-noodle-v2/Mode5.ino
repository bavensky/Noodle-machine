//////// Mode 5 Warning mode ///////
void mode5() {
  // backlight loop
  unsigned long curGet = millis();

  //  ไฟหน้าจอกระพริบทุก ๆ 1 วินาที
  if (curGet - preGet >= 1000) {
    lcd.noBacklight();
    preGet = curGet;
  } else {
    lcd.backlight();
  }



  // mode 5 display
  lcd.setCursor(0, 0);
  lcd.print("     Warning !!!    ");
  lcd.setCursor(0, 1);
  lcd.print("   Out of Sevice    ");
  lcd.setCursor(0, 2);
  if (noodleState == true) {
    lcd.print(" Noodle Outof Stock ");
  } else if (tempState == true) {
    lcd.print(" Heater Not Working ");
  }  else if (waterState == true) {
    lcd.print("      No Water      ");
  } else if (changeCoin == true) {
    lcd.print("   No Change Coin   ");
  } else if (checkWaterFilter = true) {
    lcd.print(" Clear Water Filter ");
  }
  lcd.setCursor(0, 3);
  lcd.print("                    ");



  // exit mode for fix machine
  char customKey = keypad.getKey();
  if (customKey == 'D') {
    lcd.backlight();
    noodleState = false;
    tempState = false;
    waterState = false;
    changeCoin = false;

    
    checkWaterFilter = false;
    // update clear month for first time when you upload code
    DateTime now = rtc.now();   //  read time now
    clearMonth = now.month() + 6;
    if (clearMonth > 12) {
      clearMonth = clearMonth - 12;
    }
    EEPROM.write(addrClear, addrClear);

    // read clear month form EEPROM
    clearMonth = EEPROM.read(addrClear);


    lcd.clear();
    lcdCol = 11;
    countGet = 0;
    dataNoodle = 0;

    // กระโดดไปโหมด 2 เข้าระบบแอดมิน
    mode = 2;
  }
}
