/****************************************************************************************************/
/**
\file       memory_allocation.h
\brief      Dynamic Memory allocation services.
\author     Abraham Tezmol
\version    1.0
\date       21/09/2013
*/
/****************************************************************************************************/

#ifndef __MEMORY_ALLOCATION_H        /*prevent duplicated includes*/ 
#define    __MEMORY_ALLOCATION_H    

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
/** Dynamic Memory allocation configuration definitions */
#include    "cnf_mem_alloc.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/* Data type definitions for near memory */

typedef struct 
{
    enum tPagedRAMpages         RamPageId;
    tu8ptr_near                 ptr_nearCurrentAddress;
    tu8ptr_near                 ptr_nearEndAddress;       
    UINT16                      u16_FreeBytes;
}tNearRAMpages_status;

typedef struct 
{      
    tNearRAMpages_status *      RamPageStatus;
    UINT8                       u8NumberOfPages;
}tNearMemAlloc_status;

/* Data type definitions for far memory */
typedef struct 
{
    enum tPagedRAMpages         RamPageId;
    tu8ptr_far                  ptr_CurrentAddress;
    tu8ptr_far                  ptr_EndAddress;       
    UINT16                      u16_FreeBytes;
}tPagedRAMpages_status;

typedef struct 
{      
    tPagedRAMpages_status *     RamPageStatus;
    UINT8                       u8NumberOfPages;
}tMemAlloc_status;
/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

#define MEM_ALLOC_1_BYTE_ALIGN  0xFFFF
#define MEM_ALLOC_2_BYTE_ALIGN  0xFFFE
#define MEM_ALLOC_4_BYTE_ALIGN  0xFFFC

/*****************************************************************************************************
* Declaration of module wide VARIABLEs
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS - NEAR ALLOCAATION
*****************************************************************************************************/
/** Dynamic Memory Allocation Initialization */
void vfnMemAlloc_NearInit( const tNearMemAlloc_config * mem_alloc_config  );
/** Dynamic Memory Allocation - Actual allocation mechanism */
tu8ptr_near MemAlloc_NearReserve( UINT16  u16SizeinBytes);
/** Dynamic Memory Allocation - RAM Erase mechanism */
void vfnMemAlloc_NearErase( tu8ptr_near StartAddress , UINT16  u16SizeinBytes);


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS - FAR ALLOCAATION
*****************************************************************************************************/
/** Dynamic Memory Allocation Initialization */
void vfnMemAlloc_Init( const tMemAlloc_config * mem_alloc_config  );
/** Dynamic Memory Allocation - Actual allocation mechanism */
tu8ptr_far MemAlloc_Reserve( UINT16  u16SizeinBytes );
/** Dynamic Memory Allocation - RAM Erase mechanism */
void vfnMemAlloc_Erase( tu8ptr_far StartAddress , UINT16  u16SizeinBytes);

#endif /* __MEMORY_ALLOCATION_H */ 