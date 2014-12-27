/****************************************************************************************************/
/**
\file       watchdog.h
\brief      Computer operating properly functions and prototypes.
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

#ifndef __WATCHDOG_H
#define __WATCHDOG_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Core Modules */
/** Configuration Options */
  #include    "configuration.h"
/** MCU derivative information */
  #include    __MCU_DERIVATIVE
/** Variable types and common definitions */
  #include    "typedefs.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/* COP watchdog state machine status definitions: */
#define COPWATCHDOG_DISARMED        0u
#define COPWATCHDOG_ARMED           1u

/* COP watchdog timeout periods definition */
        /* Normal COP Operation:    */
        /* COPCTL_WCOP = 0u;         */
        /* Allow the COP and RTI counters to stop whenever the MCU is in active BDM mode */
        /* COPCTL_RSBCK = 0u;        */
        /* Write of WCOP and CR[2:0] has an effect with this write of COPCTL */
        /* COPCTL_WRTMASK = 0u;      */
        /* COP watchdog rate:  OSCCLK Cycles to Timeout = 2^22 (524.28ms @ 8MHz approximately) */
        /* COPCTL_CR2 = 1u;          */
        /* COPCTL_CR1 = 0u;          */
        /* COPCTL_CR0 = 1u;          */
#define COPWATCHDOG_TIMEOUT_DISABLED            0x40u
#define COPWATCHDOG_TIMEOUT_2_TO_14_CYCLES      0x41u
#define COPWATCHDOG_TIMEOUT_2_TO_16_CYCLES      0x42u
#define COPWATCHDOG_TIMEOUT_2_TO_18_CYCLES      0x43u
#define COPWATCHDOG_TIMEOUT_2_TO_20_CYCLES      0x44u
#define COPWATCHDOG_TIMEOUT_2_TO_22_CYCLES      0x45u
#define COPWATCHDOG_TIMEOUT_2_TO_23_CYCLES      0x46u
#define COPWATCHDOG_TIMEOUT_2_TO_24_CYCLES      0x47u


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** COP watchdog initalization (arming) */
void vfnCOPWatchdog_Init(void);

/** COP watchdog timeout reset */
void vfnCOPWatchdog_Reset(void);

/** MCU reset by means of the COP watchdog */
void vfnCOPWatchdog_MCUReset(void);

/*=================================================================================================*/
#endif /*__WATCHDOG_H */
