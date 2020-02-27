/*
 * Snake.c
 *
 * Created: 18.07.2019 10:15:22
 *  Author: Ivan Khodyrev
 */

#include "../includes/Device_Manadger.h"
#include "../includes/Game_Basic.h"

#define SNAKE_MAX_LENGTH 100

unsigned char snake_length;
unsigned char direct;
unsigned char food_x;
unsigned char food_y;
unsigned char snake_body[SNAKE_MAX_LENGTH][2];
unsigned char head_index, tile_index;

void Draw_Borders() {
	unsigned char i = 0;
	unsigned char j;
	for (i = 0; i < lcd_height; i++) {
		;
		for (j = 0; j < lcd_width; j++) {
			if (i == 0 || j == 0 || i == lcd_height - 1 || j == lcd_width - 1) {
				Lcd_Drawing_Display_Put_Pixel(j, i, 1);
			}
		}
	}
}

void Update() {
	unsigned char x = snake_body[head_index][0];
	unsigned char y = snake_body[head_index][1];

	switch (direct) {
	case direct_up:
		snake_body[head_index][1]--;
		break;
	case direct_right:
		snake_body[head_index][0]++;
		break;
	case direct_down:
		snake_body[head_index][1]++;
		break;
	case direct_left:
		snake_body[head_index][0]--;
		break;
	}
	if (Lcd_Drawing_Display_Get_Pixel(snake_body[head_index][0],
			snake_body[head_index][1]) == 1) {
		if ((snake_body[head_index][0] == food_x)
				& (snake_body[head_index][1] == food_y)) {
			snake_length++;
			srand(
					food_x + food_y + snake_body[tile_index][0]
							+ snake_body[tile_index][1]);
			food_x = rand() % (126 - 1 + 1) + 1;
			food_y = rand() % (62 - 1 + 1) + 1;
		} else {
			is_run = 0;
		}
	} else {
		Lcd_Drawing_Display_Put_Pixel(snake_body[tile_index][0],
				snake_body[tile_index][1], 0);
		tile_index++;
		if (tile_index == SNAKE_MAX_LENGTH)
			tile_index = 0;
	}
	head_index++;
	if (head_index == 100) {
		head_index = 0;
		snake_body[head_index][0] = snake_body[99][0];
		snake_body[head_index][1] = snake_body[99][1];
		snake_body[99][0] = x;
		snake_body[99][1] = y;
	} else {
		snake_body[head_index][0] = snake_body[head_index - 1][0];
		snake_body[head_index][1] = snake_body[head_index - 1][1];
		snake_body[head_index - 1][0] = x;
		snake_body[head_index - 1][1] = y;
	}
	Lcd_Drawing_Display_Put_Pixel(snake_body[head_index][0],
			snake_body[head_index][1], 1);
	Lcd_Drawing_Display_Put_Pixel(food_x, food_y, 1);
	if (snake_length == SNAKE_MAX_LENGTH)
		is_run = 0;
}

void Start_Snake() {
	Lcd_Drawing_Init();
	Lcd_Drawing_Display_Clear();
	Lcd_Drawing_Display_Redraw();

	Draw_Borders();
	snake_length = 10;
	direct = direct_up;
	food_x = 30;
	food_y = 30;
	is_run = 0;
	tile_index = 0;
	head_index = 9;
	unsigned char i;
	for (i = 0; i < 100; i++) {
		snake_body[i][0] = -1;
		snake_body[i][1] = -1;
	}
	for (i = 0; i < snake_length; i++) {
		snake_body[snake_length - i - 1][0] = lcd_width / 2;
		snake_body[snake_length - i - 1][1] = lcd_height / 2 + i;
		Lcd_Drawing_Display_Put_Pixel(lcd_width / 2, lcd_height / 2 + i, 1);
	}
	Lcd_Drawing_Display_Put_Pixel(food_x, food_y, 1);

	Lcd_Drawing_Display_Fast_Redraw();
	Delay_ms(1000);

	is_run = 1;

	unsigned char btn = Btn_None;
	while (is_run) {
		btn = Get_Pressed_Button();
		switch (btn) {
		case Btn_Right:
			if (direct != 3) {
				direct = 1;
			}
			break;
		case Btn_Up:
			if (direct != 2) {
				direct = 0;
			}
			break;
		case Btn_Left:
			if (direct != 1) {
				direct = 3;
			}
			break;
		case Btn_Down:
			if (direct != 0) {
				direct = 2;
			}
			break;
		case Btn_Reset:
			is_run = 0;
			break;
		}

		Update();
		Lcd_Drawing_Display_Fast_Redraw();
		Delay_ms(45);
	}
	Draw_Score(snake_length - 10);
}
