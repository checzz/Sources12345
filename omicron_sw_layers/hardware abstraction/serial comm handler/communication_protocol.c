/****************************************************************************************************/
/**
\file       communication_protocol.c
\brief      High Level Serial communication protocol services.
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
/** Serial communication protocol definitions */
#include    "communication_protocol.h"
/** RPM control definitions */
#include    "rpm_control.h"

#include    "scheduler.h"

/** Used modules */

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

void vfnCOM_Init( void  );
void vfnCOM_SendAck( void );
void vfnCOM_Analyse( void );

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

               /* Maximum Rx buffer length minun header, service and length bytes */
               UINT8   au8COM_RX_message[ kCOM_RX_MaxSize];
               UINT8   u8COM_State;
               UINT32  u32COM_control_timer;
               UINT8   u8FormatID_found;
               UINT8   u8RxFormatID;
               UINT8   u8COM_RxLength;
               UINT8   u8COM_Byte_counter;
               UINT8   u8COM_RxLength;
               UINT8   u8COM_Checksum;
               UINT8   u8RxSid;
               UINT8   u8RxData;
               UINT8   u8RxByteCount;
               UINT8   au8COM_TX_message[] = { 81, NOT_ACKNOWLEDGED, 0, 0};
               UINT8   au8COM_TX_RPM_message[]= { 82, 0, 0, 0};
               UINT8   u8Ack;
               UINT16  u16RPM_temp;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/**************************************************************************************************/
/**
* \brief    vfnCommProtocol_Init - Initialization of low-level SCI resources needed for communications
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnCommProtocol_Init(void)
{
    
	/* SCI Initialization */
    vfnSCI_Init(&SCI_config[0]);
	

    vfnCOM_Init();
}

/**************************************************************************************************/
/**
* \brief    vfnCOM_Init - Reset of cummunication tasks
* \author   Abraham Tezmol 
* \param    void
* \return   void
* \todo     
*/
void vfnCOM_Init( void  )
{
    /* Reset Communication State Machine Status*/
    u8COM_State          = COM_STATE_WAIT_FOR_RX;
    /* Reset timeout control counter */
    u32COM_control_timer = 0u;
    /* Set default acknowledge state */ 
    u8Ack                = NOT_ACKNOWLEDGED;
    /* Default state for header rx state machine */
    u8FormatID_found = 0;
}

/**************************************************************************************************/
/**
* \brief    vfnCOM_RxByte - Rx processing of 1 byte
* \author   Abraham Tezmol 
* \param    void
* \return   void
* \todo     
*/
void vfnCOM_RxByte(void )
{
    static UINT8 u8ActivationStatus;
    
    if( u8SCI_CheckRx( SERIAL_COMM_CHANNEL ) != 0u )
    {
        u8ActivationStatus = u8Scheduler_EventActivationHandler(&vfnCOM_TxByte, TASKS_EVENT_A, 1);
        vfnSCI_ClearRx( SERIAL_COMM_CHANNEL );
        
    }
}

/**************************************************************************************************/
/**
* \brief    vfnCOM_TxByte - Tx processing of 1 byte
* \author   Abraham Tezmol 
* \param    void
* \return   void
* \todo     
*/
void vfnCOM_TxByte(void)
{
    /* Acknowledge */
    vfnSCI_WriteTx( SERIAL_COMM_CHANNEL, 0xBC );         /* Send Acknowledge */
}

/****************************************************************************************************/
/**
* \brief    
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
    
void vfnCheckCommands(void)
{
    UINT8 u8Index;
    static UINT8 u8RxBytes;

    u32COM_control_timer++;

    switch(u8COM_State) 
    {
      /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        case COM_STATE_WAIT_FOR_RX:
            /* Waiting for reception of Format Byte */
                u8RxBytes =  u8SCI_CheckRx( SERIAL_COMM_CHANNEL );
                if( u8RxBytes == 0u )
                {
                /* In case no data bytes have been received, check for timeout */
                    if( u32COM_control_timer >= COM_RX_TIMEOUT_MAX )
                    {
                    /* In case timeout elapses, discard any previous communication */
                        vfnCOM_Init( );
                    }
                }
                else
                {
                    for (u8Index=0; u8Index<u8RxBytes; u8Index++)
                    {
                       /* Format Byte received, proceed to verify for valid Format byte */
                        u8RxFormatID = u8SCI_ReadRx( SERIAL_COMM_CHANNEL ); 
                        /* If valie Format Byte                                         */
                        if( u8RxFormatID  == VALID_HEADER )
                        {
                            u8FormatID_found = 1;
                            break;
                        }
                    }
                    if (!u8FormatID_found)
                    {
                    
                        /* Discard message */
                        vfnSCI_ClearRx( SERIAL_COMM_CHANNEL );
                    }
                    else
                    { /* Valid Format ID, process message data */ 
                    /* Start message reception */
                        u8COM_State          = COM_STATE_VALID_HEADER;
                    /* Begin calculation of Checksum */
                        u8COM_Checksum       = u8RxFormatID;
                    /* Reset byte counter */
                        u8COM_Byte_counter   = 0u;
                    }
                }
            /* end of state */
                break;
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/      
            case COM_STATE_VALID_HEADER:
            /* Waiting for reception of Valid ID Byte */
                if( u8SCI_CheckRx( SERIAL_COMM_CHANNEL ) == 0u )
                {
                /* In case no data bytes have been received, check for timeout */
                    if( u32COM_control_timer >= COM_RX_TIMEOUT_MAX )
                    {
                    /* In case timeout elapses, discard any previous communication */
                        vfnCOM_Init( );
                    }
                } 
                else
                {
                /* Service ID received, proceed to verify for valid Format byte */
                    u8RxSid = u8SCI_ReadRx( SERIAL_COMM_CHANNEL );
                    /* If invalid Format Byte                                           */
                    /* or invalid message size (no data bytes or too many data bytes)   */
                    if ( 
                         (u8RxSid == kCOM_Set_Crank_Prof) || (u8RxSid == kCOM_Set_Cram_Prof) || 
                         (u8RxSid == kCOM_Set_RPM) ||  
                         (u8RxSid == kCOM_Set_Crank_Type_Direction) || (u8RxSid == kCOM_Get_RPM) || (u8RxSid == kCOM_Enable_Stop)
                       )
                    { 
                    /* Valid Service ID, process message data */ 
                    /* Start message reception */
                        u8COM_State          = COM_STATE_VALID_SID;
                    /* Proceed with calculation of Checksum */
                        u8COM_Checksum       |= u8RxSid;
                    }
                    else
                    {
                        vfnSCI_ClearRx( SERIAL_COMM_CHANNEL );
                    } 
                }
            /* end of state */
                break;
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/      
            case COM_STATE_VALID_SID:
            /* Waiting for reception of Format Byte */
                if( u8SCI_CheckRx( SERIAL_COMM_CHANNEL ) == 0u )
                {
                /* In case no data bytes have been received, check for timeout */
                    if( u32COM_control_timer >= COM_RX_TIMEOUT_MAX )
                    {
                    /* In case timeout elapses, discard any previous communication */
                        vfnCOM_Init( );
                    }
                } 
                else
                {
                /* Length byte received */
                    u8COM_RxLength = u8SCI_ReadRx( SERIAL_COMM_CHANNEL );
                    
                /* Valid Service ID, process message data */ 
                /* Start message reception */
                    u8COM_State          = COM_STATE_RECEIVING;
                /* Proceed with calculation of Checksum */
                    u8COM_Checksum       |= u8COM_RxLength;
                }
            /* end of state */
                break;
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            case COM_STATE_RECEIVING:
            /* Proceed to message reception */
                u8RxByteCount = u8SCI_CheckRx( SERIAL_COMM_CHANNEL );

                /* waiting for reception of Format Byte */
                if( u8RxByteCount == 0u )
                {
                /* In case no data bytes have been received, check for timeout */
                    if( u32COM_control_timer >= COM_RX_TIMEOUT_MAX )
                    {
                    /* In case timeout elapses, discard any previous communication */
                        vfnCOM_Init( );
                    }
                } 
                else
                {

                /* Process expected data bytes one by one */
                    for(u8Index = 0; u8Index<u8RxByteCount; u8Index++)
                    {
                    /* Read 1 data byte */
                        u8RxData = u8SCI_ReadRx( SERIAL_COMM_CHANNEL );
                    /* Check if byte is a messag character or a checksum byte */
                        if( u8COM_Byte_counter < u8COM_RxLength )
                        {
                        /* Byte is a message character, save received character */
                            au8COM_RX_message[ u8COM_Byte_counter ] = u8RxData;
                        /* Update checksum calculation */
                            u8COM_Checksum |= u8RxData;
                        /* Update number of expected data bytes */
                            ++u8COM_Byte_counter;
                        }
                        else
                        { 
                            /* Byte corresponds to checksum, verify checksum */ 
                            if( u8COM_Checksum != u8RxData )
                            { /* Checksum invalid, discharge message */  
                                vfnSCI_ClearRx( SERIAL_COMM_CHANNEL );
                                u8Ack = NOT_ACKNOWLEDGED;
                                /* Send acknowledge to serial interface */
                                vfnCOM_SendAck( );
                            }
                            else
                            { 
                            /* Clear Communication time out - Valid message has been received */
                                u32COM_control_timer = 0;
                            /* Checksum valid, proceed to call appropriate service */ 
                                if (u8RxSid == kCOM_Get_RPM) 
                                {
                                    vfnCOM_SendRPM( );
                                } 
                                else 
                                {
                                    /** Request access to shared data */
                                    XGATE_lock_hw_semaphore_1();

                                    vfnCOM_Analyse( );

                                    /* Release access to shared data */
                                    XGATE_release_hw_semaphore_1();

                                    /* Send acknowledge to serial interface */
                                    vfnCOM_SendAck( );
                                }
                                
                            /* Discard already processed message in order to flush RX buffer */
                                vfnSCI_ClearRx( SERIAL_COMM_CHANNEL );
                            /* Reset comm state machine */
                                u8COM_State = COM_STATE_WAIT_FOR_RX;
                            }
                        /* Message processing complete. Exit while loop*/
                            u8COM_Byte_counter= 0;
                            u8RxByteCount = 0u;
                        }
                    }
                }
            /* end of state */
                break;
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        default:      
            /* end of state */
                break;                 
    }

}
    
/**************************************************************************************************/
/**
* \brief    vfnCOM_SendAck - Send communication acknowledge to serial interface
* \author   Manuel Cortes / Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnCOM_SendAck(void) 
{           
    /* Acknowledge */
    au8COM_TX_message[1] = u8Ack;
    au8COM_TX_message[2] = u8RxSid;
    vfnSCI_WriteBufferTx( SERIAL_COMM_CHANNEL, au8COM_TX_message, COMMAND_SIZE );         /* Send Acknowledge */  
}

/**************************************************************************************************/
/**
* \brief    vfnCOM_SendRPM - Send current value of RPM to serial interface
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnCOM_SendRPM(void) 
{           
    /* Acknowledge */
    /** Request access to shared data */
    XGATE_lock_hw_semaphore_1();
    
    au8COM_TX_RPM_message[1] = (UINT8)u16SystemRPM;
    au8COM_TX_RPM_message[2] = (UINT8)(u16SystemRPM>>8);
    au8COM_TX_RPM_message[3] = cam_crank_channels[0].u8Direction;
    
    /* Release access to shared data */
    XGATE_release_hw_semaphore_1();

    vfnSCI_WriteBufferTx( SERIAL_COMM_CHANNEL, au8COM_TX_RPM_message, 4 );         /* Send Acknowledge */  
}

/**************************************************************************************************/
/**
* \brief    vfnCOM_Analyse - Definition of available communication services
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnCOM_Analyse(void) 
{
    static UINT16   u16CAMAngle = 0;
    static UINT16   u16Index;
    static UINT8    u8Index;
    static UINT8    u8Index2;
    static UINT8    u8Index3;
    static UINT8    u8CamEnable = 0;
    static UINT8    u8CAM_phase[4] = 0;
    static UINT8    u8CAM_value = CAM_SIGNAL_INIT_LEVEL;
    static UINT8    u8CAMarrayindex = 0;
    static UINT8    *ptrCAM_cell;
    static UINT8    *ptrCAM_arrays[4] = 
                    {
                        &u8CamConfig0[0],
                        &u8CamConfig1[0],
                        &u8CamConfig2[0],
                        &u8CamConfig3[0]
                    };

    
    u8Ack = NOT_ACKNOWLEDGED;    

    /* Invoke appropriate diagnostic service depending upon Diagnostic Service Identifier */
    switch( u8RxSid )
    {        
        case kCOM_Set_Crank_Prof: 
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /* Set Crank Profile Service */       

            u8Index = 0;
            /* Receive teeth definitions */
            u8CrankActiveLevel = au8COM_RX_message[u8Index++];
            u8CrankIdleLevel = (~u8CrankActiveLevel) & 0x01;
            u8CrankTeeth = au8COM_RX_message[u8Index++];
            u8MissingTeeth = au8COM_RX_message[u8Index++];                                           
            /* Initialize Crank profile with IDLE level */
            for( u16Index = 0; u16Index < ENGINE_ANGLE_DEGREES; u16Index++ )
            {
                u8CrankConfig[u16Index] = CRANK_SIGNAL_LOGICAL_IDLE_LEVEL;
            }
            /* Place active level teeth on the Crank profile */
            for( u8Index2 = 0; u8Index2 < u8CrankTeeth; u8Index2++ )
            {
                /* Set Crankshaft configuration */
                u8CrankConfig[u8Index2*(360/u8CrankTeeth)] = CRANK_SIGNAL_LOGICAL_ACTIVE_LEVEL;      
                u8CrankConfig[u8Index2*(360/u8CrankTeeth) + 360] = CRANK_SIGNAL_LOGICAL_ACTIVE_LEVEL;      
            }
            
            /* Set missing teeth */
            for( u8Index2 = 0; u8Index2 < u8MissingTeeth; u8Index2++ )
            {
                u16MissingTeethIndex = (UINT16) au8COM_RX_message[u8Index++];
                u16MissingTeethIndex = u16MissingTeethIndex*(360/u8CrankTeeth);
            
                u8CrankConfig[u16MissingTeethIndex] = CRANK_SIGNAL_LOGICAL_IDLE_LEVEL;
                u16MissingTeethIndex = u16MissingTeethIndex + 360;          
                u8CrankConfig[u16MissingTeethIndex] = CRANK_SIGNAL_LOGICAL_IDLE_LEVEL; 
            }
            
            /* Set extra tooth */
            u16ExtraTooth_degrees = au8COM_RX_message[u8Index++];
            u16ExtraTooth_degrees = (256* au8COM_RX_message[u8Index]) + u16ExtraTooth_degrees;
            u8CrankConfig[u16ExtraTooth_degrees] = CRANK_SIGNAL_LOGICAL_ACTIVE_LEVEL;

            u8Ack = ACKNOWLEDGED;
            /* end of state */
            break;  
        
        case kCOM_Set_Cram_Prof:
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /* Set CAM profile Service */          
            
            /* Prepare index to loop through all RX data bytes */
            u8Index = 0;
            u8CAMarrayindex = 0;
            
            for (u8Index3 = 0; u8Index3 < 4; u8Index3++)
            {    
                ptrCAM_cell = ptrCAM_arrays[u8CAMarrayindex++];
                /* Get number of transitions for CAM Signal */
                u8CamSignalTransitions = au8COM_RX_message[u8Index++];
                /* Get initial value of CAM signal */
                u8CAM_value = au8COM_RX_message[u8Index++];
                /* Prepare index to loop through all CAM profile */
                u16Index = 0;
                
                /* Loop through all transitions that define CAM signal */
                for( u8Index2 = 0; u8Index2 < u8CamSignalTransitions; u8Index2++ )
                {
                    /* Calculate next transition index */
                    u16CAMAngle = (UINT16)au8COM_RX_message[u8Index++];
                    u16CAMAngle += au8COM_RX_message[u8Index++]<<8;
                    
                    /* Set CAMshaft configuration */
                    for (u16Index ; u16Index < u16CAMAngle; u16Index ++) 
                    {    
                        *ptrCAM_cell++ = u8CAM_value;
                    }
                    /* Toggle CAM signal to create next level of CAM signal */
                    u8CAM_value ^= 0x01;
                }
            }

            u8Ack = ACKNOWLEDGED;
            /* end of state */                
            break;
        
        case kCOM_Set_RPM:
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /* Set RPM Service */             
                            
            /* Calculate RPMs */
            u16RPM_temp = (UINT16)(au8COM_RX_message[0] + (256*au8COM_RX_message[1])); 
            /* Set RPM's value if within allowed range */
            if (u16RPM_temp <= POSITIVE_RPM_MAX)
            {    
                u16RPMValue =   u16RPM_temp;
                u8Ack = ACKNOWLEDGED;                       
            }

            /* end of state */
            break;
        
        case kCOM_Set_Crank_Type_Direction:
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /* Set CRANK Type and Direction Service */  

            /* Get u8Direction */
            cam_crank_channels[0].u8DirConfig = au8COM_RX_message[0];    
            /* Get u8DirConfig */                 
            u8Direction = au8COM_RX_message[1];
            cam_crank_channels[0].u8Direction = u8Direction;           

            /* end of state */
            u8Ack = ACKNOWLEDGED;
            break;       

        case kCOM_Enable_Stop:
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /* Enable Signal Generation stop at specific crank tooth Service */

            /* Get Angle degrees at which we shall stop */
            u16StopAtCrankAngle = (UINT16)(au8COM_RX_message[0] + (256*au8COM_RX_message[1])); 

            u8Ack = ACKNOWLEDGED;
            /* end of state */
            break;

        default:
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /* Default state - NO valid service */
            u8Ack = NOT_ACKNOWLEDGED;
            /* end of state */
            break;              
    }
}




    