/*******************************************************************************/
/**
\file       GPIO.c
\brief      General purpose IO functions
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Configuration Options */
#include "configuration.h"
/** MCU derivative information */
#include __MCU_DERIVATIVE
/** Variable types and common definitions */
#include "typedefs.h"

/** Own headers */
/* GPIO routines prototypes */ 
#include "GPIO.h"

/** Used modules */


/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/****************************************************************************************************/
/**
* \brief    Turn a combination of 3 LEDs with a unique blinking pattern, this funcation shall be 
* \brief    called periodically to operate. 
* \author   Abraham Tezmol
* \param    UINT8 u8LED0 - GPIO definition to be used to drive LED 0 
* \param    UINT8 u8LED1 - GPIO definition to be used to drive LED 1 
* \param    UINT8 u8LED2 - GPIO definition to be used to drive LED 2 
* \return   void
*/
void vfnGPIO_FlashMainLED(UINT8 u8LED0,UINT8 u8LED1,UINT8 u8LED2)
{
    static UINT8 u8Counter = 0;
    
    u8Counter++;
    switch (u8Counter)
    {
        case  1:                            
            LED_ON(u8LED0);                     
            LED_OFF(u8LED1);                    
            LED_ON(u8LED2);                     
            break;                          
        case  51:                           
            LED_OFF(u8LED0);                    
            LED_ON(u8LED1);                     
            LED_OFF(u8LED2);                    
            break;                         
        case 100:                           
            u8Counter = 0;                  
            break;                            
    }
}


/****************************************************************************************************/
/**
* \brief    Initialize GPIO port connected to LEDs on eval board
* \author   Abraham Tezmol
* \param    void 
* \return   void
*/
void vfnGPIO_LED_Init(void)
{
    /* Data Port A initialization */
    PORTA = 0x00u;
    /* Data Direction Register Setup */
    DDRA =  0x0Fu;
    /* Data Direction Register Setup for Port P */
    DDRP =  0x00;  
}

/****************************************************************************************************/