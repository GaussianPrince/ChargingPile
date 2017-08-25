/*****************************************************

   GovlanOSCore.h defines data structure and function of core.  
   Copyright (c) WangYunXing,Govlan
               All rights reserved
   RAM SPACE:9*20+1+3=184BYTE
 *****************************************************/
#ifndef _GOVLANOSCORE_H
#define _GOVLANOSCORE_H
#define GOVLANOSMAXTASKS  20					//Define the maximum tasks of GovlanOS
#define GOVLANOSTOOMANYTASKS  31		
#define GOVLANOSRETURNERRORNULL	30
#define GOVLANOSRETURNENORMAL	29	
#define  GOVLANOSSCI1CONFIGOVERTIME 28
#define  GOVLANOSCAN0OVERTIME    26
#include"Include.h"
/*****************************************************
	Store in local ram for rapid access.
	Total memory per task is 9 bytes.
*******************************************************/
typedef volatile struct  __GovlanOSTask
{
    void (*PTask)(void);
	UInt16 Delay; 							//Delay until the function will be run.
	UInt16 Period;							//Interval between subsequent 
	UInt8  RunTask;							//Incremented (by scheduler) when task is to be execute
	UInt8  Cooperation;						//Indicate which of type is using
}GovlanOSTask;
/*****************************************************
	Global variable used in scheduler
*******************************************************/
extern GovlanOSTask GovlanOSTaskArr[GOVLANOSMAXTASKS];  		//Array storing tasks
extern UInt8 GovlanOSErrorCode;							 	//Used to display the error code
/*****************************************************
	Initialize RTC
*******************************************************/
extern void GovlanOSStartup(void);
/*****************************************************
	Load IPLL
*******************************************************/
extern void GovlanOSIPLLStartup(UInt8 FBus);
/*****************************************************
	Core scheduler functions
*******************************************************/
extern void GovlanOSDispatchTasks(void);
extern void GovlanOSReportStatus(void);
extern void GovlanOSTaskArrInit(void);
extern void GovlanOSFeedDog(void);
extern UInt8 GovlanOSAddTask(void(*InTask)(void),const UInt16 Delay,const UInt16 Period,UInt8 InCooperation);
extern UInt8 GovlanOSDeleteTask(const UInt8 Index);
#endif