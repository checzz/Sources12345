/****************************************************************************************************/
/**
\file       pll.c
\brief      S12XE/S12XS CPU and PLL initialization
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
/** PLL prototypes and definitions */
#include "pll.h"

/** Used modules */

/* -- Variables --------------------------------------------------------*/

/* Global variable that holds status of Clock */
UINT16 gu16ClockGlobalStatus;

/* Loss of Lock counter */
UINT16 u16PLL_Loss_of_Lock_Counter;

/* Actual Bus frequency value */
UINT32 gu32BusFrequency;

/*******************************************************************************/
/**
* \brief    PLL initialization.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \notes    Refer to the "System configuration definitions" section of the "ser_pll.h" header file.
*           User shall manually adjust the definitions on this section depending on 
*           the value of the Xtal and the selected PLL frequency.
*           Some macros are provided in the "System clock related macros" section
*           but user adjustment is still required.
*/
void vfnPLL_Init(void)
{       
    /* Disable PLL */
    vfnPLL_OFF();           
    
    #ifdef __S12_CORE
       
        /* Set PLL synthesizer register */
        SYNR_SYNDIV = SYNR_VALUE;         
        /* Set PLL divider register */  
        REFDV_REFDIV = REFDV_VALUE;         
        /* Configure PLL filter for optimal stability and lock time */
        REFDV_REFFRQ = REFFRQ_VALUE;        
        /* Set Postdiv value,  */
        POSTDIV_POSTDIV = POSTDIV_VALUE;                
        /* Configure VCO gain for optimal stability and lock time */
        SYNR_VCOFRQ = VCOFRQ_VALUE;         
        /* Clock Monitor Enable. This is required to enter Self Clock Mode */
        PLLCTL_CME = 1u;                     
        /* Self Clock Mode Enable, If CME & SCME are both asserted and the Clock Monitor
        in the oscillator block detects a loss of clock, Self Clock Mode will be entred */
        PLLCTL_SCME = 1u;                    
        /* Clear Self Clock Mode Interrupt Flag */                                                                          
        CRGFLG_SCMIF = 1u;                   
        /* Interrupt will be requested whenever SCMIF(Self Clock Mode Interrupt Flag) is set */ 
        CRGINT_SCMIE = 1u;                    
    #endif
    
    #ifdef __S08_CORE
    #endif
    
    /* Enable PLL and wait for locking */
    vfnPLL_ON();                          
    /* Once PLL is stable, select it as clock source */
    vfnSelectClockSource_PLL();
}

/*******************************************************************************/
/**
* \brief    Turn PLL ON.
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnPLL_ON(void)
{
    #ifdef __S12_CORE            
        /* PLL enabled */
        PLLCTL_PLLON = 1u;                   
        
        /* Initialize PLL Loss-of-clock event counter */    
        u16PLL_Loss_of_Lock_Counter = 0u;            
        /* Wait until the PLL is within the desired frequency */
        while(!CRGFLG_LOCK)
        {}
        /* Initialize Global status variable to default value */                                   
        gu16ClockGlobalStatus = CLOCK_STATUS_PLL_OK;        
        /* Clear IPLL Lock Interrupt Flag */
        CRGFLG_LOCKIF = 1u;                  
        /* Interrupt will be requested whenever LOCKIF(IPLL Lock Interrupt Flag)is set */        
        CRGINT_LOCKIE = 1u;                        
    #endif
    
    #ifdef __S08_CORE
    #endif                                     
}

/*******************************************************************************/
/**
* \brief    Turn PLL OFF.
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnPLL_OFF(void)
{
    #ifdef __S12_CORE
        /* Disable the PLL */
        PLLCTL_PLLON = 0u;
        /* update global status variable */                                   
        gu16ClockGlobalStatus = CLOCK_STATUS_PLL_OFF;
    #endif
    
    #ifdef __S08_CORE
    #endif
}

/*******************************************************************************/
/**
* \brief    Select PLL as clock source.
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnSelectClockSource_PLL(void)
{
    #ifdef __S12_CORE
        /* Select PLL as clock source */
        CLKSEL_PLLSEL = 1u;
        /* update global status variable */                                   
        gu16ClockGlobalStatus = CLOCK_STATUS_PLL_SELECTED;
        /* update bus frequency variable with PLL frequency value */
        gu32BusFrequency = ACTUAL_BUS_FREQ;
    #endif
    
    #ifdef __S08_CORE
    #endif    
}

/*******************************************************************************/
/**
* \brief    Select Crystal as clock source.
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnSelectClockSource_XTAL(void)
{
    #ifdef __S12_CORE
        /* Select XTAL as clock source */
        CLKSEL_PLLSEL = 0u;
        /* update global status variable */                                   
        gu16ClockGlobalStatus = CLOCK_STATUS_XTAL_SELECTED;
        /* update bus frequency variable with XTAL frequency value */
        gu32BusFrequency = ((UINT32)XTAL_FREQ_KHZ*1000u);
    #endif
    
    #ifdef __S08_CORE
    #endif    
}


/*******************************************************************************/
/**
* \brief    Clock monitor Interrup Service routine.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt vfnPll_Clock_Monitor_Isr(void)
{   
    #ifdef __S12_CORE  
        /* Verify that IPLL Lock Interrupt Flag caused the interrupt */
        if (CRGFLG_LOCKIF == 1u)
        {
            /* Clear IPLL Lock Interrupt Flag */  
            CRGFLG_LOCKIF = 1u;
            /* Update Loss-of-Lock event counter */
            u16PLL_Loss_of_Lock_Counter++;
            if (u16PLL_Loss_of_Lock_Counter >= 5u)
            {
                /* Set gu16ClockGlobalStatus to its appropriate status */
                gu16ClockGlobalStatus = CLOCK_STATUS_PLL_LOCK_ERROR;
                /* Configure all I/O to their default values */
                
                /* If we reach Loss-of-Lock 5 consecutive times, get into an infinite loop */
                for (;;){}
            }
        }
        else
        {        
            /* Verify that Self Clock Mode Interrupt flag caused the interrupt */
            if (CRGFLG_SCMIF == 1u)
            {
                /* Clear Self Clock Mode Interrupt Flag */
                CRGFLG_SCMIF = 1u;
                /* Set gu16ClockGlobalStatus to its appropriate status */ 
                gu16ClockGlobalStatus = CLOCK_STATUS_SCM_ERROR;        
                /* If we reach SCM condition, get into an infinite loop */
                for (;;){}                
            }
        } 
    #endif
    
    #ifdef __S08_CORE
    #endif
}
#pragma CODE_SEG DEFAULT    
/*******************************************************************************/