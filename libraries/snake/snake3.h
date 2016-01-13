#ifndef snake_h
#define snake_h

#include <avr/pgmspace.h>

//EEPROM
#define E_EASY 1023
#define E_MEDIUM 1022
#define E_HARD 1021
#define E_CRAZY 1020

//MENU
#define START	0
#define MENU	1
#define RESTART 2

//MENU2
#define DIFFICULTY	255
#define SCORE		254
#define FOOD		253

//DIFFICULTY
#define EASY 2
#define MEDIUM 4
#define HARD 6
#define CRAZY 8

//FOOD
#define VINTAGE 0
#define HEART 1

//true-false
#define TRUE	1
#define FALSE	0

//on-off
#ifndef ON

#define ON  1
#define OFF 0

#endif

//MODE
#define NORMAL 255
#define SURVIVAL 125

//KeyPressed
#define A 1
#define B 2
#define NONE 0

//KEYS association
#define keyUp 1
#define keyDown 2
#define keyLeft 0
#define keyRight 3
#define keyA 4
#define keyB 5

//key pressed
#define Pressed(P) ((PINC >> (P)) & 0x01)

#define keyUpPressed (Pressed(keyUp))
#define keyDownPressed (Pressed(keyDown))
#define keyLeftPressed (Pressed(keyLeft))
#define keyRightPressed (Pressed(keyRight))
#define keyAPressed (Pressed(keyA))
#define keyBPressed (Pressed(keyB))

//Bitmap offsets
#define OFFSET_FOOD 0

#define OFFSET_SNVE 8
#define OFFSET_SNHO 16

#define OFFSET_SNDL 24
#define OFFSET_SNUL 32
#define OFFSET_SNUR 40
#define OFFSET_SNDR 48

#define OFFSET_SNHU 56
#define OFFSET_SNHR 64
#define OFFSET_SNHD 72
#define OFFSET_SNHL 80

#define OFFSET_SNTU 88
#define OFFSET_SNTR 96
#define OFFSET_SNTD 104
#define OFFSET_SNTL 112

#define OFFSET_FOO2 120

//Time const
#define TIME 10

//Arena DIM
#define ARENA_X		16
#define ARENA_Y		8
#define ARENA_X8	128
#define ARENA_Y8	64
#define ARENA_X0	0
#define ARENA_Y0	0

//Arena CODE
#define CODE_EMPTY   0
#define CODE_FOOD  128
#define CODE_SNAKE 255

//Direction
#define UP		0
#define RIGHT	1
#define DOWN	2
#define LEFT	3

//Snake max lenght
#define LENMAX 128 //16*8

//end and score const
#define END 255
#define SCORE_STEP 1

//bitmap pixel
#define BMP_X	8
#define BMP_Y	8

//SELECTORS
#define LEFT_SEL	126
#define RIGHT_SEL	127

//bitmap
static const uint8_t BITMAP[] = \
   {0b00000000,  // food
	0b00000000,
	0b00011000,
	0b00100100,
	0b00100100,
	0b00011000,
	0b00000000,
	0b00000000,
	
	0b00000000,  // snake_vertical
	0b00000000,
	0b11101110,
	0b11101110,
	0b01110111,
	0b01110111,
	0b00000000,
	0b00000000,
	
	0b00001100,  // snake_horizontal
	0b00111100,
	0b00111100,
	0b00110000,
	0b00001100,
	0b00111100,
	0b00111100,
	0b00110000,
	
	0b00001100,  // snake_down_left
	0b00111100,
	0b11111100,
	0b11101000,
	0b01111000,
	0b01100000,
	0b00000000,
	0b00000000,
	
	0b00001100,  // snake_up_left
	0b00111100,
	0b00111110,
	0b00010110,
	0b00011111,
	0b00000111,
	0b00000000,
	0b00000000,
	
	0b00000000,  // snake_up_right
	0b00000000,
	0b00000110,
	0b00011110,
	0b00010111,
	0b00111111,
	0b00111100,
	0b00110000,
	
	0b00000000,  // snake_down_right
	0b00000000,
	0b11100000,
	0b11111000,
	0b01101000,
	0b01111100,
	0b00111100,
	0b00110000,
	
	0b00000000,  // snake_head_up   // link up, head looks down
	0b00111000,
	0b01001110,
	0b01111110,
	0b01111111,
	0b01001111,
	0b00110000,
	0b00000000,
	
	0b00000000,  // snake_head_right  // link right
	0b00111100,
	0b01011010,
	0b01011010,
	0b01111110,
	0b00111100,
	0b00111100,
	0b00110000,
	
	0b00000000,  // snake_head_down  // link down
	0b00011100,
	0b11110010,
	0b11111110,
	0b01111110,
	0b01110010,
	0b00011100,
	0b00000000,
	
	0b00001100,  // snake_head_left  // link left
	0b00111100,
	0b00111100,
	0b01111110,
	0b01011010,
	0b01011010,
	0b00111100,
	0b00000000,
	
	0b00000000,  // snake_tail_up   // link up
	0b00000000,
	0b00101110,
	0b11101110,
	0b11110111,
	0b00110111,
	0b00000000,
	0b00000000,
	
	0b00011000,  // snake_tail_right  // link right
	0b00011000,
	0b00111100,
	0b00110000,
	0b00001100,
	0b00111100,
	0b00111100,
	0b00110000,
	
	0b00000000,  // snake_tail_down  // link down
	0b00000000,
	0b11101100,
	0b11101111,
	0b01110111,
	0b01110100,
	0b00000000,
	0b00000000,
	
	0b00001100,  // snake_tail_left  // link left
	0b00111100,
	0b00111100,
	0b00110000,
	0b00001100,
	0b00111100,
	0b00011000,
	0b00011000,
	
	0b00011110, //food heart
	0b00100001,	
	0b01000001,
	0b10000010,
	0b10000010,
	0b01000001,
	0b00100001,
	0b00011110};

#endif
