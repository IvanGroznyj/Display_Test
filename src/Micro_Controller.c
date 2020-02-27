/*
 * Micro_Controller.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Ivan Khodyrev
 */

#include "../includes/Compile_Mode.h"

#if MODE==MC_MODE
	#include <avr/io.h>
	#include <avr/iom32.h>
	#include "../includes/Micro_Controller.h"

	void Set_Port_IOs(unsigned char port, unsigned char bits) {
		switch (port) {
		case Port_A: {
			DDRA = bits;
			break;
		}
		case Port_B: {
			DDRB = bits;
			break;
		}
		case Port_C: {
			DDRC = bits;
			break;
		}
		case Port_D: {
			DDRD = bits;
			break;
		}
		}
	}

	void Set_Port(unsigned char port, unsigned char bits) {
		switch (port) {
		case Port_A: {
			PORTA = bits;
			break;
		}
		case Port_B: {
			PORTB = bits;
			break;
		}
		case Port_C: {
			PORTC = bits;
			break;
		}
		case Port_D: {
			PORTD = bits;
			break;
		}
		}
	}

	unsigned char Get_Port(unsigned char port) {
		switch (port) {
		case Port_A: {
			return PINA;
		}
		case Port_B: {
			return PINB;
		}
		case Port_C: {
			return PINC;
		}
		case Port_D: {
			return PIND;
		}
		}
		return 0;
	}
#endif
