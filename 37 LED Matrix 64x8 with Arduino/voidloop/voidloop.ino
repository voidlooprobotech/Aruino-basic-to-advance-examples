/* Example code for scrolling text effect on MAX7219 LED dot matrix display with Arduino. More info: https://www.makerguides.com */

// Include the required Arduino libraries:
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define hardware type, size, and output pins:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


void setup() {
  // Intialize the object:
  myDisplay.begin();
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(1);
  // Clear the display:
  myDisplay.displayClear();
  myDisplay.displayText("void loop Robotech and Automation", PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  }
}
