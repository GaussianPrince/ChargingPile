#ifndef _SCI4_H
#define	_SCI4_H
#include "Include.h"
#define  NETFRAMECMDINDEX	16
#define	 NETFRAMEDATAINDEX	17
typedef union 
{
	UInt8 data[519];
	struct 
	{
		UInt8	NetConfigSwitch;
		UInt8	NetFrameBuff[256];
		UInt8	NetFrameIndex;
		UInt8	NetDataBuff[256];
		UInt8	NetDataLen;
		UInt8	NetCheckNum;
		UInt8	NetOverTimeCounter;
		UInt8	NetHeartFrequence;
		UInt8	NetHasRecFaultFlag : 1;
		UInt8	NetHasRecCCNFlag : 1;
		UInt8 : 6;
	}Compts;
}SCI4Operat;

#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
extern  SCI4Operat SCI4OperatBuff;
extern  UInt8		ChargingEnd;
#pragma DATA_SEG DEFAULT
extern void SCI4Init(void);
extern void SCI4SendN(UInt8 *far InData, UInt8 Len);
extern void SCI4Analysis(void);
extern void SCI4StateControl(void);
#endif