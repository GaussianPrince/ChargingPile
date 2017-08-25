/*****************************************************

   Define data struct of time
   Copyright (c) WangYunXing,Govlan
               All rights reserved
   RAM SPACE:10BYTES
 *****************************************************/
#ifndef _TIMELOCAL_H
#define _TIMELOCAL_H
#define  MAXTICKCOUNT  5
#include"Include.h"
typedef  union
{
	UInt16 data[6];
	struct 
	{
		UInt16 Year;

		UInt16 Month	:8;
		UInt16 Day		:8;

		UInt16 Week		:8;
		UInt16 Hour		:8;

		UInt16 Minute	:8;
		UInt16 Second	:8;

		UInt16 PassDay	;
		UInt16 LeapYearFlag :8;
		UInt16 				:8;
	}Compts;
}LocalTime;
typedef union 
{
	UInt16 data[7];
	struct 
	{
		UInt16 TickCount[MAXTICKCOUNT+1];
		UInt16 Front : 8;
		UInt16 Rear : 8;
	}Compts;
}TimerOperation;
extern TimerOperation TimerOperationBuff;		//Use timer to count
extern LocalTime LocalTimeBuff;
extern UInt8 IsLeapYear(void);
extern void LocalTimeCounter(void);
extern void  CalendarCal(void);
extern void  LocalTimeBuffInit(void);
extern void  TimerOperationBuffInit(void);
extern void  TimerInit(void);
#endif