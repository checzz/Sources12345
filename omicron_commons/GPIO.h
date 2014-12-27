/*******************************************************************************/
/**
\file       GPIO_macros.h
\brief      Macro definitions for registers access and I/O handling
\author     Abraham Tezmol
\version    0.2
\date       7/07/2008
*/
/*******************************************************************************/

#ifndef _GPIO_H        /*prevent duplicated includes*/
#define _GPIO_H

/*-- Includes ----------------------------------------------------------------*/

/** Core modules */
/** Configuration Options */
#include "configuration.h"
/** MCU derivative information */
#include __MCU_DERIVATIVE
/** Variable types and common definitions */
#include "typedefs.h"

/*-- Variables ---------------------------------------------------------------*/

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/
#define LED_Port    PORTA
#define D0         1
#define D1         2
#define D2         4
#define D3         8
#define D4         16
#define D5         32
#define D6         64
#define D7         128

/*-- Macros ------------------------------------------------------------------*/
/* Indicator LEDs handling */

/** Set LED */ 
#define LED_ON(BitMask)                     (LED_Port |= (UINT8)(BitMask))
/** Clear LED */ 
#define LED_OFF(BitMask)                    (LED_Port &= ~(UINT8)(BitMask))
/** Toggle LED */ 
#define LED_TOGGLE(BitMask)                 (LED_Port ^= (UINT8)(BitMask)) 

/** MaLo: Generic Macros for handling ports */
/** Set BIT */
#define PORT_ON(Port,BitMask)                (Port |= (UINT8)(BitMask))
/** Clear BIT */ 
#define PORT_OFF(Port,BitMask)               (Port &= ~(UINT8)(BitMask))
/** Toggle BIT */ 
#define PORT_TOGGLE(Port,BitMask)            (Port ^= (UINT8)(BitMask))

/*-- Function Prototypes -----------------------------------------------------*/

void vfnGPIO_FlashMainLED(UINT8 u8LED0,UINT8 u8LED1,UINT8 u8LED2);
void vfnGPIO_LED_Init(void);


#endif /* _GPIO_H */

/*******************************************************************************/