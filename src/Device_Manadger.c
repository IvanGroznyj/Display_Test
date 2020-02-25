/*
 * Buttons.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Ivan Khodyrev
 */

#include "../headers/Device_Manadger.h"
#include "../headers/Micro_Controller.h"

unsigned char lcd_width = 128;
unsigned char lcd_height = 64;

unsigned char x_zero = 0b10000000;
unsigned char y_zero = 0b10000000;
unsigned char display_map[32][32];
unsigned char updates_map[32][2];

unsigned char Get_Pressed_Button() {
	if ((Get_Port(Port_D) >> 6) % 2 == 0) { //right
		return Btn_Right;
	}
	if ((Get_Port(Port_D) >> 5) % 2 == 0) { //up
		return Btn_Up;
	}
	if ((Get_Port(Port_D) >> 4) % 2 == 0) { //left
		return Btn_Left;
	}
	if ((Get_Port(Port_D) >> 3) % 2 == 0) { //down
		return Btn_Down;
	}
	if ((Get_Port(Port_D) >> 2) % 2 == 0) { //reset
		return Btn_Reset;
	}
	return Btn_None;
}

void Lcd_Send_Command(unsigned char cmd) {
	Set_Port(Port_A, 0b00000100);
	Set_Port(Port_B, cmd);
	_delay_us(36);
	Set_Port(Port_A, 0b00000000);
}

void Lcd_Send_Data(unsigned char data) {
	Set_Port(Port_A, 0b00000101);
	Set_Port(Port_B, data);
	_delay_us(36);
	Set_Port(Port_A, 0b00000001);
}

//*** TEXT MODE ***
void Lcd_Text_Init() {
	Lcd_Send_Command(0b00001100); // display
	_delay_us(30);
	Lcd_Send_Command(0b00110000); // 8bit mode
	_delay_us(30);
	Lcd_Send_Command(0b00000001); //clear
	_delay_ms(5);
	Lcd_Send_Command(0b00000010);
	_delay_us(10);
	Lcd_Send_Command(0b00000110); //select 1st row and 1 col for data
	_delay_us(30);
}

void Lcd_Text_Write_Symbols(unsigned char x, unsigned char y, const char *text) {
	if (x >= 0 && x < lcd_width / 8 && y >= 0 && y < lcd_height / 32) {
		Lcd_Send_Command(0b10000000 + y * 16 + x);

		const char *p = text;
		while (*p != '\0') {
			Lcd_Send_Data(*p);
			p++;
			_delay_ms(10);
		}
	}
}
//*** END TEXT MODE ***

//*** DRAWING MODE ***
void Lcd_Drawing_Init() {
	Lcd_Send_Command(0b00000001); //clear
	_delay_ms(5);
	Lcd_Send_Command(0b00001000); // display
	_delay_us(30);
	Lcd_Send_Command(0b00110110); //8-bit mode and Graphics
	_delay_us(72);
	Lcd_Send_Command(0b00000011);
	_delay_us(10);
}

void Lcd_Drawing_Display_Clear() {
	unsigned char i = 0;
	unsigned char j = 0;
	for (i = 0; i < lcd_height / 2; i++) {
		for (j = 0; j < lcd_width / 4; j++) {
			display_map[i][j] = 0x00;
			updates_map[i][j / 16] = 0x00;
		}
	}
}

void Lcd_Drawing_Display_Redraw() {
	unsigned char i = 0;
	unsigned char j = 0;
	for (i = 0; i < lcd_height / 2; i++) {
		Lcd_Send_Command(y_zero + i);
		Lcd_Send_Command(x_zero);
		for (j = 0; j < lcd_width / 4; j++) {
			Lcd_Send_Data(display_map[i][j]);
		}
	}
}

void Lcd_Drawing_Display_Fast_Redraw() {
	unsigned char i = 0;
	unsigned char j = 0;
	for (i = 0; i < lcd_height / 2; i++) {
		for (j = 0; j < lcd_width / 8; j++) {
			if ((updates_map[i][j / 8] >> (7 - j % 8)) % 2 == 1) {
				Lcd_Send_Command(y_zero + i);
				Lcd_Send_Command(x_zero + j);
				Lcd_Send_Data(display_map[i][j * 2]);
				Lcd_Send_Data(display_map[i][j * 2 + 1]);
			}
		}
	}
	for (i = 0; i < lcd_height / 2; i++) {
		for (j = 0; j < lcd_width / 64; j++) {
			updates_map[i][j] = 0x00;
		}
	}
}

void Lcd_Drawing_Display_Put_Block(unsigned char x, unsigned char y,
		unsigned char block1, unsigned char block2) {
	display_map[y % (lcd_height / 2)][x + y / (lcd_height / 2) * 16] = block1;
	display_map[y % (lcd_height / 2)][x + y / (lcd_height / 2) * 16 + 1] =
			block2;
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
	updates_map[iy][ix / 128] |= 1 << (7 - (ix / 16) % 8);
}

unsigned char Lcd_Drawing_Display_Get_Pixel(unsigned char x, unsigned char y) {
	unsigned char iy = y % (lcd_height / 2);
	unsigned char ix = x + y / (lcd_height / 2) * lcd_width;
	return (display_map[iy][ix / 8] >> (7 - ix % 8)) % 2;
}
//*** END DRAWING MODE ***
