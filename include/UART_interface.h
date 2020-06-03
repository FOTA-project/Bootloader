/************************************
* Author: Esraa Awad                *
* Date: 3/26/2020                   *
* File: UART.h                   *
* Target: STM                       *
************************************/

#ifndef UART_H
#define UART_H



/************* UART Peripherals Addresses    ************************************/
#define  USART1               ((void*)0x40013800)
#define  USART2               ((void*)0x40004400)
#define  USART3               ((void*)0x40004800)
#define  UART4                ((void*)0x40004C00)
#define  UART5                ((void*)0x40005000)


/******** Word Length **********/
#define UART_WORD_LENGTH_8 0x00000000
#define UART_WORD_LENGTH_9 0x00001000

/***** STOP BITS **************/
#define UART_STOP_BITS_CLR 0xffffdfff
#define UART_STOP_BITS_0_5 0x00001000
#define UART_STOP_BITS_1   0x00000000
#define UART_STOP_BITS_1_5 0x00003000
#define UART_STOP_BITS_2   0x00002000

/****** Parity *****************/
#define UART_CR1_PCE_ENABLE  0x00000400
#define UART_CR1_PCE_DISABLE 0x00000000
#define UART_CR1_PS_EVEN     0x00000000
#define UART_CR1_PS_ODD      0x00000200


/****** Baud Rate &  **************/
#define UART_FCK              72000000
#define UART_BUADRATE_9600    9600U
#define UART_BUADRATE_115200  115200U


#define ON 			1
#define OFF 		2
/******************************/

/***** TX and RX CallBack Functions types***/
typedef void (*UART_Txcbf_t)(void);
typedef void (*UART_Rxcbf_t)(void);

/*******************************  FUNCTION PROTOTYPES ************/
/*
*
* Description: This API initialize UART
* Input:   1-USART1
           2-USART2
           3-USART3
           4-UART4
           5-UART5
* Otput: void
*
*/
extern void UART_voidInit (void* UART_Peri);

/*
*
* Description: This API send a data through UART
* Input: u8 Array and the length of array
* Output: void
*
*/
extern ERROR_STATUS UART_Send(u8 * Buffer , u16 DataLength);

/*
*
* Description: This API recieve a data through UART
* Input: Array and the length of the array
* Output: void
*
*/
extern ERROR_STATUS UART_Recieve(u8* Buffer , u16 DataLength);



/*
*
* Description: This API take the call back function which execute when recieving is done
* Input: Function name
* Output: void
*
*/
extern ERROR_STATUS UART_SetRxCbf(UART_Rxcbf_t Rxcbf);


extern ERROR_STATUS  UART_SetTxCbf(UART_Txcbf_t Txcbf);

#endif

