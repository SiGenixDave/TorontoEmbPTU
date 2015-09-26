/*****************************************************************************
*
* .b
*   Copyright (c) 1996 ABB Daimler-Benz Transportation (North America) Inc.
*
*   Project:
*               Common
*
*   File Name:
*               ptufltdt.c
*
*   SubSystem:
*               PTU
*
*   Procedures:
*
*   EPROM Drawing:
*
* .b
*
*   History:        07/10/94    Creation of Version 3.0         jsl
*   Revised:        09/11/95    ddp
*                   - Added in compression data
*                   10/05/95    ddp
*                   - Removed compression data
*                   04/04/01    JJN
*                   - Modified by D. Schnewlin for TDSL ...Added structs
*                     to accommodate 2 additional fault and data logs for
*                     TDSLite.
*                   10/03/2001  S.Taher
*                   - Moved the declaration of the EventLogHunkX, DataLogHunkX
*                     DataLogDef and EventLogDef.
*               02/27/2003  Becki Cirinelli @ Bombardier Transportation
*							SCR 71 - addded event and data log info
*							for logs 4,5,and 6.  removed log 3
*                     specification to a separate file (from ptu.h).
*               06/17/2003  John Novacek @ Bombardier Transportation
*	                  Merged updates made for Pitt LRV.
*	Jan-31-2006 D.Smail
* 	Changed the data recording rate from 15 msecs to 60 msecs in both the 
* 	Propulsion & Engineering data log.
*
*****************************************************************************/
/*  Grab all of the compiler #pragma's.                                     */
#ifdef __cplusplus
extern "C" {
#endif

#include "ptuprj.h"

#ifdef CCINTEL
#pragma datasegment (PTUFault)
#endif

/*  Grab the PTU specific files.                                            */
#include "ptu.h"
#include "ptufltdt.h"
#include "ptulogger.h"

struct faultlogqueue_t DATAFARTYPE  cc_faultlog[NUMOFEVENTLOGS];
struct datalogqueue_t  DATAFARTYPE  cc_datalog[NUMOFEVENTLOGS];


UINT_8 DATAFARTYPE  EventLogHunk0    [1/*SIZEOF_EVENTLOGHUNK0*/];
UINT_8 DATAFARTYPE  EventLogHunk1    [1/*SIZEOF_EVENTLOGHUNK1*/];
UINT_8 DATAFARTYPE  EventLogHunk2    [1/*SIZEOF_EVENTLOGHUNK2*/];
UINT_8 DATAFARTYPE  EventLogHunk4    [1/*SIZEOF_EVENTLOGHUNK3*/];
UINT_8 DATAFARTYPE  EventLogHunk5    [1/*SIZEOF_EVENTLOGHUNK3*/];
UINT_8 DATAFARTYPE  EventLogHunk6    [1/*SIZEOF_EVENTLOGHUNK3*/];

UINT_8 DATAFARTYPE  DataLogHunk0     [1/*SIZEOF_DATALOGHUNK0*/];
UINT_8 DATAFARTYPE  DataLogHunk1     [1/*SIZEOF_DATALOGHUNK1*/];
UINT_8 DATAFARTYPE  DataLogHunk2     [1/*SIZEOF_DATALOGHUNK2*/];
UINT_8 DATAFARTYPE  DataLogHunk4     [1/*SIZEOF_DATALOGHUNK3*/];
UINT_8 DATAFARTYPE  DataLogHunk5     [1/*SIZEOF_DATALOGHUNK3*/];
UINT_8 DATAFARTYPE  DataLogHunk6     [1/*SIZEOF_DATALOGHUNK3*/];

UINT_8 DATAFARTYPE  DataLogDataHunk0 [1/*SIZEOF_DATALOGDATAHUNK0*/];
UINT_8 DATAFARTYPE  DataLogDataHunk1 [1/*SIZEOF_DATALOGDATAHUNK1*/];
UINT_8 DATAFARTYPE  DataLogDataHunk2 [1/*SIZEOF_DATALOGDATAHUNK2*/];
UINT_8 DATAFARTYPE  DataLogDataHunk4 [1/*SIZEOF_DATALOGDATAHUNK3*/];
UINT_8 DATAFARTYPE  DataLogDataHunk5 [1/*SIZEOF_DATALOGDATAHUNK3*/];
UINT_8 DATAFARTYPE  DataLogDataHunk6 [1/*SIZEOF_DATALOGDATAHUNK3*/];

const     struct    EventLogDef_t   EventLogDef[NUMOFEVENTLOGS] =
{
  /* Event/Data Logger #0 : Propulsion Faults */
  {
    EventLogHunk0,                      /* Address of Event Log Area        */
    LOGGER0_NUMBER_OF_TASKS,            /* Maximum Number of Tasks          */
    LOGGER0_NUMBER_OF_FAULTS_PER_TASK,  /* Maximum possible Faults per Task */
    LOGGER0_MAX_NUM_OF_FAULTS,          /* Maximum Number of Faults         */
    LOGGER0_SIZE_OF_FAULT_QUEUE,        /* Maximum size of Fault Queue      */
  },

  /* Event/Data Logger #1 : Engineering Faults */
  {
    EventLogHunk1,                      /* Address of Event Log Area        */
    LOGGER1_NUMBER_OF_TASKS,            /* Maximum Number of Tasks          */
    LOGGER1_NUMBER_OF_FAULTS_PER_TASK,  /* Maximum possible Faults per Task */
    LOGGER1_MAX_NUM_OF_FAULTS,          /* Maximum Number of Faults         */
    LOGGER1_SIZE_OF_FAULT_QUEUE,        /* Maximum size of Fault Queue      */
  },

  /* Event/Data Logger #2 : DCU FASTMDB Faults */
  {
    EventLogHunk2,                      /* Address of Event Log Area        */
    LOGGER2_NUMBER_OF_TASKS,            /* Maximum Number of Tasks          */
    LOGGER2_NUMBER_OF_FAULTS_PER_TASK,  /* Maximum possible Faults per Task */
    LOGGER2_MAX_NUM_OF_FAULTS,          /* Maximum Number of Faults         */
    LOGGER2_SIZE_OF_FAULT_QUEUE,        /* Maximum size of Fault Queue      */
  },
#if 0
  /* Event/Data Logger #4 : DCU Control Faults */
  {
    EventLogHunk4,                      /* Address of Event Log Area        */
    LOGGER4_NUMBER_OF_TASKS,            /* Maximum Number of Tasks          */
    LOGGER4_NUMBER_OF_FAULTS_PER_TASK,  /* Maximum possible Faults per Task */
    LOGGER4_MAX_NUM_OF_FAULTS,          /* Maximum Number of Faults         */
    LOGGER4_SIZE_OF_FAULT_QUEUE,        /* Maximum size of Fault Queue      */
  },
  /* Event/Data Logger #5 : DCU Hardware Faults */
  {
    EventLogHunk5,                      /* Address of Event Log Area        */
    LOGGER5_NUMBER_OF_TASKS,            /* Maximum Number of Tasks          */
    LOGGER5_NUMBER_OF_FAULTS_PER_TASK,  /* Maximum possible Faults per Task */
    LOGGER5_MAX_NUM_OF_FAULTS,          /* Maximum Number of Faults         */
    LOGGER5_SIZE_OF_FAULT_QUEUE,        /* Maximum size of Fault Queue      */
  },
  /* Event/Data Logger #6 : DCU Temperature Faults */
  {
    EventLogHunk6,                      /* Address of Event Log Area        */
    LOGGER6_NUMBER_OF_TASKS,            /* Maximum Number of Tasks          */
    LOGGER6_NUMBER_OF_FAULTS_PER_TASK,  /* Maximum possible Faults per Task */
    LOGGER6_MAX_NUM_OF_FAULTS,          /* Maximum Number of Faults         */
    LOGGER6_SIZE_OF_FAULT_QUEUE,        /* Maximum size of Fault Queue      */
  },
#endif
};

const     struct    DataLogDef_t   DataLogDef[NUMOFEVENTLOGS] =
{
  /* Event/Data Logger #0 : Propulsion Faults */
  {
    DataLogHunk0,                       /* Address of Data Log Area          */
    LOGGER0_NUM_OF_DATALOG_ELEMENTS,    /* Number of Datalog Elements in ROM */
    LOGGER0_NUM_LOGGED_VARIABLES,       /* Number of Variables to Log in ROM */
    LOGGER0_NUM_OF_DATALOG_ENTRIES,     /* Number of Entries in an Element   */
    75,                                 /* Entry corresponding to Fault      */
    2,                                  /* Sample Freq as a multiplier of
               DataRecordingRate                 */
    60,                                 /* Data Recording Rate in ms         */
    {
      118, 226, 227, 54, 242, 243, 62, 63,
    },                                  /* DefaultStream Variables           */
    DataLogDataHunk0,                   /* Address of Data Log Data Area     */
  },

  /* Event/Data Logger #1 : Engineering Faults */
  {
    DataLogHunk1,                       /* Address of Data Log Area          */
    LOGGER1_NUM_OF_DATALOG_ELEMENTS,    /* Number of Datalog Elements in ROM */
    LOGGER1_NUM_LOGGED_VARIABLES,       /* Number of Variables to Log in ROM */
    LOGGER1_NUM_OF_DATALOG_ENTRIES,     /* Number of Entries in an Element   */
    75,                                 /* Entry corresponding to Fault      */
    2,                                  /* Sample Freq as a multiplier of
               DataRecordingRate                 */
    60,                                 /* Data Recording Rate in ms         */
    {
       118, 226, 227, 54, 242, 243, 62, 63
    },                                  /* DefaultStream Variables           */
    DataLogDataHunk1,                   /* Address of Data Log Data Area     */
  },

  /* Event/Data Logger #2 : DCU FASTMDB Faults */
  {
    DataLogHunk2,                       /* Address of Data Log Area          */
    LOGGER2_NUM_OF_DATALOG_ELEMENTS,    /* Number of Datalog Elements in ROM */
    LOGGER2_NUM_LOGGED_VARIABLES,       /* Number of Variables to Log in ROM */
    LOGGER2_NUM_OF_DATALOG_ENTRIES,     /* Number of Entries in an Element   */
    80,                                 /* Entry corresponding to Fault      */
    1,                                  /* Sample Freq as a multiplier of
               DataRecordingRate                 */
    4,                                  /* Data Recording Rate in ms         */
    {
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,
    },                                  /* DefaultStream Variables           */
    DataLogDataHunk2,                   /* Address of Data Log Data Area     */
  },
#if 0
  /* Event/Data Logger #4 : DCU Control Faults */
  {
    DataLogHunk4,                       /* Address of Data Log Area          */
    LOGGER4_NUM_OF_DATALOG_ELEMENTS,    /* Number of Datalog Elements in ROM */
    LOGGER4_NUM_LOGGED_VARIABLES,       /* Number of Variables to Log in ROM */
    LOGGER4_NUM_OF_DATALOG_ENTRIES,     /* Number of Entries in an Element   */
    81,                                 /* Entry corresponding to Fault      */
    1,                                  /* Sample Freq as a multiplier of
               DataRecordingRate                 */
    16,/*???*/                          /* Data Recording Rate in ms         */
    {
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     0
    },                                  /* DefaultStream Variables           */
    DataLogDataHunk4,                   /* Address of Data Log Data Area     */
  },

  /* Event/Data Logger #5 : DCU Hardware Faults */
  {
    DataLogHunk5,                       /* Address of Data Log Area          */
    LOGGER5_NUM_OF_DATALOG_ELEMENTS,    /* Number of Datalog Elements in ROM */
    LOGGER5_NUM_LOGGED_VARIABLES,       /* Number of Variables to Log in ROM */
    LOGGER5_NUM_OF_DATALOG_ENTRIES,     /* Number of Entries in an Element   */
    6,                                 /* Entry corresponding to Fault      */
    1,                                  /* Sample Freq as a multiplier of
               DataRecordingRate                 */
    16,/*???*/                          /* Data Recording Rate in ms         */
    {
     0, 0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0
    },                                  /* DefaultStream Variables           */
    DataLogDataHunk5,                   /* Address of Data Log Data Area     */
  },
  /* Event/Data Logger #6 : DCU Temperature Faults */
  {
    DataLogHunk6,                       /* Address of Data Log Area          */
    LOGGER6_NUM_OF_DATALOG_ELEMENTS,    /* Number of Datalog Elements in ROM */
    LOGGER6_NUM_LOGGED_VARIABLES,       /* Number of Variables to Log in ROM */
    LOGGER6_NUM_OF_DATALOG_ENTRIES,     /* Number of Entries in an Element   */
    6,                                 /* Entry corresponding to Fault      */
    1,                                  /* Sample Freq as a multiplier of
               DataRecordingRate                 */
    1024,/*???*/                          /* Data Recording Rate in ms         */
    {
     0, 0, 0, 0, 0, 0, 0, 0,
	 0, 0, 0, 0, 0
    },                                  /* DefaultStream Variables           */
    DataLogDataHunk6,                   /* Address of Data Log Data Area     */
  },
#endif
};

#ifdef __cplusplus
}
#endif
