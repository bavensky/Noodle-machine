//////// Mode 2 admin mode ///////
void mode2() {
  lcd.setCursor(0, 0);
  lcd.print("Admin Login         ");
  lcd.setCursor(0, 1);
  lcd.print(" password:");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");

  getKeypad();
  if (pressState == true) {
    pressState = false;
    lcd.setCursor(lcdCol, 1);
    lcd.print(numKey);
    countPass += 1;
    lcdCol += 1;
  }

  if (countPass == 1) numKey1 = numKey;
  if (countPass == 2) numKey2 = numKey;
  if (countPass == 3) numKey3 = numKey;
  if (countPass == 4) {
    numKey4 = numKey;
    String checkPass = String(numKey1) + String(numKey2) + String(numKey3) + String(numKey4);
    if (checkPass == password) {
      lcd.setCursor(0, 2);
      lcd.print("      Suuccess.     ");
      delay(2000);
      lcd.clear();
      lcdCol = 11;
      countPass = 0;
      mode = 3;
    } else {
      lcd.setCursor(0, 2);
      lcd.print("   Fail try again.  ");
      delay(2000);
      lcd.clear();
      lcdCol = 11;
      countPass = 0;
      mode = 2;
    }
  }
}
