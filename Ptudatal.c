/*****************************************************************************
*
* .b
*   Copyright (c) 1996 ABB Daimler-Benz Transportation (North America) Inc.
*
*   Project:
*               Common
*
*   File Name:
*               ptudatal.c
*
*   SubSystem:
*               PTU
*
*   Procedures:
*               InitializeDataLogger
*               LogData
*               LogTdsData
*               TriggerDataLogger
*               FillDataQueue
*               GetCurrentQueue
*               ClearDataLogger
*               GetStreamInformation
*               SetStreamInformation
*               GetDefaultStreamInformation
*               GetStreamSize
*
*   EPROM Drawing:
*
* .b
*
*   History:        07/10/94    Creation of Version 3.0         jsl
*   Revised:        05/22/95    Updated this header             ddp
*                   01/11/96    ddp @ Adtranz
*                   - Fixed bug in GetStreamSize()
*                   03/28/96    ddp @ Adtranz
*                   - Updated all functions to check for NULL datalog pointer
*                   11/19/1999  S.Taher @ ADtranz
*                   - Made the following modifications while moving the fault
*                     log and the data log to the BBRAM :
*                     1. Included batram.h
*                     2. Deleted the external declaration for cc_datalog
*                     3. Modified the InitializeDataLogger routine. See function
*                        header for details.
*                   02/07/2000 S.Taher @ ADtranz
*                   Uncommented the LogData routine.
*                   06/09/2000  D.Schnewlin @ Adtranz
*                   - Added function LogTdsData()
*  			       02/27/2003    R.Cirinelli @ Bombardier
*                   - SCR 71 added functionality to correctly store the datalog
*					information when the number of environmental variables
*					is an odd number. Add initialization of log 4,5,6 
*					06/18/2003	JJN
*					- Replaced version of this file with the Pitt LRV file.
*****************************************************************************/
/*  Grab all of the compiler #pragma's.                                     */
#ifdef __cplusplus
extern "C" {
#endif

/*  Grab all of the project specific info                                   */

/*  Grab all of the application specific files                              */
#include "stdio.h"

/*  Grab the PTU specific files.                                            */
#include "ptuprj.h"
#include "fltinfo.h"
#include "ptu.h"
#include "batram.h"

/* Local Function Prototypes */
void SaveDatalogBytes(UINT_8 *, UINT_16, struct datalogqueue_t *, UINT_16);
void SaveDatalogBytes_tds(UINT_8 *, UINT_16, struct datalogqueue_t *, UINT_16, UINT_8 );

/* Externs */
extern const struct DataLogDef_t         DataLogDef[];

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

/* Global */
INT_16 DataLogSemaphore;
UINT_16 NumOfVarCnt;


/****************************************************************************
*
* .b
*   Procedure Name:                 InitializeDataLogger
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
*           FALSE               Boolean False
*           TRUE                Boolean True
*
*       Procedure Parameters:
*           datalogger            struct datalogqueue_t     Pointer to the
*                                                           Datalog to be
*                                                           initialized.
*
*   OUTPUTS
*
*       Globals:
*           datalogger            struct datalogqueue_t     Pointer to the
*                                                           Datalog that was
*                                                           initialized.
*
*       Returned Values:
*           None (void)
*
*   Functional Description:
*       Initialized the passed DataLogger so that the current DataLog
*       queue is the first queue, the current element is the first element,
*       no trigger queue is active, and the DataLog is currently active.
*
* .b
*
*   History:        07/10/94    Creation of Version 3.0             jsl
*                   10/02/95    ddp
*                   - Added Variable Type Information
*                   03/13/96    ddp
*                   - Added the DefaultDataCount element to save where
*                     the position where the fault is tripped in the
*                     DataLog
*                   03/28/96    ddp @ Adtranz
*                   - Added check on datalog pointer
*                   12/18/96    ddp @ Adtranz
*                   - adapted for variable sized datalogs
*                   11/19/1999  S.Taher @ ADtranz
*                   - Made the following modifications while moving the fault
*                     log and the data log to BBRAM:
*                     1. Changed the pointer variable to point to the
*                        DataLogHunk area created in BBRAM
*                     2. Changed the pointer, datalogger->Data, to point to the
*                        DataLogDataHunk area created in BBRAM
*					02/27/03 R.Cirinelli @ Bombardier
*					SCR 71 - added initialization of log 4,5,6 and deleted 3
*					02/06/2006  Amadou Diop @ Bombardier Transportation
*					- Adapted TDSL for DFW project 
*                   09/10/2009 JEP @ Bombardier Transportation
*                     Modified InitializeDataLogger to accomodate 1 stream data
*                     sample per 60 msec.
*****************************************************************************/
void InitializeDataLogger(struct datalogqueue_t *datalogger)
{
	UINT_16 Counter;
	UINT_16 Element;
	UINT_16 Position;
	UINT_8  *pointer;
	UINT_8  *data;

	if (datalogger == NULL) return;

	/*  Set the Datalog to be enabled and logging data in element 1 of queue 1. */
	/*  Store the rate at which the data log data is being recorded */
	datalogger->datarecordingrate = DataLogDef[CurrentEventLog].DataRecordingRate;
	datalogger->currentqueue      = 0;
	datalogger->datalogtrip       = FALSE;
	datalogger->DefaultDownCount  = DataLogDef[CurrentEventLog].FaultTripPoint;
	datalogger->Enabled           = TRUE;
	datalogger->DefaultSampleRate = DataLogDef[CurrentEventLog].StreamSampleRate;
	datalogger->NumberOfVariables = DataLogDef[CurrentEventLog].NumLoggedVariables;
	datalogger->NumberOfSamples   = DataLogDef[CurrentEventLog].NumOfDataLogEntries;
	datalogger->NumberOfStreams   = DataLogDef[CurrentEventLog].NumOfDataLogElements;

	/* Set up all the variables to point to the right area */
	switch( CurrentEventLog )
    {
        case 0  : pointer = bat_ram_area->non_constant_area.DataLogHunk0; break;
        case 1  : pointer = bat_ram_area->non_constant_area.DataLogHunk1; break;
        case 2  : pointer = bat_ram_area->non_constant_area.DataLogHunk2; break;
		/*case 3  : pointer = bat_ram_area->non_constant_area.DataLogHunk4; break;
		case 4  : pointer = bat_ram_area->non_constant_area.DataLogHunk5; break;
		case 5  : pointer = bat_ram_area->non_constant_area.DataLogHunk6; break; */
        default : return;
    }
	datalogger->queueposition = (UINT_16 *)pointer;

	pointer += datalogger->NumberOfStreams * sizeof(UINT_16);
	datalogger->SampleRate = (UINT_16 *)pointer;

	pointer += datalogger->NumberOfStreams * sizeof(UINT_16);
	datalogger->SampleRateCounter = (UINT_16 *)pointer;

	pointer += datalogger->NumberOfStreams * sizeof(UINT_16);
	datalogger->faulthook = (UINT_16 *)pointer;

	pointer += datalogger->NumberOfStreams * sizeof(UINT_16);
	datalogger->StreamVariable = (UINT_16 *)pointer;

	pointer +=  datalogger->NumberOfStreams *
				datalogger->NumberOfVariables *
				sizeof(UINT_16);
	datalogger->StreamVariableType = (UINT_16 *)pointer;

	pointer +=  datalogger->NumberOfStreams *
				datalogger->NumberOfVariables *
				sizeof(UINT_16);
	datalogger->DefaultStreamVariable = (UINT_16 *)pointer;

	pointer +=  datalogger->NumberOfVariables *
				sizeof(UINT_16);
	datalogger->DefaultStreamVariableType = (UINT_16 *)pointer;

	/* Set up DATA area to point to the pre-allocated area for this Log */
	switch( CurrentEventLog )
    {
        case 0  : data = bat_ram_area->non_constant_area.DataLogDataHunk0; break;
        case 1  : data = bat_ram_area->non_constant_area.DataLogDataHunk1; break;
        case 2  : data = bat_ram_area->non_constant_area.DataLogDataHunk2; break;
		/*case 3  : data = bat_ram_area->non_constant_area.DataLogDataHunk4; break;
		case 4  : data = bat_ram_area->non_constant_area.DataLogDataHunk5; break;
		case 5  : data = bat_ram_area->non_constant_area.DataLogDataHunk6; break;  */
        default : return;
    }
	datalogger->Data = (CastUnion_t *)data;

	/* Initialise Datalog Variable specific variables */
	for (Counter = 0; Counter < datalogger->NumberOfVariables; Counter++)
	{
		datalogger->DefaultStreamVariable[Counter] =
			DataLogDef[CurrentEventLog].DataLogElements[Counter];
		datalogger->DefaultStreamVariableType[Counter] =
			VariableDef[DataLogDef[CurrentEventLog].DataLogElements[Counter]].type_id;
	}

	/* Initialise Datalog Element specific variables */
	for (   Element = 0;
			Element < datalogger->NumberOfStreams;
			Element++ )
	{
		Position = Element * datalogger->NumberOfVariables;

		/*  Load the stream variable arrays and the sample rate */
		for (Counter = 0; Counter < datalogger->NumberOfVariables; Counter++)
		{
			datalogger->StreamVariable[Position + Counter] =
				DataLogDef[CurrentEventLog].DataLogElements[Counter];
			datalogger->StreamVariableType[Position + Counter] =
				VariableDef[DataLogDef[CurrentEventLog].DataLogElements[Counter]].type_id;
		}
		datalogger->queueposition[Element]     = 0;
		datalogger->faulthook[Element]         = 0xffff;
		datalogger->SampleRate[Element]        = datalogger->DefaultSampleRate;
		datalogger->SampleRateCounter[Element] = datalogger->DefaultSampleRate;

		//datalogger->SampleRateCounter[Element] = datalogger->DefaultSampleRate - 1;
	}

	DataLogSemaphore = 0;
}


/****************************************************************************
*
* .b
*   Procedure Name:                 LogData
*
*   Abstract:
*       LogData fills the current element of the current queue in the
*       DataLog with data and readies the next element in the same queue.
*       If a tripqueue is active, the tripqueue is serviced in the same manner.
*       If the tripqueue is full, LogData terminates logging into the
*       tripqueue.
*
*   INPUTS:
*
*       Globals:
*           None
*       Constants:
*           FALSE               Boolean False
*
*       Procedure Parameters:
*           EventLogToLogTo         UINT_16                 Event Log ID of
*                                                           Dataog to be used.
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values:
*           None
*
*   Functional Description:
*       LogData checks to see if the passed DataLogger is currently active.
*       If not, LogData returns.  If the passed DataLogger is active and a
*       tripqueue is active, the current tripqueue element is logged with
*       data.  If the tripqueue is full, the tripqueue is saved and data
*       logging into is terminated.  If a current queue is active, data is
*       logged then logged into it.  LogData then returns.
*
*
*       Fault Data
*
*       DataLog Element         0               1       ... NUMOFDATALOGELEMENTS
*       DataLog Entry   ------------------------------------------------------
*           0           |               |              |                     |
*                       ------------------------------------------------------
*           1           |0|1|2|3|4|5|6|7|
*                       -----------------
*           2           |0|1|2|3|4|5|6|7|
*                       -----------------
*           :                   :
*           :                   :
*           :                   :
*           :           -----------------
*           :           |0|1|2|3|4|5|6|7|
*           :           ------------------------------------------------------
*   NUMDATALOGENTRIES   |0|1|2|3|4|5|6|7|               |                    |
*                       ------------------------------------------------------
*
*
* .b
*
*   History:        07/10/94    Creation of Version 3.0             jsl
*   Revised:        06/08/95    ddp
*                   - Updated Functional Description
*                   10/03/95    ddp
*                   - Changed the way FillDataQueue was invoked
*                   11/27/95    ddp
*                   - Changed LogData to now receive the Event Log ID and
*                   then Log to the appropriate DataLog
*                   03/28/96    ddp @ Adtranz
*                   - Added check on datalog pointer
*
*****************************************************************************/
void LogData(UINT_16 EventLogToLogTo)
{
	INT_16                  XIndex;
	struct datalogqueue_t   *datalogger;

	if (DataLogSemaphore) return;

	/* Make sure the Event Log is Valid */
	if (EventLogToLogTo >= NUMOFEVENTLOGS)
		return;

	/* Get the Data log for this Event Log and make sure it is valid */
	datalogger = &(bat_ram_area->non_constant_area.cc_datalog[EventLogToLogTo]);
	if (datalogger == NULL) return;

	/*  If the DataLog has not been enabled, return */
	if (!datalogger->Enabled) return;

	/*  Check to see if the datalogtrip flag has been set */
	if (datalogger->datalogtrip)
	{
		/* Make sure trip queue is valid */
		if ((XIndex = datalogger->tripqueue) >= datalogger->NumberOfStreams)
			return;

		/* Check to see if the sample rate counter has reached 0 */
		if (--datalogger->SampleRateCounter[XIndex] <= 0)
		{
			/*  The datalogtrip flag has been set, check to see if the */
			/*  downcount counter has been decremented to 0.           */
			if (--datalogger->downcount > 0)
			{
				/*  log data into the tripped data log queue. */
				FillDataQueue(datalogger, XIndex);
			}
			else
			{
				/*  The downcount counter has been decremented to 0, */
				/*  set the datalog trip flag to false.              */
				datalogger->datalogtrip = FALSE;
			}

			/* Reset the Sample Rate Counter */
			datalogger->SampleRateCounter[XIndex] =
											datalogger->SampleRate[XIndex];
		}
	}

	/* Make sure current queue is valid */
	if ((XIndex = datalogger->currentqueue) >= datalogger->NumberOfStreams)
		 return;

	/* Decrement the Sample Rate Counter until its time to save a sample */
	if (--datalogger->SampleRateCounter[XIndex] > 0)
		return;

	/*  Fill the current queue. */
	FillDataQueue(datalogger, XIndex);

	/* Reset the Sample Rate Counter */
	datalogger->SampleRateCounter[XIndex] = datalogger->SampleRate[XIndex];

	return;
}


/****************************************************************************
*
* .b
*   Procedure Name:                 LogTdsData
*
*   Abstract:
*       If a tripqueue is active, LogTdsData fills the tripqueue element of
*       the tripqueue queue in the DataLog with TDS environment data.
*
*   INPUTS:
*
*       Globals:
*           bat_ram_area->non_constant_area.cc_datalog[]
*           DataLogSemaphore
*
*       Constants:
*           FALSE               Boolean False
*           NULL                Invalid Pointer
*           NUMOFEVENTLOGS      Number of event loggers
*
*       Procedure Parameters:
*           EventLogToLogTo  UINT_16  Event Log ID of Dataog to be used.
*           DataBuffer[]     UINT_16  Pointer to sampled data in Words.
*           lg_block         UINT_8   Block length (Words per sample)
*           block_nb         UINT_8   Block number (number of samples)
*           old_block        UINT_8   Oldest block (oldest sample)
*           trigg_block      UINT_8   Trigger block (trigger sample)
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
*       LogTdsData checks the vality all parameters and if the passed
*       DataLogger is currently active. If not, LogTdsData returns. If the
*       passed DataLogger is active and a tripqueue is active, the current
*       tripqueue element is logged with the specified environment data.
*       Since the data in the input buffer does not necessarily start with
*       the oldest sample, this logging is done in two parts:
*       - First LogTdsData copies the data starting from the first sampled
*         variable until the end of the buffer.
*       - Finaly it copies the reminding data starting at position 0.
*       LogTdsData then resets the tripqueue and returns.
*
*
*       Data Buffer
*       ==========
*                       -----------------
*        WrapAround     |0|1|2|3|4|5|6|7|    \
*                       -----------------    |
*      WrapAround + n   |0|1|2|3|4|5|6|7|    |
*                       -----------------    |  Second data block to copy
*           :                   :            |
*           :                   :            |
*                       -----------------    |
*    NumberOfWords - n  |0|1|2|3|4|5|6|7|    /
*                       -----------------
*        OldestWord     |0|1|2|3|4|5|6|7|    \
*                       -----------------    |
*      OldestWord + n   |0|1|2|3|4|5|6|7|    |
*                       -----------------    |  First data block to copy
*           :                   :            |
*           :                   :            |
*           :           -----------------    |
*      WrapAround - n   |0|1|2|3|4|5|6|7|    /
*                       -----------------
* (n = NumberOfVariables for each sample)
*
*       Fault Data
*       ==========
*
*       DataLog Element         0               1       ... NUMOFDATALOGELEMENTS
*       DataLog Entry   ------------------------------------------------------
*           0           |0|1|2|3|4|5|6|7|              |                     |
*                       ------------------------------------------------------
*           1           |0|1|2|3|4|5|6|7|
*                       -----------------
*           2           |0|1|2|3|4|5|6|7|
*                       -----------------
*           :                   :
*           :                   :
*                       -----------------
*      WrapAround - n   |0|1|2|3|4|5|6|7|
*                       -----------------
*        WrapAround     |0|1|2|3|4|5|6|7|
*                       -----------------
*      WrapAround + n   |0|1|2|3|4|5|6|7|
*                       -----------------
*           :                   :
*           :                   :
*           :           -----------------
*           :           |0|1|2|3|4|5|6|7|
*           :           ------------------------------------------------------
*   NUMDATALOGENTRIES   |0|1|2|3|4|5|6|7|               |                    |
*                       ------------------------------------------------------
*
*
* .b
*
*   History:        06/07/2000  D.Schnewlin @ Adtranz - Creation
*   Revised:		02/27/2003  R.Cirinelli @ Bombardier
*					- added a check to determine if the number of variables
*					  is an odd value.  This value is then passed to the
*					  SaveDatalogBytes_tds function
*****************************************************************************/

void LogTdsData(UINT_16 EventLogToLogTo,
                UINT_16 DataBuffer[],
                UINT_8  lg_block,
                UINT_8  block_nb,
                UINT_8  old_block,
                UINT_8  trigg_block )

{
	INT_16                  XIndex;
	struct datalogqueue_t   *datalogger;
   UINT_16                 NumberOfWords = (UINT_16)lg_block * (UINT_16)block_nb;
   UINT_16                 OldestWord    = (UINT_16)lg_block * (UINT_16)old_block;
   UINT_8  				   OddNumVars;

	if (DataLogSemaphore) return;

	/* Make sure the Event Log is Valid */
	if (EventLogToLogTo >= NUMOFEVENTLOGS) return;

   /* Get the Data log for this Event Log and make sure it is valid */
	datalogger = &(bat_ram_area->non_constant_area.cc_datalog[EventLogToLogTo]);
	if (datalogger == NULL) return;

	/*  If the DataLog has not been enabled, return */
	if (!datalogger->Enabled) return;

	/*  Check to see if the datalogtrip flag has been set */
	if (!datalogger->datalogtrip) return;

    /* Make sure trip queue is valid */
	XIndex = datalogger->tripqueue;

	if ((XIndex) >= datalogger->NumberOfStreams)
		return;

    /* Make sure trip queue is valid */
	if ((XIndex = datalogger->tripqueue) >= datalogger->NumberOfStreams)
		return;

    /* Make sure all parameters are valid and correspond to configuration */
//    if( block_nb < trigg_block || block_nb < old_block ||
//        block_nb != datalogger->NumberOfSamples ||
//        lg_block != datalogger->NumberOfVariables ||
//        (block_nb + old_block - trigg_block - 1) % block_nb != datalogger->DefaultDownCount)
//        return 7;

    if( block_nb < trigg_block || block_nb < old_block ||
        block_nb != datalogger->NumberOfSamples ||
        lg_block != datalogger->NumberOfVariables )
        return;

	/*  Make sure DataLog has been enabled and stream number is valid */
    if (!datalogger->Enabled || XIndex>=datalogger->NumberOfStreams)
        return;

    /* determine if the number of variables is an odd value */
	if (datalogger->NumberOfVariables % 2 == 1)
	  OddNumVars = 255;
	
    /* Copy data starting with first sampled environment data */
    SaveDatalogBytes_tds((UINT_8 *)&DataBuffer[OldestWord],
                     (UINT_16)((NumberOfWords - OldestWord) * sizeof( UINT_16 )),
                     datalogger,
                     XIndex,
                     OddNumVars);

    /* Call only if OldestWord is > 0  9-13-00 JJN */
    if (OldestWord > 0)
    {
    	/* Copy data with reminding environment data */
    	SaveDatalogBytes_tds((UINT_8 *)&DataBuffer[0],
      	               (UINT_16)((OldestWord) * sizeof( UINT_16 )),
         	            datalogger,
            	        XIndex,
                        OddNumVars);

    }

	/* reset the number of variable counter so that it will be
	   ready for the next fault */
	NumOfVarCnt = 0;
    /*  Event data has been copied, set the datalog trip flag to false.              */
	datalogger->datalogtrip = FALSE;

	return;
}


/****************************************************************************
*
* .b
*   Procedure Name:                 TriggerDataLogger
*
*   Abstract:
*       TriggerDataLogger is called when an event posts a notice that a
*       DataLog queue should be trigger to store pre- and post-event
*       data.
*
*   INPUTS:
*
*       Globals:
*           None
*       Constants:
*           TRUE                    Boolean True
*           NUMDATALOGENTRIES       Number of Element Frames in a Datalog
*           NUMOFDATALOGELEMENTS    Number of Queues in a Datalog
*
*       Procedure Parameters:
*           datalogger            struct datalogqueue_t   Pointer to the
*                                                           Datalog to be used.
*
*   OUTPUTS
*
*       Globals:
*           datalogger            struct datalogqueue_t   Updated Datalog
*                                                           Information.
*
*       Returned Values:
*           None (void)
*
*   Functional Description:
*       TriggerDataLogger check to see if the passed DataLogger is currently
*       active.  If not, TriggerDataLogger returns.  Otherwise, trigger
*       DataLogger sets the current DataLog queue to be the active trigger
*       queue and indicates that half of the queue is to contain pre-event
*       data and half is to contain post-event data.  TriggerDataLogger
*       then modifies the passed DataLogger structure to indicated that
*       a trigger queue is active.
*
* .b
*
*   History:        07/10/94    Creation of Version 3.0             jsl
*   Revised:        03/28/96    ddp @ Adtranz
*                   - Added check on datalog pointer
*
*****************************************************************************/
UINT_16 TriggerDataLogger(  struct datalogqueue_t   *datalogger,
							struct faultlogqueue_t  *eventlogger )
{
	UINT_16 Counter;
	UINT_16 Position;
	UINT_16 ReturnValue;

	do
	{
		/* Make sure both the Data Log and Fault logs are valid */
		if (datalogger == NULL || eventlogger == NULL)
		{ ReturnValue = 0xffff; break; }

		/*  If the datalogtrip flag is currently set ignore this trip */
		if (datalogger->datalogtrip)
		{ ReturnValue = 0xffff; break; }

		/*  Set the number of frames to be saved after the trip event */
		datalogger->downcount = datalogger->DefaultDownCount;

		DataLogSemaphore = 1;

		/*  Set the tripqueue and queueposition values for the newly */
		/*  tripped queue.                                           */
		datalogger->tripqueue = datalogger->currentqueue;
		datalogger->queueposition[datalogger->tripqueue] =
						datalogger->queueposition[datalogger->currentqueue];

		/*  Increment the currentqueue counter and fix any wrap-around errors */
		datalogger->currentqueue++;
		if (datalogger->currentqueue >= datalogger->NumberOfStreams)
			datalogger->currentqueue = 0;

		/*  Clear the queueposition counter for the new queue */
		datalogger->queueposition[datalogger->currentqueue] = 0;

		/*  Clear any reference to the tripqueue from the Fault Log */
		PurgeDataLogNumber(eventlogger, datalogger, datalogger->tripqueue);

		/*  Clear any reference to the currentqueue from the Fault Log */
		PurgeDataLogNumber(eventlogger, datalogger, datalogger->currentqueue);

		/*  Load the sample rate from the default */
		datalogger->SampleRate[datalogger->currentqueue] =
								datalogger->DefaultSampleRate;
		datalogger->SampleRateCounter[datalogger->currentqueue] =
								datalogger->DefaultSampleRate;

		/*  Load the stream variables indexes from the default */
		Position = datalogger->currentqueue * datalogger->NumberOfVariables;

		for (Counter = 0; Counter < datalogger->NumberOfVariables; Counter++)
		{
			datalogger->StreamVariable[Position + Counter] =
						datalogger->DefaultStreamVariable[Counter];
			datalogger->StreamVariableType[Position + Counter] =
						datalogger->DefaultStreamVariableType[Counter];
		}

		/*  Indicate that a tripqueue is currently active. */
		datalogger->datalogtrip = TRUE;

		/*  Return the new trip queue. */
		ReturnValue = datalogger->tripqueue;

	} while (FALSE);

	DataLogSemaphore = 0;

	return ReturnValue;
}


/****************************************************************************
*
* .b
*   Procedure Name:                 FillDataQueue
*
*   Abstract:
*       FillDataQueue fills that passed DataLog queue element with the
*       values of the logged variables.
*
*   INPUTS:
*
*       Globals:
*           None
*
*       Constants:
*           INT_8_TYPE          8 Bit Signed Integer
*           UINT_8_TYPE         8 Bit Unsigned Integer
*           INT_16_TYPE         16 Bit Signed Integer
*           UINT_16_TYPE        16 Bit Unsigned Integer
*           INT_32_TYPE         32 Bit Signed Integer
*           UINT_32_TYPE        32 Bit Unsigned Integer
*
*       Procedure Parameters:
*           PassedDataQueuePointer  struct dataqueue_t  Pointer to the
*                                                       Datalog queue element
*                                                       to be filled.
*
*   OUTPUTS
 *
*       Globals:
*
*       Returned Values:
*           None (void)
*
*   Functional Description:
*       FillDataQueue loads the respective DataLog queue element member
*       with the value of the proper variable.  This is repeated for
*       each member in the DataLog queue element.
*
* .b
*
*   History:        07/10/94    Creation of Version 3.0             jsl
*   Revised:        10/02/95    Compress into bytes instead of      ddp
*                               keeping all data in longs.
*                   03/28/96    ddp @ Adtranz
*                   - Added check on datalog pointer
*****************************************************************************/
void FillDataQueue( struct datalogqueue_t   *datalogger,
					UINT_16                 StreamNumber )
{
	UINT_16         Index;
	UINT_16         VarIndex;
	UINT_16         Count;
	UINT_16         Position;
	UINT_8          Buffer[NUMLOGGEDVARIABLES * 4];

	if (datalogger == NULL) return;
	if (StreamNumber >= datalogger->NumberOfStreams)
		return;

	/* Initialise */
	Count = 0;
	for (Index = 0; Index < datalogger->NumberOfVariables * 4; Index++)
		Buffer[Index] = 0x00;

	/*  Load the passed queue element with the data pointed to by the list */
	/*  of variables to be logged. */
	Position = StreamNumber * datalogger->NumberOfVariables;
	for (Index = 0; Index < datalogger->NumberOfVariables; Index++)
	{
		if (datalogger->StreamVariable[Position + Index] >= NUMDEFINEDVARS)
			datalogger->StreamVariable[Position + Index] = 0;

		VarIndex = datalogger->StreamVariable[Position + Index];

		switch (VariableDef[VarIndex].type_id)
		{
			case INT_8_TYPE  :
			case UINT_8_TYPE :
				Buffer[Count++] = *(UINT_8 *)VariableDef[VarIndex].var_start_addr;
				break;

			case INT_16_TYPE  :
			case UINT_16_TYPE :
				Buffer[Count++] = *(UINT_8 *)VariableDef[VarIndex].var_start_addr;
				Buffer[Count++] = *((UINT_8 *)VariableDef[VarIndex].var_start_addr + 1);
				break;

			case INT_32_TYPE  :
			case UINT_32_TYPE :
				Buffer[Count++] = *(UINT_8 *)VariableDef[VarIndex].var_start_addr;
				Buffer[Count++] = *((UINT_8 *)VariableDef[VarIndex].var_start_addr + 1);
				Buffer[Count++] = *((UINT_8 *)VariableDef[VarIndex].var_start_addr + 2);
				Buffer[Count++] = *((UINT_8 *)VariableDef[VarIndex].var_start_addr + 3);
				break;
		}
	}
	SaveDatalogBytes(Buffer, Count, datalogger, StreamNumber);
}


/****************************************************************************
*
* .b
*   Procedure Name:                 SaveDatalogBytes
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
*
*       Procedure Parameters:
*               UINT_8                  *ByteBuffer
*               UINT_16                 NumberOfBytes
*               struct datalogqueue_t   *datalogger
*               UINT_16                 StreamNumber
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values:
*           None (void)
*
*   Functional Description:
*
* .b
*
*   History:        10/02/95    Creation of Version 1.0             ddp
*   Revised:        10/18/96    ddp @ Adtranz
*                   - Fixed bugs
*                   12/18/96    ddp @ Adtranz
*                   - adapted for variable sized datalogs
*****************************************************************************/
void SaveDatalogBytes(  UINT_8                  *ByteBuffer,
						UINT_16                 NumberOfBytes,
						struct datalogqueue_t   *datalogger,
						UINT_16                 StreamNumber )
{
	UINT_16     Count;
	UINT_32     position;
	UINT_32     startposition;

	/* Get Starting position in Data Buffer for next gob of data */
	startposition =  StreamNumber *
					 datalogger->NumberOfSamples *
					 datalogger->NumberOfVariables;

	position = startposition + datalogger->queueposition[StreamNumber];

	/* Loop thru the bytes in the buffer in chunks of 4 bytes */
	for(Count = 0; Count < NumberOfBytes; Count += 4)
	{
		/* Check for wrap around */
		if (position >= (UINT_32)((StreamNumber + 1) *
								  datalogger->NumberOfSamples *
								  datalogger->NumberOfVariables))
		{
			position =  startposition;
		}

		/* Stuff Data into Datalog Data Buffer */
		datalogger->Data[position].Words.Word0 =
										  *(UINT_16 *)&ByteBuffer[Count];
		datalogger->Data[position].Words.Word1 =
										  *(UINT_16 *)&ByteBuffer[Count + 2];

		position++;
	}

	/* Save the next position in Data buffer */
	datalogger->queueposition[StreamNumber] = position - startposition;
}


/****************************************************************************
*
* .b
*   Procedure Name:                 ClearDataLogger
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
*           FALSE               Boolean False
*           TRUE                Boolean True
*
*       Procedure Parameters:
*           datalogger              struct datalogqueue_t   Pointer to the
*                                                           Datalog to be
*                                                           initialized.
*           eventlogger             struct faultlogqueue_t  Pointer to the
*                                                           Fault Log to be
*                                                           checked.
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values:
*           None (void)
*
*   Functional Description:
*       Clears the passed DataLogger so that the current DataLog
*       queue is the first queue, the current element is the first element,
*       no trigger queue is active, and the DataLog is currently active.
*
* .b
*
*   History:       07/10/94    Creation of Version 3.0             jsl
*   Revised:       03/28/96    ddp @ Adtranz
*                   - Added check on datalog pointer
*
*****************************************************************************/
void ClearDataLogger(struct datalogqueue_t *datalogger)
{
	UINT_16 Counter;
	UINT_16 Element;
	UINT_16 Position;

	if (datalogger == NULL) return;

	/*  Set the Datalog to be enabled and logging data in element 1 of queue 1. */
	datalogger->currentqueue      = 0;
	datalogger->datalogtrip       = FALSE;
	datalogger->Enabled           = TRUE;

	for ( Element = 0;
		  Element < datalogger->NumberOfStreams;
		  Element++ )
	{
		/*  Load the stream variable arrays and the sample rate. */
		Position = Element * datalogger->NumberOfVariables;
		for (Counter = 0; Counter < datalogger->NumberOfVariables; Counter++)
		{
			datalogger->StreamVariable[Position + Counter] =
							datalogger->DefaultStreamVariable[Counter];
			datalogger->StreamVariableType[Position + Counter] =
							datalogger->DefaultStreamVariableType[Counter];
		}

		datalogger->queueposition[Element]     = 0;
		datalogger->faulthook[Element]         = 0xffff;
		datalogger->SampleRate[Element]        = datalogger->DefaultSampleRate;
		datalogger->SampleRateCounter[Element] = datalogger->DefaultSampleRate;
	}
}


/****************************************************************************
*
* .b
*   Procedure Name:                 GetCurrentQueue
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
*
*       Procedure Parameters:
*           datalogger            struct datalogqueue_t   Pointer to the
*                                                         Datalog to be
*                                                         checked.
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*           UINT_16         Value of the current queue for the passed
*                           DataLog.
*
*   Functional Description:
*       GetCurrentQueue retuned the ID of the currently active queue for
*       the passed DataLog.  This function is provided as a friend function
*       to allow DataLog access by the PTU and FaultLogger.
*
* .b
*
*   History:        07/10/94    Creation of Version 3.0             jsl
*   Revised:        03/28/96    ddp @ Adtranz
*                   - Added check on datalog pointer
*
*****************************************************************************/
UINT_16 GetCurrentQueue(struct datalogqueue_t *datalogger)
{
	UINT_16 QueueNumber;

	if (datalogger == NULL) return 0xffff;

	/*  Get and return the Id of the current data queue. */
	QueueNumber = datalogger->currentqueue;

	return QueueNumber;
}


/****************************************************************************
*
* .b
*   Procedure Name:                 GetStreamInformation
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
*
*       Procedure Parameters:
*           datalogger              struct datalogqueue_t   Pointer to the
*                                                           Data Log to be
*                                                           checked.
*           StreamNumber            UINT_16
*           ReturnedInformation     StreamInformation_t
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
* .b
*
*   History:        07/10/94    Creation of Version 3.0             jsl
*   Revised:        05/22/95    Added this header                   ddp
*                   10/02/95    Added Variable Type Information     ddp
*                   01/29/96    Changed Stream Variable Interface   ddp
*                   03/28/96    ddp @ Adtranz
*                   - Added check on datalog pointer and Stream Number
*
*****************************************************************************/
void GetStreamInformation(  struct datalogqueue_t   *datalogger,
							UINT_16                 StreamNumber,
							StreamInformation_t     *ReturnedInformation )
{
	UINT_16 Counter;
	UINT_16 Position;

	if (datalogger == NULL ||
		StreamNumber >= datalogger->NumberOfStreams)
	{
		ReturnedInformation->NumberOfVariables  = 0;
		ReturnedInformation->NumberOfSamples    = 0;
		ReturnedInformation->SampleRate         = 0;
		return;
	}

	ReturnedInformation->NumberOfVariables  = datalogger->NumberOfVariables;
	ReturnedInformation->NumberOfSamples    = datalogger->NumberOfSamples;
	ReturnedInformation->SampleRate         = datalogger->SampleRate[StreamNumber];

	Position = StreamNumber * datalogger->NumberOfVariables;
	for (Counter = 0; Counter < datalogger->NumberOfVariables; Counter++)
	{
		ReturnedInformation->StreamVariableInfo[Counter].StreamVariable =
			datalogger->StreamVariable[Position + Counter];
		ReturnedInformation->StreamVariableInfo[Counter].StreamVariableType =
			datalogger->StreamVariableType[Position + Counter];
	}

	return;
}


/****************************************************************************
*
* .b
*   Procedure Name:                 SetStreamInformation
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
*
*       Procedure Parameters:
*           datalogger              struct datalogqueue_t   Pointer to the
*                                                           Data Log to be
*                                                           checked.
*           PassedInformation       StreamInformation_t
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
* .b
*
*   History:        07/10/94    Creation of Version 3.0             jsl
*   Revised:        05/22/95    Added this header                   ddp
*                   10/02/95    Added Variable Type Information     ddp
*                   01/29/96    Changed Stream Variable Interface   ddp
*                   03/28/96    ddp @ Adtranz
*                   - Added check on datalog pointer
*
*****************************************************************************/
void SetStreamInformation(  struct datalogqueue_t   *datalogger,
							StreamInformation_t     *PassedInformation  )
{
	UINT_16 Counter;

	if (datalogger == NULL) return;

	datalogger->DefaultSampleRate = PassedInformation->SampleRate;

	for (Counter = 0; Counter < datalogger->NumberOfVariables; Counter++)
	{
		datalogger->DefaultStreamVariable[Counter] =
			PassedInformation->StreamVariableInfo[Counter].StreamVariable;
		datalogger->DefaultStreamVariableType[Counter] =
			VariableDef[PassedInformation->StreamVariableInfo[Counter].StreamVariable].type_id;
	}

	TriggerDataLogger(datalogger, GlobalFaultLog);
}


/****************************************************************************
*
* .b
*   Procedure Name:                 GetDefaultStreamInformation
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
*
*       Procedure Parameters:
*           datalogger              struct datalogqueue_t   Pointer to the
*                                                           Data Log to be
*                                                           checked.
*           ReturnedInformation     StreamInformation_t
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
* .b
*
*   History:        07/10/94    Creation of Version 3.0             jsl
*   Revised:        05/22/95    Added this header                   ddp
*                   10/02/95    Added Variable Type Information     ddp
*                   01/29/96    Changed Stream Variable Interface   ddp
*                   03/28/96    ddp @ Adtranz
*                   - Added check on datalog pointer
*
*****************************************************************************/
void GetDefaultStreamInformation(struct datalogqueue_t *datalogger,
								 StreamInformation_t   *ReturnedInformation )
{
	UINT_16 Counter;

	if (datalogger == NULL)
	{
		ReturnedInformation->NumberOfVariables  = 0;
		ReturnedInformation->NumberOfSamples    = 0;
		ReturnedInformation->SampleRate         = 0;
		return;
	}

	ReturnedInformation->NumberOfVariables  = datalogger->NumberOfVariables;
	ReturnedInformation->NumberOfSamples    = datalogger->NumberOfSamples;
	ReturnedInformation->SampleRate         = datalogger->DefaultSampleRate;

	for (Counter = 0; Counter < datalogger->NumberOfVariables; Counter++)
	{
		ReturnedInformation->StreamVariableInfo[Counter].StreamVariable =
			datalogger->DefaultStreamVariable[Counter];
		ReturnedInformation->StreamVariableInfo[Counter].StreamVariableType =
			datalogger->DefaultStreamVariableType[Counter];
	}
}


/****************************************************************************
*
* .b
*   Procedure Name:                 GetStreamSize
*
*   Abstract:
*       Computes the actual size of the data in an Datalog Queue
*
*   INPUTS:
*
*       Globals:
*           None
*
*       Constants:
*           INT_8_TYPE
*           UINT_8_TYPE
*           INT_16_TYPE
*           UINT_16_TYPE
*           INT_32_TYPE
*           UINT_32_TYPE
*
*       Procedure Parameters:
*           datalogger          struct datalogqueue_t       Pointer to the
*                                                           Data Log to be
*                                                           checked.
*           StreamNumber        UINT_16
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*           Size of Stream
*
*   Functional Description:
*
*   Computes the size of the data in the Data log Buffer by examining
*   the type of each of the variables and computing the size of each
*   sample of data and then finally returning the product of the
*   number of samples in a queue and this computed size.
*
* .b
*
*   History:        10/03/95    Creation of Version 1.0             ddp
*   Revised:        01/11/96    ddp @ Adtranz
*                   - Fixed bug with rounding off of byte count
*                   03/28/96    ddp @ Adtranz
*                   - Added check on datalog pointer
*
*****************************************************************************/
UINT_16 GetStreamSize(struct datalogqueue_t *datalogger, UINT_16 StreamNumber)
{
	UINT_16 Count;
	UINT_16 Index;
	UINT_16 Position;

	Position = StreamNumber * datalogger->NumberOfVariables;
	Count = 0;
	for (Index = 0; Index < datalogger->NumberOfVariables; Index++)
	{
		switch (datalogger->StreamVariableType[Position + Index])
		{
			case INT_8_TYPE   :
			case UINT_8_TYPE  : Count++; break;

			case INT_16_TYPE  :
			case UINT_16_TYPE : Count += 2; break;

			case INT_32_TYPE  :
			case UINT_32_TYPE : Count += 4; break;
		}
	}

	/* Round off to next word */
	if (Count % 4) Count += (4 - (Count % 4));

	return Count * datalogger->NumberOfSamples;
}


/****************************************************************************
*
* .b
*   Procedure Name:                 GetDataLogData
*
*   Abstract:
*       Returns a buffer with the Datalog Data, the Number of Bytes of data
*       and the position of the origin in this Datalog Data buffer.
*
*   INPUTS:
*
*       Globals:
*           None
*
*       Constants:
*           NULL
*           MAXDATALOGBUFFERSIZE
*
*       Procedure Parameters:
*           datalogger          struct datalogqueue_t       Pointer to the
*                                                           Data Log to be
*                                                           checked.
*           StreamNumber        UINT_16
*           *DatalogBuffer      UINT_32
*           *OriginPosition     UINT_16
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*           Size of Queue, 0 on error.
*
*   Functional Description:
*
* .b
*
*   History:        09/03/96    Creation of Version 1.0             ddp
*   Revised:        12/18/96    ddp @ Adtranz
*                   - adapted for variable sized datalogs
*
*****************************************************************************/
UINT_16 GetDataLogData( struct datalogqueue_t   *datalogger,
						UINT_16                 StreamNumber,
						UINT_32                 *DatalogBuffer,
						UINT_16                 *OriginPosition )
{
	UINT_16 NumberOfBytes;
	UINT_16 StreamSize;
	UINT_32 Position;
	UINT_16 Counter;
	UINT_16 max_size;


	/* Make sure passed parameters are valid */
	if (datalogger == NULL || StreamNumber >= datalogger->NumberOfStreams)
		return 0;

	/* Compute size of one stream */
	StreamSize = datalogger->NumberOfSamples * datalogger->NumberOfVariables;

	/* Get size of compressed Data Log */
	NumberOfBytes = GetStreamSize(datalogger, StreamNumber);

    max_size = MAXDATALOGBUFFERSIZE;
	/* Make sure no boundaries are crossed */
	if ((NumberOfBytes > (StreamSize * 4)) || (NumberOfBytes > max_size) )
		return 0;

	/* Compute start Position in Datalog Data Buffer */
	Position =  StreamNumber * StreamSize;
	Position += datalogger->queueposition[StreamNumber];

	/* Loop thru Datalog Data Buffer pulling out long words from the */
	/* end of the buffer */
	Counter = (NumberOfBytes / 4);
	while (Counter > 0)
	{
		/* If the buffer wraps around then reset to end of buffer */
		if (Position <= StreamNumber * StreamSize)
		{
			Position = (UINT_32)((StreamNumber + 1) * StreamSize);
		}

		DatalogBuffer[--Counter] = datalogger->Data[--Position].DWords.DWord0;

	}

	*OriginPosition = datalogger->DefaultDownCount;

	return NumberOfBytes;
}

/****************************************************************************
*
* .b
*   Procedure Name:                 SaveDatalogBytes_tds
*
*   Abstract:
*       stored the environmental data associated with a TDSL fault
*
*   INPUTS:
*
*       Globals:
*           NumOfVarCnt
*
*
*   OUTPUTS
*
*       Globals:
*           datalog buffer
*
*   Functional Description:
*
* .b
*
*   History:        
*   Revised:        02/27/2003    R.Cirinelli @ Bombardier
*                   - added functionality to correctly store the datalog
*					information when the number of environmental variables
*					is an odd number.  The buffer is filled in double words
*					therefore when an odd number of variables was defined
*					the information was incorrect.  The function
*					will look for the last variable and stuff a dummy word
*					the function will then decrease the buffer count so 
*					that the first variable of the next sample is not
*					missed
*
*****************************************************************************/
void SaveDatalogBytes_tds(  UINT_8                  *ByteBuffer,
						UINT_16                 NumberOfBytes,
						struct datalogqueue_t   *datalogger,
						UINT_16                 StreamNumber,
						UINT_8     OddNumVars )
{
	UINT_16     Count;
	UINT_32     position;
	UINT_32     startposition;

	/* Get Starting position in Data Buffer for next gob of data */
	startposition =  StreamNumber *
					 datalogger->NumberOfSamples *
					 datalogger->NumberOfVariables;

	position = startposition + datalogger->queueposition[StreamNumber];

	/* Loop thru the bytes in the buffer in chunks of 4 bytes */

	for(Count = 0; Count < NumberOfBytes; Count += 4)
	{
		/* Check for wrap around */
		if (position >= (UINT_32)((StreamNumber + 1) *
								  datalogger->NumberOfSamples *
								  datalogger->NumberOfVariables))
		{
			position =  startposition;
		}

		/* Check to determine if there are an odd number of variabes
		   if there are,  increment the number of variables counter
		   to reflect the number of variable words to be stored. 
		   Since two words are saved at a time, increment by 2.
		   Added by Becki Cirinelli 2/27/03 to allow odd number
		   of variables */
		if (OddNumVars == 255)
			NumOfVarCnt = NumOfVarCnt + 2;
				
		/* Check to see if the number of variables read in is greater
		   than the total number of variables.  This will determine
		   if a dummy location has to be stuffed with zero's.  This is 
		   done when the last variable is read in when the total variable
		   count is an odd value */
		if (NumOfVarCnt >= datalogger->NumberOfVariables)
		{
		  datalogger->Data[position].Words.Word0 =
							*(UINT_16 *)&ByteBuffer[Count];
		  /* stuff last word with zeros so that the words are stored
		     correctly when the total variable count is zero */

		  //datalogger->Data[position].Words.Word1 = (UINT_16 *)0;
		  datalogger->Data[position].Words.Word1 = (UINT_16)0;

		  /*reset the variable count so that we can count up for the
		    next variable set */
		  NumOfVarCnt = 0;
		  /* reduce the count value by 2 so that the first variable
		     value is not missed.  If the first value is missed, the
			 remaining data will be skewed */
		  Count = Count - 2;
		}
		else
		{
		/* Stuff Data into Datalog Data Buffer */
		datalogger->Data[position].Words.Word0 =
										   *(UINT_16 *)&ByteBuffer[Count];
		datalogger->Data[position].Words.Word1 =
										   *(UINT_16 *)&ByteBuffer[Count + 2];
		}

		position++;

	}

	/* Save the next position in Data buffer */
	datalogger->queueposition[StreamNumber] = position - startposition;
}

#ifdef __cplusplus
}
#endif
