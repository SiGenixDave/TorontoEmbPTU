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

extern MaxRequest_t DATAFARTYPE             Request;
extern UINT_16 ComDevice;


/*******************************************************************/
/*********************** CONSTANTS *********************************/
/*******************************************************************/
#define MAX_CLIENTS_PER_SERVER				10
#define MAX_INITIAL_SERVER_SOCKETS			3
#define TCP_RX_BUFFER_SIZE					4096
#define MAX_INACTIVE_SOCKET_TIME_SECONDS	(10 * 60)
/*******************************************************************/


/*******************************************************************/
/*********************** STRUCTURES ********************************/
/*******************************************************************/
typedef void TCPServerCallbackFunc(char *aBuffer, int aNumBytes, int aClientSocketId);


typedef struct
{
	/* Server port number */
	unsigned port;
	/* typical address info structure required for initializing socket */
	struct sockaddr_in addressInfo;
	/* Function invoked when client activity detected */
	TCPServerCallbackFunc *callbackFunc;
	/* socket id of the server as determined by the OS */
	int socketId;
	/* List of client sockets */
	int clientSockets[MAX_CLIENTS_PER_SERVER];
	/* non-zero if all client sockets to be closed on select() timeout **/
	int closeExistingOnTimeout;
} ServerSocketInfo;
/*******************************************************************/


/*******************************************************************/
/*********************** ENUMERATIONS ******************************/
/*******************************************************************/
typedef enum
{
	WAIT_FOR_SOM,
	WAIT_FOR_COMMAND,

} PtuTcpRxMsgState;
/*******************************************************************/


/*******************************************************************/
/************ STATIC VARIABLE DECLARATIONS *************************/
/*******************************************************************/
static PtuTcpRxMsgState mStateMachineIP = WAIT_FOR_SOM;
static UINT_16 mNumServerSockets;
static UINT_16 mMaxNumServerSockets;
static INT_16 mCurrentClientSocket;
static ServerSocketInfo *mServers;
static fd_set mReadfds;
static struct timeval mTimer;
static struct timeval *mTimerPtr;
/*******************************************************************/

/*******************************************************************/
/************ STATIC FUNCTION DECLARATIONS *************************/
/*******************************************************************/
static void TCPInitConnections (void);
static void TCPSetBlockingTime (long int aSeconds, long int aMicroSeconds);
static void TCPServiceIncomingSocketData (void);
static INT_16 TCPPopulateSocketDescriptorList (void);
static void TCPCreateServerSocket (unsigned aPort, TCPServerCallbackFunc aCallbackFunc, int aCloseExistingOnTimeout);
static void TCPScanForNewConnections (void);
static void TCPServerPTUCallback (char *aBuffer, int aNumBytes, int aClientSocketId);
static void TCPCloseActiveSockets (void);
/*******************************************************************/


/**********************************************************************
*
*   Module:     TCP_Init
*
*   Abstract:   Initializes the TCP Server
*
*   Globals:  	NONE
*
*   Parameters:	NONE
*
* Return Value: NONE
*
* Functional Description :  Sets up a server socket for the PTU.
*
*
*   Date & Author:  05/15/09 - Paavani Gatram
*					03/02/11 - Coleen Doherty PIPPC
*					Moved all initialization tasks to this function.
*					it is being called by app.c now.
*					10/26//15 - Dave Smail Overhauled TCP interface to
*					accept multiple clients and stabilize
*   Description:    Initial Release for PowerPC board
*****************************************************************************/
void TCP_Init(void)
{
    TCPInitConnections();
    TCPCreateServerSocket (SERVER_PORT_NUM, TCPServerPTUCallback, TRUE);
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
* Return Value: NONE
*
*
*
* Functional Description :  TODO
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
*					change task timer to the system clock in app.c. It is no
*					longer spawned.
*					10/26/15 - Dave Smail Implemented more stable TCP interface
*					that can handle multiple servers wth each server being
*					able to handle multiple clients
*****************************************************************************/
void TCP_Main(void)
{
    INT_16 activity, maxSd;

	maxSd = TCPPopulateSocketDescriptorList ();

    debugPrintf ("maxSd = %d\n", maxSd);

    /* wait for an activity on any of the sockets, if mTimerPtr is NULL; wait indefinitely for
     * activity on the registered sockets. Wakes up only when a new client is trying to connect
     * or an existing client has sent a request. */
    activity = select (maxSd + 1, &mReadfds, NULL, NULL, mTimerPtr);

    debugPrintf ("Activity = %d, mTimer.sec = %ld, mTimer.usec = %ld, err = %d\n",
    		   activity, mTimer.tv_sec, mTimer.tv_usec, errno);


    if (activity == 0)
    {
        /* a timeout has occurred (no socket activity) on all of the active sockets (if any are present)
         * close and free all of the
         */
    	TCPCloseActiveSockets ();
    }
    else if ( (activity < 0) && (errno != EINTR) )
    {
    	/* an error has occurred... do nothing. Hopefully system can recover */
        os_io_printf("TCP ERROR: select error\n");
    }
    else
    {
    	/* Scan for any new clients */
    	TCPScanForNewConnections ();
    	/* Service existing client connection(s) */
    	TCPServiceIncomingSocketData ();
    }

}

/**********************************************************************
*
*
*   Module:		TCPGetActiveClientSocket
*
*   Abstract:   Accessor function for client socket
*
*   Globals:	NONE
*
*   Parameters:	NONE
*
*   IN:			NONE
*
* Return Value : int - most recently active client socket
*
*
*
* Functional Description :  Returns the active client socket so that a response
* 							can be sent to the proper client by other modules
* 							in this project
*
*
*   Date & Author:	10/26/15 - Dave Smail
*   Description:    Initial Release which includes overhauled TCP/IP
*					implementation for PTU
*
*****************************************************************************/
int TCPGetActiveClientSocket (void)
{
	return mCurrentClientSocket;
}

/**********************************************************************
*
*
*   Module:		TCPServerPTUCallback
*
*   Abstract:   Invoked when PTU application sends data to target.
*
*   Globals:	NONE
*
*   Parameters:	aBuffer - pointer to the received array of byte(s)
*   			aNumBytes - number of bytes received
*   			aClientSocketId - client socket id (used to send response to)
*
*   IN:			NONE
*
* Return Value : NONE
*
*
*
* Functional Description :  This function is invoked when a message is received
* 							from a PTU client. It executes a simple state machine
* 							Once a SOM character is received, it echos the SOM
* 							character (SOM is based on machine "endianness"). It then
* 							waits for a message request from the PTU client. Once
* 							the entire message is received, it processes it just
* 							as the serial connection would.
*
*
*   Date & Author:	10/26/15 - Dave Smail
*   Description:    Initial Release which includes overhauled TCP/IP
*					implementation for PTU
*
*****************************************************************************/
static void TCPServerPTUCallback (char *aBuffer, int aNumBytes, int aClientSocketId)
{
	INT_8  sendSOM = THE_SOM;
	INT_16  bytesSent;

	debugPrintf ("PTU Server Handler invoked: SocketId = %d, # Bytes in Msg = %d, Msg = %s\n", aClientSocketId, aNumBytes, aBuffer);

	switch (mStateMachineIP)
	{
		case WAIT_FOR_SOM:
		default:
			if (aNumBytes == 1)
			{
				if (aBuffer[0] == SYNC_SOM)
				{
					debugPrintf ("SYNC_SOM received ONLY\n");
					bytesSent = 0;
					while (bytesSent != 1)
					{
						/*  Send a Start Of Message out to Ethernet port. */
						bytesSent = os_ip_send (aClientSocketId, (const char*)&sendSOM, 1, 0);
					}
					debugPrintf ("Sent THE_SOM; id = 3\n");
					mStateMachineIP = WAIT_FOR_COMMAND;
				}
				else
				{
					os_io_printf ("TCP ERROR: SOM not received when expected\n");
				}
			}
			else
			{
				os_io_printf ("TCP ERROR: More bytes received than just SYNC_SOM\n");
			}
			break;

		case WAIT_FOR_COMMAND:
			/* Get the PTU command packet*/
			if (TCPIP_GetDataPacket ( (Header_t *)&Request, aBuffer, aNumBytes) == TCP_MSG_GOOD)
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
				/* Intentionally do nothing: wait for the entire packet */
			}
			break;
	}
}

/**********************************************************************
*
*
*   Module:		TCPInitConnections
*
*   Abstract:   Initializes the TCP related variables
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
* Functional Description :  Initializes all TCP related variables and sets
* 							the timeout timer for the select function
*
*
*   Date & Author:	10/26/15 - Dave Smail
*   Description:    Initial Release which includes overhauled TCP/IP
*					implementation for PTU
*
*****************************************************************************/
static void TCPInitConnections( void )
{
	mNumServerSockets = 0;
	mMaxNumServerSockets = MAX_INITIAL_SERVER_SOCKETS;

	/* allocate memory for server structures since but
	 * most likely only one server for this application */
	mServers = (ServerSocketInfo *)calloc (mMaxNumServerSockets, sizeof(ServerSocketInfo));

	/* Set the inactivity time for the select function */
	TCPSetBlockingTime (MAX_INACTIVE_SOCKET_TIME_SECONDS, 0);
}

/**********************************************************************
*
*
*   Module:		TCPSetBlockingTime
*
*   Abstract:   Sets the blocking time for the select function
*
*   Globals:	NONE
*
*   Parameters:	aSeconds - amount of seconds to block +
*   	 		aMicroSeconds - amount of microseconds to block
*
*   IN:			NONE
*
* Return Value : NONE
*
*
*
* Functional Description :  Initializes the TCP select function timer. If
* 							this function is not called, "mTimerPtr" remains null
* 							and the select function never times out. NOTE: the
* 							select function wakes up immediately when activity is
* 							detected.
*
*
*   Date & Author:	10/26/15 - Dave Smail
*   Description:    Initial Release which includes overhauled TCP/IP
*					implementation for PTU
*
*****************************************************************************/
static void TCPSetBlockingTime (long int aSeconds, long int aMicroSeconds)
{
	/* Set the timer */
	mTimer.tv_sec = aSeconds;
	mTimer.tv_usec = aMicroSeconds;

	/* point the select timer to this mTimer; mTimerPtr was set to NULL which is OK
	 * Had this function not been called, the select function would never time out.. */
	mTimerPtr = &mTimer;
}


/**********************************************************************
*
*
*   Module:		TCPCreateServerSocket
*
*   Abstract:   Creates a TCP server socket
*
*   Globals:	NONE
*
*   Parameters:	aPort - TODO
*   	 		aCallbackFunc - TODO
*   	 		aCloseExistingOnTimeout - TODO
*
*   IN:			NONE
*
* Return Value : NONE
*
*
*
* Functional Description :  TODO
*
*
*   Date & Author:	10/26/15 - Dave Smail
*   Description:    Initial Release which includes overhauled TCP/IP
*					implementation for PTU
*
*****************************************************************************/
static void TCPCreateServerSocket (unsigned aPort,
										TCPServerCallbackFunc aCallbackFunc,
										int aCloseExistingOnTimeout)
{
	INT_16 serverSocket;
	struct sockaddr_in address;
	INT_32 opt = TRUE;
    UINT_16 socketFailure = 0;
    INT_16 sockReturnVal;

    /* Open a new socket */
	serverSocket = socket (AF_INET, SOCK_STREAM , 0);

    /* create a master socketId */
    if (serverSocket == 0)
    {
        os_io_printf ("TCP ERROR: Server socket creation failed\n");
        socketFailure = 1;
    }

    if (socketFailure == 0)
    {
    	sockReturnVal = os_ip_setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (INT_8 *)&opt, sizeof(opt));
		/* set master socket to allow multiple connections , this is just a good habit,
		 * it will work without this
		 */
		if (sockReturnVal < 0 )
		{
			os_io_printf ("TCP ERROR: set socket option failed\n");
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
			os_io_printf ("TCP ERROR: bind failed\n");
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
			os_io_printf ("TCP ERROR: listen failed\n");
			socketFailure = 1;
		}
    }

    if (socketFailure == 0)
    {
    	if (mNumServerSockets >= mMaxNumServerSockets)
    	{
    		mMaxNumServerSockets += MAX_INITIAL_SERVER_SOCKETS;
    		/* expand the number of servers if necessary... shouldn't have any need though for this project */
    		mServers = (ServerSocketInfo *)realloc ( (void *)mServers, sizeof (ServerSocketInfo) * mMaxNumServerSockets);
    	}

    	mServers[mNumServerSockets].port = aPort;
    	mServers[mNumServerSockets].addressInfo = address;
    	mServers[mNumServerSockets].socketId = serverSocket;
    	mServers[mNumServerSockets].callbackFunc = aCallbackFunc;
    	mServers[mNumServerSockets].closeExistingOnTimeout = aCloseExistingOnTimeout;
    	mNumServerSockets++;
    }

}


/**********************************************************************
*
*
*   Module:		TCPPopulateSocketDescriptorList
*
*   Abstract:   TODO
*
*   Globals:	NONE
*
*   Parameters:	NONE
*
*   IN:			NONE
*
* Return Value : INT_16 -
*
*
*
* Functional Description :  TODO
*
*
*   Date & Author:	10/26/15 - Dave Smail
*   Description:    Initial Release which includes overhauled TCP/IP
*					implementation for PTU
*
*****************************************************************************/
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


/**********************************************************************
*
*
*   Module:		TCPServiceIncomingSocketData
*
*   Abstract:   TODO
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
* Functional Description :  TODO
*
*
*   Date & Author:	10/26/15 - Dave Smail
*   Description:    Initial Release which includes overhauled TCP/IP
*					implementation for PTU
*
*****************************************************************************/
static void TCPServiceIncomingSocketData (void)
{
	INT_16 sd, valread;
	UINT_16 i;
    UINT_16 addrlen;
    struct sockaddr_in addressInfo;
	char buffer[TCP_RX_BUFFER_SIZE];
	UINT_16 socketCnt = 0;

	while (mServers[socketCnt].socketId != 0)
	{
		/* its some IO operation on some other socket */
		for (i = 0; i < MAX_CLIENTS_PER_SERVER; i++)
		{
			sd = mServers[socketCnt].clientSockets[i];

			if (sd == 0)
			{
				continue;
			}

			if (FD_ISSET (sd, &mReadfds))
			{
				valread = os_ip_recv (sd, buffer, TCP_RX_BUFFER_SIZE, 0);
				/* Check if it was for closing , and also read the incoming message */
				if (valread == 0)
				{
					addrlen = sizeof (addressInfo);
					/* Client disconnected, get his details and print */
#ifdef TEST_ON_PC
					getpeername (sd, (struct sockaddr *)&addressInfo , (socklen_t *)&addrlen);
					debugPrintf ("Host disconnected, IP Address =  %s, Port # =  %d \n" , inet_ntoa(addressInfo.sin_addr) , ntohs(addressInfo.sin_port));
#endif
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
				/* Typically TCP RST issued by client will cause this. */
				else
				{
					/* Close the socket and mark as 0 in list for reuse */
					os_ip_shutdown (sd, 2);
					os_ip_close (sd);
					mServers[socketCnt].clientSockets[i] = 0;
				}
			}
		}
		socketCnt++;
	}

}

/**********************************************************************
*
*
*   Module:		TCPScanForNewConnections
*
*   Abstract:   TODO
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
* Functional Description :  TODO
*
*
*   Date & Author:	10/26/15 - Dave Smail
*   Description:    Initial Release which includes overhauled TCP/IP
*					implementation for PTU
*
*****************************************************************************/
static void TCPScanForNewConnections (void)
{
    INT_32 newClientSocket;
    UINT_16 socketCnt = 0;
    int addrlen;
    UINT_16 i;
    UINT_16 failure = 0;

    while ((mServers[socketCnt].socketId != 0) && (failure == 0))
    {
        addrlen = sizeof(mServers[socketCnt].addressInfo);

		/* If something happened on the master socketId, then its an incoming connection */
		if (FD_ISSET(mServers[socketCnt].socketId, &mReadfds) != 0)
		{
			newClientSocket = os_ip_accept(mServers[socketCnt].socketId, (struct sockaddr *)&mServers[socketCnt].addressInfo, &addrlen);
			if (newClientSocket < 0)
			{
				failure = 1;
			}

			if (failure == 0)
			{
				/* inform user of socketId number - used in send and receive commands */
				os_io_printf("New connection , socketId FD = %d , ip is : %s , port : %d \n",
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
*
*   Module:		TCPCloseActiveSockets
*
*   Abstract:   TODO
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
* Functional Description :  TODO
*
*
*   Date & Author:	10/26/15 - Dave Smail
*   Description:    Initial Release which includes overhauled TCP/IP
*					implementation for PTU
*
*****************************************************************************/
static void TCPCloseActiveSockets (void)
{
	UINT_16 i;
	UINT_16 socketCnt = 0;
	INT_16 sd;

	while (mServers[socketCnt].socketId != 0)
	{
		/* Determine if the server should close all active clients when a timeout occurs */
		if (mServers[socketCnt].closeExistingOnTimeout != 0)
		{
			/* Scan through the list and look for active clients */
			for (i = 0; i < MAX_CLIENTS_PER_SERVER; i++)
			{
				if (mServers[socketCnt].clientSockets[i] != 0)
				{
					sd = mServers[socketCnt].clientSockets[i];
					/* Close the socket and mark as 0 in list for reuse */
					os_ip_shutdown (sd, 2);
					os_ip_close (sd);
					mServers[socketCnt].clientSockets[i] = 0;
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

	/* need system call for memcpy */
	memcpy (DataPacket, buffer, bufferLength);

	return TCP_MSG_GOOD;
}

#ifdef __cplusplus
}
#endif


