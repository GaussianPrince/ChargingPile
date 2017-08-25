/*****************************************************

   Define interrupt vector
   Copyright (c) WangYunXing,Govlan
               All rights reserved

 *****************************************************/
extern void near _Startup(void);
extern void near OSRTCTick(void);
extern void near OSCtxSw(void);
extern void near CAN0Power(void);
extern void near CAN2BMS(void);
extern void near TimerService(void);
extern void near SCI1Meter(void);
extern void near SCI5Card(void);
//extern void near SCI0HMI(void);
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void UnimplementedISR(void)
{
  asm BGND;
}

typedef void(*near tIsrFunc)(void);
const tIsrFunc _vect[] @0xFF10 = {     /* Interrupt table */
	UnimplementedISR,                 /*10 vector 119 */
	UnimplementedISR,                 /*12 vector 118 */
	UnimplementedISR,                 /*14 vector 117 */
	UnimplementedISR,                 /*16 vector 116 */
	UnimplementedISR,                 /*18 vector 115 */
	UnimplementedISR,                 /*1a vector 114 */
	UnimplementedISR,                 /*1c vector 113 */
	UnimplementedISR,                 /*1e vector 112 */
	UnimplementedISR,                 /*20 vector 111 */
	UnimplementedISR,                 /*22 vector 110 */
	UnimplementedISR,                 /*24 vector 109 */
	UnimplementedISR,                 /*26 vector 108 */
	UnimplementedISR,                 /*28 vector 107 */
	UnimplementedISR,                 /*2a vector 106 */
	UnimplementedISR,                 /*2c vector 105 */
	UnimplementedISR,                 /*2e vector 104 */
	UnimplementedISR,                 /*30 vector 103 */
	UnimplementedISR,                 /*32 vector 102 */
	UnimplementedISR,                 /*34 vector 101 */
	UnimplementedISR,                 /*36 vector 100 */
	UnimplementedISR,                 /*38 vector 99 */
	UnimplementedISR,                 /*3a vector 98 */
	UnimplementedISR,                 /*3c vector 97 */
	UnimplementedISR,                 /*3e vector 96 */
	UnimplementedISR,                 /*40 vector 95 */
	UnimplementedISR,                 /*42 vector 94 */
	UnimplementedISR,                 /*44 vector 93 */
	UnimplementedISR,                 /*46 vector 92 */
	UnimplementedISR,                 /*48 vector 91 */
	UnimplementedISR,                 /*4a vector 90 */
	UnimplementedISR,                 /*4c vector 89 */
	UnimplementedISR,                 /*4e vector 88 */
	UnimplementedISR,                 /*50 vector 87 */
	UnimplementedISR,                 /*52 vector 86 */
	TimerService,                 /*54 vector 85 */
	UnimplementedISR,                 /*56 vector 84 */
	UnimplementedISR,                 /*58 vector 83 */
	UnimplementedISR,                 /*5a vector 82 */
	UnimplementedISR,                 /*5c vector 81 */
	UnimplementedISR,                 /*5e vector 80 */
	UnimplementedISR,                 /*60 vector 79 */
	UnimplementedISR,                 /*62 vector 78 */
	UnimplementedISR,                 /*64 vector 77 */
	UnimplementedISR,                 /*66 vector 76 */
	UnimplementedISR,                 /*68 vector 75 */
	UnimplementedISR,                 /*6a vector 74 */
	UnimplementedISR,                 /*6c vector 73 */
	UnimplementedISR,                 /*6e vector 72 */
	UnimplementedISR,                 /*70 vector 71 */
	UnimplementedISR,                 /*72 vector 70 */
	UnimplementedISR,                 /*74 vector 69 */
	UnimplementedISR,                 /*76 vector 68 */
	UnimplementedISR,                 /*78 vector 67 */
	UnimplementedISR,                 /*7a vector 66 */
	UnimplementedISR,                 /*7c vector 65*/
	UnimplementedISR,                 /*7e vector 64*/
	UnimplementedISR,                 /*80 vector 63 */
	UnimplementedISR,                 /*82 vector 62 */
	SCI5Card,                 /*84 vector 61 */
	UnimplementedISR,                 /*86 vector 60 */
	UnimplementedISR,                 /*88 vector 59 */
	UnimplementedISR,                 /*8a vector 58 */
	UnimplementedISR,                 /*8c vector 57 */
	UnimplementedISR,                 /*8e vector 56 */
	UnimplementedISR,                 /*90 vector 55 */
	UnimplementedISR,                 /*92 vector 54 */
	UnimplementedISR,                 /*94 vector 53 */
	UnimplementedISR,                 /*96 vector 52 */
	UnimplementedISR,                 /*98 vector 51 */
	UnimplementedISR,                 /*9a vector 50 */
	UnimplementedISR,                 /*9c vector 49 */
	UnimplementedISR,                 /*9e vector 48 */
	UnimplementedISR,                 /*a0 vector 47 */
	CAN2BMS,                 /*a2 vector 46 */
	UnimplementedISR,                 /*a4 vector 45 */
	UnimplementedISR,                 /*a6 vector 44 */
	UnimplementedISR,                 /*a8 vector 43 */
	UnimplementedISR,                 /*aa vector 42 */
	UnimplementedISR,                 /*ac vector 41 */
	UnimplementedISR,                 /*ae vector 40 */
	UnimplementedISR,                 /*b0 vector 39 */
	CAN0Power,                 /*b2 vector 38 */
	UnimplementedISR,                 /*b4 vector 37 */
	UnimplementedISR,                 /*b6 vector 36 */
	UnimplementedISR,                 /*b8 vector 35 */
	UnimplementedISR,                 /*ba vector 34 */
	UnimplementedISR,                 /*bc vector 33 */
	UnimplementedISR,                 /*be vector 32 */
	UnimplementedISR,                 /*c0 vector 31 */
	UnimplementedISR,                 /*c2 vector 30 */
	UnimplementedISR,                 /*c4 vector 29 */
	UnimplementedISR,                 /*c6 vector 28 */
	UnimplementedISR,                 /*c8 vector 27 */
	UnimplementedISR,                 /*ca vector 26 */
	UnimplementedISR,                 /*cc vector 25 */
	UnimplementedISR,                 /*ce vector 24 */
	UnimplementedISR,                 /*d0 vector 23 */
	UnimplementedISR,                 /*d2 vector 22 */
	SCI1Meter,                 /*d4 vector 21 */
	UnimplementedISR,                 /*d6 vector 20 */
	UnimplementedISR,                 /*d8 vector 19 */
	UnimplementedISR,                 /*da vector 18 */
	UnimplementedISR,                 /*dc vector 17 */
	UnimplementedISR,                 /*de vector 16 */
	UnimplementedISR,                 /*e0 vector 15 */
	UnimplementedISR,                 /*e2 vector 14 */
	UnimplementedISR,                 /*e4 vector 13 */
	UnimplementedISR,                 /*e6 vector 12 */
	UnimplementedISR,                 /*e8 vector 11 */
	UnimplementedISR,                 /*ea vector 10 */
	UnimplementedISR,                 /*ec vector 09 */
	UnimplementedISR,                 /*ee vector 08 */
		OSRTCTick,                      /*f0 vector 07 */
	UnimplementedISR,                 /*f2 vector 06 */
	UnimplementedISR,                 /*f4 vector 05 */
	UnimplementedISR,                 /*f6 vector 04 */
	UnimplementedISR,                 /*f8 vector 03 */
	_Startup,                         /*fa vector 02 */
	_Startup,                         /*fc vector 01 */
									 //       _Startup                        /*fe Resetvector */
};
#pragma  CODE_SEG  DEFAULT
