#include  "ptuconxt.h"

const     struct    VariableDef_t       VariableDef[NUMDEFINEDVARS] =
{
/*  Variable Number 0 */
/* Architecture Version */
          {
                    &u16[ARCHVERSION],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1 */
/* BBRam - Const BBram Flag */
          {
                    &u8[cbramFlag],
                    UINT_8_TYPE,
                    0,                            0,
                    PTUD_PSSWD1
          },
/*  Variable Number 2 */
/* BBRam - Const Car ID */
          {
                    &u16[cbramCarId],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 3 */
/* BBRam - Const Crc */
          {
                    &u16[cbramCrc],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD1
          },
/*  Variable Number 4 */
/* BBRam - Const Pattern */
          {
                    &u16[cbramPattern],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD1
          },
/*  Variable Number 5 */
/* BBRam - Const SW Version */
          {
                    &u32[cbramSwVersion],
                    UINT_32_TYPE,
                    255,                          0,
                    PTUD_PSSWD1
          },
/*  Variable Number 6 */
/* BBRam - Const Test Var */
          {
                    &u16[cbramTestVar],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD1
          },
/*  Variable Number 7 */
/* BBRam - Non Constant Bram End */
          {
                    &u32[ncbramBramEnd],
                    UINT_32_TYPE,
                    255,                          0,
                    PTUD_PSSWD1
          },
/*  Variable Number 8 */
/* BBRam - Non Constant Test Var */
          {
                    &u16[ncbramTestVar],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD1
          },
/*  Variable Number 9 */
/* BBRam - RTS Mon Mode */
          {
                    &u16[ptuRTSMonMode],
                    UINT_16_TYPE,
                    10,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 10 */
/* Debug 1 I16 */
          {
                    &i16[Debug16i1],
                    INT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 11 */
/* Debug 1 I32 */
          {
                    &i32[Debug32i1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 12 */
/* Debug 1 U16 */
          {
                    &u16[Debug16u1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 13 */
/* Debug 1 U32 */
          {
                    &u32[Debug32u1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 14 */
/* Debug 2 I16 */
          {
                    &i16[Debug16i2],
                    INT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 15 */
/* Debug 2 I32 */
          {
                    &i32[Debug32i2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 16 */
/* Debug 2 U16 */
          {
                    &u16[Debug16u2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 17 */
/* Debug 2 U32 */
          {
                    &u32[Debug32u2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 18 */
/* Debug 3 I16 */
          {
                    &i16[Debug16i3],
                    INT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 19 */
/* Debug 3 I32 */
          {
                    &i32[Debug32i3],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 20 */
/* Debug 3 U16 */
          {
                    &u16[Debug16u3],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 21 */
/* Debug 3 U32 */
          {
                    &u32[Debug32u3],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 22 */
/* Debug 4 I16 */
          {
                    &i16[Debug16i4],
                    INT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 23 */
/* Debug 4 I32 */
          {
                    &i32[Debug32i4],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 24 */
/* Debug 4 U16 */
          {
                    &u16[Debug16u4],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 25 */
/* Debug 4 U32 */
          {
                    &u32[Debug32u4],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 26 */
/* Debug 5 I16 */
          {
                    &i16[Debug16i5],
                    INT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 27 */
/* Debug 5 I32 */
          {
                    &i32[Debug32i5],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 28 */
/* Debug 5 U16 */
          {
                    &u16[Debug16u5],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 29 */
/* Debug 5 U32 */
          {
                    &u32[Debug32u5],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 30 */
/* Debug 6 I16 */
          {
                    &i16[Debug16i6],
                    INT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 31 */
/* Debug 6 I32 */
          {
                    &i32[Debug32i6],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 32 */
/* Debug 6 U16 */
          {
                    &u16[Debug16u6],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 33 */
/* Debug 6 U32 */
          {
                    &u32[Debug32u6],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 34 */
/* Inp - DI 340 Inputs */
          {
                    &i32[DI340INPUTWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 35 */
/* Inp - DI 340 STS Word */
          {
                    &i32[DI340STSWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 36 */
/* Inp - DI 340 Self Test Toggle Bit */
          {
                    &i32[DI340STTBWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 37 */
/* Inp - DX 330 Self Test Toggle Bit */
          {
                    &i32[DX330STTBWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 38 */
/* Inp - DX 360 Self Test Toggle Bit */
          {
                    &i32[DX360STTBWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 39 */
/* Inp - Input Counter */
          {
                    &u16[IOCounter],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 40 */
/* Inp - AX 320 Self Test Toggle Bit  */
          {
                    &i32[AX320_STTBWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 41 */
/* Inp - DX 360 Inputs */
          {
                    &i32[DX360INPUTWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 42 */
/* Inp - DX 330 Inputs */
          {
                    &i32[DX330INPUTWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 43 */
/* Inp - AX 520 Self Test Toggle Bit */
          {
                    &i32[AX520_STTBWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 44 */
/* Inp - AX 370 STTB Status */
          {
                    &u32[AX370_STTBSTATUS],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 45 */
/* Inp - AX 520 STTB Status */
          {
                    &u32[AX520_STTBSTATUS],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 46 */
/* Inp - AX 320 STTB Status */
          {
                    &u32[AX320_STTBSTATUS],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 47 */
/* Inp - AX 320 Self Test Status */
          {
                    &i32[AX320_STATUS],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 48 */
/* Inp - AX 370 Self Test Status */
          {
                    &i32[AX370_STATUS],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 49 */
/* Inp - AX 520 Self Test Status */
          {
                    &i32[AX520_STATUS],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 50 */
/* Inp - AX 370 Self Test Toggle Bit  */
          {
                    &i32[AX370_STTBWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 51 */
/* Inp - DX 330 STS Word */
          {
                    &i32[DX330STSWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 52 */
/* Inp - DX 360 STS Word */
          {
                    &i32[DX360STSWORD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 53 */
/* Inp - AX 320 Battery Voltage */
          {
                    &i32[AX320_BATTVOLT],
                    INT_32_TYPE,
                    1000,                         0,
                    PTUD_READONLY
          },
/*  Variable Number 54 */
/* Inp - Line Voltage #1 */
          {
                    &i32[AX320_LINEVOLTAGE],
                    INT_32_TYPE,
                    1000,                         0,
                    PTUD_READONLY
          },
/*  Variable Number 55 */
/* Inp - Line Current #1 */
          {
                    &i32[AX320_LINECURRENT],
                    INT_32_TYPE,
                    1000,                         -1000,
                    PTUD_READONLY
          },
/*  Variable Number 56 */
/* Inp - Return Current #1 */
          {
                    &i32[AX320_RETCURRENT],
                    INT_32_TYPE,
                    1000,                         -1000,
                    PTUD_READONLY
          },
/*  Variable Number 57 */
/* Inp - AX 370 Battery Voltage */
          {
                    &i32[AX370_BATTVOLT],
                    INT_32_TYPE,
                    1000,                         0,
                    PTUD_READONLY
          },
/*  Variable Number 58 */
/* Inp - AX 520 Battery Voltage */
          {
                    &i32[AX520_BATTVOLT],
                    INT_32_TYPE,
                    1000,                         0,
                    PTUD_READONLY
          },
/*  Variable Number 59 */
/* Inp - Line Voltage #2 */
          {
                    &i32[AX370_LINEVOLTAGE],
                    INT_32_TYPE,
                    1000,                         0,
                    PTUD_READONLY
          },
/*  Variable Number 60 */
/* Inp - Line Current #2 */
          {
                    &i32[AX370_LINECURRENT],
                    INT_32_TYPE,
                    1000,                         -1000,
                    PTUD_READONLY
          },
/*  Variable Number 61 */
/* Inp - Return Current #2 */
          {
                    &i32[AX370_RETCURRENT],
                    INT_32_TYPE,
                    1000,                         -1000,
                    PTUD_READONLY
          },
/*  Variable Number 62 */
/* Inp - FB Cyl Pressure Truck 1 */
          {
                    &i32[AX320_FBPRESS],
                    INT_32_TYPE,
                    100,                          0,
                    PTUD_READONLY
          },
/*  Variable Number 63 */
/* Inp - FB Cyl Pressure Truck 2 */
          {
                    &i32[AX370_FBPRESS],
                    INT_32_TYPE,
                    100,                          0,
                    PTUD_READONLY
          },
/*  Variable Number 64 */
/* Inp - Main Reservoir Pressure */
          {
                    &i32[AX520_MRPRESS],
                    INT_32_TYPE,
                    200,                          0,
                    PTUD_READONLY
          },
/*  Variable Number 65 */
/* Inp - Load Weigh Press #1 */
          {
                    &i32[AX520_LWPRESS1],
                    INT_32_TYPE,
                    200,                          0,
                    PTUD_READONLY
          },
/*  Variable Number 66 */
/* Inp - Load Weigh Press #2 */
          {
                    &i32[AX520_LWPRESS2],
                    INT_32_TYPE,
                    200,                          0,
                    PTUD_READONLY
          },
/*  Variable Number 67 */
/* Inp - IT Switch */
          {
                    &i32[DI340ITSPOSITION],
                    INT_32_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 68 */
/* Inp - Car ID */
          {
                    &i32[DI340CARID],
                    INT_32_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 69 */
/* Inp - FB Cutout */
          {
                    &i32[DI340FBCUTOUT],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 70 */
/* Inp - Prop Overspeed Relay */
          {
                    &i32[DI340OVRSPDRELAY],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 71 */
/* Inp - LCBC #1 */
          {
                    &i32[DI340LCBC1],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 72 */
/* Inp - LCBC #2 */
          {
                    &i32[DI340LCBC2],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 73 */
/* Inp - Prop Emerg Shutdown */
          {
                    &i32[DI340ESHUTDOWN],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 74 */
/* Inp - Parking Brake Cutout */
          {
                    &i32[DI340PBCUTOUT],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 75 */
/* Inp - ATO Trainline 2 */
          {
                    &i32[DI340ATOSPARE],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 76 */
/* Inp - ATO Trainline 1 */
          {
                    &i32[DI340ATOTRNLINE],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 77 */
/* Inp - Ch #1 Zero Velocity */
          {
                    &i32[DI340ZEROVELCH1],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 78 */
/* Inp - Ch #2 Zero Velocity */
          {
                    &i32[DI340ZEROVELCH2],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 79 */
/* Inp - BVD K1-3 Status #1 */
          {
                    &i32[DX330BVDFDBKSTAT1],
                    INT_32_TYPE,
                    7,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 80 */
/* Inp - BVD K1-3 Status #2 */
          {
                    &i32[DX360BVDFDBKSTAT2],
                    INT_32_TYPE,
                    7,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 81 */
/* Inp - OLR Status #1 */
          {
                    &i32[DX330OLRSTAT1],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 82 */
/* Inp - OLR Status #2 */
          {
                    &i32[DX360OLRSTAT2],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 83 */
/* Inp - Parking Brake Status */
          {
                    &i32[DX330PBSTAT],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 84 */
/* Inp - Emergency Relay Status  #1 */
          {
                    &i32[DX330ERSTATUS1],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 85 */
/* Inp - Emergency Relay Status  #2 */
          {
                    &i32[DX360ERSTATUS2],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 86 */
/* Inp - Direction TL - Truck 1 */
          {
                    &i32[DX330DIRTL1],
                    INT_32_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 87 */
/* Inp - Direction TL - Truck 2 */
          {
                    &i32[DX360DIRTL2],
                    INT_32_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 88 */
/* Inp - BVD K4 Status #1 */
          {
                    &i32[DX330K4STAT],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 89 */
/* Inp - BVD K4 Status #2 */
          {
                    &i32[DX360K4STAT],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 90 */
/* ProdSt - BVD K1 Cmd Truck 1 */
          {
                    &u16[DX330OUT_K1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 91 */
/* ProdSt - BVD K2 Cmd Truck 1 */
          {
                    &u16[DX330OUT_K2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 92 */
/* ProdSt - BVD K3 Cmd Truck 1 */
          {
                    &u16[DX330OUT_K3],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 93 */
/* ProdSt - BVD K1 Cmd Truck 2 */
          {
                    &u16[DX360OUT_K1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 94 */
/* ProdSt - BVD K2 Cmd Truck 2 */
          {
                    &u16[DX360OUT_K2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 95 */
/* ProdSt - BVD K3 Cmd Truck 2  */
          {
                    &u16[DX360OUT_K3],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 96 */
/* ProdSt - Parking Brake Apply */
          {
                    &u16[DX330OUT_PBAPPLY],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 97 */
/* ProdSt - Parking Brake Release */
          {
                    &u16[DX330OUT_PBREL],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 98 */
/* ProdSt - Overload Relay #1 Cmd */
          {
                    &u16[DX330OUT_OLR1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 99 */
/* ProdSt - Overload Relay #2 Cmd */
          {
                    &u16[DX360OUT_OLR2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 100 */
/* ProdSt - Prop Overspeed Relay */
          {
                    &u16[DX360OUT_POR],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 101 */
/* ProdSt - Zero Velocity CH#1 Cmd */
          {
                    &u16[DX360OUT_ZV1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 102 */
/* ProdSt - ST Enable */
          {
                    &u16[PRODSTENABLE],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 103 */
/* ProdSt - FB Cmd Truck 1 */
          {
                    &u32[FB1CMDREQUEST],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 104 */
/* ProdSt - FB Cmd Truck 2 */
          {
                    &u32[FB2CMDREQUEST],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 105 */
/* Inp - Spare Trainline */
          {
                    &i32[DI340SSTRNLINE],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 106 */
/* Vel - Axle 1 Op Status */
          {
                    &u16[VelAxle1OpStatus],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 107 */
/* Vel - Axle 1 Raw RPM */
          {
                    &i32[VelAxle1Raw],
                    INT_32_TYPE,
                    9000000,                      0,
                    PTUD_READONLY
          },
/*  Variable Number 108 */
/* Vel - Axle 1 Speed */
          {
                    &u32[VelAxle1Speed],
                    UINT_32_TYPE,
                    110000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 109 */
/* Vel - Axle 2 Op Status */
          {
                    &u16[VelAxle2OpStatus],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 110 */
/* Vel - Axle 2 Raw RPM */
          {
                    &i32[VelAxle2Raw],
                    INT_32_TYPE,
                    9000000,                      0,
                    PTUD_READONLY
          },
/*  Variable Number 111 */
/* Vel - Axle 2 Speed */
          {
                    &u32[VelAxle2Speed],
                    UINT_32_TYPE,
                    110000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 112 */
/* Vel - Axle 3 Op Status */
          {
                    &u16[VelAxle3OpStatus],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 113 */
/* Vel - Axle 3 Raw RPM */
          {
                    &i32[VelAxle3Raw],
                    INT_32_TYPE,
                    9000000,                      0,
                    PTUD_READONLY
          },
/*  Variable Number 114 */
/* Vel - Axle 3 Speed */
          {
                    &u32[VelAxle3Speed],
                    UINT_32_TYPE,
                    110000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 115 */
/* Vel - Axle 4 Op Status */
          {
                    &u16[VelAxle4OpStatus],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 116 */
/* Vel - Axle 4 Raw RPM */
          {
                    &i32[VelAxle4Raw],
                    INT_32_TYPE,
                    9000000,                      0,
                    PTUD_READONLY
          },
/*  Variable Number 117 */
/* Vel - Axle 4 Speed */
          {
                    &u32[VelAxle4Speed],
                    UINT_32_TYPE,
                    110000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 118 */
/* Vel - Car Speed */
          {
                    &i32[VelCarSpeed],
                    INT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 119 */
/* Vel - Car State */
          {
                    &u16[VelCarState],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 120 */
/* Vel - Car Velocity */
          {
                    &i32[CarVelocity],
                    INT_32_TYPE,
                    110000,                       -110000,
                    PTUD_READONLY
          },
/*  Variable Number 121 */
/* Vel - Counter */
          {
                    &u16[VelCounter],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 122 */
/* Vel - Odometer */
          {
                    &u32[VelOdometer],
                    UINT_32_TYPE,
                    429496700,                    0,
                    PTUD_READONLY
          },
/*  Variable Number 123 */
/* Vel - Truck 1 Speed Calc High */
          {
                    &u16[VelTruck1SpeedCalcHi],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 124 */
/* Vel - Truck 1 Speed Calc Low */
          {
                    &u16[VelTruck1SpeedCalcLo],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 125 */
/* Vel - Zero Speed - Move */
          {
                    &u32[ZeroSpeedMove],
                    UINT_32_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 126 */
/* Vel - Zero Speed - Stop */
          {
                    &u32[ZeroSpeedStop],
                    UINT_32_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 127 */
/* Vel - Zero Speed Flag */
          {
                    &u16[VelZeroSpeedFlag],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 128 */
/* Vel - Truck 1 Speed */
          {
                    &u32[VelTruck1Speed],
                    UINT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 129 */
/* Vel - Truck 1 Status */
          {
                    &u16[VelTruck1Status],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 130 */
/* Vel - Truck 2 Speed */
          {
                    &u32[VelTruck2Speed],
                    UINT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 131 */
/* Vel - Truck 2 Status */
          {
                    &u16[VelTruck2Status],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 132 */
/* Vel - CarSpeedCalcHi Active */
          {
                    &u16[VelCarSpeedCalcHi],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 133 */
/* Vel - CarSpeedCalcLo Active */
          {
                    &u16[VelCarSpeedCalcLo],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 134 */
/* Vel - CarID */
          {
                    &u16[VelCarType],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 135 */
/* Vel - Truck 2 Speed Calc High */
          {
                    &u16[VelTruck2SpeedCalcHi],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 136 */
/* Vel - Truck 2 Speed Calc Low */
          {
                    &u16[VelTruck2SpeedCalcLo],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 137 */
/* MVB -  1024 PTU Override */
          {
                    &u16[mvb1024PtuOverride],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 138 */
/* MVB - 128 PTU Override */
          {
                    &u16[mvb128PtuOverride],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 139 */
/* MVB - 16 PTU Override */
          {
                    &u16[mvb16PtuOverride],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 140 */
/* MVB - 64 PTU Override */
          {
                    &u16[mvb64PtuOverride],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 141 */
/* MVB - D1VSPDAXL1 */
          {
                    &D1VSPDAXL1,
                    UINT_16_TYPE,
                    65534,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 142 */
/* MVB - D1VSPDAXL2 */
          {
                    &D1VSPDAXL2,
                    UINT_16_TYPE,
                    65534,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 143 */
/* MVB - D1VSPDAXL3 */
          {
                    &D1VSPDAXL3,
                    UINT_16_TYPE,
                    65534,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 144 */
/* MVB - D1VSPDAXL4 */
          {
                    &D1VSPDAXL4,
                    UINT_16_TYPE,
                    65534,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 145 */
/* MVB - D1VSTAWORD1 */
          {
                    &D1VSTAWORD1,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 146 */
/* MVB - D1VWDCNTR01 */
          {
                    &D1VWDCNTR01,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 147 */
/* MVB - D1VWDCNTR02 */
          {
                    &D1VWDCNTR02,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 148 */
/* MVB - D1VWDCNTR03 */
          {
                    &D1VWDCNTR03,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 149 */
/* MVB - D1VWDCNTR04 */
          {
                    &D1VWDCNTR04,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 150 */
/* MVB - D2VSPDAXL1 */
          {
                    &D2VSPDAXL1,
                    UINT_16_TYPE,
                    65534,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 151 */
/* MVB - D2VSPDAXL2 */
          {
                    &D2VSPDAXL2,
                    UINT_16_TYPE,
                    65534,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 152 */
/* MVB - D2VSPDAXL3 */
          {
                    &D2VSPDAXL3,
                    UINT_16_TYPE,
                    65534,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 153 */
/* MVB - D2VSPDAXL4 */
          {
                    &D2VSPDAXL4,
                    UINT_16_TYPE,
                    65534,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 154 */
/* MVB - D2VSTAWORD1 */
          {
                    &D2VSTAWORD1,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 155 */
/* MVB - D2VWDCNTR01 */
          {
                    &D2VWDCNTR01,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 156 */
/* MVB - D2VWDCNTR02 */
          {
                    &D2VWDCNTR02,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 157 */
/* MVB - D2VWDCNTR04 */
          {
                    &D2VWDCNTR04,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 158 */
/* Vel - Axle 1 Wheel Diameter */
          {
                    &u16[VelAxle1WheelDiameter],
                    UINT_16_TYPE,
                    71500,                        63400,
                    PTUD_READONLY
          },
/*  Variable Number 159 */
/* Vel - Axle 2 Wheel Diameter */
          {
                    &u16[VelAxle2WheelDiameter],
                    UINT_16_TYPE,
                    71500,                        63400,
                    PTUD_READONLY
          },
/*  Variable Number 160 */
/* Vel - Axle 3 Wheel Diameter */
          {
                    &u16[VelAxle3WheelDiameter],
                    UINT_16_TYPE,
                    71500,                        63400,
                    PTUD_READONLY
          },
/*  Variable Number 161 */
/* Vel - Axle 4 Wheel Diameter */
          {
                    &u16[VelAxle4WheelDiameter],
                    UINT_16_TYPE,
                    71500,                        63400,
                    PTUD_READONLY
          },
/*  Variable Number 162 */
/* Vel - Axle 1 Rate */
          {
                    &i32[VelAxle1Rate],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 163 */
/* Vel - Axle 2 Rate */
          {
                    &i32[VelAxle2Rate],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 164 */
/* Vel - Axle 3 Rate */
          {
                    &i32[VelAxle3Rate],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 165 */
/* Vel - Axle 4 Rate */
          {
                    &i32[VelAxle4Rate],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 166 */
/* Vel - Truck 1 Rate Calc High */
          {
                    &u16[VelTruck1RateCalcHi],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 167 */
/* Vel - Truck 1 Rate Calc Low */
          {
                    &u16[VelTruck1RateCalcLo],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 168 */
/* Vel - Truck 1 Rate */
          {
                    &i32[VelTruck1Rate],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 169 */
/* Vel - Truck 2 Rate */
          {
                    &i32[VelTruck2Rate],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 170 */
/* Vel - Truck 2 Rate Calc High */
          {
                    &u16[VelTruck2RateCalcHi],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 171 */
/* Vel - Truck 2 Rate Calc Low */
          {
                    &u16[VelTruck2RateCalcLo],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 172 */
/* Vel - Car Rate */
          {
                    &i32[VelCarRate],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 173 */
/* Vel - Car Rate Calc Low */
          {
                    &u16[VelCarRateCalcLo],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 174 */
/* Vel - Car Rate Calc High */
          {
                    &u16[VelCarRateCalcHi],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 175 */
/* Dir - Rollback */
          {
                    &u16[DIRRBPROPINHIBIT],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 176 */
/* Dir - Trk1 Dir MismatchPropInhib */
          {
                    &u16[DIRMMPROPINHIBIT1],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 177 */
/* Dir - Trk1 Dir Req Prop Inhibit */
          {
                    &u16[DIRREQPROPINHIBIT1],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 178 */
/* Dir - Trk1 Direction Command */
          {
                    &u16[DIRCOMMAND1],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 179 */
/* Dir - Trk1 Direction Feedback */
          {
                    &u16[DIRFEEDBACK1],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 180 */
/* Dir - Trk1 Direction Request */
          {
                    &u16[DIRREQUEST1],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 181 */
/* Dir - Trk2 Dir MismatchPropInhib */
          {
                    &u16[DIRMMPROPINHIBIT2],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 182 */
/* Dir - Trk2 Dir Req Prop Inhibit */
          {
                    &u16[DIRREQPROPINHIBIT2],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 183 */
/* Dir - Trk2 Direction Command */
          {
                    &u16[DIRCOMMAND2],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 184 */
/* Dir - Trk2 Direction Feedback */
          {
                    &u16[DIRFEEDBACK2],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 185 */
/* Dir - Trk2 Direction Request */
          {
                    &u16[DIRREQUEST2],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 186 */
/* Dir - Trk1 Dir Req Charge Req */
          {
                    &u16[DIRREQCHARGE1],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 187 */
/* Dir - Trk2 Dir Req Charge Req */
          {
                    &u16[DIRREQCHARGE2],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 188 */
/* Prot - Car Type */
          {
                    &u16[PROTCARTYPE],
                    UINT_16_TYPE,
                    4,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 189 */
/* Prot - Car Type Valid */
          {
                    &u16[PROTCARVALID],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 190 */
/* Prot - Counter */
          {
                    &u16[PROTCOUNTER],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 191 */
/* Prot - Monitor Enable */
          {
                    &u16[PROTMONDISABLE],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 192 */
/* Prot - Lockout Reset */
          {
                    &u16[PROTLOCKOUTRESET],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 193 */
/* Prot - Good Beh P/B - A Car */
          {
                    &u16[PROTGOODBEHCOUNT],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 194 */
/* Prot - Good Beh P/B - B Car */
          {
                    &u16[PROTGOODBEHCOUNTB],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 195 */
/* Prot - HVB DC Thresh #1 */
          {
                    &i32[HVBDCTHRSH1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 196 */
/* Prot - HVB DC Thresh #2 */
          {
                    &i32[HVBDCTHRSH2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 197 */
/* Prot - HVB DC Timer #1 */
          {
                    &u32[HVBDCTMR1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 198 */
/* Prot - HVB DC Timer #2 */
          {
                    &u32[HVBDCTMR2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 199 */
/* Prot - HVB Grnd Flt Limit #1 */
          {
                    &u16[HVBGFL1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 200 */
/* Prot - HVB Grnd Flt Limit #2 */
          {
                    &u16[HVBGFL2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 201 */
/* Prot - HVB Grnd Flt Count #1 */
          {
                    &u32[HVBGFC1],
                    UINT_32_TYPE,
                    20,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 202 */
/* Prot - HVB Grnd Flt Count #2 */
          {
                    &u32[HVBGFC2],
                    UINT_32_TYPE,
                    20,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 203 */
/* Prot - Line Overcurrent Count #1 */
          {
                    &u32[PROTLOCCOUNT1],
                    UINT_32_TYPE,
                    20,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 204 */
/* Prot - Line Overcurrent Limit #1 */
          {
                    &u16[PROTLOCLIMIT1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 205 */
/* Prot - LC Overcurrent Thresh #1 */
          {
                    &i32[PROTLOCTHRES1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 206 */
/* Prot - LC Overcurrent Timer #1 */
          {
                    &u32[PROTLOCTIMER1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 207 */
/* Prot - Line Overcurrent Count #2 */
          {
                    &u32[PROTLOCCOUNT2],
                    UINT_32_TYPE,
                    20,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 208 */
/* Prot - Line Overcurrent Limit #2 */
          {
                    &u16[PROTLOCLIMIT2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 209 */
/* Prot - LC Overcurrent Thresh #2 */
          {
                    &i32[PROTLOCTHRES2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 210 */
/* Prot - LC Overcurrent Timer #2 */
          {
                    &u32[PROTLOCTIMER2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 211 */
/* Prot - OLR Trip Count #1 */
          {
                    &u32[PROTOLRCOUNT1],
                    UINT_32_TYPE,
                    20,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 212 */
/* Prot - OLR Trip Status #1 */
          {
                    &u16[PROTOLRSTAT1],
                    UINT_16_TYPE,
                    20,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 213 */
/* Prot - OLR Trip Count #2 */
          {
                    &u32[PROTOLRCOUNT2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 214 */
/* Prot - OLR Trip Status #2 */
          {
                    &u16[PROTOLRSTAT2],
                    UINT_16_TYPE,
                    20,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 215 */
/* Prot - OLR Reset Fault Count #1 */
          {
                    &u32[PROTOLRRESCOUNT1],
                    UINT_32_TYPE,
                    20,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 216 */
/* Prot - OLR Reset Fault Count #2 */
          {
                    &u32[PROTOLRRESCOUNT2],
                    UINT_32_TYPE,
                    20,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 217 */
/* IP PCN Input 1 */
          {
                    &PCNINPUT1,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 218 */
/* IP PCN Input 2 */
          {
                    &PCNINPUT2,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 219 */
/* IP PCN Input 3 */
          {
                    &PCNINPUT3,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 220 */
/* IP PCN Input 5 */
          {
                    &PCNINPUT5,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 221 */
/* IP PCN Input 6 */
          {
                    &PCNINPUT6,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 222 */
/* IP PCN Input 7 */
          {
                    &PCNINPUT7,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 223 */
/* IP PCN Input 9 */
          {
                    &PCNINPUT9,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 224 */
/* IP PTU Override */
          {
                    &u16[ipPtuOverride],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 225 */
/* Tc - Input Counter */
          {
                    &u16[TcCounter],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 226 */
/* Tc - Oper Rate Req */
          {
                    &i32[TcOperRateReq],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 227 */
/* Tc - Oper Mode Req */
          {
                    &u16[TcOperModeReq],
                    UINT_16_TYPE,
                    10,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 228 */
/* Tc - Tc Mode */
          {
                    &u16[TcTcMode],
                    UINT_16_TYPE,
                    10,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 229 */
/* Tc - Max Brake Rate */
          {
                    &i16[TcMaxBrkRate],
                    INT_16_TYPE,
                    30000,                        -30000,
                    PTUD_PSSWD2
          },
/*  Variable Number 230 */
/* Tc - Min Brake Rate */
          {
                    &i16[TcMinBrkRate],
                    INT_16_TYPE,
                    30000,                        -30000,
                    PTUD_PSSWD2
          },
/*  Variable Number 231 */
/* Tc - Min Power Rate */
          {
                    &i16[TcMinPwrRate],
                    INT_16_TYPE,
                    30000,                        -30000,
                    PTUD_PSSWD2
          },
/*  Variable Number 232 */
/* Tc - Max Power Rate */
          {
                    &i16[TcMaxPwrRate],
                    INT_16_TYPE,
                    30000,                        -30000,
                    PTUD_PSSWD2
          },
/*  Variable Number 233 */
/* Tc - Max Speed Limit Target 1 */
          {
                    &u32[TcMaxSpeedLimitTarget1],
                    UINT_32_TYPE,
                    100000,                       0,
                    PTUD_PSSWD2
          },
/*  Variable Number 234 */
/* Tc - Max Speed Limit Target 2 */
          {
                    &u32[TcMaxSpeedLimitTarget2],
                    UINT_32_TYPE,
                    100000,                       0,
                    PTUD_PSSWD2
          },
/*  Variable Number 235 */
/* Inv - DCU#1 Command */
          {
                    &u16[DCU1REQCOMMAND],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 236 */
/* Inv - DCU#1 Control Word */
          {
                    &u32[DCU1EXTCOND],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 237 */
/* Inv - DCU#1 Reset Isolation */
          {
                    &u16[DCU1RESETISOL],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 238 */
/* Inv - DCU#2 Command */
          {
                    &u16[DCU2REQCOMMAND],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 239 */
/* Inv - DCU#2 Reset Isolation */
          {
                    &u16[DCU2RESETISOL],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 240 */
/* MVB - D1VSTAWORD2 */
          {
                    &D1VSTAWORD2,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 241 */
/* MVB - D2VSTAWORD2 */
          {
                    &D2VSTAWORD2,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 242 */
/* MVB - D1VDCUSTATE */
          {
                    &D1VDCUSTATE,
                    UINT_16_TYPE,
                    60,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 243 */
/* MVB - D2VDCUSTATE */
          {
                    &D2VDCUSTATE,
                    UINT_16_TYPE,
                    60,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 244 */
/* Mot - Counter */
          {
                    &u16[MotCounter],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 245 */
/* Mot - Mode Trk 1 */
          {
                    &u16[MotMotionModeTrk1],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 246 */
/* Mot - Mode Trk 2 */
          {
                    &u16[MotMotionModeTrk2],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 247 */
/* Mot - Prop TE Req Trk 1 */
          {
                    &i32[MotPropTEReqTrk1],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 248 */
/* Mot - Prop TE Req Trk 2 */
          {
                    &i32[MotPropTEReqTrk2],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 249 */
/* Mot - FB TE Req Trk 1 */
          {
                    &i32[MotFBTEReqTrk1],
                    INT_32_TYPE,
                    0,                            -50000,
                    PTUD_READONLY
          },
/*  Variable Number 250 */
/* Mot - FB TE Req Trk 2 */
          {
                    &i32[MotFBTEReqTrk2],
                    INT_32_TYPE,
                    0,                            -50000,
                    PTUD_READONLY
          },
/*  Variable Number 251 */
/* MVB - VD1TREFTREQ */
          {
                    &VD1TREFTREQ,
                    INT_16_TYPE,
                    10000,                        -10000,
                    PTUD_PSSWD2
          },
/*  Variable Number 252 */
/* MVB - VD2TREFTREQ */
          {
                    &VD2TREFTREQ,
                    INT_16_TYPE,
                    10000,                        -10000,
                    PTUD_PSSWD2
          },
/*  Variable Number 253 */
/* MVB - D1VTREFTDEL */
          {
                    &D1VTREFTDEL,
                    INT_16_TYPE,
                    10000,                        -10000,
                    PTUD_PSSWD2
          },
/*  Variable Number 254 */
/* MVB - D2VTREFTDEL */
          {
                    &D2VTREFTDEL,
                    INT_16_TYPE,
                    10000,                        -10000,
                    PTUD_PSSWD2
          },
/*  Variable Number 255 */
/* Mot - Load Weigh Trk 1 */
          {
                    &u32[MotLoadWeighTrk1],
                    UINT_32_TYPE,
                    40000,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 256 */
/* Mot - Load Weigh Trk 2 */
          {
                    &u32[MotLoadWeighTrk2],
                    UINT_32_TYPE,
                    40000,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 257 */
/* MS - Local MSStatus */
          {
                    &u16[MYTOKEN],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 258 */
/* MS - Local Vcu_Id */
          {
                    &u16[MVBADDRESS],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 259 */
/* MS - Local Watchdog */
          {
                    &u16[LOCAL_WD],
                    UINT_16_TYPE,
                    65534,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 260 */
/* MS - Prev Remote MS Status */
          {
                    &u16[PREVREMOTEVCU_MSSTATUS],
                    UINT_16_TYPE,
                    4,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 261 */
/* MS - Dead Count Max */
          {
                    &u16[REDDEADCOUNTER],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 262 */
/* MS - Remote MSStatus */
          {
                    &u16[REMOTEVCU_MSSTATUS],
                    UINT_16_TYPE,
                    4,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 263 */
/* MS - Remote Vcu_Id */
          {
                    &u16[REMOTEMVBADDRESS],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 264 */
/* MS - Remote WatchDog */
          {
                    &u16[REMOTEVCU_WD],
                    UINT_16_TYPE,
                    65534,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 265 */
/* MS - Swap Master Slave */
          {
                    &u16[STARTRED],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 266 */
/* FB - Friction Brake Cmd Trk1 */
          {
                    &i32[MOTFBCOM1],
                    INT_32_TYPE,
                    2000,                         0,
                    PTUD_READONLY
          },
/*  Variable Number 267 */
/* FB - Friction Brake Cmd Trk2 */
          {
                    &i32[MOTFBCOM2],
                    INT_32_TYPE,
                    2000,                         0,
                    PTUD_READONLY
          },
/*  Variable Number 268 */
/* FB - Trk1 In Shot Pressure #1 */
          {
                    &i32[MOTT1ISP1],
                    INT_32_TYPE,
                    8000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 269 */
/* FB - In Shot Speed */
          {
                    &u32[MOTISS],
                    UINT_32_TYPE,
                    50000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 270 */
/* FB - Trk1 In Shot Time */
          {
                    &u16[MOTT1IST],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 271 */
/* FB - Trk1 In Shot Pressure #2 */
          {
                    &i32[MOTT1ISP2],
                    INT_32_TYPE,
                    8000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 272 */
/* FB - Trk2 In Shot Pressure #1 */
          {
                    &i32[MOTT2ISP1],
                    INT_32_TYPE,
                    8000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 273 */
/* FB - Trk2 In Shot Pressure #2 */
          {
                    &i32[MOTT2ISP2],
                    INT_32_TYPE,
                    8000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 274 */
/* FB - Trk2 In Shot Time */
          {
                    &u16[MOTT2IST],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 275 */
/* Inv - DCU#2 Control Word */
          {
                    &u32[DCU2EXTCOND],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 276 */
/* Prot - Fault Enumeration - DCU1 */
          {
                    &u32[PROTFLTENUMB],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 277 */
/* Prot - Fault Enumeration - DCU2 */
          {
                    &u32[PROTFLTENUM],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 278 */
/* Prot - PCULockoutStatus DCU1 */
          {
                    &u16[PROTPCULockoutDCU1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 279 */
/* Prot - PCULockoutStatus DCU2 */
          {
                    &u16[PROTPCULockoutDCU2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 280 */
/* Mot - System Jerk Limit */
          {
                    &i32[MotSystemJRL],
                    INT_32_TYPE,
                    20000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 281 */
/* Mot - Dyn Brk Cutout Trk 1 */
          {
                    &u16[MotPtuDbCutout],
                    UINT_16_TYPE,
                    10,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 282 */
/* Mot - Dyn Brk Cutout Trk 2 */
          {
                    &u16[MotPtuDbCutout2],
                    UINT_16_TYPE,
                    10,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 283 */
/* Mot - High Perf Enable */
          {
                    &u16[MotPtuHighPerfEnable],
                    UINT_16_TYPE,
                    10,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 284 */
/* Mot - RBP Brk Pres Lmt T1 */
          {
                    &u32[MotRBPBrakePressureLimit],
                    UINT_32_TYPE,
                    200,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 285 */
/* Mot - RBP Brk Pres Lmt T2 */
          {
                    &u32[MotRBPBrakePressureLimit2],
                    UINT_32_TYPE,
                    200,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 286 */
/* Mot - RBP Timer Limit Trk 1 */
          {
                    &u32[MotRBPTimerLimit],
                    UINT_32_TYPE,
                    60000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 287 */
/* Mot - RBP Timer Limit Trk 2 */
          {
                    &u32[MotRBPTimerLimit2],
                    UINT_32_TYPE,
                    60000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 288 */
/* MVB - D1VBRKRTEMP */
          {
                    &D1VBRKRTEMP,
                    UINT_16_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 289 */
/* MVB - D2VBRKRTEMP */
          {
                    &D2VBRKRTEMP,
                    UINT_16_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 290 */
/* Inp - Inv #1 Brk Resistor Temp. */
          {
                    &i32[DCU1DBRTEMP],
                    INT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 291 */
/* Inp - Inv #2 Brk Resistor Temp. */
          {
                    &i32[DCU2DBRTEMP],
                    INT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 292 */
/* Dir - Dir Cmd to Truck #1 */
          {
                    &u16[DIRCOMTRK1],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 293 */
/* Dir - Dir Cmd to Truck #2 */
          {
                    &u16[DIRCOMTRK2],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 294 */
/* Dir - Rollback Speed Threshold */
          {
                    &i32[RBSPEEDTHRESH],
                    INT_32_TYPE,
                    5000,                         -5000,
                    PTUD_PSSWD2
          },
/*  Variable Number 295 */
/* Dir - Rollback Time Threshold */
          {
                    &u32[RBTIMETHRESH],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 296 */
/* Mot - Car Weight */
          {
                    &u32[MotCarWeight],
                    UINT_32_TYPE,
                    60000,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 297 */
/* Prot - Car Regen Cut-Out Enable */
          {
                    &u16[PROTREGENENABLE],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 298 */
/* Prot - OverSpeed Fwd-Alarm */
          {
                    &i32[PROTFWDSPDLIMLO],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 299 */
/* Prot - OverSpeed Fwd-Emergency */
          {
                    &i32[PROTFWDSPDLIMHI],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 300 */
/* Prot - OverSpeed Rev-Emergency */
          {
                    &i32[PROTREVSPDLIMHI],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 301 */
/* Prot - OverSpeed Rev-Alarm */
          {
                    &i32[PROTREVSPDLIMLO],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 302 */
/* FB - Exp BCP in Emergency #1 */
          {
                    &i32[FBTRK1EXPEBRAKE],
                    INT_32_TYPE,
                    100,                          0,
                    PTUD_READONLY
          },
/*  Variable Number 303 */
/* FB - Exp BCP in Emergency #2 */
          {
                    &i32[FBTRK2EXPEBRAKE],
                    INT_32_TYPE,
                    100,                          0,
                    PTUD_READONLY
          },
/*  Variable Number 304 */
/* FB - Main Air Reservoir Fault */
          {
                    &u16[FBMARF],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 305 */
/* FB - Park Brk Apply Command */
          {
                    &u16[FBPBAPPLYCOM],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 306 */
/* FB - Park Brk Command */
          {
                    &u16[FBPBCOMMAND],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 307 */
/* FB - Park Brk Release Command */
          {
                    &u16[FBPBRELCOM],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 308 */
/* FB - Trk1 Snow Brake Pressure #1 */
          {
                    &i32[FBSBPRES1],
                    INT_32_TYPE,
                    1000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 309 */
/* FB - Trk1 Snow Brake Pressure #2 */
          {
                    &i32[FBSBPRES2],
                    INT_32_TYPE,
                    1000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 310 */
/* FB - Trk1 Snow Brake Time */
          {
                    &u16[FBSBTIME],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 311 */
/* FB - Trk1 Cutout Status */
          {
                    &u16[FBTRK1CUTOUT],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 312 */
/* FB - Trk1 Dragging */
          {
                    &u16[FBTRK1DRAGGING],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 313 */
/* FB - Trk1 Load Limiting Valve */
          {
                    &u16[FBTRK1LLV],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 314 */
/* FB - Trk1 Slide Control Status */
          {
                    &u16[FBTRK1SLIDE],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 315 */
/* FB - Trk2 Cutout Status */
          {
                    &u16[FBTRK2CUTOUT],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 316 */
/* FB - Trk2 Dragging */
          {
                    &u16[FBTRK2DRAGGING],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 317 */
/* FB - Trk2 Load Limiting Valve */
          {
                    &u16[FBTRK2LLV],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 318 */
/* FB - Trk2 Slide Control Status */
          {
                    &u16[FBTRK2SLIDE],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 319 */
/* Inp - Close Chg Ctr DCU1 Com */
          {
                    &i32[DCU1CCCCOM],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 320 */
/* Inp - Close Sep Ctr DCU1 Com */
          {
                    &i32[DCU1CSCCOM],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 321 */
/* Inp - Close Chg Ctr DCU2 Com */
          {
                    &i32[DCU2CCCCOM],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 322 */
/* Inp - Close Sep Ctr DCU2 Com */
          {
                    &i32[DCU2CSCCOM],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 323 */
/* Inp - Chg Ctr DCU1 Status */
          {
                    &i32[DCU1CCSTAT],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 324 */
/* Inp - Sep Ctr DCU1 Status */
          {
                    &i32[DCU1SCSTAT],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 325 */
/* Inp - Chg Ctr DCU2 Status */
          {
                    &i32[DCU2CCSTAT],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 326 */
/* Inp - Sep Ctr DCU2 Status */
          {
                    &i32[DCU2SCSTAT],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 327 */
/* Inp - DCU1 Tractive Effort Del. */
          {
                    &i32[DCU1TEDEL],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 328 */
/* Inp - DCU2 Tractive Effort Del. */
          {
                    &i32[DCU2TEDEL],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 329 */
/* Inp - Link Voltage #1 */
          {
                    &i32[DCU1LINKVOL],
                    INT_32_TYPE,
                    10000,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 330 */
/* Inp - Link Voltage #2 */
          {
                    &i32[DCU2LINKVOL],
                    INT_32_TYPE,
                    10000,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 331 */
/* Inp - Link Current #1 */
          {
                    &i32[DCU1LINKCUR],
                    INT_32_TYPE,
                    10000,                        -10000,
                    PTUD_READONLY
          },
/*  Variable Number 332 */
/* Inp - Link Current #2 */
          {
                    &i32[DCU2LINKCUR],
                    INT_32_TYPE,
                    10000,                        -10000,
                    PTUD_READONLY
          },
/*  Variable Number 333 */
/* Inp - Link Power #1 */
          {
                    &i32[DCU1LINKPWR],
                    INT_32_TYPE,
                    200000000,                    0,
                    PTUD_READONLY
          },
/*  Variable Number 334 */
/* Inp - Link Power #2 */
          {
                    &i32[DCU2LINKPWR],
                    INT_32_TYPE,
                    200000000,                    0,
                    PTUD_READONLY
          },
/*  Variable Number 335 */
/* Inp - Chopper Power #1 */
          {
                    &i32[DCU1CPPWR],
                    INT_32_TYPE,
                    200000000,                    0,
                    PTUD_READONLY
          },
/*  Variable Number 336 */
/* Inp - Chopper Power #2 */
          {
                    &i32[DCU2CPPWR],
                    INT_32_TYPE,
                    200000000,                    0,
                    PTUD_READONLY
          },
/*  Variable Number 337 */
/* Inp - Motor Power #1 */
          {
                    &i32[DCU1MOTPWR],
                    INT_32_TYPE,
                    200000000,                    0,
                    PTUD_READONLY
          },
/*  Variable Number 338 */
/* Inp - Motor Power #2 */
          {
                    &i32[DCU2MOTPWR],
                    INT_32_TYPE,
                    200000000,                    0,
                    PTUD_READONLY
          },
/*  Variable Number 339 */
/* Inp - Mot. Conv. Air Temp. #1 */
          {
                    &i32[DCU1AIRTEMP],
                    INT_32_TYPE,
                    25000,                        -5000,
                    PTUD_READONLY
          },
/*  Variable Number 340 */
/* Inp - Mot. Conv. Air Temp. #2 */
          {
                    &i32[DCU2AIRTEMP],
                    INT_32_TYPE,
                    25000,                        -5000,
                    PTUD_READONLY
          },
/*  Variable Number 341 */
/* Inp - Conv. Heatsink Temp. #1 */
          {
                    &i32[DCU1HSTEMP],
                    INT_32_TYPE,
                    25000,                        -5000,
                    PTUD_READONLY
          },
/*  Variable Number 342 */
/* Inp - Conv. Heatsink Temp. #2 */
          {
                    &i32[DCU2HSTEMP],
                    INT_32_TYPE,
                    25000,                        -5000,
                    PTUD_READONLY
          },
/*  Variable Number 343 */
/* Inp - DCU1 Motor #1 Temp. */
          {
                    &i32[DCU1MOT1TEMP],
                    INT_32_TYPE,
                    50000,                        -5000,
                    PTUD_READONLY
          },
/*  Variable Number 344 */
/* Inp - DCU1 Motor #2 Temp. */
          {
                    &i32[DCU1MOT2TEMP],
                    INT_32_TYPE,
                    50000,                        -5000,
                    PTUD_READONLY
          },
/*  Variable Number 345 */
/* Inp - DCU2 Motor #1 Temp. */
          {
                    &i32[DCU2MOT1TEMP],
                    INT_32_TYPE,
                    50000,                        -5000,
                    PTUD_READONLY
          },
/*  Variable Number 346 */
/* Inp - DCU2 Motor #2 Temp. */
          {
                    &i32[DCU2MOT2TEMP],
                    INT_32_TYPE,
                    50000,                        -5000,
                    PTUD_READONLY
          },
/*  Variable Number 347 */
/* Inp - Charging Resistor Temp. #1 */
          {
                    &i32[DCU1CHGRTEMP],
                    INT_32_TYPE,
                    150000,                       -5000,
                    PTUD_READONLY
          },
/*  Variable Number 348 */
/* Inp - Charging Resistor Temp. #2 */
          {
                    &i32[DCU2CHGRTEMP],
                    INT_32_TYPE,
                    150000,                       -5000,
                    PTUD_READONLY
          },
/*  Variable Number 349 */
/* Inp - Traction Safe Enable #1 */
          {
                    &i32[DCU1TSENABLE],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 350 */
/* Inp - Traction Safe Enable #2 */
          {
                    &i32[DCU2TSENABLE],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 351 */
/* Inp - Earth Fault Detected #1 */
          {
                    &i32[DCU1EARTHFLT],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 352 */
/* Inp - Earth Fault Detected #2 */
          {
                    &i32[DCU2EARTHFLT],
                    INT_32_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 353 */
/* Inp - Mot. Stator Cur. (RMS) #1 */
          {
                    &i32[DCU1RMSCUR],
                    INT_32_TYPE,
                    10000,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 354 */
/* Inp - Mot. Stator Cur. (RMS) #2 */
          {
                    &i32[DCU2RMSCUR],
                    INT_32_TYPE,
                    10000,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 355 */
/* Slide: EB Detect Async Thresh */
          {
                    &i32[slideAsyncEmerBrakeThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 356 */
/* Slide: EB Detect Sync Thresh */
          {
                    &i32[slideSyncEmerBrakeThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 357 */
/* Slide: EB Detect Velocity Thresh */
          {
                    &u32[slideVelocityEmerBrakeThresh],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 358 */
/* Slide: EB Drop Rate Percentage */
          {
                    &u16[slideEbDropPercent],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 359 */
/* Slide: EB JerkRate - Knee1 */
          {
                    &u16[slideEBJRKnee1],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 360 */
/* Slide: EB JerkRate - Knee2 */
          {
                    &u16[slideEBJRKnee2],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 361 */
/* Slide: EB JerkRate - Knee3 */
          {
                    &u16[slideEBJRKnee3],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 362 */
/* Slide: EB JerkRate - Knee4 */
          {
                    &u16[slideEBJRKnee4],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 363 */
/* Slide: EB JerkRate - Knee5 */
          {
                    &u16[slideEBJRKnee5],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 364 */
/* Slide: EB JRLimitScale - Knee1 */
          {
                    &u16[slideEBJRLPercentKnee1],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 365 */
/* Slide: EB JRLimitScale - Knee2 */
          {
                    &u16[slideEBJRLPercentKnee2],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 366 */
/* Slide: EB JRLimitScale - Knee3 */
          {
                    &u16[slideEBJRLPercentKnee3],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 367 */
/* Slide: EB JRLimitScale - Knee4 */
          {
                    &u16[slideEBJRLPercentKnee4],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 368 */
/* Slide: EB JRLimitScale - Knee5 */
          {
                    &u16[slideEBJRLPercentKnee5],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 369 */
/* Slide: EB Readhere Async Thresh */
          {
                    &i32[slideEBReadhereAsyncThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 370 */
/* Slide: EB Readhere Sync Thresh */
          {
                    &i32[slideEBReadhereSyncThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 371 */
/* Slide: EB Readhere Vel Thresh */
          {
                    &i32[slideEBReadhereVelocityThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 372 */
/* Slide: EmerBrake Slide Control */
          {
                    &u8[slideDetectEmerBrakeEn],
                    UINT_8_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 373 */
/* Slide: EB Initial Drop Percentage */
          {
                    &u16[slideEbInitDropPercent],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 374 */
/* Slide: SB Initial Drop Percentage */
          {
                    &u16[slideSbInitDropPercent],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 375 */
/* Slide: SB Detect Async Thresh */
          {
                    &i32[slideAsyncServiceThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 376 */
/* Slide: SB Detect Sync Thresh */
          {
                    &i32[slideSyncServiceThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 377 */
/* Slide: SB Detect Velocity Thresh */
          {
                    &u32[slideVelocityServiceThresh],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 378 */
/* Slide: SB Drop Rate Percentage */
          {
                    &u16[slideSbDropPercent],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 379 */
/* Slide: SB JerkRate - Knee1 */
          {
                    &u16[slideSBJRKnee1],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 380 */
/* Slide: SB JerkRate - Knee2 */
          {
                    &u16[slideSBJRKnee2],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 381 */
/* Slide: SB JerkRate - Knee3 */
          {
                    &u16[slideSBJRKnee3],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 382 */
/* Slide: SB JerkRate - Knee4 */
          {
                    &u16[slideSBJRKnee4],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 383 */
/* Slide: SB JerkRate - Knee5 */
          {
                    &u16[slideSBJRKnee5],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 384 */
/* Slide: SB JRLimitScale - Knee1 */
          {
                    &u16[slideSBJRLPercentKnee1],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 385 */
/* Slide: SB JRLimitScale - Knee2 */
          {
                    &u16[slideSBJRLPercentKnee2],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 386 */
/* Slide: SB JRLimitScale - Knee3 */
          {
                    &u16[slideSBJRLPercentKnee3],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 387 */
/* Slide: SB JRLimitScale - Knee4 */
          {
                    &u16[slideSBJRLPercentKnee4],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 388 */
/* Slide: SB JRLimitScale - Knee5 */
          {
                    &u16[slideSBJRLPercentKnee5],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 389 */
/* Slide: SB Readhere Async Thresh */
          {
                    &i32[slideSBReadhereAsyncThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 390 */
/* Slide: SB Readhere Sync Thresh */
          {
                    &i32[slideSBReadhereSyncThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 391 */
/* Slide: SB Readhere Vel Thresh */
          {
                    &i32[slideSBReadhereVelocityThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 392 */
/* Slide: Timeout Mode */
          {
                    &u16[slideTimeoutEnabled],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 393 */
/* Slide: Timeout Timer */
          {
                    &u32[slideTimeoutTimer],
                    UINT_32_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 394 */
/* Spin: Detect Async Thresh */
          {
                    &i32[spinDetAsyncThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 395 */
/* Spin: Detect Sync Thresh */
          {
                    &i32[spinDetSyncThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 396 */
/* Spin: Detect Velocity Thresh */
          {
                    &i32[spinDetVelocityThresh],
                    INT_32_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 397 */
/* Spin: Drop Rate percentage */
          {
                    &u16[spinReadhere],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 398 */
/* Spin: Initial Drop Rate percentage */
          {
                    &u16[spinReadhereInit],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 399 */
/* Spin: JerkRate - Knee1 */
          {
                    &u16[spinJRKnee1],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 400 */
/* Spin: JerkRate - Knee2 */
          {
                    &u16[spinJRKnee2],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 401 */
/* Spin: JerkRate - Knee3 */
          {
                    &u16[spinJRKnee3],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 402 */
/* Spin: JerkRateLimitScale - Knee1 */
          {
                    &u16[spinJRLPercentKnee1],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 403 */
/* Spin: JerkRateLimitScale - Knee2 */
          {
                    &u16[spinJRLPercentKnee2],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 404 */
/* Spin: JerkRateLimitScale - Knee3 */
          {
                    &u16[spinJRLPercentKnee3],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 405 */
/* Spin: Readhere Async Thresh */
          {
                    &i32[spinAsyncReadhereThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 406 */
/* Spin: Readhere Sync Thresh */
          {
                    &i32[spinSyncReadhereThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 407 */
/* Spin: Readhere Velocity Thresh */
          {
                    &i32[spinVelocityReadhereThresh],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 408 */
/* SS: Counter */
          {
                    &u16[ssSchedCounter],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 409 */
/* SS: Input Axle1 Rate */
          {
                    &i32[ssInAxle1Rate],
                    INT_32_TYPE,
                    3000,                         -3000,
                    PTUD_READONLY
          },
/*  Variable Number 410 */
/* SS: Input Axle1 Speed */
          {
                    &i32[ssInAxle1Speed],
                    INT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 411 */
/* SS: Input Axle2 Rate */
          {
                    &i32[ssInAxle2Rate],
                    INT_32_TYPE,
                    3000,                         -3000,
                    PTUD_READONLY
          },
/*  Variable Number 412 */
/* SS: Input Axle2 Speed */
          {
                    &i32[ssInAxle2Speed],
                    INT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 413 */
/* SS: Input Axle3 Rate */
          {
                    &i32[ssInAxle3Rate],
                    INT_32_TYPE,
                    3000,                         -3000,
                    PTUD_READONLY
          },
/*  Variable Number 414 */
/* SS: Input Axle3 Speed */
          {
                    &i32[ssInAxle3Speed],
                    INT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 415 */
/* SS: Input Axle4 Rate */
          {
                    &i32[ssInAxle4Rate],
                    INT_32_TYPE,
                    3000,                         -3000,
                    PTUD_READONLY
          },
/*  Variable Number 416 */
/* SS: Input Axle4 Speed */
          {
                    &i32[ssInAxle4Speed],
                    INT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 417 */
/* SS: Input Car Rate */
          {
                    &i32[ssInCarRate],
                    INT_32_TYPE,
                    3000,                         -3000,
                    PTUD_READONLY
          },
/*  Variable Number 418 */
/* SS: Input Car Speed */
          {
                    &u32[ssInCarSpeed],
                    UINT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 419 */
/* SS: Input Motion1 Rate Req */
          {
                    &i32[ssInMot1RateReq],
                    INT_32_TYPE,
                    3000,                         -3000,
                    PTUD_READONLY
          },
/*  Variable Number 420 */
/* SS: Input Motion2 Rate Req */
          {
                    &i32[ssInMot2RateReq],
                    INT_32_TYPE,
                    3000,                         -3000,
                    PTUD_READONLY
          },
/*  Variable Number 421 */
/* SS: Input Operator Rate Req */
          {
                    &i32[ssInOperRateReq],
                    INT_32_TYPE,
                    3000,                         -3000,
                    PTUD_READONLY
          },
/*  Variable Number 422 */
/* Spin1: Active */
          {
                    &u16[spin1Active],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 423 */
/* Spin1: Enabled ID */
          {
                    &u16[spin1IsEnabledId],
                    UINT_16_TYPE,
                    15,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 424 */
/* Spin1: Correction Stage */
          {
                    &u16[spin1CorrectionStage],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 425 */
/* Spin1: Master State */
          {
                    &u16[spin1MasterState],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 426 */
/* Spin1: In Progress ID */
          {
                    &u16[spin1InProgressId],
                    UINT_16_TYPE,
                    15,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 427 */
/* Spin2: Active */
          {
                    &u16[spin2Active],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 428 */
/* Spin2: Correction Stage */
          {
                    &u16[spin2CorrectionStage],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 429 */
/* Spin2: Enabled ID */
          {
                    &u16[spin2IsEnabledId],
                    UINT_16_TYPE,
                    15,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 430 */
/* Spin2: In Progress ID */
          {
                    &u16[spin2InProgressId],
                    UINT_16_TYPE,
                    15,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 431 */
/* Spin2: Master State */
          {
                    &u16[spin2MasterState],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 432 */
/* Slide1: Active */
          {
                    &u16[slide1Active],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 433 */
/* Slide1: All Wheels Sliding */
          {
                    &u8[slide1AllWheels],
                    UINT_8_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 434 */
/* Slide1: Enabled ID */
          {
                    &u16[slide1IsEnabledId],
                    UINT_16_TYPE,
                    15,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 435 */
/* Slide1: In Progress ID */
          {
                    &u16[slide1InProgressId],
                    UINT_16_TYPE,
                    15,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 436 */
/* Slide1: Master State */
          {
                    &u16[slide1MasterState],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 437 */
/* Slide2: Active */
          {
                    &u16[slide2Active],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 438 */
/* Slide2: All Wheels Sliding */
          {
                    &u8[slide2AllWheels],
                    UINT_8_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 439 */
/* Slide2: Enabled ID */
          {
                    &u16[slide2IsEnabledId],
                    UINT_16_TYPE,
                    15,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 440 */
/* Slide2: In Progress ID */
          {
                    &u16[slide2InProgressId],
                    UINT_16_TYPE,
                    15,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 441 */
/* Slide2: Master State */
          {
                    &u16[slide2MasterState],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 442 */
/* Slide1: Correction Stage */
          {
                    &u16[slide1CorrectionStage],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 443 */
/* Slide2: Correction Stage */
          {
                    &u16[slide2CorrectionStage],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 444 */
/* SS1: Output Jerk Rate Limit */
          {
                    &i32[ssOutRateJerkLimit1],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 445 */
/* SS1: Output Non Jerk Rate Limit */
          {
                    &i32[ssOutRateNonJerkLimit1],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 446 */
/* SS1: Output Rate Limit */
          {
                    &i32[ssOutRateLimit1],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 447 */
/* SS2: Output Jerk Rate Limit */
          {
                    &i32[ssOutRateJerkLimit2],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 448 */
/* SS2: Output Non Jerk Rate Limit */
          {
                    &i32[ssOutRateNonJerkLimit2],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 449 */
/* SS2: Output Rate Limit */
          {
                    &i32[ssOutRateLimit2],
                    INT_32_TYPE,
                    20000,                        -20000,
                    PTUD_READONLY
          },
/*  Variable Number 450 */
/* Spin: Timeout Mode */
          {
                    &u16[spinTimeoutEnabled],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 451 */
/* Spin: Timeout Timer */
          {
                    &u32[spinTimeoutTimer],
                    UINT_32_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 452 */
/* Slide: Low Speed Disable */
          {
                    &u32[slideSpeedThresh],
                    UINT_32_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 453 */
/* Spin: Low Speed Disable */
          {
                    &u32[spinSpeedThresh],
                    UINT_32_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 454 */
/* SS2: Mode State */
          {
                    &u16[ssModeState2],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 455 */
/* SS2: Slide Processing */
          {
                    &u16[ssEnableSlide2],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 456 */
/* SS2: Spin Processing */
          {
                    &u16[ssEnableSpin2],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 457 */
/* SS1: Mode State */
          {
                    &u16[ssModeState1],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 458 */
/* SS1: Slide Processing */
          {
                    &u16[ssEnableSlide1],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 459 */
/* SS1: Spin Processing */
          {
                    &u16[ssEnableSpin1],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 460 */
/* Tc - Turtle Mode */
          {
                    &u16[TCTURTLEMODE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 461 */
/* Prot - Brake Rate Speed Thresh */
          {
                    &i32[PROTBRKRATESPD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 462 */
/* Prot - Brake Rate Fault */
          {
                    &u16[PROTBRKRATE],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 463 */
/* MVB - VD1CTLWORD1 */
          {
                    &VD1CTLWORD1,
                    INT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 464 */
/* MVB - VD2CTLWORD1 */
          {
                    &VD2CTLWORD1,
                    INT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 465 */
/* MVB - VD1VLINEVOL */
          {
                    &VD1VLINEVOL,
                    INT_16_TYPE,
                    32766,                        -32767,
                    PTUD_READONLY
          },
/*  Variable Number 466 */
/* MVB - VD2VLINEVOL */
          {
                    &VD2VLINEVOL,
                    INT_16_TYPE,
                    1200,                         0,
                    PTUD_READONLY
          },
/*  Variable Number 467 */
/* Prot - TM #1 Counter */
          {
                    &u32[PROTTM1COUNTER],
                    UINT_32_TYPE,
                    429496700,                    0,
                    PTUD_PSSWD2
          },
/*  Variable Number 468 */
/* Prot - TM #2 Counter */
          {
                    &u32[PROTTM2COUNTER],
                    UINT_32_TYPE,
                    429496700,                    0,
                    PTUD_PSSWD2
          },
/*  Variable Number 469 */
/* Prot - TM #3 Counter */
          {
                    &u32[PROTTM3COUNTER],
                    UINT_32_TYPE,
                    429496700,                    0,
                    PTUD_PSSWD2
          },
/*  Variable Number 470 */
/* Prot - TM #4 Counter */
          {
                    &u32[PROTTM4COUNTER],
                    UINT_32_TYPE,
                    429496700,                    0,
                    PTUD_PSSWD2
          },
/*  Variable Number 471 */
/* Prot - GU #1 Counter */
          {
                    &u32[PROTGU1COUNTER],
                    UINT_32_TYPE,
                    429496700,                    0,
                    PTUD_PSSWD2
          },
/*  Variable Number 472 */
/* Prot - GU #2 Counter */
          {
                    &u32[PROTGU2COUNTER],
                    UINT_32_TYPE,
                    429496700,                    0,
                    PTUD_PSSWD2
          },
/*  Variable Number 473 */
/* Prot - GU #3 Counter */
          {
                    &u32[PROTGU3COUNTER],
                    UINT_32_TYPE,
                    429496700,                    0,
                    PTUD_PSSWD2
          },
/*  Variable Number 474 */
/* Prot - GU #4 Counter */
          {
                    &u32[PROTGU4COUNTER],
                    UINT_32_TYPE,
                    429496700,                    0,
                    PTUD_PSSWD2
          },
/*  Variable Number 475 */
/* FB - Trk2 Snow Brake Pressure #1 */
          {
                    &i32[FBT2SBPRES1],
                    INT_32_TYPE,
                    1000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 476 */
/* FB - Trk2 Snow Brake Pressure #2 */
          {
                    &i32[FBT2SBPRES2],
                    INT_32_TYPE,
                    1000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 477 */
/* FB - Trk2 Snow Brake Time */
          {
                    &u16[FBT2SBTIME],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 478 */
/* Prot - DCU1 Diagnostic Word 1 */
          {
                    &i32[DCU1DIAGWRD1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 479 */
/* Prot - DCU1 Diagnostic Word 10 */
          {
                    &i32[DCU1DIAGWRD10],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 480 */
/* Prot - DCU1 Diagnostic Word 13 */
          {
                    &i32[DCU1DIAGWRD13],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 481 */
/* Prot - DCU1 Diagnostic Word 2 */
          {
                    &i32[DCU1DIAGWRD2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 482 */
/* Prot - DCU1 Diagnostic Word 3 */
          {
                    &i32[DCU1DIAGWRD3],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 483 */
/* Prot - DCU1 Diagnostic Word 4 */
          {
                    &i32[DCU1DIAGWRD4],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 484 */
/* Prot - DCU1 Diagnostic Word 5 */
          {
                    &i32[DCU1DIAGWRD5],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 485 */
/* Prot - DCU1 Diagnostic Word 6 */
          {
                    &i32[DCU1DIAGWRD6],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 486 */
/* Prot - DCU1 Diagnostic Word 9 */
          {
                    &i32[DCU1DIAGWRD9],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 487 */
/* Prot - DCU2 Diagnostic Word 1 */
          {
                    &i32[DCU2DIAGWRD1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 488 */
/* Prot - DCU2 Diagnostic Word 13 */
          {
                    &i32[DCU2DIAGWRD13],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 489 */
/* Prot - DCU2 Diagnostic Word 2 */
          {
                    &i32[DCU2DIAGWRD2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 490 */
/* Prot - DCU2 Diagnostic Word 3 */
          {
                    &i32[DCU2DIAGWRD3],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 491 */
/* Prot - DCU2 Diagnostic Word 4 */
          {
                    &i32[DCU2DIAGWRD4],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 492 */
/* Prot - DCU2 Diagnostic Word 6 */
          {
                    &i32[DCU2DIAGWRD6],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 493 */
/* Prot - DCU2 Diagnostic Word 9 */
          {
                    &i32[DCU2DIAGWRD9],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 494 */
/* Prot - DCU2 Diagnostic Word 10 */
          {
                    &i32[DCU2DIAGWRD10],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 495 */
/* Slide1: BVD State */
          {
                    &u16[slide1BVDState],
                    UINT_16_TYPE,
                    7,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 496 */
/* Slide1: BVD Knee */
          {
                    &u16[slide1BVDKnee],
                    UINT_16_TYPE,
                    4,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 497 */
/* Slide2: BVD Knee */
          {
                    &u16[slide2BVDKnee],
                    UINT_16_TYPE,
                    4,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 498 */
/* Slide1: BVD Enabled */
          {
                    &u8[slide1BVDEnabled],
                    UINT_8_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 499 */
/* Slide2: BVD Enabled */
          {
                    &u8[slide2BVDEnabled],
                    UINT_8_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 500 */
/* Slide: BVD HoldTime1 */
          {
                    &u16[slideBVDHoldTime1],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 501 */
/* Slide: BVD HoldTime2 */
          {
                    &u16[slideBVDHoldTime2],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 502 */
/* Slide: BVD HoldTime3 */
          {
                    &u16[slideBVDHoldTime3],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 503 */
/* Slide: BVD HoldTime4 */
          {
                    &u16[slideBVDHoldTime4],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 504 */
/* Slide: BVD HoldTime5 */
          {
                    &u16[slideBVDHoldTime5],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 505 */
/* Slide: BVD ApplyTime1 */
          {
                    &u16[slideBVDApplyTime1],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 506 */
/* Slide: BVD ApplyTime2 */
          {
                    &u16[slideBVDApplyTime2],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 507 */
/* Slide: BVD ApplyTime3 */
          {
                    &u16[slideBVDApplyTime3],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 508 */
/* Slide: BVD ApplyTime4 */
          {
                    &u16[slideBVDApplyTime4],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 509 */
/* Slide: BVD ApplyTime5 */
          {
                    &u16[slideBVDApplyTime5],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 510 */
/* SS: Car State */
          {
                    &u16[ssCarState],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 511 */
/* SS: Output All Wheel Slide */
          {
                    &u16[ssAllWheelSlide],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 512 */
/* Prot - DCU2 Diagnostic Word 5 */
          {
                    &i32[DCU2DIAGWRD5],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 513 */
/* Slide2: BVD State */
          {
                    &u16[slide2BVDState],
                    UINT_16_TYPE,
                    7,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 514 */
/* Prot - POR Command */
          {
                    &u16[PROTPORCOMMAND],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 515 */
/* Prot - OLR1 Command */
          {
                    &u16[OLR1COMMAND],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 516 */
/* Prot - OLR2 Command */
          {
                    &u16[OLR2COMMAND],
                    UINT_16_TYPE,
                    5,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 517 */
/* MVB - D2VWDCNTR03 */
          {
                    &D2VWDCNTR03,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 518 */
/* Prot - DCU 1 Isolation Code */
          {
                    &i32[DCU1ISOLATIONCODE],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 519 */
/* Prot - DCU 2 Isolation Code */
          {
                    &i32[DCU2ISOLATIONCODE],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 520 */
/* Slide1: Friction Brake */
          {
                    &u8[slideFBApplied1],
                    UINT_8_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 521 */
/* Slide2: Friction Brake */
          {
                    &u8[slideFBApplied2],
                    UINT_8_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 522 */
/* IP PCN Input 20 */
          {
                    &PCNINPUT20,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 523 */
/* IP PCN Input 21 */
          {
                    &PCNINPUT21,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 524 */
/* IP PCN Input 24 */
          {
                    &PCNINPUT24,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 525 */
/* IP PCN Input 23 */
          {
                    &PCNINPUT23,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 526 */
/* IP PCN Input 22 */
          {
                    &PCNINPUT22,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 527 */
/* IP PCN Input 25 */
          {
                    &PCNINPUT25,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 528 */
/* IP PCN Input 26 */
          {
                    &PCNINPUT26,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 529 */
/* IP PCN Input 27 */
          {
                    &PCNINPUT27,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 530 */
/* IP PCN Input 28 */
          {
                    &PCNINPUT28,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 531 */
/* IP PCN Input 29 */
          {
                    &PCNINPUT29,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 532 */
/* PCNOUTPUT1 */
          {
                    &PCNOUTPUT1,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 533 */
/* Prot - HV Input Mile Ctr Lmt Tk2 */
          {
                    &u16[PROTLVNRGMILE2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 534 */
/* NM - Car A */
          {
                    &u16[zeroVelCarA],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 535 */
/* NM - Car Speed */
          {
                    &u32[zeroVelCarSpeed],
                    UINT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 536 */
/* NM - CarState */
          {
                    &u16[zeroVelCarState],
                    UINT_16_TYPE,
                    3,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 537 */
/* NM - Ch1 RelayCmd */
          {
                    &u16[zeroVelCh1RelayCmd],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 538 */
/* NM - Ch1 Status */
          {
                    &u16[zeroVelCh1Status],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 539 */
/* NM - Ch2 Status */
          {
                    &u16[zeroVelCh2Status],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 540 */
/* NM - FaultId */
          {
                    &u16[zeroVelFaultId],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 541 */
/* NM - ManagerState */
          {
                    &u16[zeroVelManagerState],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 542 */
/* NM - Speed Threshold */
          {
                    &u16[zeroVelThresh],
                    UINT_16_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 543 */
/* NM - Zero Spd In Fault */
          {
                    &u16[zeroVelZeroSpdWhileFaulted],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 544 */
/* St - Life Sign */
          {
                    &u16[ST_LIFESIGN],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 545 */
/* St - Self Test In Progress */
          {
                    &u16[STSTATE],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 546 */
/* St - Self Test Reset */
          {
                    &u16[STRESET],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 547 */
/* St - Phase Commutation Timeout */
          {
                    &u32[STCOMTESTTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 548 */
/* St - Inverter Charge Timeout */
          {
                    &u32[STCHGTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 549 */
/* St - IGBT Test Timeout */
          {
                    &u32[STIGBTTESTTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 550 */
/* St - Phase Load Test Timeout */
          {
                    &u32[STLDTESTTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 551 */
/* St - Inverter Operation Timeout */
          {
                    &u32[STOPERTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 552 */
/* St - OVP Test Timeout */
          {
                    &u32[STOVPTESTTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 553 */
/* St - Passive Disch Test Timeout */
          {
                    &u32[STPDCHGTESTTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 554 */
/* St - Test Mode Response Timeout */
          {
                    &u32[STTESTMODETIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 555 */
/* St - Test Number Resp. Timeout */
          {
                    &u32[STTESTNOTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 556 */
/* IP PCN Input 16 */
          {
                    &PCNINPUT16,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 557 */
/* IP PCN Input 160 */
          {
                    &PCNINPUT160,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 558 */
/* IP PCN Input 161 */
          {
                    &PCNINPUT161,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 559 */
/* IP PCN Input 162 */
          {
                    &PCNINPUT162,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 560 */
/* IP PCN Input 163 */
          {
                    &PCNINPUT163,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 561 */
/* IP PCN Input 164 */
          {
                    &PCNINPUT164,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 562 */
/* IP PCN Input 165 */
          {
                    &PCNINPUT165,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 563 */
/* IP PCN Input 166 */
          {
                    &PCNINPUT166,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 564 */
/* IP PCN Input 167 */
          {
                    &PCNINPUT167,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 565 */
/* IP PCN Input 17 */
          {
                    &PCNINPUT17,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 566 */
/* IP PCN Input 18 */
          {
                    &PCNINPUT18,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 567 */
/* IP PCN Input 180 */
          {
                    &PCNINPUT180,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 568 */
/* IP PCN Input 181 */
          {
                    &PCNINPUT181,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 569 */
/* IP PCN Input 182 */
          {
                    &PCNINPUT182,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 570 */
/* IP PCN Input 183 */
          {
                    &PCNINPUT183,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 571 */
/* IP PCN Input 184 */
          {
                    &PCNINPUT184,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 572 */
/* IP PCN Input 19 */
          {
                    &PCNINPUT19,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 573 */
/* IP PCN Input 200 */
          {
                    &PCNINPUT200,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 574 */
/* IP PCN Input 30 */
          {
                    &PCNINPUT30,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 575 */
/* IP PCN Input 31 */
          {
                    &PCNINPUT31,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 576 */
/* IP PCN Input 32 */
          {
                    &PCNINPUT32,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 577 */
/* IP PCN Input 33 */
          {
                    &PCNINPUT33,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 578 */
/* IP PCN Input 34 */
          {
                    &PCNINPUT34,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 579 */
/* IP PCN Input 35 */
          {
                    &PCNINPUT35,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 580 */
/* IP PCN Input 36 */
          {
                    &PCNINPUT36,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 581 */
/* IP PCN Input 37 */
          {
                    &PCNINPUT37,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 582 */
/* PCNOUTPUT10 */
          {
                    &PCNOUTPUT10,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 583 */
/* PCNOUTPUT100 */
          {
                    &PCNOUTPUT100,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 584 */
/* PCNOUTPUT101 */
          {
                    &PCNOUTPUT101,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 585 */
/* PCNOUTPUT102 */
          {
                    &PCNOUTPUT102,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 586 */
/* PCNOUTPUT103 */
          {
                    &PCNOUTPUT103,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 587 */
/* PCNOUTPUT104 */
          {
                    &PCNOUTPUT104,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 588 */
/* PCNOUTPUT105 */
          {
                    &PCNOUTPUT105,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 589 */
/* PCNOUTPUT106 */
          {
                    &PCNOUTPUT106,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 590 */
/* PCNOUTPUT107 */
          {
                    &PCNOUTPUT107,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 591 */
/* PCNOUTPUT108 */
          {
                    &PCNOUTPUT108,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 592 */
/* PCNOUTPUT109 */
          {
                    &PCNOUTPUT109,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 593 */
/* PCNOUTPUT11 */
          {
                    &PCNOUTPUT11,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 594 */
/* PCNOUTPUT110 */
          {
                    &PCNOUTPUT110,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 595 */
/* PCNOUTPUT111 */
          {
                    &PCNOUTPUT111,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 596 */
/* PCNOUTPUT112 */
          {
                    &PCNOUTPUT112,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 597 */
/* PCNOUTPUT113 */
          {
                    &PCNOUTPUT113,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 598 */
/* PCNOUTPUT114 */
          {
                    &PCNOUTPUT114,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 599 */
/* PCNOUTPUT115 */
          {
                    &PCNOUTPUT115,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 600 */
/* PCNOUTPUT116 */
          {
                    &PCNOUTPUT116,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 601 */
/* PCNOUTPUT117 */
          {
                    &PCNOUTPUT117,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 602 */
/* PCNOUTPUT118 */
          {
                    &PCNOUTPUT118,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 603 */
/* PCNOUTPUT119 */
          {
                    &PCNOUTPUT119,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 604 */
/* PCNOUTPUT12 */
          {
                    &PCNOUTPUT12,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 605 */
/* PCNOUTPUT13 */
          {
                    &PCNOUTPUT13,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 606 */
/* PCNOUTPUT14 */
          {
                    &PCNOUTPUT14,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 607 */
/* PCNOUTPUT140 */
          {
                    &PCNOUTPUT140,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 608 */
/* PCNOUTPUT141 */
          {
                    &PCNOUTPUT141,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 609 */
/* PCNOUTPUT142 */
          {
                    &PCNOUTPUT142,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 610 */
/* PCNOUTPUT143 */
          {
                    &PCNOUTPUT143,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 611 */
/* PCNOUTPUT144 */
          {
                    &PCNOUTPUT144,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 612 */
/* PCNOUTPUT145 */
          {
                    &PCNOUTPUT145,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 613 */
/* PCNOUTPUT146 */
          {
                    &PCNOUTPUT146,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 614 */
/* PCNOUTPUT147 */
          {
                    &PCNOUTPUT147,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 615 */
/* PCNOUTPUT148 */
          {
                    &PCNOUTPUT148,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 616 */
/* PCNOUTPUT149 */
          {
                    &PCNOUTPUT149,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 617 */
/* PCNOUTPUT15 */
          {
                    &PCNOUTPUT15,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 618 */
/* PCNOUTPUT150 */
          {
                    &PCNOUTPUT150,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 619 */
/* PCNOUTPUT16 */
          {
                    &PCNOUTPUT16,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 620 */
/* PCNOUTPUT160 */
          {
                    &PCNOUTPUT160,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 621 */
/* PCNOUTPUT161 */
          {
                    &PCNOUTPUT161,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 622 */
/* PCNOUTPUT17 */
          {
                    &PCNOUTPUT17,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 623 */
/* PCNOUTPUT170 */
          {
                    &PCNOUTPUT170,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 624 */
/* PCNOUTPUT180 */
          {
                    &PCNOUTPUT180,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 625 */
/* PCNOUTPUT181 */
          {
                    &PCNOUTPUT181,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 626 */
/* PCNOUTPUT182 */
          {
                    &PCNOUTPUT182,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 627 */
/* PCNOUTPUT183 */
          {
                    &PCNOUTPUT183,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 628 */
/* PCNOUTPUT184 */
          {
                    &PCNOUTPUT184,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 629 */
/* PCNOUTPUT185 */
          {
                    &PCNOUTPUT185,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 630 */
/* PCNOUTPUT186 */
          {
                    &PCNOUTPUT186,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 631 */
/* PCNOUTPUT187 */
          {
                    &PCNOUTPUT187,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 632 */
/* PCNOUTPUT188 */
          {
                    &PCNOUTPUT188,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 633 */
/* PCNOUTPUT189 */
          {
                    &PCNOUTPUT189,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 634 */
/* PCNOUTPUT19 */
          {
                    &PCNOUTPUT19,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 635 */
/* PCNOUTPUT190 */
          {
                    &PCNOUTPUT190,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 636 */
/* PCNOUTPUT191 */
          {
                    &PCNOUTPUT191,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 637 */
/* PCNOUTPUT192 */
          {
                    &PCNOUTPUT192,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 638 */
/* PCNOUTPUT193 */
          {
                    &PCNOUTPUT193,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 639 */
/* PCNOUTPUT194 */
          {
                    &PCNOUTPUT194,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 640 */
/* PCNOUTPUT2 */
          {
                    &PCNOUTPUT2,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 641 */
/* PCNOUTPUT20 */
          {
                    &PCNOUTPUT20,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 642 */
/* PCNOUTPUT200 */
          {
                    &PCNOUTPUT200,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 643 */
/* PCNOUTPUT21 */
          {
                    &PCNOUTPUT21,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 644 */
/* PCNOUTPUT23 */
          {
                    &PCNOUTPUT23,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 645 */
/* PCNOUTPUT24 */
          {
                    &PCNOUTPUT24,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 646 */
/* PCNOUTPUT28 */
          {
                    &PCNOUTPUT28,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 647 */
/* PCNOUTPUT29 */
          {
                    &PCNOUTPUT29,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 648 */
/* PCNOUTPUT3 */
          {
                    &PCNOUTPUT3,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 649 */
/* PCNOUTPUT30 */
          {
                    &PCNOUTPUT30,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 650 */
/* PCNOUTPUT31 */
          {
                    &PCNOUTPUT31,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 651 */
/* PCNOUTPUT32 */
          {
                    &PCNOUTPUT32,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 652 */
/* PCNOUTPUT33 */
          {
                    &PCNOUTPUT33,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 653 */
/* PCNOUTPUT34 */
          {
                    &PCNOUTPUT34,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 654 */
/* PCNOUTPUT35 */
          {
                    &PCNOUTPUT35,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 655 */
/* PCNOUTPUT36 */
          {
                    &PCNOUTPUT36,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 656 */
/* PCNOUTPUT37 */
          {
                    &PCNOUTPUT37,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 657 */
/* PCNOUTPUT38 */
          {
                    &PCNOUTPUT38,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 658 */
/* PCNOUTPUT39 */
          {
                    &PCNOUTPUT39,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 659 */
/* PCNOUTPUT4 */
          {
                    &PCNOUTPUT4,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 660 */
/* PCNOUTPUT40 */
          {
                    &PCNOUTPUT40,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 661 */
/* PCNOUTPUT41 */
          {
                    &PCNOUTPUT41,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 662 */
/* PCNOUTPUT42 */
          {
                    &PCNOUTPUT42,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 663 */
/* PCNOUTPUT43 */
          {
                    &PCNOUTPUT43,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 664 */
/* PCNOUTPUT44 */
          {
                    &PCNOUTPUT44,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 665 */
/* PCNOUTPUT45 */
          {
                    &PCNOUTPUT45,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 666 */
/* PCNOUTPUT46 */
          {
                    &PCNOUTPUT46,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 667 */
/* PCNOUTPUT47 */
          {
                    &PCNOUTPUT47,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 668 */
/* PCNOUTPUT48 */
          {
                    &PCNOUTPUT48,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 669 */
/* PCNOUTPUT49 */
          {
                    &PCNOUTPUT49,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 670 */
/* PCNOUTPUT5 */
          {
                    &PCNOUTPUT5,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 671 */
/* PCNOUTPUT51 */
          {
                    &PCNOUTPUT51,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 672 */
/* PCNOUTPUT52 */
          {
                    &PCNOUTPUT52,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 673 */
/* PCNOUTPUT53 */
          {
                    &PCNOUTPUT53,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 674 */
/* PCNOUTPUT54 */
          {
                    &PCNOUTPUT54,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 675 */
/* PCNOUTPUT55 */
          {
                    &PCNOUTPUT55,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 676 */
/* PCNOUTPUT56 */
          {
                    &PCNOUTPUT56,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 677 */
/* PCNOUTPUT57 */
          {
                    &PCNOUTPUT57,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 678 */
/* PCNOUTPUT58 */
          {
                    &PCNOUTPUT58,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 679 */
/* PCNOUTPUT59 */
          {
                    &PCNOUTPUT59,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 680 */
/* PCNOUTPUT6 */
          {
                    &PCNOUTPUT6,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 681 */
/* PCNOUTPUT60 */
          {
                    &PCNOUTPUT60,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 682 */
/* PCNOUTPUT61 */
          {
                    &PCNOUTPUT61,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 683 */
/* PCNOUTPUT62 */
          {
                    &PCNOUTPUT62,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 684 */
/* PCNOUTPUT63 */
          {
                    &PCNOUTPUT63,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 685 */
/* PCNOUTPUT64 */
          {
                    &PCNOUTPUT64,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 686 */
/* PCNOUTPUT65 */
          {
                    &PCNOUTPUT65,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 687 */
/* PCNOUTPUT66 */
          {
                    &PCNOUTPUT66,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 688 */
/* PCNOUTPUT67 */
          {
                    &PCNOUTPUT67,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 689 */
/* PCNOUTPUT68 */
          {
                    &PCNOUTPUT68,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 690 */
/* PCNOUTPUT69 */
          {
                    &PCNOUTPUT69,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 691 */
/* PCNOUTPUT7 */
          {
                    &PCNOUTPUT7,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 692 */
/* PCNOUTPUT70 */
          {
                    &PCNOUTPUT70,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 693 */
/* PCNOUTPUT71 */
          {
                    &PCNOUTPUT71,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 694 */
/* PCNOUTPUT72 */
          {
                    &PCNOUTPUT72,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 695 */
/* PCNOUTPUT73 */
          {
                    &PCNOUTPUT73,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 696 */
/* PCNOUTPUT8 */
          {
                    &PCNOUTPUT8,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 697 */
/* PCNOUTPUT9 */
          {
                    &PCNOUTPUT9,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 698 */
/* Mot - Trk 1 Load Weigh Var 1 */
          {
                    &i32[PROTT1LWVAR1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 699 */
/* Mot - Trk 1 Load Weigh Var 2 */
          {
                    &i32[PROTT1LWVAR2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 700 */
/* Mot - Trk 2 Load Weigh Var 1 */
          {
                    &i32[PROTT2LWVAR1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 701 */
/* Mot - Trk 2 Load Weigh Var 2 */
          {
                    &i32[PROTT2LWVAR2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 702 */
/* FB - Overall Parking Brk Status */
          {
                    &u16[PBOVERALLSTATUS],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 703 */
/* Prot - Propulsion Status DCU1 */
          {
                    &u16[PROPSTATUSB],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 704 */
/* FB - Trk1 Overall FB Status */
          {
                    &u16[FBTRK1OVERALLSTATUS],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 705 */
/* FB - Trk2 Overall FB Status */
          {
                    &u16[FBTRK2OVERALLSTATUS],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 706 */
/* Prot - Propulsion Status DCU2 */
          {
                    &u16[PROPSTATUS],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 707 */
/* Mot - Snow Brake Status */
          {
                    &u16[SNOWBRAKESTATUS],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 708 */
/* FB - FB Pressure Scale */
          {
                    &i32[MOTFBSCALE],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 709 */
/* Mot - DB Fade Speed */
          {
                    &i32[MotDbFadeSpeed],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 710 */
/* St - Wheel Slide Test Info */
          {
                    &u32[STPDTINFO],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 711 */
/* St - Wheel Slide Test Status */
          {
                    &u16[STPDTFLAG],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 712 */
/* St - Wheel Slide Tests Failed */
          {
                    &u32[STPDTFAILED],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 713 */
/* Inp - Startup Test Complete */
          {
                    &i32[VCUSUTCOM],
                    INT_32_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 714 */
/* St - PB Psi Test Timing */
          {
                    &u16[STPBTIME],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 715 */
/* St - Trk1 K1 K2 K3 Timing */
          {
                    &u32[STK123TIMET1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 716 */
/* St - Trk1 K4 Timing */
          {
                    &u32[STK4TIMET1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 717 */
/* St - Trk2 K1 K2 K3 Timing */
          {
                    &u32[STK123TIMET2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 718 */
/* St - Trk2 K4 Timing */
          {
                    &u32[STK4TIMET2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 719 */
/* Dir - Trk1 Neutral Stop Op Time */
          {
                    &u32[DCT1NTRLSTOPOP],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 720 */
/* Dir - Trk2 Neutral Stop Op Time */
          {
                    &u32[DCT2NTRLSTOPOP],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 721 */
/* Dir - Trk1 Neutral Discharge Time */
          {
                    &u32[DCT1NTRLDSCHRG],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 722 */
/* Dir - Trk2 Neutral Disch Time */
          {
                    &u32[DCT2NTRLDSCHRG],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 723 */
/* FB - LLV Scale Factor */
          {
                    &i32[FBLLVVAR1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 724 */
/* NM - Ch2 Fault Counter */
          {
                    &u16[ch2faultcounter],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 725 */
/* NM - Ch2 Fault Count Limit */
          {
                    &u16[ch2faultcountlimit],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 726 */
/* St - BVC Trk1 BVD Apply Time */
          {
                    &u32[STAPPLYTIMET1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 727 */
/* St - BVC Trk1 BVD Dump Time */
          {
                    &u32[STDUMPTIMET1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 728 */
/* St - BVC Trk1 FB Apply Time */
          {
                    &u32[STFBAPPLYTIMET1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 729 */
/* St - BVC Trk1 BVD Apply PSI */
          {
                    &i32[STAPPLYPSIT1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 730 */
/* St - BVC Trk1 FB Command PSI */
          {
                    &i32[STCOMMANDPSIT1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 731 */
/* St - BVC Trk1 BVD Hold PSI */
          {
                    &i32[STHOLDPSIT1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 732 */
/* St - BVC Trk1 FB Range PSI */
          {
                    &i32[STRANGEPSIT1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 733 */
/* St - BVC Trk1 MR PSI */
          {
                    &i32[STMRPSIT1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 734 */
/* St - BVC Trk2 BVD Apply Time */
          {
                    &u32[STAPPLYTIMET2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 735 */
/* St - BVC Trk2 BVD Dump Time */
          {
                    &u32[STDUMPTIMET2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 736 */
/* St - BVC Trk2 FB Apply Time */
          {
                    &u32[STFBAPPLYTIMET2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 737 */
/* St - BVC Trk2 BVD Apply PSI */
          {
                    &i32[STAPPLYPSIT2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 738 */
/* St - BVC Trk2 FB Command PSI */
          {
                    &i32[STCOMMANDPSIT2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 739 */
/* St - BVC Trk2 BVD Hold PSI */
          {
                    &i32[STHOLDPSIT2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 740 */
/* St - BVC Trk2 FB Range PSI */
          {
                    &i32[STRANGEPSIT2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 741 */
/* St - BVC Trk2 MR PSI */
          {
                    &i32[STMRPSIT2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 742 */
/* Vel - Axle Ref RPM */
          {
                    &i32[VelAxleRefRaw],
                    INT_32_TYPE,
                    5000000,                      -5000000,
                    PTUD_READONLY
          },
/*  Variable Number 743 */
/* Vel - TIMS Ref Wheel Diam */
          {
                    &u16[VelAxleRefWheelDiameter],
                    UINT_16_TYPE,
                    75000,                        60000,
                    PTUD_READONLY
          },
/*  Variable Number 744 */
/* Vel - Car Position */
          {
                    &u16[VelCarPosition],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 745 */
/* Vel - Reference Wheel Diameter */
          {
                    &u16[VelRefWheelDiameter],
                    UINT_16_TYPE,
                    7144018.28803658,             6350012.7000254,
                    PTUD_PSSWD2
          },
/*  Variable Number 746 */
/* IP PCN Input 300 */
          {
                    &PCNINPUT300,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 747 */
/* IP PCN Input 301 */
          {
                    &PCNINPUT301,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 748 */
/* IP PCN Input 302 */
          {
                    &PCNINPUT302,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 749 */
/* IP PCN Input 303 */
          {
                    &PCNINPUT303,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 750 */
/* IP PCN Input 304 */
          {
                    &PCNINPUT304,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 751 */
/* IP PCN Input 305 */
          {
                    &PCNINPUT305,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 752 */
/* IP PCN Input 306 */
          {
                    &PCNINPUT306,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 753 */
/* IP PCN Input 307 */
          {
                    &PCNINPUT307,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 754 */
/* IP PCN Input 308 */
          {
                    &PCNINPUT308,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 755 */
/* IP PCN Input 309 */
          {
                    &PCNINPUT309,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 756 */
/* IP PCN Input 310 */
          {
                    &PCNINPUT310,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 757 */
/* IP PCN Input 311 */
          {
                    &PCNINPUT311,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 758 */
/* IP PCN Input 312 */
          {
                    &PCNINPUT312,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 759 */
/* IP PCN Input 313 */
          {
                    &PCNINPUT313,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 760 */
/* IP PCN Input 314 */
          {
                    &PCNINPUT314,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 761 */
/* IP PCN Input 350 */
          {
                    &PCNINPUT350,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 762 */
/* IP PCN Input 351 */
          {
                    &PCNINPUT351,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 763 */
/* IP PCN Input 352 */
          {
                    &PCNINPUT352,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 764 */
/* IP PCN Input 353 */
          {
                    &PCNINPUT353,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 765 */
/* IP PCN Input 354 */
          {
                    &PCNINPUT354,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 766 */
/* IP PCN Input 355 */
          {
                    &PCNINPUT355,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 767 */
/* IP PCN Input 356 */
          {
                    &PCNINPUT356,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 768 */
/* IP PCN Input 357 */
          {
                    &PCNINPUT357,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 769 */
/* IP PCN Input 358 */
          {
                    &PCNINPUT358,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 770 */
/* IP PCN Input 359 */
          {
                    &PCNINPUT359,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 771 */
/* IP PCN Input 360 */
          {
                    &PCNINPUT360,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 772 */
/* IP PCN Input 361 */
          {
                    &PCNINPUT361,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 773 */
/* IP PCN Input 362 */
          {
                    &PCNINPUT362,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 774 */
/* IP PCN Input 363 */
          {
                    &PCNINPUT363,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 775 */
/* IP PCN Input 364 */
          {
                    &PCNINPUT364,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 776 */
/* IP PCN Input 400 */
          {
                    &PCNINPUT400,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 777 */
/* IP PCN Input 401 */
          {
                    &PCNINPUT401,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 778 */
/* IP PCN Input 402 */
          {
                    &PCNINPUT402,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 779 */
/* IP PCN Input 403 */
          {
                    &PCNINPUT403,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 780 */
/* IP PCN Input 404 */
          {
                    &PCNINPUT404,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 781 */
/* IP PCN Input 405 */
          {
                    &PCNINPUT405,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 782 */
/* IP PCN Input 406 */
          {
                    &PCNINPUT406,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 783 */
/* IP PCN Input 407 */
          {
                    &PCNINPUT407,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 784 */
/* IP PCN Input 408 */
          {
                    &PCNINPUT408,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 785 */
/* IP PCN Input 409 */
          {
                    &PCNINPUT409,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 786 */
/* IP PCN Input 410 */
          {
                    &PCNINPUT410,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 787 */
/* IP PCN Input 411 */
          {
                    &PCNINPUT411,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 788 */
/* IP PCN Input 412 */
          {
                    &PCNINPUT412,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 789 */
/* IP PCN Input 413 */
          {
                    &PCNINPUT413,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 790 */
/* IP PCN Input 414 */
          {
                    &PCNINPUT414,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 791 */
/* IP PCN Input 450 */
          {
                    &PCNINPUT450,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 792 */
/* IP PCN Input 451 */
          {
                    &PCNINPUT451,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 793 */
/* IP PCN Input 452 */
          {
                    &PCNINPUT452,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 794 */
/* IP PCN Input 453 */
          {
                    &PCNINPUT453,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 795 */
/* IP PCN Input 454 */
          {
                    &PCNINPUT454,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 796 */
/* IP PCN Input 455 */
          {
                    &PCNINPUT455,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 797 */
/* IP PCN Input 456 */
          {
                    &PCNINPUT456,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 798 */
/* IP PCN Input 457 */
          {
                    &PCNINPUT457,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 799 */
/* IP PCN Input 458 */
          {
                    &PCNINPUT458,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 800 */
/* IP PCN Input 459 */
          {
                    &PCNINPUT459,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 801 */
/* IP PCN Input 460 */
          {
                    &PCNINPUT460,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 802 */
/* IP PCN Input 461 */
          {
                    &PCNINPUT461,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 803 */
/* IP PCN Input 462 */
          {
                    &PCNINPUT462,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 804 */
/* IP PCN Input 463 */
          {
                    &PCNINPUT463,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 805 */
/* IP PCN Input 464 */
          {
                    &PCNINPUT464,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 806 */
/* IP PCN Input 500 */
          {
                    &PCNINPUT500,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 807 */
/* IP PCN Input 501 */
          {
                    &PCNINPUT501,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 808 */
/* IP PCN Input 502 */
          {
                    &PCNINPUT502,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 809 */
/* IP PCN Input 503 */
          {
                    &PCNINPUT503,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 810 */
/* IP PCN Input 504 */
          {
                    &PCNINPUT504,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 811 */
/* IP PCN Input 505 */
          {
                    &PCNINPUT505,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 812 */
/* IP PCN Input 506 */
          {
                    &PCNINPUT506,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 813 */
/* IP PCN Input 507 */
          {
                    &PCNINPUT507,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 814 */
/* IP PCN Input 508 */
          {
                    &PCNINPUT508,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 815 */
/* IP PCN Input 509 */
          {
                    &PCNINPUT509,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 816 */
/* IP PCN Input 510 */
          {
                    &PCNINPUT510,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 817 */
/* IP PCN Input 511 */
          {
                    &PCNINPUT511,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 818 */
/* IP PCN Input 512 */
          {
                    &PCNINPUT512,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 819 */
/* IP PCN Input 513 */
          {
                    &PCNINPUT513,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 820 */
/* IP PCN Input 514 */
          {
                    &PCNINPUT514,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 821 */
/* IP PCN Input 550 */
          {
                    &PCNINPUT550,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 822 */
/* IP PCN Input 551 */
          {
                    &PCNINPUT551,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 823 */
/* IP PCN Input 552 */
          {
                    &PCNINPUT552,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 824 */
/* IP PCN Input 553 */
          {
                    &PCNINPUT553,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 825 */
/* IP PCN Input 554 */
          {
                    &PCNINPUT554,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 826 */
/* IP PCN Input 555 */
          {
                    &PCNINPUT555,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 827 */
/* IP PCN Input 556 */
          {
                    &PCNINPUT556,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 828 */
/* IP PCN Input 557 */
          {
                    &PCNINPUT557,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 829 */
/* IP PCN Input 558 */
          {
                    &PCNINPUT558,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 830 */
/* IP PCN Input 559 */
          {
                    &PCNINPUT559,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 831 */
/* IP PCN Input 560 */
          {
                    &PCNINPUT560,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 832 */
/* IP PCN Input 561 */
          {
                    &PCNINPUT561,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 833 */
/* IP PCN Input 562 */
          {
                    &PCNINPUT562,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 834 */
/* IP PCN Input 563 */
          {
                    &PCNINPUT563,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 835 */
/* IP PCN Input 564 */
          {
                    &PCNINPUT564,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 836 */
/* IP PCN Input 600 */
          {
                    &PCNINPUT600,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 837 */
/* IP PCN Input 601 */
          {
                    &PCNINPUT601,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 838 */
/* IP PCN Input 602 */
          {
                    &PCNINPUT602,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 839 */
/* IP PCN Input 603 */
          {
                    &PCNINPUT603,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 840 */
/* IP PCN Input 604 */
          {
                    &PCNINPUT604,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 841 */
/* IP PCN Input 605 */
          {
                    &PCNINPUT605,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 842 */
/* IP PCN Input 606 */
          {
                    &PCNINPUT606,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 843 */
/* IP PCN Input 607 */
          {
                    &PCNINPUT607,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 844 */
/* IP PCN Input 608 */
          {
                    &PCNINPUT608,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 845 */
/* IP PCN Input 609 */
          {
                    &PCNINPUT609,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 846 */
/* IP PCN Input 610 */
          {
                    &PCNINPUT610,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 847 */
/* IP PCN Input 611 */
          {
                    &PCNINPUT611,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 848 */
/* IP PCN Input 612 */
          {
                    &PCNINPUT612,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 849 */
/* IP PCN Input 613 */
          {
                    &PCNINPUT613,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 850 */
/* IP PCN Input 614 */
          {
                    &PCNINPUT614,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 851 */
/* IP PCN Input 650 */
          {
                    &PCNINPUT650,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 852 */
/* IP PCN Input 651 */
          {
                    &PCNINPUT651,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 853 */
/* IP PCN Input 652 */
          {
                    &PCNINPUT652,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 854 */
/* IP PCN Input 653 */
          {
                    &PCNINPUT653,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 855 */
/* IP PCN Input 654 */
          {
                    &PCNINPUT654,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 856 */
/* IP PCN Input 655 */
          {
                    &PCNINPUT655,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 857 */
/* IP PCN Input 656 */
          {
                    &PCNINPUT656,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 858 */
/* IP PCN Input 657 */
          {
                    &PCNINPUT657,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 859 */
/* IP PCN Input 658 */
          {
                    &PCNINPUT658,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 860 */
/* IP PCN Input 659 */
          {
                    &PCNINPUT659,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 861 */
/* IP PCN Input 660 */
          {
                    &PCNINPUT660,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 862 */
/* IP PCN Input 661 */
          {
                    &PCNINPUT661,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 863 */
/* IP PCN Input 662 */
          {
                    &PCNINPUT662,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 864 */
/* IP PCN Input 663 */
          {
                    &PCNINPUT663,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 865 */
/* IP PCN Input 664 */
          {
                    &PCNINPUT664,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 866 */
/* IP PCN Input 700 */
          {
                    &PCNINPUT700,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 867 */
/* IP PCN Input 701 */
          {
                    &PCNINPUT701,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 868 */
/* IP PCN Input 702 */
          {
                    &PCNINPUT702,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 869 */
/* IP PCN Input 703 */
          {
                    &PCNINPUT703,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 870 */
/* IP PCN Input 704 */
          {
                    &PCNINPUT704,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 871 */
/* IP PCN Input 705 */
          {
                    &PCNINPUT705,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 872 */
/* IP PCN Input 706 */
          {
                    &PCNINPUT706,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 873 */
/* IP PCN Input 707 */
          {
                    &PCNINPUT707,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 874 */
/* IP PCN Input 708 */
          {
                    &PCNINPUT708,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 875 */
/* IP PCN Input 709 */
          {
                    &PCNINPUT709,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 876 */
/* IP PCN Input 710 */
          {
                    &PCNINPUT710,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 877 */
/* IP PCN Input 711 */
          {
                    &PCNINPUT711,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 878 */
/* IP PCN Input 712 */
          {
                    &PCNINPUT712,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 879 */
/* IP PCN Input 713 */
          {
                    &PCNINPUT713,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 880 */
/* IP PCN Input 714 */
          {
                    &PCNINPUT714,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 881 */
/* IP PCN Input 750 */
          {
                    &PCNINPUT750,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 882 */
/* IP PCN Input 751 */
          {
                    &PCNINPUT751,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 883 */
/* IP PCN Input 752 */
          {
                    &PCNINPUT752,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 884 */
/* IP PCN Input 753 */
          {
                    &PCNINPUT753,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 885 */
/* IP PCN Input 754 */
          {
                    &PCNINPUT754,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 886 */
/* IP PCN Input 755 */
          {
                    &PCNINPUT755,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 887 */
/* IP PCN Input 756 */
          {
                    &PCNINPUT756,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 888 */
/* IP PCN Input 757 */
          {
                    &PCNINPUT757,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 889 */
/* IP PCN Input 758 */
          {
                    &PCNINPUT758,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 890 */
/* IP PCN Input 759 */
          {
                    &PCNINPUT759,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 891 */
/* IP PCN Input 760 */
          {
                    &PCNINPUT760,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 892 */
/* IP PCN Input 761 */
          {
                    &PCNINPUT761,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 893 */
/* IP PCN Input 762 */
          {
                    &PCNINPUT762,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 894 */
/* IP PCN Input 763 */
          {
                    &PCNINPUT763,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 895 */
/* IP PCN Input 764 */
          {
                    &PCNINPUT764,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 896 */
/* IP PCN Input 800 */
          {
                    &PCNINPUT800,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 897 */
/* IP PCN Input 801 */
          {
                    &PCNINPUT801,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 898 */
/* IP PCN Input 802 */
          {
                    &PCNINPUT802,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 899 */
/* IP PCN Input 803 */
          {
                    &PCNINPUT803,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 900 */
/* IP PCN Input 804 */
          {
                    &PCNINPUT804,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 901 */
/* IP PCN Input 805 */
          {
                    &PCNINPUT805,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 902 */
/* IP PCN Input 806 */
          {
                    &PCNINPUT806,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 903 */
/* IP PCN Input 807 */
          {
                    &PCNINPUT807,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 904 */
/* IP PCN Input 808 */
          {
                    &PCNINPUT808,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 905 */
/* IP PCN Input 809 */
          {
                    &PCNINPUT809,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 906 */
/* IP PCN Input 810 */
          {
                    &PCNINPUT810,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 907 */
/* IP PCN Input 811 */
          {
                    &PCNINPUT811,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 908 */
/* IP PCN Input 812 */
          {
                    &PCNINPUT812,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 909 */
/* IP PCN Input 813 */
          {
                    &PCNINPUT813,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 910 */
/* IP PCN Input 814 */
          {
                    &PCNINPUT814,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 911 */
/* IP PCN Input 850 */
          {
                    &PCNINPUT850,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 912 */
/* IP PCN Input 851 */
          {
                    &PCNINPUT851,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 913 */
/* IP PCN Input 852 */
          {
                    &PCNINPUT852,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 914 */
/* IP PCN Input 853 */
          {
                    &PCNINPUT853,
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 915 */
/* IP PCN Input 854 */
          {
                    &PCNINPUT854,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 916 */
/* IP PCN Input 855 */
          {
                    &PCNINPUT855,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 917 */
/* IP PCN Input 856 */
          {
                    &PCNINPUT856,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 918 */
/* IP PCN Input 857 */
          {
                    &PCNINPUT857,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 919 */
/* IP PCN Input 858 */
          {
                    &PCNINPUT858,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 920 */
/* IP PCN Input 859 */
          {
                    &PCNINPUT859,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 921 */
/* IP PCN Input 860 */
          {
                    &PCNINPUT860,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 922 */
/* IP PCN Input 861 */
          {
                    &PCNINPUT861,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 923 */
/* IP PCN Input 862 */
          {
                    &PCNINPUT862,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 924 */
/* IP PCN Input 863 */
          {
                    &PCNINPUT863,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 925 */
/* IP PCN Input 864 */
          {
                    &PCNINPUT864,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 926 */
/* FB - Park Brk Mismatch Set Time */
          {
                    &u32[FBPBMMSETTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 927 */
/* Prot - Cum Enrgy ConsTk 1 */
          {
                    &u32[Cum_En_ConTk1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 928 */
/* Prot - Cum Engy Regen Tk2 */
          {
                    &u32[cumEnergyRegenTk2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 929 */
/* Prot - Cum Engy NonReg Tk1 */
          {
                    &u32[cumEnergyNonRegenTk1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 930 */
/* Prot - Cum Enrgy ConsTk 2 */
          {
                    &u32[Cum_En_ConTk2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 931 */
/* Prot - Cum Engy NonReg Tk2 */
          {
                    &u32[cumEnergyNonRegenTk2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 932 */
/* Prot - Cum Engy Regen Tk1 */
          {
                    &u32[cumEnergyRegenTk1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 933 */
/* Prot - Cum VCU Alive Time */
          {
                    &u32[cumVcuAliveTime],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 934 */
/* Prot - Lost FB TE */
          {
                    &i32[PROTLOSTFBTE],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 935 */
/* Prot - Lost Prop TE */
          {
                    &i32[PROTLOSTPROPTE],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 936 */
/* Prot - Number Failed FB */
          {
                    &u16[PROTNUMFAILEDFB],
                    UINT_16_TYPE,
                    12,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 937 */
/* Tc - Inop FB Limit Flag */
          {
                    &u16[TCINOPFBFLAG],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 938 */
/* Tc - Inop FB Speed Target 1 */
          {
                    &u32[TCINOPFBSPEEDTARGET1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 939 */
/* Tc - Inop FB Speed Target 2 */
          {
                    &u32[TCINOPFBSPEEDTARGET2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 940 */
/* Prot - HV Input Line Voltage TK2 */
          {
                    &i32[LVLOWNRGTHRSH2],
                    INT_32_TYPE,
                    315,                          20,
                    PTUD_PSSWD2
          },
/*  Variable Number 941 */
/* Prot - HV Input Line Voltage TK1 */
          {
                    &i32[LVLOWNRGTHRSH1],
                    INT_32_TYPE,
                    315,                          20,
                    PTUD_PSSWD2
          },
/*  Variable Number 942 */
/* Prot - HV Input Mile Ctr Lmt Tk1 */
          {
                    &u16[PROTLVNRGMILE1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 943 */
/* Slide1: Timeout Enabled */
          {
                    &u16[slideTimeoutEnabledTrk1],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 944 */
/* Slide2: Timeout Enabled */
          {
                    &u16[slideTimeoutEnabledTrk2],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 945 */
/* Spin1: Timeout Enabled */
          {
                    &u16[spinTimeoutEnabledTrk1],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 946 */
/* Spin2: Timeout Enabled */
          {
                    &u16[spinTimeoutEnabledTrk2],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 947 */
/* Slide1: Timeout Timer */
          {
                    &u32[slideTimeoutTimerTrk1],
                    UINT_32_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 948 */
/* Slide2: Timeout Timer */
          {
                    &u32[slideTimeoutTimerTrk2],
                    UINT_32_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 949 */
/* Spin1: Timeout Timer */
          {
                    &u32[spinTimeoutTimerTrk1],
                    UINT_32_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 950 */
/* Spin2: Timeout Timer */
          {
                    &u32[spinTimeoutTimerTrk2],
                    UINT_32_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 951 */
/* Vel - All Wheel Slide Flag */
          {
                    &u16[VelAllWheelSlide],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 952 */
/* Spin: JerkRate - Knee4 */
          {
                    &u16[spinJRKnee4],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 953 */
/* Spin: JerkRate - Knee5 */
          {
                    &u16[spinJRKnee5],
                    UINT_16_TYPE,
                    5000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 954 */
/* Spin: JerkRateLimitScale - Knee4 */
          {
                    &u16[spinJRLPercentKnee4],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 955 */
/* Spin: JerkRateLimitScale - Knee5 */
          {
                    &u16[spinJRLPercentKnee5],
                    UINT_16_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 956 */
/* Vel - Reference Speed */
          {
                    &u32[VelRefSpeed],
                    UINT_32_TYPE,
                    100000,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 957 */
/* IP - TIMS Message Fault */
          {
                    &u32[timsMessageFault],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 958 */
/* IP - A1 Master Zero Buffer Ctr */
          {
                    &u16[a1MasterZBTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 959 */
/* IP - A1 Master Cir Buffer TO */
          {
                    &u16[a1MasterComTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 960 */
/* IP - A1 Master Protocol Ver Mis */
          {
                    &u16[a1MasterVerTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 961 */
/* IP - A1 Master Qualify One Source */
          {
                    &u16[a1masterQualOneTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 962 */
/* IP - A1 Backup Cir Buffer TO */
          {
                    &u16[a1BackupComTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 963 */
/* IP - A1 Backup Protocol Ver Mis */
          {
                    &u16[a1BackupVerTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 964 */
/* IP - A1 Backup Qualify One Source */
          {
                    &u16[a1BackupQualOneTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 965 */
/* IP - A1 Backup Zero Buffer Ctr */
          {
                    &u16[a1BackupZBTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 966 */
/* IP - A6 Master Cir Buffer TO */
          {
                    &u16[a6MasterComTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 967 */
/* IP - A6 Master Protocol Ver Mis */
          {
                    &u16[a6MasterVerTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 968 */
/* IP - A6 Master Qualify One Source */
          {
                    &u16[a6masterQualOneTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 969 */
/* IP - A6 Master Zero Buffer Ctr */
          {
                    &u16[a6MasterZBTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 970 */
/* IP - A6 Backup Cir Buffer TO */
          {
                    &u16[a6BackupComTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 971 */
/* IP - A6 Backup Protocol Ver Mis */
          {
                    &u16[a6BackupVerTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 972 */
/* IP - A6 Backup Qualify One Source */
          {
                    &u16[a6BackupQualOneTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 973 */
/* IP - A6 Backup Zero Buffer Ctr */
          {
                    &u16[a6BackupZBTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 974 */
/* Mot - DB Fade Rate Limit Trk 1 */
          {
                    &i32[MotDBFadeJRLTruck1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 975 */
/* Mot - DB Fade Rate Limit Trk 2 */
          {
                    &i32[MotDBFadeJRLTruck2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 976 */
/* IP PCN Input 220 */
          {
                    &PCNINPUT220,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 977 */
/* Prot - TempShutdown Status T 2 */
          {
                    &u32[TEMPSHUTDOWNSTATUS],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 978 */
/* Prot - TempShutdown Status T1 */
          {
                    &u32[TEMPSHUTDOWNSTATUSB],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 979 */
/* Mot - Backup Prop TE Trk#1 */
          {
                    &i32[MOTBTE1],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 980 */
/* Mot - Backup Prop TE Trk#2 */
          {
                    &i32[MOTBTE2],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 981 */
/* Mot - BFC Flag Trk1 */
          {
                    &u16[MOTTRK1BFCFLAG],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 982 */
/* Mot - BFC Flag Trk2 */
          {
                    &u16[MOTTRK2BFCFLAG],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 983 */
/* Mot - Comp Fade Rate */
          {
                    &i32[MOTCOMPFADERATE],
                    INT_32_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 984 */
/* Mot - DB Fade Flag Trk1 */
          {
                    &u16[MOTTRK1DBFADE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 985 */
/* Mot - DB Fade Flag Trk2 */
          {
                    &u16[MOTTRK2DBFADE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 986 */
/* Mot - Max FB Comp TE */
          {
                    &i32[MOTMAXFBTE],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_PSSWD2
          },
/*  Variable Number 987 */
/* Mot - Number Failed Inverters */
          {
                    &u16[MOTNUMFAILEDINV],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 988 */
/* Mot - Train Weight Factor */
          {
                    &u16[MOTWEIGHTFACTOR],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 989 */
/* Mot - Trk1 Brk Comp */
          {
                    &u16[MOTTRK1COMPOFF],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 990 */
/* Mot - Trk1 Comp TE */
          {
                    &i32[MOTTRK1COMPVAL],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_PSSWD2
          },
/*  Variable Number 991 */
/* Mot - Trk2 Brk Comp */
          {
                    &u16[MOTTRK2COMPOFF],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 992 */
/* Prot - BFC Disable No Master */
          {
                    &u16[PROTBFCDISABLED],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 993 */
/* Prot - Train Weight */
          {
                    &u32[PROTTRAINWEIGHT],
                    UINT_32_TYPE,
                    4294967295,                   0,
                    PTUD_READONLY
          },
/*  Variable Number 994 */
/* Prot - Powered Truck Weight */
          {
                    &u32[PROTPTRKWEIGHT],
                    UINT_32_TYPE,
                    4294967295,                   0,
                    PTUD_READONLY
          },
/*  Variable Number 995 */
/* Mot - Prop Deviation Trk1 */
          {
                    &i32[MOTTRK1PROPDEV],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 996 */
/* Mot - Prop Deviation Trk2 */
          {
                    &i32[MOTTRK2PROPDEV],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 997 */
/* Mot - Max Prop Deviation */
          {
                    &i32[MOTPROPDEVTHRESH],
                    INT_32_TYPE,
                    50000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 998 */
/* Mot - Actual Prop TE Req Trk 1 */
          {
                    &i32[MOTACTUALPROPOUTPUT1],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 999 */
/* Mot - Actual Prop TE Req Trk 2 */
          {
                    &i32[MOTACTUALPROPOUTPUT2],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 1000 */
/* Mot - DB Fade Delay */
          {
                    &u16[MOTDBFADEDELAYENABLE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1001 */
/* Mot - DB Fade Delay Time */
          {
                    &u16[MOTDBFADEDELAY],
                    UINT_16_TYPE,
                    23,                           0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1002 */
/* Mot - Elapsed Fade Time Trk 1 */
          {
                    &u16[MOTELAPFADE1],
                    UINT_16_TYPE,
                    23,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 1003 */
/* Mot - Elapsed Fade Time Trk 2 */
          {
                    &u16[MOTELAPFADE2],
                    UINT_16_TYPE,
                    23,                           0,
                    PTUD_READONLY
          },
/*  Variable Number 1004 */
/* Mot - Max Fade Index Truck 1 */
          {
                    &u16[MOTMAXFADEINDEX1],
                    UINT_16_TYPE,
                    200,                          0,
                    PTUD_READONLY
          },
/*  Variable Number 1005 */
/* Mot - Max Fade Index Truck 2 */
          {
                    &u16[MOTMAXFADEINDEX2],
                    UINT_16_TYPE,
                    200,                          0,
                    PTUD_READONLY
          },
/*  Variable Number 1006 */
/* Tc - Bypass Off Time MC1 */
          {
                    &u32[MC1BYPASSOFFTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1007 */
/* Tc - Bypass Off Time MC2 */
          {
                    &u32[MC2BYPASSOFFTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1008 */
/* Tc - Door Bypass Status MC1 */
          {
                    &u16[MC1BYPASSSTATUS],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1009 */
/* Tc - Door Bypass Status MC2 */
          {
                    &u16[MC2BYPASSSTATUS],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1010 */
/* Vel - Axle 1 Calc Wheel Diam */
          {
                    &u16[CalcWheelDiam1],
                    UINT_16_TYPE,
                    71440,                        63500,
                    PTUD_READONLY
          },
/*  Variable Number 1011 */
/* Vel - Axle 1 Max Calc WD Diff */
          {
                    &u16[calcWheelDiamDiffmax1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1012 */
/* Vel - Axle 2 Calc Wheel Diam */
          {
                    &u16[CalcWheelDiam2],
                    UINT_16_TYPE,
                    71440,                        63500,
                    PTUD_READONLY
          },
/*  Variable Number 1013 */
/* Vel - Axle 2 Max Calc WD Diff */
          {
                    &u16[calcWheelDiamDiffmax2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1014 */
/* Vel - Axle 3 Calc Wheel Diam */
          {
                    &u16[CalcWheelDiam3],
                    UINT_16_TYPE,
                    71440,                        63500,
                    PTUD_READONLY
          },
/*  Variable Number 1015 */
/* Vel - Axle 3 Max Calc WD Diff */
          {
                    &u16[calcWheelDiamDiffmax3],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1016 */
/* Vel - Axle 4 Calc Wheel Diam */
          {
                    &u16[CalcWheelDiam4],
                    UINT_16_TYPE,
                    71440,                        63500,
                    PTUD_READONLY
          },
/*  Variable Number 1017 */
/* Vel - Axle 4 Max Calc WD Diff */
          {
                    &u16[calcWheelDiamDiffmax4],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1018 */
/* Prot - General System Mode */
          {
                    &u16[STGENSYSMODE],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1019 */
/* Prot - Pre-dep Data */
          {
                    &u16[PROTPREDEPDATA],
                    UINT_16_TYPE,
                    831,                          0,
                    PTUD_READONLY
          },
/*  Variable Number 1020 */
/* Prot - Pre-dep Mode */
          {
                    &u16[PROTPREDEPMODE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1021 */
/* Prot - System Test Mode */
          {
                    &u16[PROTSYSTESTMODE],
                    UINT_16_TYPE,
                    4,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1022 */
/* NM - Ch1 Mismatch Timer */
          {
                    &u32[NMmismatchTime],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1023 */
/* Mot - FMC High Perf Fac Trk1 */
          {
                    &i32[MOTFMCHIGHPERFFACTRK1],
                    INT_32_TYPE,
                    2000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1024 */
/* Mot - FMC High Perf Fac Trk2 */
          {
                    &i32[MOTFMCHIGHPERFFACTRK2],
                    INT_32_TYPE,
                    2000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1025 */
/* Mot - FMC Std Perf Fac Trk1 */
          {
                    &i32[MOTFMCSTDPERFFACTRK1],
                    INT_32_TYPE,
                    2000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1026 */
/* Mot - FMC Std Perf Fac Trk2 */
          {
                    &i32[MOTFMCSTDPERFFACTRK2],
                    INT_32_TYPE,
                    2000,                         0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1027 */
/* Mot - Prop Rate Req Trk1 */
          {
                    &i32[MOTPROPRATEREQTRK1],
                    INT_32_TYPE,
                    100000,                       -100000,
                    PTUD_READONLY
          },
/*  Variable Number 1028 */
/* Mot - Prop Rate Req Trk2 */
          {
                    &i32[MOTPROPRATEREQTRK2],
                    INT_32_TYPE,
                    100000,                       -100000,
                    PTUD_READONLY
          },
/*  Variable Number 1029 */
/* Mot - FB Xfer Function */
          {
                    &u16[MOTFBXFERFUNC],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1030 */
/* Mot - Integral Cntl Factor */
          {
                    &i32[MOTINTFACTOR],
                    INT_32_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1031 */
/* Mot - mA To Te Var1 */
          {
                    &i32[MOTMATOTEVAR1],
                    INT_32_TYPE,
                    -1,                           -100000,
                    PTUD_PSSWD2
          },
/*  Variable Number 1032 */
/* Mot - mA To Te Var2 */
          {
                    &i32[MOTMATOTEVAR2],
                    INT_32_TYPE,
                    1000000,                      0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1033 */
/* Mot - PCL Limit Enable */
          {
                    &u16[MOTPCLENABLE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1034 */
/* Mot - PCL Model Enable */
          {
                    &u16[MOTPCLMODEL],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1035 */
/* Mot - Proportional Cntl Factor */
          {
                    &i32[MOTPROPFACTOR],
                    INT_32_TYPE,
                    100,                          0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1036 */
/* Mot - Sim Time Constant */
          {
                    &i32[MOTSIMTIMECONST],
                    INT_32_TYPE,
                    100000000,                    0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1037 */
/* Mot - Targeted App TE Trk1 */
          {
                    &i32[MOTTRGTEFF1],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 1038 */
/* Mot - Targeted App TE Trk2 */
          {
                    &i32[MOTTRGTEFF2],
                    INT_32_TYPE,
                    50000,                        -50000,
                    PTUD_READONLY
          },
/*  Variable Number 1039 */
/* Mot - PCL Request Trk1 */
          {
                    &i32[MOTIREQUESTTRK1],
                    INT_32_TYPE,
                    1000000,                      -1000000,
                    PTUD_READONLY
          },
/*  Variable Number 1040 */
/* Mot - PCL Integral Trk1 */
          {
                    &i32[MOTIINTEGRALTRK1],
                    INT_32_TYPE,
                    1000000,                      -1000000,
                    PTUD_READONLY
          },
/*  Variable Number 1041 */
/* Mot - PCL Command Trk1 */
          {
                    &i32[MOTICOMMANDTRK1],
                    INT_32_TYPE,
                    1000000,                      -1000000,
                    PTUD_READONLY
          },
/*  Variable Number 1042 */
/* Mot - PCL Predict Trk1 */
          {
                    &i32[MOTIPREDICTTRK1],
                    INT_32_TYPE,
                    1000000,                      -1000000,
                    PTUD_READONLY
          },
/*  Variable Number 1043 */
/* Mot - PCL Request Trk2 */
          {
                    &i32[MOTIREQUESTTRK2],
                    INT_32_TYPE,
                    1000000,                      -1000000,
                    PTUD_READONLY
          },
/*  Variable Number 1044 */
/* Mot - PCL Integral Trk2 */
          {
                    &i32[MOTIINTEGRALTRK2],
                    INT_32_TYPE,
                    1000000,                      -1000000,
                    PTUD_READONLY
          },
/*  Variable Number 1045 */
/* Mot - PCL Command Trk2 */
          {
                    &i32[MOTICOMMANDTRK2],
                    INT_32_TYPE,
                    1000000,                      -1000000,
                    PTUD_READONLY
          },
/*  Variable Number 1046 */
/* Mot - PCL Predict Trk2 */
          {
                    &i32[MOTIPREDICTTRK2],
                    INT_32_TYPE,
                    1000000,                      -1000000,
                    PTUD_READONLY
          },
/*  Variable Number 1047 */
/* MS - Stop TIMS Bad Swap */
          {
                    &u16[stopTimsBadSwap],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1048 */
/* Tc - Inop FB Speed Tolerance */
          {
                    &u32[TCINOPFBTOL],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1049 */
/* Tc - Turtle Speed Target 1 */
          {
                    &u32[TCTURTLESPEEDTARGET1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1050 */
/* Tc - Turtle Speed Target 2 */
          {
                    &u32[TCTURTLESPEEDTARGET2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1051 */
/* Tc - Turtle Speed Tolerance */
          {
                    &u32[TCTURTLETOL],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1052 */
/* Slide: EB Detect Velocity Percent */
          {
                    &u32[slideVelocityEmerBrakePercent],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1053 */
/* Slide: EB Readhere Vel Percent */
          {
                    &u32[slideEBReadhereVelocityPercent],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1054 */
/* Slide: Readhere Velocity Thresh */
          {
                    &u32[slideVelocityReadhereThreshold],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1055 */
/* Slide: SB Detect Velocity Percent */
          {
                    &u32[slideVelocityServicePercent],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1056 */
/* Slide: SB Readhere Vel Percent */
          {
                    &u32[slideSBReadhereVelocityPercent],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1057 */
/* Slide1: Detect Velocity Thresh  */
          {
                    &u32[slideVelocityTripThreshold1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1058 */
/* Slide1: Pulse BVD Enable Trk 1 */
          {
                    &u16[ssPulseBVDDisable1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1059 */
/* Slide2: Detect Velocity Thresh */
          {
                    &u32[slideVelocityTripThreshold2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1060 */
/* Slide2: Pulse BVD Enable Trk 2 */
          {
                    &u16[ssPulseBVDDisable2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1061 */
/* SS: Ang Rate Flag */
          {
                    &u16[ssAngRateDisable],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1062 */
/* Vel - Axle 1 Ang Rate */
          {
                    &i32[VelAxle1AngRate],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1063 */
/* Vel - Axle 2 Ang Rate */
          {
                    &i32[VelAxle2AngRate],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1064 */
/* Vel - Axle 3 Ang Rate */
          {
                    &i32[VelAxle3AngRate],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1065 */
/* Vel - Axle 4 Ang Rate */
          {
                    &i32[VelAxle4AngRate],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1066 */
/* Vel - Car Ang Rate */
          {
                    &i32[VelCarAngRate],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1067 */
/* Vel - Car Ang Speed */
          {
                    &i32[VelCarAngSpeed],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1068 */
/* Vel - Ref Speed Ang */
          {
                    &i32[refSpeedAng],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1069 */
/* Vel - Ref Speed Select */
          {
                    &u16[VelRefSpeedSelect],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1070 */
/* Vel - Selected Ref Speed */
          {
                    &u32[VelSelectedRefSpeed],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1071 */
/* Slide1: BVD Command */
          {
                    &u16[slide1BVDCommand],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1072 */
/* Slide2: BVD Command */
          {
                    &u16[slide2BVDCommand],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1073 */
/* Prot - Cum Fb Effort Tk1 */
          {
                    &u32[cumFbEffortTk1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1074 */
/* Prot - Cum Fb Effort Tk2 */
          {
                    &u32[cumFbEffortTk2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1075 */
/* Prot - Cum M/S Swaps */
          {
                    &u32[PROTCUMMSSWAPS],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1076 */
/* Prot - Cum Time in Emerg */
          {
                    &u32[PROTCUMTIMEEMERG],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1077 */
/* Prot - Cum Time in Motion */
          {
                    &u32[PROTCUMTIMEMOTION],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1078 */
/* Prot - ER1 Mismatch Time */
          {
                    &u32[PROTER1MISMATCHTIME],
                    UINT_32_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1079 */
/* Prot - ER2 Mismatch Time */
          {
                    &u32[PROTER2MISMATCHTIME],
                    UINT_32_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1080 */
/* Prot - LLV EB Threshold Trk1 */
          {
                    &i32[PROTLLVEBTHRESH1],
                    INT_32_TYPE,
                    70,                           5,
                    PTUD_PSSWD2
          },
/*  Variable Number 1081 */
/* Prot - LLV EB Threshold Trk2 */
          {
                    &i32[PROTLLVEBTHRESH2],
                    INT_32_TYPE,
                    70,                           5,
                    PTUD_PSSWD2
          },
/*  Variable Number 1082 */
/* Prot - LLV EB Time Trk1 */
          {
                    &u32[PROTLLVEBTIME1],
                    UINT_32_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1083 */
/* Prot - LLV EB Time Trk2 */
          {
                    &u32[PROTLLVEBTIME2],
                    UINT_32_TYPE,
                    10000,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1084 */
/* Prot - Current Time POSIX */
          {
                    &u32[PROTCURRENTTIME],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1085 */
/* Prot - Hours Elapsed */
          {
                    &i32[PROTHOURSELAPSED],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1086 */
/* Prot - MOBAD Life Remaining */
          {
                    &i32[PROTMOBADLIFE],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1087 */
/* Inv - DCU#1 Powerup Override */
          {
                    &u16[DCU1PUPOVERRIDE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1088 */
/* Inv - DCU#2 Powerup Override */
          {
                    &u16[DCU2PUPOVERRIDE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1089 */
/* Prot - Rate Deviation */
          {
                    &i32[PROTBRKRATEDEV],
                    INT_32_TYPE,
                    100,                          -100,
                    PTUD_READONLY
          },
/*  Variable Number 1090 */
/* Vel - Axle 1 Filtered RPM */
          {
                    &i32[VelAxle1Filtered],
                    INT_32_TYPE,
                    9000000,                      0,
                    PTUD_READONLY
          },
/*  Variable Number 1091 */
/* Vel - Axle 2 Filtered RPM */
          {
                    &i32[VelAxle2Filtered],
                    INT_32_TYPE,
                    9000000,                      0,
                    PTUD_READONLY
          },
/*  Variable Number 1092 */
/* Vel - Axle 3 Filtered RPM */
          {
                    &i32[VelAxle3Filtered],
                    INT_32_TYPE,
                    9000000,                      0,
                    PTUD_READONLY
          },
/*  Variable Number 1093 */
/* Vel - Axle 4 Filtered RPM */
          {
                    &i32[VelAxle4Filtered],
                    INT_32_TYPE,
                    9000000,                      0,
                    PTUD_READONLY
          },
/*  Variable Number 1094 */
/* Vel - WD Calc Rate Thresh A1 */
          {
                    &u32[velWdCalcRateThresA1],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1095 */
/* Vel - WD Calc Rate Thresh A2 */
          {
                    &u32[velWdCalcRateThresA2],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1096 */
/* Vel - WD Calc Rate Thresh A3 */
          {
                    &u32[velWdCalcRateThresA3],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1097 */
/* Vel - WD Calc Rate Thresh A4 */
          {
                    &u32[velWdCalcRateThresA4],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1098 */
/* MS - Tims Key Down Swap */
          {
                    &u16[stopKeyDown],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1099 */
/* FB - In Shot During Slide */
          {
                    &u16[FBISSLIDE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1100 */
/* MS - Tims Key Down  */
          {
                    &u16[timsKeyDownReq],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1101 */
/* MS - Key Down Flag */
          {
                    &u16[timsKeyDownReqFlag],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1102 */
/* IP  - A1 Master Off Ctr */
          {
                    &u16[A1MasterOffCtr],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1103 */
/* IP  - A1 Backup Off Ctr */
          {
                    &u16[A1BackupOffCtr],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1104 */
/* IP  - A6 Master Off Ctr */
          {
                    &u16[A6MasterOffCtr],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1105 */
/* IP  - A6 Backup Off Ctr */
          {
                    &u16[A6BackupOffCtr],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1106 */
/* MS - Key Down Count */
          {
                    &u16[msKeydownCount],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1107 */
/* Tc - Key Down Count Master */
          {
                    &u16[tcKeydownCountM],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1108 */
/* Tc - Key Down Count backup */
          {
                    &u16[tcKeydownCountBackup],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1109 */
/* Tc - Off Status Master */
          {
                    &u16[tcOffMaster],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1110 */
/* Tc - Off Status Backup */
          {
                    &u16[tcOffBackup],
                    UINT_16_TYPE,
                    2,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1111 */
/* Vel - Set Odometer Flag */
          {
                    &u16[VelSetOdometerFlag],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1112 */
/* Vel - New Odometer Value */
          {
                    &u32[VelNewOdometerValue],
                    UINT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1113 */
/* Vel - Tach Reset Cmd */
          {
                    &u16[velTachResetCmd],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1114 */
/* FB - PCL High Speed Enable */
          {
                    &u16[FBPCLHSE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1115 */
/* St - BVC Trk1 Fail Count */
          {
                    &u16[STBVCFC1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1116 */
/* St - BVC Trk1 Fail Limit */
          {
                    &u16[STBVCFL1],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1117 */
/* St - BVC Trk2 Fail Count */
          {
                    &u16[STBVCFC2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1118 */
/* St - BVC Trk2 Fail Limit */
          {
                    &u16[STBVCFL2],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1119 */
/* Dir - Dir Change Speed Threshold */
          {
                    &i32[DIRCHANGESPEED],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1120 */
/* PCNOUTPUT18 */
          {
                    &PCNOUTPUT18,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1121 */
/* St - Maint Allowed Bypass */
          {
                    &u16[STMAINTBYPASS],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1122 */
/* Prot - Wheel Slide Test Data */
          {
                    &u16[PROTWSTD],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1123 */
/* Prot - Wheel Slide Test Mode */
          {
                    &u16[PROTWSTM],
                    UINT_16_TYPE,
                    4,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1124 */
/* Prot - Wheel Slide Test Command */
          {
                    &u16[PROTWSTC],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1125 */
/* Prot - Rollback Mileage Lmt */
          {
                    &i32[PROTROLLTHRES],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1126 */
/* Prot - BCP Cmd Mon Threshold */
          {
                    &i32[FBCMDDIFFTHRESHOLD],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1127 */
/* Prot - BCP Mon Low Range */
          {
                    &i32[FBPRESSRANGELO],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1128 */
/* Prot - BCP Mon High Range */
          {
                    &i32[FBPRESSRANGEHI],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1129 */
/* BBRam - Reference Wheel Diam */
          {
                    &u16[cbramRefWheelDiam],
                    UINT_16_TYPE,
                    655350,                       0,
                    PTUD_READONLY
          },
/*  Variable Number 1130 */
/* IP PCN Input 42 */
          {
                    &PCNINPUT42,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1131 */
/* IP PCN Input 43 */
          {
                    &PCNINPUT43,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1132 */
/* IP PCN Input 45 */
          {
                    &PCNINPUT45,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1133 */
/* IP PCN Input 46 */
          {
                    &PCNINPUT46,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1134 */
/* IP PCN Input 47 */
          {
                    &PCNINPUT47,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1135 */
/* IP PCN Input 41 */
          {
                    &PCNINPUT41,
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1136 */
/* IP PCN Input 4 */
          {
                    &PCNINPUT4,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1137 */
/* IP PCN Input 8 */
          {
                    &PCNINPUT8,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1138 */
/* IP PCN Input 44 */
          {
                    &PCNINPUT44,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1139 */
/* IP PCN Input 48 */
          {
                    &PCNINPUT48,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1140 */
/* PCNOUTPUT50 */
          {
                    &PCNOUTPUT50,
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1141 */
/* Tc - ATO Mode MC1 */
          {
                    &u16[MC1ATOMODE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1142 */
/* Tc - ATO Mode MC2 */
          {
                    &u16[MC2ATOMODE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1143 */
/* Tc - ATO Mode ATO1 */
          {
                    &u16[ATO1ATOMODE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1144 */
/* Tc - ATO Mode ATO2 */
          {
                    &u16[ATO2ATOMODE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1145 */
/* Tc - ATO FSB Req ATO1 */
          {
                    &u16[ATO1ATOFSBREQ],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1146 */
/* Tc - ATO FSB Req ATO2 */
          {
                    &u16[ATO2ATOFSBREQ],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1147 */
/* Tc - ATO FSB Req MC1 */
          {
                    &u16[MC1ATOFSBREQ],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1148 */
/* Tc - ATO FSB Req MC2 */
          {
                    &u16[MC2ATOFSBREQ],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1149 */
/* Tc - Controlling Mc */
          {
                    &u16[actRequestor],
                    UINT_16_TYPE,
                    7,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1150 */
/* Prot - ATO FSB BCP Thres - A Cars */
          {
                    &i32[PROTATOBCPTHRES1],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1151 */
/* Prot - ATO FSB BCP Thres - B Cars */
          {
                    &i32[PROTATOBCPTHRES2],
                    INT_32_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1152 */
/* Tc - ATO Mode */
          {
                    &u16[ATOMODE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1153 */
/* IP - A1 ATO Cir Buffer TO */
          {
                    &u16[a1ATOComTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 1154 */
/* IP - A1 ATO Protocol Ver Mis */
          {
                    &u16[a1ATOVerTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 1155 */
/* IP - A1 ATO Qualify One Source */
          {
                    &u16[a1ATOQualOneTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 1156 */
/* IP - A1 ATO Zero Buffer Ctr */
          {
                    &u16[a1ATOZBTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 1157 */
/* Mot - Fade OutputTrk 1 */
          {
                    &i32[MOTFADEOUTPUT1],
                    INT_32_TYPE,
                    0,                            -30000,
                    PTUD_READONLY
          },
/*  Variable Number 1158 */
/* Mot - Fade OutputTrk 2 */
          {
                    &i32[MOTFADEOUTPUT2],
                    INT_32_TYPE,
                    0,                            -30000,
                    PTUD_READONLY
          },
/*  Variable Number 1159 */
/* Tc - ATO Enable */
          {
                    &u16[ATOEnable],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1160 */
/* IP  - ATO Enable */
          {
                    &u16[IPATOEnable],
                    UINT_16_TYPE,
                    0,                            0,
                    PTUD_PSSWD2
          },
/*  Variable Number 1161 */
/* IP - A6 ATO Zero Buffer Ctr */
          {
                    &u16[a6ATOZBTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 1162 */
/* IP - A6 ATO Protocol Ver Mis */
          {
                    &u16[a6ATOVerTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 1163 */
/* IP - A6 ATO Qualify One Source */
          {
                    &u16[a6ATOQualOneTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 1164 */
/* IP - A6 ATO Cir Buffer TO */
          {
                    &u16[a6ATOComTO],
                    UINT_16_TYPE,
                    65535,                        0,
                    PTUD_READONLY
          },
/*  Variable Number 1165 */
/* Tc - MC1 Power Enable */
          {
                    &u16[MC1POWERENABLE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1166 */
/* Tc - MC2 Power Enable */
          {
                    &u16[MC2POWERENABLE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1167 */
/* Tc - ATO1 Power Enable */
          {
                    &u16[ATO1POWERENABLE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1168 */
/* Tc - ATO2 Power Enable */
          {
                    &u16[ATO2POWERENABLE],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1169 */
/* Tc - ATO1 Encoder Status */
          {
                    &u16[ATO1ENCODERSTATUS],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1170 */
/* Tc - ATO2 Encoder Status */
          {
                    &u16[ATO2ENCODERSTATUS],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1171 */
/* Tc - MC1 Encoder Status */
          {
                    &u16[MC1ENCODERSTATUS],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          },
/*  Variable Number 1172 */
/* Tc - MC2 Encoder Status */
          {
                    &u16[MC2ENCODERSTATUS],
                    UINT_16_TYPE,
                    1,                            0,
                    PTUD_READONLY
          }
};

#define   NUMOFEVENTLOGS                2

const     UINT_16   EventlogNumofTasks[NUMOFEVENTLOGS] =
{
          8, 9
};

const     UINT_16   EventlogNumofFaults[NUMOFEVENTLOGS] =
{
          48, 40
};



