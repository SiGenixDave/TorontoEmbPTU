/*****************************************************************************
*
* .b
*   Copyright (c) 1991-1995 AEG Transportation Systems Inc.
*
*   Project:
*               Common
*
*   File Name:
*               ptusrl.c
*
*   SubSystem:
*               PTU
*
*   Procedures:
*               tgetc
*               tputc
*               comm_init
*               ptu_test
*
*   EPROM Drawing:
*
* .b
*
*   History:    03/30/92    Creation of Version 2.0         jsl
*   Revised:    04/05/95    D. Pradhan @ ATSI
*                           - integrated all jobs to have one source.
*                           - cleaned up comments and code.
*				04/15/2003  Rebecca Cirinelli  @ Bombardier Transportation
*					- Added bbram check before rts mon task is deleted
*                   - Added getcbramsize and getncbramsize to obtain the
*                     sizes of the constant and non-constant bbram that
*                     are part of the rhapsody packages
*               03/13/2008 Erik Holm
*                   - See comm_init().
*				6/1/2010	Andrew Thomas
*					- Changes for IP PTU
*				11/21/2012 Erik Holm
*					- See comm_init().
*
*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "ptuprj.h"

#ifndef TEST_ON_PC
#include "batram.h"
#else
#include "rs232.h"
#endif

/*  Grab the PTU specific files.                                            */
#include "ptu.h"

#ifndef EOF
#define     EOF         -1
#endif

INT32                       fds[NUM_SERIAL_CHANNELS];

#ifndef COMC_PTU
extern UINT_16 getcbramsize(void);
extern UINT_16 getncbramsize(void);
#endif

/****************************************************************************
*
* .b
*   Procedure Name:                 tgetc
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*
*       Constants:
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values:
*
*   Functional Description:
*
* .b
*
*   History:        04/05/95    Creation of Version 1.0             ddp
*
*****************************************************************************/

/* reads a byte from the Serial port corresponding to the passed channel */
/* returns EOF if nothing read else returns the byte read */
INT_16 tgetc(INT_16 channel)
{
#ifdef TEST_ON_PC
    int n;
	unsigned char buf;

	n = RS232_PollComport(0, &buf, 1);

	if (n > 0) {
		printf ("RX - %d\n", buf);
		return (INT_16)buf;
	}
	else
	{
		return EOF;
	}
#else
    UINT_8           byte_read;
    INT_16           word_read;
    INT_16           status;
    INT32            no_of_bytes_read;
    /* Read the Port */
    status = os_io_read(fds[channel], (char *)&byte_read, 1, 0 /*TRUE*/, &no_of_bytes_read);

    /* Force return character to EOF on Error or nothing to read */
    if ((status == ERROR) || (no_of_bytes_read == 0))
	{
		word_read = EOF;
	}
	else
    {
    	word_read = (INT_16)byte_read;
    }
    
    /* Return a word */
    return(word_read);
#endif

}

/****************************************************************************
*
* .b
*   Procedure Name:                 tputc
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*
*       Constants:
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values:
*
*   Functional Description:
*
* .b
*
*   History:        04/05/95    Creation of Version 1.0             ddp
*
*****************************************************************************/

/* writes a byte to the Serial port corresponding to the passed channel */
void tputc(INT_16 channel, UINT_8 byte_to_write)
{
#ifdef TEST_ON_PC
	// return value of 0 is success
	while (RS232_SendByte (0, byte_to_write));
	// Required when running VPSE to slow the data rate down
	Sleep(2);
	printf ("TX - %d\n", byte_to_write);
#else
	INT32 no_of_bytes_written;

	/* Write to the Port */
    os_io_write(fds[channel], (char *)&byte_to_write, 1, TRUE, &no_of_bytes_written);
#endif
}

/****************************************************************************
*
* .b
*   Procedure Name:                 comm_init
*
*   Abstract:
*
*   INPUTS:
*
*       Globals:
*
*       Constants:
*
*       Procedure Parameters:
*
*   OUTPUTS
*
*       Globals:
*
*       Returned Values:
*
*   Functional Description:
*
* .b
*
*   History:        04/05/95    Creation of Version 1.0             ddp
*                   10/08/2002  Sarfaraz Taher
*                   - Added deletion of the RTS Mon task.
*					04/15/2003  Rebecca Cirinelli
*					- Added bbram check before rts mon task is deleted
*                     getcbramsize and getncbramsize are used to get the
*                     sizes of the constant and non-constant bbram that
*                     are part of the rhapsody packages
*					10/26/2004  Amadou Diop
*					- Added check for COMC PTU to process BBRAM
*                   03/13/2008 Erik Holm
*                     Replaced macro MAX_BBRAM_SIZE with NVRAM_SIZE.
*                     Added OS_RESET_IDLE as reset reason.
*					11/21/2012 Erik Holm
*					  Replaced NVRAM_SIZE with a call to the CSS NVRAM API.
*                  
*****************************************************************************/
#ifndef TEST_ON_PC
/* initialize comm ports */
INT_16 comm_init(void)
{
	UINT_32 data_size = 0;
	UINT_16 csize = 0;
	UINT_16 ncsize = 0;
	nvram_dev_info_t dev_info;
	nvram_seg_info_t seg_info_array[NVRAM_MAX_NUM_SEGS];
	UINT_32 nvram_size = 0;
	INT_32 result = -1;

	#ifndef COMC_PTU
	/* Check BBRAM data size */
	csize = getcbramsize();
	ncsize = getncbramsize();

	data_size = BBRAM_DATA_SIZE+csize+ncsize;
/* Find out how much NVRAM is available. Use the CSS NVRAM API */
	/* Send a request for the current NVRAM status */
	/* The API returns the number of available NVRAM segments */
	result = nvram_info(&dev_info, NULL);

	if (result >= 0)
	{
		/* Success. Find out the total size of availble NVRAM */
		nvram_size = (UINT_32)dev_info.size;
	}
	else
	{
		/* Error. No NVRAM available */
		nvram_size = 0;
	}

	os_io_printf("\r \n nvram_info result = %d", result);
	os_io_printf("\r \n nvram size = %d", nvram_size);
	os_io_printf("\r \n data size = %d", data_size);

	/* Check if requested size fits in NVRAM */
	if (data_size > nvram_size)
	{
		/* Print messages */
		os_io_printf("\r \n !!!!BBRAM data size too large!!!!");

		/* Wait */
 		os_t_delay(100);

		/* Reset and go back to the test mode */
		os_hi_shutdown(OS_RESET_IDLE);
	}
    #endif


	/* Open this Serial Port */
	if ( os_io_open(OS_IO_COM4, &fds[0]) == ERROR)
	{
		os_io_printf ("\n##############ERROR!!!!Open this Serial Port\r");
		return(ERROR);
	}
	else
	{
		os_io_printf ("\n*************SUCCESS!!!!Opening this Serial Port\r");
	}

	/* Set all options OFF ... raw mode */
	if (os_io_ctrl(fds[0], OS_IO_OPTIONS_SET, OS_IO_ARG_RAW) == ERROR)
	{
	/*	os_io_printf ("\n##############ERROR!!!!Set all options OFF ... raw mode\r");*/
		return(ERROR);
	} 
	else
	{
		/*os_io_printf ("\n*************SUCCESS!!!!Set all options OFF ... raw mode\r");*/
	}

  return(OK);
}
#endif

void ptu_test(void)
{
  INT_16 error;

  error = ptu_init();
  PTUMain();
}

/* #endif */
#ifdef __cplusplus
}
#endif
