/****************************************************************************************************/
/**
\file       cnf_serial.c
\brief      Configuration of Serial Communication Interface services
\author     Abraham Tezmol
\version    1.0
\date       5/10/2013
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** SCI configuration definitions */
#include    "cnf_serial.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Dynamic memory allocation configuration for NEAR memory */
const tSCIchannel_config SCI_channel_cfg[] =
{
    {   
        (UINT32)57600,		        /* SCI_baudrate */
        (tCallbackFunction)NULL,	/* SCI_TX_callback */
        (tCallbackFunction)NULL,	/* SCI_RX_callback */
        SCI_CH0,         	        /* SCI_Channel */	
        (UINT8)ENABLE,              /* SCI_TX_enable */ 
        (UINT8)ENABLE,              /* SCI_RX_enable */
        (UINT8)ENABLE,              /* SCI_TIE_enable  */
        (UINT8)ENABLE,              /* SCI_RIE_enable */
        (UINT8)SCI_TX_MAX_SIZE,     /* SCI_TX_MAX_BUFFER_SIZE */
        (UINT8)SCI_RX_MAX_SIZE      /* SCI_RX_MAX_BUFFER_SIZE */
    },
    {   
        (UINT32)19200,		        /* SCI_baudrate */
        (tCallbackFunction)NULL,	/* SCI_TX_callback */
        (tCallbackFunction)NULL,	/* SCI_RX_callback */
        SCI_CH1,         	        /* SCI_Channel */	
        (UINT8)ENABLE,              /* SCI_TX_enable */ 
        (UINT8)ENABLE,              /* SCI_RX_enable */
        (UINT8)ENABLE,              /* SCI_TIE_enable  */
        (UINT8)ENABLE,              /* SCI_RIE_enable */
        (UINT8)SCI_TX_MAX_SIZE,     /* SCI_TX_MAX_BUFFER_SIZE */
        (UINT8)SCI_RX_MAX_SIZE      /* SCI_RX_MAX_BUFFER_SIZE */
    },
};


const tSCIdriver_config  SCI_config[] =
{
    {
        sizeof(SCI_channel_cfg)/sizeof(SCI_channel_cfg[0]),         /* number of configured channels */
        &SCI_channel_cfg[0]                                         /* SCI channels configuration structure */
    }
};

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/


/*****************************************************************************************************
* Code of public FUNCTIONS
*****************************************************************************************************/


/***************************************************************************************************/
