
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
int i = 0;
char *text[] =
{
 "    ",
 "Hello..",
 "World",
 "welcome",
 "to",
 "void",
 "loop",
 "robotech",
 "and",
 "Automation",
 "please",
 "support",
 "me. by",
 "Like",
 "subscribe",
 "and",
 "share",
 "Thanks",
 "for",
 "watching" 
};

textEffect_t texteffect[] =
{
  PA_PRINT,
  PA_WIPE_CURSOR,
  PA_SCAN_HORIZ,
  PA_SCROLL_LEFT,
  PA_WIPE,
  PA_SCROLL_UP_LEFT,
  PA_SCROLL_UP,
  PA_SCROLL_RIGHT,
  PA_GROW_UP,
  PA_SCROLL_LEFT,
  PA_DISSOLVE,
  PA_SCROLL_UP_LEFT,
  PA_MESH,
  
  PA_SCROLL_DOWN_RIGHT,
  PA_SCROLL_RIGHT,
  PA_OPENING_CURSOR,
  PA_SLICE,
  PA_BLINDS,
  PA_RANDOM,
  PA_SCROLL_LEFT
,
  
  /*
   PA_GROW_DOWN,
  PA_SCAN_VERT,
  PA_SCROLL_DOWN_LEFT
  PA_SCROLL_UP_RIGHT,
  
  PA_CLOSING,
  PA_OPENING,
  
  
  PA_CLOSING_CURSOR,
  
  PA_SCROLL_DOWN
  */
};

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  myDisplay.begin();
  myDisplay.setIntensity(0);
 // myDisplay.setTextAlignment(PA_CENTER);
 // myDisplay.setPause(1000);
 // myDisplay.setSpeed(100);
  myDisplay.displayClear();
}
void loop() {
  if (myDisplay.displayAnimate()) {
    
 if (i < sizeof(texteffect)) {
      i++;
    }
    else {
      i = 0;
    }

   myDisplay.displayText(text[i], PA_CENTER, 100, 1000, texteffect[i], texteffect[i]);
    myDisplay.displayReset();
    
 }
}
