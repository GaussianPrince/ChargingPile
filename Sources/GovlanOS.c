#include "GovlanOS.h"
#include "GovlanOSCPU.h"
//#define  RTCDEBUG
UInt8 GovlanOSErrorCode;
UInt16 CPUStaReg;	//Store CCR 
UInt16 CPUSpReg;
UInt8  OSRunning;    //Indicate whether OS is running
UInt8  OSNesting;	//See if there has been interrupt nesting
UInt32 AllCycles;    //Increase one every tick
UInt32 FreeCyles;	//Increase one every idle task
UInt32 ResumeCycles;
UInt8 GovlanOSErrorCode;		//Error code 
UInt8  OSIdleStk[128];		//Stack space of idle task
UInt8  OSPriorityHigh;		//Record highest priority
UInt8  OSStaticInc ;
UInt8  OSBitMapGroup;
UInt8  OSBitMapOne[4];		//First level bitmap
UInt8  OSBitMapTwo[32];		//Second level bitmap
OSTCB *OSTaskCur;
OSTCB *OSTaskHigh;
OSTCB *OSTaskUsedHeader;
OSTCB *OSTaskFreeHeader;
OSTCB OSTCBTable[MAXTASK];
OSTCB *OSTCBReadyTable[MAXTASK];
UInt32 TmpRec;
OSTaskAddr OSTaskAddrTable[MAXTASK];
UInt8 x, y, z, w;
#ifdef RTCDEBUG
UInt8 SecondRec = 0;
UInt8 SecondCounter = 0;
#endif // RTCDEBUG

/*****************************************************
const variable stored in flash to accelerate search process

UInt8 i,j,Tmp,Pos;
OSMapArr[0]=0;
for(i=0;i<255;i++)
{
Tmp=i;
Pos=0;
for(j=0;j<8;j++)
{
if(Tmp&0x01)
{
OSMapArr[Tmp]=Pos;
}
Tmp=Tmp>>1;
Pos++;
}
}
OSMapArr[255]=0;
*******************************************************/
#pragma  CONST_SEG CONST_DISTRIBUTE
const UInt8  OSMapArr[] = {
	0,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0
};//Find highest priority
const UInt8 OSBitSetArr[] = {
	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80
};//Set corresponding bit
#pragma  CONST_SEG DEFAULT
static void OSIPLLInit(UInt8 IPLL)
{
	asm
	{
		LDAA #$08
		STAA CLKSEL					//Make IPLL off the line 
		MOVB #$07,REFDV
		IPLL32 :
	CMPB #32
		BGT IPLL40
		MOVB #$07,SYNR
		BRA STARTIPLL
		IPLL40 :
	CMPB #40
		BGT IPLL64
		MOVB #$09,SYNR
		BRA STARTIPLL
		IPLL64 :
	CMPB #64
		BGT  IPLL80
		MOVB #$4F,SYNR
		BRA STARTIPLL
		IPLL80 :
	CMPB #80
		BGT  IPLL96
		MOVB #$53,SYNR
		BRA STARTIPLL
		IPLL96 :
	CMPB #96
		BGT IPLL120
		MOVB #$D7,SYNR
		BRA STARTIPLL
		IPLL120 :
	MOVB #$DD,SYNR
		STARTIPLL :
	BSET PLLCTL,#$40
		NOP
		NOP
		BRCLR CRGFLG,#$08,*
		MOVB  #$00,POSTDIV
		BSET CLKSEL,#$80				//Make IPLL on line

		BCLR IRQCR,#$40
	}
}
static void OSRTCInit(void)
{
	asm
	{
		MOVB #$80,CRGINT
		MOVB #$AF,RTICTL
		MOVB #$80,CRGINT
	}
}
static UInt8 * OSStkInit(void(*InTask)(void),UInt8 *StkTop)
{
	UInt8  *BStk;

	TmpRec = (UInt32)(&OSIDleTask);
	BStk = (UInt8*)StkTop;
	*--BStk = (UInt8)(((UInt32)TmpRec >> 8) & 0xFF);
	*--BStk = (UInt8)(((UInt32)TmpRec >> 16)&0xFF);
	*--BStk = (UInt8)((UInt32)TmpRec & 0xFF);
	*--BStk = (UInt8)(((UInt32)InTask >> 8) & 0xFF);
	*--BStk = (UInt8)(((UInt32)InTask >> 16)&0xFF);
	*--BStk = 0x44;
	*--BStk = 0x33;
	*--BStk = 0x22;
	*--BStk = 0x11;
	*--BStk = 0xAA;
	*--BStk = 0xBB;
	*--BStk = 0xC0;
	*--BStk = 0x00;
	*--BStk = EPAGE;
	*--BStk = RPAGE;
	*--BStk = (UInt8)((UInt32)InTask & 0xFF);
	*--BStk = GPAGE;
	return ((UInt8*)BStk);
}
static void OSTCBTableInit(void)
{
	UInt8 n;
	OSTCB *TmpPtr;
	OSTaskUsedHeader = (OSTCB*)(&OSTCBTable[0]);
	OSTaskFreeHeader = (OSTCB*)(&OSTCBTable[0]);
	TmpPtr = OSTaskUsedHeader;
	for (n = 0; n < MAXTASK; n++)
	{
		TmpPtr->Delay = 0;
		TmpPtr->Period = 0;
		TmpPtr->OSTaskStkStartAddr = NULL;
		TmpPtr->OSTaskStkTopPtr = NULL;
		TmpPtr->WakeUpFlag = 0;
		if (n < MAXTASK - 1)
		{
			TmpPtr->Next = (OSTCB*)(&OSTCBTable[n + 1]);
			TmpPtr = TmpPtr->Next;
		}
		else
		{
			TmpPtr->Next = NULL;
		}
		OSTCBReadyTable[n] = &OSTCBTable[n];
	}
}
void OSIDleTask(void)
{
	if (OSRunning == 1)
	{
		if (OSTaskCur != OSTaskUsedHeader)
		{
			asm TFR SP, D;
			asm STD CPUSpReg;
			asm LDS #$2100;
			OSTaskCur->OSTaskStkTopPtr = OSStkInit(OSTaskAddrTable[OSPriorityHigh], (UInt8*)CPUSpReg);
			x = (OSTaskCur->Priority >> 6);
			y = ((OSTaskCur->Priority >> 3) & 0x07);
			z = (OSTaskCur->Priority & 0x07);
			w = (OSTaskCur->Priority >> 3);
			OSBitMapTwo[w] &= ~OSBitSetArr[z];
			if (OSBitMapTwo[w] == 0)
				OSBitMapOne[x] &= ~OSBitSetArr[y];
			if (OSBitMapOne[x] == 0)
			{
				OSBitMapGroup &= ~OSBitSetArr[x];
			}
			x = OSMapArr[OSBitMapGroup];
			y = OSMapArr[OSBitMapOne[x]];
			z = OSMapArr[OSBitMapTwo[y]];
			OSPriorityHigh = (x << 6) + (y << 3) + z;
			OSTaskHigh = OSTCBReadyTable[OSPriorityHigh];
			if ((OSTaskHigh == OSTaskUsedHeader))
			{
				OSTaskCur = OSTaskHigh;
				++FreeCyles;
			}
			else
			{
			//	if(OSNesting==0)
				++AllCycles;
				OSCtxSw();
			}
		}
	}
	asm CLI;
	while (1);//Do nothing
}
void OSInit(void)	//Initialize hardware
{
	OSIPLLInit(120);
	OSRTCInit();
	MyMemset(OSIdleStk, 0, 128);
	MyMemset(OSBitMapOne, 0, 4);
	MyMemset(OSBitMapTwo, 0, 32);
	OSTCBTableInit();
}
void OSFeedDog(void)	//Feed dog 
{
	OSCRITICALENTRY();	//Prevent interruption
	FEEDDOG();			//Write sequence
}


void OSStart(void)
{
	if (OSRunning == 0)
	{
		OSCRITICALENTRY();
		OSTaskHigh = OSTaskUsedHeader;
		OSTaskCur = OSTaskUsedHeader;
		OSPriorityHigh = 0;
		OSCRITICALEXIT();
		OSRunIdleTask();
	}
}
void OSAddTask(void(*InTask)(void), UInt8 *StkPtr, UInt8 *StkStartAddr, UInt16 Delay, UInt16 Period)
{
	if (OSNesting == 0)
	{
		OSCRITICALENTRY();
		if (OSTaskFreeHeader != NULL)
		{
			OSTaskFreeHeader->OSTaskStkTopPtr = OSStkInit(InTask, StkPtr);
			OSTaskFreeHeader->OSTaskStkStartAddr = StkStartAddr;
			OSTaskFreeHeader->Delay = Delay;
			OSTaskFreeHeader->Period = Period;
			OSTaskFreeHeader->WakeUpFlag = 1;
			OSTaskFreeHeader->Priority = OSStaticInc++;
			OSTaskFreeHeader = OSTaskFreeHeader->Next;
		}
		OSCRITICALEXIT();
	}
}
void OSSchedule(void)
{
	OSTCB *TraPtr;

		//AllCycles++;
	#ifdef RTCDEBUG

		if (SecondCounter > 198)
		{
			SecondCounter = 0;
			if (SecondRec > 58)
				SecondRec = 0;
			else
				SecondRec++;
		}
		else
			SecondCounter++;
	#endif // RTCDEBUG
		if (OSNesting > 0)
		{
			--OSNesting;
		}
		if (OSNesting == 0)
		{
			for (TraPtr = OSTaskUsedHeader->Next; TraPtr != OSTaskFreeHeader;)
			{
				if (TraPtr->WakeUpFlag == 1)
				{
					if (TraPtr->Delay == 0)
					{
						x = (TraPtr->Priority >> 6);
						y = ((TraPtr->Priority >> 3) & 0x07);
						z = ((TraPtr->Priority) & 0x07);
						OSBitMapGroup |= OSBitSetArr[x];
						OSBitMapOne[x] |= OSBitSetArr[y];
						OSBitMapTwo[TraPtr->Priority >> 3] |= OSBitSetArr[z];
						TraPtr->Delay = TraPtr->Period;
					}
					else
					{
						TraPtr->Delay--;
					}
				}
				TraPtr = TraPtr->Next;
			}
			x = OSMapArr[OSBitMapGroup];
			y = OSMapArr[OSBitMapOne[x]];
			z = OSMapArr[OSBitMapTwo[y]];
			OSPriorityHigh = ((x << 6) + (y << 3) + z);
			OSTaskHigh = OSTCBReadyTable[OSPriorityHigh];
			if (OSTaskCur != OSTaskHigh)
				OSTickCtxSw();
		}
}