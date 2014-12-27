/****************************************************************************************************/
/**
  \mainpage
  \n 
  \brief        Main application (main module)
  \author       Abraham Tezmol Otero, M.S.E.E
  \project      Omicron 
  \version      1.0
  \date         26/Jun/2009
   
  Program compiled with CW for HCS12(X) v5.0, tested on DEMO9S12XEP100 board
*/
/****************************************************************************************************/

/** Main application common definitions */
#include    "main.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of global wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/
#define  APP_UPDATE_RQ  (0xAA)
/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/******************************************************************************************************
* Definition of module wide VARIABLEs 
******************************************************************************************************/
UINT8 u8Temp;
UINT16 u16MemStatus;
/******************************************************************************************************
* Code of module wide FUNCTIONS
******************************************************************************************************/

void vfnBackgroundSubsystemTasks(void);

/*~~~~~~~ Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void main(void) 
{      
    /* Disable interrupts */
    INTERRUPT_DISABLE(); 
    /* XGATE initialization */
    vfn_XGATE_CPU_init();
    /* Initialize Interrupt Module */
    vfnInterrupt_Init(ASW_WITH_BOOT);          
    /* PLL initialization to the desired target frequency */
    vfnPLL_Init();
    /* Dynamic Memory Allocation initialization */
    vfnMemAlloc_NearInit(&NearMemAlloc_config[0]);
    vfnMemAlloc_Init(&DynamicMemAlloc_config[0]);
    /* Microcontroller Input/Output pins initialization */
    vfnInputs_Outputs_Init();
    /* Initialize Serial Communications */
    vfnCommProtocol_Init();
    /* Emulated EEPROM initialization */
    u16MemStatus = u16emul_eeprom_init(&vfnCOPWatchdog_Reset,&EEEPROM_config[0]);
    /* Initialize CAM/Crank emulation */
    /*vfnCamCrank_Init();*/
    /* Initialize Task Scheduler */ 
    vfnScheduler_Init();
     /* Arm COP watchdog */
    vfnCOPWatchdog_Init();
    /* Start execution of task scheduler */
    vfnScheduler_Start();
    /* Once all initializations are complete, enable interrupts */
    INTERRUPT_ENABLE();     
    /* Start CAM/Crank emulation */
    /*vfnCamCrank_Start();*/
    /* Start J2716 emulation */
    J2716_Init(&J2716_astDevicesCfg[0]);
    /* Start ADC */
    ADC_vInit();
    /*-- Loop through all the periodic tasks from Task Scheduler --*/
    for(;;)
    {
        /* Perform all scheduled tasks */
        vfnTask_Scheduler();
        /* Perform all background susbystem control tasks */
        vfnBackgroundSubsystemTasks();
                   
    }
}
/*~~~~~~~ End of Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Background tasks related to Subsystem control */
void vfnBackgroundSubsystemTasks(void) 
{;}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/