/****************************************************************************************************/
/**
\file       cnf_serial.h
\brief      Configuration of Serial Communication Interface services
\author     Abraham Tezmol
\version    1.0
\date       5/10/2013
*/
/****************************************************************************************************/

#ifndef __CNF_SERIAL_H        /*prevent duplicated includes*/ 
#define    __CNF_SERIAL_H    

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


typedef enum 
{
    SCI_CH0,
    SCI_CH1,
    SCI_NULL
}tSCI_Channel;

typedef struct 
{
 	UINT32			    SCI_baudrate;	/* Baudrate */
	tCallbackFunction	SCI_TX_callback;
	tCallbackFunction	SCI_RX_callback;
    enum tSCI_Channel	SCI_Channel;	
    UINT8               SCI_TX_enable; 
    UINT8               SCI_RX_enable;
	UINT8			    SCI_TIE_enable; /* Transmit Interrupt Enable */
	UINT8			    SCI_RIE_enable; /* Receive Interrupt Enable */
	UINT8			    SCI_tx_buffer_size;
	UINT8			    SCI_rx_buffer_size;
}tSCIchannel_config;


typedef struct 
{
    UINT8                           u8Number_of_SCI_channels;
    const tSCIchannel_config *   	SCI_channels_cfg;
}tSCIdriver_config;

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/


    #define SCI_RX_MAX_SIZE    92u
    #define SCI_TX_MAX_SIZE    16u

    
/*****************************************************************************************************
* Declaration of public VARIABLEs / Constants 
*****************************************************************************************************/

extern const tSCIdriver_config  SCI_config[];

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/


#endif /* __CNF_SERIAL_H */ 