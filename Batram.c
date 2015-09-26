/*****************************************************************************
*
* .b
*   Copyright (c) 2000,2001 Bombardier Transportation (Holdings) Inc.
*
*   Project:     Pittsburgh LRV
*
*   File Name:   batram.c
*
*   SubSystem:   VCU
*
*
*   Procedures:  check_event_data_size
*				 Monitor_logger_bbram
*				 init_nc_logger_bram
*
* .b
*
*   History:        
*     03/09/98    Jahnavi Lokre
*       Original Version
*
*   Revised:
*     01/13/2000  S.Taher @ ADtranz
*       Made the following changes while adopting for WMATA
*       requirements:
*       1. Added the bat_ram_area pointer variable
*       2. Declared and define default_const_bat_ram_area and
*          cbram_shadow_area
*
*     10/08/2001 S.Taher @ Bombardier
*       1. Adopted for Pittsburgh LRV.
*       2. Made the following changes are per the code review comments:
*          - Corrected the file header
*          - Used the constant DIA_AVERAGE_WHEEL for the reference wheel
*            diameter instead of a literal. This required the inclusion of
*            the header files cpu_dep.h and sys_def.h.
*
*     12/10/2001 S.Taher @ Bombardier
*       Changed the default value for the reference wheel dia from average to
*       the 
*
*     4/15/2003 R. Cirinelli @ Bombardier
*	    added the functions for monitoring the non constant bbram area used
*       for data logging
*     3/13/2008 Erik Holm
*       Adapted to use the CSS NVRAM Manager. Modified init_nc_logger_bram(),
*       Monitor_logger_bbram(). Created Init_nvram_segment(),
*       Read_NVRAM_Segment(), Write_NVRAM_Segment().
*
*     6/16/2008 Sue Strane @Bombardier
*       Added function Check_SW_Version() which call a function in Rhapsody
*       which allows for checking for a change in the software version and
*       re-initializes the fault NVRAM.  This change was necessary because
*       this was original done when the class cbran in Rhapsody was being built
*       but the new CSS NVRam Manager initializes the NVRAM differently and
*       it was not complete when this was originally being called.  Setting it
*       in the function ptu_init() allows the NVRAM to be fully initialized before
*       this check is made.
*       
*     07/06/2009 Dave Smail @ Bombardier 
*       Added default values for project constant variables
*     
*     10/15/2010 Erik Holm
*       Increased size of PTU buffer caused delays in updating DCU
*       watchdog. NVRAM is now updated piecemeal instead of all at once.
*       Modified Monitor_logger_bbram(), Write_NVRAM_Segment().
*       
*****************************************************************************/
/*  Grab all of the compiler #pragma's.                                     */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef TEST_ON_PC
#include "myWrapper.h"
#else
#include "rts_api.h"
#include "cpu_dep.h"
#endif

#include "batram.h"
#include "version.h"
#include "ptu.h"
#include "ptufltdt.h"

bat_ram_interface *bat_ram_area;
bat_ram_interface ptu_fault_log_buffer;
// OI 253 Intermediate Ptu Fault Log Buffer
bat_ram_interface intermediate_ptu_buffer;
nvram_handle PTU_bbram = NVRAM_ERR_HANDLE;

extern void SWCheck();

const struct tBram default_const_bat_ram_area =
{
  SW_VERSION,         // Software version 
  REF_CAR_ID,         // Car Id           
  {
#ifdef DAS
    CCBRAM_INIT_PTN0,  // Pattern - 0      
    CCBRAM_INIT_PTN1,  // Pattern - 1      
    CCBRAM_INIT_PTN2,  // Pattern - 2      
    CCBRAM_INIT_PTN3,  // Pattern - 3      
#else
    0x000b,
	  0x0c00,
	  0x0d00,
	  0xe000,
#endif
  },
  
  1,        // ref wheel number */ 
  7123,      //ref wheel diameter
  5,        //test_c_var

  {
  //8000,     //default jerk rate limit
  2500,     // default slide timeout (msecs)
  4000,     // default spin timeout (msecs)
  3000,     // default no motion velocity (meters per hour)
  7500,     //default jerk rate limit
  0,        // High performance enable
  72000,    //reduced braking max power speed (rate limited to max power)
  75000,    //reduced braking min power speed (rate limited to 0)
  4500,     //turtle mode max power speed (rate limited to min power)
  5500,     //turtle mode min power speed (rate limited to 0)
  78000,	//forward alarm speed
  80000,	//forward penalty speed
  23000,	//reverse alarm speed
  25000,	//reverse penalty speed
  },
  
  
  0,                  // Checksum         
  {
    0, 0, 0, 0,       // Pad - 4          
    0, 0, 0, 0,      // Pad - 3          
  }
};

/*******************************************************************************
*
* .b
* Procedure Name        : init_nc_logger_bram
*
* Abstract              :
*   This function is called to zero the non-constant battery ram area used for 
*   fault logging
*   
* INPUTS :
*
*   Global Variables :
*       struct bat_ram_interface    bat_ram_area->non_constant_area
*
*   Procedure Parameters :
*       none
*
* OUTPUTS :
*
*   Global Variables :
*       struct bat_ram_interface    bat_ram_area->non_constant_area
*
*   Returned values :
*       none
*
* Functional Description:
*   see abstract
* .b
*
* History               :
*   01/15/93   Linda Taylor
*       Creation
*
* Revised               :
*
* 17 Aug 93 Ashok Bhaskar @ATSI
*    Modified the init of wheel dia
* 27 Oct 93 Linda Clawson
*    Revised for field req'ts
* 12 Oct 98 Todd Campbell
*    Added initialization of the following non constants:
*      dbfb_relay_enable_flag  = 0x00;
*      dbfb_relay_disable_flag = 0xff;
* 24 Nov 1998 Todd Campbell @ Adtranz NA - Pgh, PA
*    Changed initialization of the following non constants for testing ...
*      dbfb_relay_enable_flag  = 0x10;
*      dbfb_relay_disable_flag = 0x36;
* 27 Nov 1998 Todd Campbell @ Adtranz NA - Pgh, PA
*    Removed the initialization of the following non constants ...
*      dbfb_relay_enable_flag
*      dbfb_relay_disable_flag
*
*   01/04/2000 S.Taher @ ADtranz
*       Adopted for WMATA. Made the following changes:
*       1. Changed code to use CSS OS call to zero out the non-constant BBRAM.
*       2. The entire non-constant area is set to zero in this routine
*
*   10/08/2001 S.Taher @ Bombardier
*       Made the following changes as per the code review comments :
*       1. Updated Inputs and Outputs section in the function header.
*
*   03/07/2002 S.Taher @ Bombardier
*       Added the functionality to save the reason for re-initialization
*   4/15/2003 R. Cirinelli @ Bombardier
*       Modified to be used to only initialize non constant memory 
*       used for event and data logging
*   3/13/2008 Erik Holm
*       Adapted to use the CSS NVRAM Manager. Kept the old signature for
*       backward compatibility.
*******************************************************************************/
void init_nc_logger_bram( UINT_16 reason )
{
	int32_t status;

    status = nvram_clear(PTU_bbram);

    InitializeFaultInterface();	 
}

/*******************************************************************************
*
* .b
* Procedure Name        : Monitor_logger_bbram
*
* Abstract              :
*   This function is called to monitor battery ram area used for fault logging
*   
*   
* INPUTS :
*
*   Global Variables :
*       struct bat_ram_interface    bat_ram_area->non_constant_area
*
*   Procedure Parameters :
*       none
*
* OUTPUTS :
*
*   Global Variables :
*       struct bat_ram_interface    bat_ram_area->non_constant_area
*
*   Returned values :
*       none
*
* Functional Description:
*   see abstract
* .b
*
* History               :
*   04/15/03   Rebecca Cirinelli
*       Creation
*
* Revised:
*   3/13/2008 Erik Holm
*       Adapted to use the CSS NVRAM Manager.
*
*   10/15/2010 Erik Holm
*       OI #344. Moved pil_lock_task(), pil_unlock_task() to
*       Write_NVRAM_Segment().
*
*******************************************************************************/
void Monitor_logger_bbram(void)
{
    int32_t dirty;

    dirty = nvram_get_dirty_flag(PTU_bbram);

    if (dirty < 0)
    {
        // Error
    }
    else if (dirty == 1)
    {
        // Dirty
        init_nc_logger_bram(0);
    }

    // Update NVRAM with modified PTU buffer
    Write_NVRAM_Segment(PTU_bbram, &ptu_fault_log_buffer);
}

/*******************************************************************************
*
* .b
* Procedure Name        : Check_Event_Data_Size
*
* Abstract              :
*   This function is called to check the size of the event and datalog arrays 
*
* INPUTS :
*
*   Global Variables :
*       None
*
*   Procedure Parameters :
*       struct const_bat_ram_interface  *const_bat_ram_ptr
*
* OUTPUTS :
*
*   Global Variables :
*       None
*
*   Returned values :
*
* Functional Description:
*   This procedure checks to see if the datalog or event log sizes have changed
*   If the size is different than what is in bbram... the bbram is reinitialized
*
* .b
*
* History               :
*   06/21/2000   B.Cirinelli @ ADtranz
*       Creation
*
* Revised               :
*   10/08/2001 S.Taher @ Bombardier
*       Made the following changes as per the code review comments :
*       1. Updated Inputs and Outputs section in the function header.
*       2. Changes made to check the sizes of the non-constant area only. The
*          version change is eliminated as it is performed by Monitor_bram.
*       3. Called init_ncbram to reinitialize the non-constant area instead
*          reproducing the same code.
*******************************************************************************/
void Check_Event_Data_Size(void)
{
  UINT_16 log_number;
  UINT_16 resize_flag;
  struct non_const_bat_ram_interface  *non_const_bat_ram_ptr; /* Ptr. to the
                                                                 non-constant
                                                                 area */


  /* Assign battery backed ram pointers */
  non_const_bat_ram_ptr = &(bat_ram_area->non_constant_area);
  
  // Must reinitialize the memory if the structure sizes change - 
  // will create code lockups and bus errors if not added 
  /* Verification check on Fault and Datalogger */
 
  resize_flag = FALSE;
  
  for (log_number = 0; log_number < NUMOFEVENTLOGS; log_number++)
  {
    if ( (non_const_bat_ram_ptr->cc_faultlog[log_number].tasks            !=   
                         EventLogDef[log_number].NumberOfTasks           )||               
         (non_const_bat_ram_ptr->cc_faultlog[log_number].eventspertask    !=  
                         EventLogDef[log_number].NumberOfFaultsPerTask   )||         
         (non_const_bat_ram_ptr->cc_faultlog[log_number].maxevents        !=   
                         EventLogDef[log_number].MaxNumOfFaults          )||         
         (non_const_bat_ram_ptr->cc_faultlog[log_number].eventqueuesize   !=   
                         EventLogDef[log_number].SizeOfFaultQueue        )|| 
         (non_const_bat_ram_ptr->cc_datalog[log_number].datarecordingrate != 
                         DataLogDef[log_number].DataRecordingRate        )||
         (non_const_bat_ram_ptr->cc_datalog[log_number].DefaultDownCount  != 
                         DataLogDef[log_number].FaultTripPoint           )||
         (non_const_bat_ram_ptr->cc_datalog[log_number].NumberOfVariables != 
                         DataLogDef[log_number].NumLoggedVariables       )||         
         (non_const_bat_ram_ptr->cc_datalog[log_number].NumberOfSamples   != 
                         DataLogDef[log_number].NumOfDataLogEntries      )||
         (non_const_bat_ram_ptr->cc_datalog[log_number].NumberOfStreams   != 
                         DataLogDef[log_number].NumOfDataLogElements     ) )
    {
      resize_flag = TRUE;
    }
  }


  if (resize_flag == TRUE)
  {
    /* Fault or Data Logger corrupt - re-initialize the non-constant area */
    init_nc_logger_bram( 0 );
  }
}

#ifdef __cplusplus
}
#endif
/*******************************************************************************
*
* .b
* Procedure Name        : Check_SW_Version
*
* Abstract              :
*   This function is called to check for a change in the software version at powerup. 
*
* INPUTS :
*
*   Global Variables :
*       None
*
*   Procedure Parameters :
*       None
*
* OUTPUTS :
*
*   Global Variables :
*       None
*
*   Returned values :
*
* Functional Description:
*   This procedure call a function in Rhapsody which calls the powerup function
*	in the class cbram.  This function will check if the software version has changes 
*   and if so then re-initialize the fault NVRAM.
*
* .b
*
* History               :
*   06/16/2008   Sue Strane
*       Creation
*
* Revised               :
*     
*******************************************************************************/
void Check_SW_Version(void)
{
#ifndef TEST_ON_PC
	SWCheck();
#endif
}

/*******************************************************************************
*
* .b
* Procedure Name        : Init_nvram_segment
*
* Abstract              :
*   This function is called to initialize the non-volatile RAM (NVRAM)
*   
*   
* INPUTS :
*
*   Global Variables :
*       None
*
*   Procedure Parameters :
*       const char*    name
*       bat_ram_interface*  buffer
*
* OUTPUTS :
*
*   Global Variables :
*       None
*
*   Returned values :
*       nvram_handle    handle
*
* Functional Description:
*   The function returns a handle("tag") for a segment of memory in the
*   non-volatile RAM area. This handle is then used for all future
*   access to the segment. First, the function looks to see if a
*   segment is already defined. If so, it re-uses the segment - either as-is
*   or modified for size. Second, if it cannot find an old segment, it
*   creates a new one. Ideally, a new segment should only be created upon
*   the first power-up on a brand new VCU. Going forward, the same segment
*   should be re-used.
* .b
*
* History               :
*   3/13/2008 Erik Holm
*       Creation
*
* Revised:
* 
*
*******************************************************************************/
nvram_handle Init_nvram_segment (const char* name, bat_ram_interface* buffer)
{
#ifndef TEST_ON_PC
    nvram_handle handle = NVRAM_ERR_HANDLE;
	nvram_handle oldHandle;
    nvram_seg_info_t segmentInfo;
	INT32 status;

    // Determine if NVRAM segment is already allocated
    oldHandle = nvram_segment_info(name, &segmentInfo);

    if (oldHandle >= 0)
	{
        // Determine if buffer size has changed
        if (segmentInfo.size != sizeof(bat_ram_interface))
		{
            // Buffer size has changed
            // Reallocate the old segment
            handle = nvram_realloc(oldHandle, 1, sizeof(bat_ram_interface));
            status = nvram_clear(handle);
		}
        else
		{
            // Buffer size is unchanged
            // Continue using old segment
            handle = oldHandle;
		}
	}
    else
	{
        // Segment does not exist
        // Create a new segment
        handle = nvram_malloc(name, 1, sizeof(bat_ram_interface));
	}

    if (!NVRAM_HANDLE_VALID(handle))
	{
	    ae_put(AE_ERROR, AE_ID_NCBBRAM_PTU, "NVRAM segment 'non-constant Bram PTU' is invalid");
    }
	else
	{
	    // NVRAM segment is OK. Fill PTU buffer with NVRAM data.
		// The PTU buffer will be read only once from NVRAM and then modified throughout the entire PTU session.
	    Read_NVRAM_Segment(handle, buffer);
	}

	return (handle);
#else
	return 1;
#endif

}

/*******************************************************************************
*
* .b
* Procedure Name        : Read_NVRAM_Segment
*
* Abstract              :
*   This function is called to read a segment of the non-volatile RAM (NVRAM)
*   
*   
* INPUTS :
*
*   Global Variables :
*       None
*
*   Procedure Parameters :
*       nvram_handle   handle
*       bat_ram_interface  *buffer
*
* OUTPUTS :
*
*   Global Variables :
*       None
*
*   Returned values :
*       None
*
* Functional Description:
*   The function reads the NVRAM segment identified by the handle.
*   The read data is copied into the buffer.
* .b
*
* History               :
*   3/13/2008 Erik Holm
*       Creation
*
* Revised:
* 
*
*******************************************************************************/
void Read_NVRAM_Segment(nvram_handle handle, bat_ram_interface* buffer)
{
    int32_t count;
	UINT32 i;  

	//os_io_printf("intBuffer %d\n",&intermediate_ptu_buffer);


	// OI 253 Read the nvram into the intermediate buffer
    count = nvram_read(handle, (unsigned char *)&intermediate_ptu_buffer, sizeof(bat_ram_interface), 0);

	// OI 253 - Do not copy nvram directly into buffer
    //count = nvram_read(handle, (unsigned char *)buffer, sizeof(bat_ram_interface), 0);

#if 1	
	// Copy all non pointers in intermediate buffer to buffer
	for(i = 0; i < NUMOFEVENTLOGS; i++)
	{
		buffer->non_constant_area.cc_faultlog[i].active = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].active;
		buffer->non_constant_area.cc_faultlog[i].numberoffaults = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].numberoffaults;
		buffer->non_constant_area.cc_faultlog[i].infostart = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].infostart;
		buffer->non_constant_area.cc_faultlog[i].datacursor = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].datacursor;
		buffer->non_constant_area.cc_faultlog[i].wordssaved = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].wordssaved;
		buffer->non_constant_area.cc_faultlog[i].faultindex_msw = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].faultindex_msw;
		buffer->non_constant_area.cc_faultlog[i].faultindex_lsw = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].faultindex_lsw;
		buffer->non_constant_area.cc_faultlog[i].tasks = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].tasks;
		buffer->non_constant_area.cc_faultlog[i].eventspertask = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].eventspertask;
		buffer->non_constant_area.cc_faultlog[i].maxevents = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].maxevents;
		buffer->non_constant_area.cc_faultlog[i].eventqueuesize = intermediate_ptu_buffer.non_constant_area.cc_faultlog[i].eventqueuesize;

		buffer->non_constant_area.cc_datalog[i].datarecordingrate = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].datarecordingrate;
		buffer->non_constant_area.cc_datalog[i].downcount = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].downcount;
		buffer->non_constant_area.cc_datalog[i].tripqueue = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].tripqueue;
		buffer->non_constant_area.cc_datalog[i].datalogtrip = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].datalogtrip;
		buffer->non_constant_area.cc_datalog[i].currentqueue = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].currentqueue;
		buffer->non_constant_area.cc_datalog[i].Enabled = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].Enabled;
		buffer->non_constant_area.cc_datalog[i].DefaultDownCount = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].DefaultDownCount;
		buffer->non_constant_area.cc_datalog[i].DefaultSampleRate = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].DefaultSampleRate;
		buffer->non_constant_area.cc_datalog[i].NumberOfVariables = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].NumberOfVariables;
		buffer->non_constant_area.cc_datalog[i].NumberOfSamples = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].NumberOfSamples;
		buffer->non_constant_area.cc_datalog[i].NumberOfStreams = intermediate_ptu_buffer.non_constant_area.cc_datalog[i].NumberOfStreams;

	}

	for(i=0; i < SIZEOF_EVENTLOGHUNK0; i++)
	{
		buffer->non_constant_area.EventLogHunk0[i] = intermediate_ptu_buffer.non_constant_area.EventLogHunk0[i];
	}

	for(i=0; i < SIZEOF_DATALOGHUNK0; i++)
	{
		buffer->non_constant_area.DataLogHunk0[i] = intermediate_ptu_buffer.non_constant_area.DataLogHunk0[i];
	}

	for(i=0; i < SIZEOF_DATALOGDATAHUNK0; i++)
	{
		buffer->non_constant_area.DataLogDataHunk0[i] = intermediate_ptu_buffer.non_constant_area.DataLogDataHunk0[i];
	}

	for(i=0; i < SIZEOF_EVENTLOGHUNK1; i++)
	{
		buffer->non_constant_area.EventLogHunk1[i] = intermediate_ptu_buffer.non_constant_area.EventLogHunk1[i];
	}

	for(i=0; i < SIZEOF_DATALOGHUNK1; i++)
	{
		buffer->non_constant_area.DataLogHunk1[i] = intermediate_ptu_buffer.non_constant_area.DataLogHunk1[i];
	}

	for(i=0; i < SIZEOF_DATALOGDATAHUNK1; i++)
	{
		buffer->non_constant_area.DataLogDataHunk1[i] = intermediate_ptu_buffer.non_constant_area.DataLogDataHunk1[i];
	}

	for(i=0; i < SIZEOF_EVENTLOGHUNK2; i++)
	{
		buffer->non_constant_area.EventLogHunk2[i] = intermediate_ptu_buffer.non_constant_area.EventLogHunk2[i];
	}

	for(i=0; i < SIZEOF_DATALOGHUNK2; i++)
	{
		buffer->non_constant_area.DataLogHunk2[i] = intermediate_ptu_buffer.non_constant_area.DataLogHunk2[i];
	}

	for(i=0; i < SIZEOF_DATALOGDATAHUNK2; i++)
	{
		buffer->non_constant_area.DataLogDataHunk2[i] = intermediate_ptu_buffer.non_constant_area.DataLogDataHunk2[i];
	}

#if 0
	for(i=0; i < SIZEOF_EVENTLOGHUNK4; i++)
	{
		buffer->non_constant_area.EventLogHunk4[i] = intermediate_ptu_buffer.non_constant_area.EventLogHunk4[i];
	}

	for(i=0; i < SIZEOF_DATALOGHUNK4; i++)
	{
		buffer->non_constant_area.DataLogHunk4[i] = intermediate_ptu_buffer.non_constant_area.DataLogHunk4[i];
	}

	for(i=0; i < SIZEOF_DATALOGDATAHUNK4; i++)
	{
		buffer->non_constant_area.DataLogDataHunk4[i] = intermediate_ptu_buffer.non_constant_area.DataLogDataHunk4[i];
	}

	for(i=0; i < SIZEOF_EVENTLOGHUNK5; i++)
	{
		buffer->non_constant_area.EventLogHunk5[i] = intermediate_ptu_buffer.non_constant_area.EventLogHunk5[i];
	}

	for(i=0; i < SIZEOF_DATALOGHUNK5; i++)
	{
		buffer->non_constant_area.DataLogHunk5[i] = intermediate_ptu_buffer.non_constant_area.DataLogHunk5[i];
	}

	for(i=0; i < SIZEOF_DATALOGDATAHUNK5; i++)
	{
		buffer->non_constant_area.DataLogDataHunk5[i] = intermediate_ptu_buffer.non_constant_area.DataLogDataHunk5[i];
	}

	for(i=0; i < SIZEOF_EVENTLOGHUNK6; i++)
	{
		buffer->non_constant_area.EventLogHunk6[i] = intermediate_ptu_buffer.non_constant_area.EventLogHunk6[i];
	}

	for(i=0; i < SIZEOF_DATALOGHUNK6; i++)
	{
		buffer->non_constant_area.DataLogHunk6[i] = intermediate_ptu_buffer.non_constant_area.DataLogHunk6[i];
	}

	for(i=0; i < SIZEOF_DATALOGDATAHUNK6; i++)
	{
		buffer->non_constant_area.DataLogDataHunk6[i] = intermediate_ptu_buffer.non_constant_area.DataLogDataHunk6[i];
	}

#endif

	buffer->non_constant_area.bram_end = intermediate_ptu_buffer.non_constant_area.bram_end;

#endif
	

    if (count < 0)
    {
        // Error
    }
    else if (count < sizeof(bat_ram_interface))
    {
       // Incomplete
    }
}

/*******************************************************************************
*
* .b
* Procedure Name        : Write_NVRAM_Segment
*
* Abstract              :
*   This function is called to write a segment of the non-volatile RAM (NVRAM)
*   
*   
* INPUTS :
*
*   Global Variables :
*       None
*
*   Procedure Parameters :
*       nvram_handle   handle
*       bat_ram_interface  *buffer
*
* OUTPUTS :
*
*   Global Variables :
*       None
*
*   Returned values :
*       None
*
* Functional Description:
*   The function writes the NVRAM segment identified by the handle.
*   The data to be written is copied into the buffer.
* .b
*
* History               :
*   3/13/2008 Erik Holm
*       Creation
*
* Revised:
* 
*   10/15/2010 Erik Holm
*       Added piecemeal updating of PTU buffer in MVRAM. The
*       function writes SIZE_OF_NVRAM_BLOCK number of bytes into NVRAM
*       each cycle. Then it waits to allow other system process a chance
*       to execute in a timely fashion before proceeding with the next block
*       of data. This repeats until the entire PTU buffer has been written into
*       NVRAM.
*******************************************************************************/
void Write_NVRAM_Segment(nvram_handle handle, bat_ram_interface* buffer)
{
    int32_t count = 0;

	int32_t offset = 0;
	size_t bufferSize = 0;
	size_t remainder = 0;
	UINT_32 ptr = 0;
	UINT_16 numOfFullBlocks = 0;
	UINT_16 i = 0;

	// The size of the entire PTU buffer
	bufferSize = sizeof(bat_ram_interface);

	// Divide the buffer into a number of whole, full blocks
	numOfFullBlocks = bufferSize / SIZE_OF_NVRAM_BLOCK;

	// Determine the size of the remainder, i.e. the fraction of a full
	// block at the tail of the PTU buffer
	remainder = bufferSize % SIZE_OF_NVRAM_BLOCK;

	// Write one full block at a time to allow other system processes to execute
	// in a timely fashion.
	offset = 0;
	for (i = 0; i < numOfFullBlocks; i++)
	{
#ifdef TEST_ON_PC
		ptr = (UINT_32)buffer + (UINT_32)offset;
    	count = nvram_write(handle, (unsigned char*)ptr, SIZE_OF_NVRAM_BLOCK, offset);
		offset += SIZE_OF_NVRAM_BLOCK;
#else
		ptr = (UINT_32)buffer + (UINT_32)offset;
		pil_lock_task();
    	count = nvram_write(handle, (unsigned char*)ptr, SIZE_OF_NVRAM_BLOCK, offset);
		pil_unlock_task();
		offset += SIZE_OF_NVRAM_BLOCK;
		os_t_delay(NVRAM_BLOCK_WRITE_TIME_DELAY);
#endif
	}

	// If there is a remainder, then write the remainder last
	if (remainder > 0)
	{
#ifdef TEST_ON_PC
		ptr = (UINT_32)buffer + (UINT_32)offset;
   		count = nvram_write(handle, (unsigned char *)ptr, remainder, offset);
#else
		ptr = (UINT_32)buffer + (UINT_32)offset;
		pil_lock_task();
   		count = nvram_write(handle, (unsigned char *)ptr, remainder, offset);
		pil_unlock_task();
#endif
	}

}
