#ifndef _CARD_H
#define _CARD_H
//#define  PAYCOUNTER
#include "Include.h"
typedef union 
{
	UInt8 data[12];
	struct 
	{
		UInt16  FrameHeader;
		UInt8	FrameLen;
		UInt16  SourceAddr;
		UInt16  DestinAddr;
		UInt8	CmdCode;
		UInt8   Reserve;
		UInt8   Parameter;
		UInt16  CRC;
	}Compts;
}QueryLabel;
typedef union 
{
	UInt8 data[20];
	struct 
	{
		UInt16	FrameHeader;
		UInt8	FrameLen;
		UInt16  SourceAddr;
		UInt16  DestinAddr;
		UInt8	CmdCode;
		UInt8	Reserve;
		UInt8	KeyType;
		UInt8	Key[6];
		UInt8	BlockAddr;
		UInt8	Num;
		UInt16  CRC;
	}Compts;
}M1Read2;
typedef union
{
	UInt8 data[20];
	struct
	{
		UInt16	FrameHeader;
		UInt8	FrameLen;
		UInt16  SourceAddr;
		UInt16  DestinAddr;
		UInt8	CmdCode;
		UInt8	Reserve;
		UInt8	KeyType;
		UInt8	Key[6];
		UInt8	BlockAddr;
		UInt8	Num;
		UInt16  CRC;
	}Compts;
}M1Read8;
typedef union 
{
	UInt8 data[36];
	struct 
	{
		UInt16  FrameHeader;
		UInt8	FrameLen;
		UInt16	SourceAddr;
		UInt16	DestinAddr;
		UInt8	CmdCode;
		UInt8	Reserve;
		UInt8   KeyType;
		UInt8   Key[6];
		UInt8	BlockAddr;
		UInt8	Num;
		UInt8   BlockData[16];
		UInt16	CRC;
	}Compts;
}M1Write2;
typedef union
{
	UInt8 data[36];
	struct
	{
		UInt16  FrameHeader;
		UInt8	FrameLen;
		UInt16	SourceAddr;
		UInt16	DestinAddr;
		UInt8	CmdCode;
		UInt8	Reserve;
		UInt8   KeyType;
		UInt8   Key[6];
		UInt8	BlockAddr;
		UInt8	Num;
		UInt8   BlockData[16];
		UInt16	CRC;
	}Compts;
}M1Write8;
typedef union 
{
	UInt8 data[30];
	struct 
	{
		UInt8  QueryInf : 1;
		UInt8  PerOp : 1;
		UInt8  FeeOp : 1;
		UInt8  PayByCardStart : 1;
		UInt8 : 4;
		UInt8  CardWaitHome;
		UInt8  CardSystate;
		UInt8  CardSystateOld;
		UInt8  Permission;
		UInt8  PermissionOld;
		UInt32 UserID;
		UInt32 UserIDOld;
		UInt32 CardID;
		UInt32 CardIDOld;
		UInt32 ResidualMoney;
		UInt32 ResidualMoneyOld;
	}Compts;
}CardOperation;
#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
extern QueryLabel	 QueryLabelCmd;
extern M1Read2		 M1ReadCmd2;
extern M1Read8		 M1ReadCmd8;
extern M1Write2		 M1WriteCmd2;
extern M1Write8		 M1WriteCmd8;
extern CardOperation	 CardOperationBuff;
extern UInt16		CardCheckTem;
extern UInt32		CostCalTmp;
extern UInt8        CardMutex;
extern UInt8		FaultPay;
extern UInt8		FaultEcho;
#ifdef PAYCOUNTER
extern UInt8		PayCounter;
#endif
#pragma DATA_SEG DEFAULT
extern DataConvert	 UserMoneyConvert;
extern DataConvert	 CardIDConvert;
extern DataConvert	 UserIDConvert;
extern void SCI5SendN(UInt8 * far InData, UInt8 Len);
extern void SCI5Init(void);
extern UInt16 CardCalCRC(UInt8 *far UnProcess, UInt8 Len);
extern void MyMemsetFar(UInt8 *far InData, UInt8 Val, UInt8 Len);
extern void CardAnalysis(void);
extern void CardStateControl(void);
#endif
