/*****************************************************************************
*
* .b
*   Copyright (c) 1996 ABB Daimler-Benz Transportation (North America) Inc.
*
*   Project:
*               Common
*
*   File Name:
*               ptudata.c
*
*   SubSystem:
*               PTU
*
*   Procedures:
*
*   EPROM Drawing:
*
* .b
*
*   History:        07/10/94    Creation of Version 3.0         jsl
*   Revised:        09/11/95    ddp
*                   - Added in compression data
*                   10/05/95    ddp
*                   - Removed compression data
*
*****************************************************************************/
#include "ptuprj.h"

#ifdef CCINTEL
#pragma datasegment (PTUData)
#endif

/*  Grab the PTU specific files.                                            */
#include "ptu.h"

MaxResponse_t DATAFARTYPE       Response;
MaxRequest_t DATAFARTYPE        Request;
SerialBuffer_t DATAFARTYPE      SerialBuffer[NUMOFCHANNELS][2];

