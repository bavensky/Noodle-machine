#include <Wire.h>
int data;

//  limit switch motor
// front
#define A1_limit  22
#define A2_limit  23
#define A3_limit  24
#define A4_limit  25
#define A5_limit  26
#define A6_limit  27
// back
#define D1_limit  40
#define D2_limit  41
#define D3_limit  42
#define D4_limit  43
#define D5_limit  44
#define D6_limit  45

//  limit switch noodle
// front
#define B1_limit  28
#define B2_limit  29
#define B3_limit  30
#define B4_limit  31
#define B5_limit  32
#define B6_limit  33
// back
#define C1_limit  34
#define C2_limit  35
#define C3_limit  36
#define C4_limit  37
#define C5_limit  38
#define C6_limit  39

//  limit switch motor press
#define L_press1  7
#define L_press2  6

// motor slide
#define f_motor4  46
#define b_motor4  47
#define b_motor3  48
#define f_motor3  49
#define b_motor2  50
#define f_motor2  51
#define f_motor1  52
#define b_motor1  53

byte positionA = 0, positionB = 0;
byte NowpositionA = 0, NowpositionB = 0;
byte statePress = 0;

void checkPosit() {
  if (digitalRead(A1_limit) == 1) {
    NowpositionA = 1;
  } else if (digitalRead(A2_limit) == 1) {
    NowpositionA = 2;
  } else if (digitalRead(A3_limit) == 1) {
    NowpositionA = 3;
  } else if (digitalRead(A4_limit) == 1) {
    NowpositionA = 4;
  } else if (digitalRead(A5_limit) == 1) {
    NowpositionA = 5;
  } else if (digitalRead(A6_limit) == 1) {
    NowpositionA = 6;
  }

  if (digitalRead(D1_limit) == 1) {
    NowpositionB = 1;
  } else if (digitalRead(D2_limit) == 1) {
    NowpositionB = 2;
  } else if (digitalRead(D3_limit) == 1) {
    NowpositionB = 3;
  } else if (digitalRead(D4_limit) == 1) {
    NowpositionB = 4;
  } else if (digitalRead(D5_limit) == 1) {
    NowpositionB = 5;
  } else if (digitalRead(D6_limit) == 1) {
    NowpositionB = 6;
  }
}

void movePosit(int posi1, int posi2) {
  checkPosit();
  while (NowpositionA > 1) {

  }


}

void initPosit() {
  Serial.print("set zero");
  while (digitalRead(L_press1) != 0) {
    digitalWrite(b_motor1, LOW);
  }
  digitalWrite(b_motor1, HIGH);

  while (digitalRead(L_press2) != 0) {
    digitalWrite(b_motor4, LOW);
  }
  digitalWrite(b_motor4, HIGH);

  while (NowpositionA > 1) {
    checkPosit();
    digitalWrite(b_motor2, LOW);
  }
  digitalWrite(b_motor2, HIGH);

  Serial.println("  done...");
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  data = Wire.read();    // receive byte as an integer
  Serial.println(data);
}

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  
  pinMode(A1_limit, INPUT_PULLUP);
  pinMode(A2_limit, INPUT_PULLUP);
  pinMode(A3_limit, INPUT_PULLUP);
  pinMode(A4_limit, INPUT_PULLUP);
  pinMode(A5_limit, INPUT_PULLUP);
  pinMode(A6_limit, INPUT_PULLUP);

  pinMode(B1_limit, INPUT_PULLUP);
  pinMode(B2_limit, INPUT_PULLUP);
  pinMode(B3_limit, INPUT_PULLUP);
  pinMode(B4_limit, INPUT_PULLUP);
  pinMode(B5_limit, INPUT_PULLUP);
  pinMode(B6_limit, INPUT_PULLUP);

  pinMode(C1_limit, INPUT_PULLUP);
  pinMode(C2_limit, INPUT_PULLUP);
  pinMode(C3_limit, INPUT_PULLUP);
  pinMode(C4_limit, INPUT_PULLUP);
  pinMode(C5_limit, INPUT_PULLUP);
  pinMode(C6_limit, INPUT_PULLUP);

  pinMode(D1_limit, INPUT_PULLUP);
  pinMode(D2_limit, INPUT_PULLUP);
  pinMode(D3_limit, INPUT_PULLUP);
  pinMode(D4_limit, INPUT_PULLUP);
  pinMode(D5_limit, INPUT_PULLUP);
  pinMode(D6_limit, INPUT_PULLUP);

  pinMode(L_press1, INPUT_PULLUP);
  pinMode(L_press2, INPUT_PULLUP);

  pinMode(f_motor1, OUTPUT);
  pinMode(b_motor1, OUTPUT);
  pinMode(f_motor2, OUTPUT);
  pinMode(b_motor2, OUTPUT);
  pinMode(f_motor3, OUTPUT);
  pinMode(b_motor3, OUTPUT);
  pinMode(f_motor4, OUTPUT);
  pinMode(b_motor4, OUTPUT);

  digitalWrite(f_motor1, 1);
  digitalWrite(b_motor1, 1);
  digitalWrite(f_motor2, 1);
  digitalWrite(b_motor2, 1);
  digitalWrite(f_motor3, 1);
  digitalWrite(b_motor3, 1);
  digitalWrite(f_motor4, 1);
  digitalWrite(b_motor4, 1);

  //  digitalWrite(b_motor4, 0);
  //  delay(300);
  //  digitalWrite(b_motor4, 1);

  checkPosit();
  initPosit();

  //  while (NowpositionA > 1) {
  //    checkPosition();
  //    digitalWrite(b_motor2, 0);
  //  } else {
  //    digitalWrite(b_motor2, 1);
  //  }

  //  Serial.println(NowpositionA);
  //  Serial.println(NowpositionB);
  //  delay(2000);
}

void loop() {
  //  Serial.print("Limit sw ");
  //  Serial.print(digitalRead(L_press1));
  //  Serial.print("  ");
  //  Serial.println(digitalRead(L_press2));

  if (Serial.available() > 0) {
    char income = Serial.read();
    Serial.write(income);
    if (income == 'A') {
      Serial.write("ok");
      digitalWrite(f_motor1, LOW);
      delay(12000);
      digitalWrite(f_motor1, HIGH);
      statePress = 1;
    }
  }

  Serial.println("Loop");
  delay(200);

  while (statePress == 1) {
    Serial.println("state");
    digitalWrite(b_motor1, LOW);
    if (digitalRead(L_press1) == 0) {
      digitalWrite(b_motor1, HIGH);
      statePress = 0;
    }
  }

  //  Serial.print(digitalRead(A1_limit));
  //  Serial.print(digitalRead(A2_limit));
  //  Serial.print(digitalRead(A3_limit));
  //  Serial.print(digitalRead(A4_limit));
  //  Serial.print(digitalRead(A5_limit));
  //  Serial.print(digitalRead(A6_limit));
  //  Serial.print("  ");
  //  Serial.print(digitalRead(B1_limit));
  //  Serial.print(digitalRead(B2_limit));
  //  Serial.print(digitalRead(B3_limit));
  //  Serial.print(digitalRead(B4_limit));
  //  Serial.print(digitalRead(B5_limit));
  //  Serial.print(digitalRead(B6_limit));
  //  Serial.print("  ");
  //  Serial.print(digitalRead(C1_limit));
  //  Serial.print(digitalRead(C2_limit));
  //  Serial.print(digitalRead(C3_limit));
  //  Serial.print(digitalRead(C4_limit));
  //  Serial.print(digitalRead(C5_limit));
  //  Serial.print(digitalRead(C6_limit));
  //  Serial.print("  ");
  //  Serial.print(digitalRead(D1_limit));
  //  Serial.print(digitalRead(D2_limit));
  //  Serial.print(digitalRead(D3_limit));
  //  Serial.print(digitalRead(D4_limit));
  //  Serial.print(digitalRead(D5_limit));
  //  Serial.println(digitalRead(D6_limit));

  delay(100);

  //  if (digitalRead(A1_limit) != 1) {
  //    digitalWrite(f_motor2, LOW);
  //  } else {
  //    digitalWrite(f_motor2, HIGH);
  //  }
}
