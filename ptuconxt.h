/*****************************************************************************
*
* .b
*    Copyright (c) 2001 Bombardier Transportation (Holdings) USA Inc.
*
* Project             : Pittsburgh LRV Propulsion
*
* File Name           : ptuconxt.h
*
* Subsystem           : None
*
* Procedures          : None
*
* EPROM Drawing       :
* .b
*
* History :
*  16 Aug 2001 S.Taher @ Bombardier
*    Created
*
* Revised :
*  01 Oct 2002 S.Taher @ Bombardier
*     Made the following changes while integrating with the Rhapsody
*     generated code.
*  02 June 16 2003 J.Novacek @ Bombardier
*     Added extern declarations for implementation of TDSL (original declarations for
*     stream vars.
*  03 June 24 2003 J.Novacek @ Bombardier
*     Added additional extern declarations for vars added with Pitt LRV for
*     stream data variables.
*  04 October 26 2004 Amadou Diop @ Bombardier
*	  Added mvb_ext.h
*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _PTUCONXT_H_
#define _PTUCONXT_H_

#include "ptuconst.h"
#include "ptu.h"

#ifdef PROJECT
#include "ProjectPkg/PtuEnumPkg/VCU/VCU.h"
#include "ProjectPkg/PtuEnumPkg/PtuVarsPkg/PtuVarsPkg.h"
#endif

#ifdef TEST_ON_PC
#include "VCU.h"
#include "mvb_ext.h"
#include "ip_ext.h"
#else
#include "mvb_ext.h"
#include "../../../../project/IP/ip_ext.h"
#endif

#ifdef COMMON
// This defines the array of PTU Watch Variables of
// INT_16 data-type.
//## attribute i16 
extern INT_16 i16[];

// This defines the array of PTU Watch Variables of
// INT_32 data-type.
//## attribute i32 
extern INT_32 i32[];

// This defines the array of PTU Watch Variables of
// INT_8 data-type.
//## attribute i8 
extern INT_8 i8[];

// This defines the array of PTU Watch Variables of
// UINT_16 data-type.
//## attribute u16 
extern UINT_16 u16[];

// This defines the array of PTU Watch Variables of
// UINT_32 data-type.
//## attribute u32 
extern UINT_32 u32[];

// This defines the array of PTU Watch Variables of
// UINT_8 data-type.
//## attribute u8 
extern UINT_8 u8[];
#endif

extern INT_16 XU_DcLkAdc1_Flt;
extern INT_16 WU_DcLkBrCp_Mod;
extern INT_16 XI_Ln_Flt;
extern INT_16 XN_RxSx_Avg;
extern INT_16 WM_Mt;
extern INT_16 WM_MtLimStb;
extern INT_16 XM_TrBr_Flt;
extern INT_16 WN_RxLimStb;
extern INT_16 WY_MtRmp;
extern INT_16 XY_SxSxoAp;
extern INT_16 W_ModNdx_Abs;
extern INT_16 FX_ModeNoV;
extern INT_16 XI_ErrRfolm_Flt;
extern INT_16 WU_DcLkBrCp;
extern INT_16 XX_BrCpDcy;
extern UINT_16 S_Fb;
extern UINT_16 dcu_dummy_var;

extern UINT_16 McuCoWord;
extern UINT_16 DspStWord;
extern UINT_16 DspFaultPa;

extern INT_16 MHTIUDC;
extern INT_16 MHTIIDC;
extern INT_16 MSPEAVFL;

extern UINT_16 GSSSSQST;
extern UINT_16 MPCLSTDW;
extern UINT_16 MPCL170;

extern INT_16 ZMVBWTR;
extern INT_16 MTTQTR;
extern INT_16 MBRTHEST;

extern UINT_16 MPCL240;
extern UINT_16 MPCL250;
extern UINT_16 MPCL260;

extern UINT_16 GDHSDECO;
extern UINT_16 GDHSFECO;
extern INT_16 GANIBRDT;

extern INT_16 GANICVHT;
extern INT_16 GANIGT1;
extern INT_16 GANIGT2;
extern INT_16 GANIGT3;
extern INT_16 GANIGT4;

extern INT_16 GANICVAT;
extern INT_16 GROTCHRT;
extern UINT_32 tdsl_var_1;
extern UINT_32 tdsl_var_2;
extern UINT_32 tdsl_var_3;
extern UINT_32 tdsl_var_4;
extern UINT_32 tdsl_var_5;
extern UINT_32 tdsl_var_6;
extern UINT_32 tdsl_var_7;

extern INT_16 XY_SxSxoAp;


#endif

#ifdef __cplusplus
}
#endif
