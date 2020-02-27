/*
 * Device_Manadger.h
 *
 *  Created on: Feb 22, 2020
 *      Author: Ivan Khodyrev
 */

#include "Compile_Mode.h"

#ifndef DEVICE_MANADGER_H_
#define DEVICE_MANADGER_H_


#if MODE==MC_MODE
	#define Delay_ms(n) _delay_ms(n)
	#define Delay_us(n) _delay_us(n)

	#define F_CPU 1000000UL

	#include <util/delay.h>
#else
	void Delay_ms(int n);
	void Delay_us(int n);
#endif

extern unsigned char lcd_width;
extern unsigned char lcd_height;

enum Buttons {
	Btn_None, Btn_Up, Btn_Down, Btn_Left, Btn_Right, Btn_Reset
};

unsigned char Get_Pressed_Button();

//*** TEXT MODE ***
void Lcd_Text_Init();
void Lcd_Text_Write_Symbols(unsigned char x, unsigned char y, const char *text);
//*** END TEXT MODE ***

//*** DRAWING MODE ***
void Lcd_Drawing_Init();
void Lcd_Drawing_Display_Clear();
void Lcd_Drawing_Display_Redraw();
void Lcd_Drawing_Display_Fast_Redraw();
void Lcd_Drawing_Display_Put_Pixel(unsigned char x, unsigned char y,
		unsigned char is_on);
unsigned char Lcd_Drawing_Display_Get_Pixel(unsigned char x, unsigned char y);
//*** END DRAWING MODE ***

#endif /* DEVICE_MANADGER_H_ */
