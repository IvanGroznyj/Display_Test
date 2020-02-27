/*
 * FlappyBird.c
 *
 * Created: 20.07.2019 16:58:20
 *  Author: Ivan Khodyrev
 */

#include "../includes/Device_Manadger.h"
#include "../includes/Game_Basic.h"

unsigned char clmns_coords[4][2]; // x clmn position, y top hall position
unsigned char last_clmn_index;
unsigned char y;
signed char dy;

void Fill_Bird(unsigned char x, unsigned char y, unsigned char is_on) {
	unsigned char i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if ((i - 4) * (i - 4) + (j - 4) * (j - 4) < 16)
				Lcd_Drawing_Display_Put_Pixel(x + i, y + j, is_on);
		}
	}
}

void Start_FlappyBird() {
	Lcd_Drawing_Init();
	Lcd_Drawing_Display_Clear();
	Lcd_Drawing_Display_Redraw();

	last_clmn_index = 0;
	clmns_coords[last_clmn_index][0] = lcd_width / 2 - 11;
	clmns_coords[last_clmn_index][1] = random() % (lcd_height - 40) + 10;
	last_clmn_index++;
	clmns_coords[last_clmn_index][0] = lcd_width - 11;
	clmns_coords[last_clmn_index][1] = random() % (lcd_height - 40) + 10;
	last_clmn_index++;
	clmns_coords[last_clmn_index][0] = lcd_width + lcd_width / 2 - 11;
	clmns_coords[last_clmn_index][1] = random() % (lcd_height - 40) + 10;
	last_clmn_index++;
	clmns_coords[last_clmn_index][0] = lcd_width + lcd_width - 11;
	clmns_coords[last_clmn_index][1] = random() % (lcd_height - 40) + 10;
	last_clmn_index++;

	unsigned char i, j, k;
	for (i = 0; i < 1; i++) {
		for (j = 0; j < lcd_height; j++) {
			if (j <= clmns_coords[i][1] || j >= clmns_coords[i][1] + 20) {
				for (k = 0; k < 10; k++)
					Lcd_Drawing_Display_Put_Pixel(clmns_coords[i][0] + k, j, 1);
			}
		}
	}

	y = lcd_height / 2;
	dy = 0;
	Fill_Bird(25, y, 1);

	is_run = 1;
	score = 0;
	unsigned char btn = Btn_None;
	while (is_run) {
		btn = Get_Pressed_Button();
		switch (btn) {
		case Btn_Up:
			dy = -2;
			break;
		case Btn_Reset:
			is_run = 0;
			break;
		}

		Fill_Bird(25, y, 0);
		if (y < 4 && dy < 0)
			dy = 0;
		y += dy;
		if (y >= lcd_height - 10)
			is_run = 0;
		dy++;
		Fill_Bird(25, y, 1);

		for (i = 0; i < last_clmn_index; i++) {
			clmns_coords[i][0]--;
			for (j = 0; j < lcd_height; j++) {
				if (j <= clmns_coords[i][1] || j >= clmns_coords[i][1] + 20) {
					if (clmns_coords[i][0] <= lcd_width - 1) {
						if (clmns_coords[i][0] > 10) {
							Lcd_Drawing_Display_Put_Pixel(clmns_coords[i][0], j,
									1);
							if (clmns_coords[i][0] > lcd_width - 11)
								Lcd_Drawing_Display_Put_Pixel(lcd_width - 1, j,
										1);
						}
					}
					if (clmns_coords[i][0] + 10 <= lcd_width)
						Lcd_Drawing_Display_Put_Pixel(clmns_coords[i][0] + 10,
								j, 0);
				}

			}
			if (clmns_coords[i][0] >= 15 && clmns_coords[i][0] <= 32
					&& (y - clmns_coords[i][1] <= 0
							|| clmns_coords[i][1] + 20 - y <= 8)) {
				is_run = 0;
			}

			if (clmns_coords[i][0] == 15)
				score++;
			if (clmns_coords[i][0] == 0) {
				srand(y + dy + score);
				clmns_coords[i][0] = random() % 15 + lcd_width * 2 - 26;
				clmns_coords[i][1] = random() % (lcd_height - 40) + 10;
			}
		}
		Lcd_Drawing_Display_Fast_Redraw();
	}
	Draw_Score(score);
}
