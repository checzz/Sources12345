/****************************************************************************************************/
/**
\file       xgate_vectors.h
\brief      XGATE configuration services.
\author     Abraham Tezmol
\version    1.0
\date       15/03/2010
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Module definition against multiple inclusion
*****************************************************************************************************/
#ifndef __XGATE_VECTORS_H
#define __XGATE_VECTORS_H

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

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/* XGATE vector table entry */
typedef void (*__near XGATE_Function)(int);

/* XGATE callback function */
typedef void  ( *__near XGATE_CallbackFunction )( void );

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

typedef struct {
		/* Pointer to the handler */
  	XGATE_Function pc;        
  	/* Pointer to the data of the handler */
  	int dataptr;              
} XGATE_TableEntry;

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/* Save current segment definitions */
#pragma push						

	/* Global addressing for access to vector table for HCS12X/XGATE shared setup. */
	#pragma CONST_SEG XGATE_VECTORS  
	
	/* The first elements are unused and need not to be allocated */
	#define XGATE_VECTOR_OFFSET 9							   
	
	extern const XGATE_TableEntry XGATE_VectorTable[];

/* Restore previous segment definitions */
#pragma pop	    


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

#endif /* __XGATE_VECTORS_H */
