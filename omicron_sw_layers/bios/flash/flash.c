/****************************************************************************************************/
/**
\file       hal_flash.c
\brief      Flash routines functions and prototypess
\author     Christian Michel/Abraham Tezmol
\version    1.0.1
\date       08/12/2008
*/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own header */
/* Flash functions and prototypes */
#include    "flash.h"

/*******************************************************************************************************************
* Declaration of module wide FUNCTIONs 
*******************************************************************************************************************/
tCallbackFunction vfnFlash_Callback;

/*******************************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*******************************************************************************************************************/


/*******************************************************************************************************************
* Declaration of module wide TYPEs 
*******************************************************************************************************************/

/*******************************************************************************************************************
* Definition of module wide VARIABLEs 
*******************************************************************************************************************/
UINT16            gu16CommandArray[ 6 ];

/*******************************************************************************************************************
* Definition of module VARIABLEs - can be used by other modules
*******************************************************************************************************************/

/*******************************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*******************************************************************************************************************/

/*******************************************************************************************************************
* Code of module wide FUNCTIONS
*******************************************************************************************************************/

/**************************************************************************************************/
/**
* \brief    u16Flash_Init - Low level initialization of Flash module of microncontroller.
* \author   Christian Michel
* \param    tCallbackFunction - Callback, function to be called to reset watchdog during execution of 
* \param    Flash routines 
* \return   UINT16 - status of initialization process
* \todo     
*/
UINT16 u16Flash_Init( tCallbackFunction  Callback )
{
    UINT8  lu8FlashDivider = 0u;                                /*  < flash clock divider >                       */ 
    UINT8  lu8RegisterValue = 0u;                               /*  < store data read from flash register >       */ 
    UINT16 lu16ClockValue = 0u;                                 /*  < clock in MHz >                              */ 
    UINT16 lu16ReturnCode = 0u;                                 /*  < return code variable >                      */ 

    lu16ReturnCode    = SGF_OK;


       /*Initialize callback function*/
    vfnFlash_Callback = Callback;


    /* clear ACCERR & FPVIOL flag in flash status register */
    REG_WRITE((SSD_MCU_REGISTER_BASE + FLASH_FSTAT_OFFSET), \
              (FLASH_FSTAT_ACCERR | FLASH_FSTAT_FPVIOL))
    ;

    /* clear DFDIF,SFDIF & EPVIOLIF flag in flash error status register */
    REG_WRITE((SSD_MCU_REGISTER_BASE + FLASH_FERSTAT_OFFSET), \
              (FLASH_FERSTAT_DFDIF | FLASH_FERSTAT_SFDIF))
    ;

    /* Set the ignore single bit fault value, so that the single bit faults are ignored */
    REG_BIT_SET((SSD_MCU_REGISTER_BASE + FLASH_FCNFG_OFFSET), \
                     FLASH_FCNFG_IGNSF)
    ;
     /*Get flash clock divider register value */
    lu8RegisterValue = REG_READ(SSD_MCU_REGISTER_BASE + FLASH_FCLKDIV_OFFSET);

    if( FALSE == ( lu8RegisterValue & FLASH_FCLKDIV_FDIVLD ))   /*  clock not set */ 
    {
        /* clock not set */
        /* If S12XS family */

        /* oscillator clock in MHz */
        lu16ClockValue = SSD_OSCILLATOR_CLOCK / 100u;
        /* calculating flash divider value */
        if( ( lu16ClockValue >= 2u ) && ( lu16ClockValue < 21u ) )
        {
            lu8FlashDivider = ( UINT8 )( lu16ClockValue - 1u );
        }
        else  if( ( lu16ClockValue >= 21u ) && ( lu16ClockValue < 42u ) )
        {
            lu8FlashDivider = ( UINT8 )( lu16ClockValue - 2u );
        }
        else  if( ( lu16ClockValue >= 42u ) && ( lu16ClockValue <= 50u ) )
        {
            lu8FlashDivider = ( UINT8 )( lu16ClockValue - 3u );
        }
        else
        {
                /* if oscillator clock is less than or equal to 1MHz or greater than 50MHz,
                   return an invalid clk error code SGF_ERR_INVALIDCLK */
            lu16ReturnCode = SGF_ERR_INVALIDCLK;
        }

        if( SGF_OK == lu16ReturnCode )
        {
              /* write the flashDivider value into the FCLKDIV register */
            REG_WRITE((SSD_MCU_REGISTER_BASE + FLASH_FCLKDIV_OFFSET), \
                      (UINT8)lu8FlashDivider)
            ;
        }
    }
    else
    {
    /* clock set : do nothing */
    }

    return ( lu16ReturnCode );
}

/**************************************************************************************************/
/**
* \brief    u16Flash_IsFlashBusy - Provides global status of microcontroller flash array
* \author   Christian Michel
* \param    void
* \return   UINT16 - status of flash array
* \todo     
*/
UINT16 u16Flash_IsFlashBusy( void  )
{
    UINT16 lu16ReturnCode;

    if( FSTAT_CCIF == 1u )
    {
        lu16ReturnCode = FLASH_READY;
    }
    else
    {
        lu16ReturnCode = FLASH_BUSY;
    }
    return lu16ReturnCode;
}

/******************************************************************************************************************/

UINT16 u16Flash_PFlashProgram( UINT32  u32Dest, UINT32  u32Size, UINT32  u32Source )
{
    UINT8  lu8Counter = 0u;                                     /*  < outer loop counter >                        */ 
    UINT8  lu8LoopIndex = 0u;                                   /*  < inner loop index >                          */ 
    UINT16 lu16TempValue = 0u;
    UINT16 lu16CommandValue = 0u;                               /*  < store command value >                       */ 
    UINT16 lu16GlobalAddress = 0u;                              /*  < store global address bits >                 */ 
    UINT16 lu16ReturnCode = 0u;                                 /*  < return code variable >                      */ 
    UINT32 lu32EndAddress = 0u;                                 /*  < end address for the program operation >     */ 

    lu16ReturnCode = SGF_OK;

    /* check the size alignment */
    if( 0u != u32Size % HCS12X_WORD_SIZE )
    {
        lu16ReturnCode = SGF_ERR_SIZE;
    }
    else
    {
        /* calculate end address */
        lu32EndAddress = u32Dest + u32Size;

        /* check the range of the address */
        if( lu32EndAddress > ( UINT32 )PFLASH_BLOCK_END_ADDR )
        {
            lu16ReturnCode = SGF_ERR_RANGE;
        }
        else
        {
            lu16CommandValue = ( ( ( UINT16 )( PFLASH_PROGRAM ) )<<8u );

            while( u32Dest < lu32EndAddress )
            {
                /* preparing passing parameter for program once command */
                lu16GlobalAddress = ( UINT16 )( ( u32Dest & GLOBAL_ADDRESS_MASK )>>16u );
                /* 1st element for the FCCOB register */
                gu16CommandArray[ 0 ] = ( lu16CommandValue | lu16GlobalAddress );
                /* 2nd element fot the FCCOB register */
                gu16CommandArray[ 1 ] = ( UINT16 )( u32Dest & ADDRESS_OFFSET_MASK );
                if( u32Size > FLASH_PHRASE_SIZE )
                {
                    lu8LoopIndex = COMMAND_INDEX4;
                }
                else
                {
                    lu8LoopIndex = ( UINT8 )( u32Size / HCS12X_WORD_SIZE );
                }

                /* preparing rest of the parameters for FCCOB register */
                for( lu8Counter
                     = 0u; 
                     lu8Counter < lu8LoopIndex;
                     lu8Counter++ )
                {
                    lu16TempValue = *(UINT16 * __far)u32Source;
                    gu16CommandArray[ lu8Counter + 2u ] = lu16TempValue;
                    u32Dest += HCS12X_WORD_SIZE;
                    u32Source += HCS12X_WORD_SIZE;
                    u32Size -= HCS12X_WORD_SIZE;
                }

                /* Fill the rest of the unused bytes with 0xFF's */

                for( lu8Counter = lu8LoopIndex;
                     lu8Counter < COMMAND_INDEX4; lu8Counter++ )
                {
                    lu16TempValue = 0xFFFFu;
                    gu16CommandArray[ lu8Counter + 2u ] = lu16TempValue;
                    u32Dest += HCS12X_WORD_SIZE;
                    u32Source += HCS12X_WORD_SIZE;
                    u32Size -= HCS12X_WORD_SIZE;
                }

                /* calling flash command sequence to execute the command */
                lu16ReturnCode = u16Flash_CommandSequence( COMMAND_INDEX5 );

                /* checking for the success of command execution */
                if( SGF_OK != lu16ReturnCode )
                {
                    break;
                }
            }
        }
    }

    return ( lu16ReturnCode );
}
/******************************************************************************************************************/

UINT16 u16Flash_PFlashEraseSector( UINT32  u32Destination )
{
    UINT16 lu16CommandValue;                                    /*  < store command value >                       */ 
    UINT16 lu16GlobalAddress;                                   /*  < store global address bits >                 */ 
    UINT16 lu16ReturnCode;                                      /*  < return code variable >                      */ 

    lu16ReturnCode = SGF_OK;

    /* address has to be phrase aligned! */
    /* range checking */
    if( ( u32Destination < PFLASH_BLOCK_START_ADDR )
         || ( u32Destination >= PFLASH_BLOCK_END_ADDR ) )

    {
        lu16ReturnCode = SGF_ERR_RANGE;
    }
    else
    {
        lu16CommandValue = ( ( ( UINT16 )( PFLASH_ERASE_SECTOR ) )<<8u );

        /* preparing passing parameter for 256 Bytes sector erase */
        lu16GlobalAddress = ( UINT16 )( ( u32Destination & GLOBAL_ADDRESS_MASK )>>16u );
        gu16CommandArray[ 0 ] = ( lu16CommandValue | lu16GlobalAddress );
        gu16CommandArray[ 1 ] = ( UINT16 )( u32Destination & ADDRESS_OFFSET_MASK );

        /* calling flash command sequence function to execute the command */
        lu16ReturnCode = u16Flash_CommandSequence( COMMAND_INDEX1 );

    }
    return ( lu16ReturnCode );
}

/******************************************************************************************************************/

UINT16 u16Flash_Erase_PFlash_blocks( void  )
{
    UINT32 lu32Address;
    UINT16 lu16ReturnCode = 0;
    for( lu32Address
           = PFLASH_BLOCK_START_ADDR;
           lu32Address
            < PFLASH_BLOCK_END_ADDR;
           lu32Address += 0x400u )
    {
        lu16ReturnCode += u16Flash_PFlashEraseSector( lu32Address );

        /*call callback function, if initialized*/
        if( vfnFlash_Callback != NULL )
        {
            vfnFlash_Callback( );
        }
    }
    return ( lu16ReturnCode );
}


/**************************************************************************************************/
/**
* \brief    u16Flash_FullDFlash_Partition - Erases and then creates Data flash partitions for emulated EEPROM 
* \author   Abraham Tezmol
* \param    UINT8 u8DataFlashPartitions - Number of Data flash partitions for non-emulated EEPROM purposes, maximum 16
* \param    UINT8 u8EEPROMPartitions - Number of Data flash partitions for emulated EEPROM purposes, maximum 16
* \return   UINT16 - status of flash command
* \todo     
*/
UINT16 u16Flash_FullDFlash_Partition( UINT8  u8DataFlashPartitions, UINT8  u8EEPROMPartitions )
{
    UINT16 lu16ReturnCode;
    UINT16 lu16CommandValue;


    lu16CommandValue = ( ( ( UINT16 )( DFLASH_FULL_PARTITION ) )<<8u );

       /* Prepare Data flash command */
    gu16CommandArray[ 0 ] = lu16CommandValue;
    gu16CommandArray[ 1 ] = ( UINT16 )u8DataFlashPartitions;
    gu16CommandArray[ 2 ] = ( UINT16 )u8EEPROMPartitions;

       /* calling flash command sequence function to execute the command */
    lu16ReturnCode = u16Flash_CommandSequence( COMMAND_INDEX2 );

    return ( lu16ReturnCode );
}

/**************************************************************************************************/
/**
* \brief    u16Flash_DFlash_Partition - Creates Data flash partitions for emulated EEPROM 
* \author   Abraham Tezmol
* \param    UINT8 u8DataFlashPartitions - Number of Data flash partitions for non-emulated EEPROM purposes, maximum 16
* \param    UINT8 u8EEPROMPartitions - Number of Data flash partitions for emulated EEPROM purposes, maximum 16
* \return   UINT16 - status of flash command
* \todo     
*/
UINT16 u16Flash_DFlash_Partition( UINT8  u8DataFlashPartitions, UINT8  u8EEPROMPartitions )
{
    UINT16 lu16ReturnCode;
    UINT16 lu16CommandValue;


    lu16CommandValue = ( ( ( UINT16 )( DFLASH_PARTITION ) )<<8u );

       /* Prepare Data flash command */
    gu16CommandArray[ 0 ] = lu16CommandValue;
    gu16CommandArray[ 1 ] = ( UINT16 )u8DataFlashPartitions;
    gu16CommandArray[ 2 ] = ( UINT16 )u8EEPROMPartitions;

       /* calling flash command sequence function to execute the command */
    lu16ReturnCode = u16Flash_CommandSequence( COMMAND_INDEX2 );

    return ( lu16ReturnCode );
}

/**************************************************************************************************/
/**
* \brief    u16Flash_EEEPROM_Enable - Enables Emulation of EEPROM using Data flash
* \author   Abraham Tezmol
* \param    void
* \return   UINT16 - status of flash command
* \todo     
*/
UINT16 u16Flash_EEEPROM_Enable( void  )
{
    UINT16 lu16ReturnCode;
    UINT16 lu16CommandValue;


    lu16CommandValue = ( ( ( UINT16 )( DFLASH_ENABLE_EEPROM_EMUL ) )<<8u );

       /* Prepare Data flash command */
    gu16CommandArray[ 0 ] = lu16CommandValue;

       /* calling flash command sequence function to execute the command */
    lu16ReturnCode = u16Flash_CommandSequence( COMMAND_INDEX0 );

    return ( lu16ReturnCode );
}

/**************************************************************************************************/
/**
* \brief    u16Flash_EEEPROM_Disable - Enables Emulation of EEPROM using Data flash
* \author   Abraham Tezmol
* \param    void
* \return   UINT16 - status of flash command
* \todo     
*/
UINT16 u16Flash_EEEPROM_Disable( void  )
{
    UINT16 lu16ReturnCode;
    UINT16 lu16CommandValue;


    lu16CommandValue = ( ( ( UINT16 )( DFLASH_DISABLE_EEPROM_EMUL ) )<<8u );

       /* Prepare Data flash command */
    gu16CommandArray[ 0 ] = lu16CommandValue;

       /* calling flash command sequence function to execute the command */
    lu16ReturnCode = u16Flash_CommandSequence( COMMAND_INDEX0 );

    return ( lu16ReturnCode );
}


/****************************************************************************************************/

#pragma CODE_SEG RAM_ROUTINES
UINT16 u16Flash_CommandSequence( UINT8  u8Index )
{
    UINT8  lu8Counter = 0u;                                     /*  < for loop counter variable >                 */ 
    UINT8  lu8RegisterValue = 0u;                               /*  < store data read from flash register >       */ 
    UINT16 lu16ReturnCode = 0u;                                 /*  < return code variable >                      */ 

    lu16ReturnCode = SGF_OK;


    /* check CCIF bit */
    while(FALSE == (REG_BIT_TEST((SSD_MCU_REGISTER_BASE + \
                   FLASH_FSTAT_OFFSET), FLASH_FSTAT_CCIF)
    ))
    {
    /* wait till CCIF bit is set */
    }

    /* clear ACCERR and FPVIOL bits */
    REG_WRITE((SSD_MCU_REGISTER_BASE + FLASH_FSTAT_OFFSET), \
              (FLASH_FSTAT_ACCERR|FLASH_FSTAT_FPVIOL))
    ;

    /* load FCCOBIX & FCCOB register */
    for( lu8Counter = 0u; 
           lu8Counter <= u8Index; 
           lu8Counter++ )
    {
        REG_WRITE(SSD_MCU_REGISTER_BASE + FLASH_FCCOBIX_OFFSET, lu8Counter);
        REG_WRITE16(SSD_MCU_REGISTER_BASE + FLASH_FCCOB_OFFSET, \
                    gu16CommandArray[lu8Counter])
        ;
    }

    /* clear CCIF bit */
    REG_WRITE(SSD_MCU_REGISTER_BASE + FLASH_FSTAT_OFFSET, FLASH_FSTAT_CCIF);

    /* check CCIF bit */
    while(FALSE == (REG_BIT_TEST((SSD_MCU_REGISTER_BASE + \
                   FLASH_FSTAT_OFFSET), FLASH_FSTAT_CCIF)
    ))
    {
    /* wait till CCIF bit is set */

    }

     /* Check error bits */
    /*Get flash status register value */
    lu8RegisterValue = REG_READ(SSD_MCU_REGISTER_BASE + FLASH_FSTAT_OFFSET);

    /* checking access error */
    if( ( lu8RegisterValue & FLASH_FSTAT_ACCERR ) != 0u )
    {
        lu16ReturnCode = SGF_ERR_ACCERR;
    }                                                           /*  checking protection error                     */ 
    else  if( 0u != ( lu8RegisterValue & FLASH_FSTAT_FPVIOL ) )
    {
        lu16ReturnCode = SGF_ERR_PVIOL;
    }                                                           /*    checking MGSTAT1 error                      */ 
    else  if( 0u != ( lu8RegisterValue & FLASH_FSTAT_MGSTAT1 ) )
    {
        lu16ReturnCode = SGF_ERR_MGSTAT1;
    }                                                           /*      checking MGSTAT0 non-correctable error    */ 
    else  if( 0u != ( lu8RegisterValue & FLASH_FSTAT_MGSTAT0 ) )
    {
        lu16ReturnCode = SGF_ERR_MGSTAT0;
    }
    else
    {
                /* do nothing*/
    }

    return ( lu16ReturnCode );
}
#pragma CODE_SEG DEFAULT