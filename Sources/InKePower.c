#include "InKePower.h"
InKePowerOperation InKePowerOperationBuff;
CanMsgBuf	InKeMultUseMsg;
CanMsgBuf	InKeModuleOutput[MAXMODULENUM];
CanMsgBuf	InKeModuleReply[MAXMODULENUM];
UInt32		InKeModuleCounter;
static void InKePowerOnDataLoad(void)
{
	asm
	{
		LDAA #$02
		STAA InKeMultUseMsg.Data[0]
		CLRA
		STAA InKeMultUseMsg.Data[1]
		STAA InKeMultUseMsg.Data[2]
		STAA InKeMultUseMsg.Data[3]
		STAA InKeMultUseMsg.Data[4]
		STAA InKeMultUseMsg.Data[5]
		STAA InKeMultUseMsg.Data[6]
		LDAA #$55
		STAA InKeMultUseMsg.Data[7]
		LDAA #$01
		STAA InKeMultUseMsg.NewFlag
	}
}
static void InKePowerOffDataLoad(void)
{
	asm
	{
		LDAA #$02
		STAA InKeMultUseMsg.Data[0]
		CLRA
		STAA InKeMultUseMsg.Data[1]
		STAA InKeMultUseMsg.Data[2]
		STAA InKeMultUseMsg.Data[3]
		STAA InKeMultUseMsg.Data[4]
		STAA InKeMultUseMsg.Data[5]
		STAA InKeMultUseMsg.Data[6]
		LDAA #$AA
		STAA InKeMultUseMsg.Data[7]
		LDAA #$01
		STAA InKeMultUseMsg.NewFlag
	}
}
static void VolCurDataLoad(void)
{
	UInt32 Tmp, Tmp1;
	Tmp = 0;
	Tmp1 = 0;
	if (BMSComCtlBuff.Compts.SystemState == 3)
	{
		Tmp = (UInt32)BCLData.Compts.RequestCur*(-1) * 100;
		Tmp = Tmp / CAN0OperationBuff.Compts.TotalNum;
		if (Tmp >= (UInt32)CAN0OperationBuff.Compts.MaximumCur * 1000)
		{
			Tmp = (UInt32)CAN0OperationBuff.Compts.MaximumCur * 1000;
		}

		Tmp1 = (UInt32)BCLData.Compts.RequestVol * 100;
	}
	else if (BMSComCtlBuff.Compts.SystemState == 2)
	{
		if (BCPData.Compts.MaxAllowVol <= (UInt16)CAN0OperationBuff.Compts.MaximumVol * 10)
		{
			Tmp1 = (UInt32)BCPData.Compts.MaxAllowVol * 100;
		}
		else
		{
			Tmp1 = (UInt32)CAN0OperationBuff.Compts.MaximumVol * 1000;
		}
	}
	InKeMultUseMsg.Data[0] = 0x00;
	InKeMultUseMsg.Data[1] = (UInt8)(Tmp >> 16);
	InKeMultUseMsg.Data[2] = (UInt8)(Tmp >> 8);
	InKeMultUseMsg.Data[3] = (UInt8)(Tmp);
	InKeMultUseMsg.Data[4] = (UInt8)(Tmp1 >> 24);
	InKeMultUseMsg.Data[5] = (UInt8)(Tmp1 >> 16);
	InKeMultUseMsg.Data[6] = (UInt8)(Tmp1 >> 8);
	InKeMultUseMsg.Data[7] = (UInt8)(Tmp1);
	InKeMultUseMsg.NewFlag = 1;
}
void InKeCANIDInit(void)
{
	UInt8 n;
	InKeMultUseMsg.CANID.TotalID = 0x1307C080;
	InKeMultUseMsg.Length = 8;
	InKeMultUseMsg.Priority = 1;
	InKeMultUseMsg.NewFlag = 0;
	CANIDConvert(&InKeMultUseMsg);

	for (n = 0; n < MAXMODULENUM; n++)
	{
		InKeModuleOutput[n].CANID.TotalID = 0x1307C080 + ((UInt32)(n + 1));
		InKeModuleOutput[n].Length = 8;
		InKeModuleOutput[n].Priority = 1;
		InKeModuleOutput[n].NewFlag = 0;
		CANIDConvert(&InKeModuleOutput[n]);

		InKeModuleReply[n].CANID.TotalID = 0x1207C080 + ((UInt32)(n + 1));
		InKeModuleReply[n].Length = 8;
		InKeModuleReply[n].Priority = 1;
		InKeModuleReply[n].NewFlag = 0;
		CANIDConvert(&InKeModuleReply[n]);
	}
}
void InKeConfig(void)
{
	UInt8	n;
	if (InKePowerOperationBuff.Compts.StartTimerFlag == 0)
	{
		asm BSET InKePowerOperationBuff.data[1], #$01;
		InKePowerOperationBuff.Compts.InKeCounter=0;
	}
	else
	{
		if (InKePowerOperationBuff.Compts.InKeCounter >=20)
		{
			if(InKeModuleCounter==0)
				AllModuleType[1].OverTimeFlag = 1;
			else
			{
				for (n = 0; n < 32; n++)
				{
					if (InKeModuleCounter & 0x01)
					{
						CAN0OperationBuff.Compts.TotalNum++;
						InKeModuleCounter = (InKeModuleCounter >> 1);
					}
				}
				CAN0OperationBuff.Compts.MaximumCur = 20;
				CAN0OperationBuff.Compts.MinimumCur = 1;
				CAN0OperationBuff.Compts.MaximumVol = 750;
				CAN0OperationBuff.Compts.MinimumVol = 200;
				CAN0OperationBuff.Compts.ModuleType = 1;
				CAN0OperationBuff.Compts.ModuleSwitchCtl = 3;
			}
		}
		else
		{
			InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[0] = 0x01;
			InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[1] = 0x00;
			InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[2] = 0x00;
			InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[3] = 0x00;
			InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[4] = 0x00;
			InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[5] = 0x00;
			InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[6] = 0x00;
			InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[7] = 0x00;
			InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].NewFlag = 1;
			CAN0OperationBuff.Compts.ModuleSeq++;
			if (CAN0OperationBuff.Compts.ModuleSeq >= MAXMODULENUM)
			{
				CAN0OperationBuff.Compts.ModuleSeq = 0;
			}
			InKePowerOperationBuff.Compts.InKeCounter++;
		}
	}
	
}
void InKePowerOn(void)
{
	if (InKePowerOperationBuff.Compts.LoopPowerOnFlowFlag == 0)
	{
		InKePowerOperationBuff.Compts.LoopPowerOnFlowFlag = 1;
		CAN0OperationBuff.Compts.ModuleOperateSeq = 0;
		CAN0OperationBuff.Compts.ModuleSeq = 0;
	}
	switch (CAN0OperationBuff.Compts.ModuleOperateSeq)
	{
	case 0:
		VolCurDataLoad();
		++CAN0OperationBuff.Compts.ModuleOperateSeq;
		break;
	case 1:
		InKePowerOnDataLoad();
		++CAN0OperationBuff.Compts.ModuleOperateSeq;
		break;
	case 2:
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[0] = 0x01;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[1] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[2] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[3] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[4] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[5] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[6] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[7] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].NewFlag = 1;
		CAN0OperationBuff.Compts.ModuleSeq++;
		if (CAN0OperationBuff.Compts.ModuleSeq >= CAN0OperationBuff.Compts.TotalNum)
		{
			InKePowerOperationBuff.Compts.LoopPowerOnFlowFlag = 0;
		}
		break;
	}
}
void InKePowerOff(void)
{
	if (InKePowerOperationBuff.Compts.LoopPowerOffFlowFlag == 0)
	{
		InKePowerOperationBuff.Compts.LoopPowerOffFlowFlag = 1;
		CAN0OperationBuff.Compts.ModuleSeq = 0;
		CAN0OperationBuff.Compts.ModuleOperateSeq = 0;
	}
	switch (CAN0OperationBuff.Compts.ModuleOperateSeq)
	{
	case 0:
		InKePowerOffDataLoad();
		++CAN0OperationBuff.Compts.ModuleOperateSeq;
		break;
	case 1:
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[0] = 0x01;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[1] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[2] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[3] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[4] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[5] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[6] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].Data[7] = 0x00;
		InKeModuleOutput[CAN0OperationBuff.Compts.ModuleSeq].NewFlag = 1;
		CAN0OperationBuff.Compts.ModuleSeq++;
		if (CAN0OperationBuff.Compts.ModuleSeq >= CAN0OperationBuff.Compts.TotalNum)
		{
			InKePowerOperationBuff.Compts.LoopPowerOffFlowFlag = 0;
		}
		break;
	}
}
void InKeTransmit(void)
{
	UInt8 n;
	if (InKeMultUseMsg.NewFlag == 1)
	{
		MSCAN0Transmit(&InKeMultUseMsg);
	}
	for (n = 0; n < MAXMODULENUM; n++)
	{
		if (InKeModuleOutput[n].NewFlag == 1)
		{
			MSCAN0Transmit(&InKeModuleOutput[n]);
		}
	}
}
void InKeAddToCAN0(void)
{
	AllModuleType[1].Config = InKeConfig;
	AllModuleType[1].ExecuteTransmit = InKeTransmit;
	AllModuleType[1].OverTimeFlag = 0;
	AllModuleType[1].PowerOff = InKePowerOff;
	AllModuleType[1].PowerOn = InKePowerOn;
}
void InKeReciever(void)
{
	UInt8 n;
	if (CAN0OperationBuff.Compts.ModuleSwitchCtl == 0)
	{
		for (n = 0; n < MAXMODULENUM; n++)
		{
			if ((InKeModuleReply[n].CANID.ID.ID1 == CAN0RXIDR0) && (InKeModuleReply[n].CANID.ID.ID2 == CAN0RXIDR1)
				&& (InKeModuleReply[n].CANID.ID.ID3 == CAN0RXIDR2) && (InKeModuleReply[n].CANID.ID.ID4 == CAN0RXIDR3))
			{
				InKeModuleCounter |= ((UInt32)1 << n);
			}
		}

	}
	else
	{
		for (n = 0; n < CAN0OperationBuff.Compts.TotalNum; n++)
		{
			if ((InKeModuleReply[n].CANID.ID.ID1 == CAN0RXIDR0) && (InKeModuleReply[n].CANID.ID.ID2 == CAN0RXIDR1)
				&& (InKeModuleReply[n].CANID.ID.ID3 == CAN0RXIDR2) && (InKeModuleReply[n].CANID.ID.ID4 == CAN0RXIDR3))
			{
				ConvertVol.UInt8_Data[0] = CAN0RXDSR0;
				ConvertVol.UInt8_Data[1] = CAN0RXDSR1;
				ConvertVol.UInt8_Data[2] = CAN0RXDSR2;
				ConvertVol.UInt8_Data[3] = CAN0RXDSR3;
				AllModuleData[n].Compts.ModuleOutCur = (UInt16)(ConvertVol.UInt16_Data[1]);
				ConvertCur.UInt8_Data[0] = CAN0RXDSR4;
				ConvertCur.UInt8_Data[1] = CAN0RXDSR5;
				ConvertCur.UInt8_Data[2] = CAN0RXDSR6;
				ConvertCur.UInt8_Data[3] = CAN0RXDSR7;
				AllModuleData[n].Compts.ModuleOutVol = (UInt16)(ConvertCur.UInt16_Data[0]);
			}
		}
	}
}