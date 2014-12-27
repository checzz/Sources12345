/****************************************************************************************************/
/**
\file       typedefs.h
\brief      Variable types and common macros
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

#ifndef TYPEDEFS_H        /*prevent duplicated includes*/ 
#define    TYPEDEFS_H    

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Std_Types.h"
/*****************************************************************************************************
* Declaration of project wide TYPES
*****************************************************************************************************/

typedef            unsigned         char
                                         UINT8; /*unsigned 8 bit definition */ 
typedef            unsigned  short       UINT16; /*unsigned 16 bit definition*/ 
typedef            unsigned  long        UINT32; /*unsigned 32 bit definition*/ 
typedef            signed           char
                                         INT8; /*signed 8 bit definition */ 
typedef                      short       INT16; /*signed 16 bit definition*/ 
typedef                      long   int
                                         INT32; /*signed 32 bit definition*/                                          

typedef  volatile  unsigned         char
                                         VUINT8; /*unsigned 8 bit definition */ 
typedef  volatile  unsigned  short       VUINT16; /*unsigned 16 bit definition*/ 
typedef  volatile  unsigned  long        VUINT32; /*unsigned 32 bit definition*/ 
typedef  volatile  signed           char
                                         VINT8; /*signed 8 bit definition */ 
typedef  volatile  short       VINT16;       /*signed 16 bit definition*/ 
typedef  volatile  long   int  VINT32;       /*signed 32 bit definition*/ 


typedef  unsigned    char CHAR; /*unsigned 8 bit definition for S-Record support */ 

/*type used for callback function*/
	typedef  void  ( * tCallbackFunction )( void  );
	typedef  void  ( * tPtr_to_function  )( void  );


/* Data type for Subsystems identification, useful for services configuration */
typedef enum
{
    BOOT,
    ASW_WITH_BOOT,
    ASW_WO_BOOT
}tSubsystemType;
	
/* Data type definitions for near memory */
typedef UINT8 * tu8ptr_near;

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/* Common Constants */
#ifndef ON
	#define    ON     1u
#endif

#ifndef OFF
	#define    OFF    0u
#endif

#ifndef TRUE
	#define    TRUE    1u
#endif

#ifndef FALSE
	#define    FALSE    0u
#endif

#ifndef PASS
	#define    PASS    0u
#endif

#ifndef FAIL
	#define    FAIL    1u
#endif

#ifndef SET
	#define    SET    1u
#endif

#ifndef CLEAR
	#define    CLEAR    0u
#endif

#ifndef YES
	#define    YES    1u
#endif

#ifndef NO
	#define    NO     0u
#endif

#ifndef DISABLED
	#define 	 DISABLED  0u
#endif

#ifndef ENABLE
	#define 	 ENABLE 1u
#endif

#ifndef NULL
  #define    NULL    ( ( void * ) 0 )
#endif


/*-- Macros ------------------------------------------------------------------*/

#define    XIRQ_ENABLE( )                                                                                                                 \
                {                                                                                                                         \
                              asm andcc #0xBF;                                                                                            \
                }                                /*XIRQ enabled              */ 
#define    WAIT( )    { asm wait ; }             /*enter wait mode           */ 
#define    STOP_ENABLE( )                                                                                                                 \
                {                                                                                                                         \
                              asm andcc #0x7F;                                                                                            \
                }                                /*stop mode enabled         */ 
#define    STOP( )    { asm stop ; }             /*enter stop mode           */ 
#define    NOP( )     { asm nop ; }              /*enter NOP asm instruction */ 

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

#endif                                     /* TYPEDEFS_H */ 