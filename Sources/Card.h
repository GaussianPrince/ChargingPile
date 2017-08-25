#ifndef _CARD_H
#define _CARD_H
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
	UInt8 data[15];
	struct 
	{
		UInt8	ReadUIDSuccessfully : 1;
		UInt8	ReadMoneySuccessfully : 1;
		UInt8	ReadUserIDSuccessfully : 1;
		UInt8	WriteBlock2Successfully : 1;
		UInt8	WriteBlock8Successfully : 1;
		UInt8	CardEnable : 1;
		UInt8	PayByCardStart : 1;
		UInt8 : 1;
		UInt8   CardSystate;
		UInt8	CardCode;
		UInt8	CardPermission;
		UInt32	UserID;
		UInt32  CardID;
		UInt32	ResidualMoney;
	}Compts;
}CardOperat;
#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
extern QueryLabel	 QueryLabelCmd;
extern M1Read2		 M1ReadCmd2;
extern M1Read8		 M1ReadCmd8;
extern M1Write2		 M1WriteCmd2;
extern M1Write8		 M1WriteCmd8;
extern CardOperat	 CardOperatBuff;
extern UInt16		 CardCheckTem;
#pragma DATA_SEG DEFAULT
extern DataConvert	 UserMoneyConvert;
extern DataConvert	 CardIDConvert;
extern DataConvert	 UserIDConvert;
extern void SCI5SendN(UInt8 * far InData, UInt8 Len);
extern void SCI5Init(void);
extern UInt16 CardCalCRC(UInt8 *far UnProcess, UInt8 Len);
extern void CardAnalysis(void);
extern void CardStateControl(void);
#endif
