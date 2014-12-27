/****************************************************************************************************/
/**
\file       J2716.h
\brief      J2716 Data types
\author     Team 3
\version    1.0
\date       27/Nov/2012
*/
/****************************************************************************************************/
#ifndef __J2716_TYPES_H        /*prevent duplicated includes*/
#define __J2716_TYPES_H

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
typedef uint8 J2716_ChannelType;

/* J2716 channels's state */
typedef enum
{
  J2716_INIT=0x7FFF,
  J2716_IDLE=0x7FFE,
  J2716_TX=0x7FFD,
  J2716_CBK=0x7FFC
}J2716_StateType;

/* Supported channles */
typedef enum
{
  J2716_Ch0=0,
  J2716_Ch1,
  J2716_MAX_CHANNELS
}J2716_Channels;

/* Supported devices */
typedef enum
{
  J2716_SENT=0,
  J2716_MAX_DEVICES
}J2716_Channels;

typedef enum
{
  J2716_Start=0,
  J2716_Sync,
  J2716_Status,
  J2716_Data,
  J2716_Crc,
  J2716_Pause,
  J2716_TxBits,
  J2716_Error
}J2716_Sequence;

typedef struct
{
  J2716_Channels  enId;
  J2716_StateType enMsgStatus;
  J2716_Sequence  enMsgSeq;
  uint8*          pu8MsgPort;
  uint16          u8MsgPin;
  uint16          u8MsgTick;
  uint16          u8MsgLen;
  uint16          u8MsgCrc;
  uint16          u8MsgCbkEn;
  uint16          u8MsgNibble;/* Current transmited nibble */
  uint16          u8MsgTickCtr;
  uint16          u8MsgDataIndex;/* Current transmited nibble */
  uint16          u8MsgPauseEn;
  uint16           au8MsgData[6];
}J2716_StatusType;

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

#pragma DATA_SEG SHARED_DATA

#pragma DATA_SEG DEFAULT

#pragma DATA_SEG XGATE_DATA

#pragma DATA_SEG DEFAULT	

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/
#define J2716_OFFSET                      ((uint16)0xC000)

#define J2716_MIN_TICK_LEN                ((uint8)3)
#define J2716_MAX_TICK_LEN                ((uint8)90)
#define J2716_TICK_RESOLUTION             ((uint8)3)


/* Values to define the waveform */
#define J2716_LOW_PULSE_TICKS             ((uint8)5)
#define J2716_MIN_PERIOD_TICKS            ((uint8)12)
#define J2716_SYNC_PERIOD_TICKS           ((uint8)56)
#define J2716_PAUSE_TICKS                 ((uint8)77)

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

#endif /* __J2716_TYPES_H */