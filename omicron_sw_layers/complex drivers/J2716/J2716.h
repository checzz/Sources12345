/****************************************************************************************************/
/**
\file       J2716.h
\brief      J2716 initialization and low-level functions and prototypes
\author     Team 3
\version    1.0
\date       27/Nov/2012
*/
/****************************************************************************************************/
#ifndef __J2716_H        /*prevent duplicated includes*/
#define __J2716_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core Modules */
/** Variable types and common definitions */
#include    "J2716_Types.h"
#include    "J2716_Cfg.h"

/** Used Modules */
/** PLL definitions and prototypes*/
#include    "pll.h"
/* XGATE relevant data types and prototypes */
#include    "xgate_vectors.h"
/** XGATE Intrinsics */
#include    "intrinsics_xgate.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/
#pragma DATA_SEG SHARED_DATA
extern volatile J2716_StatusType * pstChannelsStat;
extern volatile J2716_StatusType * pstLocalStat;
extern volatile uint8 J2716X_u8Devices;
extern volatile uint8 J2716X_u8Channels;
extern volatile uint8 J2716X_boCallbackPending;
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG XGATE_DATA

#pragma DATA_SEG DEFAULT	

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/
extern void J2716_Init(const J2716_ConfigType * kstConfig);
extern void J2716_DeInit(void);
extern Std_ReturnType J2716_Transmit(J2716_ChannelType xChannel, uint8 * pu8DataBuffer);
extern void J2716_EnableNotification(J2716_ChannelType xChannel);
extern void J2716_DisableNotification(J2716_ChannelType xChannel);
#pragma CODE_SEG __NEAR_SEG NON_BANKED
extern void interrupt  vfnJ2716_Callback_Isr(void);
#pragma CODE_SEG DEFAULT
#endif /* __J2716_H */