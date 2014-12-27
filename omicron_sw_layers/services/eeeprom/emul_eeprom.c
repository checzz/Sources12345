/****************************************************************************************************/
/**
\file       emul_eeprom.c
\brief      Emulated EEPROM functions and services.
\author     Abraham Tezmol
\version    1.0
\date       08/12/2008
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include    "emul_eeprom.h"

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
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

tCallbackFunction WdgtCallbackFunction;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/****************************************************************************************************
* \brief    u16emul_eeprom_init - Initialization of MCU flash array for emulated eeprom functionality
* \author   Abraham Tezmol
* \param    tCallbackFunction - Callback, function to be called to reset watchdog during execution of 
* \param    Flash routines 
* \param    tEmulEEPROM_config - EmulEEPROM_cfg, EEEPROM configuration
* \return   UINT16 - status of initialization process
*/
UINT16 u16emul_eeprom_init( tCallbackFunction  Callback, const tEmulEEPROM_config * EmulEEPROM_cfg )
{
    static UINT16 lu16ReturnCode_init;
    static UINT16 lu16DataFlashReserved;

    lu16ReturnCode_init = ERR_OK;
    WdgtCallbackFunction = Callback;

      /* Initialize Flash Module */
    lu16ReturnCode_init = u16Flash_Init( WdgtCallbackFunction );
    
    lu16ReturnCode_init = u16emul_eeprom_read( 
                                        (UINT32)EmulEEPROM_cfg->ptrNVM_ValidPattern, 
                                        sizeof(EmulEEPROM_cfg->NVM_ValidPattern), 
                                        (tu8ptr_far)&lu16DataFlashReserved );

    if( lu16DataFlashReserved == EmulEEPROM_cfg->NVM_ValidPattern )
    {
        /* enable emulation of EEPROM in hardware */
        lu16ReturnCode_init = u16Flash_EEEPROM_Enable( );
    }
    else
    {
        if ( (EmulEEPROM_cfg->Subsystem == ASW_WO_BOOT)||(EmulEEPROM_cfg->Subsystem == BOOT) )
        {            
            /* Configure Data flash to support emulated EEPROM */
            lu16ReturnCode_init = u16Flash_FullDFlash_Partition( DFPART, ERPART );
        }       
        /* Once data flash has been partitioned, enable emulation of EEPROM in hardware */
        lu16ReturnCode_init = u16Flash_EEEPROM_Enable( );
        /* Initialize EEEPROM RAM sector with default data */
        lu16ReturnCode_init = u16emul_eeprom_write( (UINT32)EmulEEPROM_cfg->NVM_RAM_start,
                                                    EmulEEPROM_cfg->NVM_ROM_Default, 
                                                    EmulEEPROM_cfg->u16NVM_Default_size ); 
    }
    /* Verify status of EEEPROM memory controller */
    do
    {
        lu16ReturnCode_init = u16emul_eeprom_status( );
        WdgtCallbackFunction();
    }
    while (EMUL_EEPROM_STAT_OK != u16emul_eeprom_status() );

    return ( lu16ReturnCode_init );
}

/****************************************************************************************************
* \brief    u16emul_eeprom_read - Read array of data from emulated eeprom partition
* \author   Abraham Tezmol
* \param    UINT32  u32AddressToRead
* \param    UINT16  u16Size
* \param    UINT8 * pu8DestPtr
* \return   UINT16 - status of reading process
*/
UINT16 u16emul_eeprom_read( UINT32  u32AddressToRead, UINT16  u16Size, tu8ptr_far pu8DestPtr )
{
    UINT16 lu16ReturnCode;
    UINT16 lu16Index;


    lu16ReturnCode = ERR_OK;

    /* Verify status of EEEPROM memory controller */
    do
    {
        lu16ReturnCode = u16emul_eeprom_status( );
        WdgtCallbackFunction();
    }
    while (EMUL_EEPROM_STAT_OK != u16emul_eeprom_status() );
    
    /* Perform readout process */
    for( lu16Index = 0u; 
         lu16Index < u16Size; 
         lu16Index++ )
    {
        *pu8DestPtr++ = *( ( UINT8 * )u32AddressToRead++ );
    }
    return ( lu16ReturnCode );
}

/****************************************************************************************************
* \brief    u16emul_eeprom_read - Read array of data from emulated eeprom partition
* \author   Abraham Tezmol
* \param    UINT32  u32AddressToWrite
* \param    tu8ptr_far pu8SrcPtr
* \param    UINT8   u8DataSize
* \return   UINT16  - status of writing process
*/
UINT16 u16emul_eeprom_write( UINT32 u32AddressToWrite, tu8ptr_far pu8SrcPtr, UINT16  u16DataSize )
{
    UINT16   lu16ReturnCode;
    UINT16   lu16Index;

    lu16ReturnCode     = ERR_OK;

    
    /* Verify status of EEEPROM memory controller */
    do
    {
        lu16ReturnCode = u16emul_eeprom_status( );
        WdgtCallbackFunction();
    }
    while (EMUL_EEPROM_STAT_OK != u16emul_eeprom_status() );
        
    /* Perform write operation */
    for( lu16Index = 0u; 
         lu16Index < u16DataSize;
         lu16Index++ )
    {
        *( ( UINT8 * )u32AddressToWrite++ ) = *pu8SrcPtr++;
    }
    
    return ( lu16ReturnCode );
}

/****************************************************************************************************
* \brief    u16emul_eeprom_status - Provides indication of activity of EEEPROM memory controller activity
* \author   Abraham Tezmol
* \param    void
* \return   UINT16  - status of memory controller activity
*/
UINT16 u16emul_eeprom_status( void  )
{
    UINT16 lu16ReturnCode;

    if( ( ETAG > 0u ) || ( FSTAT_MGBUSY == 1u ) )
    {
        lu16ReturnCode = EMUL_EEPROM_STAT_BUSY;
    }
    else
    {
        lu16ReturnCode = EMUL_EEPROM_STAT_OK;
    }
    return lu16ReturnCode;

}

/****************************************************************************************************/