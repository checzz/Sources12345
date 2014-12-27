/*******************************************************************************/
/**
\file       cam_crank.c
\brief      CAM CRANK signal generation functions and prototypes
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Configuration Options */
  #include "configuration.h"
/** MCU derivative information */
  #include __MCU_DERIVATIVE
/** Variable types and common definitions */
  #include "typedefs.h"

/** Own headers */
/* Cam Crank routines prototypes */ 
#include    "cam_crank.h"
/** Emulated EEPROM functions and definitions */
#include    "emul_eeprom.h"

/** Used modules */
/** XGATE definitions */
  #include    "xgate_config.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
tCamCrankChDescr* ptCamCrankChDescr_Duty_ptr;

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Cam Crank function - Initialization
* \author   Abraham Tezmol
* \param    void
* \return   UINT8 - operation status
* \todo     
*/
void vfnCamCrank_Init( void )
{	
    UINT16 lu16command_status;
    
    /* Initialize CAM Crank calibratable parameters out of EEEPROM */
    lu16command_status = u16emul_eeprom_read( (UINT32)&sNVM_Data.cam_crank_channels[0], 
                                sizeof(sNVM_Data)-2-ENGINE_ANGLE_DEGREES, (tu8ptr_far)&cam_crank_channels[0] );
    lu16command_status = u16emul_eeprom_read( (UINT32)&sNVM_Data.u8CrankConfig[0], 
                                ENGINE_ANGLE_DEGREES, (tu8ptr_far)&u8CrankConfig[0] );                              
    /* Command SW trigger 1 to execute --> XGATE to initialize appropriate signal mechanism */
	  XGATE_SW_TRIGGER( SOFTWARE_TRIGGER_1, SOFTWARE_TRIGGER_ENABLE);
}

/****************************************************************************************************/
/**
* \brief    Cam Crank function - Start
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnCamCrank_Start( void )
{
    /* Perform Low level PIT start */
    /*vfnPIT1_Start();*/

}

/****************************************************************************************************/