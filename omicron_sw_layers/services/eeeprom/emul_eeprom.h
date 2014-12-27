/****************************************************************************************************/
/**
\file       emul_eeprom.h
\brief      Emulated EEPROM functions and services.
\author     Abraham Tezmol
\version    1.0.1
\date       08/12/2008
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Module definition against multiple inclusion
*****************************************************************************************************/

#ifndef __EMUL_EEPROM_H        /*prevent duplicated includes*/ 
#define    __EMUL_EEPROM_H    

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Variable types and common definitions */
#include    "typedefs.h"
/** Omicron Bootloader Configuration Options */
#include    "configuration.h"
/** MCU derivative information */
#include    __MCU_DERIVATIVE

/** Used modules */
/* Flash functions and prototypes */
#include    "flash.h"
/** Configuration of Emulated EEPROM */
#include    "cnf_emul_eeprom.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/
extern tCallbackFunction WdgtCallbackFunction;

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

#ifdef __S12XEP100


/* Emulated EEPROM SIZE SECTION */

    /* Specify the # of 256-byte sectors of EEE RAM for Emulation Purposes. Valid range is 0-16 sections: */
#define    ERPART                            12u

    /* Specify the # of 256-byte sectors of Data flash for general use: */
#if (  ERPART  ==  1u  )
#define    DFPART    ( 128u - 12u )
#else
#define    DFPART    ( 128u - ( 8u * ERPART ) )
#endif

#endif

/* ~~~~~~~~~~~~~ Return values used by driver ~~~~~~~~~~~~~~~~*/
/* re-use same value from flash driver(layer below) 0x0000 */
#define    ERR_OK                      SGF_OK
#define    ERR_RANGE                   (UINT16)0x4444
#define    ERR_DRIVER_BUSY             (UINT16)0x5555
#define    ERR_WRONG_REGION_NUMBER     (UINT16)0x6666
#define    ERR_NO_SUCH_SECTOR_FOUND    (UINT16)0x7777
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* ~~~~~~~~~~~~~ Return values used by driver ~~~~~~~~~~~~~~~~*/
#define    EMUL_EEPROM_STAT_OK         (UINT16)0x0000
#define    EMUL_EEPROM_STAT_BUSY       (UINT16)0x5555


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/*-----Public Functions---------------------------------------------------------*/
UINT16 u16emul_eeprom_init( tCallbackFunction  Callback, const tEmulEEPROM_config * EmulEEPROM_cfg );
UINT16 u16emul_eeprom_read( UINT32  u32AddressToRead, UINT16  u16Size, tu8ptr_far pu8DestPtr );
UINT16 u16emul_eeprom_write( UINT32 u32AddressToWrite, tu8ptr_far pu8SrcPtr, UINT16  u16DataSize );
UINT16 u16emul_eeprom_status( void  );

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/


#endif /*__EMUL_EEPROM_H */ 

