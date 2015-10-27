/*******************************************************************************
*
* .b
*   Copyright (c) 1991-1995,2000 DaimleerChrysler Rail Systems Inc.
*
*   Project :
*               Common
*
*   File Name :
*               ptu.h
*
*   Subsystem :
*               PTU
*
*   EPROM Drawing   5624B95
*
* .b
*
*   History :   ??/??/??    J. Lyon - Creation
*   Revised :   06/30/95    DDP @ ATSI
*               - Added faulthook to DataLog Structure
*               - Added this header
*               07/10/95    DDP @ ATSI
*               - Added prototype for InitializeChartRecorder()
*               10/03/95    DDP @ ATSI
*               - Added prototype for GetStreamSize()
*               - Modified prototype for FillDataQueue()
*               10/06/95    DDP @ ATSI
*               - Modified to handle multiple fault and data logs
*               11/13/95    DDP @ ATSI
*               - Modified for Mobile PTU (added ResponseType to DPP)
*               11/17/95    DDP @ ATSI
*               - Cleaned up while porting to Motorola.
*                   . removed all ints and chars and replaced with
*                     INT_16, INT_8.
*                   . also ensure that all structures/unions within
*                     another structure are on an even boundary
*                   . changed MAX_VAR_LENGTH to 26
*                   . added MOTOROLA_SOM
*               11/17/95    DDP @ ATSI
*               - Changed DataType in WatchElement_t to a UINT_16
*               - Changed SetInfo in GetSelfTestPacketRes_t to a UINT_16
*               02/20/96    DDP @ Adtranz
*               - Modified GetFaultDataReq_t to pass the number of fault
*                 for which fault data must be retrieved.
*               - Correspondingly, The buffer size for Fault Data has
*                 been increased to 4K.
*               03/10/96    DDP @ Adtranz
*               - Modified to pass the Data Recording Rate for Data
*                 Logging for each Event Log back to the WPTU.
*    			12/23/99	RAZ @ADtranz
*               - Changed scale_buffer in ptu_globals from INT_8 to INT_16 for
*                 use on wmata project.
*               12/31/99    RAZ @ADtranz
*               - Added prototype for chart recorder service.
*                 Added #define for Min and Max chart channels.
*               01/17/2000 S.Taher @ ADtranz
*               Bound the file with "#ifdef" - "#endif" to avoid redefinition
*               of variables if this file is included in more files.
*               06/21/2000  D.Schnewlin @ Adtranz
*               - Renamed function LogFault() to ExtendedLogFault()
*               - Defined macros LogFault() and LogTdsFault()
*               - Added functions LogTdsData(), LoadFaultHeaderWithoutTime(),
*                 psv_ed_clear_state_table(), psv_ed_read_life_sign_counter(),
*                 psv_ed_fatal_error_status() and psv_ed_main().
*               08/22/2000  J.Novacek @ Adtranz
*					 - Revised LOGGER2_NUM_OF_DATALOG_ENTRIES from 100 to 80 based
*                 on parameters configured in CAPE/C function blocks
*                 for the DCUs.
*               04/09/2001  J.Novacek @ Adtranz  Revised
*                           LOGGER0_NUM_OF_DATALOG_ELEMENTS from 3 to 6,
*                           LOGGER1_NUM_OF_DATALOG_ELEMENTS from 3 to 6, and
*                           LOGGER2_MAX_NUM_OF_FAULTS from 3 to 50 for TDSL.
*				8/14/2001   Becki Cirinelli @ Bombardier Transportation
*							added PTUCONFIGURATION and NUMOFEVENTLOGS to file.
*							moved from ptupaqa.h
*				04/03/2002  Becki Cirinelli @ Bombardier Transportation
*							added function prototypes for fixed chart
*							recorder functions
*               11/12/2002  Sarfaraz Taher @ Bombardier Transportation
*                           Added the prototypes for GetSwVersion and
*                           GetVersionString.
*               11/21/2002  Sarfaraz Taher @ Bombardier Transportation
*                           Moved the fault logger specification information
*                           from this file to a new file ptulogger.h.
*               06/17/2003  John Novacek @ Bombardier Transportation
*	                         Revised NUMOFEVENTLOGS to 6 from 4 based on logs
*                           implemented for Pitt LRV.
*				6/1/2010	Andrew Thomas
*							- Changes for IP PTU
*				08/17/2010	Erik Holm
*							-  Added macro TCP_SOCKET_TIMEOUT
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _PTU_H_
#define _PTU_H_

#ifndef __ptuconst__    /* comment */
#include "ptuconst.h"
#endif

#ifndef __ptuprj__    /* comment */
#include "ptuprj.h"
#endif

#ifdef TEST_ON_PC
#include "myWrapper.h"
#else
#include "rts_api.h"
#include "os_api.h"
#include "mon_api.h"
#endif

#ifndef TRUE    /* comment */
#define     TRUE                    1
#endif

#ifndef FALSE  /* comment */
#define     FALSE                   0
#endif

#define     DISABLE                 0
#define     ENABLE                  1
#define     UINT_8_TYPE             0
#define     UINT_16_TYPE            1
#define     UINT_32_TYPE            2
#define     INT_8_TYPE              3
#define     INT_16_TYPE             4
#define     INT_32_TYPE             5
#define     FARPOINTER              5
#define     PTUPTR                  void *
#define     MAX_EVAL_SIZE           8
#define     MAX_SCAN_TBL_ENTRIES    8
#define     MAX_CR_TBL_ENTRIES      8
#define     MAX_SCAN_VARS           8
#define     MAX_CR_VARS             8
#define     MAX_VAR_LENGTH          26
#define     HEX                     0x01
#define     DECIMAL                 0x02
#define     BINARY                  0x03

#define     PTUD_BBRAM              0x80000000l
#define     PTUD_DESC1              0x40000000l
#define     PTUD_DESC2              0x20000000l
#define     PTUD_DESC3              0x10000000l
#define     PTUD_PSSWD1             0x08000000l
#define     PTUD_PSSWD2             0x04000000l
#define     PTUD_READONLY           0x02000000l

#define     PTUCONFIG_WATCH         0x00000001l
#define     PTUCONFIG_CHART         0x00000002l
#define     PTUCONFIG_EVENTLOG      0x00000004l
#define     PTUCONFIG_DATALOG       0x00000008l
#define     PTUCONFIG_CLOCK         0x00000010l
#define     PTUCONFIG_SELFTEST      0x00000020l
#define     PTUCONFIG_TERMINAL      0x00000040l
#define     PTUCONFIG_DATABASE      0x00000080l


#define     INCHES                  01
#define     FEET                    02
#define     MILES                   03
#define     MILLIMETERS             04
#define     CENTIMETERS             05
#define     METERS                  06
#define     KILOMETERS              07
#define     MPH                     10
#define     MPHPERSEC               11
#define     KPH                     15
#define     FEETSEC2                20
#define     MILESSEC2               21
#define     METERSSEC2              22
#define     KILOSEC2                23
#define     MILESHRSEC2             26
#define     METERSSEC3              27
#define     VOLTS                   30
#define     VOLTSPERSEC             31
#define     MILLIAMPS               34
#define     AMPS                    35
#define     WATTS                   36
#define     KILOWATTHOUR            37
#define     KILOWATTS               38
#define     MEGAWATTHOURS           39
#define     RPM                     40
#define     FOOTPOUNDS              50
#define     NEWTONMETERS            51
#define     PERCENT                 60
#define     SECONDS                 70
#define     MILLISECONDS            71
#define     MINUTES                 72
#define     HOURS                   73
#define     HERTZ                   74
#define     DEGREESF                80
#define     DEGREESC                81
#define     POUNDS                  90
#define     KILOGRAMS               95
#define     PSI                     96

#define     DIV10                   0x0100
#define     DIV100                  0x0200
#define     DIV1000                 0x0300
#define     DIV10000                0x0400
#define     DIVp005                 0x0500
#define     DIVp022                 0x0600
#define     DIVp03                  0x0700
#define     DIVp207                 0x0800
#define     DIVp311                 0x0900
#define     DIVp48                  0x0a00
#define     DIVp499                 0x0b00
#define     DIV5                    0x0c00
#define     DIV20                   0x0d00
#define     DIV100000               0x0e00
#define     DIV10000000             0x0f00

#define     MUL10                   0x4100
#define     MUL100                  0x4200
#define     MUL1000                 0x4300
#define     MUL10000                0x4400
#define     MULp005                 0x4500
#define     MULp022                 0x4600
#define     MULp03                  0x4700
#define     MULp207                 0x4800
#define     MULp311                 0x4900
#define     MULp48                  0x4a00
#define     MULp499                 0x4b00
#define     MUL5                    0x4c00
#define     MUL20                   0x4d00
#define     MUL100000               0x4e00
#define     MUL10000000             0x4f00

/*  Defines for ptu2.c:                                                     */
#define     SUCCESSFUL              0
//#define     TIMEOUT                 2
#define     CHECKSUM_ERROR          4
#define     MESSAGE_REC             255
#define     CHECKSUMMAXVALUE        0xffff
#define     SOM                     ':'
#define     PTU_ACK                 (0x04)
#define     PTU_NAK                 (0x06)
#define     SIGNED                  01
#define     UNSIGNED                02
#define     MAXREQUESTLENGTH        100
#define     MAXDATALOGBUFFERSIZE    \
      MAXFAULTBUFFERSIZE > (NUMLOGGEDVARIABLES * NUMOFDATALOGENTRIES * 4) ? \
      (MAXFAULTBUFFERSIZE + 50) : \
      ((NUMLOGGEDVARIABLES * NUMOFDATALOGENTRIES * 4) + 50)
#define     MAXRESPONSELENGTH       MAXDATALOGBUFFERSIZE

#define MINCHARTCHANNEL 0
#define MAXCHARTCHANNEL 8




/*  Defines for the PTU communications protocol.                            */
#define WATCHSIZE                   20

#define SET_WATCH_ELEMENT           2
#define SET_WATCH_ELEMENTS          3
#define UPDATE_WATCH_ELEMENTS       4
#define SET_CHART_SCALE             5
#define READ_VARIABLE_VALUE         6
#define SEND_VARIABLE_VALUE         7
#define GET_DICTIONARY_SIZE         8
#define GET_VARIABLE_INFORMATION    9
#define GET_EMBEDDED_INFORMATION    10
#define GET_CHART_MODE              11
#define SET_CHART_MODE              12
#define GET_CHART_INDEX             13
#define SET_CHART_INDEX             14
#define GET_WATCH_VALUES            15
#define GET_TIME_DATE               16
#define SET_TIME_DATE               17
#define START_SELF_TEST_TASK        18
#define SELF_TEST_COMMAND           19
#define GET_SELF_TEST_PACKET        20
#define EXIT_SELF_TEST_TASK         21
#define SET_FAULT_LOG               22
#define GET_FAULT_INDICES           23
#define GET_FAULT_HISTORY           24
#define GET_FAULT_DATA              25
#define GET_FAULT_FLAG              26
#define SET_FAULT_FLAG              27
#define GET_DATALOG_INFORMATION     30
#define GET_DATALOG_STATUS          31
#define GET_DATALOG_BUFFER          32
#define CLEAR_DATALOG               33
#define SET_CARID                   34
#define CLEAR_EVENTLOG              35
#define INITIALIZE_EVENTLOG         36
#define SET_STREAM_INFORMATION      37
#define GET_STREAM_INFORMATION      38
#define GET_DEFAULT_STREAM          39
#define START_CLOCK                 50
#define STOP_CLOCK                  51
#define CHANGE_EVENT_LOG            52
#define GET_EVENT_LOG               53
#define GET_STREAM_FLAG             54
#define TERMINATECONNECTION			102


#define DPP3                UINT_16     ResponseType;
#define DPP2                CHECKSUM_t  CheckSum;       DPP3
#define DPP1                UINT_16     PacketType;     DPP2
#define DATAPACKETPROLOG    UINT_16     PacketLength;   DPP1

/* fault log control */
#define DISABLE                 0
#define ENABLE                  1
#define PURGE                   2
#define MAXFAULTBUFFERSIZE      4096
#define MAXFAULTSIZE            255
#define DYNAMIC                 0
#define STATIC                  1
#define NUMOFTASKS              120
#define NUMOFFAULTS             100

#define DATAMODE                1
#define FULLMODE                2
#define RAMPMODE                3
#define ZEROMODE                4


/*  Defines for ptusrl.c: */
#define     CHANNELA                0
#define     CHANNELB                1
#define     NUMOFCHANNELS           2
#define     INCOMMING               0
#define     OUTGOING                1
#define     STDIN                   0x10
#define     STDOUT                  0x20
#define     STDERR                  0x40
#define     STDIO                   0x80
#define     SERIALBUFFERSIZE        246
#define     SERIALPIC               0x30

/*  The following are structure definitions for the PTU subystem.           */
/*  Structure definitions used globally.                                    */
union u_type
{
	UINT_8      u_int_8		__attribute__ ((packed));
	UINT_16     u_int_16	__attribute__ ((packed));
	UINT_32     u_int_32	__attribute__ ((packed));
	INT_8       s_int_8		__attribute__ ((packed));
	INT_16      s_int_16	__attribute__ ((packed));
	INT_32      s_int_32	__attribute__ ((packed));
};

struct VariableDef_t
{
	PTUPTR      var_start_addr	__attribute__ ((packed));
	INT_8       type_id			__attribute__ ((packed));

	UINT_32     max_scale		__attribute__ ((packed));
	INT_32      min_scale		__attribute__ ((packed));

	UINT_32     AttributeFlags	__attribute__ ((packed));
};

struct VariableInfo_t
{
	union u_type    PreviousValue       __attribute__ ((packed));
	UINT_32         max_scale       __attribute__ ((packed));
	INT_32          min_scale       __attribute__ ((packed));
};

typedef union
{
	UINT_32   Unsigned       __attribute__ ((packed));
	INT_32    Signed       __attribute__ ((packed));
} SignedUnion_t;

struct ptu_globals
{
	INT_16                      ChartRecorderMode       __attribute__ ((packed));
	INT_16                      PTUInitialized       __attribute__ ((packed));
	UINT_16                     BTUInterfaceEnabled       __attribute__ ((packed));

	struct VariableInfo_t       VariableInfo            [NUMDEFINEDVARS]       __attribute__ ((packed));
	UINT_16                     ChartRecorderElement    [MAX_CR_TBL_ENTRIES]       __attribute__ ((packed));
	UINT_16                     WatchElement            [WATCHSIZE]       __attribute__ ((packed));
	SignedUnion_t               PrevWatchValues         [WATCHSIZE]       __attribute__ ((packed));
	INT_16                      scale_buffer            [MAX_CR_TBL_ENTRIES]       __attribute__ ((packed));
};


typedef struct
{
	UINT_16 StreamVariable       __attribute__ ((packed));
	UINT_16 StreamVariableType       __attribute__ ((packed));
} StreamVariable_t;

typedef struct
{
	UINT_16          NumberOfVariables       __attribute__ ((packed));
	UINT_16          NumberOfSamples       __attribute__ ((packed));
	UINT_16          SampleRate       __attribute__ ((packed));
	StreamVariable_t StreamVariableInfo[NUMLOGGEDVARIABLES]       __attribute__ ((packed));
} StreamInformation_t;


/*  Structure definitions for the PTU communications protocol: */
typedef UINT_16 CHECKSUM_t;

typedef struct
{
	DATAPACKETPROLOG
} Header_t;

typedef struct
{
	DATAPACKETPROLOG
	INT_8 Data[MAXREQUESTLENGTH]       __attribute__ ((packed));
} MaxRequest_t;

typedef struct
{
	DATAPACKETPROLOG
	INT_8 Data[MAXRESPONSELENGTH]       __attribute__ ((packed));
} MaxResponse_t;

typedef struct
{
	UINT_16         Index       __attribute__ ((packed));
	SignedUnion_t   NewValue       __attribute__ ((packed));
	UINT_16         DataType       __attribute__ ((packed));
} WatchElement_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_8      ForceFullUpdate       __attribute__ ((packed));
} UpdateWatchElementsReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16         NumberOfUpdates       __attribute__ ((packed));
	WatchElement_t  WatchElement[WATCHSIZE]       __attribute__ ((packed));
} UpdateWatchElementsRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16     ElementIndex       __attribute__ ((packed));
	UINT_16     DictionaryIndex       __attribute__ ((packed));
} SetWatchElementReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16     WatchElement[WATCHSIZE]       __attribute__ ((packed));
} SetWatchElementsReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16     DictionaryIndex       __attribute__ ((packed));
} ReadVariableReq_t;

typedef struct
{
	DATAPACKETPROLOG
	SignedUnion_t   CurrentValue       __attribute__ ((packed));
	UINT_16         DataType       __attribute__ ((packed));
} ReadVariableRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16         DictionaryIndex       __attribute__ ((packed));
	SignedUnion_t   NewValue       __attribute__ ((packed));
} SendVariableReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 DictionarySize       __attribute__ ((packed));
} GetDictionarySizeRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 DictionaryIndex       __attribute__ ((packed));
} GetVariableInfoReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 DataType       __attribute__ ((packed));
	INT_32  MaxScale       __attribute__ ((packed));
	INT_32  MinScale       __attribute__ ((packed));
	UINT_32 AttributeFlags       __attribute__ ((packed));
} GetVariableInfoRes_t;

typedef struct
{
	DATAPACKETPROLOG
	INT_8   SoftwareVersion[41]       __attribute__ ((packed));
	INT_8   CarID[11]       __attribute__ ((packed));
	INT_8   SubSystemName[41]       __attribute__ ((packed));
	INT_8   IdentifierString[5]       __attribute__ ((packed));
	UINT_32 ConfigurationMask       __attribute__ ((packed));
} GetEmbeddedInfoRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_8  CurrentChartMode       __attribute__ ((packed));
} GetChartModeRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_8  TargetChartMode       __attribute__ ((packed));
} SetChartModeReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_8  ChartIndex       __attribute__ ((packed));
} GetChartIndexReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 VariableIndex       __attribute__ ((packed));
} GetChartIndexRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 VariableIndex       __attribute__ ((packed));
	UINT_8  ChartIndex       __attribute__ ((packed));
} SetChartIndexReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 DictionaryIndex       __attribute__ ((packed));
	INT_32  MaxScale       __attribute__ ((packed));
	INT_32  MinScale       __attribute__ ((packed));
} SetChartScaleReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 WatchIndexes[WATCHSIZE]       __attribute__ ((packed));
} GetWatchValuesReq_t;

typedef struct
{
	DATAPACKETPROLOG
	SignedUnion_t   WatchValues[WATCHSIZE]       __attribute__ ((packed));
	UINT_8          DataTypes[WATCHSIZE]       __attribute__ ((packed));
} GetWatchValuesRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_8  Hour       __attribute__ ((packed));
	UINT_8  Minute       __attribute__ ((packed));
	UINT_8  Second       __attribute__ ((packed));
	UINT_8  Year       __attribute__ ((packed));
	UINT_8  Month       __attribute__ ((packed));
	UINT_8  Day       __attribute__ ((packed));
} GetTimeDateRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_8  Hour       __attribute__ ((packed));
	UINT_8  Minute       __attribute__ ((packed));
	UINT_8  Second       __attribute__ ((packed));
	UINT_8  Year       __attribute__ ((packed));
	UINT_8  Month       __attribute__ ((packed));
	UINT_8  Day       __attribute__ ((packed));
} SetTimeDateReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_8  id       __attribute__ ((packed));
	UINT_8  xy_info       __attribute__ ((packed));
	UINT_16 data       __attribute__ ((packed));
} SelfTestCommandReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_8  Valid       __attribute__ ((packed));
	UINT_8  msg_mode       __attribute__ ((packed));
	UINT_16 set_info       __attribute__ ((packed));
	UINT_16 test_id       __attribute__ ((packed));
	UINT_8  buffer[10]       __attribute__ ((packed));  /* 6 for size of union below */
/*
	union st_test_result_data   result;
*/
	UINT_32 flags       __attribute__ ((packed));
	UINT_8  reserved[4]       __attribute__ ((packed));
} GetSelfTestPacketRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_8  TargetState       __attribute__ ((packed));
} SetFaultLogReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_32 Newest       __attribute__ ((packed));
	INT_32 Oldest       __attribute__ ((packed));
} GetFaultIndicesRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_32 FaultIndex       __attribute__ ((packed));
	UINT_16 NumberOfFaults       __attribute__ ((packed));
} GetFaultDataReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 BufferSize       __attribute__ ((packed));
	UINT_8  Buffer[MAXFAULTBUFFERSIZE]       __attribute__ ((packed));
} GetFaultDataRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 BufferSize       __attribute__ ((packed));
	UINT_16 EnableFlag[MAXFAULTBUFFERSIZE / 2]       __attribute__ ((packed));
} GetFaultFlagRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 BufferSize       __attribute__ ((packed));
	UINT_16 DatalogFlag[MAXFAULTBUFFERSIZE / 2]       __attribute__ ((packed));
} GetStreamFlagRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 TaskID       __attribute__ ((packed));
	UINT_16 FaultID       __attribute__ ((packed));
	UINT_8  EnableFlag       __attribute__ ((packed));
	UINT_8  DatalogFlag       __attribute__ ((packed));
} SetFaultFlagReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 TaskID       __attribute__ ((packed));
	UINT_16 FaultID       __attribute__ ((packed));
} GetFaultHistoryReq_t;

typedef struct
{
	DATAPACKETPROLOG
	INT_16 StaticHistory       __attribute__ ((packed));
	INT_16 DynamicHistory       __attribute__ ((packed));
} GetFaultHistoryRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 NumberOfDatalogs       __attribute__ ((packed));
} GetDatalogStatusRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 DatalogIndex       __attribute__ ((packed));
} GetDatalogBufferReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 TimeOrigin       __attribute__ ((packed));
	UINT_16 BufferSize       __attribute__ ((packed));
	UINT_32 DatalogBuffer[MAXDATALOGBUFFERSIZE / 4]       __attribute__ ((packed));
} GetDatalogBufferRes_t;

typedef struct
{
	DATAPACKETPROLOG
	INT_8   NewCarID[11]       __attribute__ ((packed));
} SetCarIDReq_t;

typedef struct
{
	DATAPACKETPROLOG
	StreamInformation_t Information       __attribute__ ((packed));
} SetStreamInfoReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 StreamNumber       __attribute__ ((packed));
} GetStreamInfoReq_t;

typedef struct
{
	DATAPACKETPROLOG
	StreamInformation_t Information       __attribute__ ((packed));
} GetStreamInfoRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 CurrentEventLog       __attribute__ ((packed));
	UINT_16 NumberEventLogs       __attribute__ ((packed));
} GetEventLogRes_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 NewEventLog       __attribute__ ((packed));
} ChangeEventLogReq_t;

typedef struct
{
	DATAPACKETPROLOG
	UINT_16 ChangeStatus       __attribute__ ((packed));
	UINT_16 DataRecordingRate       __attribute__ ((packed));
	UINT_16 MaxTasks       __attribute__ ((packed));
	UINT_16 MaxEvents       __attribute__ ((packed));
} ChangeEventLogRes_t;


typedef union
{
	struct
	{
		UINT_8  Byte0       __attribute__ ((packed));
		UINT_8  Byte1       __attribute__ ((packed));
		UINT_8  Byte2       __attribute__ ((packed));
		UINT_8  Byte3       __attribute__ ((packed));
	} Bytes;
	struct
	{
		UINT_16 Word0       __attribute__ ((packed));
		UINT_16 Word1       __attribute__ ((packed));
	} Words;
	struct
	{
		UINT_32 DWord0       __attribute__ ((packed));
	} DWords;
} CastUnion_t;


/*  Structure definitions for ptudatal.c:                                   */
struct    DataLogDef_t
{
	PTUPTR  DataLogAddr       __attribute__ ((packed));
	UINT_16 NumOfDataLogElements       __attribute__ ((packed));
	UINT_16 NumLoggedVariables       __attribute__ ((packed));
	UINT_16 NumOfDataLogEntries       __attribute__ ((packed));
	UINT_16 FaultTripPoint       __attribute__ ((packed));
	UINT_16 StreamSampleRate       __attribute__ ((packed));
	UINT_16 DataRecordingRate       __attribute__ ((packed));
	const UINT_16 DataLogElements[NUMLOGGEDVARIABLES]       __attribute__ ((packed));
	PTUPTR  DataLogDataAddr       __attribute__ ((packed));
};

/*
	The DataLogAddr of the structure 'DataLogDef_t' points
    to Data, which has the following Organization :

    struct SYMBOLIC_STRUCTURE_OF_DATALOGHUNK
    {
	    UINT_16     queueposition             [NumberOfStreams];
	    UINT_16     SampleRate                [NumberOfStreams];
	    UINT_16     SampleRateCounter         [NumberOfStreams];
	    UINT_16     faulthook                 [NumberOfStreams];
	    UINT_16     StreamVariable            [NumberOfStreams]
                                              [NumberOfVariables];
	    UINT_16     StreamVariableType        [NumberOfStreams]
                                              [NumberOfVariables];
	    UINT_16     DefaultStreamVariable     [NumberOfVariables];
	    UINT_16     DefaultStreamVariableType [NumberOfVariables];
    };
*/

/*
	When Allocating Data for where the DataLogAddr points to
	ENSURE that the number of BYTES allocated is
	atleast the sum of the values listed below ...
*/
#define SIZEOF_DATALOGHUNK(NumOfDatalogElements,                        \
                           NumLoggedVariables)                          \
          ( NumOfDatalogElements * sizeof(UINT_16)                      \
          + NumOfDatalogElements * sizeof(UINT_16)                      \
          + NumOfDatalogElements * sizeof(UINT_16)                      \
          + NumOfDatalogElements * sizeof(UINT_16)                      \
          + NumOfDatalogElements * NumLoggedVariables * sizeof(UINT_16) \
          + NumOfDatalogElements * NumLoggedVariables * sizeof(UINT_16) \
          + NumLoggedVariables * sizeof(UINT_16)                        \
          + NumLoggedVariables * sizeof(UINT_16)                        )

/*
	The DataLogDataAddr of the structure 'DataLogDef_t' points
    to Data, which has the following Organization :

    typedef CastUnion_t DATALOGDATAHUNK [NumOfDatalogElements]
                                        [NumOfDatalogEntries]
                                        [NumLoggedVariables];
*/

/*
	When Allocating Data for where the DataLogAreaAddr points to
	ENSURE that the number of BYTES allocated is
	atleast the sum of the values listed below ...
*/
#define SIZEOF_DATALOGDATAHUNK(NumOfDatalogElements,    \
                               NumOfDatalogEntries,     \
                               NumLoggedVariables)      \
          ( NumOfDatalogElements * NumOfDatalogEntries  \
          * NumLoggedVariables   * sizeof(CastUnion_t)  )

struct datalogqueue_t
{
	UINT_16     datarecordingrate       __attribute__ ((packed));
	UINT_16     downcount       __attribute__ ((packed));
	UINT_16     tripqueue       __attribute__ ((packed));
	UINT_16     datalogtrip       __attribute__ ((packed));
	UINT_16     currentqueue       __attribute__ ((packed));
	UINT_16     Enabled       __attribute__ ((packed));
	UINT_16     DefaultDownCount       __attribute__ ((packed));
	UINT_16     DefaultSampleRate       __attribute__ ((packed));
	UINT_16     NumberOfVariables       __attribute__ ((packed));
	UINT_16     NumberOfSamples       __attribute__ ((packed));
	UINT_16     NumberOfStreams       __attribute__ ((packed));
	UINT_16     *queueposition       __attribute__ ((packed));
	UINT_16     *SampleRate       __attribute__ ((packed));
	UINT_16     *SampleRateCounter       __attribute__ ((packed));
	UINT_16     *faulthook       __attribute__ ((packed));
	UINT_16     *StreamVariable       __attribute__ ((packed));
	UINT_16     *StreamVariableType       __attribute__ ((packed));
	UINT_16     *DefaultStreamVariable       __attribute__ ((packed));
	UINT_16     *DefaultStreamVariableType       __attribute__ ((packed));
	CastUnion_t *Data       __attribute__ ((packed));
};

/*  Structure definitions for ptufault.c:                                   */
struct faultpacketdef_t
{
	UINT_16             location       __attribute__ ((packed));
	UINT_16             size       __attribute__ ((packed));
	CastUnion_t         index       __attribute__ ((packed));
};

#ifdef __fltinfo__
struct minfaultpacket_t
{
	FAULTPACKETPROLOG
} __attribute__ ((packed));
#endif

struct    EventLogDef_t
{
	PTUPTR  EventLogAddr       __attribute__ ((packed));
	UINT_16 NumberOfTasks       __attribute__ ((packed));
	UINT_16 NumberOfFaultsPerTask       __attribute__ ((packed));
	UINT_16 MaxNumOfFaults       __attribute__ ((packed));
	UINT_16 SizeOfFaultQueue       __attribute__ ((packed));
};

/*
	The EventLogAddr of the structure EventLogDef_t points
    to Data, which has the following Organization :

    struct EVENTLOGHUNK
    {
	    BITFIELD_16             triggertable   [NumberOfTasks]
                                               [NumberOfFaultsPerTask]
                                               [16BITS];
	    BITFIELD_16             faulttable     [NumberOfTasks]
                                               [NumberOfFaultsPerTask]
                                               [16BITS];
	    UINT_16                 statichistory  [NumberOfTasks]
                                               [NumberOfFaultsPerTask];
	    UINT_16                 dynamichistory [NumberOfTasks]
                                               [NumberOfFaultsPerTask];
	    struct faultpacketdef_t faultinfo      [MaxNumOfFaults];
	    UINT_16                 faultqueue     [MaxNumOfFaults*
                                                sizeof(AVERAGE_FAULTPACKET)];
    };

*/

/*
	When Allocating Data the EventLogAddr points to
	ENSURE that the number of BYTES allocated is
	atleast the sum of the values listed below ...
*/
#define SIZEOF_EVENTLOGHUNK(NumberOfTasks,                          \
                            NumberOfFaultsPerTask,                  \
                            MaxNumOfFaults,                         \
                            SizeOfFaultQueue)                       \
          ( (NumberOfTasks * NumberOfFaultsPerTask / 8) + 1         \
          + (NumberOfTasks * NumberOfFaultsPerTask / 8) + 1         \
          + NumberOfTasks * NumberOfFaultsPerTask * sizeof(UINT_16) \
          + NumberOfTasks * NumberOfFaultsPerTask * sizeof(UINT_16) \
          + MaxNumOfFaults * sizeof(struct faultpacketdef_t)        \
          + SizeOfFaultQueue * sizeof(UINT_16)                      )


struct faultlogqueue_t
{
	struct datalogqueue_t   *linkedlogger       __attribute__ ((packed));
	UINT_16                 active       __attribute__ ((packed));
	UINT_16                 numberoffaults       __attribute__ ((packed));
	UINT_16                 infostart       __attribute__ ((packed));
	UINT_16                 datacursor       __attribute__ ((packed));
	UINT_16                 wordssaved       __attribute__ ((packed));
	UINT_16                 faultindex_msw       __attribute__ ((packed));
	UINT_16                 faultindex_lsw       __attribute__ ((packed));
	UINT_16                 tasks       __attribute__ ((packed));
	UINT_16                 eventspertask       __attribute__ ((packed));
	UINT_16                 maxevents       __attribute__ ((packed));
	UINT_16                 eventqueuesize       __attribute__ ((packed));
	UINT_16                 *triggertable       __attribute__ ((packed));
	UINT_16                 *statichistory       __attribute__ ((packed));
	UINT_16                 *dynamichistory       __attribute__ ((packed));
	UINT_16                 *faulttable       __attribute__ ((packed));
	struct faultpacketdef_t *faultinfo       __attribute__ ((packed));
	UINT_16                 *faultqueue       __attribute__ ((packed));
};

/*  Structure definitions are for ptusrl.c: */
typedef struct
{
	INT_16  Enabled       __attribute__ ((packed));
	INT_16  Head       __attribute__ ((packed));
	INT_16  Tail       __attribute__ ((packed));
	INT_16  PrimeFlag       __attribute__ ((packed));
	UINT_8  Buffer[SERIALBUFFERSIZE]       __attribute__ ((packed));
} SerialBuffer_t;


/*  The following are function prototypes for the PTU subsystem. */

/*  Prototype for ptu.c: */
void CODEFARTYPE    PTUMain                 (void);
INT_16              ptu_init                (void);
INT_16              GetPTUChar              (void);
INT_16              GetByte                 (void);
void                TransmitMessage         (Header_t *, UINT_16);
INT_16              GetRequestPacket        (Header_t *);
void                TransmitACK             (void);
void                GetVariableValue        (UINT_16, SignedUnion_t *);

/*  Prototypes for ptu2.c: */
void                MessageManager          (Header_t *);

/*  Prototypes for ptusrl.c: */
INT_16 				tgetc     				(INT_16);
void  				tputc     				(INT_16, UINT_8);
INT_16 				comm_init				(void);

#ifdef CCINTEL
#pragma interrupt (SerialInterruptHandler)
#endif

void CODEFARTYPE    SerialInterruptHandler  (void);

/*  Prototypes for ptuchart.c: */
void                Chart_Rec_Service       (void);

/*  Prototypes for ptudatal.c: */
void    LogData                     (UINT_16);
void    LogTdsData                  (UINT_16, UINT_16[], UINT_8,
                                     UINT_8, UINT_8, UINT_8);
void    InitializeDataLogger        (struct datalogqueue_t *);
void    ClearDataLogger             (struct datalogqueue_t *);
void    FillDataQueue               (struct datalogqueue_t *, UINT_16);
UINT_16 TriggerDataLogger           (struct datalogqueue_t *,
									 struct faultlogqueue_t *);
UINT_16 GetCurrentQueue             (struct datalogqueue_t *);
void    GetStreamInformation        (struct datalogqueue_t *, UINT_16,
									 StreamInformation_t *);
void    SetStreamInformation        (struct datalogqueue_t *,
									 StreamInformation_t *);
void    GetDefaultStreamInformation (struct datalogqueue_t *,
									 StreamInformation_t *);
UINT_16 GetStreamSize               (struct datalogqueue_t *, UINT_16);
UINT_16 GetDataLogData              (struct datalogqueue_t *, UINT_16,
									 UINT_32 *, UINT_16 *);

/*  Prototypes for ptufault.c:                                              */
void    InitializeFaultInterface    (void);

/*#ifdef __fltinfo__*/
void    ChangeEventLog              (UINT_16, UINT_16 *, UINT_16 *,
									 UINT_16 *, UINT_16 *);
UINT_8  InitializeFaultLogger       (struct faultlogqueue_t *,
									 struct datalogqueue_t *);
UINT_8  ExtendedLogFault            (UINT_16, struct minfaultpacket_t *,
									 UINT_16, UINT_8 tdsSpecific);
#define LogFault(log,fault,size)    ExtendedLogFault(log,fault,size, FALSE)
#define LogTdsFault(log,fault,size) ExtendedLogFault(log,fault,size,TRUE)
UINT_16 GetFaultSize                (struct faultlogqueue_t *, UINT_32);
UINT_16 GetFaultStructure           (struct faultlogqueue_t *, UINT_32,
									 UINT_16, void *);
UINT_32 GetNewestFaultIndex         (struct faultlogqueue_t *);
INT_32 GetOldestFaultIndex         (struct faultlogqueue_t *);
UINT_8  SetFaultTable               (struct faultlogqueue_t *, UINT_16,
									 UINT_16, UINT_8);
UINT_8  SetTriggerTable             (struct faultlogqueue_t *, UINT_16,
									 UINT_16, UINT_8);
UINT_8  SetFaultLogger              (struct faultlogqueue_t *, UINT_8);
UINT_16 GetEventEnableFlags			(struct faultlogqueue_t *, UINT_16 *);
UINT_16 GetDatalogTriggerFlags		(struct faultlogqueue_t *, UINT_16 *);
INT_16 GetDynamicFaultHistory      (struct faultlogqueue_t *, UINT_16,
									 UINT_16);
INT_16 GetStaticFaultHistory       (struct faultlogqueue_t *, UINT_16,
									 UINT_16);
UINT_8  PurgeFaultLogger            (struct faultlogqueue_t *);
UINT_8  PurgeDynamicHistory         (struct faultlogqueue_t *);
void    PurgeFaultLogNumber         (struct faultlogqueue_t *);
void    PurgeDataLogNumber          (struct faultlogqueue_t *,
									 struct datalogqueue_t *, UINT_16);
/*#endif*/

/* Prototype for PTU functions in project specific file */
#ifdef __fltinfo__
void    LoadFaultHeader             (struct minfaultpacket_t *);
void    LoadFaultHeaderWithoutTime  (struct minfaultpacket_t *);
UINT_8  SetupStreamDump             (struct faultlogqueue_t *);
#endif
void    StartScheduling             (void);
void    StopScheduling              (void);
void    ChangeChartVariable         (UINT_16, UINT_16);
void    Start_self_test_task_req    (void);
void    Self_test_cmd_req           (Header_t *);
void    Get_self_test_packet_req    (MaxResponse_t DATAFARTYPE *);
void    Exit_self_test_task_req     (void);
void    GetCarID                    (char *);
void    SetCarID                    (char *);
void    SerialCommunicationHandler  (void);
void    SendEndOfInterrupt          (void);
void    InitializeChartRecorder     (void);
void    InitialiseSerialPortPointers(void);
void    InitialiseSCC               (void);
void    Chart_Rec_Service           (void);
UINT_32 GetSwVersion                (void);
UINT_8* GetVersionString            (void);


/*  The following are external declarations for the PTU subsystem.          */
/*  External declarations used globally.                                    */
extern struct ptu_globals           GlobalPTUData;
extern struct faultlogqueue_t       *GlobalFaultLog;
extern struct datalogqueue_t        *GlobalDataLog;
extern const struct VariableDef_t   VariableDef[];
extern INT_16                       CurrentEventLog;

extern UINT_8 DATAFARTYPE           PTUStack;
extern SerialBuffer_t DATAFARTYPE   SerialBuffer[][2];
extern UINT_32                      SerialControlRegister[];
extern UINT_32                      SerialDataRegister[];

extern UINT_8                       *ChartPortAddress[];


void start_cbram_write(void);
void end_cbram_write(void);
void GetTimeDate(MaxResponse_t DATAFARTYPE *Response);
void SetTimeDate(MaxRequest_t DATAFARTYPE *PassedRequest);
void StartRTC();
void StopRTC();

void    Chart_Rec_Service           (void);
void    Scale_Fixed_Channel_Chart_Rec (void);
void    Zero_Fixed_Channel_Chart_Rec (void);
void    Ramp_Fixed_Channel_Chart_Rec (void);
void    Full_Fixed_Channel_Chart_Rec (void);

#endif


void    CODEFARTYPE    psv_ed_clear_state_table    (UINT_16 event_log_id);
UINT_32 CODEFARTYPE    psv_ed_read_life_sign_cntr  (void);
UINT_8  CODEFARTYPE    psv_ed_fatal_error_status   (void);
void    CODEFARTYPE    psv_ed_main                 (void);

#define   NUMOFEVENTLOGS                6

#define PTUCONFIGURATION        PTUCONFIG_WATCH         |       \
                                PTUCONFIG_CHART         |       \
                                PTUCONFIG_EVENTLOG      |       \
                                PTUCONFIG_DATALOG       |       \
                                PTUCONFIG_CLOCK         |       \
                                PTUCONFIG_SELFTEST      |       \
                                PTUCONFIG_DATABASE

/* ptuip.c */
void TCP_Init(void);
void TCP_Main(void);
void TCP_Close(int sockId);
INT16 EPTUServer_GetDataPacket(void *Packet, UINT16	*ByteCounter, int clientSocket);
int TCPGetActiveClientSocket (void);
#define TCP_SOCKET_TIMEOUT 60 /* seconds */

/* #endif */
#ifdef __cplusplus
}
#endif

