/*****************************************************************************
 *
 * .b
 *   Copyright (c) 2002 Bombardier Transportation (Holdings) USA, Inc.
 *
 *   Project:
 *               Common
 *
 *   File Name:
 *               ptu.c
 *
 *   SubSystem:
 *               PTU
 *
 *   Procedures:
 *               PTUMain
 *               ptu_init
 *               GetPTUChar
 *               TransmitMessage
 *               GetRequestPacket
 *               GetByte
 *               GetVariableValue
 *
 *   EPROM Drawing:
 *
 * .b
 *
 *   History:        07/10/94    Creation of Version 3.0         jsl
 *   Revised:        11/17/95    ddp @ ATSI
 *                   - Revised to handle Motorola. (variant SOM)
 *                   11/17/1999  S.Taher @ ADtranz
 *                   - Made the following modifications while moving the fault
 *                     and data log to BBRAM:
 *                     1. Deleted the external declarations for the following
 *                        variables:
 *                        - cc_faultlog
 *                        - cc_datalog
 *                        - bat_ram_area
 *                     2. Modified the PTU_init routine. See function header for
 *                        details.
 *                   11/12/2001  B. Cirinelli @ Bombardier
 *                   - Added power on dst check and dst threshold check
 *                   01/22/2003  S.Taher
 *                   - Included the file ptulogger.h when moving the fault
 *                     specification to a separate file (from ptu.h).
 *					4/15/2003 R. Cirinelli @ Bombardier Transportation
 *                   - Added startup check in ptu_init() for bbram used for
 *                     fault logging
 *					10/26/2004  Amadou Diop
 *					- Added check for COMC PTU to process BBRAM
 *                   3/13/2008 Erik Holm
 *                   - Added NVRAM Manager for non-volatile RAM. See ptu_init().
 *                   6/16/2008 Sue Strane
 *                   - Added Call to check software version change. See ptu_init().
 *					6/1/2010	Andrew Thomas
 *					- Changes for IP PTU
 *					08/17/2010 Erik Holm
 *					- Modified GetPTUChar().
 *****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*  Grab the PTU specific header files. */
#ifdef TEST_ON_PC
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fcntl.h>
#include "myWrapper.h"
#else
#include "rts_api.h"
#endif

#include "ptuprj.h"
#include "ptu.h"

#ifndef COMC_PTU
#include "ptuip.h"
#include "batram.h"
#include "fltinfo.h"
#endif

#ifndef TEST_ON_PC
#include "daylite.h"
#endif

#include "ptulogger.h"

#define     EOF     -1

/*  Declare the global structures and pointers for the PTU, DataLogger,     */
/*  and the FaultLogger.                                                    */
struct ptu_globals GlobalPTUData;
UINT_32 TransactionCounter;
struct faultlogqueue_t *GlobalFaultLog;
struct datalogqueue_t *GlobalDataLog;
INT_16 CurrentEventLog;

/* externs */
extern MaxResponse_t DATAFARTYPE Response;
extern MaxRequest_t DATAFARTYPE Request;

/* Initialized to TCPIP */
UINT_16 ComDevice;

/****************************************************************************
 *
 * .b
 *   Procedure Name:                 PTUMain
 *
 *   Abstract:
 *       PTUMain initializes the PTU and makes calls to GetPTUChar
 *
 *   INPUTS:
 *
 *       Globals:
 *           GlobalPTUData       struct ptu_globals      Global PTU Information
 *
 *       Constants:
 *
 *       Procedure Parameters:
 *           None (void)
 *
 *   OUTPUTS
 *
 *       Globals:
 *
 *       Returned Values:
 *           None (void)
 *
 *   Functional Description:
 *       PTUMain cycles in a forever loop calling GetPTUKey once each cycle.
 *
 * .b
 *
 *   History:        07/10/94    Creation of Version 3.0             jsl
 *   Revised:        11/12/01    R.Cirinelli @ Bombardier
 *                   - added power on daylite savings check and threshold check
 *                     for DST.
 *                  10/07/2002  Sarfaraz Taher @ Bombardier
 *              - Made the following changes to support integration with the
 *                code automatically generated via Rhapsody
 *                1. The ptu_init routine is now called at the constructor
 *                   of the PTUMgr class generated via Rhapsody.
 *                2. PTUMain in periodically called from the Rhapsody
 *                   generated PTUMgr class statechart.
 *                  11/12/2002 Sarfaraz Taher @ Bombardier
 *               - Deleted inclusion of the version.h (same filename issue.
 *                 Also modified the ptu_init routine in the same context. See
 *                 function header for details.
 *****************************************************************************/
static void PtuServiceSerialPort (void);

void PTUMain (void)
{

    PtuServiceSerialPort ();

}

/****************************************************************************
 *
 * .b
 *   Procedure Name:                 ptu_init
 *
 *   Abstract:
 *       InitializePTU initalizes the internal PTU and DataLogger structures.
 *
 *   INPUTS:
 *
 *       Globals:
 *           GlobalPTUData       struct ptu_globals      Global PTU Information
 *
 *       Constants:
 *           TRUE                Boolean True
 *           NUMDEFINEDVARS      Number of Variables in the Data Dictionary
 *
 *       Procedure Parameters:
 *           None (void)
 *
 *   OUTPUTS
 *
 *       Globals:
 *           GlobalPTUData   struct ptu_globals      Initialize to Default
 *                                                   Variables
 *
 *       Returned Values:
 *           None (void)
 *
 *   Functional Description:
 *       InitializePTU sets the internal PTU data structure to the following
 *       values.
 *           Chart Recorder Entries  Channels 1-8 point to Variables 0-7,
 *                                       Respectively
 *           VariableInfo            Initialzied to Values Defined in
 *                                       ptuconst.c
 *
 * .b
 *
 *   History:        07/10/94    Creation of Version 3.0             jsl
 *                   11/17/1999  S.Taher @ ADtranz
 *                   - Made the following modifications while moving the fault
 *                     and data log to BBRAM:
 *                     1. Initialization of the GlobalFaultLog and the
 *                        GlobalDataLog changed to point to the BBRAM.
 *                     2. Deleted the calls to InitializeFaultInterface,
 *                        InitializeBatRAMArea as these are handled by bramtest.c
 *                     3. Also deleted the call to copy the REF_CAR_ID   to the
 *                        constant area. This is now handled by bramtest.c
 *
 *                   11/12/2002 S.Taher @ Bombardier
 *                   - Added call to GetSwVersion instead of using the SW_VERSION
 *                     define directly. This was done to all not including
 *                     the version.h file (same filename issue).
 *
 *					4/15/2003 R. Cirinelli @ Bombardier Transportation
 *                   - Added startup check for bbram used for fault logging
 *                     check_event_data_size() was added to determine if any
 *                     of the logging settings have changed
 *
 *                   3/13/2008 Erik Holm
 *                   - Added VCU-C NVRAM initialization
 *                   6/16/2008 Sue Strane
 *                   - Added call to  Check_SW_Version() if software version
 *                     has changed this will re-initialize the NVRAM.
 *****************************************************************************/
INT_16 ptu_init (void)
{
    /*  Declare all local variables. */
    INT_16 Index;

    os_io_printf ("\n!!!! comm_init !!!!\n\r");

#ifndef TEST_ON_PC
    /* Initialize comm ports */
    if (comm_init() == ERROR)
    {
        os_io_printf("\n!!!! Comm Error !!!!");
        return ERROR;
    }

    /* Check for automatic time update for dst/standard time on power up */

    /* Power_On_Daylite_Savings_Check(); */
    /*  Initialize the Watch Window and Chart Recorder table. */
    InitializeChartRecorder();
#endif
    /*  Load the VariableInfo array with information obtained from the */
    /*  VariableDef array.                                             */
    for (Index = 0; Index < NUMDEFINEDVARS; Index++)
    {
        GlobalPTUData.VariableInfo[Index].max_scale = VariableDef[Index].max_scale;

        GlobalPTUData.VariableInfo[Index].min_scale = VariableDef[Index].min_scale;
    }

    /* Initialise the Watch Element Indices */
    for (Index = 0; Index < WATCHSIZE; Index++)
    {
        GlobalPTUData.WatchElement[Index] = 0xffff;
    }

    /*  Tell everyone that that PTU has been initialized. */
    GlobalPTUData.PTUInitialized = TRUE;
    GlobalPTUData.ChartRecorderMode = DATAMODE;

    /* Check event info stored in bbram to determine if 
     the information has changed and the memory should be
     reinitialized */

#ifndef COMC_PTU

    /* Initialize VCU-C NVRAM */
    bat_ram_area = &ptu_fault_log_buffer;
    /*
     * initialize Event logger and Data Logger
     */
    CurrentEventLog = 0;

    GlobalFaultLog = &(bat_ram_area->non_constant_area.cc_faultlog[0]);
    GlobalDataLog = &(bat_ram_area->non_constant_area.cc_datalog[0]);

    /* Initialize the fault log and data log */
    InitializeFaultInterface ();
    /*
     InitializeFaultLogger(GlobalFaultLog, GlobalDataLog);
     InitializeDataLogger(GlobalDataLog);
     */

    /* Fill the fault log with existing data from NVRAM */
    PTU_bbram = Init_nvram_segment (NCBBRAM_PTU_FAULT_LOGGER_NAME, bat_ram_area);

    Check_Event_Data_Size ();
    Check_SW_Version ();

#endif

    os_io_printf ("\n!!!!Check Event Size !!!!\n\r");
    /* Write the software version to the constant area in Battery RAM */

    return (OK);

}

/****************************************************************************
 *
 * .b
 *   Procedure Name:                 PtuServiceSerialPort
 *
 *   Abstract:
 *       GetPTUChar checks for a character from the PTU serial port.  If a
 *       Start-Of-Message is received, the rest of the packet is requested
 *       and acted upon.
 *
 *   INPUTS:
 *
 *       Globals:
 *           None
 *
 *       Constants:
 *           EOF                 End Of File
 *           SOM                 Start Of Message
 *
 *       Procedure Parameters:
 *           None (void)
 *
 *   OUTPUTS
 *
 *       Globals:
 *
 *       Returned Values:
 *
 *   Functional Description:
 *       See Abstract
 *
 * .b
 *
 *   History:        07/10/94    Creation of Version 3.0             jsl
 *
 *					08/17/2010 Erik Holm
 *					Added functionality to monitor (and close) inactive
 *					IP sockets.
 *****************************************************************************/
typedef enum
{
    WAIT_FOR_SOM, WAIT_FOR_DPP, WAIT_FOR_REMAINDER_OF_MSG_FROM_PC
} PtuSerialState;

#define OS_DELAY                        20
#define NO_COMM_DPP_TIMEOUT             (1000/OS_DELAY)
#define NO_COMM_PAYLOAD_TIMEOUT         (2000/OS_DELAY)
#define MAX_CONSECUTIVE_EOFS            5000

static UINT32 m_PtuNoCommTimer;
static PtuSerialState m_PtuSerialState = WAIT_FOR_SOM;
static UINT16 m_DppIndex = 0;

static void PtuSerialStateMachine (INT16 inByte);

static void PtuServiceSerialPort (void)
{
    INT16 inByte;
    UINT16 eofCounter = 0;

    do
    {
        inByte = tgetc (PTUCHANNEL);
        if (inByte == EOF)
        {
            eofCounter++;
        }
        else
        {
            PtuSerialStateMachine (inByte);
        }

    } while (eofCounter < MAX_CONSECUTIVE_EOFS);

    os_t_delay (OS_DELAY);
    if (m_PtuNoCommTimer != 0)
    {
        m_PtuNoCommTimer--;
        if (m_PtuNoCommTimer == 0)
        {
            m_PtuSerialState = WAIT_FOR_SOM;
            printf ("PTU Timeout\n");
        }
    }

}

static void PtuSerialStateMachine (INT16 inByte)
{

    UINT8 *headerPointer = (UINT8 *) &Request;
    UINT8 headerComplete = FALSE;

    switch (m_PtuSerialState)
    {
        case WAIT_FOR_SOM:
        default:
            if (inByte == SYNC_SOM)
            {
                /* Echo Start Of Message to the smart PTU to indicate that the EPTU is
                 * ready to receive a smart PTU packet */
                tputc (PTUCHANNEL, THE_SOM);
                m_PtuSerialState = WAIT_FOR_DPP;
                printf ("Rx: ");
                m_DppIndex = 0;
                m_PtuNoCommTimer = NO_COMM_DPP_TIMEOUT;
                // printf ("Sync SOM detected\n");
            }
            break;

        case WAIT_FOR_DPP:
            headerPointer[m_DppIndex] = (UINT8) (inByte & 0xFF);
            tputc (PTUCHANNEL, headerPointer[m_DppIndex]);
            m_DppIndex++;
            // printf ("Header Byte %d\n", m_DppIndex);
            printf ("%02X ", inByte);

            if (m_DppIndex >= sizeof(Header_t))
            {
                printf (" Header... ");
                //printf ("Header Complete\n");
                headerComplete = TRUE;
                m_PtuNoCommTimer = 0;
            }

            if (headerComplete)
            {
                if (Request.PacketLength != m_DppIndex)
                {
                    m_PtuSerialState = WAIT_FOR_REMAINDER_OF_MSG_FROM_PC;
                    m_PtuNoCommTimer = NO_COMM_PAYLOAD_TIMEOUT;
                }
                else
                {
                    ComDevice = RS232;
                    MessageManager ((Header_t *) &Request);
                    m_PtuNoCommTimer = 0;
                    m_PtuSerialState = WAIT_FOR_SOM;
                    m_DppIndex = 0;
                    //printf ("End of Msg from 1\n");
                }

            }
            break;

        case WAIT_FOR_REMAINDER_OF_MSG_FROM_PC:
            if (Request.PacketLength != m_DppIndex)
            {
                printf ("%02X ", inByte);
                headerPointer[m_DppIndex] = (UINT8) (inByte & 0xFF);
                tputc (PTUCHANNEL, headerPointer[m_DppIndex]);
                m_DppIndex++;
            }

            if (m_DppIndex >= Request.PacketLength)
            {
                printf ("   Payload\n");
                ComDevice = RS232;
                MessageManager ((Header_t *) &Request);
                m_PtuNoCommTimer = 0;
                m_PtuSerialState = WAIT_FOR_SOM;
                m_DppIndex = 0;
                //printf ("End of Msg from 2\n");
            }
            break;

    }

}

/****************************************************************************
 *
 * .b
 *   Procedure Name:                 TransmitMessage
 *
 *   Abstract:
 *       TransmitMessage calculates the check sum of a passed EPTUI
 *       packet and sends it out the serial port.
 *
 *   INPUTS:
 *
 *       Globals:
 *           None
 *
 *       Constants:
 *           SOM                 Start Of Message
 *           PTUCHANNEL          serial port that the smart PTU is connected to
 *
 *       Procedure Parameters:
 *           PassedResponse      union msg_response_union *
 *                                               packet that is to be sent out
 *                                               the serial port that the smart
 *                                               PTU is connected to
 *           PassedMessageLength UINT_16         length of PassedResponse
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
 *       Transmit_Message calculates the 16-bit checksum of PassedResponse by
 *       adding each byte in PassedResponse together and subtracting the
 *       result from 0xffff.  Transmit_Message then transmits the packet, byte
 *       by byte, out the serial port indicated by PTUCHANNEL.
 *
 * .b
 *
 *   History:        03/30/93    Creation of Version 2.0             jsl
 *   Revised:        11/17/95    ddp @ ATSI
 *                   - Changed SOM from SYNC_SOM to THE_SOM
 *		    10/20/2003  TimDurant
 *		      - removed delay loop inside send
 *
 *****************************************************************************/
void TransmitMessage (Header_t *PassedResponse, UINT_16 PassedMessageLength)
{
    UINT_8 *BytePointer;
    UINT_16 ByteIndex;
    UINT_16 NumBytes = 0;
    UINT_8 Send_SOM;
    int clientSocket;

    /*  Place the true length into the response packet. */
    PassedResponse->PacketLength = PassedMessageLength;

    switch (ComDevice)
    {
        case RS232:
            /*  Send a Start Of Message out the serial port. */
            tputc (PTUCHANNEL, THE_SOM);

            BytePointer = (UINT_8 *) PassedResponse;

            printf("Tx: ");
            /*  Send every byte in PassedResponse out the serial port. */
            for (ByteIndex = 0; ByteIndex < PassedMessageLength; ByteIndex++)
            {
                printf("%02X ",*(BytePointer + ByteIndex));
                tputc (PTUCHANNEL, *(BytePointer + ByteIndex));
            }
            printf("\n");
            break;

        case TCPIP:
            Send_SOM = THE_SOM;

            clientSocket = TCPGetActiveClientSocket ();

            /*  Send a Start Of Message out to Ethernet port. */
            os_ip_send (clientSocket, (const char*) &Send_SOM, 1, 0);
            printf ("DASDAS\n");

#ifdef TEST_ON_PC
            BytePointer = (UINT_8 *) (PassedResponse);
            printf ("TX: ");
            for (NumBytes = 0; NumBytes < PassedMessageLength; NumBytes++)
            {
                printf ("%3d ", BytePointer[NumBytes] & 0xff);
            }
            printf ("\n\r");
#endif

            /*  Send every byte in PassedResponse out on TCP/IP port. */
            NumBytes = os_ip_send (clientSocket, (char *) PassedResponse, PassedMessageLength, 0);
            break;

        default:
            break;
    }
}

/****************************************************************************
 *
 * .b
 *   Procedure Name:                 TransmitACK
 *
 *   Abstract:
 *       TransmitACK sends an ASCII ACK (0x04) to the PTU Serial Port.
 *
 *   INPUTS:
 *
 *       Globals:
 *           None
 *
 *       Constants:
 *           PTUCHANNEL          serial port that the smart PTU is connected to
 *
 *       Procedure Parameters:
 *           None (void)
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
 *           See Abstract
 *
 * .b
 *
 *   History:        07/10/94    Creation of Version 3.0             jsl
 *
 *****************************************************************************/
void TransmitACK (void)
{
    char TxACK;

    TxACK = PTU_ACK;

    switch (ComDevice)
    {
        case RS232: /*Transmit PTU_ACK via RS232*/
            tputc (PTUCHANNEL, PTU_ACK);
            break;

        case TCPIP: /*Transmit PTU_ACK via TCP/IP*/
            os_ip_send (TCPGetActiveClientSocket (), (const char*) &TxACK, 1, 0);
            break;

        default:
            break;
    }
}

/****************************************************************************
 *
 * .b
 *   Procedure Name:                 GetRequestPacket
 *
 *   Abstract:
 *       GetRequestPacket receives a PTU packet from the serial port.
 *
 *   INPUTS:
 *
 *       Globals:
 *           None
 *
 *       Constants:
 *           TRUE
 *           FALSE
 *
 *       Procedure Parameters:
 *           PassedRequest           Header_t *  a pointer to the area where
 *                                               the newly received packet is
 *                                               to be placed
 *
 *   OUTPUTS
 *
 *       Globals:
 *           None
 *
 *       Returned Values:
 *           TRUE        A packet was successfully received
 *           FALSE       A packet was not successfully received
 *
 *   Functional Description:
 *           GetRequestPacket continually polls the serial port assigned to
 *           the PTU was request packet data.  If a timeout or a checksum
 *           error occurs, GetRequestPacket returns FALSE.  Otherwise, the
 *           received packet is placed in to the area pointed to by
 *           PassedRequest and TRUE is returned.
 *
 * .b
 *
 *   History:        07/10/94    Creation of Version 3.0             jsl
 *   Revised:        11/17/95    ddp @ ATSI
 *                   - Changed SOM from SYNC_SOM to THE_SOM
 *
 *****************************************************************************/
INT_16 GetRequestPacket (Header_t *PassedRequest)
{
    INT_16 Index;
    INT_16 InByte;
    UINT_8 *TempPointer;

    /*  Send a Start Of Message to the smart PTU to indicate that the EPTU is   */
    /*  ready to receive a smart PTU packet.                                    */
    tputc (PTUCHANNEL, THE_SOM);

    /*  Loop around for the length of the smart PTU packet header, grabbing a   */
    /*  byte each time through.                                                 */
    for (Index = 0; Index < sizeof(Header_t); Index++)
    {
        if ((InByte = GetByte ()) == EOF)

            /*  If a timeout occured, return TIMEOUT to the calling procedure.          */
            return FALSE;

        else
        {
            TempPointer = (UINT_8 *) ((UINT_8 *) (PassedRequest) + Index);
            *TempPointer = (InByte & 0x00ff);
        }
    }

    /*  Loop around for the length of the smart PTU packet data, grabbing a     */
    /*  byte each time through.                                                 */

    /*  Check to see if a valid PacketLength was received.                      */
    if (PassedRequest->PacketLength < MAXREQUESTLENGTH)
    {
        for (; Index < PassedRequest->PacketLength; Index++)
        {
            if ((InByte = GetByte ()) == EOF)

                /*  If a timeout occured, return TIMEOUT to the calling procedure.          */
                return FALSE;

            else
            {
                TempPointer = (UINT_8 *) ((UINT_8 *) (PassedRequest) + Index);
                *TempPointer = (InByte & 0x00ff);
            }
        }
    }
    else
        return FALSE;

    return TRUE;
}

/****************************************************************************
 *
 * .b
 *   Procedure Name:                 GetByte
 *
 *   Abstract:
 *       GetByte receives a character from the serial port and echoes it back.
 *
 *   INPUTS:
 *
 *       Globals:
 *           None
 *
 *       Constants:
 *
 *       Procedure Parameters:
 *           None (void)
 *
 *   OUTPUTS
 *
 *       Globals:
 *           None
 *
 *       Returned Values:
 *           EOF                 no character was available at the serial port
 *
 *   Functional Description:
 *
 * .b
 *
 *   History:        07/10/94    Creation of Version 3.0             jsl
 *
 *****************************************************************************/
INT_16 GetByte (void)
{
    INT_16 ReturnedValue;

    ReturnedValue = tgetc (PTUCHANNEL);

    /*  Return the received character to the calling procedure.             */
    return (ReturnedValue);
}

/****************************************************************************
 *
 * .b
 *   Procedure Name:                 GetVariableValue
 *
 *   Abstract:
 *
 *   INPUTS:
 *
 *       Globals:
 *           None
 *
 *       Constants:
 *
 *       Procedure Parameters:
 *           None (void)
 *
 *   OUTPUTS
 *
 *       Globals:
 *           None
 *
 *       Returned Values:
 *
 *   Functional Description:
 *
 * .b
 *
 *   History:        05/04/95    Creation of Version 3.0             ddp
 *
 ****************************************************************************/
void GetVariableValue (UINT_16 Index, SignedUnion_t *ReturnValue)
{
    if (Index == 0xffff)
    {
        ReturnValue->Signed = 0;
        return;
    }

    switch (VariableDef[Index].type_id)
    {
        case UINT_8_TYPE:
            ReturnValue->Unsigned = *(UINT_8 *) (VariableDef[Index].var_start_addr);
            break;

        case INT_8_TYPE:
            ReturnValue->Signed = *(INT_8 *) (VariableDef[Index].var_start_addr);
            break;

        case UINT_16_TYPE:
            ReturnValue->Unsigned = *(UINT_16 *) (VariableDef[Index].var_start_addr);
            break;

        case INT_16_TYPE:
            ReturnValue->Signed = *(INT_16 *) (VariableDef[Index].var_start_addr);
            break;

        case UINT_32_TYPE:
            ReturnValue->Unsigned = *(UINT_32 *) (VariableDef[Index].var_start_addr);
            break;

        case INT_32_TYPE:
            ReturnValue->Signed = *(INT_32 *) (VariableDef[Index].var_start_addr);
            break;
    }
}

/* #endif */
#ifdef __cplusplus
}
#endif

