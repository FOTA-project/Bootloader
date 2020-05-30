/************************************
 * Author: Esraa Awad                *
 * Date: 26/3/2020                   *
 * File: UART.h                      *
 * Target: STM                       *
 ************************************/

#ifndef UART_CFG_H_
#define UART_CFG_H_

/******** Word Length Options ******
***  -> UART_WORD_LENGTH_8 
***  -> UART_WORD_LENGTH_9 */

#define UART_WORD_LENGTH   UART_WORD_LENGTH_8

   
/***** STOP BITS Options ***********
***  -> UART_STOP_BITS_CLR 
***  -> UART_STOP_BITS_0_5 
***  -> UART_STOP_BITS_1   
***  -> UART_STOP_BITS_1_5 
***  -> UART_STOP_BITS_2   */

#define UART_STOP_BITS    UART_STOP_BITS_1


/****** Parity Options ****************
***  -> UART_CR1_PCE_DISABLE 
***  -> UART_CR1_PS_EVEN  
***  -> UART_CR1_PS_ODD   */

#define UART_CR1_PCE    UART_CR1_PCE_DISABLE

/****** Baud Rate  options -> UART_BUADRATE_9600  **************/

#define UART_BUADRATE  UART_BUADRATE_9600 

/****** UART interrupt Number ******/

#define UART_IQUNUMBER    NVIC_IRQ37




#endif