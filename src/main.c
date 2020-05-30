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
#include "Diag/trace.h"
//#include "cmsis_gcc.h"


#define     VTOR       *((u32      *)    (0xE000E000UL +  0x0D00UL + 0x8     )  ) /*!< SCB configuration struct */


/*__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_MSP(uint32_t topOfMainStack)
{
  __ASM volatile ("MSR msp, %0\n" : : "r" (topOfMainStack) : "sp");
}*/


#define APP_1_MARKER	0xAAAAAAAA
#define APP_2_MARKER	0xBBBBBBBB
#define NO_APP_MARKER	0x00000000
#define KEY_CORRECT			    1
#define KEY_INCORRECT			0
#define PAGE_SIZE 				1024
#define START_ADDRESS 			0x08002000

typedef void (*AppEntryPoint_t) (void);


__attribute__((section(".marker_section"),used))
u32 Marker =  NO_APP_MARKER;

static u32 StartAddress;
static u32 AppSize;
static u32 EntryPoint;
static u8 KeyValue;


u8 CurrentPage;

static u8 RxBuffer [sizeof (ReqDateFrame_t)] ;
ReqDateFrame_t * ReqFrame = (ReqDateFrame_t *) RxBuffer;

static u8 TxBuffer [sizeof (RespFrame_t)] ;
RespFrame_t * RespFrame = (RespFrame_t *) TxBuffer;

static u8 TxBuffer2 [1] = "H";


void txcb (void)
{
	trace_printf("TX cb hello\n");
}


void Comm_Cb (void)
{

trace_printf("RX cb hello\n");

	static u32 counter;

	RespFrame -> CMD_No = ReqFrame -> ReqHeader.CMD_No;
	RespFrame -> Request_No = ReqFrame -> ReqHeader.Request_No;

	if (ReqFrame -> ReqHeader.CMD_No == Cmd_FlashNewApp  )
	{
		if (ReqFrame ->  Data_t.FlashNewApp.Key == KEY_ENCRYPTION)
		{
			StartAddress = ReqFrame ->  Data_t.FlashNewApp.StartAddress ;
			AppSize = ReqFrame ->  Data_t.FlashNewApp.AppSize ;
			EntryPoint = ReqFrame ->  Data_t.FlashNewApp.EntryPoint ;

			KeyValue = KEY_CORRECT;

			RespFrame -> Result = OK_RESPONSE;
			UART_Send(TxBuffer,sizeof(RespFrame_t));

		}
		else
		{
			KeyValue = KEY_INCORRECT;
			RespFrame ->Result = NOK_RESPONSE;
			UART_Send(TxBuffer,sizeof(RespFrame_t));
		}
	}
	else if (ReqFrame -> ReqHeader.CMD_No == Cmd_WriteSector )
	{
		if (KeyValue == KEY_CORRECT)
		{
			counter +=  ReqFrame -> Data_t.WriteSector.FrameDataSize;

			Flash_unlock();

			if (ReqFrame -> Data_t.WriteSector.Address/PAGE_SIZE != CurrentPage)
			{
				Flash_EarsePage(ReqFrame -> Data_t.WriteSector.Address);
				CurrentPage = ReqFrame -> Data_t.WriteSector.Address/PAGE_SIZE;
			}

			Flash_ProgramWrite ((u32*)&ReqFrame -> Data_t.WriteSector.Data,(u32*)&ReqFrame -> Data_t.WriteSector.Address, ReqFrame -> Data_t.WriteSector.FrameDataSize);

			/* TODO: Verify by BL */

			RespFrame ->Result = OK_RESPONSE;

			UART_Send(TxBuffer,sizeof(RespFrame_t));

			if ( counter == AppSize)
			{
				RespFrame -> Result = OK_RESPONSE;
				UART_Send(TxBuffer,sizeof(RespFrame_t));
				Flash_EarsePage((u32  )&Marker);
				Flash_WriteWord (&Marker , APP_1_MARKER );  //TODO: APP_1_MARKER need to be modified
				counter = 0;
			}
		}
		else
		{
			RespFrame ->Result = NOK_RESPONSE;
			UART_Send(TxBuffer,sizeof(RespFrame_t));
		}

	}

	UART_Recieve(RxBuffer,sizeof(ReqDateFrame_t));
}


void main (void)
{

	AppEntryPoint_t MSP = *(void **) START_ADDRESS;

	const AppEntryPoint_t App1EntryPoint = (const AppEntryPoint_t) EntryPoint  ;
	//const AppEntryPoint_t App2EntryPoint = (const AppEntryPoint_t) ReqFrame -> Data_t.FlashNewApp.EntryPoint;

	switch (Marker)
	{
	case APP_1_MARKER:
		//__set_MSP(*(u32*)StartAddress); // TODO: Init stack pointer of APP1
		 asm volatile ("MSR msp, %0\n" : : "p" (MSP) : );
		 // Switch vector table
		 VTOR = START_ADDRESS ;
		App1EntryPoint();
   break;

	case APP_2_MARKER:
	//	__set_MSP(*(__IO uint32_t*)StartAddress);  // TODO: Init stack pointer of APP2
		//App2EntryPoint();
   break;

	default:
      RCC_EnablePrephiralClock(AHBENR_BUS, FLASH_ENABLE);
      RCC_EnablePrephiralClock(APB2ENR_BUS, PORTA_Enable);
      RCC_EnablePrephiralClock(APB2ENR_BUS, UART_Enable);

		UART_voidInit(USART1);
		UART_SetRxCbf(Comm_Cb);
		UART_SetTxCbf(txcb);
		UART_Send(TxBuffer2, 1 );

		UART_Recieve(RxBuffer,sizeof(ReqDateFrame_t));

      trace_printf("sizeof(FlashNewApp_t) = %d\n", sizeof(FlashNewApp_t));
      trace_printf("sizeof(WriteSector_t) = %d\n", sizeof(WriteSector_t));
      trace_printf("sizeof(ReqHeader_t) = %d\n", sizeof(ReqHeader_t));
      trace_printf("sizeof(ReqDateFrame_t) = %d\n", sizeof(ReqDateFrame_t));
      trace_printf("sizeof(RespFrame_t) = %d\n", sizeof(RespFrame_t));


		while(1)
		{
			if (Marker != NO_APP_MARKER)
			{
				/* System Reset */
				NVIC_ResetSystem();
			}
		}
	}
}
