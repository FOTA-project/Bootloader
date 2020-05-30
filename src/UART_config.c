
/************************************
 * Author: Esraa Awad                *
 * Date: 26/3/2020                   *
 * File: UART_Config.c               *
 * Target: STM                       *
 ************************************/
#include "STD_TYPES.h"

#include "GPIO_interface.h"


/* 	UARTX IO configure pins */
GPIO_t HUART_GPIO_CONFIG[2] =
{

	{
			//Tx Pin
		.pin   = PIN9,
		.mode  = MODE_OUTPUT_SPEED_50,
		.configuration = CONFIG_OUTPUT_ALTERNATE_FUNCTION_PUSH_PULL,
		.port  = PORTA,
	},


	{
			//Rx pin
		.pin   = PIN10,
		.mode  = MODE_INPUT,
		.configuration = CONFIG_INPUT_PULL_UP_DOWN,
		.port  = PORTA,
	}
};

