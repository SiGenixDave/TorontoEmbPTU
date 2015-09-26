/*****************************************************************************
*
* .b
*    Copyright 1995,1996,1999,2001 Bombardier Transportation (Holdings) USA Inc.
*
* Project             : Pittsburgh LRV Propulsion
*
* File Name           : batram.h
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
* Revision History:
*
* 01/15/93   LFT  Created
* 06/17/93   LFC
* 11/19/93   LFC  New battery ram init
* 11/30/93   AM   Added daily MWH readings : changed init pattern
* 12/17/93   LFC  Changed ref_wheel_dia from UINT_32 to UINT_16 and
*				   added externs for start_cbram_write(), end_cbram_write()
* 07/13/94   AM   added parameter adjustablility variables to constant area
* 01/30/95   AM   added car run stats structure to NC bat ram area
* 11/17/1999 SRT  Made the following changes while moving the fault log and the
*                 datalog to BBRAM :
*                 1. Added then following constants:
*                    - BBRAM_START_ADDRESS
*                    - BBRAM_END_ADDRESS
*                    - MAX_BBRAM_SIZE
*                    - BBRAM_END_SIGNATURE
*                 2. Added the following members to the structure declaration
*                    for the non_const_bat_ram_interface:
*                    - cc_faultlog
*                    - cc_datalog
*                    - EventLogHunk
*                    - DataLogHunk
*                    - DataLogDataHunk
*                    - bram_end
*                 3. Added the external declarations for the following two
*                    variables :
*                    - *bat_ram_area
*                 4. Deleted unused unions.
* 12/02/2000 SRT Added the olr_fault_ctr to the non_constant area.
* 02/20/2001 SRT Added the tach_fault_count to the non_constant area.
* 11/15/2000 JJN Added in TDSL structs Hunk #0, #1 #2 and #3
*					   within the non_const_bat_ram_interface
*					   struct. Added MAX_PCL_INDEX, MAX_BLOCK_INDEX and
*					   PSV_ED_STATE_TABLE.  Original additions by D.Schnewlin.
* 04/09/2001 JJN Revised BBRAM_START_ADDRESS from 0x02FE0000 to
*                0x02F00000 to accommodate additional TDSL data and
*						event storage.
*
* 08/21/2001 SRT Adopted for Pittsburgh LRV and made changes to the non-
*                constant battery RAM structure.
* 11/21/2001 RAC Changed BBRAM_END_ADDRESS to allocate the last 15 bytes
*                for daylight savings time use
* 01/30/2002 RAC Changed BBRAM_START_ADDRESS to allocate the first 15
*                bytes for daylight savings time use
*                Reset BBRAM_END_ADDRESS to original value
* 05/28/2002 RAC Changed MAX_PCL_INDEX to 8 instead of 10
* 08/09/2002 JEP @ Bombardier
*   Added pbal_fault_ctr to struct non_const_bat_ram_interface due to the 
*   addition of power balance monitor function.
* 09/13/2002 JEP @ Bombardier
*   SCR 27 - Ventilation Monitoring
*   Add vent_fault_ctr to struct non_const_bat_ram_interface.
* 01/22/2003  S.Taher
*  - Included the file ptulogger.h when moving the fault 
*    specification to a separate file (from ptu.h).
* 04/15/2003 R. Cirinelli
*  - Modified to only account for information used in non constant bbram
*
* 06/23/2003
*  - Added EventLogHunk 4,5 and 6 according to Pitt LRV implementation,
*    deleted EventLogHunk 3.
*
* 03/28/2005  D.Smail
*  - Added wheelDiam[2] & odomoter (tNcbram) to the structures
* 06/07/2007 Amadou Diop
*  - Added the packed attribute to adapt to the Power PC
* 03/13/2008 Erik Holm
*  - Removed all hardcoded BBRAM pointer values. BBRAM is accessed exclusively
*    through the NVRAM Manager. Added Universal BBRAM segment names.
*    Added function prototypes to match new functions in batram.c
* 07/06/2008 Dave Smail    
*  - Added ProjConstVars structure. This allows the user to add project constant
*    variables without having a backup copy in non-constant area. Requires 
*    Common Library version 0x023 or higher to function. 
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _BATRAM_H_
#define _BATRAM_H_

#include "ptulogger.h"
#include "ptu.h"
#include "nvram_api.h"
#ifndef TEST_ON_PC
#include  "../../VCUC/device/app1/apperror.h"
#endif

/* Universal BBRAM segment names */
#define NCBBRAM_NAME "ncBBRam"
#define CBBRAM_NAME "cBBRam"
#define NCBBRAM_PTU_FAULT_LOGGER_NAME "ncBBRamPtu"


#define SIZE_OF_NVRAM_BLOCK 100000 /* No of bytes to write to NVRAM per cycle */
#define NVRAM_BLOCK_WRITE_TIME_DELAY 100 /* milliseconds */

#define REF_CAR_ID            9999    /* Default car id             */

/* Definitions for module "PSV-ED.C" (TDSL)                             */
/*#define MAX_PCL_INDEX         4    Number of supported PCL's  */
#define MAX_PCL_INDEX         8    /* Number of supported PCL's */
                                    /*(including 6 PCL using the TPP-tester)*/
#define MAX_BLOCK_INDEX       64    /* Number of Bit_16 blocks    */
typedef struct BLOCK_CONTAINING_16_STATES
{
  UINT_8  state [2]		 __attribute__ ((packed));
} PSV_ED_STATE_TABLE [MAX_PCL_INDEX] [MAX_BLOCK_INDEX];

/* Event Display */
#define NUMDEFINEDEVENTS    1000

/*
 * Declare the structure associated with the non-constant battery RAM area.
 */
 typedef struct
 {
  UINT_32 slideTimeout __attribute__ ((packed));
  UINT_32 spinTimeout __attribute__ ((packed));
  UINT_32 noMotionThresh __attribute__ ((packed));
  INT_32 systemJrl __attribute__ ((packed));
  UINT_16 highPerfEnable __attribute__ ((packed));
  UINT_32 redBrkMaxPwr __attribute__ ((packed));
  UINT_32 redBrkMinPwr __attribute__ ((packed));
  UINT_32 turtleMaxPwr __attribute__ ((packed));
  UINT_32 turtleMinPwr __attribute__ ((packed));
  INT_32 fwdAlarmSpeed __attribute__ ((packed));
  INT_32 fwdPenaltySpeed __attribute__ ((packed));
  INT_32 revAlarmSpeed __attribute__ ((packed));
  INT_32 revPenaltySpeed __attribute__ ((packed));
 } ProjConstVars;
 
 
 
struct tBram {
	UINT_32 sw_version  __attribute__ ((packed));
	UINT_16 CarID  __attribute__ ((packed));
	UINT_16 cbram_init_pattern[4]  __attribute__ ((packed));
	UINT_16 ref_wheel_num  __attribute__ ((packed));
    UINT_16 ref_wheel_dia  __attribute__ ((packed));
	UINT_16 test_c_var  __attribute__ ((packed));

    ProjConstVars projVars __attribute__ ((packed)); 

	UINT_16 crc  __attribute__ ((packed));
	UINT_16 pad[16]  __attribute__ ((packed));
}; 

struct tNcbram {
   UINT_16 test_nc_var  __attribute__ ((packed));
   UINT_32 odometer  __attribute__ ((packed));
   UINT_16 wheelDiam[4]  __attribute__ ((packed));
   /* add new variables here */
   UINT_16 A_Hvb_Gnd_Flt_Lockout  __attribute__ ((packed));
   UINT_16 A_Line_Overcurr_Lockout __attribute__ ((packed));
   UINT_16 A_Olr_Trip_Mon_Lockout  __attribute__ ((packed)); 
   UINT_16 A_Olr_Reset_Flt_Lockout   __attribute__ ((packed));

   UINT_16 B_Hvb_Gnd_Flt_Lockout  __attribute__ ((packed));  
   UINT_16 B_Line_Overcurr_Lockout  __attribute__ ((packed)); 
   UINT_16 B_Olr_Trip_Mon_Lockout  __attribute__ ((packed));
   UINT_16 B_Olr_Reset_Flt_Lockout  __attribute__ ((packed));


   UINT_32 slideTimeout __attribute__ ((packed));
   UINT_32 spinTimeout __attribute__ ((packed));
 
   UINT_32 tm1Counter  __attribute__ ((packed));
   UINT_32 tm2Counter  __attribute__ ((packed));
   UINT_32 tm3Counter  __attribute__ ((packed));
   UINT_32 tm4Counter  __attribute__ ((packed));

   UINT_32 gu1Counter  __attribute__ ((packed));
   UINT_32 gu2Counter  __attribute__ ((packed));
   UINT_32 gu3Counter  __attribute__ ((packed));
   UINT_32 gu4Counter  __attribute__ ((packed));
   //Car Statistics Numbers
   UINT_32 Cum_Energy_Con_TK1 __attribute__ ((packed));
   UINT_32 Cum_Energy_Con_TK2 __attribute__ ((packed));
   UINT_32 Cum_Energy_Regen_TK1 __attribute__ ((packed));
   UINT_32 Cum_Energy_Regen_TK2 __attribute__ ((packed));
   UINT_32 Cum_Energy_NonRegen_TK1 __attribute__ ((packed));
   UINT_32 Cum_Energy_NonRegen_TK2 __attribute__ ((packed));
   UINT_32 Cum_Energy_Frict_Brk_TK1 __attribute__ ((packed));
   UINT_32 Cum_Energy_Frict_Brk_TK2 __attribute__ ((packed));
   UINT_32 Cum_Vcu_Alive_Time __attribute__ ((packed));
   UINT_32 Cum_Ms_Swaps_Fault __attribute__ ((packed));
   UINT_32 Cum_Time_In_Emerg __attribute__ ((packed));
   UINT_32 Cum_Time_In_Motion __attribute__ ((packed));

   UINT_32 Int_Odometer_Log __attribute__ ((packed));
   UINT_32 Int_Energy_Con_TK1 __attribute__ ((packed));
   UINT_32 Int_Energy_Con_TK2 __attribute__ ((packed));
   UINT_32 Int_Energy_Con_WS_TK1 __attribute__ ((packed));
   UINT_32 Int_Energy_Con_WS_TK2 __attribute__ ((packed));
   UINT_32 Int_Energy_Regen_TK1 __attribute__ ((packed));
   UINT_32 Int_Energy_Regen_TK2 __attribute__ ((packed));
   UINT_32 Int_Energy_Regen_WS_TK1 __attribute__ ((packed));
   UINT_32 Int_Energy_Regen_WS_TK2 __attribute__ ((packed));
   UINT_32 Int_Energy_NonRegen_TK1 __attribute__ ((packed));
   UINT_32 Int_Energy_NonRegen_TK2 __attribute__ ((packed));
   UINT_32 Int_Energy_NonRegen_WS_TK1 __attribute__ ((packed));
   UINT_32 Int_Energy_NonRegen_WS_TK2 __attribute__ ((packed));
   UINT_32 Int_Energy_Frict_Brk_TK1 __attribute__ ((packed));
   UINT_32 Int_Energy_Frict_Brk_TK2 __attribute__ ((packed));
   UINT_32 Int_Vcu_Alive_Time __attribute__ ((packed));
   UINT_32 Int_Ms_Swaps_Fault __attribute__ ((packed));
   UINT_32 Int_Time_In_Emerg __attribute__ ((packed));
   UINT_32 Int_Time_In_Motion __attribute__ ((packed));
   UINT_32 Int_Energy_Frict_Brk_WS_TK1 __attribute__ ((packed));
   UINT_32 Int_Energy_Frict_Brk_WS_TK2 __attribute__ ((packed));
   UINT_32 Sum_Car_Weight __attribute__ ((packed));
   UINT_32 LW_Odometer __attribute__ ((packed));
   UINT_32 Car_weight_samples __attribute__ ((packed));
   INT_32 mobadLife __attribute__ ((packed));
   UINT_32 storedTime __attribute__ ((packed));
   UINT_32 Int_Time_Power_Tk1 __attribute__ ((packed));
   UINT_32 InT_Time_Brk_Regen_Tk1  __attribute__ ((packed));
   UINT_32 Int_Time_Brk_NonRegen_Tk1  __attribute__ ((packed));
   UINT_32 Int_Time_Power_Tk2 __attribute__ ((packed));
   UINT_32 InT_Time_Brk_Regen_Tk2  __attribute__ ((packed));
   UINT_32 Int_Time_Brk_NonRegen_Tk2  __attribute__ ((packed));	
   
  
   

   UINT_32 bram_end  __attribute__ ((packed)); 
   UINT_16 RTSMonMode  __attribute__ ((packed));
};

struct event_display_nvram{
   UINT_16 BBRAM_EVENT_TABLE_STRUCT[NUMDEFINEDEVENTS] __attribute__ ((packed)) ; 	
};

struct non_const_bat_ram_interface
{
  struct  faultlogqueue_t cc_faultlog [NUMOFEVENTLOGS];  /* Fault Log        */
  struct  datalogqueue_t  cc_datalog  [NUMOFEVENTLOGS];  /* Data Log         */

  /* Hunk #0 : Propulsion Fault Logger */
  UINT_8  EventLogHunk0    [SIZEOF_EVENTLOGHUNK0]  __attribute__ ((packed));       /* Fault data area  */
  UINT_8  DataLogHunk0     [SIZEOF_DATALOGHUNK0]  __attribute__ ((packed));        /* Data log area    */
  UINT_8  DataLogDataHunk0 [SIZEOF_DATALOGDATAHUNK0]  __attribute__ ((packed));    /* Datalog data area*/

  /* Hunk #1 : Engineering Fault Logger */
  UINT_8  EventLogHunk1    [SIZEOF_EVENTLOGHUNK1]  __attribute__ ((packed));       /* Fault data area  */
  UINT_8  DataLogHunk1     [SIZEOF_DATALOGHUNK1]  __attribute__ ((packed));        /* Data log area    */
  UINT_8  DataLogDataHunk1 [SIZEOF_DATALOGDATAHUNK1]  __attribute__ ((packed));    /* Datalog data area*/

  /* Hunk #2 : DCU_FASTMDB_LOGGER Fault Logger */
  UINT_8  EventLogHunk2    [SIZEOF_EVENTLOGHUNK2]  __attribute__ ((packed));       /* Fault data area  */
  UINT_8  DataLogHunk2     [SIZEOF_DATALOGHUNK2]  __attribute__ ((packed));        /* Data log area    */
  UINT_8  DataLogDataHunk2 [SIZEOF_DATALOGDATAHUNK2]  __attribute__ ((packed));    /* Datalog data area*/
#if 0
  /* Hunk #4 : DCU_HCTSMD_LOGGER Fault Logger */
  UINT_8  EventLogHunk4    [SIZEOF_EVENTLOGHUNK4]  __attribute__ ((packed));       /* Fault data area  */
  UINT_8  DataLogHunk4     [SIZEOF_DATALOGHUNK4]  __attribute__ ((packed));        /* Data log area    */
  UINT_8  DataLogDataHunk4 [SIZEOF_DATALOGDATAHUNK4]  __attribute__ ((packed));    /* Datalog data area*/

  /* Hunk #5 : DCU_HCTSMD_LOGGER Fault Logger */
  UINT_8  EventLogHunk5    [SIZEOF_EVENTLOGHUNK5]  __attribute__ ((packed));       /* Fault data area  */
  UINT_8  DataLogHunk5     [SIZEOF_DATALOGHUNK5]  __attribute__ ((packed));        /* Data log area    */
  UINT_8  DataLogDataHunk5 [SIZEOF_DATALOGDATAHUNK5]  __attribute__ ((packed));    /* Datalog data area*/

  /* Hunk #6 : DCU_HCTSMD_LOGGER Fault Logger */
  UINT_8  EventLogHunk6    [SIZEOF_EVENTLOGHUNK6]  __attribute__ ((packed));       /* Fault data area  */
  UINT_8  DataLogHunk6     [SIZEOF_DATALOGHUNK6]  __attribute__ ((packed));        /* Data log area    */
  UINT_8  DataLogDataHunk6 [SIZEOF_DATALOGDATAHUNK6]  __attribute__ ((packed));    /* Datalog data area*/

  /* PSV-ED state table (An entry exists for each PCL) */
  PSV_ED_STATE_TABLE  psv_ed_state_table  __attribute__ ((packed));
#endif

  UINT_32 bram_end  __attribute__ ((packed));                         /* Indicates the end of the BBRAM*/
  UINT_16 dummy1 __attribute__ ((packed));  /* This variable added in order to correct sizing problem in NVRAM init */

};


/* The structure for battery RAM area */
#ifdef TEST_ON_PC
typedef struct
{
  struct non_const_bat_ram_interface non_constant_area  __attribute__ ((packed)); /* Area with values
                                                           periodically
                                                           updated */
} bat_ram_interface;

#else
struct bat_ram_interface
{
  struct non_const_bat_ram_interface non_constant_area  __attribute__ ((packed)); /* Area with values
                                                           periodically
                                                           updated */
};

#endif

#define BBRAM_DATA_SIZE    (sizeof ( struct bat_ram_interface ))


/* External Declarations */
/* AGD pointer to the BBRAM data*/
/* extern struct bat_ram_interface *bat_ram_area; */
extern bat_ram_interface *bat_ram_area;
extern nvram_handle PTU_bbram;
void Read_NVRAM_Segment(nvram_handle, bat_ram_interface*);
void Write_NVRAM_Segment(nvram_handle, bat_ram_interface*);
extern bat_ram_interface ptu_fault_log_buffer;
nvram_handle Init_nvram_segment(const char*, bat_ram_interface*);

void init_nc_logger_bram   ( UINT_16 event );
void Monitor_logger_bbram  (void);
void Check_Event_Data_Size ( void );
void Check_SW_Version      ( void );

#ifndef DAS
extern const struct tBram default_const_bat_ram_area;
#endif


#endif

#ifdef __cplusplus
}
#endif
