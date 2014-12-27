/****************************************************************************************************/
/**
\file       int_vectors.c
\brief      Interrupt service routine vectors
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Own modules */
#include    "int_vectors.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
/* Startup defined in Start12.c */
extern  void interrupt  _Startup( void  );

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/** Interrupt vectors table */
void (* near const vectors[])(void) @ 0x7F10 =
{

  vfnDummy_D_Isr,          /* 0x08  0xFF10 ivVsi           */
  vfnDummy_D_Isr,          /* 0x09  0xFF12 ivu8Reserved119   */
  vfnDummy_D_Isr,          /* 0x0A  0xFF14 ivu8Reserved118   */
  vfnDummy_D_Isr,          /* 0x0B  0xFF16 ivu8Reserved117   */
  vfnDummy_D_Isr,          /* 0x0C  0xFF18 ivu8Reserved116   */
  vfnDummy_D_Isr,          /* 0x0D  0xFF1A ivu8Reserved115   */
  vfnDummy_D_Isr,          /* 0x0E  0xFF1C ivu8Reserved114   */
  vfnDummy_D_Isr,          /* 0x0F  0xFF1E ivu8Reserved113   */
  vfnDummy_D_Isr,          /* 0x10  0xFF20 ivu8Reserved112   */
  vfnDummy_D_Isr,          /* 0x11  0xFF22 ivu8Reserved111   */
  vfnDummy_D_Isr,          /* 0x12  0xFF24 ivu8Reserved110   */
  vfnDummy_D_Isr,          /* 0x13  0xFF26 ivu8Reserved109   */
  vfnDummy_D_Isr,          /* 0x14  0xFF28 ivu8Reserved108   */
  vfnDummy_D_Isr,          /* 0x15  0xFF2A ivu8Reserved107   */
  vfnDummy_D_Isr,          /* 0x16  0xFF2C ivu8Reserved106   */
  vfnDummy_D_Isr,          /* 0x17  0xFF2E ivu8Reserved105   */
  vfnDummy_D_Isr,          /* 0x18  0xFF30 ivu8Reserved104   */
  vfnDummy_D_Isr,          /* 0x19  0xFF32 ivu8Reserved103   */
  vfnDummy_D_Isr,          /* 0x1A  0xFF34 ivu8Reserved102   */
  vfnDummy_D_Isr,          /* 0x1B  0xFF36 ivu8Reserved101   */
  vfnDummy_D_Isr,          /* 0x1C  0xFF38 ivu8Reserved100   */
  vfnDummy_D_Isr,          /* 0x1D  0xFF3A ivu8Reserved99    */
  vfnDummy_D_Isr,          /* 0x1E  0xFF3C ivu8Reserved98    */
  vfnDummy_D_Isr,          /* 0x1F  0xFF3E ivu8Reserved97    */
  vfnDummy_D_Isr,          /* 0x20  0xFF40 ivu8Reserved96    */
  vfnDummy_D_Isr,          /* 0x21  0xFF42 ivu8Reserved95    */
  vfnDummy_D_Isr,          /* 0x22  0xFF44 ivu8Reserved94    */
  vfnDummy_D_Isr,          /* 0x23  0xFF46 ivu8Reserved93    */
  vfnDummy_D_Isr,          /* 0x24  0xFF48 ivu8Reserved92    */
  vfnDummy_D_Isr,          /* 0x25  0xFF4A ivu8Reserved91    */
  vfnDummy_D_Isr,          /* 0x26  0xFF4C ivu8Reserved90    */
  vfnDummy_D_Isr,          /* 0x27  0xFF4E ivu8Reserved89    */
  vfnDummy_D_Isr,          /* 0x28  0xFF50 ivu8Reserved88    */
  vfnDummy_D_Isr,          /* 0x29  0xFF52 ivu8Reserved87    */
  vfnDummy_D_Isr,          /* 0x2A  0xFF54 ivu8Reserved86    */
  vfnDummy_D_Isr,          /* 0x2B  0xFF56 ivu8Reserved85    */
  vfnDummy_D_Isr,          /* 0x2C  0xFF58 ivu8Reserved84    */
  vfnDummy_D_Isr,          /* 0x2D  0xFF5A ivu8Reserved83    */
  vfnDummy_D_Isr,          /* 0x2E  0xFF5C ivu8Reserved82    */
  vfnDummy_D_Isr,          /* 0x2F  0xFF5E ivu8Reserved81    */
  vfnDummy_D_Isr,          /* 0x30  0xFF60 ivVxsramav      */
  vfnDummy_D_Isr,          /* 0x31  0xFF62 ivVxsei         */
  vfnDummy_D_Isr,          /* 0x32  0xFF64 ivVxst7         */
  vfnDummy_D_Isr,          /* 0x33  0xFF66 ivVxst6         */
  vfnDummy_D_Isr,          /* 0x34  0xFF68 ivVxst5         */
  vfnDummy_D_Isr,          /* 0x35  0xFF6A ivVxst4         */
  vfnDummy_D_Isr,          /* 0x36  0xFF6C ivVxst3         */
  vfnJ2716_Callback_Isr,   /* 0x37  0xFF6E ivVxst2         */
  vfnDummy_D_Isr,          /* 0x38  0xFF70 ivVxst1         */
  vfnDummy_D_Isr,          /* 0x39  0xFF72 ivVxst0         */
  vfnDummy_D_Isr,          /* 0x3A  0xFF74 ivVpit3         */
  vfnDummy_D_Isr,          /* 0x3B  0xFF76 ivVpit2         */
  vfnDummy_D_Isr,          /* 0x3C  0xFF78 ivVpit1         */
  vfnPIT_Channel0_Isr,     /* 0x3D  0xFF7A ivVpit0         */
  vfnDummy_D_Isr,          /* 0x3E  0xFF7C ivVu8Reserved65   */
  vfnDummy_D_Isr,          /* 0x3F  0xFF7E ivVapi          */
  vfnDummy_D_Isr,          /* 0x40  0xFF80 ivVlvi          */
  vfnDummy_D_Isr,          /* 0x41  0xFF82 ivVu8Reserved62   */
  vfnDummy_D_Isr,          /* 0x42  0xFF84 ivVu8Reserved61   */
  vfnDummy_D_Isr,          /* 0x43  0xFF86 ivVu8Reserved60   */
  vfnDummy_D_Isr,          /* 0x44  0xFF88 ivVu8Reserved59   */
  vfnDummy_D_Isr,          /* 0x45  0xFF8A ivVu8Reserved58   */
  vfnDummy_D_Isr,          /* 0x46  0xFF8C ivVpmffault3    */
  vfnDummy_D_Isr,          /* 0x47  0xFF8E ivVpmffault2    */
  vfnDummy_D_Isr,          /* 0x48  0xFF90 ivVpmffault1    */
  vfnDummy_D_Isr,          /* 0x49  0xFF92 ivVpmffault0    */
  vfnDummy_D_Isr,          /* 0x4A  0xFF94 ivVpmfgcr       */
  vfnDummy_D_Isr,          /* 0x4B  0xFF96 ivVpmfgbr       */
  vfnDummy_D_Isr,          /* 0x4C  0xFF98 ivVpmfgar       */
  vfnDummy_D_Isr,          /* 0x4D  0xFF9A ivVfrprot       */
  vfnDummy_D_Isr,          /* 0x4E  0xFF9C ivVfrchi        */
  vfnDummy_D_Isr,          /* 0x4F  0xFF9E ivVfrwakeup     */
  vfnDummy_D_Isr,          /* 0x50  0xFFA0 ivVfrrxfifob    */
  vfnDummy_D_Isr,          /* 0x51  0xFFA2 ivVfrrxfifoa    */
  vfnDummy_D_Isr,          /* 0x52  0xFFA4 ivVfrrxmessbuff */
  vfnDummy_D_Isr,          /* 0x53  0xFFA6 ivVfrtxmessbuff */
  vfnDummy_D_Isr,          /* 0x54  0xFFA8 ivVu8Reserved43   */
  vfnDummy_D_Isr,          /* 0x55  0xFFAA ivVu8Reserved42   */
  vfnDummy_D_Isr,          /* 0x56  0xFFAC ivVu8Reserved41   */
  vfnDummy_D_Isr,          /* 0x57  0xFFAE ivVu8Reserved40   */
  vfnDummy_D_Isr,          /* 0x58  0xFFB0 ivVcan0tx       */
  vfnDummy_D_Isr,          /* 0x59  0xFFB2 ivVcan0rx       */
  vfnDummy_D_Isr,          /* 0x5A  0xFFB4 ivVcan0err      */
  vfnDummy_D_Isr,          /* 0x5B  0xFFB6 ivVcan0wkup     */
  vfnDummy_D_Isr,          /* 0x5C  0xFFB8 ivVflash        */
  vfnDummy_D_Isr,          /* 0x5D  0xFFBA ivVeeprom       */
  vfnDummy_D_Isr,          /* 0x5E  0xFFBC ivVu8Reserved33   */
  vfnDummy_D_Isr,          /* 0x5F  0xFFBE ivVspi1         */
  vfnDummy_D_Isr,          /* 0x60  0xFFC0 ivVu8Reserved31   */
  vfnDummy_D_Isr,          /* 0x61  0xFFC2 ivVu8Reserved30   */
  vfnDummy_D_Isr,          /* 0x62  0xFFC4 ivVcrgscm       */
  vfnDummy_D_Isr,          /* 0x63  0xFFC6 ivVcrgplllck    */
  vfnDummy_D_Isr,          /* 0x64  0xFFC8 ivVtimpabovf    */
  vfnDummy_D_Isr,          /* 0x65  0xFFCA ivVtimmdcu      */
  vfnDummy_D_Isr,          /* 0x66  0xFFCC ivVu8Reserved25   */
  vfnDummy_D_Isr,          /* 0x67  0xFFCE ivVu8Reserved24   */
  vfnDummy_D_Isr,          /* 0x68  0xFFD0 ivVatd          */
  vfnADC_SequenceRdy_Isr,  /* 0x69  0xFFD2 ivVu8Reserved22   */
  vfnSCI1_TxRx_Isr,        /* 0x6A  0xFFD4 ivVsci1         */
  vfnSCI0_TxRx_Isr,        /* 0x6B  0xFFD6 ivVsci0         */
  vfnDummy_D_Isr,          /* 0x6C  0xFFD8 ivVspi0         */
  vfnDummy_D_Isr,          /* 0x6D  0xFFDA ivVtimpaie      */
  vfnDummy_D_Isr,          /* 0x6E  0xFFDC ivVtimpaaovf    */
  vfnDummy_D_Isr,          /* 0x6F  0xFFDE ivVtimovf       */
  vfnDummy_D_Isr,          /* 0x70  0xFFE0 ivVtimch7       */
  vfnDummy_D_Isr,          /* 0x71  0xFFE2 ivVtimch6       */
  vfnDummy_D_Isr,          /* 0x72  0xFFE4 ivVtimch5       */
  vfnDummy_D_Isr,          /* 0x73  0xFFE6 ivVtimch4       */
  vfnDummy_D_Isr,          /* 0x74  0xFFE8 ivVtimch3       */
  vfnDummy_D_Isr,          /* 0x75  0xFFEA ivVtimch2       */
  vfnDummy_D_Isr,          /* 0x76  0xFFEC ivVtimch1       */
  vfnDummy_D_Isr,          /* 0x77  0xFFEE ivVtimch0       */
  vfnDummy_D_Isr,          /* 0x78  0xFFF0 ivVrti          */
  vfnDummy_D_Isr,          /* 0x79  0xFFF2 ivVirq          */
  vfnDummy_D_Isr,          /* 0x7A  0xFFF4 ivVxirq         */
  vfnDummy_D_Isr,          /* 0x7B  0xFFF6 ivVswi          */
  vfnDummy_D_Isr,          /* 0x7C  0xFFF8 ivVtrap         */
  _Startup,             /* 0xFFFA  ivVcop               */
  vfnPll_Clock_Monitor_Isr   /* 0xFFFC  ivVclkmon            */
  /*_Startup               0xFFFE  ivVreset           */
}
;

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Dummy ISR, if reached, processing will enter an empty routine
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt  vfnDummy_D_Isr( void  )
{
}
#pragma CODE_SEG DEFAULT
