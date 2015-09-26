/*****************************************************************************
*
* .b
*    Copyright (c) 2001 Bombardier Transportation (Holdings) USA Inc.
*
* Project             : Pittsburgh LRV Propulsion
*
* File Name           : ptufltdt.h
*
* Subsystem           : None
*
* Procedures          : None
*
* .b
*
* History :
*  03 Oct 2001 S.Taher @ Bombardier
*    Created
*
* Revised :
*
*               02/27/2003  Becki Cirinelli @ Bombardier Transportation
*							SCR 71 - addded event and data log info
*							for logs 4,5,and 6.  removed log 3
*               06/17/2003  John Novacek @ Bombardier Transportation
*	                  Merged updates made for Pitt LRV.
*
*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _PTUFLTDT_H_
#define _PTUFLTDT_H_

#ifdef TEST_ON_PC
#include "myWrapper.h"
#else
#include "cpu_dep.h"
#endif
#include "ptu.h"

extern UINT_8 DATAFARTYPE EventLogHunk0[];
extern UINT_8 DATAFARTYPE EventLogHunk1[];
extern UINT_8 DATAFARTYPE EventLogHunk2[];
extern UINT_8 DATAFARTYPE EventLogHunk4[];
extern UINT_8 DATAFARTYPE EventLogHunk5[];
extern UINT_8 DATAFARTYPE EventLogHunk6[];

extern UINT_8 DATAFARTYPE DataLogHunk0[];
extern UINT_8 DATAFARTYPE DataLogDataHunk0[];
extern UINT_8 DATAFARTYPE DataLogHunk1[];
extern UINT_8 DATAFARTYPE DataLogDataHunk1[];
extern UINT_8 DATAFARTYPE DataLogHunk2[];
extern UINT_8 DATAFARTYPE DataLogDataHunk2[];
extern UINT_8 DATAFARTYPE DataLogHunk4[];
extern UINT_8 DATAFARTYPE DataLogDataHunk4[];
extern UINT_8 DATAFARTYPE DataLogHunk5[];
extern UINT_8 DATAFARTYPE DataLogDataHunk5[];
extern UINT_8 DATAFARTYPE DataLogHunk6[];
extern UINT_8 DATAFARTYPE DataLogDataHunk6[];

/* Externs */
extern const struct DataLogDef_t    DataLogDef[];
extern const struct EventLogDef_t   EventLogDef[];

#endif

#ifdef __cplusplus
}
#endif
