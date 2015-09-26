/*************************************************************************
*
* .b
*   Copyright (c) 1996 ABB Daimler-Benz Transportation (North America) Inc.
*
*   Project :
*               Common
*
*   File Name :
*               ptufault.c
*
*   Subsystem :
*               PTU
*
*   Procedures :
*               InitializeFaultInterface
*               ChangeEventLog
*               InitializeFaultLogger
*               ExtendedLogFault
*               GetFaultSize
*               GetFaultStructure
*               GetNewestFaultIndex
*               GetOldestFaultIndex
*               SetFaultTable
*               SetTriggerTable
*               SetFaultLogger
*               GetEventEnableFlags
*               GetEventTriggerFlags
*               GetDynamicFaultHistory
*               GetStaticFaultHistory
*               PurgeFaultLogger
*               PurgeDynamicHistory
*               PurgeFaultLogNumber
*               PurgeDataLogNumber
*
*   EPROM Drawing   5624B95
*
* .b
*
*   History :   11/21/91    J. Lyon - Creation
*   Revised :   02/07/92    JSL
*               - Added fault history counters for the PTU
*               02/08/92    JSL
*                - Modified fault.c to dfault.c by linking a data logger
*               04/05/94    DDP @ ATSI
*               - integrated all jobs to have one source.
*               - cleaned up comments and code.
*               10/06/95    DDP @ ATSI
*               - Modified for handling multiple fault and data logs
*               10/19/95    DDP @ ATSI
*               - Added InitializeFaultInterface()
*               02/20/96    DDP @ Adtranz
*               - Changed GetFaultStructure()
*               02/20/96    DDP @ Adtranz
*               - Changed ChangeEventLog()
*               03/28/96    DDP @ Adtranz
*               - Added check in all functions for NULL fault log pointer
*               11/19/1999  S.Taher @ ADtranz
*               - Made the following modifications while moving the fault
*                 log and the data log to the BBRAM :
*                 1. Included batram.h
*                 2. Deleted the external declarations for cc_datalog and
*                    cc_datalog
*                 3. Modified following routines. See function header for
*                    details :
*                    - InitializeFaultInterface
*                    - ChangeEventLog
*                    - InitializeFaultLogger
*                    - LogFault
*               06/07/2000  D.Schnewlin @ Adtranz
*               - Renamed function from LogFault() to ExtendedLogFault().
*				02/27/2003 R. Cirinelli @ Bombarder
*				- Added initialization of log 4,5,6 and deleted 3
*           06/17/2003  John Novacek @ Bombardier Transportation
*	         - Merged in updates made for Pitt LRV.
*           02/06/2006  Amadou Diop @ Bombardier Transportation
*			 - Adapted TDSL for DFW project 
*************************************************************************/
/*  Grab all of the compiler #pragma's.                                     */
#ifdef __cplusplus
extern "C" {
#endif

/* Grab all the project specific information */

/* Grab all the application specific information */
#include "stdio.h"

/* Grab all the PTU specific information */
#include "ptuprj.h"
#include "fltinfo.h"
#include "ptu.h"
#include "batram.h"
#include "ptulogger.h"

/* Externs */
extern const struct EventLogDef_t           EventLogDef[];


/* Local Function Prototypes */
UINT_32 GetFaultIndex                   (struct faultlogqueue_t *, UINT_16);
struct minfaultpacket_t *GetFaultPointer(struct faultlogqueue_t *, UINT_32);
UINT_8  GetFaultHeader                  (struct faultlogqueue_t *, UINT_32,
										 struct minfaultpacket_t *);
UINT_8  InsertFaultHeader               (struct faultlogqueue_t *, UINT_32,
										 struct minfaultpacket_t *);
/* Temporarily added by JJN on 9-7-00 */
extern UINT_16 XU_DcLkAdc1;
extern UINT_16 WU_DcLkBrCp_Mod;
extern UINT_16 XI_DcLk;
extern UINT_16 XN_RxSx_Avg;
extern UINT_16 WM_Mt;
extern UINT_16 WM_MtLimStb;
extern UINT_16 XM_TrBr_Sel;
extern UINT_16 WN_RxLimStb;
extern UINT_16 WY_MtRmp;
extern UINT_16 XY_SxSxoAp;
extern UINT_16 W_ModNdx_Abs;
extern UINT_16 FX_ModeNoV;
extern UINT_16 XI_ErrRfoIm;
extern UINT_16 WU_DcLkBrCp;
extern UINT_16 XX_BrCpDcy;
extern UINT_16 X_Clim_Min;
extern UINT_16 S_Fb0;
extern UINT_16 Log_Status_1;
extern UINT_16 Log_Status_2;
extern UINT_16 Log_Status_3;

/************************************************************************
*
* .b
*
*   Procedure Name :    InitializeFaultInterface
*
*   Abstract :
*               Initializes all Event and Data Logs
*
*   Inputs :
*       Global :    None
*
*       Constants :
*               NUMOFEVENTLOGS        Number of Event Logs for this job
*
*       Parameters : None
*
*   Outputs :
*       Global :
*                   CurrentEventLog
*                   bat_ram_area->non_constant_area.cc_faultlog[]
*                   bat_ram_area->non_constant_area.cc_datalog[]
*
*       Parameters :
*
*       Returned :  None
*
*   Functional Description :
*
* .b
*
*   History :   10/19/95    D. Pradhan Creation
*   Revised :
*               11/19/1999  S.Taher @ ADtranz
*               - Made the following modifications while moving the fault
*                 log and the data log to the BBRAM :
*                 1. Changed the parameters in the call to the
*                    InitializeFaultLogger and InitializeDataLogger to the
*                    fault log and the data log located in BBRAM.
*
*************************************************************************/
void InitializeFaultInterface()
{
	UINT_16 Counter;

	for (Counter = 0; Counter < NUMOFEVENTLOGS; Counter++)
	{
		CurrentEventLog = Counter;
		InitializeFaultLogger(
       &(bat_ram_area->non_constant_area.cc_faultlog[Counter]),
       &(bat_ram_area->non_constant_area.cc_datalog[Counter] ) );
		InitializeDataLogger (
       &(bat_ram_area->non_constant_area.cc_datalog[Counter]) );
	}


	CurrentEventLog = 0;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    ChangeEventLog
*
*   Abstract :
*
*   Inputs :
*       Global :    None
*
*       Constants :
*
*       Parameters :
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :  None
*
*   Functional Description :
*
*
* .b
*
*   History :   10/05/95    Dev Pradhan @ ATSI Created
*   Revised :   03/08/96    Dev Pradhan @ Adtranz
*               - Passing the Data Recording Rate for the Data Logger
*                 back to WPTU
*               11/19/1999  S.Taher @ ADtranz
*               - Made the following modifications while moving the fault
*                 log and the data log to the BBRAM :
*                 1. Changed the parameters in the call to the
*                    InitializeFaultLogger and InitializeDataLogger to the
*                    fault log and the data log located in BBRAM.
*
*************************************************************************/
void ChangeEventLog(UINT_16 EventLogNumber, UINT_16 *ChangeStatus,
					UINT_16 *DataRecordRate, UINT_16 *MaxNumberOfTasks,
					UINT_16 *MaxNumberOfEvents)
{
	if (EventLogNumber < NUMOFEVENTLOGS)
	{
		/* Change request is legal */
		CurrentEventLog     = EventLogNumber;
		*ChangeStatus       = TRUE;
	}
	else
	{
		/* Change could not be made */
		*ChangeStatus = FALSE;
	}

	GlobalDataLog       =
              &(bat_ram_area->non_constant_area.cc_datalog[CurrentEventLog]);
	GlobalFaultLog      =
              &(bat_ram_area->non_constant_area.cc_faultlog[CurrentEventLog]);
	*DataRecordRate     = GlobalDataLog->datarecordingrate;
	*MaxNumberOfTasks   = GlobalFaultLog->tasks;
	*MaxNumberOfEvents  = GlobalFaultLog->eventspertask;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    InitializeFaultLogger
*
*   Abstract :
*               Initializes members in the fault log structure
*               passed to it to create an empty fault log
*               queue linked with a given data logger.
*
*   Inputs :
*       Global :    None
*
*       Constants :
*               SIZEOFFAULTQUEUE    size in bytes of the fault log queue
*
*
*               MAXNUMOFFAULTS      maximum number of faults
*                                   that may be saved on the
*                                   fault queue at any given
*                                   time
*
*       Parameters :
*               eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be initialized
*
*               passedlogger struct datalogqueue_t *
*                       pointer to the data logger to
*                       be linked with this fault
*                       logger
*
*   Outputs :
*       Global :    None
*
*       Parameters :
*                   eventlogger initialized to a empty fault logger
*
*
*       Returned :  TRUE if successfull, FALSE if not
*
*   Functional Description :
*               InitializeFaultLogger sets all of the necessary
*               variables in the passed fault log queue to
*               values indicating an empty fault logger.  The
*               passed fault logger is also linked with the
*               passed datalogger.  This procedure should
*               always be called before using a fault log
*               queue.
*
* .b
*
*   History :   11/21/91    J. Lyon Creation
*   Revised :   02/08/92    Added data logger link - JSL
*               10/06/95    D. Pradhan @ATSI
*               - Modified to handle multiple fault and data logs.
*               03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*               11/19/1999  S.Taher @ ADtranz
*               - Made the following modifications while moving the fault
*                 log and the data log to the BBRAM :
*                 1. Changed the variable 'pointer' to point to the
*                    EventLogHunk located in BBRAM.
*				02/27/2003 R. Cirinelli @ Bombarder
*				- Added initialization of log 4,5,6 and deleted 3
*
*************************************************************************/
UINT_8 InitializeFaultLogger(   struct faultlogqueue_t  *eventlogger,
								struct datalogqueue_t   *passedlogger)
{
	UINT_16 counter;
	UINT_8  *pointer;
	UINT_16 tablesize;

	if (eventlogger == NULL) return FALSE;

	/*  Initialize all values to indicated an empty fault logger.   */
	eventlogger->numberoffaults = 0;
	eventlogger->wordssaved     = 0;
	eventlogger->faultindex_msw = 0;
	eventlogger->faultindex_lsw = 0;
	eventlogger->infostart      = 0;
	eventlogger->datacursor     = 0;

	/*  Link this fault logger with the passed data logger.     */
	eventlogger->linkedlogger = passedlogger;

	eventlogger->tasks          = EventLogDef[CurrentEventLog].NumberOfTasks;
	eventlogger->eventspertask  = EventLogDef[CurrentEventLog].NumberOfFaultsPerTask;
	eventlogger->maxevents      = EventLogDef[CurrentEventLog].MaxNumOfFaults;
	eventlogger->eventqueuesize = EventLogDef[CurrentEventLog].SizeOfFaultQueue;

	switch( CurrentEventLog )
    {
        case 0  : pointer = bat_ram_area->non_constant_area.EventLogHunk0; break;
        case 1  : pointer = bat_ram_area->non_constant_area.EventLogHunk1; break;
        case 2  : pointer = bat_ram_area->non_constant_area.EventLogHunk2; break;
		/*case 3  : pointer = bat_ram_area->non_constant_area.EventLogHunk4; break;
		case 4  : pointer = bat_ram_area->non_constant_area.EventLogHunk5; break;
		case 5  : pointer = bat_ram_area->non_constant_area.EventLogHunk6; break;*/
        default : return FALSE;
    }
	eventlogger->triggertable = (UINT_16 *)pointer;

	/* Force table to be on even boundary */
	if ((eventlogger->tasks * eventlogger->eventspertask) % 8)
		pointer += ((eventlogger->tasks * eventlogger->eventspertask) / 8) + 1;
	else
		pointer += ((eventlogger->tasks * eventlogger->eventspertask) / 8);

	eventlogger->faulttable = (UINT_16 *)pointer;

	/* Force table to be on even boundary */
	if ((eventlogger->tasks * eventlogger->eventspertask) % 8)
		pointer += ((eventlogger->tasks * eventlogger->eventspertask) / 8) + 1;
	else
		pointer += ((eventlogger->tasks * eventlogger->eventspertask) / 8);

	eventlogger->statichistory = (UINT_16 *)pointer;

	pointer += eventlogger->tasks * eventlogger->eventspertask * 2;
	eventlogger->dynamichistory = (UINT_16 *)pointer;

	pointer += eventlogger->tasks * eventlogger->eventspertask * 2;
	eventlogger->faultinfo = (struct faultpacketdef_t *)pointer;

	pointer += eventlogger->maxevents * sizeof(struct faultpacketdef_t);
	eventlogger->faultqueue = (UINT_16 *)pointer;

	/* Figure out the Table Size */
	if ((eventlogger->tasks * eventlogger->eventspertask) % 16)
		tablesize = ((eventlogger->tasks * eventlogger->eventspertask) / 16) + 1;
	else
		tablesize = (eventlogger->tasks * eventlogger->eventspertask) / 16;

	/*  Set all of the entries in the fault table */
	/*  Reset all of the entries in the trigger table */
	for (counter = 0; counter < tablesize; counter++)
	{
		/*  Enable ALL 16 fault flags */
		eventlogger->faulttable[counter] = 0xFFFF;

		/*  Disable ALL data log trip for these 16 faults */
		eventlogger->triggertable[counter] = 0x0000;
	}

	/*  Set all of the entries in the history counters to 0. */
	for (counter = 0;
		 counter < eventlogger->tasks * eventlogger->eventspertask;
		 counter++)
	{
		/*  Set the dynamic and static history counter for this fault to 0 */
		eventlogger->statichistory[counter]  = 0;
		eventlogger->dynamichistory[counter] = 0;
	}

	/*  Enable the passed fault logger */
	eventlogger->active = TRUE;

	/*  Enable a default stream dumps */
	SetupStreamDump(eventlogger);

    /* Clear corresponding PSV-ED state table */
  // Commented out - awating functionality integration
//psv_ed_clear_state_table( CurrentEventLog );

	/*  All done, return TRUE indicating success */
	return TRUE;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    ExtendedLogFault (LogFault & LogTdsFault)
*
*   Abstract :
*               Logs a fault onto the fault log queue.  Returns
*               TRUE is successful, FALSE if not.
*
*   Inputs :
*       Global :    None
*
*       Constants :
*               SIZEOFFAULTQUEUE    size in bytes of the
*                                   fault log queue
*
*               MAXNUMOFFAULTS      maximum number of faults
*                                   that may be saved on the
*                                   fault queue at any given
*                                   time
*
*       Parameters :
*               EventLogToLogTo     UINT_16
*                       Event Log ID of Datalog to be used
*
*               passedfault struct minfaultpacket_t *
*                       pointer to the fault that is to
*                       be logged
*
*               faultsize   UINT_16
*                       size of the fault that is to be
*                       logged
*
*               tdsSpecific  UINT_8
*                       activate TDS specific options
*
*   Outputs :
*       Global :    None
*
*       Parameters :    eventlogger has new fault logged onto it
*
*       Returned :  TRUE if successfull, FALSE if not
*
*   Functional Description :
*               ExtendedLogFault will to see if the passed fault queue
*               is active and if the passed fault can be
*               logged.  If not, FALSE will be returned.
*               Otherwise, it will check to see if there is
*               any room for the passed fault on the passed
*               fault log queue.  If not, ExtendedLogFault will delete
*               older faults until enough resources have been
*               de-allocated.  The fault will then be copied
*               onto the fault log queue with an information
*               record initialized and assigned to  it.  If
*               ExtendedLogFault was successful, TRUE will be returned,
*               FALSE if not.
*               Note:   When option "tdsSpecific" is set, then time
*                       stamp in fault header is not overwritten
*                       and the data logger is always triggered, i.e.
*                       independent from the flag in the triggertable.
*
* .b
*
*   History :   01/30/91    J. Lyon Creation
*   Revised :
*               03/26/94    Ajay Mishra @ ATSI
*                           - Global fault variables are initialized
*               04/05/95    D. Pradhan @ ATSI
*                           - Added call to LoadFaultHeader()
*               04/11/95    D. Pradhan @ ATSI
*                           - Added calls to StopScheduling() &
*                             StartScheduling()
*               03/28/96    DDP @ Adtranz
*                           - Added check for NULL fault log pointer
*               11/19/1999  S.Taher @ ADtranz
*               - Made the following modifications while moving the fault
*                 log and the data log to the BBRAM :
*                 1. Changed the initialization of the variable 'eventlogger'
*                    to point to the cc_faultlog created in the BBRAM.
*               06/09/2000  D.Schnewlin @ Adtranz
*               - Renamed function from LogFault() to ExtendedLogFault().
*               - Added input parameter tdsSpecific
*               - Adapted code for TDS specific use
*               - Introduced check of loggerid and faultid
*************************************************************************/
UINT_8 ExtendedLogFault(UINT_16                 EventLogToLogTo,
				        struct minfaultpacket_t *passedfault,
				        UINT_16                 faultsize,
                        UINT_8                  tdsSpecific)
{
	UINT_16                 wordcounter;
	UINT_16                 infocursor;
	UINT_16                 FaultSizeInWords;
	struct faultlogqueue_t  *eventlogger;
	UINT_16                 Index;
	UINT_16                 theBit;
    

	if (EventLogToLogTo >= NUMOFEVENTLOGS)
		return FALSE;

	eventlogger = &(bat_ram_area->non_constant_area.cc_faultlog[EventLogToLogTo]);
	
	if (eventlogger == NULL)
   	return FALSE;


	/*  If loggerid or faultid are invalid return FALSE. */
    if (passedfault->loggerid > EventLogDef[EventLogToLogTo].NumberOfTasks ||
	    passedfault->faultid > EventLogDef[EventLogToLogTo].NumberOfFaultsPerTask)
		return FALSE;

	/*  If the passed fault logger is not active return FALSE. */
	if (eventlogger->active != TRUE)
		return FALSE;

	/*  If the passed fault type is not enabled in the fault table */
	/*  return FALSE.                                              */
	Index = (passedfault->loggerid * eventlogger->eventspertask) +
			passedfault->faultid;
	theBit = 0x0001;
	theBit = theBit << Index % 16;
	if ( !(eventlogger->faulttable[Index / 16] & theBit) )
		return FALSE;

	/*  Check to see if the passed fault will physically fit on the */
	/*  fault log queue.  Return FALSE if not.                      */
	if (faultsize > eventlogger->eventqueuesize)
		return FALSE;

	/* Following functions must not be interrupted */
	StopScheduling();

	/*  Increment the dynamic history counter for this fault type.  */
	(eventlogger->dynamichistory[Index])++;

	/*  Load the header belonging to passedfault with the appropiate    */
	/*  values, including the fault index and fault time.  Increment    */
	/*  the fault index.                                                */
	if (++eventlogger->faultindex_lsw == 0)
		eventlogger->faultindex_msw++;

	passedfault->index = (UINT_32)
			((UINT_32)(eventlogger->faultindex_msw << 16) |
			eventlogger->faultindex_lsw);

    /*  Load global fault header. Set up time as well unless this call  */
    /*  is TDS specific.                                                */

	if (!tdsSpecific)
        LoadFaultHeader(passedfault);
    else
        LoadFaultHeaderWithoutTime(passedfault);

	/* Check to see if a Datalog Flag was set for this fault or if this */
    /* is a TDS specific call and if so, trigger data logger            */
	if (eventlogger->triggertable[Index / 16] & theBit || tdsSpecific)
		passedfault->DataLogNumber =
            TriggerDataLogger(eventlogger->linkedlogger, eventlogger);
	else
		passedfault->DataLogNumber = 0xffff;


	/*  Check to see if there is enough memory to save this fault       */
	/*  without overwriting an older fault.  If not, delete the oldest  */
	/*  fault and check again.  Continue to do this until there is      */
	/*  enough memory for this fault in the faultqueue.                 */
	while ( ((eventlogger->wordssaved * 2) + faultsize >
			 eventlogger->eventqueuesize) ||
			(eventlogger->numberoffaults > eventlogger->maxevents - 1)
		  )
	{

		/*  The oldest fault must be deleted to make room for this fault. */
		/*  Subtract the size of the oldest fault from the bytessaved     */
		/*  counter and increment the infostart counter to delete the     */
		/*  oldest fault.                                                 */
		eventlogger->wordssaved -=
		  eventlogger->faultinfo[eventlogger->infostart].size;

		/* If the fault that is being overwritten has a DataLog tripped then */
		/* clear the pointer to this fault in that DataLog */
		PurgeFaultLogNumber(eventlogger);

		eventlogger->infostart++;

		/*  If we ran off the end of the world when incrementing */
		/*  infostart, reset it to 0.                            */
		if (eventlogger->infostart > (eventlogger->maxevents - 1))
			eventlogger->infostart = 0;

		/*  Since there is one less fault in the faultqueue, decrement the  */
		/*  numberoffaults counter.                                         */
		eventlogger->numberoffaults--;
	}

	/*  Now that we have enough resources to log the fault, load the    */
	/*  next unused faultinfo structure with the fault information and  */
	/*  copy the fault onto the faultqueue.                             */
	infocursor = eventlogger->infostart + eventlogger->numberoffaults;
	if (infocursor > (eventlogger->maxevents - 1))
		infocursor -= eventlogger->maxevents;

	FaultSizeInWords = (faultsize % 2) ? (faultsize / 2 + 1) : (faultsize / 2);
	eventlogger->faultinfo[infocursor].location = eventlogger->datacursor;
	eventlogger->faultinfo[infocursor].index.Words.Word0 =
		(UINT_16)(passedfault->index & 0x0000ffffl);
	eventlogger->faultinfo[infocursor].index.Words.Word1 =
		(UINT_16)((passedfault->index & 0xffff0000l) >> 16);
	eventlogger->faultinfo[infocursor].size = FaultSizeInWords;

	/* Update the Datalog structure to have the Datalog Element that */
	/* is logging data for this fault know which Fault it corresponds to */
	if (passedfault->DataLogNumber <
		eventlogger->linkedlogger->NumberOfStreams)
	{
		eventlogger->linkedlogger->faulthook[passedfault->DataLogNumber] =
												infocursor;
	}

	for (wordcounter = 0; wordcounter < FaultSizeInWords; wordcounter++)
	{
		eventlogger->faultqueue[eventlogger->datacursor++] =
			*((UINT_16 *)passedfault + wordcounter);

		/*  If the datacursor was incremented off the end of the world, */
		/*  reset it to 0.                                              */
		if (eventlogger->datacursor > (eventlogger->eventqueuesize / 2) - 1)
			eventlogger->datacursor = 0;
	}

	/* Add the size of this fault onto the bytessaved counter. */
	eventlogger->wordssaved += eventlogger->faultinfo[infocursor].size;

	/* Increment the numberoffaults counter. */
	eventlogger->numberoffaults++;

	/*  All done, no errors by default. */
	StartScheduling();

	return TRUE;
}

/* Provide original function 'LogFault' for modules "tachss.c"
   and "mot_misc.c", which do not use interfacefile "ptu.h" !!! */
#undef LogFault
UINT_8 LogFault(UINT_16                 EventLogToLogTo,
				struct minfaultpacket_t *passedfault,
				UINT_16                 faultsize)
{
    ExtendedLogFault(EventLogToLogTo,passedfault,faultsize, FALSE);

	return TRUE;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    GetFaultSize
*
*   Abstract :
*               Returns the size of the fault identified by
*               the passed index if that fault exists on the
*               fault log queue, FALSE if not.
*
*   Inputs :
*       Global :    None
*
*       Constants :
*               MAXNUMOFFAULTS  maximum number of faults
*                               that may be saved on the
*                               fault queue at any given
*                               time
*
*       Parameters :
*               eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be initialized
*               faultindex  UINT_32
*                       index of the fault whose size is
*                       to be returned
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :
*               size of the fault identified by passed
*               faultindex if found on the fault log queue,
*               FALSE if not
*
*   Functional Description :
*               GetFaultSize will page through the fault log
*               queue passed to it until it finds a fault whose
*               index matches passed faultindex or until to end
*               of the fault log queue has been reached.  If the
*               correct fault was found to exist on the fault
*               log queue, its size will be returned.  If the
*               correct fault was not found, FALSE will be
*               returned.
*
* .b
*
*   History :   11/21/91    J. Lyon Creation
*   Revised :   03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_16 GetFaultSize(   struct faultlogqueue_t  *eventlogger,
						UINT_32                 faultindex)
{
	UINT_16 infocursor;
	UINT_16 faultcounter;

	if (eventlogger == NULL) return FALSE;

	/*  Initialize all of the locals. */
	infocursor = eventlogger->infostart;
	faultcounter = 0;

	/*  Page through the fault log queue until the correct fault has    */
	/*  been found or the end of the fault log queue has been reached.  */
	while ((GetFaultIndex(eventlogger, infocursor++) != faultindex) &&
		   (faultcounter++ < eventlogger->numberoffaults))

	/*  If we incremented off the end of the fault log queue, reset */
	/*  infocursor to the beginning of the fault log queue.     */
		if (infocursor > (eventlogger->maxevents - 1))
			infocursor -= eventlogger->maxevents;

	/*  If the correct fault was found, return its size...      */
	if (GetFaultIndex(eventlogger, --infocursor) == faultindex)
		return (eventlogger->faultinfo[infocursor].size * 2);

	/*  ...otherwise, return FALSE.                 */
	else
		return FALSE;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    GetFaultStructure
*
*   Abstract :
*               Copies the fault identified by the passed
*               index if that fault exists on the fault log
*               queue. Returns TRUE if successful, FALSE if not.
*
*   Inputs :
*       Global :    None
*
*       Constants : MAXNUMOFFAULTS  maximum number of faults
*                           that may be saved on the
*                           fault queue at any given
*                           time
*
*       Parameters :
*               eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be initialized
*               faultindex  UINT_32
*                       index of the fault that is to be
*                       copied
*               faultstruct struct minfaultpacket_t
*                       buffer that the fault structure
*                       is to be copied into
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :
*               TRUE if the fault was found on the fault log
*               queue and successfuly copied to the pass buffer,
*               FALSE if not
*
*   Functional Description :
*               GetFaultSize will page through the fault log
*               queue passed to it until it finds a fault whose
*               index matches passed faultindex or until to end
*               of the fault log queue has been reached.  If the
*               correct fault was found on the fault log queue,
*               a copy if transfered into the area pointed to by
*               passed faultbuffer.  If the correct fault was
*               found, TRUE wil be returned, FALSE if not.
*
*
*   NOTE:
*       To make fault log extraction more efficient. This routine
*       now has the capability of sending back Fault Log Data for
*       multiple fault indices ("numberoffaults" faults actually).
*
*       The buffer will therefore look like this ...
*
*           ----------------------------------------------------------
*           | faultsize | fault data    | faultsize | fault data    | ....
*           ----------------------------------------------------------
*
*       I also pass back the total used size of the buffer.
*
* .b
*
*   History :   11/21/91    J. Lyon Creation
*   Revised :   02/20/96    D. Pradhan
*               - Changed to pass back in "buffer" data for
*                 multiple fault indices.
*               03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_16 GetFaultStructure(  struct faultlogqueue_t  *eventlogger,
							UINT_32                 faultindex,
							UINT_16                 numberoffaults,
							void                    *faultbuffer )
{
	UINT_16 Counter;
	UINT_16 infocursor;
	UINT_16 faultcounter;
	UINT_16 wordcursor;
	UINT_16 index;
	UINT_16 faultsize;
	UINT_16 cumfaultsize;
	UINT_16 *faultdataindex;

	if (eventlogger == NULL) return 0;

	/*  Initialize all of the locals. */
	infocursor          = eventlogger->infostart;
	cumfaultsize        = 0;
	faultdataindex      = (UINT_16 *)faultbuffer;
	faultcounter        = 0;

	/* Page through the fault log queue until the correct fault has  */
	/* been found or the end of the fault log queue has been reached */
	while ( (GetFaultIndex(eventlogger, infocursor) != faultindex) &&
			(faultcounter++ < eventlogger->numberoffaults))
	{
		/* If we incremented off the end of the fault log queue, reset */
		/* infocursor to the beginning of the fault log queue.     */
		if (++infocursor > (eventlogger->maxevents - 1))
			infocursor = 0;
	}

	/* Check to see if the fault index was found .. */
	/* if not get the next index */
	if (faultcounter >= eventlogger->numberoffaults)
		return 0;

	/* If the first fault was found, copy it and the rest into the */
	/* area pointed to by passed faultbuffer...                    */
	for (Counter = 0; Counter < numberoffaults; Counter++, infocursor++)
	{
		/* If we incremented off the end of the fault log queue, reset */
		/* infocursor to the beginning of the fault log queue.     */
		if (infocursor > (eventlogger->maxevents - 1))
			infocursor = 0;

		/* Get the size of this fault, crudely make sure its not garbage .. */
		faultsize = eventlogger->faultinfo[infocursor].size * 2;
		if (faultsize > MAXFAULTSIZE || faultsize <= 0)
		{
			*faultdataindex++ = 0;
			continue;
		}

		/* Track total size of fault data collected .. make sure it can */
		/* fit in our fault buffer */
		cumfaultsize += (faultsize + 2);
		if (cumfaultsize > MAXFAULTBUFFERSIZE)
			return (cumfaultsize - faultsize - 2);

		/* Store the size in the buffer */
		*faultdataindex++ = faultsize;

		/* Follow the size with the data */
		wordcursor = eventlogger->faultinfo[infocursor].location;
		for (index = 0; index < eventlogger->faultinfo[infocursor].size;
			 wordcursor++, index++ )
		{
			/* If we incremented off the end of the fault log queue, reset */
			/* bytecursor to the beginning of the fault log queue.     */
			if (wordcursor > ((eventlogger->eventqueuesize / 2) - 1))
				wordcursor = 0;

			/*  Copy one word.*/
			*faultdataindex++ = eventlogger->faultqueue[wordcursor];
		}
	}

	return cumfaultsize;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    GetNewestFaultIndex
*
*   Abstract :
*               Returned the index number of the most recently logged fault.
*
*   Inputs :
*       Global :    None
*
*       Constants : MAXNUMOFFAULTS  maximum number of faults
*                           that may be saved on the
*                           fault queue at any given
*                           time
*
*       Parameters :
*               eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure
*                       to be examined
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :
*               The index number of the most recently logged
*               fault.  If no faults have been logged, returns
*               2^32.
*
*   Functional Description :
*               GetNewestFaultIndex will find the newest
*               fault information structure and return the
*               index member.
*
* .b
*
*   History :   11/21/91    J. Lyon Creation
*   Revised :   03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_32 GetNewestFaultIndex(struct faultlogqueue_t *eventlogger)
{
	UINT_16 infocursor;

	if (eventlogger == NULL) return 0xffffffff;

	/*  If no faults have been logged on this fault logger, return -1, */
	/*  or 2^32.                            */
	if (eventlogger->numberoffaults == 0)
		return 0xffffffff;

	/*  Find the newest fault information structure.            */
	infocursor = eventlogger->infostart + (eventlogger->numberoffaults - 1);

	/*  If we added of the end of the world, fix infocursor.      */
	if (infocursor > (eventlogger->maxevents - 1))
		infocursor -= (eventlogger->maxevents);

	/* Return index of the information structure pointed to by infocursor */
	return GetFaultIndex(eventlogger, infocursor);
}


/************************************************************************
*
* .b
*
*   Procedure Name :    GetOldestFaultIndex
*
*   Abstract :
*               Returned the index number of the least
*               recently logged fault.
*
*   Inputs :
*       Global :    None
*
*       Constants :
*                   MAXNUMOFFAULTS  maximum number of faults
*                                   that may be saved on the
*                                   fault queue at any given
*                                   time
*
*       Parameters :
*                   eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be examined
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :
*               The index number of the least recently logged
*               fault.  If no faults have been logged, returns
*               2^32.
*
*   Functional Description :
*               GetOldestFaultIndex will find the oldest
*           fault information structure and return the
*               index member.
*
* .b
*
*   History :   11/21/91    J. Lyon Creation
*   Revised :   03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
INT_32 GetOldestFaultIndex(struct faultlogqueue_t *eventlogger)
{
	if (eventlogger == NULL) return -1;

	/*  If not faults have been logged on this fault logger, */
	/*  return -1, or 2^32.                                  */
	if (eventlogger->numberoffaults == 0)
		return -1;

	/*  Return the index of the oldest logged fault. */
	return GetFaultIndex(eventlogger, eventlogger->infostart);
}


/************************************************************************
*
* .b
*
*   Procedure Name :    SetFaultTable
*
*   Abstract :
*               Enables or disables a fault log for a specific fault type
*
*   Inputs :
*       Global :    None
*
*       Parameters :
*              eventlogger  struct faultlogqueue_t *    pointer to the fault log
*                                                       structure to be modified
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :  TRUE is successful, FALSE if not
*
*   Functional Description :
*               SetFaultTable will check to insure that the
*               passed loggerid and faultid parameter are in
*               bounds.  If this is not true, FALSE is returned
*               and the procedure terminated.  Otherwise,
*               SetFaultTable will modify the faulttable
*               array in the passed eventlogger to enable
*               or disable faults for a specific fault
*               type
*
* .b
*
*   History :   11/21/91    J. Lyon Creation
*   Revised :   10/06/95    D. Pradhan @ATSI
*               - Modified to handle multiple fault and data logs.
*               10/23/95    D. Pradhan
*               - Redesigned to bit mapped approach. Each fault
*                 flag is a bit. 1 - ON, 0 - OFF
*               03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_8 SetFaultTable(   struct faultlogqueue_t  *eventlogger,
						UINT_16                 loggerid,
						UINT_16                 faultid,
						UINT_8                  state)
{
	UINT_16 thebit;
	UINT_16 index;

	if (eventlogger == NULL) return FALSE;

	/*  If the loggerid or the faultid are out of bounds, return FALSE */
	if (loggerid > eventlogger->tasks - 1)
		return FALSE;

	if (faultid > eventlogger->eventspertask - 1)
		return FALSE;

	/*  Set the appropriate member if the faulttable to the correct state */
	index = (loggerid * eventlogger->eventspertask) + faultid;
	thebit = 0x0001;
	thebit = thebit << index % 16;

	if (state)
		eventlogger->faulttable[index / 16] |= thebit;
	else
		eventlogger->faulttable[index / 16] &= ~(thebit);

	/*  All done, return TRUE by default.               */
	return TRUE;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    SetTriggerTable
*
*   Abstract :
*               Enables or disables a data log trigger for
*               a specific fault type
*
*   Inputs :
*
*       Global :    None
*
*       Parameters :
*               eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be modified
*
*               loggerid    UINT_16
*                       loggerid for the fault to
*                       be modified
*
*               faultid     UINT_16
*                       faultid for the fault to be
*                       modified
*
*               state       UINT_8
*                       state that table is to be
*                       modified to
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :  TRUE is successful, FALSE if not
*
*   Functional Description :
*               SetTriggerTable will check to insure that the
*               passed loggerid and faultid parameter are in
*               bounds.  If this is not true, FALSE is
*               returned and the procedure terminated.
*               Otherwise, SetTriggerTable will modify the
*               triggertable array in the passed eventlogger
*               to enable or disable data logs for a specific
*               fault type
*
* .b
*
*   History :   02/08/92    J. Lyon Creation
*   Revised :   10/06/95    D. Pradhan @ATSI
*               - Modified to handle multiple fault and data logs.
*               10/23/95    D. Pradhan
*               - Redesigned to bit mapped approach. Each fault
*                 flag is a bit. 1 - ON, 0 - OFF
*               03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_8 SetTriggerTable( struct faultlogqueue_t  *eventlogger,
						UINT_16                 loggerid,
						UINT_16                 faultid,
						UINT_8                  state)
{
	UINT_16 thebit;
	UINT_16 index;

	if (eventlogger == NULL) return FALSE;

	/*  If the loggerid or the faultid are out of bounds, return */
	/*  FALSE... */
	if (loggerid > eventlogger->tasks - 1)
		return FALSE;

	if (faultid > eventlogger->eventspertask - 1)
		return FALSE;

	/*  Set the appropriate member if the triggertable to the correct */
	/*  state */
	index = (loggerid * eventlogger->eventspertask) + faultid;
	thebit = 0x0001;
	thebit = thebit << index % 16;

	if (state)
		eventlogger->triggertable[index / 16] |= thebit;
	else
		eventlogger->triggertable[index / 16] &= ~(thebit);

	/*  All done, return TRUE by default */
	return TRUE;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    SetFaultLogger
*
*   Abstract :
*               Enables or disables the passed Fault Logger
*
*
*   Inputs :
*       Global :    None
*
*       Parameters :
*               eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be modified
*
*               state       UINT_8
*                       state that table is to be
*                       modified to
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :  TRUE is successful, FALSE if not
*
*   Functional Description :
*               SetFaultTable will modify the active member
*               in the passed fault log structure to disable
*               or enable the Fault Logger
*
* .b
*
*   History :   11/21/91    J. Lyon Creation
*   Revised :   03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_8 SetFaultLogger(struct faultlogqueue_t *eventlogger, UINT_8 state)
{
	if (eventlogger == NULL) return FALSE;

	/*  Set the active member to the appropriate state. */
	eventlogger->active = state;

	/*  All done, return TRUE by default. */
	return TRUE;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    GetEventEnableFlags
*
*   Abstract :
*       Retrieves the settings for the Event Enable Flags.
*
*   Inputs :
*       Global :    None
*
*       Parameters :
*           eventlogger struct faultlogqueue_t *    pointer to the fault log
*                                                   structure to be modified
*
*   Outputs :
*       Global :    None
*
*       Parameters :
*           EnableFlags UINT_16 *                   storage for flag info
*
*       Returned :
*           Size (used) of the returned array of Enable Flags
*
*   Functional Description :
*       Each bit in the returned array describes the settings for the
*       Event Enable flag. If the bit is 1 then the flag is enabled.
*
* .b
*
*   History :   09/04/96    D. Pradhan @ Adtranz (Sweden) Creation
*   Revised :
*
*************************************************************************/
UINT_16 GetEventEnableFlags(struct faultlogqueue_t  *eventlogger,
							UINT_16                 *EnableFlags )
{
	UINT_16 NumberOfWords;
	UINT_16 Counter;

	if (eventlogger == NULL) return 0;

	NumberOfWords = (eventlogger->tasks * eventlogger->eventspertask) / 16;
	if ((eventlogger->tasks * eventlogger->eventspertask) % 16)
		NumberOfWords++;

	for (Counter = 0; Counter < NumberOfWords; Counter++)
	{
		EnableFlags[Counter] = eventlogger->faulttable[Counter];
	}

	return NumberOfWords * 2;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    GetDatalogTriggerFlags
*
*   Abstract :
*       Retrieves the settings for the Event Trigger Flags.
*
*   Inputs :
*       Global :    None
*
*       Parameters :
*           eventlogger struct faultlogqueue_t *    pointer to the fault log
*                                                   structure to be modified
*
*   Outputs :
*       Global :    None
*
*       Parameters :
*           TriggerFlags UINT_16 *                  storage for flag info
*
*       Returned :
*           Size (used) of the returned array of Trigger Flags
*
*   Functional Description :
*       Each bit in the returned array describes the settings for the
*       Event Trigger (Datalog) flag. If the bit is 1 then the flag is
*       enabled.
*
* .b
*
*   History :   09/04/96    D. Pradhan @ Adtranz (Sweden) Creation
*   Revised :
*
*************************************************************************/
UINT_16 GetDatalogTriggerFlags( struct faultlogqueue_t  *eventlogger,
								UINT_16                 *TriggerFlags )
{
	UINT_16 NumberOfWords;
	UINT_16 Counter;

	if (eventlogger == NULL) return 0;

	NumberOfWords = (eventlogger->tasks * eventlogger->eventspertask) / 16;
	if ((eventlogger->tasks * eventlogger->eventspertask) % 16)
		NumberOfWords++;

	for (Counter = 0; Counter < NumberOfWords; Counter++)
	{
		TriggerFlags[Counter] = eventlogger->triggertable[Counter];
	}

	return NumberOfWords * 2;
}

/************************************************************************
*
* .b
*
*   Procedure Name :    GetDynamicFaultHistory
*
*   Abstract :
*               Returns the number of faults that have been
*               counted for a given fault type since the
*               last PurgeDynamicHistory
*
*   Inputs :
*       Global :
*
*       Parameters :
*               eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be inspected
*               loggerid    UINT_16
*                       loggerid of the fault type
*                       whose count is to be returned
*               faultid UINT_16
*                       faultid of the fault type
*                       whose count is to be returned
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :  TRUE is successful, FALSE if not
*
*   Functional Description :
*               GetDynamicFaultHistory will check the bounds
*               of the passed loggerid and faultid values
*               against the maximum values.  If the bounds
*               check faults, FALSE will be returned, if not,
*               GetDynamicFaultHistory will index into the
*               dynamichistory array of the passed fault
*               queue and return the number of fault that
*               have been logged for a given fault type
*               since the last PurgeDynamicHistory.
*
* .b
*
*   History :   02/07/92    J. Lyon Creation
*   Revised :   10/06/95    D. Pradhan @ATSI
*               - Modified to handle multiple fault and data logs.
*               03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
INT_16 GetDynamicFaultHistory( struct faultlogqueue_t  *eventlogger,
								UINT_16                 loggerid,
								UINT_16                 faultid )
{
	UINT_16 curr_pos;

	if (eventlogger == NULL) return -1;

	/*  Check bounds.  If loggerid or faultid is out of bounds, return  */
	/*  -1 or 2^32.                         */
	if (loggerid > eventlogger->tasks - 1)
		return -1;

	if (faultid > eventlogger->eventspertask - 1)
		return -1;

	/*  Return the number of fault logs for this particular fault type  */
	/*  that have occured since the last PurgeDynamicHistory.       */
	curr_pos = (loggerid * eventlogger->eventspertask) + faultid;

	return eventlogger->dynamichistory[curr_pos];
}


/************************************************************************
*
* .b
*
*   Procedure Name :    GetStaticFaultHistory
*
*   Abstract :
*               Returns the number of faults that have been
*               placed in the static history array by
*               PurgeDynamicHistory
*
*   Inputs :
*       Global :
*               EventlogNumofTasks[]
*               EventlogNumofFaults[]
*               CurrentEventLog
*
*       Parameters :
*               eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be inspected
*               loggerid    UINT_16
*                       loggerid of the fault type
*                       whose count is to be returned
*               faultid UINT_16
*                       faultid of the fault type
*                       whose count is to be returned
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :  TRUE is successful, FALSE if not
*
*   Functional Description :
*               GetStaticFaultHistory will check the bounds
*               of the passed loggerid and faultid values
*               against the maximum values.  If the bounds
*               check faults, FALSE will be returned, if not,
*               GetStaticFaultHistory will index into the
*               statichistory array of the passed fault
*               queue and return the number of fault that
*               have been placed for a given fault by
*               PurgeDynamicHistory.
*
* .b
*
*   History :   02/07/92    J. Lyon Creation
*   Revised :   10/06/95    D. Pradhan @ATSI
*               - Modified to handle multiple fault and data logs.
*               03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
INT_16 GetStaticFaultHistory(  struct faultlogqueue_t  *eventlogger,
								UINT_16 loggerid,
								UINT_16 faultid)
{
	UINT_16 curr_pos;

	if (eventlogger == NULL) return -1;

	/*  Check bounds.  If loggerid or faultid is out of bounds, return  */
	/*  -1 or 2^32.                         */
	if (loggerid > eventlogger->tasks - 1)
		return -1;

	if (faultid > eventlogger->eventspertask - 1)
		return -1;

	/*  Return the number of fault logs for this particular fault type  */
	/*  that have been purged from the dynamic counter.         */
	curr_pos = (loggerid * eventlogger->eventspertask) + faultid;

	return eventlogger->statichistory[curr_pos];
}


/************************************************************************
*
* .b
*
*   Procedure Name :    PurgeFaultLogger
*
*   Abstract :
*           Initializes all values to indicated an empty fault logger.
*
*   Inputs :
*       Global :    None
*
*       Constants :
*
*       Parameters :
*               eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be initialized
*
*   Outputs :
*       Global :    None
*
*       Parameters :
*
*       Returned :  TRUE
*
*   Functional Description :
*
* .b
*
*   History :   ??/??/??    J. Lyon Creation
*   Revised :   03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_8 PurgeFaultLogger(struct faultlogqueue_t  *eventlogger)
{
	if (eventlogger == NULL) return FALSE;

	/* Initialize all values to indicated an empty fault logger. */
	eventlogger->numberoffaults = 0;
	eventlogger->wordssaved     = 0;
	eventlogger->infostart      = 0;
	eventlogger->datacursor     = 0;

	PurgeDynamicHistory(eventlogger);

	return TRUE;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    PurgeDynamicHistory
*
*   Abstract :
*               Adds the dynamic history array to the
*               static history area and store the value in
*               the static history area for the passed fault
*               log queue.  Sets all the values in the
*               dynamic history array to 0.
*
*   Inputs :
*       Global :
*               EventlogNumofTasks[]
*               EventlogNumofFaults[]
*               CurrentEventLog
*
*       Parameters :
				eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be modified
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :  TRUE is successful, FALSE if not
*
*   Functional Description :
*               PurgeDynamicHistory will add the all of
*               the values in the dynamichistory area
*               belonging to the passed fault log queue to
*               the respective members of the statichistory
*               area belonging to the save queue.  All of
*               the members in the dynamichistory area will
*               then be set to 0.
*
* .b
*
*   History :   02/07/92    J. Lyon Creation
*   Revised :   10/06/95    D. Pradhan @ATSI
*               - Modified to handle multiple fault and data logs.
*               03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_8 PurgeDynamicHistory(struct faultlogqueue_t *eventlogger)
{
	UINT_16 counter;

	if (eventlogger == NULL) return FALSE;

	/*  Copy all of the dynamic faults history into the static fault */
	/*  history and set the dynamic fault history to 0. */
	for (   counter = 0;
			counter < eventlogger->tasks * eventlogger->eventspertask;
			counter++)
	{
		/* Copy this particular fault type history. */
		eventlogger->statichistory[counter] +=
									eventlogger->dynamichistory[counter];

		/* Delete the dynamic history for the particular fault type. */
		eventlogger->dynamichistory[counter] = 0;
	}

	/*  All done, return TRUE by default. */
	return TRUE;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    PurgeFaultLogNumber
*
*   Abstract :
*     This function clears the pointer to the Fault Log from the Data Log
*
*   Inputs :
*       Global :    None
*
*       Constants :
*
*       Parameters :
*           struct faultlogqueue_t  *eventlogger; pointer to fault log
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :  None
*
*   Functional Description :
*
*   This function takes the index of the current fault (indicated by
*   infostart) and retrieves the header for the fault. The header
*   gives us the DataLog that this fault has triggered (0xffff
*   indicates that a DataLog has not been triggered). We use this
*   DataLogNumber to clear out the fault hook in the DataLog structure.
*
*   NOTE
*       The FaultLog tracks which DataLogElement it corresponds to using the
*   DataLogNumber element in its header (FAULTPACKETPROLOG).
*       The DataLog tracks which Fault it belongs to by using the faulthook
*   array in the DataLog structure.
*
* .b
*
*   History :   06/30/95    Dev Pradhan @ ATSI Created
*   Revised :   03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
void PurgeFaultLogNumber(struct faultlogqueue_t  *eventlogger)
{
	struct minfaultpacket_t currentfault;

	if (eventlogger == NULL) return;

	if (eventlogger->infostart < eventlogger->maxevents)
	{
		/* Get 32 bit value index for current fault */
		currentfault.index =
			(UINT_32)((eventlogger->faultinfo[eventlogger->infostart].index.Words.Word1 << 16) |
					  eventlogger->faultinfo[eventlogger->infostart].index.Words.Word0);

		/* Get the Header Information for this */
		GetFaultHeader(eventlogger, currentfault.index, &currentfault);

		/* Get DataLogNumber .. and for that Data Log Element clear the pointer */
		/* to the Fault Log */
		if (currentfault.DataLogNumber <
			eventlogger->linkedlogger->NumberOfStreams)
		{
			eventlogger->linkedlogger->faulthook[currentfault.DataLogNumber] =
				0xffff;
		}
	}
}


/****************************************************************************
*
* .b
*   Procedure Name:                 PurgeDataLogNumber
*
*   Abstract:
*       See Functional Description.
*
*   INPUTS:
*
*       Globals:
*           None
*
*       Constants:
*           NULL
*           MAXNUMOFFAULTS
*
*       Procedure Parameters:
*           datalogger    struct datalogqueue_t   Pointer to the
*                                                 Datalog to be
*                                                 checked.
*           eventlogger   struct faultlogqueue_t  Pointer to the
*                                                 Fault Log to be
*                                                 checked.
*           StreamNumber  UINT_16
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*           None
*
*   Functional Description:
*
*   This function takes the index of the current fault (indicated by
*   infostart) and retrieves the header for the fault. The header
*   gives us the DataLog that this fault has triggered (0xffff
*   indicates that a DataLog has not been triggered). We use this
*   DataLogNumber to clear out the fault hook in the DataLog structure.
*
*   NOTE
*       The FaultLog tracks which DataLogElement it corresponds to using the
*       DataLogNumber element in its header (FAULTPACKETPROLOG).
*       The DataLog tracks which Fault it belongs to by using the faulthook
*       array in the DataLog structure.
*
* .b
*
*   History:        07/10/94    Creation of Version 3.0             jsl
*   Revised:        05/22/95    Added this header                   ddp
*                   06/30/95    Redesigned                          ddp
*                   03/28/96    ddp @ Adtranz
*                   - Added check on datalog and faultlog pointer and
*                     DataLogNumber
*
*****************************************************************************/
void PurgeDataLogNumber( struct faultlogqueue_t *eventlogger,
						 struct datalogqueue_t  *datalogger,
						 UINT_16                StreamNumber)
{
	UINT_16                 infostart;
	struct minfaultpacket_t currentfault;

	if (datalogger == NULL || eventlogger == NULL)
		return;

	if (StreamNumber >= datalogger->NumberOfStreams)
		return;

	/* Figure out which faultinfo this DataLogElement corresponds to .. */
	infostart = datalogger->faulthook[StreamNumber];

	if (infostart < MAXNUMOFFAULTS)
	{
		/* Get the index for this Fault */
		currentfault.index =
		(UINT_32)((eventlogger->faultinfo[infostart].index.Words.Word1 << 16) |
				  eventlogger->faultinfo[infostart].index.Words.Word0);

		/* Get the header information for this Fault */
		GetFaultHeader(eventlogger, currentfault.index, &currentfault);

		/* Clear out the DataLogNumber */
		currentfault.DataLogNumber = 0xffff;

		/* Insert Header back into fault queue */
		InsertFaultHeader(eventlogger, currentfault.index, &currentfault);
	}

	return;
}



/*=======================================================================

				L O C A L  F U N C T I O N S

========================================================================*/


/************************************************************************
*
* .b
*
*   Procedure Name :    GetFaultIndex
*
*   Abstract :
*
*   Inputs :
*       Global :    None
*
*       Parameters :
*           eventlogger struct faultlogqueue_t *    pointer to the fault log
*                                                   structure to be modified
*           InfoCursor  UINT_16
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :
*
*   Functional Description :
*
* .b
*
*   History :   ??/??/??    J. Lyon Creation
*   Revised :   03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_32 GetFaultIndex(  struct faultlogqueue_t  *eventlogger,
						UINT_16                 InfoCursor)
{
	UINT_32 TempDWord;

	if (eventlogger == NULL) return 0xffffffff;

	TempDWord =  (UINT_32)(eventlogger->faultinfo[InfoCursor].index.Words.Word0 & 0x0000ffff);
	TempDWord += (UINT_32)((eventlogger->faultinfo[InfoCursor].index.Words.Word1 & 0xffff0000) >> 16);

	return TempDWord;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    GetFaultPointer
*
*   Abstract :
*     This function returns pointer to the specified fault.
*
*   Inputs :
*       Global :    None
*
*       Parameters :
*               eventlogger struct faultlogqueue_t *
*                       pointer to the fault log
*                       structure to be modified
*               InfoCursor  UINT_32
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :
*           struct minfaultpacket_t *
*
*   Functional Description :
*
*    Given a fault index, this function searches the fault log
*    for the corresponding fault and returns the pointer to the
*   starting location of the fault. If the corresponding fault is
*   not found, then this function returns NULL.
*
*   NOTE : The fault data may not be consecutive ( if the fault is
*    at the end of the faultqueue, it may be wrapped around). It
*   is upto the calling routine to ensure wrap-around when processing
*   the data based on the returned pointer.
* .b
*
*   History :   04/07/95    Ajay Mishra : added SMRS
*   Revised :   03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
struct minfaultpacket_t *GetFaultPointer(struct faultlogqueue_t  *eventlogger,
										 UINT_32                 PassedIndex )
{
	UINT_16 infocursor;
	UINT_16 faultcounter;

	if (eventlogger == NULL) return NULL;

	/*  Initialize all of the locals. */
	infocursor = eventlogger->infostart;
	faultcounter = 0;

	/*  Page through the fault log queue until the correct fault has   */
	/*  been found or the end of the fault log queue has been reached. */
	while ((GetFaultIndex(eventlogger, infocursor++) != PassedIndex) &&
			(faultcounter++ < eventlogger->numberoffaults))
	 {

	/*  If we incremented off the end of the fault log queue, reset */
	/*  infocursor to the beginning of the fault log queue.         */
		if (infocursor > (eventlogger->maxevents - 1))
			infocursor -= eventlogger->maxevents;
	 }

	/*  If the correct fault was found, return it's address. */
	if (GetFaultIndex(eventlogger, --infocursor) == PassedIndex)
	{
		return (struct minfaultpacket_t *)
			&(eventlogger->faultqueue
				[eventlogger->faultinfo[infocursor].location]);
	}

	/*  No fault was found, return a null pointer. */
	return (struct minfaultpacket_t *)0;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    InsertFaultHeader
*
*   Abstract :
*     This function inserts the specified faultheader.
*
*   Inputs :
*       Global :    None
*
*       Parameters :
*           struct faultlogqueue_t  *eventlogger; pointer to fault log
*           UINT_32                 FaultIndex ; index of fault
*           struct minfaultpacket_t *FaultHeader; header to be inserted
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :
*           struct minfaultpacket_t *
*
*   Functional Description :
*
*   This function searches the fault log for the fault with the
*   specified index and replaces it's header with the passed header.
*   This is required by the data log function. (when data logs
*   wrap around).
*
* .b
*
*   History :   04/07/95    Ajay Mishra : added SMRS
*   Revised :   03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_8  InsertFaultHeader(  struct faultlogqueue_t  *eventlogger,
							UINT_32                 FaultIndex,
							struct minfaultpacket_t *FaultHeader    )
{
	UINT_16 *Target;
	UINT_16 HeaderSize;
	UINT_16 WordCounter;

	if (eventlogger == NULL) return FALSE;

	/*  Find the start of this fault. */
	Target = (UINT_16 *)GetFaultPointer(eventlogger, FaultIndex);

	/*  If the fault was not found, return FALSE. */
	if (Target == (UINT_16 *)0)
		return FALSE;

	/*  Determine the amount of whole words in the fault header. */
	HeaderSize = (sizeof(struct minfaultpacket_t) / 2);
	if (sizeof(struct minfaultpacket_t) % 2)
		HeaderSize--;

	/*  Copy the passed header to the area pointed to by the fault pointer */
	/*  fixing any wrap arounds.                                           */
	for (WordCounter = 0; WordCounter < HeaderSize; WordCounter++)
	{
		*Target++ = *(((UINT_16 *)FaultHeader) + WordCounter);
		/*
		 * AM : 04/06/1995  : max size of fault queue is
		 *  SIZEOFFAULTQUEUE/2 - 1.
		 */
		if (Target >
			&eventlogger->faultqueue[(eventlogger->eventqueuesize / 2)-1])
			Target = &eventlogger->faultqueue[0];
	}

	/*  All done, return TRUE; */
	return TRUE;
}


/************************************************************************
*
* .b
*
*   Procedure Name :    GetFaultHeader
*
*   Abstract :
*     This function copies the specifed fault's header into the passed
*     buffer
*
*   Inputs :
*       Global :    None
*
*       Parameters :
*           struct faultlogqueue_t  *eventlogger; pointer to fault log
*           UINT_32                 FaultIndex ; index of fault
*           struct minfaultpacket_t *FaultHeader; header to be inserted
*
*   Outputs :
*       Global :    None
*
*       Parameters :    None
*
*       Returned :
*           struct minfaultpacket_t *
*
*   Functional Description :
*
*   This function searches the fault log for the fault with the
*   specified index and copies it to the passed buffer. This is used
*   by the data logger when the data log wraps around.
*
* .b
*
*   History :   04/07/95    Ajay Mishra : added SMRS
*   Revised :   03/28/96    DDP @ Adtranz
*               - Added check for NULL fault log pointer
*
*************************************************************************/
UINT_8 GetFaultHeader(  struct faultlogqueue_t  *eventlogger,
						UINT_32                 faultindex,
						struct minfaultpacket_t *faultheader    )
{
	UINT_16 infocursor;
	UINT_16 faultcounter;
	UINT_16 wordcursor;
	UINT_16 index;
	UINT_16 indexlimit;

	if (eventlogger == NULL) return FALSE;

	/*  Initialize all of the locals.                   */
	infocursor = eventlogger->infostart;
	faultcounter = 0;

	/*  Page through the fault log queue until the correct fault has    */
	/*  been found or the end of the fault log queue has been reached.  */
	while ((GetFaultIndex(eventlogger,infocursor++) != faultindex) &&
			(faultcounter++ < eventlogger->numberoffaults))
	{
		/*  If we incremented off the end of the fault log queue, reset */
		/*  infocursor to the beginning of the fault log queue.     */
		if (infocursor > (eventlogger->maxevents - 1))
			infocursor -= eventlogger->maxevents;
	}

	/*  If the correct fault was found, copy it into the area pointed   */
	/*  to by passed faultbuffer...                 */
	if (GetFaultIndex(eventlogger,--infocursor) == faultindex)
	{
		indexlimit = (sizeof(struct minfaultpacket_t) % 2) ?\
						(sizeof(struct minfaultpacket_t)/2 - 1):\
						(sizeof(struct minfaultpacket_t)/2);

		wordcursor = eventlogger->faultinfo[infocursor].location;
		for (index = 0; index < indexlimit; wordcursor++, index++)
		{
			/*  If we incremented off the end of the fault log queue, reset */
			/*  bytecursor to the beginning of the fault log queue.     */
			if (wordcursor > ((eventlogger->eventqueuesize / 2) - 1))
				wordcursor = 0;

			/*  Copy one word */
			*(UINT_16 *)((UINT_16 *)faultheader + index) =
						eventlogger->faultqueue[wordcursor];
		}

		/*  All done, return TRUE */
		return TRUE;
	}

	return FALSE;
}

#ifdef __cplusplus
}
#endif

