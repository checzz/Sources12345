/****************************************************************************************************/
/**
\file       J2716.h
\brief      J2716 initialization and low-level functions and prototypes
\author     Team 3
\version    1.0
\date       27/Nov/2012
*/
/****************************************************************************************************/
#ifndef __J2716_CFG_H        /*prevent duplicated includes*/
#define __J2716_CFG_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core Modules */
#include    "J2716_Types.h"
/** Configuration Options */
#include    "configuration.h"
/** S12X derivative information */
#include    __MCU_DERIVATIVE
/** Variable types and common definitions */
#include    "typedefs.h"
/** Access to GPIO definitions */
#include    "gpio.h"

#define J2716_DBG FALSE

typedef struct 
{
  J2716_Channels    enId;
  uint8*            pu8OutputPort;
  uint8             u8PortPin;
  uint8             u8MsgLen;
  uint8             u8TickPeriod;
  uint8             u8PauseEnable;
  tCallbackFunction pfnCallback;
}J2716_ConfigChannelType;

typedef struct 
{
  uint8                           u8DeviceId;
  uint8                           u8Channels; 
  const J2716_ConfigChannelType*  pstChannlesCfg;
}J2716_ConfigType;

/*Expose the static configuration*/
extern const J2716_ConfigType  J2716_astDevicesCfg[];
extern const uint8 J2716_u8Devices;

#endif /* __J2716_CFG_H */