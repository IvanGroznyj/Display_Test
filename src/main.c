/*
 * DisplayTest.c
 *
 * Created: 09.07.2019 16:28:41
 * Author : Ivan Khodyrev
 */

#define F_CPU 1000000UL

#include <util/delay.h>

#include "../headers/Micro_Controller.h"
#include "../headers/Game_Basic.h"

int main(void) {
	Set_Port_IOs(Port_B, 0xff);
	Set_Port_IOs(Port_A, 0b00000111);
	Set_Port_IOs(Port_D, 0x00);
	Set_Port(Port_D, 0b01111100);

	Start_Menu();
}
