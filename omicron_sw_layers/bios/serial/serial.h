/****************************************************************************************************/
/**
\file       serial.h
\brief      Serial Communication Interface functions
\author     Abraham Tezmol
\version    1.0
\date       26/Jun/2009
*/
/****************************************************************************************************/

#ifndef __SERIAL_H        /*prevent duplicated includes*/
#define __SERIAL_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Omicron Configuration Options */
  #include    "configuration.h"
/** MCU derivative information */
  #include    __MCU_DERIVATIVE
/** Variable types and common definitions */
  #include    "typedefs.h"
/** SCI configuration definitions */
  #include    "cnf_serial.h"   

/** Used modules */
/** PLL prototypes and definitions */
  #include    "pll.h"
/** Dynamic Memory allocation services */
  #include    "memory_allocation.h"
     

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

typedef struct 
{
	UINT8  *		    u8SCI_RxData;
	UINT8  *		    u8SCI_TxData;
	UINT8  * 		    pu8SCI_Receive_Data_ptr;
	UINT8  * 		    pu8SCI_Read_Receive_Data_ptr;
	UINT8  *		    pu8SCI_Read_Transmit_Data_ptr;
	UINT8  			    u8SCI_RxLength;
	UINT8 			    u8SCI_TxLength;
    UINT8  			    u8SCI_Comm_Status;	
    enum tSCI_Channel	SCI_Channel;
}tSCIchannel_status;

typedef struct 
{      
    tSCIchannel_status *    SCIchannel_status;
    UINT8                   u8Number_of_SCI_channels;
}tSCIdriver_status;


/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/


/*-- Communication status defines --------------------------------------------*/

#define SCI_COMM_ON             0u
#define SCI_COMM_OFF            1u
#define SCI_COMM_TX_BUSY        2u
#define SCI_COMM_RX_OVERRUN     3u

/*-- Macros ------------------------------------------------------------------*/

#define SCI115200bps    (UINT16)((UINT32)(gu32BusFrequency) / (UINT32)(1843200u))/* (115200 * 16) */ 
#define SCI57600bps     (UINT16)((UINT32)(gu32BusFrequency) / (UINT32)(921600u)) /* (57600 * 16) */   
#define SCI38400bps     (UINT16)((UINT32)(gu32BusFrequency) / (UINT32)(614400u)) /* (38400 * 16) */
#define SCI19200bps     (UINT16)((UINT32)(gu32BusFrequency) / (UINT32)(307200u)) /* (19200 * 16) */
#define SCI9600bps      (UINT16)((UINT32)(gu32BusFrequency) / (UINT32)(153600u)) /* (9600 * 16)  */
#define SCI4800bps      (UINT16)((UINT32)(gu32BusFrequency) / (UINT32)(76800u))  /* (4800 * 16)  */


/*-- Register definitions ----------------------------------------------------*/

#define SCI_MAIN_NODE_OFS                   8

#define SCI_CR2_RE_MASK                     (UINT8)4
#define SCI_CR2_TE_MASK                     (UINT8)8
#define SCI_SR1_RDRF_MASK                   (UINT8)32
#define SCI_CR2_TIE_MASK                    (UINT8)128
#define SCI_SR1_TDRE_MASK                   (UINT8)128
#define SCI_SR1_OR_MASK                     (UINT8)8

#define SCIxCR1_DEFAULT         0x00u    
/* Configuration of SCI control register 1         */
/* SCIxCR1 = 0x00u;                                */
/*    0b00000000
        ||||||||____ Even parity bit, even parity
        |||||||_____ Parity function bit, parity disabled 
        ||||||______ Idle character bit count begins after start bit 
        |||||_______ Idle line wakeup
        ||||________ One start bit, eight data bits, one stop bit
        |||_________ Rx input internally connected to Tx output
        ||__________ SCI enabled in wait mode
        |___________ Loop Select bit, normal operation enabled
*/
#define SCIxCR2_DEFAULT         0x00u
/* Configuration of SCI control register 2          */
/* SCI0CR2 = 0x00u;                                 */
/*    0b00000000
        ||||||||____ SendBrakeBit
        |||||||_____ Receiver Wakeup bit
        ||||||______ Receiver Enable bit
        |||||_______ Transmiter Enable Bit
        ||||________ Idle Line Interrupt Enable Bit
        |||_________ Receiver full interrupt enable bit
        ||__________ Transmission complete interrupt enable bit
        |___________ Transmitter Interrupt Enable Bit
*/

#define SCI_WRITE_BD(NodeIndex, Value)      (*((&SCI0BD)  + (SCI_MAIN_NODE_OFS * NodeIndex)) = (UINT16)Value)
#define SCI_WRITE_CR1(NodeIndex, Value)     (*((&SCI0CR1) + (SCI_MAIN_NODE_OFS * NodeIndex)) = (UINT8) Value)
#define SCI_WRITE_CR2(NodeIndex, Value)     (*((&SCI0CR2) + (SCI_MAIN_NODE_OFS * NodeIndex)) = (UINT8) Value)
#define SCI_WRITE_DRL(NodeIndex, Value)     (*((&SCI0DRL) + (SCI_MAIN_NODE_OFS * NodeIndex)) = (UINT8) Value) 


#define SCI_READ_CR2(NodeIndex)             (*((&SCI0CR2) + (SCI_MAIN_NODE_OFS * NodeIndex)))
#define SCI_READ_SR1(NodeIndex)             (*((&SCI0SR1) + (SCI_MAIN_NODE_OFS * NodeIndex)))
#define SCI_READ_DRL(NodeIndex)             (*((&SCI0DRL) + (SCI_MAIN_NODE_OFS * NodeIndex)))
                                                                                        
                                            
/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/


/** SCI Port disable transmission and reception */
void vfnSCI_OFF(enum tSCI_Channel u8SCIPort);
/** SCI Initalization */
void vfnSCI_Init(const tSCIdriver_config * SCIdriver_config);
/** SCI Low-Level Byte Transmit function **/
void vfnSCI_WriteTx(enum tSCI_Channel u8SCIPort, UINT8 u8TxDataByte);
/** SCI Byte read from receive buffer **/
UINT8 u8SCI_ReadRx(enum tSCI_Channel u8SCIPort);
/** SCI Data bytes available from receive buffer **/
UINT8 u8SCI_CheckRx(enum tSCI_Channel u8SCIPort);
/** Discard any incomming data on SCI receive buffer **/
void vfnSCI_ClearRx(enum tSCI_Channel u8SCIPort);
/** Discard any queued data on SCI transmit buffer **/
void vfnSCI_ClearTx(enum tSCI_Channel u8SCIPort);
/** SCI Low-Level Buffer Transmit function - interrupt driven scheme */
void vfnSCI_WriteBufferTx(enum tSCI_Channel  u8SCIPort, UINT8*  pu8TxDataBuffer, UINT8 u8BufferLenght );
/** SCI Status - to be used by upper layers */
UINT8 u8SCI_GetStatus(enum tSCI_Channel u8SCIPort); 

#pragma CODE_SEG __NEAR_SEG NON_BANKED
/** SCI 0 serves Tx and Rx events **/
void interrupt vfnSCI0_TxRx_Isr (void);
/** SCI 1 serves Tx and Rx events **/
void interrupt vfnSCI1_TxRx_Isr (void);
#pragma CODE_SEG DEFAULT


/**************************************************************************************************/

#endif /* __SERIAL_H */