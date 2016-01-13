/*
 * Snake_GLCD.ino
 *
 * Created: 30/04/2015 12:39:43 AM
 * Author: Daniele
 * Based on PIC18F4550 Snake Game on 128x64 GLCD v2 
 * http://microelefun.blogspot.ro/2012/11/pic18f4550-snake-game-on-128x64-glcd-v2.html
 *
 */ 
 
#include <glcd.h>
#include <fonts/allFonts.h>
#include <EEPROM.h>
#include <snake3.h>

//uint8_t pointerX = startX, pointerY = startY;

/*var*/
uint8_t snakeDir = RIGHT;
uint8_t arena[ARENA_X][ARENA_Y];
uint8_t snakeX[LENMAX];
uint8_t snakeY[LENMAX];
uint8_t score;
uint8_t snakeLen;
uint8_t lap=30;
uint8_t best_easy = 0, best_medium = 0, best_hard = 0, best_crazy = 0;
uint8_t difficulty=EASY;
uint8_t start = MENU;
uint8_t eeprom = OFF;
uint8_t food = OFFSET_FOOD;

void inline put_food() /*put food randomly in the arena*/
{
	uint8_t x, y;
	while(true) /*repeat until it found a free spot to place the food*/
	{
		x = random(ARENA_X); /*set random x and y*/
		y = random(ARENA_Y); 
		if(arena[x][y]!=CODE_SNAKE) /*put the food at XY only if the snake isn't in the same location*/
		{
			arena[x][y] = CODE_FOOD;
			break;
		}
	}
}

void inline arena_clear() 
{
	uint8_t x, y;
	for(x=0; x<ARENA_X; x++)
		for(y=0; y<ARENA_Y; y++)
			arena[x][y] = CODE_EMPTY;
}

void inline glcdUpdate() 
{
	uint8_t x, y, code, i;
	uint8_t bitmapOffset;
	
	for(y = 0; y < ARENA_Y; y++) 
	{	
		for(x = 0; x < ARENA_X; x++) 
		{
			code = arena[x][y];
			
			if(code==CODE_SNAKE) 
			{
				bitmapOffset = snakeBitmapOffset(x, y);
				GLCD.GotoXY(x*8, y*8);
				for(i=0; i<8; i++)
					GLCD.WriteData(BITMAP[bitmapOffset+i]);
			}
			else if(code==CODE_EMPTY) 
			{
					GLCD.GotoXY(x*8, y*8);
					for(i=0; i<8; i++)
						GLCD.WriteData(0x00);
			}
			else if(code==CODE_FOOD) 
			{
				GLCD.GotoXY(x*8, y*8);
				for(i=0; i<8; i++)
					GLCD.WriteData(BITMAP[food+i]);
			}	
		}	
	}
	GLCD.DrawRect(0,0,127,63);
}

uint8_t inline move_snake() 
{
	char tail_x, tail_y, head_x, head_y;
	uint8_t i;
	
	tail_x = snakeX[snakeLen-1];
	tail_y = snakeY[snakeLen-1];
	
	
	for(i=snakeLen-1; i>0; i--) 
	{
		snakeX[i] = snakeX[i-1];
		snakeY[i] = snakeY[i-1];
	}
	
	head_x = snakeX[0];
	head_y = snakeY[0];
	
	switch(snakeDir)
	 {
		case	UP:	head_y--; break;
		case RIGHT:	head_x++; break;
		case  DOWN:	head_y++; break;
		case  LEFT:	head_x--; break;
	}
	
	if(head_x < 0) //no else because of return
	return END;
	
	if(head_y < 0)
	return END;
	
	if(head_x >= ARENA_X)
	return END;
	
	if(head_y >= ARENA_Y)
	return END;
	
	if(arena[head_x][head_y] == CODE_SNAKE) return END;
	
	snakeX[0] = head_x;
	snakeY[0] = head_y;
	
	if(arena[head_x][head_y] != CODE_FOOD) 
	{  // nothing eaten
		arena[tail_x][tail_y] = CODE_EMPTY;  // cut tail
	}
	
	if(arena[head_x][head_y] == CODE_FOOD) 
	{
		snakeX[snakeLen] = tail_x;
		snakeY[snakeLen] = tail_y;
		snakeLen++;
		arena[head_x][head_y] = CODE_SNAKE;  // add head
		return SCORE;
	}
	
	
	arena[head_x][head_y] = CODE_SNAKE;  // add head
	return 0;
	
}

uint8_t inline snakeBitmapOffset(uint8_t x, uint8_t y)
{
	uint8_t i;
	
	i = 0;
	while(true)
	{
		if(snakeX[i]==x && snakeY[i]==y) break;
		i++;
	}
	
	if(i==0)
	{
		if(snakeX[i+1]==x+1) return OFFSET_SNHR;
		if(snakeX[i+1]==x-1) return OFFSET_SNHL;
		if(snakeY[i+1]==y+1) return OFFSET_SNHD;
		if(snakeY[i+1]==y-1) return OFFSET_SNHU;
	}
	
	if(i==snakeLen-1)
	{
		if(snakeX[i-1]==x+1) return OFFSET_SNTR;
		if(snakeX[i-1]==x-1) return OFFSET_SNTL;
		if(snakeY[i-1]==y+1) return OFFSET_SNTD;
		if(snakeY[i-1]==y-1) return OFFSET_SNTU;
	}
	
	if(snakeX[i+1]==x && snakeX[i-1]==x) return OFFSET_SNVE;
	if(snakeY[i+1]==y && snakeY[i-1]==y) return OFFSET_SNHO;
	
	
	if(snakeX[i+1]==x+1 && snakeY[i-1]==y+1) return OFFSET_SNDR;
	if(snakeX[i-1]==x+1 && snakeY[i+1]==y+1) return OFFSET_SNDR;
	
	if(snakeX[i+1]==x-1 && snakeY[i-1]==y+1) return OFFSET_SNDL;
	if(snakeX[i-1]==x-1 && snakeY[i+1]==y+1) return OFFSET_SNDL;
	
	if(snakeX[i+1]==x+1 && snakeY[i-1]==y-1) return OFFSET_SNUR;
	if(snakeX[i-1]==x+1 && snakeY[i+1]==y-1) return OFFSET_SNUR;
	
	if(snakeX[i+1]==x-1 && snakeY[i-1]==y-1) return OFFSET_SNUL;
	if(snakeX[i-1]==x-1 && snakeY[i+1]==y-1) return OFFSET_SNUL;
	
	return OFFSET_SNVE;
}

uint8_t inline refreshSnakeDir() 
{
	uint8_t oldDir;
	oldDir = snakeDir;
	if(!keyUpPressed) snakeDir = UP;
	else if(!keyRightPressed) snakeDir = RIGHT;
	else if(!keyDownPressed) snakeDir = DOWN;
	else if(!keyLeftPressed) snakeDir = LEFT;
	if(oldDir!=snakeDir && ((snakeDir == LEFT && oldDir != RIGHT) || (snakeDir == RIGHT && oldDir != LEFT) || (snakeDir == DOWN && oldDir != UP) || (snakeDir == UP && oldDir != DOWN)))
		return true;
	else
	{
		snakeDir = oldDir;
		return false;
	}
}

void inline select()
{
	GLCD.SelectFont(System5x7);
	GLCD.CursorToXY(0, 56);
	GLCD.print("A-select");
}

void inline back()
{
	GLCD.SelectFont(System5x7);
	GLCD.CursorToXY(92, 56);
	GLCD.print("B-back");
}

void inline menu_op(uint8_t sel)
{
		GLCD.SelectFont(Arial14);
		if(sel == START)
		{
			GLCD.SetFontColor(WHITE);
			GLCD.DrawVLine(40, 15, 11);
		}
		else 
		{
			GLCD.SetFontColor(BLACK);
			GLCD.DrawVLine(40, 15, 11, WHITE);
		}
		GLCD.CursorToXY(41, 15);
		GLCD.print("START");
		GLCD.FillRect(39, 27, 50, 2, WHITE);
		if(sel == MENU)
		{ 
			GLCD.SetFontColor(WHITE);
			GLCD.DrawVLine(44, 35, 11);
		}
		else 
		{
			GLCD.SetFontColor(BLACK);
			GLCD.DrawVLine(44, 35, 11, WHITE);
		}
		GLCD.CursorToXY(45, 35);
		GLCD.print("MENU");
		GLCD.FillRect(44, 47, 50, 2, WHITE);
		
		select();
}

void inline menu_menu_op(uint8_t sel)
{
	GLCD.SelectFont(Arial14);
	if(sel == SCORE)
	{
		GLCD.SetFontColor(WHITE);
		GLCD.DrawVLine(25, 6, 11);
	}
	else
	{
		GLCD.SetFontColor(BLACK);
		GLCD.DrawVLine(25, 6, 11, WHITE);
	}
	GLCD.CursorToXY(26, 6);
	GLCD.print("BEST SCORE");
	GLCD.FillRect(25, 18, 100, 2, WHITE);
	
	if(sel == DIFFICULTY)
	{
		GLCD.SetFontColor(WHITE);
		GLCD.DrawVLine(28, 24, 11);
	}
	else
	{
		GLCD.SetFontColor(BLACK);
		GLCD.DrawVLine(28, 24, 11, WHITE);
	}
	GLCD.CursorToXY(29, 24); 
	GLCD.print("DIFFICULTY");
	GLCD.FillRect(28, 36, 100, 2, WHITE);
	
	if(sel == FOOD)
	{
		GLCD.SetFontColor(WHITE);
		GLCD.DrawVLine(44, 42, 11);
	}
	else
	{
		GLCD.SetFontColor(BLACK);
		GLCD.DrawVLine(44, 42, 11, WHITE);
	}
	GLCD.CursorToXY(45, 42);
	GLCD.print("FOOD");
	GLCD.FillRect(44, 54, 50, 2, WHITE);
	
	select();
	back();
}

void inline menu_sco_op(uint8_t sel)
{
	uint8_t best_score = 0;
	if (sel == EASY)
		best_score = best_easy;
	else if (sel == MEDIUM)
		best_score = best_medium;
	else if (sel == HARD)
		best_score = best_hard;
	else if (sel == CRAZY)
	best_score = best_crazy;
	GLCD.SelectFont(fixednums15x31);
	if (best_score < 10) GLCD.CursorToXY(56, 15);
	else if (best_score < 100) GLCD.CursorToXY(48, 15);
	else GLCD.CursorToXY(36, 15);
	GLCD.print(best_score);
	back();
}

void inline menu_dif_op(uint8_t sel)
{
	GLCD.SelectFont(Arial14);
	
	if(sel == EASY)
	{
		GLCD.SetFontColor(WHITE);
		GLCD.DrawVLine(46, 0, 11);
	}
	else
	{
		GLCD.SetFontColor(BLACK);
		GLCD.DrawVLine(46, 0, 11, WHITE);
	}
	GLCD.CursorToXY(47, 0);
	GLCD.print("EASY");
	GLCD.FillRect(46, 12, 50, 2, WHITE);
	
	if(sel == MEDIUM)
	{
		GLCD.SetFontColor(WHITE);
		GLCD.DrawVLine(40, 14, 11);
	}
	else
	{
		GLCD.SetFontColor(BLACK);
		GLCD.DrawVLine(40, 14, 11, WHITE);
	}
	GLCD.CursorToXY(41, 14);
	GLCD.print("MEDIUM");
	GLCD.FillRect(40, 26, 100, 2, WHITE);
	
	if(sel == HARD)
	{
		GLCD.SetFontColor(WHITE);
		GLCD.DrawVLine(46, 28, 11);
	}
	else
	{
		GLCD.SetFontColor(BLACK);
		GLCD.DrawVLine(46, 28, 11, WHITE);
	}
	GLCD.CursorToXY(47, 28);
	GLCD.print("HARD");
	GLCD.FillRect(46, 40, 50, 2, WHITE);
	
	if(sel == CRAZY)
	{
		GLCD.SetFontColor(WHITE);
		GLCD.DrawVLine(40, 42, 11);
	}
	else
	{
		GLCD.SetFontColor(BLACK);
		GLCD.DrawVLine(40, 42, 11, WHITE);
	}
	GLCD.CursorToXY(41, 42);
	GLCD.print("CRAZY");
	GLCD.FillRect(39, 54, 50, 2, WHITE);
	
	select();
	back();
}

void inline menu_food_op(uint8_t sel)
{
	uint8_t j;
	
	if(sel == VINTAGE)
	{
		GLCD.DrawVLine(55,14,9);
	}
	else
	{
		GLCD.DrawVLine(55,14,9, WHITE);
	}
	
	GLCD.GotoXY(60,15);
	for (j=0; j < 8; j++)
		GLCD.WriteData(BITMAP[OFFSET_FOOD + j]);
	
	if(sel == HEART)
	{
		GLCD.DrawVLine(55,34,9);
	}
	else
	{
		GLCD.DrawVLine(55,34,9, WHITE);
	}	
	
	GLCD.GotoXY(60,35);
	for (j=0; j < 8; j++)
		GLCD.WriteData(BITMAP[OFFSET_FOO2 + j]);
	
	select();
	back();
}

void inline menu()
{
	uint8_t sel = START;
	uint8_t oldSel;
	
	GLCD.ClearScreen();
	
	menu_op(sel);
	
	while(!keyAPressed == 0)
	{
		oldSel = sel;
		if (!keyDownPressed) sel=MENU;
		delay(TIME);
		if (!keyUpPressed) sel=START;
		delay(TIME);
		
		if (oldSel!=sel) menu_op(sel);
	}
	while(!keyAPressed) delay(TIME);
	if (sel == START) return;
	
	menu_menu();
}

void inline menu_menu()
{
	uint8_t sel = SCORE;
	uint8_t oldSel;
	uint8_t keyPressed = NONE;
	
	GLCD.ClearScreen();
		
	menu_menu_op(sel);
	while (true)
	{
		oldSel = sel;
		if (!keyUpPressed && sel == FOOD)
		{ 
			sel = DIFFICULTY;
			while(!keyUpPressed) delay(TIME);
		}
		else if (!keyUpPressed && sel == DIFFICULTY)
		{
			sel = SCORE;
			while(!keyUpPressed) delay(TIME);
		}
		else if (!keyDownPressed && sel == SCORE) 
		{
			sel = DIFFICULTY;
			while(!keyDownPressed) delay(TIME);
		}
		else if (!keyDownPressed && sel == DIFFICULTY)
		{
			sel = FOOD;
			while(!keyDownPressed) delay(TIME);
		}
		if (oldSel != sel)
		{ 
			menu_menu_op(sel);
		}
		
		delay(TIME);
		
		if (!keyAPressed)
		{
			keyPressed = A;
			while(!keyAPressed) delay(TIME);
			break;
		}
		
		if (!keyBPressed)
		{
			keyPressed = B;
			while(!keyBPressed) delay(TIME);
			break;
		}
	}
	if (keyPressed == B) menu();
	else if (sel == DIFFICULTY) menu_dif();
	else if (sel == SCORE) menu_pre_sco();
	else if (sel == FOOD) menu_food();
}

void inline menu_pre_sco()
{
	uint8_t sel;
	uint8_t oldSel;
	uint8_t keyPressed = NONE;
	
	sel = difficulty;
	
	GLCD.ClearScreen();
	menu_dif_op(sel);
	while (true)
	{
		oldSel = sel;
		if (!keyUpPressed && sel == CRAZY)
		{
			sel = HARD;
			while(!keyUpPressed) delay(TIME);
		}
		else if (!keyUpPressed && sel == HARD)
		{
			sel = MEDIUM;
			while(!keyUpPressed) delay(TIME);
		}
		else if (!keyUpPressed && sel == MEDIUM)
		{
			sel = EASY;
			while(!keyUpPressed) delay(TIME);
		}
		else if (!keyDownPressed && sel == EASY)
		{
			sel = MEDIUM;
			while(!keyDownPressed) delay(TIME);
		}
		else if (!keyDownPressed && sel == MEDIUM)
		{
			sel = HARD;
			while(!keyDownPressed) delay(TIME);
		}
		else if (!keyDownPressed && sel == HARD)
		{
			sel = CRAZY;
			while(!keyDownPressed) delay(TIME);
		}
		if (oldSel != sel)
		{
			menu_dif_op(sel);
		}
		
		delay(TIME);
		
		if (!keyAPressed)
		{
			keyPressed = A;
			while(!keyAPressed) delay(TIME);
			break;
		}
		
		if (!keyBPressed)
		{
			keyPressed = B;
			while(!keyBPressed) delay(TIME);
			break;
		}
	}
	if (keyPressed == A)
		menu_sco(sel);
	else menu_menu();
}

void inline menu_sco(uint8_t sel)
{
	GLCD.ClearScreen();
	menu_sco_op(sel);
	while (!keyBPressed == 0) delay(TIME);
	while (!keyBPressed) delay(TIME);
	menu_pre_sco();
}

void inline menu_dif()
{
	uint8_t sel;
	uint8_t oldSel;
	uint8_t keyPressed = NONE;
	
	sel = difficulty;
	
	GLCD.ClearScreen();
	menu_dif_op(sel);
	while (true)
	{
		oldSel = sel;
		if (!keyUpPressed && sel == CRAZY)
		{
			sel = HARD;
			while(!keyUpPressed) delay(TIME);
		}
		else if (!keyUpPressed && sel == HARD)
		{
			sel = MEDIUM;
			while(!keyUpPressed) delay(TIME);
		}
		else if (!keyUpPressed && sel == MEDIUM)
		{
			sel = EASY;
			while(!keyUpPressed) delay(TIME);
		}
		else if (!keyDownPressed && sel == EASY)
		{
			sel = MEDIUM;
			while(!keyDownPressed) delay(TIME);
		}
		else if (!keyDownPressed && sel == MEDIUM)
		{
			sel = HARD;
			while(!keyDownPressed) delay(TIME);
		}
		else if (!keyDownPressed && sel == HARD)
		{
			sel = CRAZY;
			while(!keyDownPressed) delay(TIME);
		}
		if (oldSel != sel)
		{
			menu_dif_op(sel);
		}
		
		delay(TIME);
		
		if (!keyAPressed)
		{
			keyPressed = A;
			while(!keyAPressed) delay(TIME);
			break;
		}
		
		if (!keyBPressed)
		{
			keyPressed = B;
			while(!keyBPressed) delay(TIME);
			break;
		}
	}
	if (keyPressed == A)
		if(sel == EASY) difficulty = EASY;
		else if(sel == MEDIUM) difficulty = MEDIUM;
		else if(sel == HARD) difficulty = HARD;
		else if(sel == CRAZY) difficulty = CRAZY;
	
	menu_menu();
}

void inline menu_food()
{
	uint8_t sel;
	uint8_t oldSel;
	uint8_t keyPressed;
	
	if (food == OFFSET_FOOD) sel = VINTAGE;
	else sel = HEART;
	
	GLCD.ClearScreen();
	menu_food_op(sel);
	
	while(true)
	{
		oldSel = sel;
		
		if(!keyUpPressed)
		{
			sel = VINTAGE;
			while(!keyUpPressed) delay(TIME);
		}
		else if(!keyDownPressed)
		{
			sel = HEART;
			while(!keyDownPressed) delay(TIME);
		}
		
		if (oldSel != sel)
		{
			menu_food_op(sel);
		}
		delay(TIME);
		
		if (!keyAPressed)
		{
			keyPressed = A;
			while(!keyAPressed) delay(TIME);
			break;
		}
		
		if (!keyBPressed)
		{
			keyPressed = B;
			while(!keyBPressed) delay(TIME);
			break;
		}
	}
	if (keyPressed == A)
		if (sel == VINTAGE) food = OFFSET_FOOD;
		else food = OFFSET_FOO2;
	
	menu_menu();
}

void inline lap_choice()
{
	if (difficulty == EASY) lap = 30;
	else if (difficulty == MEDIUM) lap = 20;
	else if (difficulty == HARD) lap = 10;
	else if (difficulty == CRAZY) lap = 6;
}

void setup()
{
	/* add setup code here, setup code runs once when the processor starts */	
	//var	
	uint8_t i;
	uint8_t res;
	uint8_t dirChanged;
	
	score = 0;
	
	randomSeed(analogRead(A7));
	
	DDRC &= ~0x3F;
	PORTC |= 0x3F;
	
	//clear eeprom used bytes
	if (!keyAPressed && !keyBPressed && !keyDownPressed && eeprom == OFF)
		for (i=0; i<4; i++)
		{
			EEPROM.write(E_EASY-i, 0);
		}
	
	eeprom = ON;
	
	best_easy = EEPROM.read(E_EASY); 
	best_medium = EEPROM.read(E_MEDIUM);
	best_hard = EEPROM.read(E_HARD);
	best_crazy = EEPROM.read(E_CRAZY);
	
	GLCD.Init();
	
	if (start == MENU)
		menu();
	
	lap_choice();
	
	arena_clear();
	
	snakeY[0] = 0;
	snakeY[1] = 0;
	snakeY[2] = 0;
	
	snakeX[0] = 2;
	snakeX[1] = 1;
	snakeX[2] = 0;
	
	arena[0][0] = CODE_SNAKE;
	arena[1][0] = CODE_SNAKE;
	arena[2][0] = CODE_SNAKE;
	
	snakeDir = RIGHT;
	snakeLen = 3;

	put_food();
	GLCD.DrawRect(0,0,127,63);
	glcdUpdate();
	
	while(true) 
	{
		//put_food();
		for(i=0; i<lap; i++) 
		{
			dirChanged = refreshSnakeDir();
			delay(TIME);
			
			if( dirChanged || !keyBPressed || !keyAPressed )
			        break;
		}
		if(dirChanged && ((lap-1)-i!= 0)) delay(TIME*((lap-1)-i));
		else if(!keyBPressed) 
		{
			GLCD.SelectFont(Arial14);
			GLCD.CursorToXY(43,20);
			GLCD.print("PAUSE");
			GLCD.SelectFont(System5x7);
			GLCD.CursorToXY(35,35);
			GLCD.print("B-continue");
			delay(2*TIME);
			
			while(!keyBPressed)
			delay(TIME);
			
			while(keyBPressed)
			delay(TIME);
			
			while(!keyBPressed)
			delay(TIME);
			glcdUpdate();
		}
		
		
		else if(!keyAPressed) delay(5*TIME);
		
		
		//refreshSnakeDir();
		
		res = move_snake();
		
		if(res==SCORE) 
		{
			score++;
			if (score != (LENMAX - 3))
				put_food();
		}
		
		if(res==END) {
			GLCD.ClearScreen();
			GLCD.SelectFont(Arial14);
			GLCD.CursorToXY(25,15);
			GLCD.print("GAME OVER!");
			GLCD.SelectFont(System5x7);
			GLCD.CursorToXY(37, 32);
			GLCD.print("SCORE: ");
			GLCD.print(score);
			if (difficulty == EASY && score > best_easy) EEPROM.write(E_EASY, score);
			else if (difficulty == MEDIUM && score > best_medium) EEPROM.write(E_MEDIUM, score);
			else if (difficulty == HARD && score > best_hard) EEPROM.write(E_HARD, score);
			else if (difficulty == CRAZY && score > best_crazy) EEPROM.write(E_CRAZY, score);
			GLCD.CursorToXY(0, 56);
			GLCD.print("A-restart");
			GLCD.CursorToXY(92, 56);
			GLCD.print("B-menu");
			while(!keyAPressed) delay(TIME);
			break;
		}		
		
		glcdUpdate();
		
	}
	
}

void loop()/*executed when the game ends*/
{
	/* add main program code here, this code starts again each time it ends */
	if(!keyAPressed) //if A pressed restart (skip the menu part)
	{
		start = RESTART;
		while(!keyAPressed) delay(TIME);
		setup();
	}
	delay(TIME);
	if(!keyBPressed)//if B pressed go to menu START (menu_menu)
	{
		start = MENU;
		while(!keyBPressed) delay(TIME);
		setup();
	}
	delay(TIME);
}
