/*****************************************************************************
*
* .b
*   Copyright (c) 1991-95,2001 Bombardier Transportation (Holdings) USA Inc..
*
*   Project:
*               Common
*
*   File Name:
*               ptuprj.h
*
*   SubSystem:
*               PTU
*
*   EPROM Drawing:
*
* .b
*
*   History:        05/04/95    Creation of Version 3.0         ddp
*   Revised:        05/11/95    ddp @ATSI
*                   - cleaned up initial version to use PTU with IVPS
*                   12/23/99	RAZ @ADtranz
*                   - Defined DAC type 2 and made DACSIZE 4095.
*                   09/07/2001  SRT @ Bombardier
*                   - Deleted the constant "CHARTDACTYPE2" as it is not
*                     required.
*				    04/03/2002  Becki Cirinelli @ Bombardier Transportation
*							added constants for fixed chart recorder
*							scales and offsets
*				    07/16/2003  Amadou Diop @ Bombardier Transportation
*							Modified the VCU DACSIZE from 4095 to 
*                           4000 counts (10 V)
*           05/05/2009  D.Smail 
*             Modified VCU DACSIZE from 4095 to 4063l
*					6/1/2010	Andrew Thomas
*							- Changes for IP PTU
*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#define __ptuprj__    /* for ptu.h */

#define SYNC_SOM        ':'
#define ASYNC_SOM       ';'
#define MOTOROLA_SOM    'S'

#define WATCHSIZE                   40

/* LILLE - AC DRIVE PROPULSION */
#ifdef LILLE

#ifndef  __noincludesptu__
#include "ptuprg.h"
#include "pturmk.h"
#include "cpu_dep.h"
#include "car_def.h"
#include "car_def2.h"
#include "get_slot.h"
#endif

#include <ptulipr.h>

#define CCINTEL         1               /* Uses an Intel C-Compiler */
#define DATAFARTYPE     far
#define CODEFARTYPE     far

#define DELAYCONSTANT   650             /* Communication Delay Factor */
#define THE_SOM         SYNC_SOM

#define CHANNEL0_CNTRL  0x0408          /* Serial Channel Addresses */
#define CHANNEL1_CNTRL  0x0400
#define CHANNEL0_DATA   0x040c
#define CHANNEL1_DATA   0x0404
#define PTUinbyte(x)    inbyte((UINT_16)x)
#define PTUoutbyte(x,t) outbyte((UINT_16)x,t)


#define CHARTDACTYPE1   1
#define DACSIZE         255l            /* The size in bits of the DACs used. */

#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0xbe
#define CHARTCHANNEL1   0x3e
#define CHARTCHANNEL2   0xbd
#define CHARTCHANNEL3   0x3d
#define CHARTCHANNEL4   0xbb
#define CHARTCHANNEL5   0x3b
#define CHARTCHANNEL6   0xb7
#define CHARTCHANNEL7   0x37

#endif


/* DART - AC DRIVE PROPULSION */
#ifdef DART

#ifndef  __noincludesptu__
#include "ptuprg.h"
#include "pturmk.h"
#include "cpu_dep.h"
#include "car_def.h"
#include "car_def2.h"
#include "get_slot.h"
#include <i386.h>
#endif

#include <ptudapr.h>

#define CCINTEL         1               /* Uses an Intel C-Compiler */
#define DATAFARTYPE     far
#define CODEFARTYPE     far

#define DELAYCONSTANT   650             /* Communication Delay Factor */
#define THE_SOM         SYNC_SOM

#define CHANNEL0_CNTRL  0x0408          /* Serial Channel Addresses */
#define CHANNEL1_CNTRL  0x0400
#define CHANNEL0_DATA   0x040c
#define CHANNEL1_DATA   0x0404
#define PTUinbyte(x)    inbyte((UINT_16)x)
#define PTUoutbyte(x,t) outbyte((UINT_16)x,t)

#define CHARTDACTYPE1   1
#define DACSIZE         255l            /* The size in bits of the DACs used. */
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0xbe
#define CHARTCHANNEL1   0x3e
#define CHARTCHANNEL2   0xbd
#define CHARTCHANNEL3   0x3d
#define CHARTCHANNEL4   0xbb
#define CHARTCHANNEL5   0x3b
#define CHARTCHANNEL6   0xb7
#define CHARTCHANNEL7   0x37

#define PROP_EVENT_LOG  0
#define TEST_EVENT_LOG  1

#endif


/* LA GREEN LINE - AC DRIVE PROPULSION */
#ifdef LA

#ifndef  __noincludesptu__
#include "ptuprg.h"
#include "pturmk.h"
#include "cpu_dep.h"
#include "car_def.h"
#include "car_def2.h"
#include "get_slot.h"
#include <i386.h>
#endif

#include <ptulapr.h>

#define CCINTEL         1               /* Uses an Intel C-Compiler */
#define DATAFARTYPE     far
#define CODEFARTYPE     far

#define DELAYCONSTANT   650             /* Communication Delay Factor */
#define THE_SOM         SYNC_SOM

#define CHANNEL0_CNTRL  0x0408          /* Serial Channel Addresses */
#define CHANNEL1_CNTRL  0x0400
#define CHANNEL0_DATA   0x040c
#define CHANNEL1_DATA   0x0404
#define PTUinbyte(x)    inbyte((UINT_16)x)
#define PTUoutbyte(x,t) outbyte((UINT_16)x,t)

#define CHARTDACTYPE1   1
#define DACSIZE         255l            /* The size in bits of the DACs used. */
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0xbe
#define CHARTCHANNEL1   0x3e
#define CHARTCHANNEL2   0xbd
#define CHARTCHANNEL3   0x3d
#define CHARTCHANNEL4   0xbb
#define CHARTCHANNEL5   0x3b
#define CHARTCHANNEL6   0xb7
#define CHARTCHANNEL7   0x37

#endif


/* TTC -T1 : AC DRIVE PROPULSION */
#ifdef TOR

#ifndef  __noincludesptu__
#include "ptuprg.h"
#include "pturmk.h"
#include "cpu_dep.h"
#include "car_def.h"
#include "car_def2.h"
#include "get_slot.h"
#include <i386.h>
#endif

#include <ptutrpr.h>

#define CCINTEL         1               /* Uses an Intel C-Compiler */
#define DATAFARTYPE     far
#define CODEFARTYPE     far

#define PTUSERIALINT    1               /* serial interrupts */
#define DELAYCONSTANT   650             /* Communication Delay Factor */
#define THE_SOM         SYNC_SOM

#define CHANNEL0_CNTRL  0x0408          /* Serial Channel Addresses */
#define CHANNEL1_CNTRL  0x0400
#define CHANNEL0_DATA   0x040c
#define CHANNEL1_DATA   0x0404
#define PTUinbyte(x)    inbyte((UINT_16)x)
#define PTUoutbyte(x,t) outbyte((UINT_16)x,t)

#define CHARTDACTYPE1   1
#define DACSIZE         255l            /* The size in bits of the DACs used. */
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0xbe
#define CHARTCHANNEL1   0x3e
#define CHARTCHANNEL2   0xbd
#define CHARTCHANNEL3   0x3d
#define CHARTCHANNEL4   0xbb
#define CHARTCHANNEL5   0x3b
#define CHARTCHANNEL6   0xb7
#define CHARTCHANNEL7   0x37

#endif


/* TAIPEI : AC DRIVE PROPULSION */
#ifdef TAIPEI

#ifndef  __noincludesptu__
#include "ptuprg.h"
#include "pturmk.h"
#include "cpu_dep.h"
#include "car_def.h"
#include "car_def2.h"
#include "get_slot.h"
#include <i386.h>
#endif

#include <ptutapr.h>

#define CCINTEL         1               /* Uses an Intel C-Compiler */
#define DATAFARTYPE     far
#define CODEFARTYPE     far

#define DELAYCONSTANT   650             /* Communication Delay Factor */
#define THE_SOM         SYNC_SOM

#define CHANNEL0_CNTRL  0x0408          /* Serial Channel Addresses */
#define CHANNEL1_CNTRL  0x0400
#define CHANNEL0_DATA   0x040c
#define CHANNEL1_DATA   0x0404
#define PTUinbyte(x)    inbyte((UINT_16)x)
#define PTUoutbyte(x,t) outbyte((UINT_16)x,t)

#define CHARTDACTYPE1   1
#define DACSIZE         255l            /*  The size in bits of the DACs used. */
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0xbb
#define CHARTCHANNEL1   0x3b
#define CHARTCHANNEL2   0xb7
#define CHARTCHANNEL3   0x37
#define CHARTCHANNEL4   0xaf
#define CHARTCHANNEL5   0x2f
#define CHARTCHANNEL6   0x9f
#define CHARTCHANNEL7   0x1f

#endif


/* R110A : AC DRIVE PROPULSION */
#ifdef R110

#ifndef  __noincludesptu__
#include "ptuprg.h"
#include "pturmk.h"
#include "cpu_dep.h"
#include "car_def.h"
#include "car_def2.h"
#include "get_slot.h"
#include <i386.h>
#endif

#include <ptur1pr.h>

#define CCINTEL         1               /* Uses an Intel C-Compiler */
#define DATAFARTYPE     far
#define CODEFARTYPE     far
#define THE_SOM         SYNC_SOM

#define PTUSERIALINT    1               /* serial interrupts */
#define DELAYCONSTANT   650             /* Communication Delay Factor */

#define CHANNEL0_CNTRL  0x0408          /* Serial Channel Addresses */
#define CHANNEL1_CNTRL  0x0400
#define CHANNEL0_DATA   0x040c
#define CHANNEL1_DATA   0x0404
#define PTUinbyte(x)    inbyte((UINT_16)x)
#define PTUoutbyte(x,t) outbyte((UINT_16)x,t)

#define CHARTDACTYPE1   1
#define DACSIZE         255l            /* The size in bits of the DACs used. */
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0xbe
#define CHARTCHANNEL1   0x3e
#define CHARTCHANNEL2   0xbd
#define CHARTCHANNEL3   0x3d
#define CHARTCHANNEL4   0xbb
#define CHARTCHANNEL5   0x3b
#define CHARTCHANNEL6   0xb7
#define CHARTCHANNEL7   0x37

#endif


/* R110 - Intermediate Voltage Power Supply */
#ifdef R110IVPS

#ifndef  __noincludesptu__
#include <rmxc.h>
#include <rmxerr.h>
#include "cpu_dep.h"
#include <i186.h>
#endif

#include <ptur1iv.h>

#define CCINTEL         1               /* Uses an Intel C-Compiler */
#define DATAFARTYPE     far
#define CODEFARTYPE     far

#define DELAYCONSTANT   100             /* Communication Delay Factor */
#define THE_SOM         SYNC_SOM

#define CHANNEL0_CNTRL  0x7204          /* Serial Channel Addresses */
#define CHANNEL1_CNTRL  0x7200
#define CHANNEL0_DATA   0x7206
#define CHANNEL1_DATA   0x7202
#define PTUinbyte(x)    inbyte((UINT_16)x)
#define PTUoutbyte(x,t) outbyte((UINT_16)x,t)

#define CHARTDACTYPE1   1
#define DACSIZE         4095l           /* The size in bits of the DACs used. */
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0xbe
#define CHARTCHANNEL1   0x3e
#define CHARTCHANNEL2   0xbd
#define CHARTCHANNEL3   0x3d
#define CHARTCHANNEL4   0xbb
#define CHARTCHANNEL5   0x3b
#define CHARTCHANNEL6   0xb7
#define CHARTCHANNEL7   0x37

#endif


/* R110 - Low Voltage Power Supply */
#ifdef R110LVPS

#ifndef  __noincludesptu__
#include <rmxc.h>
#include <rmxerr.h>
#include "cpu_dep.h"
#include <i186.h>
#endif

#include <ptur1lv.h>

#define CCINTEL         1               /* Uses an Intel C-Compiler */
#define DATAFARTYPE     far
#define CODEFARTYPE     far

#define DELAYCONSTANT   100             /* Communication Delay Factor */
#define THE_SOM         SYNC_SOM

#define CHANNEL0_CNTRL  0x7204          /* Serial Channel Addresses */
#define CHANNEL1_CNTRL  0x7200
#define CHANNEL0_DATA   0x7206
#define CHANNEL1_DATA   0x7202
#define PTUinbyte(x)    inbyte((UINT_16)x)
#define PTUoutbyte(x,t) outbyte((UINT_16)x,t)

#define CHARTDACTYPE1   1
#define DACSIZE         255l            /* The size in bits of the DACs used. */
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0xbe
#define CHARTCHANNEL1   0x3e
#define CHARTCHANNEL2   0xbd
#define CHARTCHANNEL3   0x3d
#define CHARTCHANNEL4   0xbb
#define CHARTCHANNEL5   0x3b
#define CHARTCHANNEL6   0xb7
#define CHARTCHANNEL7   0x37

#endif


/* BART -  Auxilliary Power Supply */
#ifdef BARTAPS

#ifndef  __noincludesptu__
#include <c166.h>
#include <reg167.h>
#include "c:/rtxc/kernel/rtxcapi.h"
#include "cpu_dep.h"
#endif

#include <ptubrap.h>

#define DATAFARTYPE         far
#define CODEFARTYPE         huge

#define DELAYCONSTANT   650             /* Communication Delay Factor */
#define THE_SOM         SYNC_SOM

#define CHANNEL0_CNTRL  0x500004        /* Serial Channel Addresses */
#define CHANNEL1_CNTRL  0x500000
#define CHANNEL0_DATA   0x500006
#define CHANNEL1_DATA   0x500002
#define PTUinbyte(x)    (unsigned char huge *)x
#define PTUoutbyte(x,t) (unsigned char huge *)x = t

#define CHARTDACTYPE1   2
#define MINCHARTCHANNEL 2
#define MAXCHARTCHANNEL 8

#define DACSIZE         255l            /* The size in bits of the DACs used. */
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0x300000
#define CHARTCHANNEL1   0x300002
#define CHARTCHANNEL2   0x300004
#define CHARTCHANNEL3   0x300006
#define CHARTCHANNEL4   0x300008
#define CHARTCHANNEL5   0x30000a
#define CHARTCHANNEL6   0x30000c
#define CHARTCHANNEL7   0x30000e

#define     puts(x)                 tputs(STDOUT, x)

#endif


/* FLEXIBLOK - vehicle ATO */
#ifdef ATCSVATO

#include "cpu_dep.h"
#include "ser_comm.h"

#define DATAFARTYPE
#define CODEFARTYPE

#define DELAYCONSTANT   0             /* Communication Delay Factor */
#define THE_SOM         MOTOROLA_SOM

/* Serial Controller Constants */

#define CHANNEL0_CNTRL      CHANNEL0_ADDRESS_CNTRL
#define CHANNEL1_CNTRL      CHANNEL1_ADDRESS_CNTRL
#define CHANNEL0_DATA       CHANNEL0_ADDRESS_DATA
#define CHANNEL1_DATA       CHANNEL1_ADDRESS_DATA
#define PTUinbyte(x)        x
#define PTUoutbyte(x,t)     x = t

#define TRANSEMPTYPENDING       0x10
#define TRANSREADYSTATBIT       0x01
#define RECVREADYSTATBIT        0x01

#define RXSTATUSREG     0x24
#define TXSTATUSREG     0x34
#define TXDATAREG       0x70
#define RXDATAREG       0x60


/* #define CHARTDACTYPE1   0   */
#define DACSIZE             255l    /* The size in bits of the DACs */
#define CHARTLATCHTYPE1     0xff
#define CHARTLATCHTYPE2     0x7f

#define CHARTCHANNEL0   0xbe
#define CHARTCHANNEL1   0x3e
#define CHARTCHANNEL2   0xbd
#define CHARTCHANNEL3   0x3d
#define CHARTCHANNEL4   0xbb
#define CHARTCHANNEL5   0x3b
#define CHARTCHANNEL6   0xb7
#define CHARTCHANNEL7   0x37

#endif


/* BART -  Inverter Controller */
#ifdef BARTINV

#ifndef  __noincludesptu__
#include <c166.h>
#include <reg167.h>
#include <rtxcapi.h>
#include "cpu_dep.h"
#endif

#include "ptubain.h"
#include "init_def.h"

#define DATAFARTYPE         far
#define DATAFARTYPE_2       huge
#define CODEFARTYPE         huge

#define DELAYCONSTANT     650             /* Communication Delay Factor */
#define THE_SOM         SYNC_SOM

#define CHANNEL0_CNTRL     0x600020        /* Serial Channel Addresses */
#define CHANNEL1_CNTRL     0x600060
#define CHANNEL0_DATA      0x600000        /* 1st byte of TXFIFO/RFIFO */
#define CHANNEL1_DATA      0x600040
#define CHANNEL0_INTSTAT_0 0x60003a        /* Interrupt Status Register 0 */
#define CHANNEL0_INTSTAT_1 0x60003b        /* Interrupt Status Register 1 */
#define CHANNEL1_INTSTAT_0 0x60007a
#define CHANNEL1_INTSTAT_1 0x60007b


#define PTUinbyte(x)    *x
#define PTUoutbyte(x,t) *x = t

#define TRANSREADYSTATBIT       0x40        /* XFW bit in STAR */
#define RECVREADYSTATBIT        0x20        /* RFIFO not empty in STAR */


#define CHARTDACTYPE3   1
#define MINCHARTCHANNEL 0
#define MAXCHARTCHANNEL 8           /* 8 channels 0 - 7 */

#define DACSIZE         4095l            /* The size in bits of the DACs used. */
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0x600130
#define CHARTCHANNEL1   0x600132
#define CHARTCHANNEL2   0x600134
#define CHARTCHANNEL3   0x600136
#define CHARTCHANNEL4   0x600138
#define CHARTCHANNEL5   0x60013a
#define CHARTCHANNEL6   0x60013c
#define CHARTCHANNEL7   0x60013e

#define     puts(x)                 tputs(STDOUT, x)

extern volatile UINT_8 *SerialControlRegister[];
extern volatile UINT_8 *SerialDataRegister[];
extern volatile UINT_8 *InterruptStatusRegister0[];
extern volatile UINT_8 *InterruptStatusRegister1[];

#define RPF_BIT   0x01
#define RMC_BIT   0x80
#define XPR_BIT   0x01
#define ALLS_BIT  0x20

#define MAIN_EVENT_LOG  0

#endif

/* Hong Kong -  Inverter Controller */
#ifdef HKPAINV

#ifndef  __noincludesptu__
#include <c166.h>
#include <reg167.h>
#include <rtxcapi.h>
#include "cpu_dep.h"
#endif

#include "ptuhkin.h"
#include "init_def.h"

#define DATAFARTYPE         far
#define DATAFARTYPE_2       huge
#define CODEFARTYPE         huge

#define DELAYCONSTANT     650             /* Communication Delay Factor */
#define THE_SOM         SYNC_SOM

#define CHANNEL0_CNTRL     0x600020        /* Serial Channel Addresses */
#define CHANNEL1_CNTRL     0x600060
#define CHANNEL0_DATA      0x600000        /* 1st byte of TXFIFO/RFIFO */
#define CHANNEL1_DATA      0x600040
#define CHANNEL0_INTSTAT_0 0x60003a        /* Interrupt Status Register 0 */
#define CHANNEL0_INTSTAT_1 0x60003b        /* Interrupt Status Register 1 */
#define CHANNEL1_INTSTAT_0 0x60007a
#define CHANNEL1_INTSTAT_1 0x60007b


#define PTUinbyte(x)    *x
#define PTUoutbyte(x,t) *x = t

#define TRANSREADYSTATBIT       0x40        /* XFW bit in STAR */
#define RECVREADYSTATBIT        0x20        /* RFIFO not empty in STAR */


#define CHARTDACTYPE3   1
#define MINCHARTCHANNEL 0
#define MAXCHARTCHANNEL 8           /* 8 channels 0 - 7 */

#define DACSIZE         4095l            /* The size in bits of the DACs used. */
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0x600130
#define CHARTCHANNEL1   0x600132
#define CHARTCHANNEL2   0x600134
#define CHARTCHANNEL3   0x600136
#define CHARTCHANNEL4   0x600138
#define CHARTCHANNEL5   0x60013a
#define CHARTCHANNEL6   0x60013c
#define CHARTCHANNEL7   0x60013e

#define     puts(x)                 tputs(STDOUT, x)

extern volatile UINT_8 *SerialControlRegister[];
extern volatile UINT_8 *SerialDataRegister[];
extern volatile UINT_8 *InterruptStatusRegister0[];
extern volatile UINT_8 *InterruptStatusRegister1[];

#define RPF_BIT   0x01
#define RMC_BIT   0x80
#define XPR_BIT   0x01
#define ALLS_BIT  0x20

#define MAIN_EVENT_LOG  0

#endif

/* VCU */
/* #ifdef VCU */

#if !defined (BC)
#ifdef TEST_ON_PC

#include "myWrapper.h"

#else

#include "rts_api.h"

#ifndef  __noincludesptu__
#include "cpu_dep.h"
#endif

#endif

#endif



#include "ptutopc.h"	

#ifdef DEBUG_PRINT
#define debugPrintf(fmt, args...)    os_io_printf(fmt, ## args)
#else
#define debugPrintf(fmt, args...)    /* Don't do anything in release builds; code effectively doesn't exist */
#endif

#define DATAFARTYPE
#define DATAFARTYPE_2
#define CODEFARTYPE

#define DELAYCONSTANT   1               /* Communication Delay Factor */
#ifdef TEST_ON_PC
#define THE_SOM         SYNC_SOM
#else
#define THE_SOM			 MOTOROLA_SOM
#endif

#define CHANNEL0_CNTRL  0x0408          /* Serial Channel Addresses */
#define CHANNEL1_CNTRL  0x0400
#define CHANNEL0_DATA   0x040c
#define CHANNEL1_DATA   0x0404
#define PTUinbyte(x)    inbyte((UINT_16)x)
#define PTUoutbyte(x,t) outbyte((UINT_16)x,t)

#define CHARTDACTYPE1   1
#define DACSIZE         4000L
#define CHARTLATCHTYPE1 0xff
#define CHARTLATCHTYPE2 0x7f

#define CHARTCHANNEL0   0xbe
#define CHARTCHANNEL1   0x3e
#define CHARTCHANNEL2   0xbd
#define CHARTCHANNEL3   0x3d
#define CHARTCHANNEL4   0xbb
#define CHARTCHANNEL5   0x3b
#define CHARTCHANNEL6   0xb7
#define CHARTCHANNEL7   0x37

#define PROP_EVENT_LOG  0

#define     SERIAL_DEVICE_NAME      OS_IO_COM2
//#define     SERIAL_DEVICE_NAME      "/tyCo/4"
#define     NUM_SERIAL_CHANNELS     1

#define CAR_SPEED_OFFSET     0
#define CAR_SPEED_SCALE      50
#define RATE_REQUEST_OFFSET  0
#define RATE_REQUEST_SCALE   5
#define RATE_REQUEST_SCALE_FACTOR 10000
#define TE_RQSTD_OFFSET      10000
#define TE_RQSTD_SCALE       20000
#define TE_DLVRD_OFFSET      10000
#define TE_DLVRD_SCALE       20000
#define VLINE_OFFSET         0
#define VLINE_SCALE          1000
#define ILINE_OFFSET         1500
#define ILINE_SCALE          3000
#define VLINK_OFFSET         0
#define VLINK_SCALE          1000
#define INV_STATUS_OFFSET    0
#define INV_STATUS_SCALE     50

#define FIX_CH1 0
#define FIX_CH2 1
#define FIX_CH3 2
#define FIX_CH4 3
#define FIX_CH5 4
#define FIX_CH6 5
#define FIX_CH7 6
#define FIX_CH8 7

/* #endif */
#ifdef __cplusplus
}
#endif
