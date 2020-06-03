/************************************
 * Author: Esraa Awad                *
 * Date: 26/3/2020                   *
 * File: UART.h                      *
 * Target: STM                       *
 ************************************/

#include "STD_TYPES.h"

#include "NVIC_interface.h"

#include "UART_interface.h"

#include "UART_Config.h"

#include "diag/Trace.h"
#include "HUART.h"

/*********** MASKS ************/
#define UART_SR_TXE       0x00000080
#define UART_SR_RXNE      0x00000020
#define UART_CR1_UE       0x00002000
#define UART_CR1_TE       0x00000008
#define UART_CR1_RE       0x00000004
#define UART_SR_TXE       0x00000080
#define UART_SR_RXNE      0x00000020
#define UART_SR_TXE_CLR   0xffffff7f
#define UART_SR_RXNE_CLR  0xffffffdf
#define UART_CR1_RXNEIE	  0x00000020
#define UART_CR1_TXIE	  0x00000080
#define UART_SR_TC_CLR    0xffffffbf
#define UART_SR_TC		  0x00000040
#define UART_CR1_TCIE     0x00000040
#define UART_CR3_CTSE	  0x00000200
#define UART_CR3_RTSE	  0x00000100

/******************************** UART DATA BUFFER  ******************************/
typedef struct
{
   u8 *DataBuffer;
   u16 DataIndex;
   u16 DataLength;
   UART_BufferState_t State;
} UART_DataBuffer_t;

typedef struct
{
   u32 SR;
   u32 DR;
   u32 BRR;
   u32 CR1;
   u32 CR2;
   u32 CR3;
   u32 GPTR;
} UART_REG_t;

static volatile UART_REG_t *UARTX_REG;

static UART_DataBuffer_t UART_TxBuffer;
static UART_DataBuffer_t UART_RxBuffer;

static UART_Txcbf_t appRxNotify;
static UART_Rxcbf_t appTxNotify;

/*
 *
 * Description: This API initialize UART
 * Input:  1-USART1
 2-USART2
 3-USART3
 4-UART4
 5-UART5

 * Output: void
 *
 */
void UART_voidInit(void* UART_Peri)
{

   UARTX_REG = (UART_REG_t*)UART_Peri;

   /*Enable usart */
   UARTX_REG->CR1 |= UART_CR1_UE;

   /* Set IO Pins */
   HUART_InitGPIO();

   /*** Default Buffer Configuration  ****/

   UART_TxBuffer.DataBuffer = NULL;
   UART_TxBuffer.DataLength = 0;
   UART_TxBuffer.DataIndex = 0;
   UART_TxBuffer.State = idle;

   UART_RxBuffer.DataBuffer = NULL;
   UART_RxBuffer.DataLength = 0;
   UART_RxBuffer.DataIndex = 0;
   UART_RxBuffer.State = idle;
   /*** setup default configurations  ****/

   UARTX_REG->CR1 |= UART_WORD_LENGTH;
   UARTX_REG->CR2 &= UART_STOP_BITS_CLR;
   UARTX_REG->CR2 |= UART_STOP_BITS;
   UARTX_REG->BRR = UART_FCK / UART_BUADRATE;

   /*Enable transmitter and receive*/
   UARTX_REG->CR1 |= UART_CR1_TE | UART_CR1_RE;

   /*Enable transmitter and receive interrupts */
   UARTX_REG->CR1 |= UART_CR1_TCIE | UART_CR1_RXNEIE;

   /*Clear TC Flag*/
   UARTX_REG->SR &= UART_SR_TC_CLR;

   /*clear uart pending*/
   NVIC_u8ClearPending(UART_IQUNUMBER);

   /* Setup interrupts */
   NVIC_u8EnableIRQ(UART_IQUNUMBER);
}

/*
 *
 * Description: This API send a data through UART
 * Input: u8 Array and the length of array
 * Output: void
 *
 */
ERROR_STATUS UART_Send(u8* Buffer, u16 BufferLength)
{
   ERROR_STATUS Local_error = status_Ok;

   if (Buffer && BufferLength > 0)
   {
      if (UART_TxBuffer.State == idle)
      {
         UART_TxBuffer.DataBuffer = Buffer;
         UART_TxBuffer.DataLength = BufferLength;
         UART_TxBuffer.DataIndex = 0;
         UART_TxBuffer.State = busy;
         UARTX_REG->DR = UART_TxBuffer.DataBuffer[UART_TxBuffer.DataIndex];

         UART_TxBuffer.DataIndex++;
      }
   }
   else
   {
      Local_error = status_NOk;
   }

   return (Local_error);
}

/*
 *
 * Description: This API receive a data through UART
 * Input: Array and the length of the array
 * Output: void
 *
 */
ERROR_STATUS UART_Recieve(u8* Buffer, u16 BufferLength)
{
   ERROR_STATUS Local_error = status_Ok;

   if (Buffer && BufferLength > 0)
   {
      if (UART_RxBuffer.State == idle)
      {
         UART_RxBuffer.DataBuffer = Buffer;
         UART_RxBuffer.DataLength = BufferLength;
         UART_RxBuffer.DataIndex = 0;
         UART_RxBuffer.State = busy;
      }
   }
   else
   {
      Local_error = status_NOk;
   }

   return (Local_error);
}

extern UART_BufferState_t UART_IsTxBufferEmpty(void)
{
   return UART_TxBuffer.State;
}

/*
 *
 * Description: This API take the call back function which execute when recieving is done
 * Input: Function name
 * Output: void
 *
 */
extern ERROR_STATUS UART_SetRxCbf(UART_Rxcbf_t Rxcbf)
{
   ERROR_STATUS Local_error = status_Ok;

   if (Rxcbf)
   {
      appRxNotify = Rxcbf;
   }
   else
   {
      Local_error = status_NOk;
   }

   return (Local_error);
}

void USART1_IRQHandler(void)
{
   if (UARTX_REG->SR & UART_SR_RXNE)
   {
      /*  Clear RXNE Bit */
      UARTX_REG->SR &= UART_SR_RXNE_CLR;

      if (UART_RxBuffer.State == busy)
      {
         UART_RxBuffer.DataBuffer[UART_RxBuffer.DataIndex] = UARTX_REG->DR;
         UART_RxBuffer.DataIndex++;

         if (UART_RxBuffer.DataIndex == UART_RxBuffer.DataLength)
         {
            UART_RxBuffer.DataBuffer = NULL;
            UART_RxBuffer.DataLength = 0;
            UART_RxBuffer.DataIndex = 0;
            UART_RxBuffer.State = idle;

            if (appRxNotify)
            {
               appRxNotify();
            }
         }
      }
      else
      {

      }
   }

   if (UARTX_REG->SR & UART_SR_TC)
   {
      /* Clear TC Bit */
      UARTX_REG->SR &= UART_SR_TC_CLR;

      if (UART_TxBuffer.DataIndex != UART_TxBuffer.DataLength)
      {
         UARTX_REG->DR = UART_TxBuffer.DataBuffer[UART_TxBuffer.DataIndex];
         UART_TxBuffer.DataIndex++;
      }
      else
      {
         UART_TxBuffer.DataBuffer = NULL;
         UART_TxBuffer.DataLength = 0;
         UART_TxBuffer.DataIndex = 0;
         UART_TxBuffer.State = idle;

         if (appTxNotify)
         {
            appTxNotify();
         }
      }
   }
}

extern ERROR_STATUS UART_SetTxCbf(UART_Txcbf_t Txcbf)
{
   ERROR_STATUS Local_error = status_Ok;

   if (Txcbf)
   {
      appTxNotify = Txcbf;
   }
   else
   {
      Local_error = status_NOk;
   }

   return (Local_error);
}

