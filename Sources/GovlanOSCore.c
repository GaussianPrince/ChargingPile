/*****************************************************

   Achieve the core scheduler functions.
   Copyright (c) WangYunXing,Govlan
               All rights reserved
               
 *****************************************************/
#include"Include.h"
#pragma MESSAGE DISABLE C1420
/*****************************************************
	Task queue
*******************************************************/
GovlanOSTask GovlanOSTaskArr[GOVLANOSMAXTASKS];
/*****************************************************
	Store the error code
*******************************************************/
UInt8 GovlanOSErrorCode=0;
/*****************************************************
	Private function prototypes
*******************************************************/
static void GovlanOSGoToSleep(void);
/*****************************************************
	Private variable			
*******************************************************/
static UInt16 GovlanOSErrorTickCount=0;
static UInt8  GovlanOSLastErrorCode=0;
/*****************************************************
	When a task(function) is to be run,this function will run it.
	It must be called (repeatedly) from the main loop.		
*******************************************************/
void GovlanOSDispatchTasks(void)
{
	UInt8 n;
	for(n=0;n<GOVLANOSMAXTASKS;n++)
	{
		if((GovlanOSTaskArr[n].Cooperation)&&(GovlanOSTaskArr[n].RunTask>0))
		{
			(*GovlanOSTaskArr[n].PTask)();
			GovlanOSTaskArr[n].RunTask-=1;
			if(GovlanOSTaskArr[n].Period==0)
			{
				GovlanOSDeleteTask(n);
			}
		}
	}
//	GovlanOSReportStatus();
//  GovlanOSGoToSleep();
}
/*****************************************************
	Add a task(function) to the queue.
	InTask 	--	Function to be scheduleInd.
	Delay	--  The interval before task is executed.
	Period  --  If PERIOD is zero,InTask is only called once.
	InCoOperation -- 0 indicates that the operating type is Cooperation.
					 1 indicates that the operating type is Preemptive
	Return 	value:
		Return the position in queue where the task has been added.
		If the return value is less then GOVLANMAXTASKS,then the task 
		was added successfully.
*******************************************************/
 UInt8 GovlanOSAddTask(void(*InTask)(void),const UInt16 Delay,const UInt16 Period,UInt8 InCooperation)
 {
 	UInt8 n=0;
 	while(GovlanOSTaskArr[n].PTask!=0)
 	{
 		++n;
		if (n == GOVLANOSMAXTASKS)
		{
			GovlanOSErrorCode = GOVLANOSTOOMANYTASKS;
			return GOVLANOSMAXTASKS;
		}
 	}
 	
 	GovlanOSTaskArr[n].PTask=InTask;
 	GovlanOSTaskArr[n].Delay=Delay;
 	GovlanOSTaskArr[n].Period=Period;
 	GovlanOSTaskArr[n].RunTask=0;
 	GovlanOSTaskArr[n].Cooperation=InCooperation;
 	return n;
 }
/*****************************************************
		Remove a task from the scheduler.
		Index -- The task index
		Return value:
			GOVLANOSRETURNERRORNULL or GOVLANOSRETURNNORMAL		
*******************************************************/ 
UInt8 GovlanOSDeleteTask(const UInt8 Index)
{
	UInt8 n;
	if(GovlanOSTaskArr[Index].PTask==0)
	{
		GovlanOSErrorCode=GOVLANOSRETURNERRORNULL;
		n=GovlanOSErrorCode;
	}
	else
	{
		n=GOVLANOSRETURNENORMAL;

	}
	GovlanOSTaskArr[Index].PTask=0;
	GovlanOSTaskArr[Index].Delay=0;
	GovlanOSTaskArr[Index].Period=0;
	GovlanOSTaskArr[Index].RunTask=0;
	GovlanOSTaskArr[Index].Cooperation=0;
	return n;
}
/*****************************************************
	Display Error code by led
*******************************************************/
void GovlanOSReportStatus(void)
{
	asm
	{
		LDAA GovlanOSErrorCode
		LDAB GovlanOSLastErrorCode
		CBA
		BEQ COUNTDOWNEERORCODE
		LSL GovlanOSErrorCode
		LSL GovlanOSErrorCode
		BSET DDRP,#$7C
		MOVB GovlanOSErrorCode,PTP
		MOVB GovlanOSErrorCode,GovlanOSLastErrorCode
		CMPA #$0
		BEQ CLRDATA
		MOVW #6000,GovlanOSErrorTickCount
		RTC
	 CLRDATA:
	 	CLRW GovlanOSErrorTickCount
	 	RTC
	 COUNTDOWNEERORCODE:
	 	LDX GovlanOSErrorTickCount
	 	CPX #$0
	 	BEQ ENDFUN
	 	DEX
	 	STX GovlanOSErrorTickCount
	 	CPX #$0
	 	BGT ENDFUN
	 	CLR GovlanOSErrorCode
	 ENDFUN:
	 	
	}
}
/*****************************************************
	CPU enters wait mode which could be restore from any interrupt
*******************************************************/
void GovlanOSGoToSleep(void)
{
	asm WAI;
}
/*****************************************************
	5ms per RTC Interrupt(16*10^6/(8*10^4)=200,1/200=5*10^-3)
*******************************************************/
void GovlanOSStartup(void)
{
	asm
	{
		MOVB #$80,CRGINT
		MOVB #$AF,RTICTL
		MOVB #$80,CRGINT
	}
}
/*****************************************************
	Set IPLL frequency
*******************************************************/
void GovlanOSIPLLStartup(UInt8 FIPLL)
{
	asm
	{
		LDAA #$08
		STAA CLKSEL					//Make IPLL off the line 
		MOVB #$07,REFDV
	IPLL32:
		CMPB #32
		BGT IPLL40 
		MOVB #$07,SYNR
		BRA STARTIPLL
	IPLL40:
		CMPB #40
		BGT IPLL64
		MOVB #$09,SYNR
		BRA STARTIPLL
	IPLL64:
		CMPB #64
		BGT  IPLL80
		MOVB #$4F,SYNR
		BRA STARTIPLL
	IPLL80:
		CMPB #80
		BGT  IPLL96
		MOVB #$53,SYNR
		BRA STARTIPLL
	IPLL96:
		CMPB #96
		BGT IPLL120
		MOVB #$D7,SYNR
		BRA STARTIPLL
	IPLL120:
		MOVB #$DD,SYNR
	STARTIPLL:
		BSET PLLCTL,#$40	
		NOP
		NOP
		BRCLR CRGFLG,#$08,*
		MOVB  #$00,POSTDIV
		BSET CLKSEL,#$80				//Make IPLL online
			
		BCLR IRQCR,#$40
	}
}
/*****************************************************
	Zero out memory block
*******************************************************/
void GovlanOSTaskArrInit(void)
{
	UInt8 n;
	for(n=0;n<GOVLANOSMAXTASKS;n++)
	{
		GovlanOSTaskArr[n].PTask = 0;
		GovlanOSTaskArr[n].Delay = 0;
		GovlanOSTaskArr[n].Period = 0;
		GovlanOSTaskArr[n].RunTask = 0;
		GovlanOSTaskArr[n].Cooperation = 0;
	}
}
/*****************************************************
	Feed dog
*******************************************************/
void GovlanOSFeedDog(void)
{
	asm
	{
		MOVB #$55,ARMCOP
		MOVB #$AA,ARMCOP
	}
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void GovlanOSTaskUpdate(void)
{
	UInt8 n;
	for(n=0;n<GOVLANOSMAXTASKS;n++)
	{
		if(GovlanOSTaskArr[n].PTask!=0)
		{
			if(GovlanOSTaskArr[n].Delay==0)
			{
				if(GovlanOSTaskArr[n].Cooperation==1)
				{
					GovlanOSTaskArr[n].RunTask+=1;
				}
				else
				{
					(*GovlanOSTaskArr[n].PTask)();
					if(GovlanOSTaskArr[n].Period==0)
					{
						GovlanOSDeleteTask(n);
					}
				}
				if(GovlanOSTaskArr[n].Period!=0)
				{
					GovlanOSTaskArr[n].Delay=GovlanOSTaskArr[n].Period;
				}
			}
			else
			{
				GovlanOSTaskArr[n].Delay-=1;
			}	
		}
	}
	asm BSET CRGFLG,#$80;
}
 #pragma  CODE_SEG  DEFAULT