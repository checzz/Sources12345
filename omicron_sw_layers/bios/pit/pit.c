/****************************************************************************************************/
/**
\file       pit.c
\brief      Periodic Interrupt Timer initialization and low-level functions and prototypes
\author     Abraham Tezmol
\version    1.0
\date       11/Abr/2010
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
/* Periodic Interrupt Timer routines prototypes */
#include    "pit.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* vfnPIT0_Callback, function to be called upon timeout of PIT channel 0 */
tCallbackFunction vfnPIT0_Callback;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    PIT Low level initialization
* \author   Abraham Tezmol
* \param    tCallbackFunction - Callback, function to be called upon timeout of PIT
* \return   void
*/
void vfnPIT0_Init(tCallbackFunction  Callback, UINT8 u8Core)
{
    /* PIT counter freeze while in Freeze mode */
    PITCFLMT_PITFRZ        = 1u;
    /* Enables PIT channel 0 */
    PITCE_PCE0             = 1u;
    /* 16-bit timer 0 counts with micro time base 0 */
    PITMUX_PMUX0           = 0u;
    /* Interrupt of PIT channel 0 is enabled */
    PITINTE_PINTE0         = 1u;
    /* Clear PTI interrupt flag */
    PITTF_PTF0             = 1u;
    /* Precalculated PIT microtimer (8-bit time base divider)*/
    PITMTLD0               = PIT_MICROTIMER_DIV_S12;
    /* Precalculated PIT count down value */
    PITLD0                 = PIT_VALUE_S12;

    /* Access to configuration data registers for interrupts */
    INT_CFADDR             = 0x70; 	/* with vectors from 0xFF70 to 0xFF7E */ 
    if (u8Core ==__XGATE_CORE) 
    {
    	INT_CFDATA5        = 0x86; 	/* Periodic Interrupt Timer Channel 0, CPU handled, priority 6 */ 
    }
    else
    {
    	INT_CFDATA5        = 0x06; 	/* Periodic Interrupt Timer Channel 0, S12 Core handled, priority 6 */
    }
    
    /*Initialize callback function*/
    vfnPIT0_Callback = Callback;
}

/****************************************************************************************************/
/**
* \brief    PIT channel 0 Low level Start procedure
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnPIT0_Start(void)
{
	/* Load 8-bit microtimer load register 0 into the 8-bit micro timer down-counter 0 */
    PITCFLMT_PFLMT0     = 1u;
    /* Load 16-bit timer load register 0 into the 16-bit timer down-counter 0 */
    PITFLT_PFLT0        = 1u;
    /* Enable Periodic Interrup Timer */
    PITCFLMT_PITE       = 1u;
}

/****************************************************************************************************/
/**
* \brief    PIT channel 1 Low level Start procedure
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnPIT1_Start(void)
{
	/* Load 8-bit microtimer load register 1 into the 8-bit micro timer down-counter 1 */
    PITCFLMT_PFLMT1     = 1u;
    /* Load 16-bit timer load register 1 into the 16-bit timer down-counter 1 */
    PITFLT_PFLT1        = 1u;
    /* Enable Periodic Interrup Timer */
    PITCFLMT_PITE       = 1u;
}

/****************************************************************************************************/
/**
* \brief    PIT channel 1 Low level Start procedure
* \author   Team3
* \param    void
* \return   void
*/
void vfnPIT2_Start(void)
{
	/* Load 8-bit microtimer load register 1 into the 8-bit micro timer down-counter 1 */
    PITCFLMT_PFLMT1     = 1u;
    /* Load 16-bit timer load register 1 into the 16-bit timer down-counter 1 */
    PITFLT_PFLT2        = 1u;
    /* Enable Periodic Interrup Timer */
    PITCFLMT_PITE       = 1u;
}

/****************************************************************************************************/
/**
* \brief    PIT Low level Stop procedure
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnPIT_Stop(void)
{
	/* Disable Periodic Interrup Timer, thus halting time basis of scheduler */
    PITCFLMT_PITE       = 0u;
}

/***************************************************************************************************/
/**
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt  vfnPIT_Channel0_Isr( void  )
{
    /* Verify that Real Time Interrupt caused the interrupt */
    if( PITTF_PTF0 == 1u )
    {
        /*call callback function, if initialized*/
        if( vfnPIT0_Callback != NULL )
        {
            vfnPIT0_Callback( );
        }
    }
    /* Clear the real time interrupt flag */
    PITTF_PTF0 = 1u;
}
#pragma CODE_SEG DEFAULT
/*******************************************************************************/
