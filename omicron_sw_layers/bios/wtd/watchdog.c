/****************************************************************************************************/
/**
\file       watchdog.c
\brief      Computer operating properly functions.
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Used Modules */
/** COP Watchdog definitions */
#include    "watchdog.h"


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
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

UINT8 gu8COPWatchdogStatus;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    COP watchdog - Timer Initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnCOPWatchdog_Init( void  )
{
    gu8COPWatchdogStatus = COPWATCHDOG_DISARMED;

    /* Proceed to arm COP watchdog: */
#ifdef __S12_CORE
    /* Adjust COP watchdog settings, this has to be done in 1 write cycle */
    COPCTL = COPWATCHDOG_TIMEOUT_2_TO_22_CYCLES;
#endif

#ifdef __S08_CORE
#endif
    /* Watchdog has been armed. Update global watchdog status */
    gu8COPWatchdogStatus = COPWATCHDOG_ARMED;
}

/****************************************************************************************************/
/**
* \brief    COP watchdog - Timeout reset
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
//#pragma CODE_SEG RAM_ROUTINES
void vfnCOPWatchdog_Reset( void  )
{
    /* If COP Watchdog has been previously armed, proceed to restart timeout */
    if( gu8COPWatchdogStatus == COPWATCHDOG_ARMED )
    {
    #ifdef __S12_CORE
            /* When COP is enabled, the following applies:                                           */
            /* To restart the COP time-out period one must write 0x55 followed by a write of 0xAA.   */
        ARMCOP = 0x55u;
        ARMCOP = 0xAAu;
    #endif

    #ifdef __S08_CORE
    #endif
    }
    /* If COP watchdog has not been initialized, signal status */
    else
    {
        gu8COPWatchdogStatus = COPWATCHDOG_DISARMED;
    }
}
//#pragma CODE_SEG DEFAULT

/****************************************************************************************************/
/**
* \brief    COP watchdog - Force MCU reset by watchdog timer
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnCOPWatchdog_MCUReset( void  )
{
    /* If COP watchdog has been previously armed, proceed to reset MCU using COP watchdog */
    if( gu8COPWatchdogStatus == COPWATCHDOG_ARMED )
    {
    #ifdef __S12_CORE
            /* When COP is enabled, the following applies:                  */
            /* Writing any value other than 0x55 or 0xAA causes a COP reset */
        ARMCOP = 0x11u;
    #endif

    #ifdef __S08_CORE
    #endif
    }
    /* If COP watchdog has not been initialized, signal status */
    else
    {
        /* Enable COP Watchdog to support reset functionality */
        vfnCOPWatchdog_Init( );
    #ifdef __S12_CORE
            /* When COP is enabled, the following applies:                  */
            /* Writing any value other than 0x55 or 0xAA causes a COP reset */
        ARMCOP = 0x11u;
    #endif

    #ifdef __S08_CORE
    #endif
    }
}
/****************************************************************************************************/
