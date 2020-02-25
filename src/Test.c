/*
 * Test.c
 *
 * Created: 05.09.2019 22:28:31
 *  Author: Nazarec
 */

#include "../headers/Device_Manadger.h"
#include "../headers/Game_Basic.h"

void Start_Test() {
	Lcd_Drawing_Init();
	Lcd_Drawing_Display_Clear();
	Lcd_Drawing_Display_Redraw();

	unsigned char i;
	unsigned char j;
	unsigned char r = lcd_height / 4;
	unsigned char x = lcd_width / 2;
	unsigned char y = lcd_height / 2;

	is_run = 1;
	unsigned char btn = Btn_None;
	while (is_run) {
		btn = Get_Pressed_Button();
		switch (btn) {
		case Btn_Right:
			if (x < lcd_width - r) {
				x++;
			}
			break;
		case Btn_Up:
			if (x < lcd_width - r) {
				r++;
			}
			break;
		case Btn_Left:
			if (x > r) {
				x--;
			}
			break;
		case Btn_Down:
			if (r > 1) {
				r--;
			}
			break;
		case Btn_Reset:
			is_run = 0;
			break;
		}

		for (i = 0; i < 2 * r; i++) {
			for (j = 0; j < 2 * r; j++) {
				if ((((i - r) * (i - r)) + ((j - r) * (j - r))) <= r * r) {
					Lcd_Drawing_Display_Put_Pixel(i + x - r, j + y - r, 1);
				} else {
					Lcd_Drawing_Display_Put_Pixel(i + x - r, j + y - r, 0);
				}
			}
		}
		Lcd_Drawing_Display_Fast_Redraw();
	}
}

