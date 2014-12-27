/****************************************************************************************************/
/**
\file       nvm_data.h
\brief      Non-volatile data definitions.
\author     Abraham Tezmol
\version    1.0.1
\date       08/12/2008
*/

#ifndef __NVM_DATA_H        /*prevent duplicated includes*/ 
#define    __NVM_DATA_H    

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Configuration Options */
#include    "configuration.h"
/** MCU derivative information */
#include    __MCU_DERIVATIVE
/** Variable types and common definitions */
#include    "typedefs.h"
/** Cam Crank routines prototypes and definitions */
#include    "cam_crank.h"

/** Used modules */
/* None */

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/* Boot Loader <--> Application Subsystem Interfacing Data type */
typedef  struct  tInterfaceData
{
    /*  Reserved for the use of the Emulated EEPROM driver for S12XEP  
        0x0A0A 		--> 	Default value define by Emulated EEPROM.
						    Not to be manually changed by user.
    */         
             UINT16 gu16DataFlashReservedValue;
    /* 
        Indicates to bootloader if application block needs to be reflashed. Encoding:
        0xAA        -->     application block needs to be reflashed.
        any other   -->     no formal request to reflash application block.
    */
             UINT8  gu8AppBlockReflashRequest;
    /* 
        Indicates validity of application block. Encoding:
        0xAA        -->     valid application block.
        any other   -->     invalid application block.
    */
             UINT8  gu8AppBlockValidityFlag;
    /*
        4 byte hex encoding of code version. i.e.:
        v1.0.0.3 = {0x01,0x00,0x00,0x03}; 
    */
             UINT32 gu32BootBlockVersion;
    /*
        4 byte hex encoding of code version. i.e.:
        v1.0.0.3 = {0x01,0x00,0x00,0x03};
    */
             UINT32 gu32AppBlockVersion;
    /* 
        Application block __Startup routine. Expected value:
        16-bit Address of __Startup routine.
    */
             UINT16 gu16AppBlockStartup;
    /* 
        Records Programming Tool unique Identifier. Encoding:
        16-bit unique identifier.
    */
             UINT16 gu16UniqueTesterID;
    /*
        application block reflashing attempts stored in a 16 bit unsigned variable.
        This variable shall only be updated under bootloader control
    */
             UINT16 gu16AppBlockReflashAttempts;
};


/* Application Subsystem NVM Data */
typedef  struct  tNVM_Data
{   
    UINT16 gu16DataFlashReservedValue;
    
    tCamCrankChDescr cam_crank_channels[5];
    
    UINT16  u16RPMValue;
    UINT16  u16SystemRPM;
    UINT16  u16Angle_OneDegreeTicks;
    UINT16  u16CamCrankWidth_ticks;
    UINT16  u16MissingTeethIndex;
    UINT16  u16ExtraTooth_degrees;
    UINT16  u16GlobalArrayIndex;
    UINT16  u16StopAtCrankAngle;
    
    UINT8   u8CrankActiveLevel;
    UINT8   u8CrankIdleLevel;
    UINT8   u8CrankTeeth;
    UINT8   u8Direction;
    UINT8   u8MissingTeeth;
    UINT8   u8CamSignalTransitions;
    UINT8   u8RPM_new_value;
    UINT8   u8PIT_ClockNew;
    UINT8   u8PIT_Clock;
    UINT8   u8TIM_Clock;
    UINT8   u8TIM_ClockNew;   
    UINT8   u8EnableStopAtToothNumber;
    
    UINT8   u8CrankConfig[ENGINE_ANGLE_DEGREES];
} ;

/* Interfacing Data type */
typedef  struct  tNVM_Data1
{
    UINT8   u8CamConfig1[ENGINE_ANGLE_DEGREES];
} ;

/* Interfacing Data type */
typedef  struct  tNVM_Data2
{
    UINT8   u8CamConfig2[ENGINE_ANGLE_DEGREES];
} ;

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/
#pragma DATA_SEG NVM_INTERFACE_DATA
extern  struct  tInterfaceData  sNVM_InterfaceData;
extern  UINT8   au8NVM_Bootloader_non_used[64-sizeof(sNVM_InterfaceData)];
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG SHADOW_EEPROM
extern  struct  tInterfaceData sNVM_InterfaceData_ROM;
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG NVM_DATA                                       /* 1K - 64 bytes (Interface data) Region */
extern  struct  tNVM_Data  sNVM_Data;
extern  UINT8   au8NVM_non_used[ 1024-64-sizeof(sNVM_Data) ]; 	/* Size of array needs to be updated upon addition of new data */
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG NVM_DATA1                                      /* 1K Regions */
extern  struct  tNVM_Data1  sNVM_Data1;
extern  UINT8   au8NVM_non_used1[ 1024-sizeof(sNVM_Data1) ]; 	/* Size of array needs to be updated upon addition of new data */
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG NVM_DATA2                                      /* 1K Regions */
extern  struct  tNVM_Data2  sNVM_Data2;
extern  UINT8   au8NVM_non_used2[ 1024-sizeof(sNVM_Data2) ]; 	/* Size of array needs to be updated upon addition of new data */
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG DEFAULT_CALS_0
extern  struct  tNVM_Data  sNVM_Data_ROM;
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG DEFAULT_CALS_1
extern  struct  tNVM_Data1 sNVM_Data_ROM1;
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG DEFAULT_CALS_2
extern  struct  tNVM_Data2 sNVM_Data_ROM2;
#pragma DATA_SEG DEFAULT

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/
/* Valid Application Block Flash Request */
#define    VALID_APP_BLOCK_REFLASH_REQUEST      0xAAu
/* Invalid Application Block Flash Request */
#define    INVALID_APP_BLOCK_REFLASH_REQUEST    0x77u
/* Valid Applicatoin Block indicator */
#define    VALID_APP_BLOCK_VALIDITY_FLAG        0xAAu
/* Invalid Applicatoin Block indicator */
#define    INVALID_APP_BLOCK_VALIDITY_FLAG      0xDEu

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

#endif /*HIL_NVM_DATA_H */ 
