//////// Mode 3 System monitor ///////
void mode3() {
  //  byte fstock1, fstock2, fstock3, fstock4, fstock5, fstock6;
  //  byte bstock1, bstock2, bstock3, bstock4, bstock5, bstock6;

  getKeypad();

  lcd.setCursor(0, 0);
  lcd.print("Noodle in stock : ");

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

  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(200);



  //  if (inChar == '1') {
  //    mp3_play(1);
  //    delay(500);
  //  } else if (inChar == '2') {
  //    mp3_play(2);
  //    delay(500);
  //  } else if (inChar == '3') {
  //    mp3_play(3);
  //    delay(500);
  //  } else if (inChar == '4') {
  //    mp3_play(4);
  //    delay(500);
  //  } else if (inChar == '5') {
  //    mp3_play(5);
  //    delay(500);
  //  } else if (inChar == '6') {
  //    mp3_play(6);
  //    delay(500);
  //  } else if (inChar == '*') {
  //    mp3_stop();
  //    delay(500);
  //  }
}

