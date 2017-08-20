//////// Mode 4 Get noodle ///////
void mode4() {
  // get data from keypad
  getKeypad();


  // get data temperature
  getTemp();


  // sound loop
  unsigned long curGet = millis();
  if (curGet - preGet >= 10000) {
    preGet = curGet;
    if (countGet <= 4) {
      mp3_play(4);  // กรุณาหยิบบะหมี่
    } else if (countGet >= 5) {
      mp3_play(5); // กรุณาเติมน้ำร้อน
    }
    countGet = countGet + 1;
  }

  if (countGet <= 1) {
    digitalWrite(heater, LOW);
  } else if (tempC <= 40) {
    digitalWrite(heater, LOW); // heater  ON
  } else {
    digitalWrite(heater, HIGH); // heater OFF
  }

  Serial.println(analogRead(flow));
  
  if (analogRead(flow) > 900) {
    countFlow += 1;
  }

  if (analogRead(flow) > 900 && countFlow == 1) {
    waterState = false;
  } else if(countFlow == 0) {
    waterState = true;
  }


  // exit mode
  if (countGet > 7) {

    //    check water temperature
    if (tempC < 40) {
      tempState = true;
    } else {
      tempState = false;
    }


    // if noodle cup out of stock
    if (fstock1 == 0 && fstock2 == 0 && fstock3 == 0 && fstock4 == 0 && fstock5 == 0 && fstock6 == 0
        && bstock1 == 0 && bstock2 == 0 && bstock3 == 0 && bstock4 == 0 && bstock5 == 0 && bstock6 == 0) {
      noodleState = true;
    }


    lcd.clear();
    countGet = 0;
    dataNoodle = 0;
    countFlow = 0;

    // กระโดดไปโหมด 0 หน้าหลัก
    mode = 0;
  }



  // mode 4 display
  lcd.setCursor(0, 0);
  lcd.print("Pick Up Your Noodles");
  lcd.setCursor(0, 1);
  lcd.print(" Water Temp: ");
  lcd.print(tempC);
  lcd.print(" C ");
  lcd.setCursor(0, 2);
  lcd.print(" Hot Water Is Ready ");
  lcd.setCursor(0, 3);
  lcd.print("   Dispenser Below  ");
}

