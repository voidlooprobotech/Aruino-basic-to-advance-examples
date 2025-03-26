#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "U8glib.h"

// Constants for joystick directions
#define RIGHT 0
#define UP    1
#define LEFT  2
#define DOWN  3
#define A     4

// Game variables
extern int box_x, box_y, box_x_length, box_y_length;
extern int snake_max_length;
extern int snake_x[100], snake_y[100];
extern int snake_body_width;
extern int food_x, food_y;
extern int snake_length;
extern unsigned int game_speed;

// Function declarations
void welcome();
int read_key();
void game_over();
void snake();
void snake_frame(int s);
void food();
void change_con(int DIR);
int snake_eat_food(int dir);
int snake_knock_wall(int dir);

#endif