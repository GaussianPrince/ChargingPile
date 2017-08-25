/*****************************************************

   Achieve calendar algorithm
   Copyright (c) WangYunXing,Govlan
               All rights reserved

 *****************************************************/
#include"Include.h"
/*****************************************************
	Union which stores local time
*******************************************************/
LocalTime LocalTimeBuff;
/*****************************************************
	Timer operation 
*******************************************************/
TimerOperation TimerOperationBuff;
/*****************************************************
	Record various type year
	Const variables stored in pflash
*******************************************************/
#pragma CONST_SEG   CONST_DISTRIBUTE
const UInt8 CommonMonthTable[]={
    31,28,31,30,
	31,30,31,31,
	30,31,30,31,
};
const UInt8 LeapMonthTable[]=
{
	31,29,31,30,
	31,30,31,31,
	30,31,30,31,
};
#pragma CONST_SEG  DEFAULT 
/*****************************************************
	Record times of day
*******************************************************/
void LocalTimeCounter(void)
{
	if (LocalTimeBuff.Compts.Second>58)
	{
		LocalTimeBuff.Compts.Second=0;
		if(LocalTimeBuff.Compts.Minute>58)
		{
			LocalTimeBuff.Compts.Minute=0;
			if(LocalTimeBuff.Compts.Hour>22)
			{
				LocalTimeBuff.Compts.Hour=0;
				++LocalTimeBuff.Compts.PassDay;
				CalendarCal();
			}
			else
			{
				++LocalTimeBuff.Compts.Hour;
			}
		}
		else
		{
			++LocalTimeBuff.Compts.Minute;
		}
	}
	else
	{
		++LocalTimeBuff.Compts.Second;
	}
	OSCRITICALENTRY();
}
/*****************************************************
	Judge whether a year is a leap year
*******************************************************/
UInt8 IsLeapYear(void)
{
	if((LocalTimeBuff.Compts.Year%100)==0)
	{
		if((LocalTimeBuff.Compts.Year%400)==0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else 
	{
		if((LocalTimeBuff.Compts.Year%4)==0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
/*****************************************************
	Count day
*******************************************************/
static void CountDay(const UInt8 *Table)
{
	if(!((LocalTimeBuff.Compts.Month>0)&&(LocalTimeBuff.Compts.Month<13)))
			return;
	if(LocalTimeBuff.Compts.Day>=Table[LocalTimeBuff.Compts.Month-1])
	{
		if(LocalTimeBuff.Compts.Month>=12)
		{
			++LocalTimeBuff.Compts.Year;
			LocalTimeBuff.Compts.Month=1;
			LocalTimeBuff.Compts.Day=1;
			LocalTimeBuff.Compts.LeapYearFlag=IsLeapYear();
		}
		else
		{
			++LocalTimeBuff.Compts.Month;
		}
	}
	else
	{
		++LocalTimeBuff.Compts.Day;
	}
}
/*****************************************************
	Calculate date 
*******************************************************/
void CalendarCal(void)
{
	if(LocalTimeBuff.Compts.LeapYearFlag==1)
	{
		CountDay(LeapMonthTable);
	}
	else
	{
		CountDay(CommonMonthTable);
	}
}
/*****************************************************
	 Zero out memory block
*******************************************************/
void  LocalTimeBuffInit(void)
{
	UInt8 n;
	for(n=0;n<6;n++)
	{
		LocalTimeBuff.data[n]=0;
	}
}
void  TimerOperationBuffInit(void)
{
	UInt8 n;
	for (n = 0; n < MAXTICKCOUNT + 2; n++)
	{
		TimerOperationBuff.data[n] = 0;
	}
	TimerOperationBuff.Compts.Front = 0;
	TimerOperationBuff.Compts.Rear = 1;
}
/*****************************************************
	Initialize timer module
*******************************************************/
void TimerInit(void)
{
	asm
	{
		MOVB  #$07,TIM_TSCR2
		MOVB  #$01,TIM_TIOS
		CLR  TIM_TCTL2
		MOVB #$01,TIM_TFLG1
		MOVB #$01,TIM_TIE
		MOVW #937,TIM_TCNT
		MOVW #937,TIM_TC0
		MOVB #$00,TIM_TSCR1
	}
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void TimerService(void)
{
	UInt8 n;
	asm
	{
		BSET TIM_TFLG1,#$01			//Clear flag
		MOVW #937,TIM_TCNT	    //Load  threshold
		MOVW #937,TIM_TC0			//Refresh value in compare register
	}
	for (n = TimerOperationBuff.Compts.Front; n < TimerOperationBuff.Compts.Rear; n++)
	{
		switch (n)
		{
		case 0:
			if (TimerOperationBuff.Compts.TickCount[0] == 3)
			{
				SCI1ChangeTransmitDirection();
			}
			else
			{
				++TimerOperationBuff.Compts.TickCount[0];
			}
			break;
		case 1:
			break;
		}
	}
}
#pragma  CODE_SEG  DEFAULT