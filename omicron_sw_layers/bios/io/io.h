/****************************************************************************************************/
/**
\file       io.h
\brief      Microcontroller low-level input/output initialization functions and prototypes
\author     Abraham Tezmol
\version    1.0
\date       11/Jul/2009
*/
/****************************************************************************************************/

#ifndef __IO_H        /*prevent duplicated includes*/
#define __IO_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Omicron Configuration Options */
#include    "configuration.h"
/** MCU derivative information */
#include    __MCU_DERIVATIVE
/** Variable types and common definitions */
#include    "typedefs.h"

/** Used modules */

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/* Data Direction Register definitions */
#define INPUT           0
#define OUTPUT          1
#define ANALOG_INPUT    2

/* Input pull-up and pull-down definitions */
#define PULL_DOWN       0
#define PULL_UP         1

/* Data output register definition */
#define LOW             0
#define HIGH            1


/** Ports redefinition for macros usability */
#ifndef PTA             
    #define PTA_PTA0 PORTA_PA0 
    #define PTA_PTA1 PORTA_PA1 
    #define PTA_PTA2 PORTA_PA2 
    #define PTA_PTA3 PORTA_PA3 
    #define PTA_PTA4 PORTA_PA4 
    #define PTA_PTA5 PORTA_PA5 
    #define PTA_PTA6 PORTA_PA6 
    #define PTA_PTA7 PORTA_PA7 
#endif

#ifndef PTE             
    #define PTE_PTE0 PORTE_PE0 
    #define PTE_PTE1 PORTE_PE1 
    #define PTE_PTE2 PORTE_PE2 
    #define PTE_PTE3 PORTE_PE3 
    #define PTE_PTE4 PORTE_PE4 
    #define PTE_PTE5 PORTE_PE5 
    #define PTE_PTE6 PORTE_PE6 
    #define PTE_PTE7 PORTE_PE7 
#endif

#ifndef PTB             
    #define PTB_PTB0 PORTB_PB0 
    #define PTB_PTB1 PORTB_PB1 
    #define PTB_PTB2 PORTB_PB2 
    #define PTB_PTB3 PORTB_PB3 
    #define PTB_PTB4 PORTB_PB4 
    #define PTB_PTB5 PORTB_PB5 
    #define PTB_PTB6 PORTB_PB6 
    #define PTB_PTB7 PORTB_PB7 
#endif

#ifndef PTK             
    #define PTK_PTK0 PORTK_PK0 
    #define PTK_PTK1 PORTK_PK1 
    #define PTK_PTK2 PORTK_PK2 
    #define PTK_PTK3 PORTK_PK3 
    #define PTK_PTK4 PORTK_PK4 
    #define PTK_PTK5 PORTK_PK5 
    #define PTK_PTK7 PORTK_PK7 
#endif

#ifndef DDRE_DDRE1
    #define DDRE_DDRE1  DDRE
#endif

/** Status of available push buttons on DEMOS12XEP100 */
#define PP0_push_button         PTIP_PTIP0
#define PP1_push_button         PTIP_PTIP1

#define PUSH_BUTTON_ACTIVE      0u
#define PUSH_BUTTON_INACTIVE    1u

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** Inputs and Outputs Initialization to default values/configuration */
void vfnInputs_Outputs_Init(void);


/**************************************************************************************************/

#endif /* __IO_H */