/*
 * myWrapper.h
 *
 *  Created on: Aug 21, 2015
 *      Author: Dave
 */

#ifndef MYWRAPPER_H_
#define MYWRAPPER_H_

#include <stdio.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned 		 		UINT_32, UINT32;
typedef signed  				INT_32, INT32;
typedef short int 				INT_16, INT16;
typedef unsigned short int 	UINT_16, UINT16;
typedef unsigned char 		UINT_8;
typedef signed char 			INT_8;


#define ERROR 			(-1)
#define OK 				(0)

#define DATAFARTYPE

#define IP_TIMEVAL			struct timeval
#define os_ip_socket		socket
#define os_errno			errno
#define os_ip_select		select
#define os_io_printf   		printf
#define os_ip_close			close
#define os_ip_bind     		bind
#define os_ip_accept   		accept
#define os_ip_listen   		listen
#define os_ip_recv     		recv
#define os_ip_setsockopt	setsockopt
#define os_ip_shutdown		shutdown
#define os_ip_send			send
#define os_io_read			read
#define os_io_write 		write

struct date_time_type  {
  UINT_8   hr;                    /* hours */
  UINT_8   min;                   /* minutes */
  UINT_8   sec;                   /* seconds */
  UINT_8 month;					  /* month */
  UINT_8 day;                     /* day */
#ifdef TOPC
  UINT_16 year;                    /* year */
  UINT_8 spare;                     /* day */
#else
  UINT_8 year;
#endif
}  __attribute__ ((packed));


#endif /* MYWRAPPER_H_ */
