/****************************************************************************************************/
/**
\file       cnf_mem_alloc.c
\brief      Configuration of Dynamic Memory Allocation services
\author     Abraham Tezmol
\version    1.0
\date       21/09/2013
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Dynamic Memory allocation configuration definitions */
#include    "cnf_mem_alloc.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Dynamic memory allocation configuration for NEAR memory */
const tNearRAMpages_config NearRamPages_config[] =
{
    {RAM_FF, (tu8ptr_near)0x3400, (tu8ptr_near)0x3BFF}
};


const tNearMemAlloc_config  NearMemAlloc_config[] =
{
    {
        sizeof(NearRamPages_config)/sizeof(NearRamPages_config[0]),         /* number of configured RAM pages */
        &NearRamPages_config[0]                                             /* RAM pages configuration structure */
    }
};

/* Dynamic memory allocation configuration for FAR memory */
const tPagedRAMpages_config PagedRamPagesFar_config[] =
{
    {RAM_F2, (tu8ptr_far)0xF21000, (tu8ptr_far)0xF21FFF},
    {RAM_F3, (tu8ptr_far)0xF31000, (tu8ptr_far)0xF31FFF}
};


const tMemAlloc_config  DynamicMemAlloc_config[] =
{
    {
        sizeof(PagedRamPagesFar_config)/sizeof(PagedRamPagesFar_config[0]), /* number of configured RAM pages */
        &PagedRamPagesFar_config[0]                                         /* RAM pages configuration structure */
    }
};
/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/


/*****************************************************************************************************
* Code of public FUNCTIONS
*****************************************************************************************************/


/***************************************************************************************************/
