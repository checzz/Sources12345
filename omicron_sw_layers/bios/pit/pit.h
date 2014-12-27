/****************************************************************************************************/
/**
\file       pit.h
\brief      Periodic Interrupt Timer initialization and low-level functions and prototypes
\author     Abraham Tezmol
\version    1.0
\date       11/Abr/2010
*/
/****************************************************************************************************/
#ifndef __PIT_H        /*prevent duplicated includes*/
#define __PIT_H

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
  #include "xgate_vectors.h"
/** XGATE Intrinsics */
	#include "intrinsics_xgate.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* vfnPIT0_Callback, function to be called upon timeout of PIT channel 0 */
extern tCallbackFunction vfnPIT0_Callback;

#pragma DATA_SEG SHARED_DATA
/* vfnPIT1_Callback, function to be called upon timeout of PIT channel 1 */
	extern tCallbackFunction vfnPIT1_Callback;

#pragma DATA_SEG DEFAULT
	

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/** Periodic Interrupt Timer definitions */
#define    PIT_uTIMER_FREQ_S12              (UINT32)1000000
#define    PIT_uTIMER_FREQ_XGATE_HIGH       (UINT32)48000000
#define    PIT_uTIMER_FREQ_XGATE_LOW        (UINT32)240000

#define    PIT_uTIMER_HIGH_RANGE            (UINT8)1
#define    PIT_uTIMER_LOW_RANGE             (UINT8)0

#define    PIT_TARGET_FREQ_S12              (UINT32)2000
#define    PIT_TARGET_FREQ_XGATE            (UINT32)6000 
#define    PIT_J2716_TARGET_FREQ_XGATE      (UINT32)335000/*Value to set period to ~3us*/

/** Periodic Interrupt Timer macros */
#define    PIT_MICROTIMER_DIV_S12           ( UINT8 ) ( ( gu32BusFrequency / PIT_uTIMER_FREQ_S12   ) - 1 )
#define    PIT_uTIMER_DIV_XGATE_HIGH        ( UINT8 ) ( ( gu32BusFrequency / PIT_uTIMER_FREQ_XGATE_HIGH ) - 1 )
#define    PIT_uTIMER_DIV_XGATE_LOW         ( UINT8 ) ( ( gu32BusFrequency / PIT_uTIMER_FREQ_XGATE_LOW ) - 1 )


#define    PIT_VALUE_S12                    ( ( PIT_uTIMER_FREQ_S12   / PIT_TARGET_FREQ_S12     ) - 1 )
#define    PIT_VALUE_XGATE_0(value)         ( ( PIT_uTIMER_FREQ_XGATE_HIGH / value ) - 1 )
#define    PIT_VALUE_XGATE_1(value)         ( ( PIT_uTIMER_FREQ_S12 / value ) - 1 )
#define    PIT_J2716_VALUE_XGATE(value)     ( ( PIT_uTIMER_FREQ_XGATE_HIGH / value ) - 1 )

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** PIT Low level initialization */
void vfnPIT0_Init(tCallbackFunction  Callback, UINT8 u8Core);

#pragma CODE_SEG XGATE_CODE 
void vfnPIT1_Init(tCallbackFunction Callback, UINT8 u8Core);
	void vfnPIT2_Init(tCallbackFunction Callback, UINT8 u8Core);
#pragma CODE_SEG DEFAULT 

/** PIT Low level Start procedure */
void vfnPIT0_Start(void);

/** PIT Low level Start procedure */
void vfnPIT1_Start(void);

/** PIT Low level Start procedure */
void vfnPIT2_Start(void);

/** PIT Low level Stop procedure */
void vfnPIT_Stop(void);

/** PIT force load new timeout value procedure */
#pragma CODE_SEG XGATE_CODE
    void vfnPIT1_ForceTimeoutLoad(UINT16 u16Timeout);
    void vfnPIT1_ForcePreScalerLoad( UINT8 u8Prescaler );
#pragma CODE_SEG DEFAULT

/** PIT Channel 0 ISR --> Main CPU  */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
	void interrupt  vfnPIT_Channel0_Isr( void  );
#pragma CODE_SEG DEFAULT

/** PIT Channel 1 ISR --> XGATE  */
#pragma CODE_SEG XGATE_CODE
	void interrupt  vfnPIT_Channel1_Isr( void  );
#pragma CODE_SEG DEFAULT

/** PIT Channel 2 ISR --> XGATE  */
#pragma CODE_SEG XGATE_CODE
	void interrupt  vfnPIT_Channel2_Isr( void  );
#pragma CODE_SEG DEFAULT

/** PIT Channel 3 ISR --> XGATE  */
#pragma CODE_SEG XGATE_CODE
	void interrupt  vfnPIT_Channel3_Isr( void  );
#pragma CODE_SEG DEFAULT

/*******************************************************************************/

#endif /* __PIT_H */