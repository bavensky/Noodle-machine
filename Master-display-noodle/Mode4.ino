//////// Mode 4 Get noodle ///////
void mode4() {
  // print mode are in
  Serial.println("Get noodle mode");


  // get data from keypad
  getKeypad();


  // get data temperature
  getTemp();



  // sound loop
  unsigned long curGet = millis();
  if (curGet - preGet >= 10000) {
    preGet = curGet;
    //    mp3_play(4);  // กรุณาหยิบบะหมี่
    if (countGet <= 4) {
      mp3_play(4);  // กรุณาเติมน้ำร้อน
    } else if (countGet >= 5) {
      mp3_play(5);
    }
    countGet = countGet + 1;
  }


  // exit mode
  if (countGet > 7) {

    // check water temperature
    if (tempC < 50) {
      tempState = true;
    } else {
      tempState = false;
    }

    lcd.clear();
    countGet = 0;
    dataNoodle = 0;
    mode = 0;
  }

  //     heater loop
  //  if (curGet - preHeat >= 15000) {
  //    countHeater += 1;
  //    preHeat = curGet;
  //  }
  //
  //  Serial.print("countHeater = ");
  //  Serial.println(countHeater);
  //
  //  if (countHeater == 1 || countHeater == 3 || countHeater == 5) {
  //    digitalWrite(heater, LOW);
  //  } else {
  //    digitalWrite(heater, HIGH);
  //  }




  //   worming water detecter
  if (FreqMeasure.available()) {
    if (tempC >= 70) {
      digitalWrite(heater, HIGH); // heater OFF
    } else {
      countFlow += 1;
      Serial.print("FreqMeasure : ");
      Serial.println(countFlow);
      digitalWrite(heater, LOW); // heater ON
      if (countFlow >= 100) {
        digitalWrite(heater, HIGH);
        countFlow = 0;
      }
    }
  } else {
    digitalWrite(heater, HIGH);  // heater OFF
  }



  // mode 4 display
  lcd.setCursor(0, 0);
  lcd.print("Pick Up Your Noodles");
  lcd.setCursor(0, 1);
  lcd.print(" Water Temp : ");
  lcd.print(tempC);
  lcd.print(" C    ");
  lcd.setCursor(0, 2);
  lcd.print(" Hot Water Is Ready ");
  lcd.setCursor(0, 3);
  lcd.print("   Dispenser Below  ");
}

