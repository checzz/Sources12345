/****************************************************************************************************/
/**
\file       timer.h
\brief      Timer initialization and low-level functions and prototypes
\author     Abraham Tezmol
\version    1.0
\date       14/Sep/2012
*/
/****************************************************************************************************/
#ifndef __TIMER_H        /*prevent duplicated includes*/
#define __TIMER_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core Modules */
/** Configuration Options */
#include    "configuration.h"
/** S12X derivative information */
#include    __MCU_DERIVATIVE
/** Variable types and common definitions */
#include    "typedefs.h"

/** Used Modules */
/** PLL definitions and prototypes*/
#include    "pll.h"
/* XGATE relevant data types and prototypes */
#include    "xgate_vectors.h"
/** XGATE Intrinsics */
#include    "intrinsics_xgate.h"


/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/


#pragma DATA_SEG SHARED_DATA

#pragma DATA_SEG DEFAULT

#pragma DATA_SEG XGATE_DATA

#pragma DATA_SEG DEFAULT	

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/** Periodic Interrupt Timer definitions */

#define    TIMER_HIGH_RANGE                         (UINT8)1
#define    TIMER_LOW_RANGE                          (UINT8)0

#define    TIMER_PRECISION_FREQ_HIGH                (UINT32)12000000
#define    TIMER_PRECISION_FREQ_LOW                 (UINT32)120000


/** Timer macros */    
#define    TIMER_PRECISION_PRS_VALUE_HIGH          ( UINT8 ) ( ( gu32BusFrequency  / TIMER_PRECISION_FREQ_HIGH  ) - 1 )
#define    TIMER_PRECISION_PRS_VALUE_LOW          ( UINT8 ) ( ( gu32BusFrequency  / TIMER_PRECISION_FREQ_LOW  ) - 1 )



/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

#pragma CODE_SEG XGATE_CODE 

/** Timer Low level initialization */
    void vfnTimer_Init( void );
    
/** Timer Low level Start procedure */
    void vfnTimer_Start(void);    

/** Timer Low level Stop procedure */    
    void vfnTimer_Stop(void);

/** Timer Low level update procedure */
    void vfnTimer_ScheduleEvent(  UINT16 u16Timeout, UINT8 level );
    void vfnTimer_SetClockSource( UINT8 u8ClockSource );
    void vfnTimer_DrivePinState (UINT8 level);
    void vfnTimer_DriveRPMPinState (UINT8 level);

#pragma CODE_SEG DEFAULT 
    void vfnTimer_ScheduleEventRPM( UINT16 u16Timeout, UINT8 level );
    void vfnTimer_DriveRPMPinState_Main (UINT8 level);

/*******************************************************************************/

#endif /* __TIMER_H */