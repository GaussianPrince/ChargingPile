#ifndef _GOVLANOSENF_H
#define _GOVLANOSENF_H
#define  MAXTASK   64
#define  GOVLANOSCAN0OVERTIME  1
#define  GOVLANOSSCI1CONFIGOVERTIME 2
#define  OSCRITICALENTRY()  {CPUStaReg=CPUSRSave();}
#define  OSCRITICALEXIT()   {CPUSRRestore(CPUStaReg);}
#define  OSSWI()			  {asm SWI;}
#define  FEEDDOG()			{asm MOVB #$55, ARMCOP; asm MOVB #$AA, ARMCOP;}
#include "Include.h"
extern  UInt8 GovlanOSErrorCode;		//Error code 
extern  UInt16 CPUStaReg;	//Store CCR 
extern  UInt16 CPUSpReg;
extern  UInt8  OSRunning;    //Indicate whether OS is running
extern  UInt8  OSNesting;	//See if there has been interrupt nesting
extern  UInt32 AllCycles;    //Increase one every tick
extern  UInt32 FreeCyles;	//Increase one every idle task
extern  UInt8  OSIdleStk[128];		//Stack space of idle task
extern  UInt8  OSPriorityHigh;		//Record highest priority
extern  UInt8  OSStaticInc ;
/*****************************************************
		Ready bitmap
*******************************************************/
extern UInt8  OSBitMapGroup;
extern UInt8  OSBitMapOne[4];		//First level bitmap
extern UInt8  OSBitMapTwo[32];		//Second level bitmap


extern OSTaskAddr OSTaskAddrTable[MAXTASK];
/*****************************************************
	Define task control block
*******************************************************/
typedef struct _OSTCB 
{
	UInt8 *OSTaskStkTopPtr;			//Stack Pointer
	UInt8 *OSTaskStkStartAddr;		//Start address
	UInt16 Period;					//How many cycles run once?
	UInt16 Delay;					//Count
	UInt8  Priority;					//Record corresponding priority
	UInt8  WakeUpFlag;				//Wake up a sleeping task
	struct _OSTCB *Next;			//Point to next node
}OSTCB;

extern OSTCB *OSTaskCur;	
extern OSTCB *OSTaskHigh;
extern OSTCB  *OSTaskUsedHeader;
extern OSTCB *OSTaskFreeHeader;
extern OSTCB OSTCBTable[MAXTASK];
extern OSTCB  *OSTCBReadyTable[MAXTASK];
extern UInt32 TmpRec;
extern void	 		OSIDleTask(void);
extern void	 		OSSchedule(void);
extern void	 		OSAddTask(void(*InTask)(void), UInt8 *StkPtr, UInt8 *StkStartAddr, UInt16 Delay, UInt16 Period);
extern void	 		OSStart(void);
extern void	 		OSFeedDog(void);
extern void	 		OSInit(void);
extern void	 		OSIDleTask(void);
#endif // _GOVLANOSENF_H