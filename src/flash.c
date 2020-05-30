/*
 * flash.c
 *
 *  Created on: May 4, 2020
 *      Author: Esraa Awad
 */
#include "STD_TYPES.h"
#include "flash.h"
#include "NVIC_interface.h"


#define FLASH_BASE_ADDRESS		0x40022000
#define FPEC 					((volatile Flash_t *)FLASH_BASE_ADDRESS)


#define FLASH_KEY1  			(u32)0x45670123
#define FLASH_KEY2  			(u32)0xCDEF89AB

#define CR_LOCK					(u32)0x00000080
#define CR_PER					(u32)0x00000002
#define CR_PER_CLR_MASK			(u32)0xFFFFFFFD
#define CR_STRT					(u32)0x00000040
#define CR_MER					(u32)0x00000004
#define CR_MER_CLR_MASK			(u32)0xFFFFFFFB
#define CR_PG					(u32)0x00000001
#define CR_PG_CLR_MASK			(u32)0x0000000E

#define SR_BSY					(u32)0x00000001
#define SR_EOP					(u32)0000000020

#define FLASH_ERASE				(u32)0xFFFFFFFF
#define FLASH_BUSY				(FPEC -> SR) & SR_BSY
#define FLASH_LOCK				(FPEC -> CR) & CR_LOCK
#define HALF_WORD				(u8)16



typedef struct
{

	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 AR;
	u32 reserved[1];
	u32 OBR;
	u32 WRPR;

}Flash_t;




void Flash_Lock (void)
{
	FPEC  -> CR = CR_LOCK;



}
void Flash_unlock (void)
{

	FPEC -> KEYR = FLASH_KEY1;
	FPEC -> KEYR = FLASH_KEY2;


}


void Flash_Init (void)
{

	/* Disable all interrupts */



	/* Unlock the flash */
	Flash_unlock();


}


void Flash_MassErase (void)
{
	if (FLASH_LOCK )
	{
		Flash_unlock();
	}


	while (FLASH_BUSY);

	FPEC -> CR |= CR_MER;

	FPEC -> CR |= CR_STRT;

	while (FLASH_BUSY);

	FPEC -> CR &= CR_MER_CLR_MASK;
	FPEC -> SR |= SR_EOP;

}

ERROR_STATUS Flash_EarsePage (u32  PageAddress)
{
	if (FLASH_LOCK )
	{
		Flash_unlock();
	}


	ERROR_STATUS Local_Error = STD_ERROR_Ok;

	while (FLASH_BUSY);

	FPEC -> CR |= CR_PER;
	FPEC -> AR |= PageAddress;
	FPEC -> CR |= CR_STRT;

	while (FLASH_BUSY);

	if ( PageAddress != FLASH_ERASE)
	{
		Local_Error = STD_ERROR_NOK;
	}

	FPEC -> CR &= CR_PER_CLR_MASK;
	FPEC -> SR |= SR_EOP;

	return (Local_Error);

}

ERROR_STATUS Flash_WriteWord (u32 * FlashAddress , u32 Data )
{
	/* Disable all interrupts */
	NVIC_DisableAllInterrupt();

	ERROR_STATUS Local_Error = STD_ERROR_Ok;

	if (FLASH_LOCK )
	{
		Flash_unlock();
	}

	if (* FlashAddress != FLASH_ERASE)
	{
		Local_Error = STD_ERROR_NOK;
	}

	FPEC -> CR = CR_PG;
	* ((u16*)FlashAddress) = (u16) Data;

	while (FLASH_BUSY);
	FPEC -> SR |= SR_EOP;

	//(u16*)FlashAddress[1] = (u16)(Data >> HALF_WORD);
	*((u16*)FlashAddress +1) = (u16)(Data >> HALF_WORD);

	FPEC -> SR |= SR_EOP;
	FPEC -> CR &= CR_PG_CLR_MASK;

	if (*FlashAddress != Data)
	{
		Local_Error = STD_ERROR_NOK;
	}

	return (Local_Error);



}

ERROR_STATUS Flash_WriteHalfWord (u32 * FlashAddress , u16 Data)
{
	/* Disable all interrupts */
	NVIC_DisableAllInterrupt();



	ERROR_STATUS Local_Error = STD_ERROR_Ok;

	if (FLASH_LOCK )
	{
		Flash_unlock ();
	}

	if (* FlashAddress != FLASH_ERASE)
	{
		Local_Error = STD_ERROR_NOK;
	}

	FPEC -> CR = CR_PG;
	* ((u16*)FlashAddress) =  Data;

	while (FLASH_BUSY);
	FPEC -> SR |= SR_EOP;

	FPEC -> CR &= CR_PG_CLR_MASK;

	if (* ((u16*)FlashAddress) != Data)
	{
		Local_Error = STD_ERROR_NOK;
	}

	return (Local_Error);
}
extern ERROR_STATUS Flash_ProgramWrite (u32 * SourceStartAddress , u32 * DestinationStartAddress , u16 BytesNumber)
{

	/* Disable all interrupts */
	NVIC_DisableAllInterrupt();

	ERROR_STATUS Local_Error = STD_ERROR_Ok;

	u16 index;

	if (FLASH_LOCK )
	{
		Flash_unlock();
	}

	if (*DestinationStartAddress != FLASH_ERASE)
	{
		Local_Error = STD_ERROR_NOK;
	}


	FPEC -> CR = CR_PG;

	for (index = 0 ; index <BytesNumber/2 ; index++ )
	{
		//(u16*)DestinationStartAddress[index] =  (u16*)SourceStartAddress[index];
		*((u16*)DestinationStartAddress+index) =  *((u16*)SourceStartAddress+index);

		while (FLASH_BUSY);
		FPEC -> SR |= SR_EOP;

	}


	FPEC -> CR &= CR_PG_CLR_MASK;


	return (Local_Error);

}











