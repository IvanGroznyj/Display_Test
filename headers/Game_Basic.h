/*
 * Game_Basic.h
 *
 *  Created on: Feb 22, 2020
 *      Author: Ivan Khodyrev
 */

#ifndef GAME_BASIC_H_
#define GAME_BASIC_H_

#include <stdlib.h> // for random

enum DIRECTIONS {
	direct_up, direct_down, direct_left, direct_right
};

unsigned char is_run;
unsigned char score;

void Start_Menu();
void Draw_Score(unsigned char score);

#endif /* GAME_BASIC_H_ */
