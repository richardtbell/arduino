//We always have to include the library
#include "LedControlMS.h"


/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
#define NBR_MTX 1 
LedControl lc=LedControl(12,11,10, NBR_MTX);

String digits= "1234567890";
int digitCounter=0;
/* we always wait a bit between updates of the display */
unsigned long delaytime=300;


void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  Serial.begin (9600);
  Serial.println("Setup");
  digitCounter=0;
  for (int i=0; i< NBR_MTX; i++){
    lc.shutdown(i,false);
  /* Set the brightness to a medium values */
    lc.setIntensity(i,1);  /* and clear the display */
    lc.clearDisplay(i);
  }
}

int scrollSpeed = 200;
void loop() { 
  scrollText("hello world!");
  delay(200);
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

