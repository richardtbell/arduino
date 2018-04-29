//We always have to include the library
#include "LedControlMS.h"


/*
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to CS 
 We have only a single MAX72XX.
 */
const int DIN = 12;
const int CLK = 11;
const int CS = 10;
const int NumLEDMatrix = 1
LedControl lc=LedControl(DIN,CLK,CS,NumLEDMatrix);

String digits= "1234567890";
int digitCounter=0;
/* we always wait a bit between updates of the display */
unsigned long delaytime=300;

const int hygrometer = A0;  //Hygrometer sensor analog pin output at pin A0 of Arduino
//Variables 
int value;


void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  Serial.begin (9600);
  Serial.println("Setup");
  digitCounter=0;
  lc.shutdown(0,false);
  /* Set the brightness to a low value */
  lc.setIntensity(0,1);  /* and clear the display */
  lc.clearDisplay(0);

}

int scrollSpeed = 100;
void loop() { 
  value = analogRead(hygrometer);   //Read analog value 
  value = constrain(value,400,1023);  //Keep the ranges!
  value = map(value,400,1023,100,0);  //Map value : 400 will be 100 and 1023 will be 0
  scrollText(String(value));
  delay(1000);
}

void scrollText(String text){
  int len = text.length() * 6;
  int bm [len] = {0};
  int count = 0;
  for (int i=0; i<text.length(); i++) {
    int pos =lc.getCharArrayPosition(text[i]);
    for (int x=0; x<6;x++) {
      bm[count] = alphabetBitmap[pos][x];
      count = count + 1;
    } 
  }
  for (int scroll =0; scroll<len; scroll++) {
     for (int i=scroll; i<len;i++) {
        lc.setRow(0,i-scroll, bm[i]);
    } 
    delay(scrollSpeed);
    lc.clearDisplay(0);
  }  
}

