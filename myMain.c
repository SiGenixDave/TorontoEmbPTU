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
UINT_8 	u8[2000];
INT_32 	i32[2000];
INT_16 	i16[2000];
INT_8 	i8[2000];

static DWORD WINAPI myTcpThread(void* threadParams)
{
    while(1){
        TCP_Main();
    }

    return 0;
}

static void CreateTCPThread (void)
{
    DWORD threadDescriptor;

    CreateThread(
        NULL,                   /* default security attributes.   */
        0,                      /* use default stack size.        */
		myTcpThread,          /* thread function name.          */
        (void*)NULL,        /* argument to thread function.   */
        0,                      /* use default creation flags.    */
        &threadDescriptor);     /* returns the thread identifier. */
}

struct flt_Blown_Collect_Fuse_Str blownFuseFault;
struct fltWheelDiamCalcdiffCheckStr wheelDiamCalcFault;

static void UserInterfaceMain()
{
	int ch;
	printf ("UI Thread\n");
	ch = getchar();
	switch (ch)
	{
		case 'b':
			blownFuseFault.ptuCarSpeed = rand();
			LogFault(Propulsion, (struct minfaultpacket_t *)&blownFuseFault, sizeof(blownFuseFault));
			break;
		case 'w':
			wheelDiamCalcFault.ptuCarSpeed = rand();
			LogFault(Engineering, (struct minfaultpacket_t *)&wheelDiamCalcFault, sizeof(wheelDiamCalcFault));
			break;
	}
	fflush(stdin);
}

static DWORD WINAPI myUIThread(void* threadParams)
{
    while(1){
        UserInterfaceMain();
    }

    return 0;
}

static void CreateUIThread (void)
{
    DWORD threadDescriptor;

    CreateThread(
        NULL,                   /* default security attributes.   */
        0,                      /* use default stack size.        */
		myUIThread,          /* thread function name.          */
        (void*)NULL,        /* argument to thread function.   */
        0,                      /* use default creation flags.    */
        &threadDescriptor);     /* returns the thread identifier. */
}


int main()
{
	int err;
	const char msg[] = "Hello World\n\r";
	int i;

	char rs232mode[] = { '8', 'N', '1', 0 };



#ifdef WIN32
	/*********************************/
	// Used exclusively for winsock
	WSADATA wsaData;   // if this doesn't work
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	#ifdef _DEBUG
	setbuf(stdout,NULL); // this disables buffering for stdout.
	#endif

	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed.\n");
		exit(1);
	}
	/**********************************/
#endif

	TCP_Init();
	ptu_init();

	// "0" is com port 1
	if (RS232_OpenComport(0, 19200, rs232mode)) {
		printf("Can not open comport\n");
	}


	memset(&blownFuseFault, 0, sizeof(blownFuseFault));
	blownFuseFault.faultid = E_COLL_SHOE_FAULT;
	blownFuseFault.loggerid = Protection;
	blownFuseFault.lineVoltage1 = -1;
	blownFuseFault.lineVoltage2 = 1;
	blownFuseFault.ITSPosition = 1000;

	memset(&wheelDiamCalcFault, 0, sizeof(wheelDiamCalcFault));
	wheelDiamCalcFault.faultid = E_WHEEL_DIAM_DIFF_CHECK;
	wheelDiamCalcFault.loggerid = Velocity;


	for (i = 0; i < 0x1000; i++)
	{
		blownFuseFault.ptuCarSpeed = i;
		LogFault(Propulsion, (struct minfaultpacket_t *)&blownFuseFault, sizeof(blownFuseFault));
		wheelDiamCalcFault.ptuCarSpeed = i + 10;
		LogFault(Engineering, (struct minfaultpacket_t *)&wheelDiamCalcFault, sizeof(wheelDiamCalcFault));
	}

	CreateTCPThread ();
	CreateUIThread ();


	while (1)
	{
		Sleep (10);
		PTUMain();
	}
}



void GetTimeDateFromPC (MaxResponse_t *Response)
{
	GetTimeDateRes_t *ptr = Response;
	time_t t;
	struct tm *myTime;
	time(&t);

	myTime = localtime(&t);

	ptr->Year = myTime->tm_year % 100;
	ptr->Month = myTime->tm_mon + 1;
	ptr->Day = myTime->tm_mday;
	ptr->Hour = myTime->tm_hour;
	ptr->Minute = myTime->tm_min;
	ptr->Second = myTime->tm_sec;

}

void ReadClockFromPC(struct date_time_type *ptr)
{
	time_t t;
	struct tm *myTime;
	time(&t);

	myTime = localtime(&t);

	ptr->year = myTime->tm_year - 100;
	ptr->month = myTime->tm_mon + 1;
	ptr->day = myTime->tm_mday;
	ptr->hr = myTime->tm_hour;
	ptr->min = myTime->tm_min;
	ptr->sec = myTime->tm_sec;
}

