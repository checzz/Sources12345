/****************************************************************************************************/
/**
\file       hal_flash.h
\brief      Flash routines functions and prototypes
\author     Christian Michel/Abraham Tezmol
\version    1.0.1
\date       08/12/2008
*/

/*****************************************************************************************************
* Module definition against multiple inclusion
*****************************************************************************************************/
#ifndef __FLASH_H        /*prevent duplicated includes*/ 
#define    __FLASH_H    

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Variable types and common definitions */
#include    "typedefs.h"
/** Bootloader Configuration Options */
#include    "pll.h"
/** MCU derivative information */
#include    __MCU_DERIVATIVE

/** Used modules */
/* Definition of registers for use within this module */
#include    "flash_registers.h"


/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/


/*****************************************************************************************************
* Declaration of module wide VARIABLES
*****************************************************************************************************/

/*------Global Variables used by DFlashProgram Function-------*/

extern   UINT32 gu32DFlashProgram_dest;
extern   UINT32 gu32DFlashProgram_size;
extern   UINT32 gu32DFlashProgram_source;


/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/* Macros used by u16Flash_IsFlashBusy function */
#define    FLASH_READY                  0
#define    FLASH_BUSY                   1
#define    DFLASH_TASK_FINISHED         0x6666

/* For CodeWarrior, the keyword is near or __near */
#define    SSD_SGF18_NEAR               __near

/* For CodeWarrior, the keyword is far or __far */
#define    SSD_SGF18_FAR                __far
#define    SSD_SGF18_FUNC_FAR           __far

/* Configuration MACROS to be used */
/* Base address of MCU register block */
#define    SSD_MCU_REGISTER_BASE        0x00000000

/* Bus clock. The unit is 10KHz */
#define    SSD_BUS_CLOCK                ( BUS_FREQ_KHZ / 10u )

/* Oscillator clock. The unit is 10KHz */
#define    SSD_OSCILLATOR_CLOCK         ( XTAL_FREQ_KHZ / 10u )

/*------------ Return Code Definition for HCS12X/S12P-SSD -------------------*/
#define    SGF_OK                       0x0000
#define    SGF_ERR_CLKSET               0x0001
#define    SGF_ERR_SIZE                 0x0002
#define    SGF_ERR_RANGE                0x0004
#define    SGF_ERR_ACCERR               0x0008
#define    SGF_ERR_PVIOL                0x0010
#define    SGF_ERR_MGSTAT0              0x0020
#define    SGF_ERR_MGSTAT1              0x0040
#define    SGF_ERR_EPVIOLIF             0x0080
#define    SGF_ERR_PROTMODE             0x0100
#define    SGF_ERR_PROTSIZE             0x0200
#define    SGF_ERR_DATAMISMATCH         0x0400
#define    SGF_ERR_INVALIDCLK           0x0800
#define    SGF_ERR_ADDR                 0x1000
#define    SGF_ERR_SFDIF                0x2000
#define    SGF_ERR_DFDIF                0x4000

/* Command Sequence Index Macros */
#define    COMMAND_INDEX0               0x00
#define    COMMAND_INDEX1               0x01
#define    COMMAND_INDEX2               0x02
#define    COMMAND_INDEX3               0x03
#define    COMMAND_INDEX4               0x04
#define    COMMAND_INDEX5               0x05

/* Address fetching mask */
#define    GLOBAL_ADDRESS_MASK          0x007F0000
#define    ADDRESS_OFFSET_MASK          0x0000FFFF

#ifdef __S12XEP100

    /* P Flash start address*/
#define    PFLASH_BLOCK_START_ADDR      0x700000

    /* P Flash end block address */
#define    PFLASH_BLOCK_END_ADDR        0x7FDFFF         /* 0x7FFFFF - 8K Bytes */ 

#endif


/*-------------- Read/Write/Set/Clear Operation Macros ------------------*/
/* CodeWarrior */
#define    REG_BIT_SET( address, mask )    ( * ( VUINT8 * SSD_SGF18_NEAR ) ( address ) |= ( mask ) )
#define    REG_BIT_CLEAR( address, mask )    ( * ( VUINT8 * SSD_SGF18_NEAR ) ( address ) &= ~ ( mask ) )
#define    REG_BIT_TEST( address, mask )    ( * ( VUINT8 * SSD_SGF18_NEAR ) ( address ) & ( mask ) )
#define    REG_WRITE( address, value )      ( * ( VUINT8 * SSD_SGF18_NEAR ) ( address ) = ( value ) )
#define    REG_READ( address )              ( ( UINT8 ) ( * ( VUINT8 * SSD_SGF18_NEAR ) ( address ) ) )
#define    REG_WRITE16( address, value )    ( * ( VUINT16 * SSD_SGF18_NEAR ) ( address ) = ( value ) )
#define    REG_READ16( address )            ( ( UINT16 ) ( * ( VUINT16 * SSD_SGF18_NEAR ) ( address ) ) )

#define    WRITE8( address, value )         ( * ( VUINT8 * SSD_SGF18_NEAR ) ( address ) = ( value ) )
#define    READ8( address )                 ( ( UINT8 ) ( * ( VUINT8 * SSD_SGF18_NEAR ) ( address ) ) )
#define    SET8( address, value )           ( * ( VUINT8 * SSD_SGF18_NEAR ) ( address ) |= ( value ) )
#define    CLEAR8( address, value )         ( * ( VUINT8 * SSD_SGF18_NEAR ) ( address ) &= ~ ( value ) )
#define    TEST8( address, value )          ( * ( VUINT8 * SSD_SGF18_NEAR ) ( address ) & ( value ) )

#define    WRITE16( address, value )        ( * ( VUINT16 * SSD_SGF18_NEAR ) ( address ) = ( value ) )
#define    READ16( address )                ( ( UINT16 ) ( * ( VUINT16 * SSD_SGF18_NEAR ) ( address ) ) )
#define    SET16( address, value )          ( * ( VUINT16 * SSD_SGF18_NEAR ) ( address ) |= ( value ) )
#define    CLEAR16( address, value )        ( * ( VUINT16 * SSD_SGF18_NEAR ) ( address ) &= ~ ( value ) )
#define    TEST16( address, value )         ( * ( VUINT16 * SSD_SGF18_NEAR ) ( address ) & ( value ) )

#define    WRITE32( address, value )        ( * ( VUINT32 * SSD_SGF18_NEAR ) ( address ) = ( value ) )
#define    READ32( address )                ( ( UINT32 ) ( * ( VUINT32 * SSD_SGF18_NEAR ) ( address ) ) )
#define    SET32( address, value )          ( * ( VUINT32 * SSD_SGF18_NEAR ) ( address ) |= ( value ) )
#define    CLEAR32( address, value )        ( * ( VUINT32 * SSD_SGF18_NEAR ) ( address ) &= ~ ( value ) )
#define    TEST32( address, value )         ( * ( VUINT32 * SSD_SGF18_NEAR ) ( address ) & ( value ) )

/*-------------------- Macro definition for HCS12X ----------------------*/
#define    HCS12X_WORD_SIZE                  0x0002

/* Phrase size */
#define    FLASH_PHRASE_SIZE                 0x0008 /* 8 bytes */ 

/*------------- Flash hardware algorithm operation commands -------------*/
#define    FLASH_ERASE_VERIFY_BLOCK          0x02
#define    PFLASH_PROGRAM                    0x06
#define    PFLASH_ERASE_SECTOR               0x0A
#define    FLASH_SET_USER_MARGIN             0x0D
#define    DFLASH_FULL_PARTITION             0x0F
#define    DFLASH_ERASE_VERIFY               0x10
#define    DFLASH_PROGRAM                    0x11
#define    DFLASH_ERASE_SECTOR               0x12
#define    DFLASH_ENABLE_EEPROM_EMUL         0x13
#define    DFLASH_DISABLE_EEPROM_EMUL        0x14
#define    DFLASH_EEPROM_EMUL_QUERY          0x15
#define    DFLASH_PARTITION                  0x20


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/*-------------FUNCTIONS RELATED TO P-FLASH-------------------------*/
/* Blocking Function. Programs the P-Flash address space */
UINT16  u16Flash_PFlashProgram( UINT32  u32Dest, UINT32  u32Size, UINT32  u32Source );
/* Blocking Function. Erase one flash sector */
UINT16  u16Flash_PFlashEraseSector( UINT32  u32Destination );
/* Blocking Function, erases all sectors in P-Flash, sector by sector */
UINT16  u16Flash_Erase_PFlash_blocks( void  );

/*-------------FUNCTIONS RELATED TO GENERAL FLASH BLOCK-------------*/
/* Tests if There is a command in progress in the Flash block */
UINT16  u16Flash_IsFlashBusy( void  );
/* Initializes flash clock divider */
UINT16  u16Flash_Init( tCallbackFunction  Callback );

/*-------------FUNCTIONS RELATED TO D-FLASH-------------------------*/
/* Erases and then creates Data Flash partitions in order to support emulated EEPROM in hardware */
UINT16  u16Flash_FullDFlash_Partition( UINT8  u8DataFlashPartitions, UINT8  u8EEPROMPartitions );
/* Create Data Flash partitions in order to support emulated EEPROM in hardware */
UINT16  u16Flash_DFlash_Partition( UINT8  u8DataFlashPartitions, UINT8  u8EEPROMPartitions );
/* Enable Emulated EEPROM using data flash */
UINT16  u16Flash_EEEPROM_Enable( void  );
/* Disable Emulated EEPROM using data flash */
UINT16  u16Flash_EEEPROM_Disable( void  );

/* FlashCommandSequence is the function that launches the flash command */
/* This has to be run from RAM or different Flash block than the one being programmed. */
#pragma CODE_SEG RAM_ROUTINES
UINT16 u16Flash_CommandSequence( UINT8  u8Index );
#pragma CODE_SEG DEFAULT


#endif /* __FLASH_H */ 

