/*************************************************************************************************
 * RCC_interface.h
 *         Author: Basma Abdelhakim
 ************************************************************************************************/


#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H


//#define OFF     0U
//#define ON      1U

/***********************************RCC_CR register bits****************************************/
#define HSION   (0x00000001)
#define HSIRDY  (0x00000002)
#define HSEON   (0x00010000)
#define HSERDY  (0x00020000)
#define HSEBYP  (0x00040000)
#define PLLON   (0x01000000)
#define PLLRDY  (0x02000000)

#define HSI_clk (0x00000001)
#define HSE_clk (0x00010000)
#define PLL_clk (0x01000000)

/***********************************************************************************************/


/*****************************RCC_CFGR register bits*********************************************/
#define SW_HSI    (0x00000000)
#define SW_HSE    (0x01)
#define SW_PLL    (0x02)
#define SWS_HSE   (0x00000004)
#define SWS_PLL   (0x00000008)
#define SW_clear  (0xFFFFFFFC)
/***********************************************************************************************/

/********************************PLL clock source configuration********************************/
#define PLL_SRC_HSI_2 (0x00010000)
#define PLL_SRC_HSE   (0x00000000)

#define PLL_x_2       (0x00000000)
#define PLL_x_3       (0x00040000)
#define PLL_x_4       (0x00080000)
#define PLL_x_5       (0x000C0000)
#define PLL_x_6       (0x00100000)
#define PLL_x_7       (0x00140000)
#define PLL_x_8       (0x00180000)
#define PLL_x_9       (0x001C0000)
#define PLL_x_10      (0x00200000)
#define PLL_x_11      (0x00240000)
#define PLL_x_12      (0x00280000)
#define PLL_x_13      (0x002C0000)
#define PLL_x_14      (0x00300000)
#define PLL_x_15      (0x00340000)
#define PLL_x_16      (0x00380000)
#define PLLMUL_clear  (0xFFC3FFFF)
/***********************************************************************************************/

/*****************************************BUS  options*****************************************/
#define AHBENR_BUS   0U
#define APB1ENR_BUS  1U
#define APB2ENR_BUS  2U
/***********************************************************************************************/


/**************************************Peripheral options***************************************/
#define PORTA_Enable (0x00000004)
#define PORTB_Enable (0x00000008)
#define PORTC_Enable (0x00000010)
#define UART_Enable  (0x00004000)
#define FLASH_ENABLE (0x00000010)
/***********************************************************************************************/


/**************************************Clock sources in MHZ*************************************/
#define HSE_MHZ     8U
#define HSI_MHZ     8U
/***********************************************************************************************/


/****************************************Prototypes**********************************************/





/************************************************************************************************
 * Description:
 *          This function is used to enable clock  for the selected peripheral.
 * Inputs:
 *     Bus field can take the following options:
 *           1.AHBENR_BUS
 *           2.APB1ENR_BUS
 *           3.APB2ENR_BUS
 *     peripheral filed can take the following options:
 *           1.PORTA_Enable
 *           2.PORTB_Enable
 *           3.PORTC_Enable
 *  Outputs:
 *       It returns in case of correct execution   OK
 *       It returns in case of incorrect execution NOT_OK
 * ********************************************************************************************/
ERROR_STATUS RCC_EnablePrephiralClock(u8 Bus,u32 periphiral);




#endif
