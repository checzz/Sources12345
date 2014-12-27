/****************************************************************************************************/
/**
\file       rpm_control.c
\brief      RMP control functions.
\author     Abraham Tezmol
\version    1.0
\date       06/01/2012
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own headers */
#include    "rpm_control.h"

/** Used modules */

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/
 #define APP_INVALID  (0x77)
/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
UINT16 u16NVM_data_request_status;
UINT8  gu8GlobalValue = VALID_APP_BLOCK_REFLASH_REQUEST;
/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
UINT8 u8TempVal;
UINT8 u8TempVal2;
UINT8 u8WriteFlg;
UINT8 u8BootFlg;
UINT16 u16MemStatus2;
UINT16 u16TempVal;
UINT16 u16InvalidateCtr;
/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/**************************************************************************************************/
/**
* \brief    vfnGetRPMButtons - Main RPM control function using push buttons.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnGetRPMButtons(void)
{
    
    /** Request to write to Shared data */
    XGATE_lock_hw_semaphore_1();
    
    if ( (PP0_push_button == PUSH_BUTTON_ACTIVE) && (PP1_push_button == PUSH_BUTTON_ACTIVE) )
    {
        /* Store all data that needs to be backed up in NVM data */
        
        /* Invalidate ASW subsystem */
        
        /* Verify status of EEEPROM memory controller */
        do
        {
            u16NVM_data_request_status = u16emul_eeprom_status( );
            WdgtCallbackFunction();
        }
        while (EMUL_EEPROM_STAT_OK != u16emul_eeprom_status() );
        
        /* Command a reset sequence to enter through boot */
        
    }
    else
    {        
        /** RPM control for BIDIRECTIONAL configuration */
        if (cam_crank_channels[0].u8DirConfig == BIDIRECTIONAL)
        {
            switch(cam_crank_channels[0].u8Direction )
            {
                case FORWARD:        
                    if (PP0_push_button == PUSH_BUTTON_ACTIVE)
                    {
                        if (u16RPMValue <= (POSITIVE_RPM_MAX - RPM_PushButton_Delta))
                        {
                            u16RPMValue = u16RPMValue + RPM_PushButton_Delta;
                        }
                    }
                    if (PP1_push_button == PUSH_BUTTON_ACTIVE)
                    {
                        if (u16RPMValue >= RPM_PushButton_Delta )
                        {
                            u16RPMValue -= RPM_PushButton_Delta;
                            if (u16RPMValue == 0u)
                            {
                                cam_crank_channels[0].u8Direction = REVERSE;
                            }
                        }
                        else 
                        {
                            /* Take care of the 0 RPM condition */
                            if (u16RPMValue == 0u) 
                            {
                                cam_crank_channels[0].u8Direction = REVERSE;
                                u16RPMValue += RPM_PushButton_Delta;
                            }
                        }
                    }
                    break;
                    
                case REVERSE:        
                    if (PP0_push_button == PUSH_BUTTON_ACTIVE)
                    {
                        if (u16RPMValue >= RPM_PushButton_Delta )
                        {
                            u16RPMValue -= RPM_PushButton_Delta;
                            if (u16RPMValue == 0u)
                            {
                                cam_crank_channels[0].u8Direction = FORWARD;
                            }
                        } 
                        else 
                        {
                            /* Take care of the 0 RPM condition */
                            if (u16RPMValue == 0u) 
                            {
                                cam_crank_channels[0].u8Direction = FORWARD;
                                u16RPMValue += RPM_PushButton_Delta;
                            }
                        }
                    }
                    if (PP1_push_button == PUSH_BUTTON_ACTIVE)
                    {
                        if (u16RPMValue <= (NEGATIVE_RPM_MIN - RPM_PushButton_Delta))
                        {
                            u16RPMValue = u16RPMValue + RPM_PushButton_Delta;
                        }
                    }
                    break; 
                    
                default:
                    break;       
            }
        }
        /** RPM control for UNIDIRECTIONAL configuration */
        else
        {
            if (PP0_push_button == PUSH_BUTTON_ACTIVE)
            {
                if (u16RPMValue <= (POSITIVE_RPM_MAX - RPM_PushButton_Delta))
                {
                    u16RPMValue = u16RPMValue + RPM_PushButton_Delta;
                }   
            }
            if (PP1_push_button == PUSH_BUTTON_ACTIVE)
            {        
                if (u16RPMValue >= RPM_PushButton_Delta )
                {
                    u16RPMValue -= RPM_PushButton_Delta;
                }
            }
        }
    }
    /* Release access to shared data */

    if( (PP0_push_button == PUSH_BUTTON_ACTIVE) &&  (PP1_push_button == PUSH_BUTTON_ACTIVE) )
    {
      if(u8WriteFlg==0)
      {
        
        if(u16InvalidateCtr < 500/* 5s/.01ms */)
        {
           u16InvalidateCtr++;
        }
        
         if(100 == u16InvalidateCtr )
        { 
          u8BootFlg=1;
        }
        
        if(500 == u16InvalidateCtr )
        {
          u8WriteFlg=1;
          u16MemStatus2=0;
          u8TempVal=APP_INVALID;
          u16MemStatus2=u16emul_eeprom_write((UINT32)&sNVM_InterfaceData.gu8AppBlockValidityFlag,(tu8ptr_far)&u8TempVal,sizeof(sNVM_InterfaceData.gu8AppBlockValidityFlag));
          while(EMUL_EEPROM_STAT_BUSY==u16emul_eeprom_status());
          u16MemStatus2=u16emul_eeprom_read((UINT32)&sNVM_InterfaceData.gu8AppBlockValidityFlag,sizeof(sNVM_InterfaceData.gu8AppBlockValidityFlag),(tu8ptr_far)&u8TempVal);
          if(APP_INVALID == u8TempVal )
          {
            for(;;);/*Force RESET*/
          }
        }
        
      }
      else
      {
      }
    }
    if( (PP0_push_button == PUSH_BUTTON_INACTIVE) &&  (PP1_push_button == PUSH_BUTTON_INACTIVE) )
    {
        /*do nothing*/
    }
}  

/**************************************************************************************************/
/**
* \brief    vfnCamCrankTimingCalculation - Set PIT timeout counts based on current value of RPM.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnCamCrankTimingCalculation(void)
{
    static UINT32 u32CrankDegrees_freq;
    static UINT32  u32HalfCrankTeeth_freq;

    /** Request to write to Shared data */
    do								
    {									
        XGSEM = 0x0101; 
    } 
    while(!(XGSEM & 0x0001));
    
    u32CrankDegrees_freq = (UINT32)((UINT32)u16RPMValue * (UINT32)DEGREES_PER_SEC);
    
    /* In case a new RPM value has been commanded */
    if (u16RPMValue != u16SystemRPM)
    {
        /* Set external RPM change indication */
        vfnTimer_DriveRPMPinState_Main(1);
        /* Schedule future event to turn off indication */
        vfnTimer_ScheduleEventRPM(25,0);

        /* This condition checks for 0 RPM condition which will cause infinite PIT timeout */
        if(u32CrankDegrees_freq != 0u)
        { 
            /* Verify requested range, choose clock source appropriately */
            if (u16RPMValue >= 100u)
            {            
                u8PIT_ClockNew = PIT_uTIMER_HIGH_RANGE;      
                /* Timeout is within working limits, use high frequency clock source */
                u16Angle_OneDegreeTicks = (UINT16)((UINT32)(PIT_uTIMER_FREQ_XGATE_HIGH) / u32CrankDegrees_freq);
            }
            else
            {            
                u8PIT_ClockNew = PIT_uTIMER_LOW_RANGE;       
                /* Timeout is within working limits, use low frequency clock source */
                u16Angle_OneDegreeTicks = (UINT16)((UINT32)(PIT_uTIMER_FREQ_XGATE_LOW) / u32CrankDegrees_freq);
                
            }
            /* Clear proper flag that enables stop mechanism */
            u8EnableStopAtToothNumber = 0x00u; 
            /* Update System RPM value with requested value */
            u16SystemRPM =  u16RPMValue; 
        }
        else
        {
            /* Timeout is outside limits (0 RPM case), flag this condition by setting the proper flag */
            u8EnableStopAtToothNumber = 0x01u;
        }
        /* */
        u8RPM_new_value = 1u;
    }
    
    /* CRANK_SIGNAL Settings */
    if(cam_crank_channels[0].u8DirConfig == BIDIRECTIONAL )
    {
        u8TIM_ClockNew = TIMER_HIGH_RANGE;
        /* BIDIRECTIONAL Configuration */
        if( cam_crank_channels[0].u8Direction == REVERSE )
        {
        /* REVERSE delay */
            u16CamCrankWidth_ticks = CRANK_WIDTH_BW_IN_PIT_COUNTS; 
        }
        else
        {
        /* FORWARD delay */
            u16CamCrankWidth_ticks = CRANK_WIDTH_FW_IN_PIT_COUNTS;      	      
        }
    }
    else
    {
            u32HalfCrankTeeth_freq =  (UINT32)((UINT32)u16SystemRPM * (UINT32)2 * (UINT32)u8CrankTeeth); 

            /* Verify requested range, choose clock source appropriately */
            if (u16RPMValue >= 100u)
            {            
                u8TIM_ClockNew = TIMER_HIGH_RANGE;      
                /* Timeout is within working limits, use high frequency clock source */
                u16CamCrankWidth_ticks = (UINT16)((UINT32)(TIMER_PRECISION_FREQ_HIGH * SECONDS_PER_MIN) / u32HalfCrankTeeth_freq);
            }
            else
            {            
                u8TIM_ClockNew = TIMER_LOW_RANGE;       
                /* Timeout is within working limits, use low frequency clock source */
                u16CamCrankWidth_ticks = (UINT16)((UINT32)(TIMER_PRECISION_FREQ_LOW *  SECONDS_PER_MIN) / u32HalfCrankTeeth_freq);
                
            }          
    }	

    /* Clear semaphore 0 by writing mask=1 and flag=0 */
    XGSEM = 0x0100;
}




