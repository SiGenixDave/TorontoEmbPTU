/***************************************************************************
*
* .b
*   Copyright (c) 2002 Bombardier Transportation (Holdings) USA, Inc.      
*
*   Project:
*               Common
*
*   File Name:
*               ptu2.c
*
*   SubSystem:
*               PTU
*
*   Procedures:
*               MessageManager
*
*   EPROM Drawing:
*
* .b
*
*   History:        07/10/94    Creation of Version 3.0         jsl
*   Revised:        09/13/95    ddp
*                   - Added compression layer for Streams
*                   10/5/95     ddp
*                   - Removed LZ Huffman compression layer for Streams
*                     Added a Type Crunching compression layer for Streams
*                   12/5/95     ddp
*                   - Fixed bug with Datalog indexinging at end of queue
*                     instead of at the start.
*                   12/5/95     ddp
*                   - Fixed bug with missing break in switch statement.
*					11/12/01    RAC
*					- added Update_EDT_EST_Flags to the SET_TIME_DATE case
*					  of the case statement in Message_Manager to update dst
*					  flags when the time is updated through the PTU
*              10/07/2002  Sarfaraz Taher
*              - Added the call to "setWV" in the case SEND_VARIABLE_VALUE
*                to enable integration with the Rhapsody generated code
*                for the PTU functionality.
*              11/12/2002 Sarfaraz Taher
*              - Deleted including the version.h file (same filename issue).
*                Modified the MessageManager routine in the same context. 
*                See function header for details.
*			   07/16/2003  Amadou Diop @ Bombardier Transportation
*			   - Modified the VCU DACSIZE from 4095 to 
*                4000 counts (10 V)
*			   10/26/2004  Amadou Diop
*			   - Added check for COMC PTU to process BBRAM
*				6/1/2010	Andrew Thomas
*				- Changes for IP PTU
*                 
***************************************************************************/
/*  Grab all of the compiler #pragma's.                                     */
#ifdef __cplusplus
extern "C" {
#endif


/*  Grab the PTU specific files.                                            */
#include "ptuprj.h"
#ifndef TEST_ON_PC
#include "io_def.h"
#include "ioclock.h"
#endif

#ifndef COMC_PTU
	#include "ptuip.h"
#ifndef TEST_ON_PC
	#include "fltinfo.h"
#endif
#endif

#include "ptu.h"
#ifndef TEST_ON_PC
#include "daylite.h"
#endif

/*  Declare the response union as global to limit the amount of stack       */
/*  needed by the PTU.                                                      */
extern MaxRequest_t DATAFARTYPE             Request;
extern MaxResponse_t DATAFARTYPE            Response;
extern void setWV(UINT_16 Index);
extern UINT_32                 TransactionCounter;


/****************************************************************************
*
* .b
*   Procedure Name:                 MessageManager
*
*   Abstract:
*       Message_Manager parses the passed request packet and build an
*       appropriate resonse packet and sends it through the serial port.
*
*   INPUTS:
*
*       Globals:
*
*       Constants:
*           TRUE                        TRUE constant
*           FALSE                       FALSE constant
*           STATIC                      identifier for the static fault count
*           DYNAMIC                     identifier for the dynamic fault count
*           ID_PCPTU                    SelfTest origin identifier
*           VERSIONNUMBER               system software version number
*           NUMDEFINEDVARS              number of variables that are defined
*           MODE_SELF_TEST              SelfTest mode identifier
*           STC_CMD_ACK_MSG             SelfTest command identifier
*           STC_NORMAL_ABORT            SelfTest command identifier
*           STC_CMD_ABORT_SES           SelfTest command identifier
*           MAX_CR_TLB_ENTRIES          number of variables used by the chart
*           NUMLOGGEDVARIABLES          number of variables that are datalogged
*           NUMOFDATALOGENTRIES         number of datalog frames
*
*       Procedure Parameters:
*           PassedRequest   Header_t *                  request packet that the
*                                                       response packet is to
*                                                       be build upon
*
*   OUTPUTS
*
*       Globals:
*           None
*
*       Returned Values:
*           None (void)
*
*   Functional Description:
*       Message_Manager enters a switch statement based on the message
*       type that has been passed into it by *PassedRequest.  The switch
*       build a response based on the data passed into it.  The response
*       is then transmitted out the serial port a call to TransmitMessage.
*
* .b
*
*   History : 07/10/94    Creation of Version 3.0             jsl
*             10/5/95     ddp
*             - Removed LZ Huffman compression layer for Streams
*               due to processing time constraints.
*               Instead added a Type Crunching algorithm while Logging Data.
*               This required passing the type of the Stream Variables back
*               to the WPTU as well as computing how much data actually needed
*               to be passed back to the WPTU to maintain a certain
*               Sample Rate.
*             12/14/95     ddp
*             - Changed the UPDATE_WATCH_ELEMENTS case. Now the DataType
*               is a UINT_16.
*             02/21/96     ddp
*             - Changed the READ_VARIABLE_VALUE case. Now the DataType
*               is a UINT_16.
*             03/08/96     ddp
*             - Changed CHANGE_EVENT_LOG and GET_EVENT_LOG to pass back
*               the Data Log Recording info and the Number Of Event Log resp.
*			  11/12/01    RAC
*			  - added Update_EDT_EST_Flags to the SET_TIME_DATE case
*			    of the case statement to update dst flags when the
*			    time is updated through the PTU
*             11/12/2002 Sarfaraz Taher 
*             - Changed code in the case GET_EMBEDDED_INFORMATION to
*               obtain the version string via a function instead of 
*               using the SWVERSIONSTRING directly. This is to allow the
*               version.h file to be located in a separate directory
*               (same filename conflict issue).
*****************************************************************************/
void MessageManager(Header_t *PassedRequest)
{
	UINT_16                 Index;
	UINT_16                 Counter;
	SignedUnion_t           TempSignedUnion;
	UINT_16                 NumberOfBytes;
	UINT_8                  *version_string;

	/*  Set the response type to the request type. */
	Response.PacketType = PassedRequest->PacketType;

	/*  Switch on the request type.  */
	switch (PassedRequest->PacketType)
	{
		case SET_WATCH_ELEMENT:
			TransmitACK();

			GlobalPTUData.WatchElement
				[((SetWatchElementReq_t *)PassedRequest)->ElementIndex] =
				((SetWatchElementReq_t *)PassedRequest)->DictionaryIndex;

			break;

		case SET_WATCH_ELEMENTS:
			TransmitACK();

			for (Index = 0; Index < WATCHSIZE; Index++)
				GlobalPTUData.WatchElement[Index] =
					((SetWatchElementsReq_t *)PassedRequest)->
						WatchElement[Index];

			break;

		case UPDATE_WATCH_ELEMENTS:
			Counter = 0;

			for (Index = 0; Index < WATCHSIZE; Index++)
			{
				if ( (GlobalPTUData.WatchElement[Index] == 0xffff) ||
					 (GlobalPTUData.WatchElement[Index] == 0xfffe) )
					continue;

				GetVariableValue( GlobalPTUData.WatchElement[Index],
								  &TempSignedUnion );

				if ( (TempSignedUnion.Unsigned ==
					  GlobalPTUData.PrevWatchValues[Index].Unsigned) &&
					  !(((UpdateWatchElementsReq_t *)PassedRequest)->ForceFullUpdate) )
					continue;

				((UpdateWatchElementsRes_t *)&Response)->
					WatchElement[Counter].NewValue.Unsigned = TempSignedUnion.Unsigned;

				((UpdateWatchElementsRes_t *)&Response)->
					WatchElement[Counter].Index = Index;

				GlobalPTUData.PrevWatchValues[Index].Unsigned =
					TempSignedUnion.Unsigned;

				switch (VariableDef[GlobalPTUData.WatchElement[Index]].type_id)
				{
					case UINT_8_TYPE:
					case UINT_16_TYPE:
					case UINT_32_TYPE:
						((UpdateWatchElementsRes_t *)&Response)->
							WatchElement[Counter++].DataType = (UINT_16)UNSIGNED;
						break;

					case INT_8_TYPE:
					case INT_16_TYPE:
					case INT_32_TYPE:
						((UpdateWatchElementsRes_t *)&Response)->
							WatchElement[Counter++].DataType = (UINT_16)SIGNED;
						break;
				}
			}

			((UpdateWatchElementsRes_t *)&Response)->NumberOfUpdates = Counter;

			TransmitMessage((Header_t *)&Response,
							(UINT_16)(sizeof(Header_t) + 2 +
									  (sizeof(WatchElement_t) * Counter)));
			break;

		case READ_VARIABLE_VALUE:
			Index = ((ReadVariableReq_t *)PassedRequest)->DictionaryIndex;

			GetVariableValue(Index,
							 &(((ReadVariableRes_t *)&Response)->CurrentValue));

			switch (VariableDef[Index].type_id)
			{
				case UINT_8_TYPE:
				case UINT_16_TYPE:
				case UINT_32_TYPE:
					((ReadVariableRes_t *)&Response)->DataType =
														(UINT_16)UNSIGNED;
					break;

				case INT_8_TYPE:
				case INT_16_TYPE:
				case INT_32_TYPE:
					((ReadVariableRes_t *)&Response)->DataType =
														(UINT_16)SIGNED;
					break;
			}

			TransmitMessage((Header_t *)&Response,
							(UINT_16)sizeof(ReadVariableRes_t));
			break;

		case SEND_VARIABLE_VALUE:
			TransmitACK();

			debugPrintf("SEND_VARIABLE_VALUE\n");

			Index = ((ReadVariableReq_t *)PassedRequest)->DictionaryIndex;

#ifndef COMC_PTU
#ifndef TEST_ON_PC
			if (VariableDef[Index].AttributeFlags & PTUD_BBRAM)
				start_cbram_write();
#endif
#endif
			switch (VariableDef[Index].type_id)
			{
				case UINT_8_TYPE:
					*(UINT_8 *)VariableDef[Index].var_start_addr =
						((SendVariableReq_t *)PassedRequest)->NewValue.Unsigned;
					break;

				case INT_8_TYPE:
					*(INT_8 *)VariableDef[Index].var_start_addr =
						((SendVariableReq_t *)PassedRequest)->NewValue.Signed;
					break;

				case UINT_16_TYPE:
					*(UINT_16 *)VariableDef[Index].var_start_addr =
						((SendVariableReq_t *)PassedRequest)->NewValue.Unsigned;
					break;

				case INT_16_TYPE:
					*(INT_16 *)VariableDef[Index].var_start_addr =
						((SendVariableReq_t *)PassedRequest)->NewValue.Signed;
					break;

				case UINT_32_TYPE:
					*(UINT_32 *)VariableDef[Index].var_start_addr =
						((SendVariableReq_t *)PassedRequest)->NewValue.Unsigned;
					break;

				case INT_32_TYPE:
					*(INT_32 *)VariableDef[Index].var_start_addr =
						((SendVariableReq_t *)PassedRequest)->NewValue.Signed;
					break;
			}

#ifndef TEST_ON_PC
#ifndef COMC_PTU
			if (VariableDef[Index].AttributeFlags & PTUD_BBRAM)
				end_cbram_write();
#endif
            /* added to support the Rhapsody generated code */
            setWV(Index);
#endif
			break;

		case GET_DICTIONARY_SIZE:
			((GetDictionarySizeRes_t *)&Response)->DictionarySize =
				NUMDEFINEDVARS;

			TransmitMessage((Header_t *)&Response,
							(UINT_16)sizeof(GetDictionarySizeRes_t) );
			break;

		case GET_VARIABLE_INFORMATION:
			Index = ((GetVariableInfoReq_t *)PassedRequest)->DictionaryIndex;

			switch (VariableDef[Index].type_id)
			{
				case UINT_8_TYPE:
				case UINT_16_TYPE:
				case UINT_32_TYPE:
					((GetVariableInfoRes_t *)&Response)->DataType =
														(UINT_16)UNSIGNED;
					break;

				case INT_8_TYPE:
				case INT_16_TYPE:
				case INT_32_TYPE:
					((GetVariableInfoRes_t *)&Response)->DataType =
														(UINT_16)SIGNED;
					break;
			}

			((GetVariableInfoRes_t *)&Response)->MaxScale =
							GlobalPTUData.VariableInfo[Index].max_scale;

			((GetVariableInfoRes_t *)&Response)->MinScale =
							GlobalPTUData.VariableInfo[Index].min_scale;

			((GetVariableInfoRes_t *)&Response)->AttributeFlags =
							VariableDef[Index].AttributeFlags;

			TransmitMessage((Header_t *)&Response,
							(UINT_16)sizeof(GetVariableInfoRes_t)   );
			break;

		case GET_EMBEDDED_INFORMATION: 
#ifndef TEST_ON_PC
			version_string = GetVersionString();
#else
			debugPrintf ("Get Embedded Info from PC request\n");

		    version_string = "TOPCVC3508";
#endif
		    strncpy( ((GetEmbeddedInfoRes_t *)&Response)->SoftwareVersion,
					 (const char *)version_string, 40);

#ifndef COMC_PTU
#ifndef TEST_ON_PC
			GetCarID( ((GetEmbeddedInfoRes_t *)&Response)->CarID );
#else
			strcpy( ((GetEmbeddedInfoRes_t *)&Response)->CarID, "1234");
#endif
#endif
			strncpy( ((GetEmbeddedInfoRes_t *)&Response)->SubSystemName,
					 WATCHWINDOWTITLE, 40);

			strncpy( ((GetEmbeddedInfoRes_t *)&Response)->IdentifierString,
					 IDENTIFIERSTRING, 4);

			((GetEmbeddedInfoRes_t *)&Response)->ConfigurationMask =
					PTUCONFIGURATION;

			TransmitMessage( (Header_t *)&Response,
							 (UINT_16)sizeof(GetEmbeddedInfoRes_t));
			break;

		case GET_CHART_MODE:
			((GetChartModeRes_t *)&Response)->CurrentChartMode =
				GlobalPTUData.ChartRecorderMode;

			TransmitMessage( (Header_t *)&Response,
						 (UINT_16)sizeof(GetChartModeRes_t));
			break;

		case SET_CHART_MODE:
			TransmitACK();

			switch (((SetChartModeReq_t *)PassedRequest)->TargetChartMode)
			{
				case DATAMODE:
				case RAMPMODE:
				case ZEROMODE:
				case FULLMODE:
					GlobalPTUData.ChartRecorderMode =
						((SetChartModeReq_t *)PassedRequest)->TargetChartMode;
					break;
			}


			break;

		case GET_CHART_INDEX:
			Index = ((GetChartIndexReq_t*)PassedRequest)->ChartIndex;

			((GetChartIndexRes_t *)&Response)->VariableIndex =
				GlobalPTUData.ChartRecorderElement[Index];

			TransmitMessage((Header_t *)&Response,
							(UINT_16)sizeof(GetChartIndexRes_t) );
            
			break;

		case SET_CHART_INDEX:
			TransmitACK();

			GlobalPTUData.ChartRecorderElement
				[((SetChartIndexReq_t *)PassedRequest)->ChartIndex] =
					((SetChartIndexReq_t *)PassedRequest)->VariableIndex;

			break;

		case SET_CHART_SCALE:
			TransmitACK();

			GlobalPTUData.VariableInfo[
				((SetChartScaleReq_t *)&Request)->DictionaryIndex].max_scale =
					((SetChartScaleReq_t *)&Request)->MaxScale;

			GlobalPTUData.VariableInfo[
				((SetChartScaleReq_t *)&Request)->DictionaryIndex].min_scale =
					((SetChartScaleReq_t *)&Request)->MinScale;


			break;


		case GET_WATCH_VALUES:
			for (Counter = 0; Counter < WATCHSIZE; Counter++)
			{
				Index = ((GetWatchValuesReq_t *)PassedRequest)->WatchIndexes[Counter];

				switch (VariableDef[Index].type_id)
				{
					case UINT_8_TYPE:
					case UINT_16_TYPE:
					case UINT_32_TYPE:
						((GetWatchValuesRes_t *)&Response)->DataTypes[Counter] = UNSIGNED;
						break;

					case INT_8_TYPE:
					case INT_16_TYPE:
					case INT_32_TYPE:
						((GetWatchValuesRes_t *)&Response)->DataTypes[Counter] = SIGNED;
						break;
				}

				GetVariableValue(
					Index,
					&(((GetWatchValuesRes_t *)&Response)->WatchValues[Counter]) );
			}

			TransmitMessage((Header_t *)&Response,
							(UINT_16)sizeof(GetWatchValuesRes_t)    );
			break;

#ifndef TEST_ON_PC
		case GET_TIME_DATE:
			GetTimeDate(&Response);
			
			TransmitMessage((Header_t *)&Response,
							(UINT_16)sizeof(GetTimeDateRes_t)   );
			break;

		case SET_TIME_DATE:
			TransmitACK();
			
			SetTimeDate((MaxRequest_t DATAFARTYPE *)PassedRequest);
			
			/*Added for Daylite savings time - Becki Cirinelli 11-12-01
			this will update the spring & fall flags when the time
			is changed via the PTU*/
			//Update_DST_ST_Flags();
			break;

		case START_CLOCK:
			TransmitACK();

			StartRTC();
			break;

		case STOP_CLOCK:
			TransmitACK();

			StopRTC();
			break;

#ifndef COMC_PTU
		case START_SELF_TEST_TASK:
			TransmitACK();
			Start_self_test_task_req();
			break;

		case SELF_TEST_COMMAND:
			TransmitACK();
			Self_test_cmd_req(PassedRequest);
			break;

		case GET_SELF_TEST_PACKET:
			Get_self_test_packet_req(&Response);
			break;

		case EXIT_SELF_TEST_TASK:
			TransmitACK();
			Exit_self_test_task_req();
			break;
#endif
#endif

		case SET_FAULT_LOG:
			TransmitACK();

			SetFaultLogger( GlobalFaultLog,
							((SetFaultLogReq_t *)PassedRequest)->TargetState);

			break;

		case GET_FAULT_INDICES:
			((GetFaultIndicesRes_t *)&Response)->Oldest =
								GetOldestFaultIndex(GlobalFaultLog);
			((GetFaultIndicesRes_t *)&Response)->Newest =
								GetNewestFaultIndex(GlobalFaultLog);

			TransmitMessage((Header_t *)&Response,
							(UINT_16)sizeof(GetFaultIndicesRes_t)   );
			break;

		case GET_FAULT_DATA:
			Index = GetFaultStructure(
						GlobalFaultLog,
						((GetFaultDataReq_t *)PassedRequest)->FaultIndex,
						((GetFaultDataReq_t *)PassedRequest)->NumberOfFaults,
						((GetFaultDataRes_t *)&Response)->Buffer );

			((GetFaultDataRes_t *)&Response)->BufferSize = Index;

			TransmitMessage((Header_t *)&Response,
							(UINT_16)(sizeof(Header_t) + 2 + Index) );
			break;

		case CLEAR_EVENTLOG:
			TransmitACK();

			PurgeFaultLogger(GlobalFaultLog);
			ClearDataLogger(GlobalDataLog);

			break;

		case INITIALIZE_EVENTLOG:
			TransmitACK();

			InitializeFaultLogger(GlobalFaultLog, GlobalDataLog);
			InitializeDataLogger(GlobalDataLog);

			break;

		case GET_FAULT_FLAG:
			NumberOfBytes = GetEventEnableFlags(
								GlobalFaultLog,
								((GetFaultFlagRes_t *)&Response)->EnableFlag);

			((GetFaultFlagRes_t *)&Response)->BufferSize = NumberOfBytes;

			TransmitMessage( (Header_t *)&Response,
							 (UINT_16)(sizeof(Header_t) + 2 + NumberOfBytes) );
			break;

		case GET_STREAM_FLAG:

			NumberOfBytes = GetDatalogTriggerFlags(
								GlobalFaultLog,
								((GetStreamFlagRes_t *)&Response)->DatalogFlag);

			((GetStreamFlagRes_t *)&Response)->BufferSize = NumberOfBytes;

			TransmitMessage( (Header_t *)&Response,
							 (UINT_16)(sizeof(Header_t) + 2 + NumberOfBytes) );


			break;

		case SET_FAULT_FLAG:
			TransmitACK();

			SetFaultTable( GlobalFaultLog,
						   ((SetFaultFlagReq_t *)&Request)->TaskID,
						   ((SetFaultFlagReq_t *)&Request)->FaultID,
						   ((SetFaultFlagReq_t *)&Request)->EnableFlag );

			SetTriggerTable( GlobalFaultLog,
							 ((SetFaultFlagReq_t *)&Request)->TaskID,
							 ((SetFaultFlagReq_t *)&Request)->FaultID,
							 ((SetFaultFlagReq_t *)&Request)->DatalogFlag);

			break;

		case GET_FAULT_HISTORY:
			((GetFaultHistoryRes_t *)&Response)->DynamicHistory =
				GetDynamicFaultHistory( GlobalFaultLog,
										((GetFaultHistoryReq_t *)&Request)->TaskID,
										((GetFaultHistoryReq_t *)&Request)->FaultID );

			((GetFaultHistoryRes_t *)&Response)->StaticHistory  =
				GetStaticFaultHistory(  GlobalFaultLog,
										((GetFaultHistoryReq_t *)&Request)->TaskID,
										((GetFaultHistoryReq_t *)&Request)->FaultID );

			TransmitMessage((Header_t *)&Response,
							(UINT_16)sizeof(GetFaultHistoryRes_t)   );
			break;

		case GET_DATALOG_STATUS:
			((GetDatalogStatusRes_t *)&Response)->NumberOfDatalogs =
											GetCurrentQueue(GlobalDataLog);

			TransmitMessage((Header_t *)&Response,
							(UINT_16)sizeof(GetDatalogStatusRes_t)  );
			break;

		case GET_DATALOG_BUFFER:
			NumberOfBytes =
				GetDataLogData(
						GlobalDataLog,
						((GetDatalogBufferReq_t *)PassedRequest)->DatalogIndex,
						((GetDatalogBufferRes_t *)&Response)->DatalogBuffer,
						&((GetDatalogBufferRes_t *)&Response)->TimeOrigin);

			((GetDatalogBufferRes_t *)&Response)->BufferSize = NumberOfBytes;

			TransmitMessage( (Header_t *)&Response,
							 (UINT_16)(sizeof(Header_t) + 4 + NumberOfBytes) );


			break;

		case SET_STREAM_INFORMATION:
			TransmitACK();

			SetStreamInformation( GlobalDataLog,
								  &((SetStreamInfoReq_t *)PassedRequest)->Information );

			break;

		case GET_STREAM_INFORMATION:

			GetStreamInformation( GlobalDataLog,
								  ((GetStreamInfoReq_t *)PassedRequest)->StreamNumber,
								  &((GetStreamInfoRes_t *)&Response)->Information     );

			TransmitMessage( (Header_t *)&Response,
							 (UINT_16)sizeof(GetStreamInfoRes_t) );

			break;

		case GET_DEFAULT_STREAM:

			GetDefaultStreamInformation( GlobalDataLog,
										 &((GetStreamInfoRes_t *)&Response)->Information );

			TransmitMessage( (Header_t *)&Response,
							 (UINT_16)sizeof(GetStreamInfoRes_t) );

			break;

		case SET_CARID:
			TransmitACK();
#ifdef TEST_ON_PC
			SetCarID( ((SetCarIDReq_t *)PassedRequest)->NewCarID );
#else
			start_cbram_write();
			SetCarID( ((SetCarIDReq_t *)PassedRequest)->NewCarID );
			end_cbram_write();
#endif

			break;

		case CHANGE_EVENT_LOG:
			ChangeEventLog( ((ChangeEventLogReq_t *)PassedRequest)->NewEventLog,
							&((ChangeEventLogRes_t *)&Response)->ChangeStatus,
							&((ChangeEventLogRes_t *)&Response)->DataRecordingRate,
							&((ChangeEventLogRes_t *)&Response)->MaxTasks,
							&((ChangeEventLogRes_t *)&Response)->MaxEvents);

			TransmitMessage( (Header_t *)&Response,
							 (UINT_16)sizeof(ChangeEventLogRes_t) );
			break;

		case GET_EVENT_LOG :
			((GetEventLogRes_t *)&Response)->CurrentEventLog = CurrentEventLog;
			((GetEventLogRes_t *)&Response)->NumberEventLogs = NUMOFEVENTLOGS;

			TransmitMessage( (Header_t *)&Response,
							 (UINT_16)sizeof(GetEventLogRes_t) );
			break;
		
		case TERMINATECONNECTION:
			/* Intentionally do nothing; TCP server handles a FIN,ACK from the client and closes/
			 * shutdowns the socket
			 */
			break;

		default:
			break;


	}
}

#ifdef __cplusplus
}
#endif


