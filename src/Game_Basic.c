/*
 * Game_Basic.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Ivan Khodyrev
 */
#include "../includes/Device_Manadger.h"
#include "../includes/Game_Basic.h"

#include "../includes/Flappy_Bird.h"
#include "../includes/Snake.h"
#include "../includes/Test.h"

unsigned char gamesCount = 3;
char *games[] = { "Snake", "Flying ball", "Test" };
unsigned char lengths[] = { 5, 11, 4 };
unsigned char currentGameIndx = 0;

void Start_Menu() {
	unsigned char i;
	while (1) {
		Lcd_Text_Init();
		Delay_ms(100);
		char *pointer = "->";
		for (i = currentGameIndx - currentGameIndx % 2;
				i < currentGameIndx - currentGameIndx % 2 + 2; i++) {
			if (i < gamesCount) {
				if (i == currentGameIndx) {
					pointer = "->";
				} else {
					pointer = "  ";
				}
				Lcd_Text_Write_Symbols(0, i % 2, pointer);
				Lcd_Text_Write_Symbols(1, i % 2, games[i]);
			}
		}
		Delay_ms(100);
		unsigned char btn = Btn_None;
		while (btn == Btn_None) {
			btn = Get_Pressed_Button();
			switch (btn) {
			case Btn_Right:
				switch (currentGameIndx) {
				case 0:
					Start_Snake();
					break;
				case 1:
					Start_FlappyBird();
					break;
				case 2:
					Start_Test();
					break;
				}
				break;
			case Btn_Up:
				if (currentGameIndx > 0) {
					currentGameIndx--;
				}
				break;
			case Btn_Down:
				if (currentGameIndx < gamesCount - 1) {
					currentGameIndx++;
				}
				break;
			}
		}
	}
}

void Draw_Score(unsigned char score) {
	Lcd_Text_Init();
	Delay_ms(100);
	char *s = "You died... 000";

	s[14] = 48 + score % 10;
	score /= 10;
	s[13] = 48 + score % 10;
	score /= 10;
	s[12] = 48 + score % 10;

	Lcd_Text_Write_Symbols(0, 0, s);

	Delay_ms(2000);
}
