//We always have to include the library
#include "LedControlMS.h"
#include <TimeLib.h>

/*
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to CS 
 pin 3 is connected to pump circuit
 We have only a single MAX72XX.
 */
const int DIN = 12;
const int CLK = 11;
const int CS = 10;
const int motorPin = 3;
const int hygrometer = A0;  // Hygrometer sensor analog pin output at pin A0 of Arduino

const int NumLEDMatrix = 1;

const int scrollSpeed = 100; // ms 
const int motorSpeed = 255; // value between 0 and 255
const int motorOnTime = 3000; // time to run pump in ms
const int desiredHydration = 80; 
const int ledBrightness = 1; // value between 1 and 15
const int timeBetweenWater = 30; // value in minutes

int startTime;
int value;

LedControl lc=LedControl(DIN,CLK,CS,NumLEDMatrix);

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  Serial.begin (9600);
  Serial.println("Setup");
  lc.shutdown(0,false);
  lc.setIntensity(0,ledBrightness);
  lc.clearDisplay(0);
  startTime = now();
  pinMode(motorPin, OUTPUT);

}

void loop() { 
  value = analogRead(hygrometer);   //Read analog value 
  value = constrain(value,400,1023);  //Keep the ranges!
  value = map(value,400,1023,100,0);  //Map value : 400 will be 100 and 1023 will be 0
  int minSinceWater = hour() * 60 + minute();
  
  scrollText("hydration: " + String(value));
  scrollText("min since water: " + String(minSinceWater));
  delay(1000);
  
  if (value < desiredHydration && minSinceWater >= timeBetweenWater) {
    waterPlant();  
  }
}

void waterPlant(){
  analogWrite(motorPin, motorSpeed); // Turn on
  delay(motorOnTime);
  analogWrite(motorPin, 0); // Turn off
  setTime(startTime);
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

