/*****************************************************

	Achieve core operation of power module
	Copyright (c) WangYunXing,Govlan
	All rights reserved

*****************************************************/
#include"Include.h"
#pragma MESSAGE DISABLE C5917 
#pragma MESSAGE DISABLE C5919
/*****************************************************
	Operating buffer
*******************************************************/
InfyPowerOperation InfyPowerOperationBuff;
CanMsgBuf InfyPowerOnMsg;
CanMsgBuf InfyPowerOffMsg;
CanMsgBuf InfyVolCurSetMsg;
CanMsgBuf InfyModuleNum;
CanMsgBuf InfyModuleNumReply;
CanMsgBuf InfyModuleOutput[MAXMODULENUM];
CanMsgBuf InfyModuleReply[MAXMODULENUM];
/*****************************************************
	Zero out memory 
*******************************************************/
void InfyPowerOperationBuffInit(void)
{
	UInt8 n;
	for (n = 0; n < 2; n++)
	{
		InfyPowerOperationBuff.data[n] = 0;
	}
}
/*****************************************************
	Read number of module 
*******************************************************/
static void InfyConfigDataLoad(void)
{
	asm
	{
		CLRA
		STAA InfyModuleNum.Data[0]
		STAA InfyModuleNum.Data[1]
		STAA InfyModuleNum.Data[2]
		STAA InfyModuleNum.Data[3]
		STAA InfyModuleNum.Data[4]
		STAA InfyModuleNum.Data[5]
		STAA InfyModuleNum.Data[6]
		STAA InfyModuleNum.Data[7]
		LDAA #$01
		STAA InfyModuleNum.NewFlag
	}
}
void InfyConfig(void)
{

	if (InfyPowerOperationBuff.Compts.StartTimerFlag == 0)
	{
		asm BSET InfyPowerOperationBuff.data[1], #$01;
		InfyPowerOperationBuff.Compts.InfyCounter = 0;
	}
	else
	{
		if (InfyPowerOperationBuff.Compts.InfyCounter>10)
		{
			if (CAN0OperationBuff.Compts.TotalNum == 0)
			{
				AllModuleType[0].OverTimeFlag = 1;
			}
		}
		else
		{
			InfyConfigDataLoad();
		}
	}
}
/*****************************************************
	Broadcast boot command
*******************************************************/
static void InfyPowerOnDataLoad(void)
{
	asm
	{
		CLRA 
		STAA InfyPowerOnMsg.Data[0]
		STAA InfyPowerOnMsg.Data[1]
		STAA InfyPowerOnMsg.Data[2]
		STAA InfyPowerOnMsg.Data[3]
		STAA InfyPowerOnMsg.Data[4]
		STAA InfyPowerOnMsg.Data[5]
		STAA InfyPowerOnMsg.Data[6]
		STAA InfyPowerOnMsg.Data[7]
		LDAA #$01
		STAA InfyPowerOnMsg.NewFlag
	}
}
/************************************************************************
	Set voltage and current 
************************************************************************/
static void VolCurDataLoad(void)
{
	UInt32 Tmp, Tmp1;
	Tmp = 0;
	Tmp1 = 0;
	if (BMSComCtlBuff.Compts.SystemState== 3)
	{
		Tmp = (UInt32)BCLData.Compts.RequestCur*(-1) * 100;
		Tmp = Tmp / CAN0OperationBuff.Compts.TotalNum;
		if (Tmp >= (UInt32)CAN0OperationBuff.Compts.MaximumCur * 1000)
		{
			Tmp = (UInt32)CAN0OperationBuff.Compts.MaximumCur * 1000;
		}
	
		Tmp1 = (UInt32)BCLData.Compts.RequestVol* 100;
	}
	else if(BMSComCtlBuff.Compts.SystemState ==2)
	{
		if (BCPData.Compts.MaxAllowVol <= (UInt16)CAN0OperationBuff.Compts.MaximumVol*10)
		{
			Tmp1 = (UInt32)BCPData.Compts.MaxAllowVol*100;
		}
		else
		{
			Tmp1 = (UInt32)CAN0OperationBuff.Compts.MaximumVol * 1000;
		}
	}
	InfyVolCurSetMsg.Data[0] = ((UInt8)(Tmp1>>24));
	InfyVolCurSetMsg.Data[1] = ((UInt8)(Tmp1>> 16));
	InfyVolCurSetMsg.Data[2] = ((UInt8)(Tmp1 >> 8));
	InfyVolCurSetMsg.Data[3] = ((UInt8)(Tmp1));
	InfyVolCurSetMsg.Data[4] = ((UInt8)(Tmp >> 24));
	InfyVolCurSetMsg.Data[5] = ((UInt8)(Tmp >> 16));
	InfyVolCurSetMsg.Data[6] = ((UInt8)(Tmp >> 8));
	InfyVolCurSetMsg.Data[7] = ((UInt8)(Tmp));
	InfyVolCurSetMsg.NewFlag = 1;
}
/***********************************************************************
	Boot sequence
************************************************************************/
void InfyPowerOn(void)
{
	UInt8 n;
	if (InfyPowerOperationBuff.Compts.LoopPowerOnFlowFlag == 0)
	{
		InfyPowerOperationBuff.Compts.LoopPowerOnFlowFlag = 1;
		CAN0OperationBuff.Compts.ModuleSeq = 0;
		CAN0OperationBuff.Compts.ModuleOperateSeq = 0;
	}
	switch (CAN0OperationBuff.Compts.ModuleOperateSeq)
	{
	case 0:
		VolCurDataLoad();
		++CAN0OperationBuff.Compts.ModuleOperateSeq;
		break;
	case 1:
		InfyPowerOnDataLoad();
		++CAN0OperationBuff.Compts.ModuleOperateSeq;
		break;
	case 2:
		for (n = 0; n < CAN0OperationBuff.Compts.TotalNum; n++)
		{
			if (n == CAN0OperationBuff.Compts.ModuleSeq)
			{
				InfyModuleOutput[n].Data[0] = 0;
				InfyModuleOutput[n].Data[1] = 0;
				InfyModuleOutput[n].Data[2] = 0;
				InfyModuleOutput[n].Data[3] = 0;
				InfyModuleOutput[n].Data[4] = 0;
				InfyModuleOutput[n].Data[5] = 0;
				InfyModuleOutput[n].Data[6] = 0;
				InfyModuleOutput[n].Data[7] = 0;
				InfyModuleOutput[n].NewFlag = 1;
				++CAN0OperationBuff.Compts.ModuleSeq;
				if (n == CAN0OperationBuff.Compts.TotalNum-1)
				{
					InfyPowerOperationBuff.Compts.LoopPowerOnFlowFlag = 0;
				}
				break;
			}
		}
		break;
	default:
		break;
	}
}
/*****************************************************
	Broadcast power off command
*******************************************************/
static void InfyPowerOffDataLoad(void)
{
	asm
	{
		LDD #$0100
		STAA InfyPowerOffMsg.Data[0]
		STAB InfyPowerOffMsg.Data[1]
		STAB InfyPowerOffMsg.Data[2]
		STAB InfyPowerOffMsg.Data[3]
		STAB InfyPowerOffMsg.Data[4]
		STAB InfyPowerOffMsg.Data[5]
		STAB InfyPowerOffMsg.Data[6]
		STAB InfyPowerOffMsg.Data[7]
		STAA InfyPowerOffMsg.NewFlag
	}
}
/************************************************************************
	shutdown sequence
************************************************************************/
void InfyPowerOff(void)
{
	UInt8 n;
	if (InfyPowerOperationBuff.Compts.LoopPowerOffFlowFlag == 0|| CAN0OperationBuff.Compts.ModuleOperateSeq == 2)
	{
		InfyPowerOperationBuff.Compts.LoopPowerOffFlowFlag = 1;
		CAN0OperationBuff.Compts.ModuleSeq = 0;
		CAN0OperationBuff.Compts.ModuleOperateSeq = 0;
	}
	switch (CAN0OperationBuff.Compts.ModuleOperateSeq)
	{
	case 0:
		InfyPowerOffDataLoad();
		++CAN0OperationBuff.Compts.ModuleOperateSeq;
		break;
	case 1:
		for (n = 0; n < CAN0OperationBuff.Compts.TotalNum; n++)
		{
			if (n == CAN0OperationBuff.Compts.ModuleSeq)
			{
				InfyModuleOutput[n].Data[0] = 0;
				InfyModuleOutput[n].Data[1] = 0;
				InfyModuleOutput[n].Data[2] = 0;
				InfyModuleOutput[n].Data[3] = 0;
				InfyModuleOutput[n].Data[4] = 0;
				InfyModuleOutput[n].Data[5] = 0;
				InfyModuleOutput[n].Data[6] = 0;
				InfyModuleOutput[n].Data[7] = 0;
				InfyModuleOutput[n].NewFlag = 1;
				++CAN0OperationBuff.Compts.ModuleSeq;
				if (n == CAN0OperationBuff.Compts.TotalNum - 1)
				{
					InfyPowerOperationBuff.Compts.LoopPowerOffFlowFlag = 0;
				}
			}
		}
	default:
		break;
	}
}
/************************************************************************
	If 'NewFlag' of  CanMsgBuf  set ,than transmit it
************************************************************************/
void InfyTransmit(void)
{
	UInt8 n;
	if (InfyModuleNum.NewFlag == 1)
	{
		MSCAN0Transmit(&InfyModuleNum);
	}
	if (InfyPowerOnMsg.NewFlag == 1)
	{
		MSCAN0Transmit(&InfyPowerOnMsg);
	}
	if (InfyPowerOffMsg.NewFlag == 1)
	{
		MSCAN0Transmit(&InfyPowerOffMsg);
	}
	if (InfyVolCurSetMsg.NewFlag == 1)
	{
		MSCAN0Transmit(&InfyVolCurSetMsg);
	}
	for (n = 0; n < CAN0OperationBuff.Compts.TotalNum; n++)
	{
		if (InfyModuleOutput[n].NewFlag == 1)
		{
			MSCAN0Transmit(&InfyModuleOutput[n]);
		}
	}
}
/************************************************************************
	Initialize CANID
************************************************************************/
void InfyCANIDInit(void)
{
	UInt8 n;
	InfyModuleNum.CANID.TotalID = 0x02823FF0;
	InfyModuleNum.Length = 8;
	InfyModuleNum.Priority = 1;
	InfyModuleNum.NewFlag = 0;
	CANIDConvert(&InfyModuleNum);

	InfyModuleNumReply.CANID.TotalID = 0x0282f03f;
	InfyModuleNumReply.Length = 8;
	InfyModuleNumReply.Priority = 1;
	InfyModuleNumReply.NewFlag = 0;
	CANIDConvert(&InfyModuleNumReply);

	InfyPowerOnMsg.CANID.TotalID = 0x029A3FF0;
	InfyPowerOnMsg.Length = 8;
	InfyPowerOnMsg.Priority = 1;
	InfyPowerOnMsg.NewFlag = 0;
	CANIDConvert(&InfyPowerOnMsg);

	InfyPowerOffMsg.CANID.TotalID = 0x029A3FF0;
	InfyPowerOffMsg.Length = 8;
	InfyPowerOffMsg.Priority=1;
	InfyPowerOffMsg.NewFlag = 1;
	CANIDConvert(&InfyPowerOffMsg);

	InfyVolCurSetMsg.CANID.TotalID = 0x029C3FF0;
	InfyVolCurSetMsg.Length = 8;
	InfyVolCurSetMsg.Priority = 1;
	InfyVolCurSetMsg.NewFlag = 0;
	CANIDConvert(&InfyVolCurSetMsg);

	for (n = 0; n < MAXMODULENUM; n++)
	{
		InfyModuleOutput[n].CANID.TotalID = 0x028300F0 + (((UInt32)(n)) * 0x100);
		InfyModuleOutput[n].Length = 8;
		InfyModuleOutput[n].Priority = 1;
		InfyModuleOutput[n].NewFlag = 0;
		CANIDConvert(&InfyModuleOutput[n]);

		CANIDTest.CANID.TotalID = 0x028300F0 + (((UInt32)(n)) * 0x100);
		CANIDConvert(&CANIDTest);
		CANIDDecode(&CANIDTest);

		InfyModuleReply[n].CANID.TotalID = 0X0283F000 + n;
		InfyModuleReply[n].Length = 8;
		InfyModuleReply[n].Priority = 1;
		InfyModuleReply[n].NewFlag = 0;
		CANIDConvert(&InfyModuleReply[n]);
	}
}
void InfyAddToCAN0(void)
{
	AllModuleType[0].Config = &InfyConfig;
	AllModuleType[0].ExecuteTransmit = &InfyTransmit;
	AllModuleType[0].OverTimeFlag = 0;
	AllModuleType[0].PowerOff = &InfyPowerOff;
	AllModuleType[0].PowerOn = &InfyPowerOn;
}
void InfyReciever(void)
{
	UInt8 n;
	if (CAN0OperationBuff.Compts.ModuleSwitchCtl == 0)
	{
		if ((InfyModuleNumReply.CANID.ID.ID1 == CAN0RXIDR0) && (InfyModuleNumReply.CANID.ID.ID2 == CAN0RXIDR1)
			&& (InfyModuleNumReply.CANID.ID.ID3 == CAN0RXIDR2)&&(InfyModuleNumReply.CANID.ID.ID4==CAN0RXIDR3))
		{
			CAN0OperationBuff.Compts.TotalNum = CAN0RXDSR2;
			CAN0OperationBuff.Compts.ModuleSwitchCtl = 3;
			CAN0OperationBuff.Compts.MaximumVol = 750;
			CAN0OperationBuff.Compts.MinimumVol = 200;
			CAN0OperationBuff.Compts.MaximumCur = 35;
			CAN0OperationBuff.Compts.MinimumCur = 1;
			CAN0OperationBuff.Compts.ModuleType = 0;
		}
	}
	else
	{
		for (n = 0; n < CAN0OperationBuff.Compts.TotalNum; n++)
		{
			if ((InfyModuleReply[n].CANID.ID.ID1 == CAN0RXIDR0) && (InfyModuleReply[n].CANID.ID.ID2 == CAN0RXIDR1) 
				&& (InfyModuleReply[n].CANID.ID.ID3 == CAN0RXIDR2) && (InfyModuleReply[n].CANID.ID.ID4 == CAN0RXIDR3))
			{
				ConvertVol.UInt8_Data[0] = CAN0RXDSR0;
				ConvertVol.UInt8_Data[1] = CAN0RXDSR1;
				ConvertVol.UInt8_Data[2] = CAN0RXDSR2;
				ConvertVol.UInt8_Data[3] = CAN0RXDSR3;
				AllModuleData[n].Compts.ModuleOutVol = (UInt16)(ConvertVol.IEEE32_Data * 10);
				ConvertCur.UInt8_Data[0] = CAN0RXDSR4;
				ConvertCur.UInt8_Data[1] = CAN0RXDSR5;
				ConvertCur.UInt8_Data[2] = CAN0RXDSR6;
				ConvertCur.UInt8_Data[3] = CAN0RXDSR7;
				AllModuleData[n].Compts.ModuleOutCur = (UInt16)(ConvertCur.IEEE32_Data * 10);
			}
		}
	}
}