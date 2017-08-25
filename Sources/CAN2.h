/*****************************************************

	CAN2.h defines messages in BMS
	Copyright (c) WangYunXing,Govlan
	All rights reserved
	RAM Space:22*15+
*****************************************************/
#ifndef _CAN2_H
#define _CAN2_H
#include"Include.h"
/*****************************************************
	Messages defined in GT/2015
*******************************************************/
/*****************************************************
	Handshake messages no more than 8BYTES 
*******************************************************/
extern CanMsgBuf  CHM;
extern CanMsgBuf  BHM;
extern CanMsgBuf  CRM;
//BRM
/*****************************************************
	Config messages  no more than 8BYTES
*******************************************************/
//BCP
extern CanMsgBuf  CTS;
extern CanMsgBuf  CML;
extern CanMsgBuf  BRO;
extern CanMsgBuf  CRO;
/*****************************************************
	Charge messages no more than 8BYTES
*******************************************************/
extern CanMsgBuf BCL;
// BCS;
extern CanMsgBuf CCS;
extern CanMsgBuf BSM;
extern CanMsgBuf BMV;
extern CanMsgBuf BMT;
extern CanMsgBuf BSP;
extern CanMsgBuf BST;
extern CanMsgBuf CST;
/*****************************************************
	End messages  no more than 8BYTES
*******************************************************/
extern CanMsgBuf BSD;
extern CanMsgBuf CSD;
/*****************************************************
	Error messages  no more than 8BYTES
*******************************************************/
extern CanMsgBuf BEM;
extern CanMsgBuf CEM;
/*****************************************************
	Multi frame transmission
*******************************************************/
extern CanMsgBuf TPCMRTS;
extern CanMsgBuf TPCMCTS;
extern CanMsgBuf TPCMDT;
/*****************************************************
	Initialize MSCAN2 
*******************************************************/
extern void CAN2Init(void);
/*****************************************************
	MSCAN2 transmit
*******************************************************/
extern void MSCAN2Transmit(CanMsgBuf *InCan);
/*****************************************************
	Initialize CAN ID
*******************************************************/
extern void BMSCANIDInit(void);
/*****************************************************
	Initialize data buffer
*******************************************************/
extern void BMSMessageDataInit(void);
/*****************************************************
	Receive message 
*******************************************************/
extern void BMSReceive(void);
/*****************************************************
	Load command
*******************************************************/
extern void CHMLoad(void);
extern void CRMLoad(void);
extern void CTSLoad(void);
extern void CMLLoad(void);
extern void CROLoad(void);
extern void CCSLoad(void);
extern void CSTLoad(void);
extern void CSDLoad(void);
extern void CEMLoad(void);
extern void TPCMCTSLoad(void);
extern void TPCMRTSEndLoad(void);
extern void CAN2Transmit250ms(void);
extern void CAN2Transmit500ms(void);
extern void CAN2Transmit50ms(void);
extern void CAN2Transmit10ms(void);

/*****************************************************
	Define data structure to operate message
*******************************************************/
typedef union 
{
	UInt8 data[3];
	struct
	{
		UInt8	VerByte1;
		UInt8	VerByte2;
		UInt8	VerByte3;
	}Compts;
}CHMStruct;
extern CHMStruct CHMData; //Associate to CHM
typedef union
{
	UInt16 data[1];
	struct
	{
		UInt16 MaxAllowVol;
	}Compts;
}BHMStruct;
extern BHMStruct BHMData;//Associate to BHM
typedef union 
{
	UInt8 data[8];
	struct 
	{
		UInt8 IdentificationResult;
		UInt8 ChargingPileNum[4];
		UInt8 AreaCode[3];
	}Compts;
}CRMStruct;
extern CRMStruct CRMData;//Associate to CRM
typedef union
{
	UInt8 data[51];
	struct 
	{
		UInt8 Version[3];
		UInt8 BatType;
		UInt16 Capacity;
		UInt16 TotalVol;
		UInt8  Manufacturer[4];
		UInt8  BatSerialNum[4];
		UInt16  Year;
		UInt8  Month;
		UInt8  Day;
		UInt32 CHargingTimes : 24;
		UInt32 PropertyFlag : 8;
		UInt8  Reserve;
		UInt8  VIN[17];
		UInt8  BMSVersion[8];
		UInt8  RecFinish;
	}Compts;
}BRMStruct;
extern BRMStruct BRMData;//Associate to BRM
typedef union 
{
	UInt8 data[14];
	struct 
	{
		UInt16 MaxMonomerAllowVol;
		Int16 MaxAllowCur;
		UInt16 NominalEny;
		UInt16 MaxAllowVol;
		Int8  MaxAllowTemp;
		UInt16  SOC;
		UInt16 TotalVol;
		UInt8 RecFinish;
	}Compts;
}BCPStruct;
extern BCPStruct BCPData;//Associate to BCP
typedef union 
{
	UInt8 data[7];
	struct 
	{
		UInt8 Second;
		UInt8 Minute;
		UInt8 Hour;
		UInt8 Day;
		UInt8 Month;
		UInt16 Year;
	}Compts;
}CTSStruct;
extern CTSStruct CTSData;
typedef union 
{
	UInt16 data[4];
	struct
	{
		UInt16	MaxOutputVol;
		UInt16  MinOutputVol;
		Int16   MaxOutputCur;
		Int16   MinOutputCur;
	}Compts;
}CMLStruct;
extern CMLStruct CMLData;
typedef union 
{
	UInt8 data[1];
	struct 
	{
		UInt8 IdentificationResult;
	}Compts;
}BROStruct;
extern BROStruct BROData;
typedef union 
{
	UInt8 data[1];
	struct 
	{
		UInt8 IdentificationResult;
	}Compts;
}CROStruct;
extern CROStruct CROData;
typedef union 
{
	UInt8 data[5];
	struct 
	{
		UInt16 RequestVol;
		Int16 RequestCur;
		UInt8  ChargMode;
	}Compts;
}BCLStruct;
extern BCLStruct BCLData;
typedef union 
{
	UInt8 data[11];
	struct 
	{
		UInt16 MeasurVol;
		Int16 MeasurCur;
		UInt16 MaxMonomer ;
		UInt8 GroupNum ;
		UInt8  SOCNow;
		UInt16 SurplusTime;
		UInt8 RecFinish;
	}Compts;
}BCSStruct;
extern BCSStruct BCSData;
typedef union 
{
	UInt8 data[7];
	struct 
	{
		UInt16  OutputVol;
		Int16  OutputCur;
		UInt16  TotalChargTime;
		UInt8   ChargingPermission : 2;
		UInt8 : 6;
	}Compts;
}CCSStruct;
extern CCSStruct CCSData;
typedef union 
{
	UInt8 data[8];
	struct 
	{
		UInt16 HighestVolNum;
		Int8 HighestTemp;
		UInt8 HighestTempCheckNum;
		Int8 LowestTemp;
		UInt8 LowestTempCheckNum;
		UInt8 MonomerVolFlag : 2;
		UInt8 TotalSocFlag : 2;
		UInt8 OverCurrentFlag : 2;
		UInt8 OverTempFlag : 2;
		UInt8 InsultStateFlag : 2;
		UInt8 ConnectionStateFlag : 2;
		UInt8 ChargingPermission : 2;
		UInt8 : 2;
	}Compts;
}BSMStruct;
extern BSMStruct BSMData;
typedef union 
{
	UInt8 data[4];
	struct 
	{
		UInt8 TargetSOC :2;
		UInt8 TargetTotalVol : 2;
		UInt8 TargetMonomerVol : 2;
		UInt8 ChargingPileTer : 2;

		UInt16 Insult : 2;
		UInt16 ConnectorOverTemp : 2;
		UInt16 BMSAndConOverTemp : 2;
		UInt16 Connector : 2;
		UInt16 BatGroupOverTemp : 2;
		UInt16 HighVolRelay : 2;
		UInt16 CheckPointTwo : 2;
		UInt16 Other : 2;

		UInt8 OverCur : 2;
		UInt8 OverVol : 2;
		UInt8 : 4;
	}Compts;
}BSTStruct;
extern BSTStruct BSTData;
typedef union 
{
	UInt8 data[4];
	struct 
	{
		UInt8  NormalTer : 2;
		UInt8  ManualTer : 2;
		UInt8  FaultTer : 2;
		UInt8  BMSActTer : 2;

		UInt16 OverTemp :2;
		UInt16 Connector : 2;
		UInt16 InternalOverTemp : 2;
		UInt16 NoEnergyTran : 2;
		UInt16 Emergency : 2;
		UInt16 Other : 2;
		UInt16 : 4;

		UInt8 MismatchCur :2;
		UInt8 MismatchVol : 2;
		UInt8 : 4;
	}Compts;
}CSTStruct;
extern CSTStruct CSTData;
typedef union 
{
	UInt8 data[7];
	struct
	{
		UInt8 TerSoc;
		UInt16 LowestMonomerVol;
		UInt16 HighesMonomertVol;
		Int8 LowestMonomerTemp;
		Int8 HighestMonomerTemp;
	}Compts;
}BSDStruct;
extern BSDStruct BSDData;
typedef union 
{
	UInt8 data[8];
	struct 
	{
		UInt16 TotalChargTime;
		UInt16 OutputEnegy;
		UInt8  PileNum[4];
	}Compts;
}CSDStruct;
extern CSDStruct CSDData;
typedef union 
{
	UInt8 data[4];
	struct 
	{
		UInt8 UnreadyCRMOverTime : 2;
		UInt8 ReadyCRRMOverTime : 2;
		UInt8 : 4;
		UInt8 CRMOrCTSOverTime : 2;
		UInt8 CROOvertime : 2;
		UInt8 : 4;
		UInt8 CCSOverTime : 2;
		UInt8 CSTOverTime : 2;
		UInt8 : 4;
		UInt8 CSDOverTime : 2;
		UInt8 : 6;
	}Compts;
}BEMStruct;
extern BEMStruct BEMData;
typedef union 
{
	UInt8 data[4];
	struct 
	{
		UInt8 BRMOverTime : 2;
		UInt8 : 6;

		UInt8 BCPOverTime : 2;
		UInt8 BROOVerTime : 2;
		UInt8 : 4;

		UInt8 BCSOverTime : 2;
		UInt8 BCLOverTime : 2;
		UInt8 BSTOverTime : 2;
		UInt8 : 2;
		UInt8 BSDOverTime :2;
		UInt8 : 6;
	}Compts;
}CEMStruct;
extern CEMStruct CEMData;
typedef union 
{
	UInt8 data[9];
	struct 
	{
		UInt8 ControlType;
		UInt16 MessageTotalLen;
		UInt8 TotalPackNum;
		UInt8 Reserve;
		UInt32 PGN;
	}Compts;
}TPCMRTSStruct;
extern TPCMRTSStruct TPCMRTSData;
typedef union
{
	UInt8 data[9];
	struct 
	{
		UInt8 ControlType;
		UInt16 NeedPacketNum;
		UInt8  StartSeq;
		UInt16 Reserve;
		UInt32 PGN;
	}Compts;
}TPCMCTSStruct;
extern TPCMCTSStruct TPCMCTSData;
typedef union 
{
	UInt8 data[8];
	struct 
	{
		UInt8 SerialNum;
		UInt8 Reciever[7];
	}Compts;
}TPCMDTStruct;
extern TPCMDTStruct TPCMDTData;
#endif