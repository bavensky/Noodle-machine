//////// Mode 2 admin mode ///////
void mode2() {
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

  //  เช็คตำแหน่งการแสดงผลหน้าจอ
  if (pressState == true) { //  ตรวจสอบเมื่อมีการกด
    pressState = false;
    lcd.setCursor(lcdCol, 1); // กำหนดตำแหน่งหน้าจอแสดงผล
    lcd.print(numKey);
    countPass += 1;
    lcdCol += 1;
  }


  unsigned long curGet = millis();

  //  ออกจากโหมดเมื่อครบ 1 นาที
  if (curGet - preGet >= 10000) {
    lcd.clear();
    lcdCol = 11;
    countPass = 0;
    preGet = curGet;
    mode = 0;
  }



  //  ตรวจสอบการกดรหัส กรณีเลือกเลขหลักสิบ
  if (countPass == 1) numKey1 = numKey;
  if (countPass == 2) numKey2 = numKey;
  if (countPass == 3) numKey3 = numKey;
  if (countPass == 4) {
    numKey4 = numKey;

    //  แปลงตัวเลขเป็นตัวอักษร เพื่อตรวจสอบ
    String checkPass = String(numKey1) + String(numKey2) + String(numKey3) + String(numKey4);

    // check password
    if (checkPass == password) {
      lcd.setCursor(0, 2);
      lcd.print("   Login Success    ");
      delay(2000);
      lcd.clear();
      lcdCol = 11;
      countPass = 0;

      // อ่านข้อความจาก EEPROM
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

      // กระโดดไปโหมด 3 แสดงผลระบบสำหรับแอดมิน
      mode = 3;
    } else {
      //  แสดงข้อความ กดรหัสผิด
      lcd.setCursor(0, 2);
      lcd.print(" Incorrect Password ");
      delay(2000);
      lcd.clear();
      lcdCol = 11;
      countPass = 0;

      // กระโดดไปโหมด 2 เข้าระบบแอดมิน
      mode = 2;
    }
  }
}
