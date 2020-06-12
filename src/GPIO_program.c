/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 17 Feb 2020                            */
/* Layer: MCAL                                  */
/* Component: GPIO                              */
/* File Name: GPIO.c                            */
/************************************************/

#include "STD_TYPES.h"

#include "GPIO_interface.h"



#define MODE_CONFIG_CLEAR 0x0000000F
#define MODE_CONFIG_SIZE 4

typedef struct {
  u32 CRL;
  u32 CRH;
  u32 IDR;
  u32 ODR;
  u32 BSRR;
  u32 BRR;
  u32 LCKR;
  
} GPIO;


/* 
  Description: This function shall initiate GPIO pin, by setting its number, port, mode and configuration
  
  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
  
  Output: ERROR_STATUS

 */
extern ERROR_STATUS GPIO_initPin(GPIO_t * peri)
{
  ERROR_STATUS currentStatus = status_Ok;
  u32 temp;
  u32 modeConfiguration;
  u32 updatedPin;
  u32 pinLoopPosition,realPosition,currentPosition;
  
  GPIO * PORT = (GPIO *) peri->port;
  
  /* Setting CRL pins configurations */
  for (pinLoopPosition = 0x00; pinLoopPosition < 0x08; pinLoopPosition++)
  {
    realPosition = (0x01) << pinLoopPosition;
    currentPosition = realPosition & peri->pin;
    /* Extracting the pin number */
    if (currentPosition == realPosition)
    {
      temp = PORT->CRL & ~(MODE_CONFIG_CLEAR << ( pinLoopPosition * MODE_CONFIG_SIZE));
      modeConfiguration = peri->mode | peri->configuration;
      temp |= modeConfiguration << (pinLoopPosition * MODE_CONFIG_SIZE);
      PORT->CRL = temp; 
    }
  }
  
  /* Setting CRH pins configurations */
  for (pinLoopPosition = 0x08; pinLoopPosition < 0x10; pinLoopPosition++)
  {
    realPosition = (0x01) << pinLoopPosition;
    currentPosition = realPosition & peri->pin;
    /* Extracting the pin number */
    if (currentPosition == realPosition)
    {
      updatedPin = pinLoopPosition - 0x08;
      temp = PORT->CRH & ~(MODE_CONFIG_CLEAR << ( updatedPin * MODE_CONFIG_SIZE));
      modeConfiguration = peri->mode | peri->configuration;
      temp |= modeConfiguration << (updatedPin * MODE_CONFIG_SIZE);
      PORT->CRH = temp; 
    }
  }
 
  return currentStatus;
}

/* 
  Description: This function shall write value on pin 
  
  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
        2- value -> The value to be written on pin, options are:
           1) PIN_SET
           2) PIN_RESET
  
  Output: ERROR_STATUS

 */
extern ERROR_STATUS GPIO_writePin(GPIO_t * peri, u32 value)
{
  
  ERROR_STATUS currentStatus = status_Ok;
  
  GPIO * PORT = (GPIO *) peri->port;
  
  if (value == PIN_SET)
  {
    PORT->BSRR = peri->pin;
  }
  else if (value == PIN_RESET)
  {
    PORT->BRR = peri->pin;
  }
  else
  {
    currentStatus =  status_NOk;
  }
  return currentStatus;
}



/* 
  Description: This function shall read value of a pin 
  
  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
        2- value -> pointer to hold value of a pin, return options are:
           1) PIN_SET
           2) PIN_RESET
  
  Output: ERROR_STATUS

 */
extern ERROR_STATUS GPIO_readPin(GPIO_t * peri, u32 *value)
{
  ERROR_STATUS status = status_Ok;
  
  GPIO * PORT = (GPIO *) peri->port;
  
  *value = PORT->IDR & peri->pin;
    
  return status;
}



