/*
 * flash.c
 *
 *  Created on: May 7, 2020
 *      Author: kariman
 */

/***************************************** INCLUDES *********************************************/

#include "STD_TYPES.h"
#include "Flash.h"


/***************************************** MASKS ************************************************/

/* Flash Control Register bits */
#define CR_PG_Set                ((u32)0x00000001)
#define CR_PG_Reset              ((u32)0x00001FFE)

#define CR_PER_Set               ((u32)0x00000002)
#define CR_PER_Reset             ((u32)0x00001FFD)

#define CR_MER_Set               ((u32)0x00000004)
#define CR_MER_Reset             ((u32)0x00001FFB)

#define CR_START_Set             ((u32)0x00000040)
#define CR_LOCK_Set              ((u32)0x00000080)

/* FLASH Keys */
#define FLASH_KEY1               ((u32)0x45670123)
#define FLASH_KEY2               ((u32)0xCDEF89AB)

 /* FLASH Busy flag */
#define FLASH_FLAG_BSY           ((u32)0x00000001)
/* FLASH End of Operation flag */
#define FLASH_FLAG_EOP           ((u32)0x00000020)


/******************************************** REGISTERS ********************************************/

#define FLASH_BASE_ADDRESS       ((u32)0x40022000)

typedef struct
{
    u32 ACR;
    u32 KEYR;
    u32 OPTKEYR;
    u32 SR;
    u32 CR;
    u32 AR;
    u32 OBR;
    u32 WRPR;

}FLASH_REGISTERS;


volatile FLASH_REGISTERS*  const FLASH  = (FLASH_REGISTERS*) FLASH_BASE_ADDRESS  ;

/************************************* FUNCTIONS DEFINITIONS ****************************************/

void FLASH_Unlock(void)
{
  /* Authorize the FPEC of Bank1 Access */
  if( (FLASH->CR & CR_LOCK_Set) == CR_LOCK_Set)
  {
	  FLASH->KEYR = FLASH_KEY1;
	  FLASH->KEYR = FLASH_KEY2;
  }
}

void FLASH_Lock(void)
{
  /* Set the Lock Bit to lock the FPEC and the CR of  Bank1 */
  FLASH->CR |= CR_LOCK_Set;
}

void FLASH_ErasePage(u32 pageAddress)
{
	/* wait for busy flag to be cleared */
	while((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY);

	/* SET PER BIT */
	FLASH->CR |= CR_PER_Set ;

    /* WRITE ADDRESS withen the page */
	FLASH->AR = pageAddress ;

	/* SET START BIT */
	FLASH->CR |= CR_START_Set ;

	/* wait for busy flag to be cleared */
	while((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY);

	/* EOP is set by hw to reset EOP we should write one */
	FLASH->SR |=  FLASH_FLAG_EOP ;

	/* RESET PER BIT */
	FLASH->CR &= CR_PER_Reset;
}


//ERROR_STATUS FLASH_WriteWord(void* address , u32 data)
//{
//	/* wait for busy flag to be cleared */
//	while((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY);
//
//    /* set PG  bit to write half word  */
//	FLASH->CR |= CR_PG_Set ;
//
//    /* write LSB FIRST */
//	*( (u16*) address ) =  (u16) data ;
//
//	/* wait for busy flag to be cleared */
//	while((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY);
//
//	/* EOP is set by hw to reset EOP we should write one */
//	FLASH->SR |=  FLASH_FLAG_EOP ;
//
//    /* write MSB SECOND */
//	*( ( ((u16*)address) + 1) ) =  (u16) (data>>16)  ;
//
//	/* wait for busy flag to be cleared */
//	while((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY);
//
//	/* EOP is set by hw to reset EOP we should write one */
//	FLASH->SR |=  FLASH_FLAG_EOP ;
//
//	/* RESET PG BIT  */
//	FLASH->CR &= CR_PG_Reset ;
//
//	/* check if data is written correctly or not */
//    if( *( (u32*) address )  ==  data)
//    {
//       return OK;
//    }
//    else
//    {
//       return NOT_OK;
//    }
//}

ERROR_STATUS FLASH_WriteProgramm(void* startAddress , void* dataAddress , u16 numberOfBytes)
{
   ERROR_STATUS state = OK;

	u16 idx;

	/* wait for busy flag to be cleared */
	while((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY);

    /* set PG  bit to write half word */
	FLASH->CR |= CR_PG_Set ;

	for(idx=0; idx < numberOfBytes/2 ; idx++)
	{
	    /* write byte */
		*( ( ((u16*)startAddress) + idx ) ) =  (u16)  ( *( ( ((u16*)dataAddress) + idx ) ) );

		/* wait for busy flag to be cleared */
		while((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY);

		/* EOP is set by hw to reset EOP we should write one */
		FLASH->SR |=  FLASH_FLAG_EOP ;
	}

	/* wait for busy flag to be cleared */
	while((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY);

	/* RESET PG BIT  */
	FLASH->CR &= CR_PG_Reset ;

   for(idx=0; idx < numberOfBytes/2 ; idx++)
   {
       /* read byte */
      if ( *((u16*)startAddress + idx) != *((u16*)dataAddress + idx) )
      {
         state = NOT_OK;
         break;
      }
   }

   return state;
}

