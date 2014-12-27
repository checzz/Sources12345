/****************************************************************************************************/
/**
\file       io.c
\brief      Microcontroller low-level input/output initialization functions
\author     Abraham Tezmol
\version    1.0
\date       11/Jul/2009
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
/* Input/Output routines prototypes */
#include    "io.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/*****************************************************************************************************/
/**
* \brief    Inputs and Outputs Initialization to default values/configuration
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnInputs_Outputs_Init(void)
{                  
    /************* Digital Inputs Initialization ******************************/
    /* - Configuration of Data Direction Register to Input                    */
    /* - ENABLED Pull up/down option                                           */
    /* - Set pull/down option to specified value                              */
    /**************************************************************************/  
              
    /** Port A, Channel 6 */
    DDRA_DDRA6 = INPUT;  
               
    /** Port A, Channel 7 */
    DDRA_DDRA7 = INPUT;   

    /** Port P, Channel 0 */
    DDRP_DDRP0 =  INPUT;
    /** Port P, Channel 1 */
    DDRP_DDRP1 =  INPUT;            
    
    /************* Digital Outputs Initialization *****************************/
    /* - Configuration of Data Direction Register to Output                   */
    /* - Set pin to specified value                                           */
    /**************************************************************************/
    
    /** LED505, Port A, Channel 0, High */
    DDRA_DDRA0 = OUTPUT;             
    PTA_PTA0 = HIGH;    
    
    /** LED504, Port A, Channel 1, Low */
    DDRA_DDRA1 = OUTPUT;             
    PTA_PTA1 = LOW;    
    
    /** LED503, Port A, Channel 2, Low */
    DDRA_DDRA2 = OUTPUT;             
    PTA_PTA2 = LOW;    
    
    /** LED502, Port A, Channel 3, Low */
    DDRA_DDRA3 = OUTPUT;             
    PTA_PTA3 = LOW;

    /** Port A, Channel 4, Low */
    DDRA_DDRA4 = OUTPUT;             
    PTA_PTA4 = LOW;

    /** Port A, Channel 5, Low */
    DDRA_DDRA5 = OUTPUT;             
    PTA_PTA5 = LOW;

    /** Port P, Channel 3, High */
    MODRR_MODRR5 = 1;
    MODRR_MODRR6 = 1;
    DDRP_DDRP3 = OUTPUT; 
    //PTP_PTP3  =  HIGH;
    PTRRR_PTRRR3 = 1;   /* Timer output compare 3 is available in PP3 */

    DDRP_DDRP2 = OUTPUT; 
    //PTP_PTP3  =  HIGH;
    PTRRR_PTRRR2 = 1;   /* Timer output compare 2 is available in PP2 */

    /* J2716 outputs */
    PTJ_PTJ6  =STD_HIGH;/*Set the value before configuring as outputs*/
    PTJ_PTJ7  =STD_HIGH;/*in oder to avoid glitches                  */
    DDRJ_DDRJ7=1;    /* PJ7 and PJ6 as outputs */
    DDRJ_DDRJ6=1;

    /************ Analog Inputs Initialization ********************************/
    /* - Configuration of Data Direction Register to Input                    */
    /* - Set Digital Input ENABLED option to 0 (DISABLED)                       */
    /* - DISABLED Pull up/down option                                          */
    /**************************************************************************/
    
    /** Port AD0, Channel 0 */
    DDR1AD0_DDR1AD00 = INPUT;
    ATD0DIEN_IEN0 =  DISABLED;
    PER1AD0_PER1AD00 = DISABLED;
    
    /** Port AD0, Channel 1 */
    DDR1AD0_DDR1AD01 = INPUT;
    ATD0DIEN_IEN1 =  DISABLED;
    PER1AD0_PER1AD01 = DISABLED;
    
    /** Port AD0, Channel 2 */
    DDR1AD0_DDR1AD02 = INPUT;
    ATD0DIEN_IEN2 =  DISABLED;
    PER1AD0_PER1AD02 = DISABLED;
    
    /** Port AD0, Channel 3 */
    DDR1AD0_DDR1AD03 = INPUT;
    ATD0DIEN_IEN3 =  DISABLED;
    PER1AD0_PER1AD03 = DISABLED;
    
    /** Port AD0, Channel 4 */
    DDR1AD0_DDR1AD04 = INPUT;
    ATD0DIEN_IEN4 =  DISABLED;
    PER1AD0_PER1AD04 = DISABLED;
    
    /** Port AD0, Channel 5 */
    DDR1AD0_DDR1AD05 = INPUT;
    ATD0DIEN_IEN5 =  DISABLED;
    PER1AD0_PER1AD05 = DISABLED;
    
    /** Port AD0, Channel 6 */
    DDR1AD0_DDR1AD06 = INPUT;
    ATD0DIEN_IEN6 =  DISABLED;
    PER1AD0_PER1AD06 = DISABLED;
    
    /** Port AD0, Channel 7 */
    DDR1AD0_DDR1AD07 = INPUT;
    ATD0DIEN_IEN7 =  DISABLED;
    PER1AD0_PER1AD07 = DISABLED;
    
    /************ Unused pins Initialization **********************************/
    /* - Configuration of Data Direction Register to Output                   */
    /* - Set pin to specified value                                           */
    /**************************************************************************/
    
    /*********** Unspecided and unbonded pins Initialization ******************/
    /* - Configuration of Data Direction Register to Output                   */
    /* - Set pin to specified value                                           */
    /**************************************************************************/
}
/*******************************************************************************/