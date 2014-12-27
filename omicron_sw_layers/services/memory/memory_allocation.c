/****************************************************************************************************/
/**
\file       memory_allocation.c
\brief      Dynamic Memory allocation services.
\author     Abraham Tezmol
\version    1.0
\date       21/09/2013
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Dynamic Memory allocation services */
#include    "memory_allocation.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Near Mem alloc status variables */
const tNearMemAlloc_config * mem_alloc_nearcnf;

tNearMemAlloc_status    NearMemAlloc_Status;

tNearRAMpages_status NearRamPages_status[MEM_ALLOC_MAX_NEAT_RAM_PAGES] = 
{
    {RAM_NULL, (tu8ptr_near)NULL,(tu8ptr_near)NULL, 0}
};

/* FAR Mem alloc status variables */
const tMemAlloc_config * mem_alloc_farcnf;
tMemAlloc_status    MemAlloc_Status;

tPagedRAMpages_status PagedRamPagesFar_status[MEM_ALLOC_MAX_FAR_RAM_PAGES] = 
{
    {RAM_NULL, (tu8ptr_far)NULL,(tu8ptr_far)NULL, 0},
    {RAM_NULL, (tu8ptr_far)NULL,(tu8ptr_far)NULL, 0}
};
/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/

/*****************************************************************************************************
* Code of public FUNCTIONS - NEAR ALLOCAATION
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    memory allocation - Initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnMemAlloc_NearInit( const tNearMemAlloc_config * mem_alloc_config  )
{
    UINT8 u8pageIndex;
    tu8ptr_near StartAddress;
    tu8ptr_near EndAddress;
    
    /* Store pointer to driver configuration */
    mem_alloc_nearcnf = mem_alloc_config;
    
    NearMemAlloc_Status.RamPageStatus = &NearRamPages_status[0];
    
    if (mem_alloc_nearcnf->u8Number_of_RAM_pages != 0)
    {
        for (u8pageIndex = 0; u8pageIndex < mem_alloc_nearcnf->u8Number_of_RAM_pages; u8pageIndex++ )
        {
            /* Obtain Start and End Addresses */
            StartAddress =   mem_alloc_nearcnf->ptr_NearRAMpages_config[u8pageIndex].ptr_nearStartAddress;
            EndAddress = mem_alloc_nearcnf->ptr_NearRAMpages_config[u8pageIndex].ptr_nearEndAddress;
            /* Update all relevant entries in status structure */ 
            NearMemAlloc_Status.RamPageStatus[u8pageIndex].RamPageId = mem_alloc_nearcnf->ptr_NearRAMpages_config[u8pageIndex].RamPageId;
            NearMemAlloc_Status.RamPageStatus[u8pageIndex].ptr_nearCurrentAddress = StartAddress;
            NearMemAlloc_Status.RamPageStatus[u8pageIndex].ptr_nearEndAddress = EndAddress;
            NearMemAlloc_Status.RamPageStatus[u8pageIndex].u16_FreeBytes = (UINT16)(EndAddress - StartAddress + 1);
            /* Updated internal variable that keeps track of available pages */
            NearMemAlloc_Status.u8NumberOfPages++;
            
            /* Erase RAM in order to assure all entries are ready to be used */
            vfnMemAlloc_NearErase(StartAddress, NearMemAlloc_Status.RamPageStatus[u8pageIndex].u16_FreeBytes);
        }
    }
}

/****************************************************************************************************/
/**
* \brief    memory allocation - reserve a buffer and return its address
* \author   Abraham Tezmol
* \param    UINT16  u16SizeinBytes
* \return   tu8ptr_near pointer to start of allocated space
* \todo     
*/
tu8ptr_near MemAlloc_NearReserve( UINT16  u16SizeinBytes)
{
    UINT8 u8pageIndex;
    tu8ptr_near prtAllocatedBuffer = (tu8ptr_near)NULL;
    static tu8ptr_near nearStartAddress;
    static tu8ptr_near nearEndAddress;
    
    for (u8pageIndex = 0; u8pageIndex < NearMemAlloc_Status.u8NumberOfPages; u8pageIndex++ )
    {
        /* Get start and end address parameters for this RAM page */ 
        nearStartAddress = NearMemAlloc_Status.RamPageStatus[u8pageIndex].ptr_nearCurrentAddress;
        nearEndAddress = NearMemAlloc_Status.RamPageStatus[u8pageIndex].ptr_nearEndAddress;
        /* Apply alginment */
        nearStartAddress = (tu8ptr_near)(((UINT16)(nearStartAddress)+3) & (UINT16)MEM_ALLOC_4_BYTE_ALIGN);
        /* Verify if enough memory is free */
        if( (UINT16)(nearEndAddress - nearStartAddress + 1) >= u16SizeinBytes )
        {
            /* Enough memory is available, reserve it and return its start address */
            prtAllocatedBuffer = nearStartAddress;
            NearMemAlloc_Status.RamPageStatus[u8pageIndex].ptr_nearCurrentAddress = nearStartAddress + u16SizeinBytes;
            NearMemAlloc_Status.RamPageStatus[u8pageIndex].u16_FreeBytes = (UINT16)(nearEndAddress - nearStartAddress - u16SizeinBytes + 1);
            /* Stop searching thorugh pages */
            break;
        }
    }
    
    return(prtAllocatedBuffer);
}

/****************************************************************************************************/
/**
* \brief    memory allocation - reserve a buffer and return its address
* \author   Abraham Tezmol
* \param    tu8ptr_far StartAddress - Start of section to be erased
* \param    UINT16  u16SizeinBytes - size of section to be erased 
* \return   tu8ptr_near pointer to start of allocated space
* \todo     
*/
void vfnMemAlloc_NearErase( tu8ptr_near StartAddress , UINT16  u16SizeinBytes)
{
    UINT16 u16Bytes;
    
    for (u16Bytes = 0; u16Bytes < u16SizeinBytes; u16Bytes++ )
    {
        *StartAddress++ = 0x00;
    }
}

/*****************************************************************************************************
* Code of public FUNCTIONS - FAR ALLOCAATION
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    memory allocation - Initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnMemAlloc_Init( const tMemAlloc_config * mem_alloc_config  )
{
    UINT8 u8pageIndex;
    tu8ptr_far StartAddress;
    tu8ptr_far EndAddress;
    
    /* Store pointer to driver configuration */
    mem_alloc_farcnf = mem_alloc_config;
    
    MemAlloc_Status.RamPageStatus = &PagedRamPagesFar_status[0];
    
    if (mem_alloc_farcnf->u8Number_of_RAM_pages != 0)
    {
        for (u8pageIndex = 0; u8pageIndex < mem_alloc_farcnf->u8Number_of_RAM_pages; u8pageIndex++ )
        {
            /* Obtain Start and End Addresses */
            StartAddress =   mem_alloc_farcnf->ptr_PagedRAMpages_config[u8pageIndex].ptr_StartAddress;
            EndAddress = mem_alloc_farcnf->ptr_PagedRAMpages_config[u8pageIndex].ptr_EndAddress;
            /* Update all relevant entries in status structure */ 
            MemAlloc_Status.RamPageStatus[u8pageIndex].RamPageId = mem_alloc_farcnf->ptr_PagedRAMpages_config[u8pageIndex].RamPageId;
            MemAlloc_Status.RamPageStatus[u8pageIndex].ptr_CurrentAddress = StartAddress;
            MemAlloc_Status.RamPageStatus[u8pageIndex].ptr_EndAddress = EndAddress;
            MemAlloc_Status.RamPageStatus[u8pageIndex].u16_FreeBytes = (UINT16)(EndAddress - StartAddress + 1);
            /* Updated internal variable that keeps track of available pages */
            MemAlloc_Status.u8NumberOfPages++;
            
            /* Erase RAM in order to assure all entries are ready to be used */
            vfnMemAlloc_Erase(StartAddress, MemAlloc_Status.RamPageStatus[u8pageIndex].u16_FreeBytes);
        }
    }
}

/****************************************************************************************************/
/**
* \brief    memory allocation - reserve a buffer and return its address
* \author   Abraham Tezmol
* \param    UINT16  u16SizeinBytes
* \return   tu8ptr_far pointer to start of allocated space
* \todo     
*/
tu8ptr_far MemAlloc_Reserve( UINT16  u16SizeinBytes)
{
    UINT8 u8pageIndex;
    tu8ptr_far prtAllocatedBuffer = (tu8ptr_far)NULL;
    static tu8ptr_far farStartAddress;
    static tu8ptr_far farEndAddress;
    
    for (u8pageIndex = 0; u8pageIndex < MemAlloc_Status.u8NumberOfPages; u8pageIndex++ )
    {
        /* Get start and end address parameters for this RAM page */ 
        farStartAddress = MemAlloc_Status.RamPageStatus[u8pageIndex].ptr_CurrentAddress;
        farEndAddress = MemAlloc_Status.RamPageStatus[u8pageIndex].ptr_EndAddress;
        /* Apply alginment */
        farStartAddress = (tu8ptr_far)(((UINT32)(farStartAddress)+3) & (UINT32)MEM_ALLOC_4_BYTE_ALIGN);
        /* Verify if enough memory is free */
        if( (UINT16)(farEndAddress - farStartAddress + 1) >= u16SizeinBytes )
        {
            /* Enough memory is available, reserve it and return its start address */
            prtAllocatedBuffer = farStartAddress;
            MemAlloc_Status.RamPageStatus[u8pageIndex].ptr_CurrentAddress = farStartAddress + u16SizeinBytes;
            MemAlloc_Status.RamPageStatus[u8pageIndex].u16_FreeBytes = (UINT16)(farEndAddress - farStartAddress + 1);
            /* Stop searching thorugh pages */
            break;
        }
    }
    
    return(prtAllocatedBuffer);
}

/****************************************************************************************************/
/**
* \brief    memory allocation - reserve a buffer and return its address
* \author   Abraham Tezmol
* \param    tu8ptr_far StartAddress - Start of section to be erased
* \param    UINT16  u16SizeinBytes - size of section to be erased 
* \return   tu8ptr_far pointer to start of allocated space
* \todo     
*/
void vfnMemAlloc_Erase( tu8ptr_far StartAddress , UINT16  u16SizeinBytes)
{
    UINT16 u16Bytes;
    
    for (u16Bytes = 0; u16Bytes < u16SizeinBytes; u16Bytes++ )
    {
        *StartAddress++ = 0x00;
    }
}

/***************************************************************************************************/
