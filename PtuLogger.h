/*******************************************************************************
*
* .b
*   Copyright (c) 2002 Bombardier Transportation and Holdings (Inc.)
*
*   Project :
*               Common
*
*   File Name :
*               PtuLogger.h
*
*   Subsystem :
*               PTU
*
*
* .b
*
*   History :   12/02/2002   Sarfaraz Taher - Creation
*   Revised :
*               06/17/2003  John Novacek @ Bombardier Transportation
*	                  Merged updates made for Pitt LRV for Loggers
*                    4,5 and 6.
*               02/28/2006  Amadou Diop @ Bombardier Transportation
*	                  Increased number of engineering faults to 100
*
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _PTULOGGER_H_
#define _PTULOGGER_H_


/* !!! IMPORTANT NOTE: Make sure that :                      !!! */
/* !!!     (NUMOFEVENTLOGS >= LOGGER0_MAX_NUM_OF_FAULTS) &&  !!! */
/* !!!     (NUMOFEVENTLOGS >= LOGGER1_MAX_NUM_OF_FAULTS) &&  !!! */
/* !!!     (NUMOFEVENTLOGS >= LOGGER2_MAX_NUM_OF_FAULTS) &&  !!! */
/* !!!     (NUMOFEVENTLOGS >= LOGGER3_MAX_NUM_OF_FAULTS)     !!! */

/* Event/Data Logger #0 : Propulsion Faults */
#define LOGGER0_NUMBER_OF_TASKS               16
#define LOGGER0_NUMBER_OF_FAULTS_PER_TASK     80
#define LOGGER0_MAX_NUM_OF_FAULTS             75
#define LOGGER0_SIZEOF_AVERAGE_FAULT_PACKAGE  124/* at least sizeof( struct minfaultpacket_t ) */
#define LOGGER0_SIZE_OF_FAULT_QUEUE           ( LOGGER0_SIZEOF_AVERAGE_FAULT_PACKAGE * \
                                                LOGGER0_MAX_NUM_OF_FAULTS              )
#define LOGGER0_NUM_OF_DATALOG_ELEMENTS       6  //  6 after BATRAM limitation has been fixed
#define LOGGER0_NUM_LOGGED_VARIABLES          16
#define LOGGER0_NUM_OF_DATALOG_ENTRIES        100

/* Event/Data Logger #1 : Engineering Faults */
#define LOGGER1_NUMBER_OF_TASKS               16
#define LOGGER1_NUMBER_OF_FAULTS_PER_TASK     80
#define LOGGER1_MAX_NUM_OF_FAULTS             75

#define LOGGER1_SIZEOF_AVERAGE_FAULT_PACKAGE  124 /* at least sizeof( struct minfaultpacket_t ) */
#define LOGGER1_SIZE_OF_FAULT_QUEUE           ( LOGGER1_SIZEOF_AVERAGE_FAULT_PACKAGE * \
                                                LOGGER1_MAX_NUM_OF_FAULTS              )
#define LOGGER1_NUM_OF_DATALOG_ELEMENTS       6     //  6 after BATRAM limitation has been fixed
#define LOGGER1_NUM_LOGGED_VARIABLES          16
#define LOGGER1_NUM_OF_DATALOG_ENTRIES        100

/* Event/Data Logger #2 : DCU FASTMDB Faults */
#define LOGGER2_NUMBER_OF_TASKS               16
#define LOGGER2_NUMBER_OF_FAULTS_PER_TASK     80
#define LOGGER2_MAX_NUM_OF_FAULTS             50    // 50 after BATRAM limitation has been fixed
#define LOGGER2_SIZEOF_AVERAGE_FAULT_PACKAGE  30 /* at least sizeof( struct minfaultpacket_t ) */
#define LOGGER2_SIZE_OF_FAULT_QUEUE           ( LOGGER2_SIZEOF_AVERAGE_FAULT_PACKAGE * \
                                                LOGGER2_MAX_NUM_OF_FAULTS              )
#define LOGGER2_NUM_OF_DATALOG_ELEMENTS       LOGGER2_MAX_NUM_OF_FAULTS
																 //change back to -->LOGGER2_MAX_NUM_OF_FAULTS
                                               	 // if problem change to 4-5-6
#define LOGGER2_NUM_LOGGED_VARIABLES          20
#define LOGGER2_NUM_OF_DATALOG_ENTRIES        80 /* Revised from 100 8-22-00 JJN */
                                                 /* Based on CAPEC function values */
#if 0
/* Event/Data Logger #4 : DCU Control Faults */
#define LOGGER4_NUMBER_OF_TASKS               16
#define LOGGER4_NUMBER_OF_FAULTS_PER_TASK     20
#define LOGGER4_MAX_NUM_OF_FAULTS             20
#define LOGGER4_SIZEOF_AVERAGE_FAULT_PACKAGE  30 /* was set=0 for tests- at least sizeof( struct minfaultpacket_t ) */
#define LOGGER4_SIZE_OF_FAULT_QUEUE           ( LOGGER4_SIZEOF_AVERAGE_FAULT_PACKAGE * \
                                                LOGGER4_MAX_NUM_OF_FAULTS              )
#define LOGGER4_NUM_OF_DATALOG_ELEMENTS       LOGGER4_MAX_NUM_OF_FAULTS
#define LOGGER4_NUM_LOGGED_VARIABLES          9
#define LOGGER4_NUM_OF_DATALOG_ENTRIES        101

/* Event/Data Logger #5 : DCU Hardware Faults */
#define LOGGER5_NUMBER_OF_TASKS               16
#define LOGGER5_NUMBER_OF_FAULTS_PER_TASK     20
#define LOGGER5_MAX_NUM_OF_FAULTS             20
#define LOGGER5_SIZEOF_AVERAGE_FAULT_PACKAGE  30 /* was set=0 for tests- at least sizeof( struct minfaultpacket_t ) */
#define LOGGER5_SIZE_OF_FAULT_QUEUE           ( LOGGER5_SIZEOF_AVERAGE_FAULT_PACKAGE * \
                                                LOGGER5_MAX_NUM_OF_FAULTS              )
#define LOGGER5_NUM_OF_DATALOG_ELEMENTS       LOGGER5_MAX_NUM_OF_FAULTS
#define LOGGER5_NUM_LOGGED_VARIABLES          12
#define LOGGER5_NUM_OF_DATALOG_ENTRIES        11

/* Event/Data Logger #6 : DCU Temperature Faults */
#define LOGGER6_NUMBER_OF_TASKS               16
#define LOGGER6_NUMBER_OF_FAULTS_PER_TASK     20
#define LOGGER6_MAX_NUM_OF_FAULTS             20
#define LOGGER6_SIZEOF_AVERAGE_FAULT_PACKAGE  30 /* was set=0 for tests- at least sizeof( struct minfaultpacket_t ) */
#define LOGGER6_SIZE_OF_FAULT_QUEUE           ( LOGGER6_SIZEOF_AVERAGE_FAULT_PACKAGE * \
                                                LOGGER6_MAX_NUM_OF_FAULTS              )
#define LOGGER6_NUM_OF_DATALOG_ELEMENTS       LOGGER6_MAX_NUM_OF_FAULTS
#define LOGGER6_NUM_LOGGED_VARIABLES          13
#define LOGGER6_NUM_OF_DATALOG_ENTRIES        8
#endif

#define SIZEOF_EVENTLOGHUNK0     SIZEOF_EVENTLOGHUNK(    LOGGER0_NUMBER_OF_TASKS,           \
                                                         LOGGER0_NUMBER_OF_FAULTS_PER_TASK, \
                                                         LOGGER0_MAX_NUM_OF_FAULTS,         \
                                                         LOGGER0_SIZE_OF_FAULT_QUEUE        )
#define SIZEOF_EVENTLOGHUNK1     SIZEOF_EVENTLOGHUNK(    LOGGER1_NUMBER_OF_TASKS,           \
                                                         LOGGER1_NUMBER_OF_FAULTS_PER_TASK, \
                                                         LOGGER1_MAX_NUM_OF_FAULTS,         \
                                                         LOGGER1_SIZE_OF_FAULT_QUEUE        )
#define SIZEOF_EVENTLOGHUNK2     SIZEOF_EVENTLOGHUNK(    LOGGER2_NUMBER_OF_TASKS,           \
                                                         LOGGER2_NUMBER_OF_FAULTS_PER_TASK, \
                                                         LOGGER2_MAX_NUM_OF_FAULTS,         \
                                                         LOGGER2_SIZE_OF_FAULT_QUEUE        )
/*#define SIZEOF_EVENTLOGHUNK4     SIZEOF_EVENTLOGHUNK(    LOGGER4_NUMBER_OF_TASKS,           \
                                                         LOGGER4_NUMBER_OF_FAULTS_PER_TASK, \
                                                         LOGGER4_MAX_NUM_OF_FAULTS,         \
                                                         LOGGER4_SIZE_OF_FAULT_QUEUE        )
#define SIZEOF_EVENTLOGHUNK5     SIZEOF_EVENTLOGHUNK(    LOGGER5_NUMBER_OF_TASKS,           \
                                                         LOGGER5_NUMBER_OF_FAULTS_PER_TASK, \
                                                         LOGGER5_MAX_NUM_OF_FAULTS,         \
                                                         LOGGER5_SIZE_OF_FAULT_QUEUE        )
#define SIZEOF_EVENTLOGHUNK6     SIZEOF_EVENTLOGHUNK(    LOGGER6_NUMBER_OF_TASKS,           \
                                                         LOGGER6_NUMBER_OF_FAULTS_PER_TASK, \
                                                         LOGGER6_MAX_NUM_OF_FAULTS,         \
                                                         LOGGER6_SIZE_OF_FAULT_QUEUE        )  */


#define SIZEOF_DATALOGHUNK0      SIZEOF_DATALOGHUNK(     LOGGER0_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER0_NUM_LOGGED_VARIABLES     )
#define SIZEOF_DATALOGHUNK1      SIZEOF_DATALOGHUNK(     LOGGER1_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER1_NUM_LOGGED_VARIABLES     )
#define SIZEOF_DATALOGHUNK2      SIZEOF_DATALOGHUNK(     LOGGER2_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER2_NUM_LOGGED_VARIABLES     )
/*#define SIZEOF_DATALOGHUNK4      SIZEOF_DATALOGHUNK(     LOGGER4_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER4_NUM_LOGGED_VARIABLES     )
#define SIZEOF_DATALOGHUNK5      SIZEOF_DATALOGHUNK(     LOGGER5_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER5_NUM_LOGGED_VARIABLES     )
#define SIZEOF_DATALOGHUNK6      SIZEOF_DATALOGHUNK(     LOGGER6_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER6_NUM_LOGGED_VARIABLES     )	*/


#define SIZEOF_DATALOGDATAHUNK0  SIZEOF_DATALOGDATAHUNK( LOGGER0_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER0_NUM_OF_DATALOG_ENTRIES,    \
                                                         LOGGER0_NUM_LOGGED_VARIABLES       )
#define SIZEOF_DATALOGDATAHUNK1  SIZEOF_DATALOGDATAHUNK( LOGGER1_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER1_NUM_OF_DATALOG_ENTRIES,    \
                                                         LOGGER1_NUM_LOGGED_VARIABLES       )
#define SIZEOF_DATALOGDATAHUNK2  SIZEOF_DATALOGDATAHUNK( LOGGER2_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER2_NUM_OF_DATALOG_ENTRIES,    \
                                                         LOGGER2_NUM_LOGGED_VARIABLES       )
/*#define SIZEOF_DATALOGDATAHUNK4  SIZEOF_DATALOGDATAHUNK( LOGGER4_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER4_NUM_OF_DATALOG_ENTRIES,    \
                                                         LOGGER4_NUM_LOGGED_VARIABLES       )
#define SIZEOF_DATALOGDATAHUNK5  SIZEOF_DATALOGDATAHUNK( LOGGER5_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER5_NUM_OF_DATALOG_ENTRIES,    \
                                                         LOGGER5_NUM_LOGGED_VARIABLES       )
#define SIZEOF_DATALOGDATAHUNK6  SIZEOF_DATALOGDATAHUNK( LOGGER6_NUM_OF_DATALOG_ELEMENTS,   \
                                                         LOGGER6_NUM_OF_DATALOG_ENTRIES,    \
                                                         LOGGER6_NUM_LOGGED_VARIABLES       ) */

#endif

/* #endif */
#ifdef __cplusplus
}
#endif
