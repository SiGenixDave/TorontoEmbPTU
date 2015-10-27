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
*************************************************************************/ 
#ifdef __cplusplus
extern "C" {
#endif

#ifdef TEST_ON_PC
#include "myWrapper.h"
#else
#include "rts_api.h"
#include "cpu_dep.h"
#endif

/* defines */ 
#define SERVER_PORT_NUM         5001   /* server's port number for bind() */ 
#define SERVER_WORK_PRIORITY    100    /* priority of server's work task */ 
#define SERVER_STACK_SIZE       10000  /* stack size of server's work task */ 
#define SERVER_MAX_CONNECTIONS  4      /* max clients connected at a time */ 
#define REQUEST_MSG_SIZE        1024   /* max size of request message */ 
#define REPLY_MSG_SIZE          500    /* max size of reply message */ 
#define MAX_NETWORK_MSG         5000
								           
#define MAX_SEND_BUFF_SIZE		5000	/* max size of the send buffer*/
#define MAX_RECV_BUFF_SIZE		5000   /* max size of the recv buffer*/
#define RS232					 0	   /* RS232 is available as comm device*/
#define TCPIP					 1	   /* TCP/IP is available as comm device*/
#define NO_COM_PORT				 3	   /* None of the comm port is selected*/

#define TCP_MSG_GOOD             	0
#define PORTOPEN            		(-1)
#define NOHARDWARE          		(-2)
#define ENTIRE_MSG_NOT_RECEIVED		(-3)
#define TIMEOUT             		(-10)
#define BADRESPONSE         		(-11)
#define CHECKSUMERROR       		(-12)
#define BADREQUEST          		(-13)
#define UNKNOWNERROR       	 		(-100)



/* #endif */
#ifdef __cplusplus
}
#endif
