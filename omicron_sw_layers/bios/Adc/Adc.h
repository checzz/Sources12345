/*******************************************************************************/
/**
\file       Adc.h
\brief      Definitions of registers for ADC
\author     Team 7 (Propedeutico Sistemas Embebidos - ITESO)
\version    1.0
\date       28/Jun/2014
\warning    (If needed)
* History:
*/
/*******************************************************************************/

#ifndef ADC_H          /*prevent duplicated includes*/
#define ADC_H


/*-- Includes ----------------------------------------------------------------*/
#include "configuration.h"

/*-- Types Definitions -------------------------------------------------------*/
/** Variable types and common definitions */
#include "typedefs.h"

/*-- Defines -----------------------------------------------------------------*/

#define CNF_ADC_RESOLUTION_8_BITS  0x0
#define CNF_ADC_RESOLUTION_10_BITS 0x1
#define CNF_ADC_RESOLUTION_12_BITS 0x2

#define CNF_ADC_JUSTIFICATION_LEFT  0x0
#define CNF_ADC_JUSTIFICATION_RIGHT 0x1

#define CNF_ADC_MAX_AVAILABLE_NUM_CHANNELS 16

/* ******* CONFIGURATION FOR CHANNEL 0 **********/
#if (HAL_ADC_NUMBER_OF_SAMPLES > 0)

#define ADC_CH0_RESOLUTION CNF_ADC_RESOLUTION_12_BITS //CNF_ADC_RESOLUTION_8_BITS

#define ADC_CH0_JUSTIFICATION CNF_ADC_JUSTIFICATION_RIGHT

#define ADC_CH0_PHYSICAL_CHANNEL 0

#endif

/* ******* CONFIGURATION FOR CHANNEL 1 **********/
#if (HAL_ADC_NUMBER_OF_SAMPLES > 1)

#define ADC_CH1_RESOLUTION CNF_ADC_RESOLUTION_12_BITS

#define ADC_CH1_JUSTIFICATION CNF_ADC_JUSTIFICATION_RIGHT

#define ADC_CH1_PHYSICAL_CHANNEL 1

#endif

/* ******* CONFIGURATION FOR CHANNEL 2 **********/
#if (HAL_ADC_NUMBER_OF_SAMPLES > 2)

#define ADC_CH2_RESOLUTION CNF_ADC_RESOLUTION_8_BITS

#define ADC_CH2_JUSTIFICATION CNF_ADC_JUSTIFICATION_LEFT //RIGHT

#define ADC_CH2_PHYSICAL_CHANNEL 10

#endif

/* ******* CONFIGURATION FOR CHANNEL 3 **********/
#if (HAL_ADC_NUMBER_OF_SAMPLES > 3)

#define ADC_CH3_RESOLUTION CNF_ADC_RESOLUTION_8_BITS

#define ADC_CH3_JUSTIFICATION CNF_ADC_JUSTIFICATION_RIGHT

#define ADC_CH3_PHYSICAL_CHANNEL 11

#endif

/* ******* CONFIGURATION FOR CHANNEL 4 **********/
#if (HAL_ADC_NUMBER_OF_SAMPLES > 4)

#define ADC_CH4_RESOLUTION CNF_ADC_RESOLUTION_8_BITS

#define ADC_CH4_JUSTIFICATION CNF_ADC_JUSTIFICATION_RIGHT

#define ADC_CH4_PHYSICAL_CHANNEL 12

#endif

/* ******* CONFIGURATION FOR CHANNEL 5 **********/
#if (HAL_ADC_NUMBER_OF_SAMPLES > 5)

#define ADC_CH5_RESOLUTION CNF_ADC_RESOLUTION_8_BITS

#define ADC_CH5_JUSTIFICATION CNF_ADC_JUSTIFICATION_RIGHT

#define ADC_CH5_PHYSICAL_CHANNEL 13

#endif

/* ******* CONFIGURATION FOR CHANNEL 6 **********/
#if (HAL_ADC_NUMBER_OF_SAMPLES > 6)

#define ADC_CH6_RESOLUTION CNF_ADC_RESOLUTION_8_BITS

#define ADC_CH6_JUSTIFICATION CNF_ADC_JUSTIFICATION_RIGHT

#define ADC_CH6_PHYSICAL_CHANNEL 14

#endif

/* ******* CONFIGURATION FOR CHANNEL 7 **********/
#if (HAL_ADC_NUMBER_OF_SAMPLES > 7)

#define ADC_CH7_RESOLUTION CNF_ADC_RESOLUTION_8_BITS

#define ADC_CH7_JUSTIFICATION CNF_ADC_JUSTIFICATION_RIGHT

#define ADC_CH7_PHYSICAL_CHANNEL 15

#endif

/* Common Constants */
extern void ADC_vInit(void);
extern void ADC_vInitiateConvertion(tCallbackFunction pfCallBack, UINT16 *pu16Buffer);
extern UINT16 ADC_u16GetValue(UINT8 u8channel);

#pragma CODE_SEG __NEAR_SEG NON_BANKED
extern void interrupt vfnADC_SequenceRdy_Isr (void);
#pragma CODE_SEG DEFAULT


/*-- Defines Validation -----------------------------------------------------------------*/
#if (HAL_ADC_NUMBER_OF_SAMPLES > 0)

#if (ADC_CH0_RESOLUTION != CNF_ADC_RESOLUTION_8_BITS) && \
    (ADC_CH0_RESOLUTION != CNF_ADC_RESOLUTION_10_BITS)&& \
    (ADC_CH0_RESOLUTION != CNF_ADC_RESOLUTION_12_BITS)
    #error "Configuration of the ADC Resolution not supported"
#endif 

#if (ADC_CH0_JUSTIFICATION != CNF_ADC_JUSTIFICATION_RIGHT) && \
    (ADC_CH0_JUSTIFICATION != CNF_ADC_JUSTIFICATION_LEFT)
    #error "Configuration of the ADC Justification not supported"
#endif 

#if (ADC_CH0_PHYSICAL_CHANNEL < 0)  || \
    (ADC_CH0_PHYSICAL_CHANNEL > CNF_ADC_MAX_AVAILABLE_NUM_CHANNELS)
    #error "Number of channel for channel 0 is not valid"
#endif

#endif /*(CNF_ADC_CH0==ON)*/

                     
#if (HAL_ADC_NUMBER_OF_SAMPLES > 1)

#if (ADC_CH1_RESOLUTION != CNF_ADC_RESOLUTION_8_BITS) && \
    (ADC_CH1_RESOLUTION != CNF_ADC_RESOLUTION_10_BITS) && \
    (ADC_CH1_RESOLUTION != CNF_ADC_RESOLUTION_12_BITS)
    #error "Configuration of the ADC Resolution not supported"
#endif 

#if (ADC_CH1_JUSTIFICATION != CNF_ADC_JUSTIFICATION_RIGHT) && \
    (ADC_CH1_JUSTIFICATION != CNF_ADC_JUSTIFICATION_LEFT)
    #error "Configuration of the ADC Justification not supported"
#endif 

#if (ADC_CH1_PHYSICAL_CHANNEL < 0)  || \
    (ADC_CH1_PHYSICAL_CHANNEL > CNF_ADC_MAX_AVAILABLE_NUM_CHANNELS)
    #error "Number of channel for channel 1 is not valid"
#endif

#endif /*(CNF_ADC_CH1==ON)*/


#if (HAL_ADC_NUMBER_OF_SAMPLES > 2)

#if (ADC_CH2_RESOLUTION != CNF_ADC_RESOLUTION_8_BITS) && \
    (ADC_CH2_RESOLUTION != CNF_ADC_RESOLUTION_10_BITS) && \
    (ADC_CH2_RESOLUTION != CNF_ADC_RESOLUTION_12_BITS)
    #error "Configuration of the ADC Resolution not supported"
#endif 

#if (ADC_CH2_JUSTIFICATION != CNF_ADC_JUSTIFICATION_RIGHT) && \
    (ADC_CH2_JUSTIFICATION != CNF_ADC_JUSTIFICATION_LEFT)
    #error "Configuration of the ADC Justification not supported"
#endif 

#if (ADC_CH2_PHYSICAL_CHANNEL < 0)  || \
    (ADC_CH2_PHYSICAL_CHANNEL > CNF_ADC_MAX_AVAILABLE_NUM_CHANNELS)
    #error "Number of channel for channel 2 is not valid"
#endif

#endif /*(CNF_ADC_CH2==ON)*/

                     
#if (HAL_ADC_NUMBER_OF_SAMPLES > 3)

#if (ADC_CH3_RESOLUTION != CNF_ADC_RESOLUTION_8_BITS) && \
    (ADC_CH3_RESOLUTION != CNF_ADC_RESOLUTION_10_BITS) && \
    (ADC_CH3_RESOLUTION != CNF_ADC_RESOLUTION_12_BITS)
    #error "Configuration of the ADC Resolution not supported"
#endif 

#if (ADC_CH3_JUSTIFICATION != CNF_ADC_JUSTIFICATION_RIGHT) && \
    (ADC_CH3_JUSTIFICATION != CNF_ADC_JUSTIFICATION_LEFT)
    #error "Configuration of the ADC Justification not supported"
#endif 

#if (ADC_CH3_PHYSICAL_CHANNEL < 0)  || \
    (ADC_CH3_PHYSICAL_CHANNEL > CNF_ADC_MAX_AVAILABLE_NUM_CHANNELS)
    #error "Number of channel for channel 3 is not valid"
#endif

#endif /*(CNF_ADC_CH3==ON)*/

#if (HAL_ADC_NUMBER_OF_SAMPLES > 4)

#if (ADC_CH4_RESOLUTION != CNF_ADC_RESOLUTION_8_BITS) && \
    (ADC_CH4_RESOLUTION != CNF_ADC_RESOLUTION_10_BITS) && \
    (ADC_CH4_RESOLUTION != CNF_ADC_RESOLUTION_12_BITS)
    #error "Configuration of the ADC Resolution not supported"
#endif 

#if (ADC_CH4_JUSTIFICATION != CNF_ADC_JUSTIFICATION_RIGHT) && \
    (ADC_CH4_JUSTIFICATION != CNF_ADC_JUSTIFICATION_LEFT)
    #error "Configuration of the ADC Justification not supported"
#endif 

#if (ADC_CH4_PHYSICAL_CHANNEL < 0)  || \
    (ADC_CH4_PHYSICAL_CHANNEL > CNF_ADC_MAX_AVAILABLE_NUM_CHANNELS)
    #error "Number of channel for channel 4 is not valid"
#endif

#endif /*(CNF_ADC_CH4==ON)*/

                     
#if (HAL_ADC_NUMBER_OF_SAMPLES > 5)

#if (ADC_CH5_RESOLUTION != CNF_ADC_RESOLUTION_8_BITS) && \
    (ADC_CH5_RESOLUTION != CNF_ADC_RESOLUTION_10_BITS) && \
    (ADC_CH5_RESOLUTION != CNF_ADC_RESOLUTION_12_BITS)
    #error "Configuration of the ADC Resolution not supported"
#endif 

#if (ADC_CH5_JUSTIFICATION != CNF_ADC_JUSTIFICATION_RIGHT) && \
    (ADC_CH5_JUSTIFICATION != CNF_ADC_JUSTIFICATION_LEFT)
    #error "Configuration of the ADC Justification not supported"
#endif 

#if (ADC_CH5_PHYSICAL_CHANNEL < 0)  || \
    (ADC_CH5_PHYSICAL_CHANNEL > CNF_ADC_MAX_AVAILABLE_NUM_CHANNELS)
    #error "Number of channel for channel 5 is not valid"
#endif

#endif /*(CNF_ADC_CH5==ON)*/

#if (HAL_ADC_NUMBER_OF_SAMPLES > 6)

#if (ADC_CH6_RESOLUTION != CNF_ADC_RESOLUTION_8_BITS) && \
    (ADC_CH6_RESOLUTION != CNF_ADC_RESOLUTION_10_BITS) && \
    (ADC_CH6_RESOLUTION != CNF_ADC_RESOLUTION_12_BITS)
    #error "Configuration of the ADC Resolution not supported"
#endif 

#if (ADC_CH6_JUSTIFICATION != CNF_ADC_JUSTIFICATION_RIGHT) && \
    (ADC_CH6_JUSTIFICATION != CNF_ADC_JUSTIFICATION_LEFT)
    #error "Configuration of the ADC Justification not supported"
#endif 

#if (ADC_CH6_PHYSICAL_CHANNEL < 0)  || \
    (ADC_CH6_PHYSICAL_CHANNEL > CNF_ADC_MAX_AVAILABLE_NUM_CHANNELS)
    #error "Number of channel for channel 6 is not valid"
#endif

#endif /*(CNF_ADC_CH6==ON)*/

                     
#if (HAL_ADC_NUMBER_OF_SAMPLES > 7)

#if (ADC_CH7_RESOLUTION != CNF_ADC_RESOLUTION_8_BITS) && \
    (ADC_CH7_RESOLUTION != CNF_ADC_RESOLUTION_10_BITS) && \
    (ADC_CH7_RESOLUTION != CNF_ADC_RESOLUTION_12_BITS)
    #error "Configuration of the ADC Resolution not supported"
#endif 

#if (ADC_CH7_JUSTIFICATION != CNF_ADC_JUSTIFICATION_RIGHT) && \
    (ADC_CH7_JUSTIFICATION != CNF_ADC_JUSTIFICATION_LEFT)
    #error "Configuration of the ADC Justification not supported"
#endif 

#if (ADC_CH7_PHYSICAL_CHANNEL < 0)  || \
    (ADC_CH7_PHYSICAL_CHANNEL > CNF_ADC_MAX_AVAILABLE_NUM_CHANNELS)
    #error "Number of channel for channel 7 is not valid"
#endif

#endif /*(CNF_ADC_CH7==ON)*/


#endif  /*ADC_H*/