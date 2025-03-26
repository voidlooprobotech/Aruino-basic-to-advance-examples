#include "snake_game.h"
#include <Arduino.h>

// Initialize game variables
int box_x = 0;
int box_y = 0;
int box_x_length = 98;
int box_y_length = 62;
int snake_max_length = 100;
int snake_x[100];
int snake_y[100];
int snake_body_width = 3;
int food_x;
int food_y;
int snake_length = 3;
unsigned int game_speed;

// Initialize the OLED display
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

// Variable to store the last valid direction
int last_direction = RIGHT; // Default direction

// Function to display the welcome screen
void welcome()
{
   u8g.firstPage();
   do
   {
     u8g.setFont(u8g_font_gdr14r);
     u8g.setPrintPos(0, 35);
     u8g.print("Snake Game");
   } while (u8g.nextPage());
}

// Function to read joystick input
int read_key()
{
   int xPosition = analogRead(A0);
   int yPosition = analogRead(A1);
   int buttonState = digitalRead(2);

   if (yPosition < 40) return UP;
   if (yPosition > 600) return DOWN;
   if (xPosition < 400) return LEFT;
   if (xPosition > 600) return RIGHT;
   if (buttonState == LOW) return A;

   return -1; // No valid input (neutral position)
}

// Function to display the game over screen
void game_over()
{
   u8g.firstPage();
   do
   {
     u8g.setFont(u8g_font_gdr14r);
     u8g.setPrintPos(0, 40);
     u8g.print("GAME OVER!");
   } while (u8g.nextPage());

   // Reset the snake's length and position
   snake_length = 3;
   snake_x[0] = 15; snake_y[0] = 15;
   snake_x[1] = snake_x[0] - 1; snake_y[1] = snake_y[0];
   snake_x[2] = snake_x[1] - 1; snake_y[2] = snake_y[1];
}

// Main game loop
void snake()
{
   int flag = 1;
   snake_x[0] = 15; snake_y[0] = 15;
   snake_x[1] = snake_x[0] - 1; snake_y[1] = snake_y[0];
   snake_x[2] = snake_x[1] - 1; snake_y[2] = snake_y[1];
   game_speed = 130;
   food();

   while (flag)
   {
     snake_frame(game_speed);
     delay(game_speed);

     int current_direction = read_key();

     // Update the direction only if a valid input is detected
     if (current_direction != -1)
     {
       // Prevent the snake from reversing direction
       if (!(last_direction == RIGHT && current_direction == LEFT) &&
           !(last_direction == LEFT && current_direction == RIGHT) &&
           !(last_direction == UP && current_direction == DOWN) &&
           !(last_direction == DOWN && current_direction == UP))
       {
         last_direction = current_direction;
       }
     }

     // Check if the snake eats food
     if (snake_eat_food(last_direction) == 1)
     {
       food();
       game_speed = (snake_length < 10) ? 130 : (snake_length < 30) ? 100 : (snake_length < 50) ? 70 : 30;
     }
     // Check if the snake hits the wall
     else if (snake_knock_wall(last_direction))
     {
       game_over();
       flag = 0;
     }
     else
     {
       change_con(last_direction);
     }
   }
}

// Static function to draw the game frame
static void snake_frame(int s)
{
   u8g.firstPage();
   do
   {
     u8g.drawFrame(box_x, box_y, box_x_length, box_y_length);
     u8g.setFont(u8g_font_5x7);
     u8g.setPrintPos(box_x_length + 1, 6);
     u8g.print("Score");
     u8g.setPrintPos(box_x_length + 15, 15);
     u8g.print((snake_length - 3) * 5);
     u8g.setPrintPos(box_x_length + 1, 25);
     u8g.print("Speed");
     u8g.setPrintPos(box_x_length + 10, 37);
     u8g.print(s);
     u8g.drawFrame(food_x * snake_body_width + 1, food_y * snake_body_width + 1, snake_body_width, snake_body_width);

     for (int i = 0; i < snake_length; i++)
     {
       if (i == 0)
         u8g.drawBox(snake_x[i] * snake_body_width + 1, snake_y[i] * snake_body_width + 1, snake_body_width, snake_body_width);
       else
         u8g.drawFrame(snake_x[i] * snake_body_width + 1, snake_y[i] * snake_body_width + 1, snake_body_width, snake_body_width);
     }
   } while (u8g.nextPage());
}

// Static function to generate food at a random position
static void food()
{
   bool flag = true;
   while (flag)
   {
     food_x = random(0, (box_x_length - 2) / 3);
     food_y = random(0, (box_y_length - 2) / 3);

     flag = false;
     for (int i = 0; i < snake_length; i++)
       if ((food_x == snake_x[i]) && (food_y == snake_y[i]))
         flag = true;
   }
}

// Static function to update the snake's position
static void change_con(int DIR)
{
   int temp_x[snake_length];
   int temp_y[snake_length];

   for (int i = 0; i < snake_length; i++)
   {
     temp_x[i] = snake_x[i];
     temp_y[i] = snake_y[i];
   }

   if (DIR == RIGHT) snake_x[0] += 1;
   if (DIR == LEFT) snake_x[0] -= 1;
   if (DIR == UP) snake_y[0] -= 1;
   if (DIR == DOWN) snake_y[0] += 1;

   for (int i = 1; i < snake_length; i++)
   {
     snake_x[i] = temp_x[i - 1];
     snake_y[i] = temp_y[i - 1];
   }
}

// Static function to check if the snake eats food
static int snake_eat_food(int dir)
{
   int x_temp = snake_x[0];
   int y_temp = snake_y[0];

   if (dir == UP) y_temp -= 1;
   if (dir == DOWN) y_temp += 1;
   if (dir == LEFT) x_temp -= 1;
   if (dir == RIGHT) x_temp += 1;

   if ((x_temp == food_x) && (y_temp == food_y))
   {
     snake_length += 1;
     snake_x[snake_length - 1] = food_x;
     snake_y[snake_length - 1] = food_y;
     return 1;
   }
   return 0;
}

// Static function to check if the snake hits the wall
static int snake_knock_wall(int dir)
{
   int x_temp = snake_x[0];
   int y_temp = snake_y[0];

   if (dir == UP) y_temp -= 1;
   if (dir == DOWN) y_temp += 1;
   if (dir == LEFT) x_temp -= 1;
   if (dir == RIGHT) x_temp += 1;

   return (x_temp < 0 || x_temp > 31 || y_temp < 0 || y_temp > 19) ? 1 : 0;
}