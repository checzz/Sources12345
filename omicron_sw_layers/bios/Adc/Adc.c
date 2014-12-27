/*******************************************************************************/
/**
\file       Adc.c
\brief      Analog -> Digital Converter functions
\author     Team 7 (Propedeutico Sistemas Embebidos - ITESO)
\version    1.0
\date       28/Jun/2014
\warning    (If needed)
* History:
*/
/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Configuration Options */
#include "configuration.h"
/* S12X derivative information */      
#include __MCU_DERIVATIVE   
/** Variable types and common definitions */
#include "typedefs.h"

/** Own headers */
#include "Adc.h"

/** Used modules */

/*******************************************************************************/

#pragma CODE_SEG DEFAULT

const volatile UINT8 au8StaticConfiguration[]={
#if (HAL_ADC_NUMBER_OF_SAMPLES > 0) 
((0x0f)|(ADC_CH0_RESOLUTION<<5)),((0x40)|(ADC_CH0_JUSTIFICATION<<7)), ((UINT8) ADC_CH0_PHYSICAL_CHANNEL),(0) /*Padding byte*/,
#endif

#if (HAL_ADC_NUMBER_OF_SAMPLES > 1) 
((0x0f)|(ADC_CH1_RESOLUTION<<5)),((0x40)|(ADC_CH1_JUSTIFICATION<<7)), ((UINT8) ADC_CH1_PHYSICAL_CHANNEL),(0) /*Padding byte*/,
#endif

#if (HAL_ADC_NUMBER_OF_SAMPLES > 2) 
((0x0f)|(ADC_CH2_RESOLUTION<<5)),((0x40)|(ADC_CH2_JUSTIFICATION<<7)), ((UINT8) ADC_CH2_PHYSICAL_CHANNEL),(0) /*Padding byte*/,
#endif

#if (HAL_ADC_NUMBER_OF_SAMPLES > 3) 
((0x0f)|(ADC_CH3_RESOLUTION<<5)),((0x40)|(ADC_CH3_JUSTIFICATION<<7)), ((UINT8) ADC_CH3_PHYSICAL_CHANNEL),(0) /*Padding byte*/,
#endif

#if (HAL_ADC_NUMBER_OF_SAMPLES > 4) 
((0x0f)|(ADC_CH4_RESOLUTION<<5)),((0x40)|(ADC_CH4_JUSTIFICATION<<7)), ((UINT8) ADC_CH4_PHYSICAL_CHANNEL),(0) /*Padding byte*/,
#endif

#if (HAL_ADC_NUMBER_OF_SAMPLES > 5) 
((0x0f)|(ADC_CH5_RESOLUTION<<5)),((0x40)|(ADC_CH5_JUSTIFICATION<<7)), ((UINT8) ADC_CH5_PHYSICAL_CHANNEL),(0) /*Padding byte*/,
#endif

#if (HAL_ADC_NUMBER_OF_SAMPLES > 6) 
((0x0f)|(ADC_CH6_RESOLUTION<<5)),((0x40)|(ADC_CH6_JUSTIFICATION<<7)), ((UINT8) ADC_CH6_PHYSICAL_CHANNEL),(0) /*Padding byte*/,
#endif

#if (HAL_ADC_NUMBER_OF_SAMPLES > 7) 
((0x0f)|(ADC_CH7_RESOLUTION<<5)),((0x40)|(ADC_CH7_JUSTIFICATION<<7)), ((UINT8) ADC_CH7_PHYSICAL_CHANNEL),(0) /*Padding byte*/,
#endif

};

static volatile UINT16 au16ResultsBuffer[HAL_ADC_NUMBER_OF_SAMPLES];
tCallbackFunction pfnAdcConvertionRdy;
UINT16* pu16ConvertionBuffer;
volatile UINT8 u8ChannelCtr;
UINT16 const* pu16ResultPointer;
 

void ADC_vInit(void) {

  ATD0CTL0=0x01;    /*Wrap around CH1*/
  ATD0CTL1=au8StaticConfiguration[0];
  ATD0CTL2=0x02;    /*Enable interrupt*/
  ATD0CTL3=au8StaticConfiguration[1];
  ATD0CTL4=0x05;    /*Define sampling/prescaler*/
  /*
  0b00000000
    ||||||||
    |||||||+- \
    ||||||+--  \
    |||||+---   > PRS[4:0] Number of ATD clock prescaler (fATDCLK = fBUS/(2x(PRS[4:5]+1)) )
    ||||+----  /
    |||+----- /
    ||+------ \
    |+-------  > SMP[2:0] Sample Time 000 - 4  ATD
    +-------- /                       001 - 6  ATD
                                      010 - 8  ATD
                                      011 - 10 ATD
                                      100 - 12 ATD
                                      101 - 16 ATD
                                      110 - 20 ATD
                                      111 - 24 ATD

  */
  //esto seara parte de lo estable
  pu16ResultPointer=(const UINT16 *const)&ATD0DR0; //pointer to the adc result ADC
  ATD0CTL5=0x30;
  /*
  0b00110000
    ||||||||
    |||||||+- \  CA
    ||||||+--  \ CB Select the starting sequence channel
    |||||+---  / CC
    ||||+---- /  CD
    |||+----- MULT  Multiple channles
    ||+------ SCAN  Continuos
    |+------- SC    Selects special channels
    +-------- RESERVED
  */
  pu16ConvertionBuffer = NULL;
}

UINT16 ADC_u16GetValue(UINT8 u8channel)
{
  return au16ResultsBuffer[u8channel];
}

void ADC_vInitiateConvertion(tCallbackFunction pfCallBack, UINT16 *pu16Buffer){
   
   pfnAdcConvertionRdy=pfCallBack;
   pu16ConvertionBuffer=pu16Buffer;
   u8ChannelCtr=0;                // It should start with Channel 0 (0x00)
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt vfnADC_SequenceRdy_Isr (void){

  if (ATD0STAT0_SCF==1)
  {/* CONVERSION COMPLETE */
    ATD0STAT0_SCF=1;/*Clear interrupt flag*/
    au16ResultsBuffer[0]=ATD0DR0;
    au16ResultsBuffer[1]=ATD0DR1;
    if(pu16ConvertionBuffer != NULL)
    {
      pu16ConvertionBuffer[0] = au16ResultsBuffer[0];
      pu16ConvertionBuffer[1] = au16ResultsBuffer[1];
    }
    /*if (u8ChannelCtr<HAL_ADC_NUMBER_OF_SAMPLES)
    {
      pu16ConvertionBuffer[u8ChannelCtr]=pu16ResultPointer[ATD0STAT0_CC];
      u8ChannelCtr++;
    } 
    else
    {
      if(pfnAdcConvertionRdy != NULL)
      {
        pfnAdcConvertionRdy();
      }
    }*/
  }
  

  if (ATD0STAT0_ETORF==1)
  {/*EXTERNAL TRIGGER OVERRUN ERROR*/
    ATD0STAT0_ETORF=1;
  }

  if (ATD0STAT0_FIFOR==1)
  {/*RESULT REGISTER ERROR*/
    ATD0STAT0_FIFOR=1;
  }
}
#pragma CODE_SEG DEFAULT



