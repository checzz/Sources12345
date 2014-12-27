/****************************************************************************************************/
/**
\file       J2716.cxgate
\brief      SW PWM signal generation functions for the XGATE
\author     Team 3
\version    1.0
\date       30/10/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Core modules */
#include "J2716_App.h"
/** driver types Configuration Options */

/** prototypes and main header Configuration Options */

/** frecuency values */
#include "pll.h"
#include "xgate_config.h"
#include "pit.h"
#include "gpio.h"
#include "J2716.h"
#include "Adc.h"
/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/
static uint8 J2716__u8Counter=0;
static uint8 J2716_AppCh0[6];
static uint8 J2716_AppCh1[3];

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/
static void J2716_vSplitNibbles(uint16 u16Val,uint8 u8Nibbles,uint8 * pu8Buffer );

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/
#define J2716_APP_CLR_LOW_NIBBLE    ((uint8)0xFC)
#define J2716_APP_LOW_NIBBLE_MSK    ((uint8)0x03)
/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
void J2716_100ms(void)
{
  uint8 u8TempPort;
  
  u8TempPort = PORTA;                         /* Read PORTA curernt value */
  u8TempPort&= J2716_APP_CLR_LOW_NIBBLE;       /* Clear low nibble*/
  u8TempPort|= J2716__u8Counter;               /* Append counter value*/
  PORTA = u8TempPort;                         /* Display value on LEDs (PA0...PA3) */
  
  J2716__u8Counter++;
  J2716__u8Counter&=J2716_APP_LOW_NIBBLE_MSK; /* Mask low nibble (0-15 values allowed) */
}

static void J2716_vSplitNibbles(uint16 u16Val,uint8 u8Nibbles,uint8 * pu8Buffer )
{
  uint8  i;
  uint8  u8TempNibble=0;
  uint16 u16Temp=0;
  
  /* Mask 12bits */
  u16Temp = u16Val & 0x0FFF;
  for(i=0; i < u8Nibbles; i++ )
  {
     u8TempNibble = (uint8) (u16Temp & 0x000F);
     pu8Buffer[i] = u8TempNibble;
     u16Temp>>=4;
  }
}

void J2716_Cbk0(void)
{
  uint16 u16AdcValCh0 = 0;
  uint16 u16AdcValCh1 = 0;
  Std_ReturnType xReturn = E_OK;

  PORT_ON(PORTA,PORTA_PA2_MASK);
  u16AdcValCh0 = ADC_u16GetValue(J2716_Ch0);
  u16AdcValCh1 = ADC_u16GetValue(J2716_Ch1);
  J2716_vSplitNibbles(u16AdcValCh0,3,&J2716_AppCh0[0]);
  J2716_vSplitNibbles(u16AdcValCh1,3,&J2716_AppCh0[3]);

  /* Copy data into the other J2716 */
  J2716_AppCh1[0] = J2716_AppCh0[3];
  J2716_AppCh1[1] = J2716_AppCh0[4];
  J2716_AppCh1[2] = J2716_AppCh0[5];
  xReturn=J2716_Transmit(J2716_Ch0,&J2716_AppCh0[0]);
  xReturn=J2716_Transmit(J2716_Ch1,&J2716_AppCh1[0]);
  PORT_OFF(PORTA,PORTA_PA2_MASK);
}

void J2716_Cbk1(void)
{
  uint16 u16AdcValCh1 = 0;
  Std_ReturnType xReturn = E_OK;

  PORT_ON(PORTA,PORTA_PA3_MASK);
  u16AdcValCh1 = ADC_u16GetValue(J2716_Ch1);
  J2716_vSplitNibbles(u16AdcValCh1,3,&J2716_AppCh1[0]);
  xReturn=J2716_Transmit(J2716_Ch1,&J2716_AppCh1[0]);
  PORT_OFF(PORTA,PORTA_PA3_MASK);
}