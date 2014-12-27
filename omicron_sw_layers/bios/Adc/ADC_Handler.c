/*******************************************************************************/
/**
\file       ADC_Handler.c
\brief      Application handler for ADC
\author     Team 7 (Propedeutico Sistemas Embebidos - ITESO)
\version    1.0
\date       28/Jun/2014
\warning    (If needed)
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
/* ADC routines prototypes */ 
#include "ADC_Handler.h"

/** Used modules */
/** ADC prototypes and definitions */


/*******************************************************************************/
 static UINT8 u8Sample_Ctr;
 static UINT16 au8SamplesBuffer[HAL_ADC_NUMBER_OF_SAMPLES][HAL_ADC_MAX_SAMPLE_NUMBER];
 static UINT16 ADC_SAMPLES_AVG[HAL_ADC_NUMBER_OF_SAMPLES];
/*******************************************************************************/
/**
* \brief    <>
* \author   Marco Lopez
* \param    void
* \return   void
*/
void ADC_vInitHandler(void)
{
  UINT8 i=0;
  UINT8 j=0;
  
  u8Sample_Ctr=0;
  
  for(i=0;i<HAL_ADC_MAX_SAMPLE_NUMBER;i++)
  {
    for(j=0;j<HAL_ADC_MAX_SAMPLE_NUMBER;j++)
    {
      au8SamplesBuffer[i][j]=0;
    }
    ADC_SAMPLES_AVG[i]=0;
  }
  ADC_vInit();
}

/*******************************************************************************/
/**
* \brief    <>
* \author   Marco Lopez
* \param    void
* \return   void
*/
void ADC_vTriggerSample(void)
{
  if(u8Sample_Ctr >= HAL_ADC_MAX_SAMPLE_NUMBER)
  {
    u8Sample_Ctr = 0;
  }
  else
  {
    /* do nothing */
  }
  ADC_vInitiateConvertion(ADC_vPerformAverage, ADC_SAMPLES_AVG);
}

/*******************************************************************************/
/**
* \brief    <>
* \author   Marco Lopez
* \param    void
* \return   void
*/
void ADC_vPerformAverage(void)
{
  
/*  for(i=0;i<HAL_ADC_MAX_SAMPLE_NUMBER;i++)
  {
    au8SamplesBuffer[u8Sample_Ctr][i]=*pau8Buffer;
    pau8Buffer++;
  }*/
  /**/
  if(u8Sample_Ctr < HAL_ADC_MAX_SAMPLE_NUMBER)
  {
    u8Sample_Ctr++;
  }
  else
  {
    u8Sample_Ctr = 0;
  }
}