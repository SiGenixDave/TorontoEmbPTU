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

struct		sockaddr_in		ClientAddress;
int			sockAddrSize;
struct		sockaddr_in		ServerAddress;
struct		sockaddr_in		PTUAddress;

/* externs */
extern MaxResponse_t DATAFARTYPE            Response;
extern MaxRequest_t DATAFARTYPE             Request;



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
void TCP_Close(int socketId)
{

	if(tcpip.status == OK)
	{
		os_ip_shutdown (socketId, 2);
		os_ip_close (socketId);
	}

}


/**********************************************************************
*
*   (c) 2007, Bombardier Inc. or its subsidiaries.  All rights reserved.
*
*   Module:		EPTUServer_GetDataPacket
*
*   Abstract:	Receives a PTU packet from the TCP port
*
*   INPUTS:
*
*   Globals:  	NONE
*
*   Parameters:	Packet - a pointer to the memory where the received
*			packet is stored.
*
*			ByteCounter - This parameter indicates the number of
*			bytes to be received.
*
*
*   OUTPUTS:
*
*		Globals:		None
*
*	   	Return Values:
*
*           	TRUE        A packet was successfully received
*           	FALSE       A packet was not successfully received
*
*   Functional Description :	This function receives PTU packet from
*					ethernet port and echoes it back.
*
*
*   Date & Author:  05/15/09 - Paavani Gatram
*   Description:    Initial Release which includes TCP/IP
*			  implementation for PTU.
*****************************************************************************/
INT16	EPTUServer_GetDataPacket(void *Packet, UINT16	*ByteCounter)
{
	INT16	ReturnCode;
	INT16	pCktSize;

	/*	Initialize the byte counter. */
	*ByteCounter = 0;

	/*	Get the packet header.	*/
	while ((ReturnCode = os_ip_recv (tcpip.socket_id, (char *)Packet, sizeof (Header_t), 0)) > 0)
	{

		if (ReturnCode == ERROR)
			return FALSE;
		else
		{
			*ByteCounter += ReturnCode;
			pCktSize = ReturnCode;
			if((((Header_t *)Packet)->PacketLength) > pCktSize)
			{
				break;
			}
			else
			{
				return TRUE;
			}
		}
	}


	/*	Get the rest of the packet.	*/
	while ((ReturnCode = os_ip_recv (tcpip.socket_id, ((char *)Packet + *ByteCounter),(((Header_t *)Packet)->PacketLength - *ByteCounter), 0))>0)
	{

		if (ReturnCode == ERROR)
			return FALSE;
		else
		{
			*ByteCounter += ReturnCode;
			return TRUE;
		}

	}

	return FALSE;

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
INT16 TCPIP_GetDataPacket(Header_t *DataPacket)
{
	INT16 	ReturnCode;
	UINT16 	ByteCounter;
	INT8	LocalPacket[20];


	if (DataPacket == NULL)
	{
		ReturnCode = EPTUServer_GetDataPacket(	(void *)LocalPacket,
			&ByteCounter);

		if (ReturnCode) return TRUE;

		if (ByteCounter && ((Header_t *)LocalPacket)->ResponseType == PTU_NAK)
			return BADRESPONSE;
	}
	else
	{
		ReturnCode = EPTUServer_GetDataPacket(	(void *)DataPacket,
			&ByteCounter);
		if (ReturnCode) return TRUE;

		if (ByteCounter && DataPacket->ResponseType == PTU_NAK)
			return BADRESPONSE;
	}

	return NOERROR;
}

#ifdef __cplusplus
}
#endif


