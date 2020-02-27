/*
 * Micro_Controller.h
 *
 *  Created on: Feb 22, 2020
 *      Author: Ivan Khodyrev
 */
#pragma once

#ifndef MICRO_CONTROLLER_H_
#define MICRO_CONTROLLER_H_

enum PORTS {
	Port_A = 0, Port_B, Port_C, Port_D
};

/**
 *	@brief Set pins to input or output
 *
 *	1 - output, 0 - input
 *
 *	@param port One of 4 ports contained into enum PORTS
 *	@param bits Byte for 8 PINs of the port
 */
void Set_Port_IOs(unsigned char port, unsigned char bits);

/**
 * @brief Activate or deactivate PINs in the port
 *
 * @param port One of 4 ports contained into enum PORTS
 * @param bits Byte for 8 PINs of the port
 */
void Set_Port(unsigned char port, unsigned char bits);

/**
 * @brief Return states of 8 PINS in the port
 *
 * 1 - have signal, 0 - no signal
 *
 * @param port One of 4 ports contained into enum PORTS
 * @return Byte which is contained states of the PINs
 */
unsigned char Get_Port(unsigned char port);

#endif /* MICRO_CONTROLLER_H_ */
