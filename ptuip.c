/*************************************************************************
*
* This document and its contents are the property of Bombardier Inc.
* or it subsidiaries.  This document contains confidential proprietary
* information.  The reproduction, distribution, utilization or the
* communication of this document or any part thereof, without express
* authorization is strictly prohibited.  Offenders will be held liable
* for the payment of damages.
*
* (c) 2009, Bombardier Inc. or its subsidiaries.  All rights reserved.
*
* Project:     Common
*
* File Name:   ptuip.h
*
* System:      PTU
*
* Modules:     None
*
* Revision:
*   05/30/2009 - Paavani Gatram @ BTECI
*   - This file contains constants, variable declarations, datastructure
*	  and function declarations related to TCP/IP communication with PTU
*
*	08/17/2010 - Erik Holm @ PIPPC
*	Modified TCP_Main(). See function for more details.
*   03/3/2011 -  Coleen Doherty @PIPPC
*	Modified TCP_Main and TCP_init. This task is now ran off the system clock
*	not spawned. Changes were also made to app.c
*************************************************************************/
/*  Grab the standard I/O header files  */
#ifdef __cplusplus
	extern "C" {
#endif

#ifdef TEST_ON_PC

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fcntl.h>
#include <unistd.h>
#include "myWrapper.h"
#include <stdio.h>

#else

#include "vxWorks.h"
#include "tasklib.h"
#include "rts_api.h"

#endif

#include <errno.h>
#include "ptuprj.h"
#include "ptu.h"

#ifndef COMC_PTU
	#include "ptuip.h"
#endif

extern MaxResponse_t DATAFARTYPE            Response;
extern MaxRequest_t DATAFARTYPE             Request;
extern UINT_16 ComDevice;

/*************************************************************************************/

#define MAX_CLIENTS_PER_SERVER				10
#define MAX_INITIAL_SERVER_SOCKETS			5
#define TCP_RX_BUFFER_SIZE					4096

/*************************************************************************************/
typedef void TCPServerCallbackFunc(char *aBuffer, int aNumBytes, int aClientSocketId);

typedef struct
{
	unsigned port;
	struct sockaddr_in addressInfo;
	TCPServerCallbackFunc *callbackFunc;
	int socketId;
	int clientSockets[MAX_CLIENTS_PER_SERVER];
} ServerSocketInfo;

typedef enum
{
	WAIT_FOR_SOM,
	WAIT_FOR_COMMAND,

} PtuIpStates;


/*************************************************************************************/
static PtuIpStates mStateMachineIP = WAIT_FOR_SOM;
static UINT_16 mNumServerSockets;
static UINT_16 mMaxNumServerSockets;
static INT_16 mCurrentClientSocket;
static ServerSocketInfo *mServers;
static fd_set mReadfds;
static struct timeval mTimer;
static struct timeval *mTimerPtr;


/*************************************************************************************/
static void TCPInitConnections (void);
static void TCPSetBlockingTime (long int aSeconds, long int aMicroSeconds);
static void TCPServiceIncomingSocketData (void);
static INT_16 TCPPopulateSocketDescriptorList (void);
static void TCPCreateServerSocket (unsigned aPort, TCPServerCallbackFunc aCallBackFunc);
static void TCPScanForNewConnections (void);
static void TCPServerPTUCallback (char *aBuffer, int aNumBytes, int aClientSocketId);


/**********************************************************************
*
*   Module:     TCP_Init
*
*   Abstract:   Initializes the TCP Server
*
*   Globals:  NONE
*
*   Parameters:
*
*   IN  port_num - tcp port number
*
* Return Value :
*         ERROR:     	Error occured
*         socket id: 	Socket identifier.
*
* Functional Description :  Server Init. Initializes a socket
* 							and bind it to the port_num.
*
*
*   Date & Author:  05/15/09 - Paavani Gatram
					03/02/11 - Coleen Doherty PIPPC
					Moved all initilization tasks to this function.
					it is being called by app.c now.
*   Description:    Initial Release for PowerPC board
*****************************************************************************/
void TCP_Init(void)
{
    TCPInitConnections();
    TCPCreateServerSocket (SERVER_PORT_NUM, TCPServerPTUCallback);
}

/**********************************************************************
*
*
*   Module:		TCP_Main
*
*   Abstract:   Initializes the TCP Server
*
*   Globals:	NONE
*
*   Parameters:	NONE
*
*   IN:			NONE
*
* Return Value : NONE
*
*
*
* Functional Description :  Server Init. Initializes a socket
* 							and bind it to the port_num.
*
*
*   Date & Author:	05/15/09 - Paavani Gatram @ BTECI
*   Description:    Initial Release which includes TCP/IP
*					implementation for PTU
*
*					08/17/10 - Erik Holm, PIPPC
*					Added masterFds list and fdMax. The purpose is to keep
*					track of new sockets being opened.
*					03/3/11 - Coleen Doherty, PIPPC
*					moved all initilization tasks to the TCP_INIT task.
*					change task timer to the system clock in app.c. It is no longer spawned.
*****************************************************************************/
void TCP_Main(void)
{
    INT_16 activity, maxSd;

	maxSd = TCPPopulateSocketDescriptorList ();

    debugPrintf ("maxSd = %d\n", maxSd);

    /* wait for an activity on any of the sockets , if mTimerPtr is NULL; wait indefinitely for
     * activity on the registered sockets */
    activity = select (maxSd + 1, &mReadfds, NULL, NULL, mTimerPtr);

    debugPrintf ("Activity = %d, mTimer.sec = %ld, mTimer.usec = %ld, err = %d\n",
    		   activity, mTimer.tv_sec, mTimer.tv_usec, errno);

    /* TODO activity = 0 when a timeout occurs (no socket activity). Should use this when checking for
     * inactivity and closing sockets that way */

    if ( (activity < 0) && (errno != EINTR) )
    {
        os_io_printf("select error");
    }


    TCPScanForNewConnections ();

    TCPServiceIncomingSocketData ();

}


int TCPGetActiveClientSocket (void)
{
	return mCurrentClientSocket;
}

static void TCPServerPTUCallback (char *aBuffer, int aNumBytes, int aClientSocketId)
{
	INT_8  sendSOM = THE_SOM;
	INT_16  bytesSent;

	debugPrintf ("PTU Server Handler invoked: SocketId = %d, # Bytes in Msg = %d, Msg = %s\n", aClientSocketId, aNumBytes, aBuffer);

	switch (mStateMachineIP)
	{
		case WAIT_FOR_SOM:
		default:
			if ((aBuffer[0] == SYNC_SOM)  && (aNumBytes == 1))
			{
				debugPrintf ("SYNC_SOM received ONLY\n");

				/*  Send a Start Of Message out to Ethernet port. */
				/* TODO need to verify that the SOM was sent */
				bytesSent = os_ip_send (aClientSocketId, (const char*)&sendSOM, 1, 0);
				debugPrintf ("Sent THE_SOM; id = 3\n");
				mStateMachineIP = WAIT_FOR_COMMAND;
			}
			else
			{
				debugPrintf ("More bytes than just SYNC_SOM\n");
			}
			break;

		case WAIT_FOR_COMMAND:
			/* Get the PTU command packet*/
			if (TCPIP_GetDataPacket ( (Header_t *)&Request, aBuffer, aNumBytes) == NO_ERROR)
			{

				/*  Send a Start Of Message out to Ethernet port. */
				if (((Header_t *)&Request)->PacketType != TERMINATECONNECTION)
				{
					/* If a smart PTU packet has been received, set comm_type to TCP/IP	*/
					/* call Message_Manager to process the packet.		                */
					ComDevice = TCPIP;
					MessageManager ((Header_t *)&Request);
					debugPrintf ("Message Type = %d\n",((Header_t *)&Request)->PacketType);
				}
				else
				{
					debugPrintf ("TERMINATECONNECTION received from PC\n");
				}
				debugPrintf ("Entire command packet received from PC\n");
				mStateMachineIP = WAIT_FOR_SOM;
			}
			else
			{
				/* TODO wait for the entire packet */
			}
			break;
	}
}

static void TCPInitConnections( void )
{
	mNumServerSockets = 0;
	mMaxNumServerSockets = MAX_INITIAL_SERVER_SOCKETS;

	/* TODO may need an OS call or just fix size; since most likely only one server for this app */
	mServers = calloc (mMaxNumServerSockets, sizeof(ServerSocketInfo));

	TCPSetBlockingTime (60, 0);
}


static void TCPSetBlockingTime (long int aSeconds, long int aMicroSeconds)
{

	mTimer.tv_sec = aSeconds;
	mTimer.tv_usec = aMicroSeconds;

	mTimerPtr = &mTimer;
}

static void TCPCreateServerSocket (unsigned aPort, TCPServerCallbackFunc aCallbackFunc)
{
	INT_16 serverSocket;
	struct sockaddr_in address;
    char opt = TRUE;
    UINT_16 socketFailure = 0;
    INT_16 sockReturnVal;

	serverSocket = socket (AF_INET, SOCK_STREAM , 0);

    /* create a master socketId */
    if (serverSocket == 0)
    {
        os_io_printf ("Server socket creation failed\n");
        socketFailure = 1;
    }

    if (socketFailure == 0)
    {
    	sockReturnVal = os_ip_setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
		/* set master socket to allow multiple connections , this is just a good habit,
		 * it will work without this
		 */
		if (sockReturnVal < 0 )
		{
			os_io_printf ("set socket option failed\n");
			socketFailure = 1;
		}
    }

    if (socketFailure == 0)
    {
		/* type of socketId created */
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons (aPort);

		/* bind the socket to local host port */
		sockReturnVal = os_ip_bind (serverSocket, (struct sockaddr *)&address, sizeof(address));
		if (sockReturnVal < 0)
		{
			os_io_printf ("bind failed\n");
			socketFailure = 1;
		}
    }

    if (socketFailure == 0)
    {
    	os_io_printf("Listener on port %d \n", aPort);

    	/* try to specify maximum of 3 pending connections for the master socketId */
    	sockReturnVal = listen (serverSocket, 3);
		if (sockReturnVal < 0)
		{
			os_io_printf ("listen failed\n");
			socketFailure = 1;
		}
    }

    if (socketFailure == 0)
    {
    	if (mNumServerSockets >= mMaxNumServerSockets)
    	{
    		mMaxNumServerSockets += MAX_INITIAL_SERVER_SOCKETS;
    		/* TODO check for OS specific to do this, shouldn't have any need though */
    		mServers = realloc ( (void *)mServers, sizeof (ServerSocketInfo) * mMaxNumServerSockets);
    	}

    	mServers[mNumServerSockets].port = aPort;
    	mServers[mNumServerSockets].addressInfo = address;
    	mServers[mNumServerSockets].socketId = serverSocket;
    	mServers[mNumServerSockets].callbackFunc = aCallbackFunc;
    	mNumServerSockets++;
    }

}


static INT_16 TCPPopulateSocketDescriptorList (void)
{
	INT_16 maxSd;
	INT_16 sd;
	UINT_16 i;
	UINT_16 socketCnt = 0;

	/* All of this is required each time in the while loop because the select function modifies the
	 * flags in the file descriptors clear the socket set
	 */
    FD_ZERO (&mReadfds);

    maxSd = 0;
    while (mServers[socketCnt].socketId != 0)
    {
    	/* add master socket to set */
    	FD_SET (mServers[socketCnt].socketId, &mReadfds);
    	if (mServers[socketCnt].socketId > maxSd)
    	{
    		maxSd = mServers[socketCnt].socketId;
    	}
    	socketCnt++;
    }

    socketCnt = 0;
    while (mServers[socketCnt].socketId != 0)
    {
    	/* add child sockets to set */
		for (i = 0 ; i < MAX_CLIENTS_PER_SERVER ; i++)
		{
			/* socket descriptor */
			sd = mServers[socketCnt].clientSockets[i];

			/* if valid socket descriptor then add to read list */
			if (sd > 0)
			{
				FD_SET (sd , &mReadfds);
			}
			else
			{
				break;
			}

			/* highest file descriptor number, need it for the select function */
			if (sd > maxSd)
			{
				maxSd = sd;
			}
		}

		socketCnt++;
	}

    return maxSd;
}


static void TCPServiceIncomingSocketData (void)
{
	INT_16 sd, valread;
	UINT_16 i;
    UINT_16 addrlen;
    struct sockaddr_in addressInfo;
	char buffer[4096];
	UINT_16 socketCnt = 0;

	while (mServers[socketCnt].socketId != 0)
	{
		/* its some IO operation on some other socket */
		for (i = 0; i < MAX_CLIENTS_PER_SERVER; i++)
		{
			sd = mServers[socketCnt].clientSockets[i];

			if (sd == 0)
			{
				break;
			}

			if (FD_ISSET (sd, &mReadfds))
			{
				valread = os_ip_recv (sd, (void *)buffer, 4096, 0);
				/* Check if it was for closing , and also read the incoming message */
				if (valread == 0)
				{
					addrlen = sizeof (addressInfo);
					/* TODO get OS equivalent Somebody disconnected , get his details and print */
					getpeername (sd, (struct sockaddr *)&addressInfo , (socklen_t *)&addrlen);
					debugPrintf ("Host disconnected, IP Address =  %s, Port # =  %d \n" , inet_ntoa(addressInfo.sin_addr) , ntohs(addressInfo.sin_port));

					/* Close the socket and mark as 0 in list for reuse */
					os_ip_shutdown (sd, 2);
					os_ip_close (sd);
					mServers[socketCnt].clientSockets[i] = 0;
				}

				/* Invoke the callback  */
				else if (valread > 0)
				{
					/* Save the current socket descriptor so that other parts of the code
					 * can use this to send to data to the appropriate socket
					 */
					mCurrentClientSocket = sd;
					mServers[socketCnt].callbackFunc(buffer, valread, sd);
				}
			}
		}
		socketCnt++;
	}

}

static void TCPScanForNewConnections (void)
{
    INT_32 newClientSocket;
    UINT_16 socketCnt = 0;
    INT_32 addrlen;
    UINT_16 i;
    UINT_16 failure = 0;

    while ((mServers[socketCnt].socketId != 0) && (failure == 0))
    {
        addrlen = sizeof(mServers[socketCnt].addressInfo);

		/* If something happened on the master socketId , then its an incoming connection */
		if (FD_ISSET(mServers[socketCnt].socketId, &mReadfds) != 0)
		{
			newClientSocket = os_ip_accept(mServers[socketCnt].socketId, (struct sockaddr *)&mServers[socketCnt].addressInfo, (socklen_t *)&addrlen);
			if (newClientSocket < 0)
			{
				failure = 1;
			}

			if (failure == 0)
			{
				/* inform user of socketId number - used in send and receive commands */
				debugPrintf("New connection , socketId FD = %d , ip is : %s , port : %d \n",
						newClientSocket,
						inet_ntoa(mServers[socketCnt].addressInfo.sin_addr),
						ntohs(mServers[socketCnt].addressInfo.sin_port));

				/* add new socketId to array of sockets */
				for (i = 0; i < MAX_CLIENTS_PER_SERVER; i++)
				{
					/* if position is empty */
					if( mServers[socketCnt].clientSockets[i] == 0 )
					{
						mServers[socketCnt].clientSockets[i] = newClientSocket;
						debugPrintf("Adding to list of sockets as %d\n" , i);
						break;
					}
				}
			}
		}
		socketCnt++;

    }

}



/**********************************************************************
*
*   (c) 2007, Bombardier Inc. or its subsidiaries.  All rights reserved.
*
*   Module:		TCPIP_GetDataPacket
*
*   Abstract:	Get data packet from a socket
*
*   INPUTS:
*
*   Globals:  	NONE
*
*   Parameters:	DataPacket - a pointer to the memory where the received
*			packet will be stored.
*
*
*   OUTPUTS:
*
*		Globals:		None
*
*	   	Return Values:
*
*           	TRUE        	A packet was successfully received
*           	BADRESPONSE		A packet was not successfully received
*
*   Functional Description :	This function receives PTU packet from
*					ethernet port.
*
*
*   Date & Author:  05/15/09 - Paavani Gatram
*   Description:    Initial Release which includes TCP/IP
*			  implementation for PTU.
*****************************************************************************/
INT16 TCPIP_GetDataPacket(Header_t *DataPacket, char *buffer, int bufferLength)
{
	/* Check the buffer to determine if the entire header was received */
	if (bufferLength != ((Header_t *)buffer)->PacketLength)
	{
		return -1;
		/* TODO return ENTIRE_HEADER_NOT_RECEIVED; */
	}

	/* TODO need system call for memcpy */
	memcpy (DataPacket, buffer, bufferLength);

	return NOERROR;
}

#ifdef __cplusplus
}
#endif


