/*************************************************************************************************
 * RCC_program.c
 *         Author: Basma Abdelhakim
 ************************************************************************************************/

#include "STD_TYPES.h"

#include "RCC_interface.h"



#define RCC_BASE_ADREES      0x40021000
#define RCC  ((volatile  RCC_t *)RCC_BASE_ADREES)
typedef struct{
	u32 CR;
	u32 CFGR;
	u32 CIR;
	u32 APB2RSTR;
	u32 APB1RSTR;
	u32 AHBENR;
	u32 APB2ENR;
	u32 APB1ENR;
	u32 BDCR;
	u32 CSR;
}RCC_t;

/***********************************Global variables********************************************/
u32 PLL_CLOCK_SRC = 0;
u32 PLL_MULT_FACTOR = 0;
u32 SYSTEM_cLK=0;
/**********************************************************************************************/


/******************************************Functions*******************************************/


ERROR_STATUS RCC_EnablePrephiralClock(u8 Bus, u32 periphiral) {
	ERROR_STATUS returnValue = status_NOk;
	switch (Bus) {
	case (AHBENR_BUS):
		RCC->AHBENR |= periphiral;
		if (RCC->AHBENR & periphiral) {
			returnValue = status_Ok;
		}
		break;
	case (APB1ENR_BUS):
		RCC->APB1ENR |= periphiral;
		if (RCC->APB1ENR & periphiral) {
			returnValue = status_Ok;
		}
		break;
	case (APB2ENR_BUS):
		RCC->APB2ENR |= periphiral;
		if ( RCC->APB2ENR & periphiral) {
			returnValue = status_Ok;
		}
		break;
	}
	return returnValue;
}
/**********************************************************************************************/



/**********************************************************************************************/
