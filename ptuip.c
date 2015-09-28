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

/* Variable declarations */
TCPIP_INFO tcpip;
INT_16 socket_id;
INT_16 new_socket_id = ERROR;

fd_set masterFds;
INT_16 fdMax = 0;

INT_16 tcp_task_run = TRUE;

INT_16 ServerSocket = 0;
INT_16 ClientSocket = 0;

INT_16 serverPortNo = SERVER_PORT_NUM;

extern MaxResponse_t DATAFARTYPE            Response;
extern MaxRequest_t DATAFARTYPE             Request;
extern UINT_16 ComDevice;

///////////////////////////////////////////////////////////////////////////////////////

#define MAX_CLIENTS_PER_SERVER				50
#define MAX_INITIAL_SERVER_SOCKETS			20

///////////////////////////////////////////////////////////////////////////////////////
typedef void TCPServerCallbackFunc(char *aBuffer, int aNumBytes, int aClientSocketId);

typedef struct
{
	unsigned port;
	struct sockaddr_in addressInfo;
	TCPServerCallbackFunc *callbackFunc;
	int socketId;
	int clientSockets[MAX_CLIENTS_PER_SERVER];
} ServerSocketInfo;

///////////////////////////////////////////////////////////////////////////////////////
static int mNumServerSockets;
static int mMaxNumServerSockets;
static int mCurrentClientSocket;
static ServerSocketInfo *mServers;
static fd_set mReadfds; //set of socket descriptors
static struct timeval mTimer;
static struct timeval *mTimerPtr;


///////////////////////////////////////////////////////////////////////////////////////
static void TCPInitConnections (void);
static void TCPSetBlockingTime (long int aSeconds, long int aMicroSeconds);
static void TCPServiceIncomingSocketData (void);
static int TCPPopulateSocketDescriptorList (void);
static void TCPCreateServerSocket (unsigned aPort, TCPServerCallbackFunc aCallBackFunc);
static void TCPScanForNewConnections (void);
static void TCPServerCallback5001 (char *aBuffer, int aNumBytes, int aClientSocketId);


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

    TCPCreateServerSocket (5001, TCPServerCallback5001);

#if 0
    INT_32 SockOpt;
	INT_16 temp_socket_id;
	sockAddrSize = sizeof (struct sockaddr_in);
	UINT_16 port_num = serverPortNo;

    /* -- set up server */
	FD_ZERO((char *) &ServerAddress);
    ServerAddress.sin_family      = AF_INET;
    ServerAddress.sin_port        = htons(port_num);
    ServerAddress.sin_addr.s_addr = htonl(0x00000000);

    /* -- set up client */
	FD_ZERO((char *) &ClientAddress);
    ClientAddress.sin_family      = AF_INET;
    ClientAddress.sin_port        = htons(port_num);
    ClientAddress.sin_addr.s_addr = htonl(0x00000000);

    /* Create a socket for incomming requests. */
    ServerSocket = os_ip_socket(AF_INET, SOCK_STREAM, 0);

    if (ServerSocket == ERROR)
    {
		os_io_printf ("socket error (errno = %i)\r\n", os_errno );
 		os_io_printf("\r\nSOCKET_CREATION_FAILURE, ServerAddress sin_addr.s_addr %ld: ", ServerAddress.sin_addr.s_addr);
		temp_socket_id = ERROR;

	}

    /* Set up Socket Options to reuse socket address*/
    SockOpt = TRUE;
	if (os_ip_setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR,(INT_8 *)&SockOpt, sizeof(SockOpt)) == ERROR)
	{
    	os_ip_shutdown(ServerSocket, 2);
		os_ip_close(ServerSocket);
	    temp_socket_id = ERROR;
	}

    /*Specify the size of receive buffer*/
    SockOpt = MAX_SEND_BUFF_SIZE;
	if (os_ip_setsockopt(ServerSocket, SOL_SOCKET, SO_RCVBUF,(INT_8 *)&SockOpt, sizeof (SockOpt)) == ERROR)
	{
    	os_ip_shutdown(ServerSocket, 2);
		os_ip_close(ServerSocket);
		temp_socket_id = ERROR;
	}

	/*Specify the size of send buffer*/
    SockOpt = MAX_RECV_BUFF_SIZE;
    if (os_ip_setsockopt(ServerSocket, SOL_SOCKET, SO_SNDBUF,(INT_8 *)&SockOpt, sizeof (SockOpt)) == ERROR)
	{
    	os_ip_shutdown(ServerSocket, 2);
		os_ip_close(ServerSocket);
		temp_socket_id = ERROR;
	}

	/*Deliver Messages Immediately*/
	SockOpt = TRUE;
	if (os_ip_setsockopt(ServerSocket, IPPROTO_TCP, TCP_NODELAY,(INT_8 *)&SockOpt, sizeof (SockOpt)) == ERROR)
	{
    	os_ip_shutdown(ServerSocket, 2);
		os_ip_close(ServerSocket);
		temp_socket_id = ERROR;
	}

	/*Detect a dead connectiom*/
	SockOpt = TRUE;
	if(os_ip_setsockopt(ServerSocket, SOL_SOCKET, SO_KEEPALIVE,(INT_8 *)&SockOpt, sizeof (SockOpt)) == ERROR)
	{
    	os_ip_shutdown(ServerSocket, 2);
		os_ip_close(ServerSocket);
		temp_socket_id = ERROR;
	}

	/* Bind socket */
	if (os_ip_bind (ServerSocket, (struct sockaddr *) &ServerAddress, (int)sizeof(ServerAddress)) == ERROR)
	{
    	os_ip_shutdown(ServerSocket, 2);
		os_ip_close(ServerSocket);
		temp_socket_id = ERROR;
	}
	else
	{
	    if (os_ip_listen (ServerSocket, 2) == ERROR )
		{
	    	os_ip_shutdown(ServerSocket, 2);
			os_ip_close(ServerSocket);
			temp_socket_id = ERROR;
		}
		else
		{

			/*Binding socket successful*/
			temp_socket_id = ServerSocket;
		}
	}
	socket_id = temp_socket_id;
	// Init client PTU socket information
	tcpip.socket_id = 0;
	tcpip.status = ERROR;
	tcpip.acceptCount = 0;
	FD_ZERO(&masterFds);
	FD_SET(socket_id, &masterFds);
	fdMax = socket_id;
#endif

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
    int activity, maxSd;

	maxSd = TCPPopulateSocketDescriptorList ();

    das_printf ("maxSd = %d\n", maxSd);

    //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
    activity = select (maxSd + 1, &mReadfds, NULL, NULL, mTimerPtr);

    das_printf ("Activity = %d, mTimer.sec = %d, mTimer.usec = %d, err = %d\n",
    		activity, mTimer.tv_sec, mTimer.tv_usec, errno);


    if ( (activity < 0) && (errno != EINTR) )
    {
        printf("select error");
    }


    TCPScanForNewConnections ();

    TCPServiceIncomingSocketData ();


#if 0
    UINT_16 timer_index;
     /* accept link */
	new_socket_id = os_ip_accept(socket_id, (struct sockaddr *)&ClientAddress, &sockAddrSize);

	if (new_socket_id != ERROR)
	{
		tcpip.socket_id = new_socket_id;
		tcpip.status = OK;
		tcpip.acceptCount ++;

		tcp_task_run = FALSE;

		FD_SET(new_socket_id, &masterFds);

		if (new_socket_id > fdMax)
		{
			fdMax = new_socket_id;
		}

		os_io_printf("\r\ntcpip.acceptCount %d", tcpip.acceptCount);
	}
	else
	{
		os_io_printf("os_ip_accept(socket_id,2) ERROR ####################################\r\n");
		os_ip_shutdown (socket_id, 2);
		os_ip_close (socket_id);
	}
#endif
}


/******************************************************************************
*
* Module:      	TCP_Close
*
* Abstract:    	This function will first shutdown and will then terminates
*			   	socket connection.
*
* Invocation:
*
* Traceability: N/A
*
* Globals :		tcpip - structure containing the details about the socket
*						and connection statistic information.
*
* Parameters :  socketId - Identifier of the socket that is to be closed
*
* Return Value :None
*
* Functional Description :  Close the socket after completing
*							the communication or request from PTU to
*							terminate communication.
*
*
*   Date & Author:	05/15/09 - Paavani Gatram @ BTECI
*   Description:    Initial Release which includes TCP/IP
*					implementation for PTU
******************************************************************************/
void TCP_Close (int socketId)
{
	// Remove client socket from server list
	// os_ip_shutdown (socketId, 2);
	// os_ip_close (socketId);
}

int GetActiveClientSocket (void)
{
	return mCurrentClientSocket;
}

typedef enum
{
	WAIT_FOR_SOM,
	WAIT_FOR_COMMAND,

} PtuIpStates;

PtuIpStates mStateMachineIP = WAIT_FOR_SOM;

static void TCPServerCallback5001 (char *aBuffer, int aNumBytes, int aClientSocketId)
{
	INT_8  sendSOM = THE_SOM;
	int bytesSent;

	das_printf ("Server 5001: SocketId = %d, # Bytes in Msg = %d, Msg = %s\n", aClientSocketId, aNumBytes, aBuffer);

	switch (mStateMachineIP)
	{
		case WAIT_FOR_SOM:
		default:
			if ((aBuffer[0] == SYNC_SOM)  && (aNumBytes == 1))
			{
				das_printf ("SYNC_SOM received ONLY\n");

				/*  Send a Start Of Message out to Ethernet port. */
				bytesSent = os_ip_send (aClientSocketId, (const char*)&sendSOM, 1, 0);
				das_printf ("Sent THE_SOM; id = 3\n");
				mStateMachineIP = WAIT_FOR_COMMAND;
			}
			else
			{
				das_printf ("More bytes than just SYNC_SOM\n");
			}
			break;

		case WAIT_FOR_COMMAND:
			/* Get the PTU command packet*/
			if (TCPIP_GetDataPacket ( (Header_t *)&Request, aBuffer, aNumBytes) == NO_ERROR)
			{

				/*  Send a Start Of Message out to Ethernet port. */
				if (((Header_t *)&Request)->PacketType != TERMINATECONNECTION)
				{
					//bytesSent = os_ip_send (aClientSocketId, (const char*)&sendSOM, 1, 0);
					//das_printf ("Sent THE_SOM; id = 1\n");
					/* If a smart PTU packet has been received, set comm_type to TCP/IP	*/
					/* call Message_Manager to process the packet.		                */
					ComDevice = TCPIP;
					MessageManager ((Header_t *)&Request);
					das_printf ("Message Type = %d\n",((Header_t *)&Request)->PacketType);
				}
				else
				{
					das_printf ("TERMINATECONNECTION received from PC\n");
				}
				das_printf ("Entire command packet received from PC\n");
				mStateMachineIP = WAIT_FOR_SOM;
			}
			else
			{
				// TODO wait for the entire packet
			}
			break;
	}
}

static void TCPInitConnections( void )
{
	mNumServerSockets = 0;
	mMaxNumServerSockets = MAX_INITIAL_SERVER_SOCKETS;

	mServers = calloc (mMaxNumServerSockets, sizeof(ServerSocketInfo));

	TCPSetBlockingTime (10, 0);
}


static void TCPSetBlockingTime (long int aSeconds, long int aMicroSeconds)
{

	mTimer.tv_sec = aSeconds;
	mTimer.tv_usec = aMicroSeconds;

	mTimerPtr = &mTimer;
}

static void TCPCreateServerSocket (unsigned aPort, TCPServerCallbackFunc aCallbackFunc)
{
	int serverSocket;
	struct sockaddr_in address;
    int opt = TRUE;
    int socketFailure = 0;
    int sockReturnVal;

	serverSocket = socket (AF_INET, SOCK_STREAM , 0);

    /* create a master socketId */
    if (serverSocket == 0)
    {
        printf ("Server socket creation failed\n");
        socketFailure = 1;
    }

    if (socketFailure == 0)
    {
    	sockReturnVal = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
		// set master socket to allow multiple connections , this is just a good habit, it will work without this
		if (sockReturnVal < 0 )
		{
			printf ("set socket option failed\n");
			socketFailure = 1;
		}
    }

    if (socketFailure == 0)
    {
		//type of socketId created
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons (aPort);

		sockReturnVal = bind (serverSocket, (struct sockaddr *)&address, sizeof(address));

		//bind the socket to local host port 8888
		if (sockReturnVal < 0)
		{
			printf ("bind failed\n");
			socketFailure = 1;
		}
    }

    if (socketFailure == 0)
    {
    	printf("Listener on port %d \n", aPort);

		// try to specify maximum of 3 pending connections for the master socketId
    	sockReturnVal = listen (serverSocket, 3);

		if (sockReturnVal < 0)
		{
			printf ("listen failed\n");
			socketFailure = 1;
		}
    }

    if (socketFailure == 0)
    {
    	if (mNumServerSockets >= mMaxNumServerSockets)
    	{
    		mMaxNumServerSockets += MAX_INITIAL_SERVER_SOCKETS;
    		mServers = realloc ( (void *)mServers, sizeof (ServerSocketInfo) * mMaxNumServerSockets);
    	}

    	mServers[mNumServerSockets].port = aPort;
    	mServers[mNumServerSockets].addressInfo = address;
    	mServers[mNumServerSockets].socketId = serverSocket;
    	mServers[mNumServerSockets].callbackFunc = aCallbackFunc;
    	mNumServerSockets++;
    }

}


static int TCPPopulateSocketDescriptorList (void)
{
	int maxSd;
	int sd;
	int i;
	int socketCnt = 0;

	// All of this is required each time in the while loop because the select function modifies the
	// flags in the file descriptors
    // clear the socket set
    FD_ZERO (&mReadfds);

    maxSd = 0;
    while (mServers[socketCnt].socketId != 0)
    {
    	//add master socket to set
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
    	//add child sockets to set
		for (i = 0 ; i < MAX_CLIENTS_PER_SERVER ; i++)
		{
			//socket descriptor
			sd = mServers[socketCnt].clientSockets[i];

			//if valid socket descriptor then add to read list
			if (sd > 0)
			{
				FD_SET (sd , &mReadfds);
			}
			else
			{
				break;
			}

			//highest file descriptor number, need it for the select function
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
	int i, sd, valread;
    int addrlen;
    struct sockaddr_in addressInfo;
	char buffer[4096];
	int socketCnt = 0;

	while (mServers[socketCnt].socketId != 0)
	{

		// its some IO operation on some other socket :)
		for (i = 0; i < MAX_CLIENTS_PER_SERVER; i++)
		{
			sd = mServers[socketCnt].clientSockets[i];

			if (sd == 0)
			{
				break;
			}

			if (FD_ISSET (sd, &mReadfds))
			{
				valread = recv (sd, (void *)buffer, 4096, 0);
				// Check if it was for closing , and also read the incoming message
				if (valread == 0)
				{
					addrlen = sizeof (addressInfo);
					//Somebody disconnected , get his details and print
					getpeername (sd, (struct sockaddr *)&addressInfo , (socklen_t *)&addrlen);
					printf ("Host disconnected, IP Address =  %s, Port # =  %d \n" , inet_ntoa(addressInfo.sin_addr) , ntohs(addressInfo.sin_port));

					// Close the socket and mark as 0 in list for reuse
					shutdown (sd, 2);
					os_ip_close (sd);
					mServers[socketCnt].clientSockets[i] = 0;
				}

				//Echo back the message that came in
				else if (valread > 0)
				{
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
    int new_socket;
    int socketCnt = 0;
    int addrlen;
    int i;
    int sendMsgLen;
    int failure = 0;

    while ((mServers[socketCnt].socketId != 0) && (failure == 0))
    {
        addrlen = sizeof(mServers[socketCnt].addressInfo);

		//If something happened on the master socketId , then its an incoming connection
		if (FD_ISSET(mServers[socketCnt].socketId, &mReadfds) != 0)
		{
			new_socket = accept(mServers[socketCnt].socketId, (struct sockaddr *)&mServers[socketCnt].addressInfo, (socklen_t *)&addrlen);
			if (new_socket < 0)
			{
				failure = 1;
			}

			if (failure == 0)
			{
				// inform user of socketId number - used in send and receive commands
				printf("New connection , socketId FD = %d , ip is : %s , port : %d \n",
						new_socket,
						inet_ntoa(mServers[socketCnt].addressInfo.sin_addr),
						ntohs(mServers[socketCnt].addressInfo.sin_port));

				//add new socketId to array of sockets
				for (i = 0; i < MAX_CLIENTS_PER_SERVER; i++)
				{
					//if position is empty
					if( mServers[socketCnt].clientSockets[i] == 0 )
					{
						mServers[socketCnt].clientSockets[i] = new_socket;
						printf("Adding to list of sockets as %d\n" , i);
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
	INT16 	ReturnCode;
	UINT16 	ByteCounter;

	/* Check the buffer to determine if the entire header was received */
	if (bufferLength != ((Header_t *)buffer)->PacketLength)
	{
		return -1;
		//TODO return ENTIRE_HEADER_NOT_RECEIVED;
	}

	//TODO need system call for memcpy
	memcpy (DataPacket, buffer, bufferLength);

	return NOERROR;
}

#ifdef __cplusplus
}
#endif


