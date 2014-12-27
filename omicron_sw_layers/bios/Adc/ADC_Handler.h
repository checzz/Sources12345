/*******************************************************************************/
/**
\file       Adc.c
\brief      Application handler for ADC
\author     Team 7 (Propedeutico Sistemas Embebidos - ITESO)
\version    1.0
\date       28/Jun/2014
\warning    (If needed)
*/
/*******************************************************************************/
#ifndef __ADC_HANDLER_H__        /*prevent duplicated includes*/
#define __ADC_HANDLER_H__


/*-- Includes ----------------------------------------------------------------*/
#include "Adc.h"

/** Variable types and common definitions */
#include "typedefs.h"

/*-- Types Definitions -------------------------------------------------------*/


/*-- Defines -----------------------------------------------------------------*/

#define HAL_ADC_MAX_SAMPLE_NUMBER 10

/*-- Function Prototypes -----------------------------------------------------*/
extern void ADC_vInitHandler(void);
extern void ADC_vTriggerSample(void);
extern void ADC_vPerformAverage(void);

/*-- Data/Configuration Validation -------------------------------------------*/
#define MAX_ADC_NUMBER_OF_SAMPLES 8
#if (HAL_ADC_NUMBER_OF_SAMPLES > MAX_ADC_NUMBER_OF_SAMPLES)
  #error Configured number of channels is greater than HAL_ADC_NUMBER_OF_SAMPLES
#endif
#endif/* EOF __ADC_HANDLER_H__ */