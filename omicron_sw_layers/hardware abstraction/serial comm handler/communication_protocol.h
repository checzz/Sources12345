/****************************************************************************************************/
/**
\file       communication_protocol.h
\brief      
\author     Manuel Cortes / Abraham Tezmol
\version    1.0
\date       08/Dec/2011
*/
/****************************************************************************************************/

#ifndef __COMMUNICATION_PROTOCOL_H        /*prevent duplicated includes*/
#define __COMMUNICATION_PROTOCOL_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Configuration Options */
#include    "configuration.h"
/** MCU derivative information */
#include    __MCU_DERIVATIVE
/** Variable types and common definitions */
#include    "typedefs.h"
/***/
#include    "xgate_config.h"
/**/
#include    "serial.h"
/**/
#include    "cam_crank.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs - NOT for use in other modules
*****************************************************************************************************/

extern UINT8 u8TimeoutFlag;

/*****************************************************************************************************
* Declaration of module wide TYPEs - NOT for use in other modules
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of global wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

#define SERIAL_COMM_CHANNEL  SCI_CH0

#define HEADER_CHECKED      0
#define NO_HEADER_CHECKED   1

/* Definition of states of the Communication Tasks state machine */
#define    COM_STATE_WAIT_FOR_RX           0u
#define    COM_STATE_RECEIVING             1u
#define    COM_STATE_VALID_HEADER          2u
#define    COM_STATE_VALID_SID             3u
#define    COM_STATE_COMM_END              4u

#define NUM_BYTES_CHECKSUM  1
#define COMMAND_SIZE        4
#define VALID_HEADER        81
#define kCOM_RX_MaxSize     128
#define kCOM_TX_MaxSize     32

#define ACKNOWLEDGED      0
#define NOT_ACKNOWLEDGED  1

/** Services Definition */
#define     kCOM_No_Service                 0
#define     kCOM_Set_Crank_Prof             96
#define     kCOM_Set_Cram_Prof              99
#define     kCOM_Set_RPM                    102
#define     kCOM_Get_RPM                    103
#define     kCOM_Set_Crank_Type_Direction   105
#define     kCOM_Set_Signal_Period          108
#define     kCOM_Get_Scheduling_Period      118
#define     kCOM_Ack                        120
#define     kCOM_Enable_Stop                128


/* Communication Protocol specific communication definitions */
#define    dLOOP_TIME                      0x01u                /* Diagnostics loop time = 1ms */

/* Time information - miliseconds */
#define    COM_RX_TIMEOUT_MAX              2000u / dLOOP_TIME
#define    COM_RX_INTER_MSG_MAX            2000u / dLOOP_TIME

/*****************************************************************************************************
* Declaration of project wide FUNCTIONS
*****************************************************************************************************/

/** Initialization of low-level SCI resources needed for communications */

void vfnCommProtocol_Init(void);
void vfnCheckCommands(void);
void vfnCOM_SendRPM(void);
void vfnCOM_RxByte(void);
void vfnCOM_TxByte(void);

#endif /* __COMMUNICATION_PROTOCOL_H */