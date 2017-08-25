/*****************************************************

   CAN0.h defines some neccessary data structrue.
   Copyright (c) WangYunXing,Govlan
               All rights reserved
  RAM SPACE:16*2+4*20+7+8=126BYTES             
 *****************************************************/
#ifndef _CAN0_H
#define _CAN0_H
#include"Include.h"
#define MAXMODULENUM 10
#define MAXMODULETYPE 2
/*****************************************************
	store data of one 
*******************************************************/
typedef union
{
	UInt32 data[1];
	struct 
	{
		UInt32 ModuleOutVol	:16;
		UInt32 ModuleOutCur :16;
	}Compts;
}ModuleOutput;
typedef union
{
	UInt16 data[10];
	struct 
	{
		UInt16 TotalVol;
		UInt16 TotalCur;
		UInt16 ModuleOperateSeq	:8;
		UInt16 ModuleSeq        :8;
		UInt16 ModuleType		:8;
		UInt16 ModuleSwitchCtl	:8;
		UInt16 ModuleConfigType : 8;
		UInt16 EFFIntFlag: 8;
		UInt16 TotalNum : 8;
		UInt16 : 8;
		UInt16 MaximumVol;
		UInt16 MinimumVol;
		UInt16 MaximumCur;
		UInt16 MinimumCur;
	}Compts;
}CAN0Operation;
typedef struct
{
	void(*Config)(void);
	void(*PowerOn)(void);
	void(*PowerOff)(void);
	void(*ExecuteTransmit)(void);
	UInt8 OverTimeFlag;
}PowerControl;
extern PowerControl AllModuleType[MAXMODULETYPE];
extern ModuleOutput AllModuleData[MAXMODULENUM];
extern CAN0Operation CAN0OperationBuff;
/*****************************************************
	Initialize CAN0
*******************************************************/
extern void CAN0Init(void);
/*****************************************************
	Calculate total output voltage and current
*******************************************************/
extern void CalculateTotalOutput(void);
/*****************************************************
	Convert CANID 
*******************************************************/
extern void CANIDConvert(CanMsgBuf * InID);
extern void CANIDDecode(CanMsgBuf *InID);
/*****************************************************
	Zero out memory
*******************************************************/
extern void AllModuleDataInit(void);
extern void AllModuleTypeInit(void);
extern void CAN0OperationBuffInit(void);
/*****************************************************
	Transmit data to MSCAN
*******************************************************/
extern void MSCAN0Transmit(CanMsgBuf *InCan);
/*****************************************************
	Module state control
*******************************************************/
extern void PowerStateControl(void);
extern CanMsgBuf  CANIDTest;
extern DataConvert ConvertVol;
extern DataConvert ConvertCur;
#endif