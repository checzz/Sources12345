/****************************************************************************************************/
/**
\file       timer.cxgate
\brief      Timer initialization and low-level functions and prototypes
\author     Abraham Tezmol
\version    1.0
\date       14/09/2012
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
/* Periodic Interrupt Timer routines prototypes */
#include    "timer.h"

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/	

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/


/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


 
/****************************************************************************************************/
/**
* \brief    TIMer future event scheduling. schedules a future event and programmes
*           the logical level for the future event  
* \author   Abraham Tezmol
* \param    UINT16 u16Timeout   - [1..0xFFFF] PIT timeout value
* \param    UINT8  level - desired logical level to be driven @ the future event
* \return   void
*/
    void vfnTimer_ScheduleEventRPM( UINT16 u16Timeout, UINT8 level )
    {
    /* Calculate future event --> 
       roll over 16 bits is possible and the expected behavior due to nature of 16-bit counters */
        TIM_TC2            = (UINT16)(TIM_TCNT + u16Timeout);
    /* Clear any pending output compare flag from past*/
        TIM_TFLG1_C2F           = 1u;
    /* Programmes logical level for the future event @ OCx pin */
        TIM_TCTL2_OL2           = level;
    }

/****************************************************************************************************/
/**
* \brief    TIMer drive pin level. Allows assciated OCx to be driven to the selected logical value
* \author   Abraham Tezmol
* \param    UINT8 level - logical level to be driven into OCx output pin
* \return   void
*/
    void vfnTimer_DriveRPMPinState_Main( UINT8 level )
    {
    /* Disconnect OCx pin from the timer control */
        TIM_OCPD_OCPD2         = 1u;
    /* Select output compare action upon match --> selected option is clear OCx output line to zero  */
        TIM_TCTL2_OM2          = 1u;
        TIM_TCTL2_OL2          = level;
    /* Allow the desired state to be programmed on its internal register */
        TIM_CFORC_FOC2         = 1u;
    /* Reconnect OCx pin to timer control --> this causes the internal programmed value into pin state */
        TIM_OCPD_OCPD2         = 0u;
    }
