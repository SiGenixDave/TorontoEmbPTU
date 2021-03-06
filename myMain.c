#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fcntl.h>
#else
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif

#include "myWrapper.h"
#include "FLTINFO.H"
#include "rs232.h"
#include "ptu.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

UINT_32 u32[2000];
UINT_16 u16[2000];
UINT_8 u8[2000];
INT_32 i32[2000];
INT_16 i16[2000];
INT_8 i8[2000];

void MySleep (int amountMs)
{
    Sleep (amountMs);
}

void os_t_delay (int amountMs)
{
    //Sleep (amountMs);
}

static DWORD WINAPI myTcpThread (void* threadParams)
{
    htons (1234);

    while (1)
    {
        TCP_Main ();
    }

    return 0;
}

static void CreateTCPThread (void)
{
    DWORD threadDescriptor;

    CreateThread (
    NULL, /* default security attributes.   */
    0, /* use default stack size.        */
    myTcpThread, /* thread function name.          */
    (void*) NULL, /* argument to thread function.   */
    0, /* use default creation flags.    */
    &threadDescriptor); /* returns the thread identifier. */
}

// TOPC
struct flt_Blown_Collect_Fuse_Str blownFuseFault;
struct fltWheelDiamCalcdiffCheckStr wheelDiamCalcFault;
// BART
struct cplgpushbtn_flt_str
{
    FAULTPACKETPROLOG
    UINT_16 couplingPushBtn;
}__attribute__ ((packed));
struct cplgpushbtn_flt_str cplpushbtn;

struct dbKnockout_flt_str
{
    FAULTPACKETPROLOG
    INT_8 a;
    INT_8 b;
    INT_8 c;
}__attribute__ ((packed));
struct dbKnockout_flt_str dbKnockout;

// R188
#define   E_BATTERY_VOLTAGE_BAD 2
struct fault_battery_voltage_str
{
    FAULTPACKETPROLOG
    INT_16 vbatt;
};
struct fault_battery_voltage_str lowBattEvent;
// 300R
struct fault_battery_voltage_str1
{
    FAULTPACKETPROLOG
    INT_16 x;
    INT_16 y;
};
struct fault_battery_voltage_str1 lowBattEvent1;


extern UINT_8 SelfTestStatus;

static void UserInterfaceMain ()
{
    int ch;
    //printf ("UI Thread\n");
    ch = getchar ();
    switch (ch)
    {
        case 'p':
            // BART
            LogFault(Propulsion, (struct minfaultpacket_t * )&cplpushbtn, sizeof(cplpushbtn));
            // R188
            //LogFault(Propulsion, (struct minfaultpacket_t *)&lowBattEvent, sizeof(lowBattEvent));
            break;

        case 'b':
            //blownFuseFault.ptuCarSpeed = rand();
            //LogFault(Propulsion, (struct minfaultpacket_t *)&blownFuseFault, sizeof(blownFuseFault));
            break;
        case 'w':
            //wheelDiamCalcFault.ptuCarSpeed = rand();
            //LogFault(Engineering, (struct minfaultpacket_t *)&wheelDiamCalcFault, sizeof(wheelDiamCalcFault));
            break;
        case 'S':
            SelfTestStatus = 1;
            printf ("---------------------- IN self test ---------------------\n");
            break;
        case 's':
            SelfTestStatus = 0;
            printf ("---------------------- OUT self test -------------------\n");
            break;
    }
    fflush (stdin);
}

static DWORD WINAPI myUIThread (void* threadParams)
{
    while (1)
    {
        UserInterfaceMain ();
    }

    return 0;
}

static void CreateUIThread (void)
{
    DWORD threadDescriptor;

    CreateThread (
    NULL, /* default security attributes.   */
    0, /* use default stack size.        */
    myUIThread, /* thread function name.          */
    (void*) NULL, /* argument to thread function.   */
    0, /* use default creation flags.    */
    &threadDescriptor); /* returns the thread identifier. */
}

#define BART

int main ()
{
    int err;
    const char msg[] = "Hello World\n\r";
    int i;

    char rs232mode[] = { '8', 'N', '1', 0 };

#ifdef WIN32
    /*********************************/
    // Used exclusively for winsock
    WSADATA wsaData;   // if this doesn't work
    setvbuf (stdout, NULL, _IONBF, 0);
    setvbuf (stderr, NULL, _IONBF, 0);
#ifdef _DEBUG
    setbuf (stdout, NULL); // this disables buffering for stdout.
#endif

    if (WSAStartup (MAKEWORD(1, 1), &wsaData) != 0)
    {
        fprintf (stderr, "WSAStartup failed.\n");
        exit (1);
    }
    /**********************************/
#endif

    TCP_Init ();
    ptu_init ();

    printf ("DAS\n");

    // "0" is com port 1
    if (RS232_OpenComport (6, 19200, rs232mode))
    {
        printf ("Can not open comport\n");
    }

#ifdef TOPC
    memset(&blownFuseFault, 0, sizeof(blownFuseFault));
    blownFuseFault.faultid = E_COLL_SHOE_FAULT;
    blownFuseFault.loggerid = Protection;
    blownFuseFault.lineVoltage1 = -1;
    blownFuseFault.lineVoltage2 = 1;
    blownFuseFault.ITSPosition = 1000;

    memset(&wheelDiamCalcFault, 0, sizeof(wheelDiamCalcFault));
    wheelDiamCalcFault.faultid = E_WHEEL_DIAM_DIFF_CHECK;
    wheelDiamCalcFault.loggerid = Velocity;

    for (i = 0; i < 2; i++)
    {
        blownFuseFault.ptuCarSpeed = i;
        LogFault(Propulsion, (struct minfaultpacket_t *)&blownFuseFault, sizeof(blownFuseFault));
        wheelDiamCalcFault.ptuCarSpeed = i + 10;
        LogFault(Engineering, (struct minfaultpacket_t *)&wheelDiamCalcFault, sizeof(wheelDiamCalcFault));
    }
#elif defined(BART1)

    memset (&cplpushbtn, 0, sizeof(cplpushbtn));
    cplpushbtn.faultid = 0;
    cplpushbtn.loggerid = 0;
    LogFault(Propulsion, (struct minfaultpacket_t * )&cplpushbtn, sizeof(cplpushbtn));
    //LogFault(Engineering, (struct minfaultpacket_t *)&wheelDiamCalcFault, sizeof(wheelDiamCalcFault));
#elif R188
    memset(&lowBattEvent, 0, sizeof(lowBattEvent));
    lowBattEvent.faultid = E_BATTERY_VOLTAGE_BAD;
    lowBattEvent.loggerid = 0;
    LogFault(Propulsion, (struct minfaultpacket_t *)&lowBattEvent, sizeof(lowBattEvent));
#endif

#ifdef BART
    memset (&cplpushbtn, 0, sizeof(cplpushbtn));
    cplpushbtn.faultid = 0;
    cplpushbtn.loggerid = 0;
    for (i = 0; i < 50; i++)
    {
        LogFault(Propulsion, (struct minfaultpacket_t * )&cplpushbtn, sizeof(cplpushbtn));
        cplpushbtn.CarSpeed_mph++;
    }

    memset (&dbKnockout, 0, sizeof(dbKnockout));
    dbKnockout.faultid = 1;
    dbKnockout.loggerid = 0;
    dbKnockout.a = 0;
    dbKnockout.b = 1;
    dbKnockout.c = 0;

    for (i = 0; i < 10; i++)
    {
        LogFault(Engineering, (struct minfaultpacket_t * )&dbKnockout, sizeof(dbKnockout));
        dbKnockout.CarSpeed_mph++;
    }

    #else

    memset(&lowBattEvent1, 0, sizeof(lowBattEvent1));
    lowBattEvent1.faultid = 2;
    lowBattEvent1.loggerid = 0;
    lowBattEvent1.x = 1;
    lowBattEvent1.y = 2;

    LogFault(Propulsion, (struct minfaultpacket_t *)&lowBattEvent1, sizeof(lowBattEvent1));
#endif

    CreateTCPThread ();
    CreateUIThread ();

    while (1)
    {
        PTUMain ();
    }
}

void GetTimeDateFromPC (MaxResponse_t *Response)
{
    GetTimeDateRes_t *ptr = Response;
    time_t t;
    struct tm *myTime;
    time (&t);

    myTime = localtime (&t);

#ifndef FOUR_DIGIT_YEAR
    ptr->Year = myTime->tm_year + 1900;
#else
    ptr->Year = myTime->tm_year % 100;
#endif
    ptr->Month = myTime->tm_mon + 1;
    ptr->Day = myTime->tm_mday;
    ptr->Hour = myTime->tm_hour;
    ptr->Minute = myTime->tm_min;
    ptr->Second = myTime->tm_sec;

    printf ("****************************************\n");
    printf ("Year = %d\n", ptr->Year);
    printf ("****************************************\n");

}

void ReadClockFromPC (struct date_time_type *ptr)
{
    time_t t;
    struct tm *myTime;
    time (&t);

    myTime = localtime (&t);

#ifdef TOPC
    ptr->year = myTime->tm_year + 1900;
#else
    ptr->year = myTime->tm_year % 100;
#endif

    ptr->month = myTime->tm_mon + 1;
    ptr->day = myTime->tm_mday;
    ptr->hr = myTime->tm_hour;
    ptr->min = myTime->tm_min;
    ptr->sec = myTime->tm_sec;

}

