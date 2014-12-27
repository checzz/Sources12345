/****************************************************************************************************/
/**
\file       serial.c
\brief      Serial Communication Interface functions
\author     Abraham Tezmol
\version    1.0
\date       14/Oct/2013
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
/* SCI routines prototypes */
#include    "serial.h"
/** Interrupt funtcion prototypes definitions */
#include    "interrupt.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

const tSCIdriver_config * sci_cfg;

/* Pointer to SCI channel status structure */
tSCIchannel_status * sci_ch_status;

/*******************************************************************************************************************
* Declaration of module wide FUNCTIONs 
*******************************************************************************************************************/

/*******************************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*******************************************************************************************************************/
 
/*******************************************************************************************************************
* Declaration of module wide TYPEs 
*******************************************************************************************************************/

/*******************************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*******************************************************************************************************************/

/*******************************************************************************************************************
* Code of module wide FUNCTIONS
*******************************************************************************************************************/

/******************************************************************************************************************/
/**
* \brief    SCI port initialization
* \author   Abraham Tezmol
* \param    tSCIdriver_config sci_config - static driver configuration
* \return   void
*/

void vfnSCI_Init(const tSCIdriver_config * SCIdriver_config)
{
    UINT8  u8Index;
    enum tSCI_Channel  SCI_Channel;
    UINT8  SCIxCR1_temp;
    UINT8  SCIxCR2_temp;
    UINT16 SCI_baudrate_temp; 
    
    sci_cfg = SCIdriver_config;
    
    /* Allocate memory for internal status and control structures */
    sci_ch_status = (tSCIchannel_status *)MemAlloc_NearReserve( sci_cfg->u8Number_of_SCI_channels * sizeof(tSCIchannel_status));
    /* Prepare CR1 value -> this one is not affected by configuration */
    SCIxCR1_temp =  SCIxCR1_DEFAULT;
    
    
    for (u8Index = 0; u8Index < sci_cfg->u8Number_of_SCI_channels; u8Index++)
    {  
        /* Obtain SCI physical channel index */
        SCI_Channel = sci_cfg->SCI_channels_cfg[u8Index].SCI_Channel;
        
        /* Allocate memory for tx and rx buffers */
        sci_ch_status[u8Index].u8SCI_RxData = MemAlloc_NearReserve( sci_cfg->SCI_channels_cfg[u8Index].SCI_rx_buffer_size );
        sci_ch_status[u8Index].u8SCI_TxData = MemAlloc_NearReserve( sci_cfg->SCI_channels_cfg[u8Index].SCI_tx_buffer_size );
        sci_ch_status[u8Index].SCI_Channel = SCI_Channel;
        
        /* Prepare CR2 value -> this one is affected by configuration */
        SCIxCR2_temp =  SCIxCR2_DEFAULT | (sci_cfg->SCI_channels_cfg[u8Index].SCI_RX_enable << 2) | 
                                          (sci_cfg->SCI_channels_cfg[u8Index].SCI_TX_enable << 3) | 
                                          (sci_cfg->SCI_channels_cfg[u8Index].SCI_RIE_enable << 5);
        
        /* Write configuration values to registers */
        SCI_WRITE_CR1(SCI_Channel, SCIxCR1_temp);
        SCI_WRITE_CR2(SCI_Channel, SCIxCR2_temp);
        
        /* Validate configuration of baud rate */
        switch (sci_cfg->SCI_channels_cfg[u8Index].SCI_baudrate)
        {   
        case (115200):
            SCI_baudrate_temp =    SCI115200bps;
            break;
        case (57600):
            SCI_baudrate_temp =    SCI57600bps;
            break;
        case (38400):
            SCI_baudrate_temp =    SCI38400bps;
            break;
        case (19200):
            SCI_baudrate_temp =    SCI19200bps;
            break;
        case (9600):
            SCI_baudrate_temp =    SCI9600bps;
            break;
        case (4800):
            SCI_baudrate_temp =    SCI4800bps;
            break;       
        }
        /* Configure targer baud rate */
        SCI_WRITE_BD(SCI_Channel, SCI_baudrate_temp & 0x1fffu);
         
        /* Reset auxiliary variables for input buffer management */
        vfnSCI_ClearRx( SCI_Channel );
        /* Reset auxiliary variables for output buffer management */
        vfnSCI_ClearTx( SCI_Channel );
        
        /* Update SCI Communication status */
         sci_ch_status[u8Index].u8SCI_Comm_Status = SCI_COMM_ON;
    }
    
    
}

/******************************************************************************************************************/
/**
* \brief    Turn SCI port OFF. Disable transmission and reception.
* \author   Abraham Tezmol
* \param    enum tSCI_Channel   u8SCIPort. SCI port number
* \return   void
*/
void vfnSCI_OFF( enum tSCI_Channel  u8SCIPort )
{    
    UINT8  SCIxCR2_temp;
    
    /* Disable Transmission and Reception on the specific channel */
    SCIxCR2_temp = SCI_READ_CR2(u8SCIPort);
    SCIxCR2_temp =  (~SCI_CR2_RE_MASK & ~SCI_CR2_TE_MASK);
    SCI_WRITE_CR2(u8SCIPort, SCIxCR2_temp);
    
    /* Update SCI Communication status */
    sci_ch_status[u8SCIPort].u8SCI_Comm_Status = SCI_COMM_OFF;
}

/******************************************************************************************************************/
/**
* \brief    Read 1 data byte from input buffer. 
* \author   Abraham Tezmol
* \param    enum tSCI_Channel u8SCIPort - Port number
            0 -> SCI channel 0
            1 -> SCI channel 1
* \return   UINT8 - read byte from input buffer.
*/
UINT8 u8SCI_ReadRx( enum tSCI_Channel  u8SCIPort )
{
    UINT8 u8ReturnValue;

    /* Start of Critical section */
    INTERRUPT_DISABLE();
    sci_ch_status[u8SCIPort].u8SCI_RxLength--;
    u8ReturnValue = *(sci_ch_status[u8SCIPort].pu8SCI_Read_Receive_Data_ptr);
    sci_ch_status[u8SCIPort].pu8SCI_Read_Receive_Data_ptr++;
    INTERRUPT_ENABLE();
    /* End of Critical section */

    return ( u8ReturnValue );
}

/******************************************************************************************************************/
/**
* \brief    Provide global status of SCI channel. 
* \author   Abraham Tezmol
* \param    enum tSCI_Channel u8SCIPort - Port number
            0 -> SCI channel 0
            1 -> SCI channel 1
* \return   UINT8 - SCI channel status.
*/
UINT8 u8SCI_GetStatus( enum tSCI_Channel  u8SCIPort )
{
    UINT8 u8ReturnValue;

    u8ReturnValue = sci_ch_status[u8SCIPort].u8SCI_Comm_Status;

    return ( u8ReturnValue );
}

/******************************************************************************************************************/
/**
* \brief    SCI Low-Level Tramsmit Function
* \author   Abraham Tezmol
* \param    enum tSCI_Channel u8SCIPort - Port number
            0 -> SCI channel 0
            1 -> SCI channel 1
            UINT8 u8TxDataByte - Data byte to be transmitted
* \return   void
*/
void vfnSCI_WriteTx( enum tSCI_Channel  u8SCIPort, UINT8  u8TxDataByte )
{
    UINT8 SCIxSR1_temp;

    /* Start of Critical section */
    INTERRUPT_DISABLE();
    SCIxSR1_temp = SCI_READ_SR1(u8SCIPort);
    
    if( (SCIxSR1_temp & SCI_SR1_TDRE_MASK) == SCI_SR1_TDRE_MASK )
    {
        SCI_WRITE_DRL(u8SCIPort, u8TxDataByte);
    }
    else
    {
        /* Update SCI Communication status */
        sci_ch_status[u8SCIPort].u8SCI_Comm_Status = SCI_COMM_TX_BUSY;
    }
    INTERRUPT_ENABLE();
    /* End of Critical section */
}

/******************************************************************************************************************/
/**
* \brief    SCI Low-Level Tramsmit Buffer Function - Interrupt driven scheme
* \author   Abraham Tezmol
* \param    enum tSCI_Channel u8SCIPort - Port number
            0 -> SCI channel 0
            1 -> SCI channel 1
            UINT8* pu8TxDataBuffer - Pointer to data buffer to be transmitted
            UINT8  u8BufferLenght - Number of bytes to be transmitted
* \return   void
*/
void vfnSCI_WriteBufferTx( enum tSCI_Channel  u8SCIPort, UINT8 * pu8TxDataBuffer, UINT8  u8BufferLenght )
{
    UINT8 u8Index;
    UINT8 SCIxCR2_temp;

    if( sci_ch_status[u8SCIPort].u8SCI_Comm_Status == SCI_COMM_ON )
    {
        for( u8Index = 0u;
             u8Index < u8BufferLenght;
             u8Index++ )
        {
            sci_ch_status[u8SCIPort].u8SCI_TxData[ u8Index ] = *pu8TxDataBuffer;
            pu8TxDataBuffer++;
        }
        sci_ch_status[u8SCIPort].u8SCI_TxLength    = u8BufferLenght;
        /* Update SCI Communication status */
        sci_ch_status[u8SCIPort].u8SCI_Comm_Status = SCI_COMM_TX_BUSY;
        /* Enable interrupt-driven transmission scheme */
        SCIxCR2_temp = SCI_READ_CR2(u8SCIPort);
        SCIxCR2_temp |= SCI_CR2_TIE_MASK;
    }
}

/******************************************************************************************************************/
/**
* \brief    Poll for new data flag on SCI input buffer
* \author   Abraham Tezmol
* \param    enum tSCI_Channel u8SCIPort - Port number
            0 -> SCI channel 0
            1 -> SCI channel 1
* \return   UINT8 - Number of bytes in the reception buffer
*/
UINT8 u8SCI_CheckRx( enum tSCI_Channel  u8SCIPort )
{
    UINT8 u8ReturnValue;

    u8ReturnValue = sci_ch_status[u8SCIPort].u8SCI_RxLength;
   
    return ( u8ReturnValue );
}

/******************************************************************************************************************/
/**
* \brief    Discard any incomming data on SCI receive buffer
* \author   Abraham Tezmol
* \param    enum tSCI_Channel u8SCIPort - Port number
            0 -> SCI channel 0
            1 -> SCI channel 1
* \return   void
*/
void vfnSCI_ClearRx( enum tSCI_Channel  u8SCIPort )
{
    /* Reset auxiliary variables for input buffer management */
    sci_ch_status[u8SCIPort].pu8SCI_Receive_Data_ptr      = sci_ch_status[u8SCIPort].u8SCI_RxData;
    sci_ch_status[u8SCIPort].pu8SCI_Read_Receive_Data_ptr = sci_ch_status[u8SCIPort].pu8SCI_Receive_Data_ptr;
    sci_ch_status[u8SCIPort].u8SCI_RxLength               = 0u;
}

/******************************************************************************************************************/
/**
* \brief    Discard any queued data on SCI transmit buffer
* \author   Abraham Tezmol
* \param    enum tSCI_Channel u8SCIPort - Port number
            0 -> SCI channel 0
            1 -> SCI channel 1
* \return   void
*/
void vfnSCI_ClearTx( enum tSCI_Channel  u8SCIPort )
{
    UINT8 SCIxCR2_temp;
    
    /* inhibit interrupt-driven Tx scheme */
    SCIxCR2_temp = SCI_READ_CR2(u8SCIPort);
    SCIxCR2_temp &= ~SCI_CR2_TIE_MASK;
    SCI_WRITE_CR2(u8SCIPort, SCIxCR2_temp);
    
    /* Reset auxiliary variables for output buffer management */
    sci_ch_status[u8SCIPort].pu8SCI_Read_Transmit_Data_ptr = sci_ch_status[u8SCIPort].u8SCI_TxData;
    sci_ch_status[u8SCIPort].u8SCI_TxLength                = 0u;
    if( sci_ch_status[u8SCIPort].u8SCI_Comm_Status == SCI_COMM_TX_BUSY )
    {
        sci_ch_status[u8SCIPort].u8SCI_Comm_Status = SCI_COMM_ON;
    }

}

/******************************************************************************************************************/
/**
* \brief    SCI Tx and Rx Handler
* \author   Abraham Tezmol
* \param    enum tSCI_Channel u8SCIPort - Port number
            0 -> SCI channel 0
            1 -> SCI channel 1
* \return   void
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void vfnSCI_Tx_Rx_Handler( enum tSCI_Channel  u8SCIPort )
{
    UINT8 SCIxSR1_temp;
    UINT8 SCIxCR2_temp;
    
    SCIxSR1_temp = SCI_READ_SR1(u8SCIPort);
    
    if( (SCIxSR1_temp & SCI_SR1_RDRF_MASK) == SCI_SR1_RDRF_MASK)
    {
        *sci_ch_status[u8SCIPort].pu8SCI_Receive_Data_ptr = SCI_READ_DRL(u8SCIPort);    /*      Copy data from input buffer               */ 
        sci_ch_status[u8SCIPort].u8SCI_RxLength++;                                      /*      Update input data bytes counter           */ 
        sci_ch_status[u8SCIPort].pu8SCI_Receive_Data_ptr++;                             /*      Update input buffer pointer               */ 
    }
    else
    {
        SCIxCR2_temp = SCI_READ_CR2(u8SCIPort);
        
        /* If Tx shift register is ready for Tx */
        if( 
            (SCIxCR2_temp & SCI_CR2_TIE_MASK == SCI_CR2_TIE_MASK) &&
            (SCIxSR1_temp & SCI_SR1_TDRE_MASK == SCI_SR1_TDRE_MASK)
          )
        {
            /* Check for pending elements to transmit */
            if( sci_ch_status[u8SCIPort].u8SCI_TxLength > 0u )
            {
                /* Send out data byte */
                SCI_WRITE_DRL(u8SCIPort, *sci_ch_status[u8SCIPort].pu8SCI_Read_Transmit_Data_ptr);
                /* If pending elements to tx, point to next element*/
                sci_ch_status[u8SCIPort].u8SCI_TxLength--;
                sci_ch_status[u8SCIPort].pu8SCI_Read_Transmit_Data_ptr++;
            }
            else
            {   /* Last element transmitted, inhibit interrupt-driven Tx scheme */ 
                SCIxCR2_temp &= ~SCI_CR2_TIE_MASK;
                SCI_WRITE_CR2(u8SCIPort, SCIxCR2_temp);
                /* Update SCI Communication status */
                sci_ch_status[u8SCIPort].u8SCI_Comm_Status             = SCI_COMM_ON;
                sci_ch_status[u8SCIPort].pu8SCI_Read_Transmit_Data_ptr = sci_ch_status[u8SCIPort].u8SCI_TxData;
            }
        }
    }
}
#pragma CODE_SEG DEFAULT

/****************************************************************************************************/
/**
* \brief    SCI ISR, serves Tx and Rx events
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt  vfnSCI0_TxRx_Isr( void  )
{
    vfnSCI_Tx_Rx_Handler(SCI_CH0);
}
#pragma CODE_SEG DEFAULT

/****************************************************************************************************/
/**
* \brief    SCI ISR, serves Tx and Rx events
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt  vfnSCI1_TxRx_Isr( void  )
{
    vfnSCI_Tx_Rx_Handler(SCI_CH1);
}
#pragma CODE_SEG DEFAULT