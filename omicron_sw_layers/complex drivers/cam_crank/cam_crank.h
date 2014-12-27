/*******************************************************************************/
/**
\file       cam_crank.h
\brief      Definitions and function prototypes for CAM CRANK signal generation
\author     Abraham Tezmol
\version    0.1
\date       04/04/2010
*/
/*******************************************************************************/

#ifndef __CAM_CRANK_H        /*prevent duplicated includes*/
#define __CAM_CRANK_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Configuration Options */
	#include 	"configuration.h"
/** S12X derivative information */
	#include 	__MCU_DERIVATIVE
/** Variable types */
	#include 	"typedefs.h"
/** Periodic Interrupt Timer routines prototypes */
	#include    "pit.h"	
/** Timer routines prototypes */
    #include    "timer.h"
/** XGATE definitions */
    #include    "xgate_config.h"	

/****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

typedef struct {
    UINT8   u8DirConfig;
    UINT8   u8Direction;    
} tCamCrankChDescr;

typedef struct {
	UINT8 	      u8ConfigSize;  
	tCamCrankChDescr 	*StrChDesPtr;	
} tCamCrankControl;

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/


#pragma DATA_SEG SHARED_DATA
	extern tCamCrankChDescr cam_crank_channels[5];                         
#pragma DATA_SEG DEFAULT

/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

#define CAM_SIGNAL                          0
#define CRANK_SIGNAL                        1

#define CRANK_SIGNAL_ACTIVE_LEVEL           0
#define CRANK_SIGNAL_IDLE_LEVEL             1

#define CRANK_SIGNAL_LOGICAL_ACTIVE_LEVEL   1
#define CRANK_SIGNAL_LOGICAL_IDLE_LEVEL     0

#define CAM_SIGNAL_INIT_LEVEL               1


#define DEFAULT_RPM_VALUE                   1000u
#define GM_CRANK_TEETH                      60u
#define GM_MISSING_TEETH                    2u
#define GM_CAM_TRANSITIONS                  9u
#define DEFAULT_ANGLE_EXTRATOOTH            6u
#define DEFAULT_ONEDEGREE_TICKS             4000u /* @ 24MHz PIT*/
#define ENGINE_ANGLE_DEGREES                1/*720*/

#define UNIDIRECTIONAL                      0u
#define BIDIRECTIONAL                       1u

#define FORWARD                             0u
#define REVERSE                             1u
#define NONE                                2u

/* For a low time of 90us if TIMER_PRECISION_FREQ_HIGH = 12000000 */
#define CRANK_WIDTH_BW_IN_PIT_COUNTS        1080u
/* For a low time of 45us if TIMER_PRECISION_FREQ_HIGH = 12000000 */
#define CRANK_WIDTH_FW_IN_PIT_COUNTS        540u  

#define CAM_CRANK_SEMAPHORE	0x00

/****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/ 

#pragma CODE_SEG XGATE_CODE

/* CAM / Crank generation ISR callback */	
    void vfnCamCrank_callback( void );

#pragma CODE_SEG DEFAULT

/* Cam Crank - Initialization */
    void vfnCamCrank_Init( void );


#pragma DATA_SEG SHARED_DATA

    extern  UINT8 u8CrankConfig[ENGINE_ANGLE_DEGREES];                           
    extern  UINT8 u8CamConfig0[ENGINE_ANGLE_DEGREES];                           
    extern  UINT8 u8CamConfig1[ENGINE_ANGLE_DEGREES];
    extern  UINT8 u8CamConfig2[ENGINE_ANGLE_DEGREES];
    extern  UINT8 u8CamConfig3[ENGINE_ANGLE_DEGREES];
  
#pragma DATA_SEG DEFAULT

#pragma DATA_SEG SHARED_DATA

    extern  UINT16  u16RPMValue;
    extern  UINT16  u16SystemRPM;
    extern  UINT16  u16Angle_OneDegreeTicks;
    extern  UINT16  u16CamCrankWidth_ticks;
    extern  UINT16  u16MissingTeethIndex;
    extern  UINT16  u16ExtraTooth_degrees;
    extern  UINT16  u16GlobalArrayIndex;
    extern  UINT16  u16StopAtCrankAngle;

    extern  UINT8   u8CrankActiveLevel;
    extern  UINT8   u8CrankIdleLevel;
    extern  UINT8   u8CrankTeeth;
    extern  UINT8   u8Direction;
    extern  UINT8   u8MissingTeeth;
    extern  UINT8   u8CamSignalTransitions;
    extern  UINT8   u8RPM_new_value;
    extern  UINT8   u8PIT_ClockNew;
    extern  UINT8   u8PIT_Clock;
    extern  UINT8   u8TIM_Clock;
    extern  UINT8   u8TIM_ClockNew;   
    extern  UINT8   u8EnableStopAtToothNumber;

#pragma DATA_SEG DEFAULT

/* CAM Crank Function Initialization */
#pragma CODE_SEG XGATE_CODE
	void interrupt vfnCamCrank_Init_XGATE_Isr(void);
#pragma CODE_SEG DEFAULT	

/* Cam Crank - Start */
void vfnCamCrank_Start ( void );

#endif /* __CAM_CRANK_H */

/*******************************************************************************/