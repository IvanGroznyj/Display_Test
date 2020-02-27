/*
 * Device_Manadger_Virtual.c
 *
 *  Created on: Feb 27, 2020
 *      Author: Ivan Khodyrev
 */

#include "../includes/Device_Manadger.h"

#if MODE==VIRTUAL_MODE
	#include <stdio.h>
	#include <unistd.h>

	unsigned char lcd_width = 128;
	unsigned char lcd_height = 64;

	unsigned char display_map[32][32];

	char ch = '\n';

	void Delay_ms(int n){}
	void Delay_us(int n){}

	unsigned char Get_Pressed_Button(){
		char ch = getchar();
		switch (ch) {
			case 'a':
				return Btn_Left;
			case 's':
				return Btn_Down;
			case 'd':
				return Btn_Right;
			case 'w':
				return Btn_Up;
			case 'q':
				return Btn_Reset;
			default:
				return Btn_None;
		}
	}

	//*** TEXT MODE ***
	void Lcd_Text_Init(){}
	void Lcd_Text_Write_Symbols(unsigned char x, unsigned char y, const char *text){
		printf(text);
	}
	//*** END TEXT MODE ***

	//*** DRAWING MODE ***
	void Lcd_Drawing_Init(){}
	void Lcd_Drawing_Display_Clear() {
		unsigned char i = 0;
		unsigned char j = 0;
		for (i = 0; i < lcd_height / 2; i++) {
			for (j = 0; j < lcd_width / 4; j++) {
				display_map[i][j] = 0x00;
			}
		}
	}

	void Draw_Byte(unsigned char byte){
		unsigned char mask;
		for(unsigned char i=0; i<8; i++){
			mask = 1 << (7-i);
			if(((byte & mask)>>(7-i)) % 2 == 0){
				printf("%c", ' ');
			}else{
				printf("%c", '#');
			}
		}
	}

	void Lcd_Drawing_Display_Redraw() {
		unsigned char i = 0;
		unsigned char j = 0;
		for (i = 0; i < lcd_height / 2; i++) {
			for (j = 0; j < lcd_width / 8; j++) {
				Draw_Byte(display_map[i][j]);
			}
			printf("\n");
		}

		for (i = 0; i < lcd_height / 2; i++) {
			for (j = lcd_width/8; j < lcd_width / 4; j++) {
				Draw_Byte(display_map[i][j]);
			}
			printf("\n");
		}
	}

	void Lcd_Drawing_Display_Fast_Redraw() {
		Lcd_Drawing_Display_Redraw();
	}

	void Lcd_Drawing_Display_Put_Pixel(unsigned char x, unsigned char y,
			unsigned char is_on) {
		unsigned char iy = y % (lcd_height / 2);
		unsigned char ix = x + y / (lcd_height / 2) * lcd_width;
		if (is_on == 1) {
			display_map[iy][ix / 8] |= 1 << (7 - ix % 8);
		} else {
			display_map[iy][ix / 8] &= ~(1 << (7 - ix % 8));
		}
	}

	unsigned char Lcd_Drawing_Display_Get_Pixel(unsigned char x, unsigned char y) {
		unsigned char iy = y % (lcd_height / 2);
		unsigned char ix = x + y / (lcd_height / 2) * lcd_width;
		return (display_map[iy][ix / 8] >> (7 - ix % 8)) % 2;
	}
	//*** END DRAWING MODE ***
#endif
