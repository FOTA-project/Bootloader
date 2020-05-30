/************************************
 * nvic.c							*
 * Created on: Mar 14, 2020			*
 * Author: Esraa Awad			    *
 * *********************************/

#include "STD_TYPES.h"

#include "NVIC_interface.h"


/**** MASKS  of numbers of sub group and preemption bits for stm23***/
#define   NVIC_PRIGROUP_CLRMask	  0xfffff8ff
#define  	NVIC_NonSubPriority			0x00000300
#define 	NVIC_OneSubthreeGroup		0x00000400
#define 	NVIC_TwoSubTwoGroup			0x00000500
#define 	NVIC_ThreeSubOneGroup		0x00000600
#define 	NVIC_NonGroupPriority		0x00000700

/*** System reset mask **/
#define SCB_AIRCR_VECTKEY_Pos              16U
#define SCB_AIRCR_SYSRESETREQ_Pos           2U
#define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)
/********************************************************************/

#define   NVIC_AIRC 		  *((volatile u32*)0xE000ED0C)    // to set number of sub group bits and sw reset
#define 	MAX_NUM_IRQ 		240
#define 	BITS_NUM			  32




typedef struct
{
	u32 Padding_0[64];
	u32 SETENA[8];
	u32 Dummy_Arr1[24];
	u32 CLRENA[8];
	u32 Dummy_Arr2[24];
	u32 SETPEND[8];
	u32 Dummy_arr3[24];
	u32 CLRPEND[8];
	u32 Dummy_arr4[24];
	u32 ACTIVE[8];
	u32 Dummy_arr5[56];
	u8  IPR[240];
	u32 Dummy_arr6[644];
	u32 STIR;            

}NVIC_t;

NVIC_t * NVIC = ( NVIC_t *)0xE000E000;










/*Description : This API shall Enable interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: Error_s  */

ERROR_STATUS NVIC_u8EnableIRQ (u8 Copy_u8IntReqNum)
{
	u8 Local_u8Error = status_Ok;

	if (Copy_u8IntReqNum < MAX_NUM_IRQ)
	{
		NVIC -> SETENA [Copy_u8IntReqNum/BITS_NUM] |= (1<<(Copy_u8IntReqNum % BITS_NUM));
	}
	\
	else
	{
		Local_u8Error = status_NOk;
	}
	return (Local_u8Error);

}




/*Description : This API shall Disable interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: Error_s  */

ERROR_STATUS NVIC_u8DisbaleIRQ (u8 Copy_u8IntReqNum)
{
	u8 Local_u8Error = status_Ok;

	if (Copy_u8IntReqNum < MAX_NUM_IRQ)
	{
		NVIC -> CLRENA [Copy_u8IntReqNum/BITS_NUM] |= (1<<(Copy_u8IntReqNum % BITS_NUM));
	}
	else
	{
		Local_u8Error = status_NOk;
	}
	return (Local_u8Error);
}












/*Description : This API clear pending of interrupt request number
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 ERROR STATUS*/

ERROR_STATUS NVIC_u8ClearPending (u8 Copy_u8IntReqNum)
{
	u8 Local_u8Error = status_Ok;
	if (Copy_u8IntReqNum < MAX_NUM_IRQ)
	{
		NVIC -> CLRPEND [Copy_u8IntReqNum/BITS_NUM] |= (1<<(Copy_u8IntReqNum % BITS_NUM));
	}
	else
	{
		Local_u8Error = status_NOk;
	}
	return (Local_u8Error);


}

/**********************************************************************************************

 * Function to Disable IRQ Interrupts ( Disable all exception except NMI and hard fault)

 * return Type :- void

 * Input Argument :- void

 *************************************************************************************************/

void NVIC_DisableAllInterrupt(void)

{

	__asm ("CPSID i");

}



/**********************************************************************************************

 * Function to Enable IRQ Interrupts.

 * return Type :- void

 * Input Argument :- void

 *************************************************************************************************/

void NVIC_EnableAllInterrupt(void)

{

	__asm ("CPSIE i");

}



/**********************************************************************************************

 * Function to Disable all fault exceptions.

 * return Type :- void

 * Input Argument :- void

 *************************************************************************************************/

void NVIC_DisableAllFaults(void)

{



	__asm ("CPSID f");



}
/* System reset*/
void NVIC_ResetSystem(void)
{
	__asm("DSB");                                                       /* Ensure all outstanding memory accesses included
                                                                     //  buffered write are completed before reset */
	NVIC_AIRC  = ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
			SCB_AIRCR_SYSRESETREQ_Msk);

	/* Ensure completion of memory access */
	__asm("DSB");

	for(;;)                                                           /* wait until reset */
	{
		__asm ("NOP");
	}
}







