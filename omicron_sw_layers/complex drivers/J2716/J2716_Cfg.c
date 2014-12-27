/****************************************************************************************************/
/**
\file       J2716_Cfg.c
\brief      J2716 static configuration structure
\author     Team 3
\version    1.0
\date       27/Nov/2012
*/
/****************************************************************************************************/
#include "J2716_Cfg.h"
#include "J2716_App.h"
/* Channel(s) configuration */
const J2716_ConfigChannelType  J2716_astChannelsCfg[]=
{
/*  CHANNEL         PORT          PIN           LENGHT  TICK(us)  PAUSE   NOTIFICATION  */
{J2716_Ch0, (uint8* const)&PTJ,  PTJ_PTJ7_MASK,     6,        3,  FALSE,  J2716_Cbk0},
//{J2716_Ch1, (uint8* const)&PTJ,  PTJ_PTJ6_MASK,     3,       30,  TRUE,   NULL/*J2716_Cbk1*/}
};

/* Device(s) configuration */
const J2716_ConfigType  J2716_astDevicesCfg[]=
{
{J2716_SENT,(sizeof(J2716_astChannelsCfg)/sizeof(J2716_ConfigChannelType)),&J2716_astChannelsCfg[0]}
};

/* Devices configurated */
const uint8 J2716_u8Devices = (uint8)(sizeof(J2716_astDevicesCfg)/sizeof(J2716_ConfigType));