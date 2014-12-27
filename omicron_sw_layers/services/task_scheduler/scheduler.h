/****************************************************************************************************/
/**
\file       scheduler.h
\brief      Task scheduler function prototypes
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

#ifndef __SCHEDULER_H        /*prevent duplicated includes*/ 
#define    __SCHEDULER_H    

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

/** Tasks definition */
#include    "tasks.h"
/** Dynamic Memory allocation services */
#include    "memory_allocation.h"
/** PIT definitions and prototypes */
#include    "pit.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/
typedef enum tTaskStates
{
    SUSPENDED,
    READY,
    RUNNING
};
typedef struct 
{
    enum tSchedulerTasks_ID     TaskId;
    tPtr_to_function            ptrTask;
    enum tTaskStates            enTaskState;
    UINT8                       u8Priority;       
    
}tSchedulingTask;

/* Task Scheduler Tasks IDs definitions */
typedef enum tSchedulerTasks_ID 
{   
    TASKS_1_MS,
    TASKS_2_MS_A,
    TASKS_2_MS_B,
    TASKS_10_MS,
    TASKS_50_MS,
    TASKS_100_MS,
    TASKS_EVENT_A,
    TASKS_EVENT_B,
    TASKS_EVENT_C,
    TASKS_EVENT_D,
    TASKS_EVENT_E,
    TASKS_EVENT_F,
    TASK_NULL,
};
/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/* Global Task Scheduler Status definitions */
#define    TASK_SCHEDULER_INIT              0x00u
#define    TASK_SCHEDULER_RUNNING           0x01u
#define    TASK_SCHEDULER_OVERLOAD_1MS      0x02u
#define    TASK_SCHEDULER_OVERLOAD_2MS_A    0x03u
#define    TASK_SCHEDULER_OVERLOAD_2MS_B    0x04u
#define    TASK_SCHEDULER_HALTED            0xAAu

#define    TASK_SCH_MAX_NUMBER_TIME_TASKS   0x06u
#define    TASK_SCH_MAX_NUMBER_EVENT_TASKS  0x05u

/*****************************************************************************************************
* Definition of module wide VARIABLEs
*****************************************************************************************************/

extern tSchedulingTask TimeTriggeredTasks[TASK_SCH_MAX_NUMBER_TIME_TASKS];

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** Sheduler Initalization (arming) */
void vfnScheduler_Init( void  );

/** Scheduler kick-off function */
void vfnScheduler_Start( void  );

/** Scheduler stop function */
void vfnScheduler_Stop( void  );

/** Scheduler - Event driven activation handler */
UINT8 u8Scheduler_EventActivationHandler(tPtr_to_function ptrTask, enum tSchedulerTasks_ID TaskId, UINT8 priority); 

/** Scheduler, schedule point */
void vfnSchedulepoint( void );

/** Multi-thread round robin task scheduler */
void vfnTask_Scheduler( void  );

/** Time triggered tasks activation handler - */
void vfnScheduler_Callback( void  );


#endif /* __SCHEDULER_H */ 