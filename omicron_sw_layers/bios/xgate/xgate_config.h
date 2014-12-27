/****************************************************************************************************/
/**
\file       xgate_config.h
\brief      XGATE configuration services.
\author     Abraham Tezmol
\version    1.0
\date       15/03/2010
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Module definition against multiple inclusion
*****************************************************************************************************/
#ifndef __XGATE_CONFIG_H
#define __XGATE_CONFIG_H

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

/** Used modules */
  #include "xgate_vectors.h"
/** XGATE Intrinsics */
  #include "intrinsics_xgate.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/
#define SOFTWARE_TRIGGER_1			(UINT8)( 0u )
#define SOFTWARE_TRIGGER_2			(UINT8)( 1u )
#define SOFTWARE_TRIGGER_3			(UINT8)( 2u )
#define SOFTWARE_TRIGGER_4			(UINT8)( 3u )
#define SOFTWARE_TRIGGER_5			(UINT8)( 4u )
#define SOFTWARE_TRIGGER_6			(UINT8)( 5u )
#define SOFTWARE_TRIGGER_7			(UINT8)( 6u )
#define SOFTWARE_TRIGGER_8			(UINT8)( 7u )

#define SOFTWARE_TRIGGER_DISABLE	(UINT8)( 0u )
#define SOFTWARE_TRIGGER_ENABLE		(UINT8)( 1u )

/** XGATE access request to hardware semaphore 1 */
#define XGATE_lock_hw_semaphore_1( )        \
{                                           \
    do								        \
    {									    \
      XGSEM = 0x0101;                       \
    }                                       \
    while(!(XGSEM & 0x0001));               \
}

/** XGATE release of hardware semaphore 1 */
#define XGATE_release_hw_semaphore_1( )     \
{                                           \
    XGSEM = 0x0100;                         \
}

#define XGATE_SET_SEM(x)  (XGSEM = 0x0101 << (x))
#define XGATE_TST_SEM(x)  (XGSEM & 0x0001 << (x))
#define XGATE_REL_SEM(x)  (XGSEM = 0x0100 << (x))

#define J2716_SEMAPHORE ((UINT8)0x02)

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** Initialization of XGATE */
void vfn_XGATE_CPU_init(void);

/** XGATE Software Triggers status command (to be used by main core) */
void XGATE_SW_TRIGGER(UINT8 u8TriggerNumber, UINT8 u8TriggerMask);

/** XGATE Software Triggers status command (to be used by XGATE) */
#pragma CODE_SEG XGATE_CODE
	void XGATE_SW_TRIGGER_X(UINT8 u8TriggerNumber, UINT8 u8TriggerMask);
#pragma CODE_SEG DEFAULT

/*****************************************************************************************************
* Declaration of module wide inline FUNCTIONs 
*****************************************************************************************************/







#endif /* __XGATE_CONFIG_H */
