/****************************************************************************************************/
/**
\author     Christian Michel
\version    1.0.1
\date       08/12/2008
*/

#ifndef __FLASH_REGISTERS_H_
#define    __FLASH_REGISTERS_H_    

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/*--------------- HCS12X Flash Module Memory Offset Map -----------------*/
/* Flash module base offset */
#define    FLASH_REG_BASE              0x0100

/* Flash clock divider register */
#define    FLASH_FCLKDIV_OFFSET        ( FLASH_REG_BASE + 0x0000 )
#define    FLASH_FCLKDIV_FDIVLD        0x80
/* For S12P part */

/* Flash CCOB index register */
#define    FLASH_FCCOBIX_OFFSET        ( FLASH_REG_BASE + 0x0002 )

/* Flash ECCR index register */
#define    FLASH_FECCRIX_OFFSET        ( FLASH_REG_BASE + 0x0003 )

/* Flash configuration register */
#define    FLASH_FCNFG_OFFSET          ( FLASH_REG_BASE + 0x0004 )
#define    FLASH_FCNFG_CCIE            0x80
#define    FLASH_FCNFG_IGNSF           0x10
#define    FLASH_FCNFG_FDFD            0x02
#define    FLASH_FCNFG_FSFD            0x01

/* Flash error configuration register */
#define    FLASH_FERCNFG_OFFSET        ( FLASH_REG_BASE + 0x0005 )
#define    FLASH_FERCNFG_DFDIE         0x02
#define    FLASH_FERCNFG_SFDIE         0x01

/* Flash status register */
#define    FLASH_FSTAT_OFFSET          ( FLASH_REG_BASE + 0x0006 )
#define    FLASH_FSTAT_CCIF            0x80
#define    FLASH_FSTAT_ACCERR          0x20
#define    FLASH_FSTAT_FPVIOL          0x10
#define    FLASH_FSTAT_MGSTAT1         0x02
#define    FLASH_FSTAT_MGSTAT0         0x01

/* Flash error status register */
#define    FLASH_FERSTAT_OFFSET        ( FLASH_REG_BASE + 0x0007 )
#define    FLASH_FERSTAT_DFDIF         0x02
#define    FLASH_FERSTAT_SFDIF         0x01

/* Flash common command object register */
#define    FLASH_FCCOB_OFFSET          ( FLASH_REG_BASE + 0x000A )

/* Flash common command object high register */
#define    FLASH_FCCOBHI_OFFSET        ( FLASH_REG_BASE + 0x000A )

/* Flash common command object low register */
#define    FLASH_FCCOBLO_OFFSET        ( FLASH_REG_BASE + 0x000B )


/* Flash margin read settings */
#define    FLASH_MARGIN_NORMAL         0x0000
#define    FLASH_USER_MARGIN_LEVEL1    0x0001
#define    FLASH_USER_MARGIN_LEVEL0    0x0002

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

#endif  /* __FLASH_REGISTERS_H_ */ 