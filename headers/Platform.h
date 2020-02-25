/*
 * Platform.h
 *
 * Created: 18.07.2019 15:55:20
 *  Author: Ivan Khodyrev
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

unsigned char plx;
unsigned char is_run;
unsigned char isFree;
int px, py;
int dx, dy;
unsigned char pldx;
unsigned char score;

void Update_Platform() {
	unsigned char isNotCollided = 1;
	unsigned char i, k;
	int x = px;
	int y = py;
	if (isFree) {
		put_pixel(px, py, 0);
		if (abs(dx) > abs(dy)) {
			k = abs(dx);
		} else {
			k = abs(dy);
		}
		for (i = 1; i <= k; i++) {
			px = x + (float) (dx) / k * i;
			py = y + (float) (dy) / k * i;
			isNotCollided = 1;
			if (isNotCollided && (px >= lcd_width - 1)) {
				px = lcd_width - 1;
				dx = -dx;
				isNotCollided = 0;
			}
			if (isNotCollided && (px <= 0)) {
				dx = -dx;
				px = 0;
				isNotCollided = 0;
			}
			if (isNotCollided && (py <= 0)) {
				py = 0;
				dy = -dy;
				isNotCollided = 0;
			}
			if (isNotCollided && (py >= lcd_height - 2)) {
				if ((px >= plx - 2) && (px <= plx + 10)) {
					py = lcd_height - 2;
					dy = -dy;
					dx += pldx;
					if (abs(dx) > 2)
						dx = 2;
				} else {
					py = lcd_height - 2;
					px = plx + 4;
					isFree = 0;
				}
				isNotCollided = 0;
			}
			if (isNotCollided && (py > 0) && (get_pixel(px, py - 1) == 1)) {
				dy = -dy;
				put_pixel(px, py - 1, 0);
				score++;
				isNotCollided = 0;
			}
			if (isNotCollided && (py != lcd_height - 2)
					&& (get_pixel(px, py + 1) == 1)) {
				dy = -dy;
				put_pixel(px, py - 1, 0);
				score++;
				isNotCollided = 0;
			}
			if (isNotCollided && (px < lcd_width - 1)
					&& (get_pixel(px + 1, py) == 1)) {
				dx = -dx;
				put_pixel(px + 1, py, 0);
				score++;
				isNotCollided = 0;
			}
			if (isNotCollided && (px > 0) && (get_pixel(px - 1, py) == 1)) {
				dx = -dx;
				put_pixel(px - 1, py, 0);
				score++;
				isNotCollided = 0;
			}
			if (isNotCollided == 0)
				break;
		}
		put_pixel(px, py, 1);
	}
}

void Start_Platform() {
	lcd_ginit();
	lcd_gclear();
	lcd_redraw();
	plx = lcd_width / 2;
	px = plx + 4;
	py = lcd_height - 2;
	score = 0;
	unsigned char i, j;
	for (i = 0; i < 8; i++) {
		put_pixel(plx + i, lcd_height - 1, 1);
	}
	for (i = 0; i < lcd_height / 2; i++) {
		for (j = 0; j < lcd_width / 16; j++) {
			put_block(j * 2, i, 0xff, 0xff);
		}
	}
	put_pixel(px, py, 1);

	is_run = 1;
	isFree = 0;
	unsigned char btnIsPressed;
	while (is_run) {
		btnIsPressed = 0;
		pldx = 0;
		if ((btnIsPressed == 0) && ((Get_Port(Port_D) >> 6) % 2 == 0)) { //right
			if (plx < lcd_width - 9) {
				plx++;
				put_pixel(plx + 7, lcd_height - 1, 1);
				put_pixel(plx - 1, lcd_height - 1, 0);
				plx++;
				put_pixel(plx + 7, lcd_height - 1, 1);
				put_pixel(plx - 1, lcd_height - 1, 0);
				if (isFree == 0) {
					put_pixel(px, py, 0);
					px += 2;
					put_pixel(px, py, 1);
				}
				pldx = 2;
			}
			btnIsPressed = 1;
		}
		if ((btnIsPressed == 0) && ((Get_Port(Port_D) >> 5) % 2 == 0)) { //up
			if (isFree == 0) {
				isFree = 1;
				dy = -(rand() % 2 + 1);
				dx = rand() % 4 - 2;
			}
			btnIsPressed = 1;
		}
		if ((btnIsPressed == 0) && ((Get_Port(Port_D) >> 4) % 2 == 0)) { //left
			if (plx > 1) {
				plx--;
				put_pixel(plx + 8, lcd_height - 1, 0);
				put_pixel(plx, lcd_height - 1, 1);
				plx--;
				put_pixel(plx + 8, lcd_height - 1, 0);
				put_pixel(plx, lcd_height - 1, 1);
				if (isFree == 0) {
					put_pixel(px, py, 0);
					px -= 2;
					put_pixel(px, py, 1);
				}
				pldx = -2;
			}
			btnIsPressed = 1;
		}

		if ((btnIsPressed == 0) && ((Get_Port(Port_D) >> 2) % 2 == 0)) { //reset
			is_run = 0;
			btnIsPressed = 1;
		}
		Update_Platform();
		lcd_redraw();
		_delay_ms(50);
	}

	lcd_init();
	_delay_ms(100);
	char *s = "You died... ";
	i = 0;
	for (i = 0; i < 12; i++) {
		lcd_data(s[i]);
		_delay_ms(10);
	}
	//free(s);
	char a = '0';
	char b = '0';
	char c = '0';
	c = 48 + score % 10;
	score /= 10;
	b = 48 + score % 10;
	score /= 10;
	a = 48 + score % 10;
	lcd_data(a);
	_delay_ms(10);
	lcd_data(b);
	_delay_ms(10);
	lcd_data(c);
	_delay_ms(2000);
}
#endif /* PLATFORM_H_ */
