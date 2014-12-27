/****************************************************************************************************/
/**
\file       nvm_data.c
\brief      Non-volatile data definitions.
\author     Abraham Tezmol
\version    1.0.1
\date       08/12/2012
*/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
/** Interface data definitions */
#include    "nvm_data.h"

/** Used modules */

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/* Shadow EEPROM definition, place structure in SHADOW_EEPROM segment */
#pragma DATA_SEG NVM_INTERFACE_DATA
    struct tInterfaceData sNVM_InterfaceData;  
    UINT8 au8NVM_Bootloader_non_used[64-sizeof(sNVM_InterfaceData)];
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG SHADOW_EEPROM
    struct tInterfaceData sNVM_InterfaceData_ROM =
    {
    {0x0A0A}, /* UINT16 gu16DataFlashReservedValue */
    {0x55}, /* UINT8 gu8AppBlockReflashRequest */
    {0x55}, /* UINT8 gu8AppBlockValidityFlag */
    {0x01000001}, /* UINT32 gu32BootBlockVersion */
    {0x00000000}, /* UINT32 gu32AppBlockVersion */
    {0x4000}, /* UINT16 gu16AppBlockStartup */
    {0x1234}, /* UINT16 gu16UniqueTesterID */
    {0x0000} /* UINT16 gu16AppBlockReflashAttempts */
    };
#pragma DATA_SEG DEFAULT



#pragma DATA_SEG NVM_DATA                               /* 1K - 64 byte Region */
struct  tNVM_Data  sNVM_Data;
UINT8   au8NVM_non_used[ 1024-64-sizeof(sNVM_Data)];	/* Size of array needs to be updated upon addition of new data */
#pragma DATA_SEG DEFAULT


/* Shadow EEPROM definition, place structure in DEFAULT_CALS_0 segment */
#pragma DATA_SEG DEFAULT_CALS_0
struct tNVM_Data sNVM_Data_ROM =
    {
        {(UINT16)0x0A0A},                         /*  UINT16 gu16DataFlashReservedValue */
        { { BIDIRECTIONAL,  FORWARD }, /* 1 */    /* tCamCrankChDescr cam_crank_channels[5]*/
          { NONE,           NONE    }, /* 2 */ 
          { NONE,           NONE    }, /* 3 */
          { NONE,           NONE    }, /* 4 */
          { NONE,           NONE    }, /* 5 */
        },
        {(UINT16)DEFAULT_RPM_VALUE},              /* UINT16  u16RPMValue                */
        {(UINT16)DEFAULT_RPM_VALUE},              /* UINT16  u16SystemRPM               */ 
        {(UINT16)DEFAULT_ONEDEGREE_TICKS},        /* UINT16  u16Angle_OneDegreeTicks    */
        {(UINT16)CRANK_WIDTH_FW_IN_PIT_COUNTS},   /* UINT16  u16CamCrankWidth_ticks     */
        {(UINT16)0},                              /* UINT16  u16MissingTeethIndex       */
        {(UINT16)DEFAULT_ANGLE_EXTRATOOTH},       /* UINT16  u16ExtraTooth_degrees      */
        {(UINT16)0},                              /* UINT16  u16GlobalArrayIndex        */
        {(UINT16)0},                              /* UINT16  u16StopAtCrankAngle        */
        {(UINT8)CRANK_SIGNAL_ACTIVE_LEVEL},       /* UINT8   u8CrankActiveLevel         */
        {(UINT8)CRANK_SIGNAL_IDLE_LEVEL},         /* UINT8   u8CrankIdleLevel           */
        {(UINT8)GM_CRANK_TEETH},                  /* UINT8   u8CrankTeeth               */
        {(UINT8)FORWARD},                         /* UINT8   u8Direction                */
        {(UINT8)GM_MISSING_TEETH},                /* UINT8   u8MissingTeeth             */
        {(UINT8)GM_CAM_TRANSITIONS},              /* UINT8   u8CamSignalTransitions     */
        {(UINT8)0},                               /* UINT8   u8RPM_new_value            */
        {(UINT8)PIT_uTIMER_HIGH_RANGE},           /* UINT8   u8PIT_ClockNew             */
        {(UINT8)PIT_uTIMER_HIGH_RANGE},           /* UINT8   u8PIT_Clock                */
        {(UINT8)TIMER_HIGH_RANGE},                /* UINT8   u8TIM_Clock                */
        {(UINT8)TIMER_HIGH_RANGE},                /* UINT8   u8TIM_ClockNew             */
        {(UINT8)0},                               /* UINT8   u8EnableStopAtToothNumber  */    
        {
            #if 0
            0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 0   .. 29  degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 30  .. 59  degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 60  .. 89  degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 90  .. 119 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 120 .. 149 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 150 .. 179 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 180 .. 209 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 210 .. 239 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 240 .. 269 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 270 .. 299 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 300 .. 329 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,  /* 330 .. 359 degrees */
            0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 360 .. 389 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 390 .. 419 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 420 .. 449 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 450 .. 479 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 480 .. 509 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 510 .. 539 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 540 .. 569 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 570 .. 599 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 600 .. 629 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 630 .. 659 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,  /* 660 .. 689 degrees */
            1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0   /* 690 .. 719 degrees */
            #endif
            1
        },  
    };
#pragma DATA_SEG DEFAULT

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
