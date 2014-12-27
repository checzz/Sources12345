/****************************************************************************************************/
/**
\file       main.h
\brief      Omicron main application (main module)
\author     Abraham Tezmol Otero, M.S.E.E
\version    1.0
\date       26/Jun/2009
*/
/****************************************************************************************************/

#ifndef __MAIN_H        /*prevent duplicated includes*/
#define __MAIN_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Omicron Configuration Options */
#include     "configuration.h"
/** Variable types and common definitions */
#include     "typedefs.h"
/** MCU derivative information */
#include     __MCU_DERIVATIVE
#pragma LINK_INFO DERIVATIVE __MCU_LINK_DERIVATIVE
/** Common defines and macros */
#include     <hidef.h>

/** Used modules */
/** PLL definitions and prototypes*/
#include     "pll.h"
/** Scheduler function prototypes definitions */
#include     "scheduler.h"
/** Dynamic Memory allocation services */
#include     "memory_allocation.h"
/** COP watchdog functions and services */
#include     "watchdog.h"
/** Interrupts module functions and services */
#include     "interrupt.h"
/** Microcontroller input output low-level pins initialization */
#include     "io.h"
/** Macro definitions for general purpose I/O handling  */
#include     "GPIO.h"
/** XGATE Configuration Options */
#include	  "xgate_config.h"
/** Emulated CAM/CRANK routines prototypes */ 
#include 	  "cam_crank.h"
/** High level Serial communication protocol */
#include      "communication_protocol.h"
/** Emulated EEPROM services */
#include      "emul_eeprom.h"
/** Emulated J2716 Driver */
#include      "J2716.h"
#include      "Adc.h"
/*****************************************************************************************************
* Definition of module wide VARIABLEs - NOT for use in other modules
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs - NOT for use in other modules
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of global wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/
  

/*****************************************************************************************************
* Declaration of project wide FUNCTIONS
*****************************************************************************************************/

/* Main application */
void main( void );


#endif /* __MAIN_H */