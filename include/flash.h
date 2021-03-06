/*
 * flash.h
 *
 *  Created on: May 4, 2020
 *      Author: Esraa Awad
 */



#ifndef FLASH_H
#define FLASH_H





extern void FLASH_Unlock(void);

extern void FLASH_Lock(void);

extern void FLASH_ErasePage(u32 pageAddress);


ERROR_STATUS FLASH_WriteWord(void* address , u32 data);

ERROR_STATUS FLASH_WriteProgramm(void* startAddress , void* dataAddress , u16 numberOfBytes);




#endif







































/*
#ifndef FLASH_H
#define FLASH_H

void Flash_Init (void);

extern ERROR_STATUS Flash_WriteWord (u32 * FlashAddress , u32 Data );
extern ERROR_STATUS Flash_WriteHalfWord (u32 * FlashAddress , u16 Data);
extern ERROR_STATUS Flash_ProgramWrite (u32 * SourceStartAddress , u32 * DestinationStartAddress , u16 BytesNumber);

extern void Flash_MassErase (void);
extern ERROR_STATUS Flash_EarsePage (u32  PageAddress);

extern void Flash_Lock (void);
extern  void Flash_unlock (void);


#endif
*/
