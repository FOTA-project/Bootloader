/*
 * Bootloader
 *
 *  Created on: May 27, 2020
 *      Author: Esraa Awad
 */

#include "STD_TYPES.h"
#include "flash.h"
#include "UART_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "GPIO_interface.h"
#include "protocol.h"

#define VTOR (*((u32*)(0xE000E000UL + 0x0D00UL + 0x8))) /* SCB configuration struct */

#define APP_1_MARKER    0xAAAAAAAA
#define APP_2_MARKER    0xBBBBBBBB
#define NO_APP_MARKER   0x00000000
#define KEY_CORRECT     1
#define KEY_INCORRECT   0
#define PAGE_SIZE       1024
#define START_ADDRESS   0x08002000



typedef void (*AppEntryPoint_t) (void);

__attribute__((section(".marker_section"),used))
 volatile u32 Marker; //APP_1_MARKER

static u32 StartAddress;
static u32 AppSize;
static u32 EntryPoint;
static u8 KeyValue;

u32 CurrentPage;

static u8 RxBuffer[sizeof(ReqDateFrame_t)];
ReqDateFrame_t *ReqFrame = (ReqDateFrame_t*)RxBuffer;

static u8 TxBuffer[sizeof(RespFrame_t)];
RespFrame_t *RespFrame = (RespFrame_t*)TxBuffer;

void Comm_Cb(void)
{
   //trace_printf("RX cb hello\n");

   static u32 counter;
   u8 returnStatus = OK;
   //u8 j;
   //u32 x;
   u32 MARKER_1 = APP_1_MARKER;

   RespFrame->CMD_No     = ReqFrame->ReqHeader.CMD_No;
   RespFrame->Request_No = ReqFrame->ReqHeader.Request_No;

   if (ReqFrame->ReqHeader.CMD_No == Cmd_FlashNewApp)
   {
      if (ReqFrame->Data_t.FlashNewApp.Key == KEY_ENCRYPTION)
      {
         StartAddress = ReqFrame->Data_t.FlashNewApp.StartAddress;
         AppSize      = ReqFrame->Data_t.FlashNewApp.AppSize;
         EntryPoint   = ReqFrame->Data_t.FlashNewApp.EntryPoint;

         KeyValue = KEY_CORRECT;

         RespFrame->Result = OK_RESPONSE;
      }
      else
      {
         KeyValue = KEY_INCORRECT;

         RespFrame->Result = NOK_RESPONSE;
      }
   }
   else if (ReqFrame->ReqHeader.CMD_No == Cmd_WriteSector)
   {
      if (KeyValue == KEY_CORRECT)
      {
         counter += ReqFrame->Data_t.WriteSector.FrameDataSize;

         FLASH_Unlock();

         if ((ReqFrame->Data_t.WriteSector.Address / PAGE_SIZE) != CurrentPage)
         {
            FLASH_ErasePage(ReqFrame->Data_t.WriteSector.Address);

            CurrentPage = ReqFrame->Data_t.WriteSector.Address / PAGE_SIZE;
         }

         //Flash_ProgramWrite ((u32*)&ReqFrame -> Data_t.WriteSector.Data,(u32*)&ReqFrame -> Data_t.WriteSector.Address, ReqFrame -> Data_t.WriteSector.FrameDataSize);
         // TODO: Verify by BL

         //returnStatus |= FLASH_WriteWord((u32*)&ReqFrame -> Data_t.WriteSector.Address , (u32) *( &(ReqFrame -> Data_t.WriteSector.Data)) );
         //returnStatus |= FLASH_WriteWord((u32*)&ReqFrame -> Data_t.WriteSector.Address +4 , (u32) *(&(ReqFrame -> Data_t.WriteSector.Data) + 4 ) );

         returnStatus = FLASH_WriteProgramm((void*) ReqFrame->Data_t.WriteSector.Address,
                                            (void*) ReqFrame->Data_t.WriteSector.Data,
                                            ReqFrame->Data_t.WriteSector.FrameDataSize);

         FLASH_Lock();

         if (returnStatus == OK) // if flashing succeeded
         {
            /*
             for(j=0; j<8 ;j++)
             {
             trace_printf("ROM address  %d  =  %x\n",j , *( (u8*)((ReqFrame -> Data_t.WriteSector.Address) + j)) );
             }
             */

            if (counter >= AppSize)
            {
               FLASH_Unlock();
               FLASH_ErasePage((u32)&Marker);
               //FLASH_WriteWord (&Marker , APP_1_MARKER );  //TODO: APP_1_MARKER need to be modified
               FLASH_WriteProgramm ((void*)&Marker, (void*)&MARKER_1, 4);
               //trace_printf("Marker = %d\n" , Marker );
               FLASH_Lock();

               //RespFrame -> Result = OK_RESPONSE;

               //for(x=0; x < 250000 ;x++);
               //UART_Send(TxBuffer,sizeof(RespFrame_t));

               counter = 0;
            }

            RespFrame->Result = OK_RESPONSE;
         }
         else  // if flashing failed
         {
            RespFrame->Result = NOK_RESPONSE;
         }
      }
      else
      {
         RespFrame->Result = NOK_RESPONSE;
      }
   }
   else
   {
      RespFrame->Result = NOK_RESPONSE;
   }

   //for(x=0; x < 1000000 ;x++);
   UART_Send(TxBuffer, sizeof(RespFrame_t));

   UART_Recieve(RxBuffer, sizeof(ReqDateFrame_t));
}

void main (void)
{
   StartAddress = 0;
   AppSize      = 0;
   EntryPoint   = 0;
   KeyValue     = KEY_INCORRECT;

   AppEntryPoint_t MSP = *(void**)START_ADDRESS;

   const AppEntryPoint_t App1EntryPoint =
         (const AppEntryPoint_t) ((*(u32*) 0x08002004) /*+ 0x2000*/); //EntryPoint
   //const AppEntryPoint_t App2EntryPoint = (const AppEntryPoint_t) ReqFrame -> Data_t.FlashNewApp.EntryPoint;

   switch (Marker)
   {
      case APP_1_MARKER:
         //__set_MSP(*(u32*)StartAddress); // TODO: Init stack pointer of APP1
         asm volatile ("MSR msp, %0\n" : : "p" (MSP) : );
         // Switch vector table
         VTOR = START_ADDRESS;
         App1EntryPoint ();
      break;

      case APP_2_MARKER:
         //   __set_MSP(*(__IO uint32_t*)StartAddress);  // TODO: Init stack pointer of APP2
         //App2EntryPoint();
      break;

      default:
         RCC_EnablePrephiralClock(AHBENR_BUS, FLASH_ENABLE);
         RCC_EnablePrephiralClock(APB2ENR_BUS, PORTA_Enable);
         RCC_EnablePrephiralClock(APB2ENR_BUS, UART_Enable);

         UART_voidInit(USART1);
         UART_SetRxCbf(Comm_Cb);
         //UART_SetTxCbf(txcb);

         UART_Recieve(RxBuffer, sizeof(ReqDateFrame_t));

         while(1)
         {
            if (Marker != NO_APP_MARKER)
            {
               /* fixes a bug where the app marker would be written
                * and immediately the main() code will reset the microcontroller
                * which cancel the transmission of the last ACK.
                * in other words the microcontroller was being reset while the ACK was being sent */
               while (UART_IsTxBufferEmpty() == busy)
               {

               }

               /* System Reset */
               NVIC_ResetSystem();
            }
         }
      break;
   }
}

