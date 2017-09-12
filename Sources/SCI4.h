#ifndef _SCI4_H
#define	_SCI4_H
#include "Include.h"
#define  NETFRAMECMDINDEX	16
#define	 NETFRAMEDATAINDEX	17
#define  SCI4ENDTEST 
typedef union 
{
	UInt8 data[520];
	struct 
	{
		UInt8	NetConfigSwitch;
		UInt8	NetFrameBuff[256];
		UInt8	NetFrameIndex;
		UInt8	NetDataBuff[256];
		UInt8	NetDataLen;
		UInt8	NetCheckNum;
		UInt8	NetState;
		UInt8	NetOverTimeCounter;
		UInt8	NetHeartFrequence;
		UInt8	NetHasRecFaultFlag : 1;
		UInt8	NetHasRecCCNFlag : 1;
		UInt8	NetHasRecStartFlag : 1;
		UInt8	NetOldCCNRec : 1;
		UInt8   NetTimeSyn : 1;
		UInt8   NetPriceSyn : 1;
		UInt8   NetSerSyn : 1;
		UInt8	NetSynAll: 1;
	}Compts;
}SCI4Operat;

#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
extern  SCI4Operat SCI4OperatBuff;
extern  UInt16		SurplusTime;
#pragma DATA_SEG DEFAULT
extern  UInt32      CardChargingDuration;
extern  UInt8		ChargingEnd;
#ifdef SCI4ENDTEST
extern  UInt8       SCI4EndCounter;
#endif // SCI4ENDTEST

extern void SCI4Init(void);
extern void SCI4SendN(UInt8 *far InData, UInt8 Len);
extern void SCI4Analysis(void);
extern void SCI4StateControl(void);
#endif