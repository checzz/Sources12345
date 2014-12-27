/****************************************************************************************************/
/**
\file       cnf_emul_eeprom.h
\brief      Configuration of emulated EEPROM function prototypes
\author     Abraham Tezmol
\version    1.0
\date       5/11/2013
*/
/****************************************************************************************************/

#ifndef __CNF_EMUL_EEPROM_H        /*prevent duplicated includes*/ 
#define    __CNF_EMUL_EEPROM_H    

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
/* Interface data structures */
#include    "nvm_data.h"


/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/
/* Data type definitions for far memory */
typedef UINT8 *__rptr tu8ptr_far;

typedef struct 
{
    UINT32          ptrNVM_ValidPattern;
    UINT16          NVM_ValidPattern;
    UINT32          NVM_RAM_start; 
    tu8ptr_far      NVM_ROM_Default; 
    UINT16          u16NVM_Default_size;
    enum tSubsystemType  Subsystem; 
}tEmulEEPROM_config;

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/*~~~~ Identification labels for emulation sectors control ~~~~*/
#define    ACTIVE_SECTOR_VALUE         (UINT16)0x0A0A

/*****************************************************************************************************
* Declaration of public VARIABLEs / Constants 
*****************************************************************************************************/

extern const tEmulEEPROM_config EEEPROM_config[];

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/


#endif /* __CNF_EMUL_EEPROM_H */ 