//////// Mode 4 Get noodle ///////
void mode4() {
  getKeypad();

  stockNoodle = stockNoodle - 1;
  lcd.setCursor(0, 0);
  lcd.print("Pick up your noodle!");
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(3000);

  EEPROM.write(eeAdd, stockNoodle);
  mode = 0;
}

