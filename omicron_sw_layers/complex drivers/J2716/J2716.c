/****************************************************************************************************/
/**
\file       J2716.c
\brief      J2716(SENT) initialization and low-level functions and prototypes
\author     Team 3
\version    1.0
\date       27/11/2012
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
/* Periodic Interrupt Timer routines prototypes */
#include "J2716.h"

#include "pit.h"
#include "xgate_config.h"
#include "memory_allocation.h"
/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/





/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/	
static uint8 J2716__u8CalcCrc( uint8* pu8Data , uint8 u8Len );
/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
static J2716_ConfigType *pstConfig;
/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
static const uint8 ku8CrcSeed = 5;
static const uint8 kau8CrcLookupTbl[ 16 ] = { 0 , 13 , 7 , 10 , 14 , 3 , 9 , 4 , 1 , 12 , 6 , 11 , 15 , 2 , 8 , 5 };
/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    J2716 - Initialization
* \author   Team 3
* \param    J2716_ConfigType * kstConfig - Static configuration of the driver
* \return   void
*/
void J2716_Init(const J2716_ConfigType * kstConfig)
{
  uint8 u8Devices=0;
  uint8 u8Channel=0;
  uint8 u8Temp=0;

  do{XGATE_SET_SEM(J2716_SEMAPHORE);}while(!XGATE_TST_SEM(J2716_SEMAPHORE));
  
  /* Get total number of channels */
  for( u8Devices=0 ; (u8Devices < J2716_u8Devices) ; u8Devices++)
  {
    u8Temp+=kstConfig[u8Devices].u8Channels;
  }
  /* Copy information into SHARED MEM */
  pstConfig = (J2716_ConfigType *)kstConfig;
  J2716X_u8Devices = J2716_u8Devices; /* Total of devices configured */
  J2716X_u8Channels = u8Temp;         /* Total of channels regardless number of devices */
  pstChannelsStat = (J2716_StatusType *)MemAlloc_NearReserve(sizeof(J2716_StatusType)*J2716X_u8Channels);  
  pstLocalStat   = (void*)((uint16)pstChannelsStat|J2716_OFFSET);
  for( u8Devices=0 ; (u8Devices < J2716_u8Devices) ; u8Devices++)
  {
    for( u8Channel=0 ; (u8Channel < J2716X_u8Channels) ; u8Channel++)
    {
      /* Resolution configured */
      u8Temp = pstConfig[u8Devices].pstChannlesCfg[u8Channel].u8TickPeriod;
      /* ToDo: initialize here the channels */
      pstChannelsStat[u8Channel].enId            = pstConfig[u8Devices].pstChannlesCfg[u8Channel].enId;
      pstChannelsStat[u8Channel].enMsgStatus     = J2716_IDLE;
      pstChannelsStat[u8Channel].enMsgSeq        = J2716_Start;
      pstChannelsStat[u8Channel].pu8MsgPort      = pstConfig[u8Devices].pstChannlesCfg[u8Channel].pu8OutputPort;
      pstChannelsStat[u8Channel].au8MsgData[0]   = J2716_MIN_PERIOD_TICKS/*Value 0*/;
      pstChannelsStat[u8Channel].au8MsgData[1]   = J2716_MIN_PERIOD_TICKS/*Value 0*/;
      pstChannelsStat[u8Channel].au8MsgData[2]   = J2716_MIN_PERIOD_TICKS/*Value 0*/;
      pstChannelsStat[u8Channel].au8MsgData[3]   = J2716_MIN_PERIOD_TICKS/*Value 0*/;
      pstChannelsStat[u8Channel].au8MsgData[4]   = J2716_MIN_PERIOD_TICKS/*Value 0*/;
      pstChannelsStat[u8Channel].au8MsgData[5]   = J2716_MIN_PERIOD_TICKS/*Value 0*/;
      pstChannelsStat[u8Channel].u8MsgPin        = pstConfig[u8Devices].pstChannlesCfg[u8Channel].u8PortPin;
      if(u8Temp < J2716_MIN_TICK_LEN)
      {
        u8Temp = J2716_MIN_TICK_LEN;
      }
      else
      {
        if(u8Temp > J2716_MAX_TICK_LEN)
        {
          u8Temp = J2716_MAX_TICK_LEN;
        }
        else
        {
          /* do nothing
              Resolution within range */
        }
      }
      pstChannelsStat[u8Channel].u8MsgTick       = u8Temp;
      pstChannelsStat[u8Channel].u8MsgLen        = pstConfig[u8Devices].pstChannlesCfg[u8Channel].u8MsgLen;
      pstChannelsStat[u8Channel].u8MsgCrc        = J2716_MIN_PERIOD_TICKS/*Value 0*/;
      if(pstConfig[u8Devices].pstChannlesCfg[u8Channel].pfnCallback!=NULL)
      pstChannelsStat[u8Channel].u8MsgCbkEn      = TRUE;
      else
      pstChannelsStat[u8Channel].u8MsgCbkEn      = FALSE;
      pstChannelsStat[u8Channel].u8MsgNibble     = 0;
      pstChannelsStat[u8Channel].u8MsgTickCtr    = 1;
      pstChannelsStat[u8Channel].u8MsgDataIndex  = 0;
      pstChannelsStat[u8Channel].u8MsgPauseEn    = pstConfig[u8Devices].pstChannlesCfg[u8Channel].u8PauseEnable;
    }
  }
  
  XGATE_REL_SEM(J2716_SEMAPHORE);
  
  /* Access to configuration data registers for interrupts */ 
  INT_CFADDR          = 0x70;         /* with vectors from 0xFF70 to 0xFF7E */
  INT_CFDATA0_PRIOLVL = 6;            /* XGATE software trigger 1, priority 6 */
  INT_CFDATA0_RQST    = 1;            /* routed to XGATE */
  /* "SOFTWARE_TRIGGER_2"  == "Channel 38 - XGATE Software Trigger 1" in xgate_vectors.cxgate */
  XGATE_SW_TRIGGER( SOFTWARE_TRIGGER_2, SOFTWARE_TRIGGER_ENABLE);
  /* PIT Ch2 will be started */ 
  vfnPIT2_Start();
  
  #if J2716_DBG == TRUE
  PTJ_PTJ0  =0;
  DDRJ_DDRJ0=1;
  #endif
}

/****************************************************************************************************/
/**
* \brief    J2716 - De-Initialization
* \author   Team 3
* \param    void
* \return   void
*/
void J2716_DeInit(void)
{
}

/****************************************************************************************************/
/**
* \brief    J2716 - Transmission of data
* \author   Team 3
* \param    uint8 * pu8DataBuffer - Address of the buffer where the data will be taken from
* \return   Std_ReturnType
*/
Std_ReturnType J2716_Transmit(J2716_ChannelType xChannel, uint8 * pu8DataBuffer)
{
  uint8 i=0;
  Std_ReturnType xRetVal = E_OK;
  
  do{XGATE_SET_SEM(J2716_SEMAPHORE);}while(!XGATE_TST_SEM(J2716_SEMAPHORE));
  /* If this interface is called in APPLICATION mode or during a CALLBACK */
  if( (J2716_IDLE == pstChannelsStat[xChannel].enMsgStatus) ||
      (J2716_CBK == pstChannelsStat[xChannel].enMsgStatus) )
  {
    /* Append CRC of current data */
    pstChannelsStat[xChannel].u8MsgCrc = J2716__u8CalcCrc(pu8DataBuffer,(uint8)pstChannelsStat[xChannel].u8MsgLen);
    pstChannelsStat[xChannel].u8MsgCrc+=J2716_MIN_PERIOD_TICKS;
    for(i=0 ; i < pstChannelsStat[xChannel].u8MsgLen ; i++ )
    {
      pstChannelsStat[xChannel].au8MsgData[i] = pu8DataBuffer[i]+J2716_MIN_PERIOD_TICKS;
    }
    
    pstChannelsStat[xChannel].enMsgStatus = J2716_TX;
  }
  else
  {
    xRetVal = E_NOT_OK;
  }
  XGATE_REL_SEM(J2716_SEMAPHORE);
return xRetVal;
}

/****************************************************************************************************/
/**
* \brief    J2716 - De-Initialization
* \author   Team 3
* \param    J2716_ChannelType xChannel  - Channel where the notification will be enabled
* \return   void
*/
void J2716_EnableNotification(J2716_ChannelType xChannel)
{
  pstChannelsStat[xChannel].u8MsgCbkEn      = TRUE;
}

/****************************************************************************************************/
/**
* \brief    J2716 - De-Initialization
* \author   Team 3
* \param    J2716_ChannelType xChannel  - Channel where the notification will be disabled
* \return   void
*/
void J2716_DisableNotification(J2716_ChannelType xChannel)
{
  pstChannelsStat[xChannel].u8MsgCbkEn      = 0xFF;
}

/****************************************************************************************************/
/**
* \brief    J2716 - Compute CRC
* \author   Team 3
* \param    uint8* pu8Data  - Data buffer to be sent out
*           uint8 u8Len     - Length of the message
* \return   uint8           - CRC value
*/
static uint8 J2716__u8CalcCrc( uint8* pu8Data , uint8 u8Len )
{
	
	uint8 i=0;
	uint8 u8Crc = ku8CrcSeed;/*Seed*/
	uint8 u8Temp;
	
	for( i = 0; i < u8Len; i++ )
	{
		u8Temp = kau8CrcLookupTbl[ u8Crc ];
		u8Crc = u8Temp ^ *pu8Data;
		pu8Data++;
	}
	u8Crc = kau8CrcLookupTbl[ u8Crc ];
	return u8Crc;
}

/****************************************************************************************************/
/**
* \brief    J2716 Init ISR, if reached, XGATE has initialized PIT ("XGATE Software Trigger 2")
* \author   Team 3
* \param    void
* \return   void
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt  vfnJ2716_Callback_Isr( void  )
{
  uint8 u8Devices=0;
  uint8 u8Channel=0;
  uint8 u8Temp=0;

  for( u8Devices=0 ; (u8Devices < J2716_u8Devices) ; u8Devices++)
  {
    for( u8Channel=0 ; (u8Channel < J2716X_u8Channels) ; u8Channel++)
    {
      if( (TRUE == pstChannelsStat[u8Channel].u8MsgCbkEn) &&
           (J2716_CBK == pstChannelsStat[u8Channel].enMsgStatus) )
      {
        pstConfig[u8Devices].pstChannlesCfg[u8Channel].pfnCallback();
        pstChannelsStat[u8Channel].enMsgStatus = J2716_IDLE;
      }
    }
  }
  J2716X_boCallbackPending = FALSE;
  /* Clear Software Interrupt request flag */
  XGATE_SW_TRIGGER( SOFTWARE_TRIGGER_3, SOFTWARE_TRIGGER_DISABLE);  
}
#pragma CODE_SEG DEFAULT