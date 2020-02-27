/*
 * DisplayTest.c
 *
 * Created: 09.07.2019 16:28:41
 * Author : Ivan Khodyrev
 */

#include "../includes/Compile_Mode.h"

#if MODE==MC_MODE
	#define F_CPU 1000000UL
	#include <util/delay.h>
#endif


#include "../includes/Micro_Controller.h"
#include "../includes/Game_Basic.h"

int main(void) {

#if MODE==MC_MODE
	Set_Port_IOs(Port_B, 0xff); // set outputs to send data to display
	Set_Port_IOs(Port_A, 0b00000111); // set outputs to control display input
	Set_Port_IOs(Port_D, 0x00); // set inputs for buttons
	Set_Port(Port_D, 0b01111100); // wait signals from buttons
#endif

	Start_Menu();
}
