#ifndef _SCI1_H
#define _SCI1_H
#include "Include.h"
#define  MAXMETERTYPE 2

typedef struct
{
	void(*SCI1Config)(void);
	void(*SCI1Transmit)(void);
	void(*SCI1Analysis)(void);
	UInt8 OverTimerCounter;
}SCI1StaMac;

typedef union 
{
	UInt32 data[3];
	struct 
	{
		UInt32 EngyVal;
		UInt32 SCI1SwitchCtl : 8;
		UInt32 SCI1MeterType : 8;
		UInt32 SCI1RecSendSwitch : 8;// 1  means sending data and 0 means receiving data 
		UInt32 SCI1ConfigSeq	: 8;
		UInt32 SCI1LoopFlag : 8;	//For future use
		UInt32 : 24;
	}Compts;
}SCI1Operation;

extern SCI1StaMac SCI1StaMacBuff[MAXMETERTYPE];
extern SCI1Operation SCI1OperationBuff;
extern void  SCI1OperationBuffInit(void);
extern void  SCI1StaMacBuffInit(void);
extern void  SCI1Send(UInt8 *InData,UInt8 Len);
extern void  SCI1Init(void);
extern void  SCI1ChangeTransmitDirection(void);
extern void  SCI1StateControl(void);
#endif
