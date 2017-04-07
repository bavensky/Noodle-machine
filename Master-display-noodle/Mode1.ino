//////// Mode 1 select noodle ///////
void mode1() {
  getKeypad();
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
    lcd.clear();
    sum = 0;
    mode = 4;
  }

  if (countPass == 1) numKey1 = numKey;
  if (countPass == 2) {
    numKey2 = numKey;
    mode = 4;
  }
}

