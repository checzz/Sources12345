/****************************************************************************************************/
/**
\file       tasks.h
\brief      Tasks to be assigned to each execution thread of Task scheduler.
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

#ifndef __TASKS_H
#define    __TASKS_H    

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Task Scheduler functions */
#include    "scheduler.h"

/** GPIO Indication functions */
#include    "GPIO.h"
/** COP watchdog functions and services */
#include    "watchdog.h"
/** RPM control functions */
#include    "rpm_control.h"
/** Serial communication protocol definitions */
#include    "communication_protocol.h"


/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/* List of tasks to be executed @ 1ms */
void TASKS_LIST_1MS( void );

/* List of tasks to be executed @ 2ms, first group */
void TASKS_LIST_2MS_A( void );

/* List of tasks to be executed @ 2ms, second group */
void TASKS_LIST_2MS_B( void );
    
/* List of tasks to be executed @ 10ms */
void TASKS_LIST_10MS(  void );

/* List of tasks to be executed @ 50ms */
void TASKS_LIST_50MS( void );

/* List of tasks to be executed @ 100ms */
void TASKS_LIST_100MS( void );


#endif /*__TASKS_H */ 
