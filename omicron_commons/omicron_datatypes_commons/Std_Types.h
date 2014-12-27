/****************************************************************************************************/
/**
\file       Std_Types.h
\brief      Standard type following AUTOSAR 4.2
\author     Marco Lopez
\version    1.0
\date       20/11/2014
*/
/****************************************************************************************************/
#ifndef STD_TYPES_H /*prevent duplicated includes*/
#define STD_TYPES_H
/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of project wide TYPES
*****************************************************************************************************/

typedef unsigned         char uint8;  /*unsigned 8 bit definition */ 
typedef unsigned  short       uint16; /*unsigned 16 bit definition*/ 
typedef unsigned  long        uint32; /*unsigned 32 bit definition*/ 
typedef   signed         char int8;   /*signed 8 bit definition */ 
typedef           short       int16;  /*signed 16 bit definition*/ 
typedef            long  int  in32;   /*signed 32 bit definition*/

/*[SWS_Std_00005]*/
typedef uint8 Std_ReturnType;

/*[SWS_Std_00015]*/
typedef struct _tag_Std_VersionInfoType
{
  uint16 vendorID;
  uint16 moduleID;
  uint8 sw_major_version;
  uint8 sw_minor_version;
  uint8 sw_patch_version;
}Std_VersionInfoType;

/*[SWS_Std_00006]*/
#ifndef STATUSTYPEDEFINED 
  #define STATUSTYPEDEFINED 
  #define E_OK      (0x00u)
  typedef unsigned char StatusType; /* OSEK compliance */
#endif
#define E_NOT_OK    (0x01u)

/*[SWS_Std_00007]*/
#define STD_HIGH    (0x01u) /* Physical state 5V or 3.3V */
#define STD_LOW     (0x00u) /* Physical state 0V */

/*[SWS_Std_00013]*/
#define STD_ACTIVE  (0x01u) /* Logical state active */
#define STD_IDLE    (0x00u) /* Logical state idle */

/*[SWS_Std_00010]*/
#define STD_ON      (0x01u)
#define STD_OFF     (0x00u)

#endif /* STD_TYPES_H */