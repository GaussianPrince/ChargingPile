#ifndef  _IOBUFFER_H
#define  _IOBUFFER_H
#include"Include.h"
typedef struct _MemoryList
{
	struct  _MemoryList *Next;
	UInt8   DataSize;
	UInt8   RecvFinishedFlag;
}MemoryList;
typedef struct
{
	MemoryList *FreeHeader;
	MemoryList *Front;
	MemoryList *Rear;
	UInt8  BlockNum;
}HashTable;
typedef union 
{
	UInt8 data[15];
	struct 
	{
		UInt8 EnQueueReturnCode[5];
		UInt8 ExQueueReturnCode[5];
		UInt8 FullFlag[5];
	}Compts; 
}IOBufferMonitor;
#pragma DATA_SEG __RPAGE_SEG     RAMF0_T
extern HashTable IOBuffer[5];
extern IOBufferMonitor IOBufferMonitorBuffer;
extern UInt8 HMIArr[512];
extern UInt8 CardArr[512];
extern UInt8 NetArr[512];
extern UInt8 InsultArr[512];
extern UInt8 VolmeterArr[512];
#pragma DATA_SEG DEFAULT
extern UInt8 IsFull(UInt8 Type);
extern UInt8 IsEmpty(UInt8 Type);
extern UInt8 EnQueue(UInt8 Type);
extern UInt8 ExQueue(UInt8 Type);
extern void IOBufferInit(void);
extern void MemoryZeroOut(void);
extern void IOBufferMonitorBufferInit(void);
#endif  
