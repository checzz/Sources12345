/****************************************************************************************************/
/**
\file       xgate_config.c
\brief      XGATE configuration services.
\author     Abraham Tezmol
\version    1.0
\date       15/03/2010
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
/** XGATE definitions */
#include    "xgate_config.h"

/** Used modules */
/** Common defines and macros */
#include <hidef.h>  

/** Variable types and common definitions */
#include "typedefs.h"

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

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    XGATE Configuration module - Initialization of XGATE cpu
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfn_XGATE_CPU_init( void  )
{
	/* Initialize the XGATE vector block and the XGVBR register */    
    XGVBR= (unsigned int)(void*__far)(XGATE_VectorTable - XGATE_VECTOR_OFFSET);    
    
    /* Access to configuration data registers for interrupts */ 
    INT_CFADDR      = 0x70;         /* with vectors from 0xFF70 to 0xFF7E */
    INT_CFDATA1_PRIOLVL = 6;        /* XGATE software trigger 0, priority 6 */
    INT_CFDATA1_RQST = 1;           /* routed to XGATE */
    
    /* Enable XGATE mode and interrupts */
    XGMCTL= 0xFBC1;      
}


/****************************************************************************************************/
/**
* \brief    XGATE Configuration module - XGATE Software Triggers status command
* \author   Abraham Tezmol
* \param    u8TriggerNumber - [0,7]
* \param    u8TriggerMask   - [0,1]
* \return   void
* \todo     
*/
void XGATE_SW_TRIGGER(UINT8 u8TriggerNumber, UINT8 u8TriggerMask)
{
	UINT16 u16temp = 0x0000u;
	
	if ((u8TriggerNumber< 8) && (u8TriggerMask < 2))
	{
		u16temp = 	(UINT16)  ( ( (UINT16)( ( 1 << u8TriggerNumber ) << 8				) ) | 
							 	( (UINT16)( u8TriggerMask            << u8TriggerNumber	) )
							  );
		XGSWT = 	u16temp;
		
	}
}
/****************************************************************************************************/