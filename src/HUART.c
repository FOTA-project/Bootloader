/************************************
 * Author: Esraa Awad                *
 * Date: 26/3/2020                   *
 * File: UART_handler.c              *
 * Target: STM                       *
 ************************************/



#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "HUART.h"


#define HUART_TX_PIN 0
#define HUART_RX_PIN 1

extern GPIO_t HUART_GPIO_CONFIG[2] ;


void HUART_InitGPIO(void)
{
  
  GPIO_initPin(&HUART_GPIO_CONFIG [HUART_TX_PIN]);
  GPIO_initPin(&HUART_GPIO_CONFIG [HUART_RX_PIN ]);

}




