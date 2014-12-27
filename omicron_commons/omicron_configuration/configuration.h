/****************************************************************************************************/
/**
\file       configuration.h
\brief      Configuration options.
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

#ifndef __CONFIGURATION_H
#define __CONFIGURATION_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Variable types and common definitions */
#include    "typedefs.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/


/*****************************************************************************************************
* Definition of global wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/** Microcontroller Derivative Selection - Select ONLY one */
	#define     __S12XEP100
	/* Other options: */
	/* #define      __S12XS256      */
	/* #define      __S12XEP100     */
	/* #define      __S08DZ60       */

/** Select XTAL and BUS Clock frequency in KHz */

/** BUS clock frequency */
	#define BUS_FREQ_KHZ        48000u       
/** Xtal frequency */ 
	#define XTAL_FREQ_KHZ       4000u 

/** Select Oscillator configuration based on external hardware. Select ONLY one */
	#define OSC_LOOP_CTRLD_PIERCE 
	/* Other options: */
	/* #define  OSC_FULL_SWING_PIERCE   */


/** Microcontroller derivative information */
   
	#ifdef __S12XEP100  
	    /* Type of core */
	    #define __S12_CORE			0u
	    #define __XGATE_CORE		1u
	    /* MCU derivative header file */
	    #define __MCU_DERIVATIVE   <mc9s12xep100.h>
	    /* MCU linker directive file */
	    #define __MCU_LINK_DERIVATIVE  "mc9s12xep100"
	#else
	    #error "Invalid MCU derivative"   
	#endif


#define HAL_ADC_NUMBER_OF_SAMPLES 2

// #define PIT_PULSE_DEBUG


#define SCI_BUFFER_MODE

#define PIT_PAUSE     0
#define PIT_CONTINUE  1

#define ACKNOWLEDGED      0
#define NOT_ACKNOWLEDGED  1

#define PORT_ENABLE   0
#define PORT_DISABLE  1

/** Define static checking compliance */
	#define __MISRA__

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

#endif /* __CONFIGURATION_H */
