
#include <LiquidCrystal.h>

int retry = 0;
int LCDpin[6] = {5, 6, 7, 8, 9, 10}; // Digital pins 5, 6, 7, 8, 9, 10 are used
int p1, p2, p3, p4, p5, p6;

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int a = 0; a < 6; a++) {
    for (int b = 0; b < 6; b++) {
      for (int c = 0; c < 6; c++) {
        for (int d = 0; d < 6; d++) {
    for (int e = 0; e < 6; e++) {
      for (int f = 0; f < 6; f++) {
              if (a != b && a != c && a != d && a != e && a != f) {
          if (b != c && b != d && b != e && b != f) {
      if (c != d && c != e && c != f) {
        if (d != e && d != f) {
          if (e != f) {
            p1 = LCDpin[a];
              p2 = LCDpin[b];
            p3 = LCDpin[c];
            p4 = LCDpin[d];
            p5 = LCDpin[e];
            p6 = LCDpin[f];
            testLCD(p1, p2, p3, p4, p5, p6);
                      }
              }
      }
    }
        }
      }
    }
  }
      }
    }
  }
}

void testLCD(int RS, int EN, int D4, int D5, int D6, int D7) {
  retry++;
  Serial.print(retry); // this will help me to see which combination is the right one
  Serial.print(": RS: ");
  Serial.print(RS);
  Serial.print(" EN: ");
  Serial.print(EN);
  Serial.print(" D4: ");
  Serial.print(D4);
  Serial.print(" D5: ");
  Serial.print(D5);
  Serial.print(" D6: ");
  Serial.print(D6);
  Serial.print(" D7: ");
  Serial.println(D7);
  LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
  lcd.begin(16, 2);
  lcd.print("retry: "); // LCD shows the line which I should search for in the serial monitor
  lcd.print(retry);
  delay(1000); // wait before trying next combination
}
