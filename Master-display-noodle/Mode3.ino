//////// Mode 3 System monitor ///////
void mode3() {
  lcd.setCursor(0, 0);
  lcd.print("System check        ");
  lcd.setCursor(0, 1);
  lcd.print("Noodle in stock : ");
  lcd.setCursor(17, 1);
  if (noodle <= 9) lcd.print("0");
  lcd.print(noodle);
  lcd.setCursor(0, 2);
  lcd.print("Play song : ");
  lcd.print(inChar);
  lcd.setCursor(0, 3);
  lcd.print("Temp : ");
  lcd.print(tempC);
  lcd.print(" C");
  delay(200);

  getKeypad();
  getTemp();

  if (inChar == '1') {
    mp3_play(1);
    delay(500);
  } else if (inChar == '2') {
    mp3_play(2);
    delay(500);
  } else if (inChar == '3') {
    mp3_play(3);
    delay(500);
  } else if (inChar == '4') {
    mp3_play(4);
    delay(500);
  } else if (inChar == '5') {
    mp3_play(5);
    delay(500);
  } else if (inChar == '6') {
    mp3_play(6);
    delay(500);
  } else if (inChar == '*') {
    mp3_stop();
    delay(500);
  }
}

