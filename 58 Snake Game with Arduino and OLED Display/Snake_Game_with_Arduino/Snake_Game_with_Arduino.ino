#include "snake_game.h"

// Setup function: Runs once at startup
void setup(void)
{
   Serial.begin(9600);
   pinMode(A0, INPUT);
   pinMode(A1, INPUT);
   pinMode(2, INPUT_PULLUP);
   welcome();
   delay(2500);
}

// Main loop: Starts the game when the button is pressed
void loop(void)
{
  if (!digitalRead(2)) // Check if the button is pressed
  {
    snake(); // Start the game
  }
}