/****************************************************************************************************/
/**
\file       cnf_mem_alloc.h
\brief      Configuration of Dynamic Memory Allocation function prototypes
\author     Abraham Tezmol
\version    1.0
\date       21/09/2013
*/
/****************************************************************************************************/

#ifndef __CNF_MEM_ALLOC_H        /*prevent duplicated includes*/ 
#define    __CNF_MEM_ALLOC_H    

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


/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/


typedef enum tPagedRAMpages
{
    RAM_F0,
    RAM_F1,
    RAM_F2,
    RAM_F3,
    RAM_F4,
    RAM_F5,
    RAM_F6,
    RAM_F7,
    RAM_F8,
    RAM_F9,
    RAM_FA,
    RAM_FB,
    RAM_FC,
    RAM_FD,
    RAM_FE,
    RAM_FF,
    RAM_NULL
};

/* Data type definitions for far memory */
typedef UINT8 *__rptr tu8ptr_far;

typedef struct 
{
    enum tPagedRAMpages         RamPageId;
    tu8ptr_far                  ptr_StartAddress;
    tu8ptr_far                  ptr_EndAddress;
}tPagedRAMpages_config;

typedef struct 
{
    UINT8                           u8Number_of_RAM_pages;
    const tPagedRAMpages_config *   ptr_PagedRAMpages_config;
}tMemAlloc_config;


typedef struct 
{
    enum tPagedRAMpages         RamPageId;
    tu8ptr_near                 ptr_nearStartAddress;
    tu8ptr_near                 ptr_nearEndAddress;
}tNearRAMpages_config;

typedef struct 
{
    UINT8                           u8Number_of_RAM_pages;
    const tNearRAMpages_config *    ptr_NearRAMpages_config;
}tNearMemAlloc_config;

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/* Global Dynamic Memory Allocation Configuration Macros  */
#define    MEM_ALLOC_MAX_FAR_RAM_PAGES              0x02u
/* Global Dynamic Memory Allocation Configuration Macros  */
#define    MEM_ALLOC_MAX_NEAT_RAM_PAGES             0x01u

/*****************************************************************************************************
* Declaration of public VARIABLEs / Constants 
*****************************************************************************************************/

extern const tMemAlloc_config  DynamicMemAlloc_config[];

const tNearMemAlloc_config  NearMemAlloc_config[];

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/


#endif /* __CNF_MEM_ALLOC_H */ 