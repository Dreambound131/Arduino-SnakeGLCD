/* food bitmap file for GLCD library */
/* Bitmap created from food.png      */
/* Date: 7 May 2015      */
/* Image Pixels = 16    */
/* Image Bytes  = 4     */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef food_H
#define food_H

static const uint8_t food[] PROGMEM = {
  4, // width
  4, // height

  /* page 0 (lines 0-7) */
  0b0010,
  0b0101,
  0b0010,
  0b0000};
  
static const uint8_t clr[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
	0b0000,
	0b0000,
	0b0000,
0b0000};

static const uint8_t snbl[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0110, //snake body left
0b0100,
0b0010,
0b0110,};
	
static const uint8_t snbr[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0110,	//snake body right
0b0010,
0b0100,
0b0110,};

static const uint8_t sntr[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
	0b0100, //snake tail right
	0b0100,
	0b0110,
	0b0110,};

static const uint8_t sntl[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
	0b0110,	//snake tail left
	0b0110,
	0b0100,
	0b0100,};

static const uint8_t sneu[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
	0b1010, //snake eat up
	0b0100,
	0b1100,
	0b0010,};

static const uint8_t sned[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
	0b0101, //snake eat down
	0b0010,
	0b0011,
	0b0100,};

static const uint8_t sner[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
	0b0101, //snake eat right
	0b0110,
	0b1001,
	0b0000,};

static const uint8_t snel[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
	0b0000, //snake eat left
	0b1001,
	0b0110,
	0b0101,};

static const uint8_t snhd[] PROGMEM = {
	4, // width
	4, // height

	0b0001, //snake head down
	0b0110,
	0b0111,
	0b0000,/* page 0 (lines 0-7) */
};
static const uint8_t snhu[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
	0b1000, //snake head up
	0b0110,
	0b1110,
	0b0000,};

static const uint8_t snhr[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0101, //snake head right
0b0110,
0b0110,
0b0000,
};

static const uint8_t snhl[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0000, //snake head left
0b0110,
0b0110,
0b0101,};

static const uint8_t snbd[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0000, //snake body down
0b1011,
0b1101,
0b0000,};

static const uint8_t snbu[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0000, //snake body up
0b1101,
0b1011,
0b0000,};

static const uint8_t sntd[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
	0b0000, //snake tail down
	0b1100,
	0b1111,
	0b0000,};

static const uint8_t sntu[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0000, //snake tail up
0b0011,
0b1111,
0b0000,
};


static const uint8_t selu[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0110, //snake eaten left/up
0b1101,
0b1011,
0b0110,
};

static const uint8_t serd[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0110, //snake eaten right/down
0b1011,
0b1101,
0b0110,
};

static const uint8_t snul[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0110, //snake up-left
0b0101,
0b0011,
0b0000,
};

static const uint8_t sndl[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0110, //snake down-left
0b1010,
0b1100,
0b0000,
};

static const uint8_t sndr[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0000, //snake down-right
0b1100,
0b1010,
0b0110,
};

static const uint8_t snur[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0000, //snake up-right
0b0011,
0b0101,
0b0110,
};

static const uint8_t sedl[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b1110, //snake eaten down-left
0b1010,
0b1100,
0b0000,
};

static const uint8_t sedr[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0000, //snake eaten down-right
0b1100,
0b1010,
0b1110,
};

static const uint8_t seul[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0111, //snake eaten left-up
0b0101,
0b0011,
0b0000,
};

static const uint8_t seru[] PROGMEM = {
	4, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0000, //snake eaten right-up
0b0011,
0b0101,
0b0111  
};

static const uint8_t spyder[] PROGMEM = {
	8, // width
	4, // height

	/* page 0 (lines 0-7) */
0b1110, //spyder
0b0010,
0b1111,
0b0111,
0b0111,
0b1111,
0b0010,
0b1110,
};

static const uint8_t turtle[] PROGMEM = {
	8, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0011, //turtle
0b0011,
0b0100,
0b0100,
0b1110,
0b0111,
0b1110,
0b0100,
};

static const uint8_t lizard[] PROGMEM = {
	8, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0110, //lizard
0b0101,
0b1110,
0b0111,
0b0110,
0b1111,
0b0110,
0b0100,
};

static const uint8_t centipede[] PROGMEM = {
	8, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0110, //centipede
0b1100,
0b0100,
0b1100,
0b0100,
0b1100,
0b0100,
0b1100,
};

static const uint8_t bird[] PROGMEM = {
	8, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0000, //bird
0b0100,
0b0110,
0b1101,
0b1111,
0b1110,
0b1100,
0b0110,
};

static const uint8_t snail[] PROGMEM = {
	8, // width
	4, // height

	/* page 0 (lines 0-7) */
0b0110, //snail
0b1000,
0b1100,
0b1110,
0b1111,
0b1101,
0b1110,
0b1000
};

#endif
