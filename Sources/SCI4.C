#include "Include.h"
#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
SCI4Operat SCI4OperatBuff;
UInt16		SurplusTime;
#pragma DATA_SEG DEFAULT
UInt32      CardChargingDuration;
UInt8		ChargingEnd;
UInt8		NetDataN;
#ifdef SCI4ENDTEST
UInt8       SCI4EndCounter;
#endif // SCI4ENDTEST
static void	NetFrameCreate(UInt8 *far InData,UInt8 CmdCode,UInt8 Len)
{
	UInt8	n;
	UInt8 i;
	SCI4OperatBuff.Compts.NetFrameIndex = 0;
	SCI4OperatBuff.Compts.NetCheckNum = 0;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0xFE;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = Len + 15;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0x00;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0x10;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0x00;
	for (n = 6; n < 16; n++)
	{
		asm MOVB #$F0, RPAGE;
		i= HMITxCmdBuff.Compts.ConfigPage.PileNumRec[n];
		asm MOVB #$F1, RPAGE;
		SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = i;
	}
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0x00;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = CmdCode;
	for (n = 0; n < Len; n++)
	{
		SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = InData[n];
	}
	for (n = 0; n < (Len + 1);n++)
	{
		SCI4OperatBuff.Compts.NetCheckNum += SCI4OperatBuff.Compts.NetFrameBuff[n + 16];
	}
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = SCI4OperatBuff.Compts.NetCheckNum;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0xEF;
}
static void NetCmdReply(UInt8	CmdCode)
{
	UInt8 n;
	n = 0;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = 0x01;
	NetFrameCreate(SCI4OperatBuff.Compts.NetDataBuff, CmdCode, n);
	n = SCI4OperatBuff.Compts.NetFrameIndex;
	SCI4SendN(SCI4OperatBuff.Compts.NetFrameBuff, n);
}
void SCI4Init(void)
{
	asm
	{
		MOVB #$00,SCI4BDH
		MOVB #$20,SCI4BDL
		MOVB #$00,SCI4CR1
		MOVB #$2C,SCI4CR2
	}
	SCI4OperatBuff.Compts.NetState = 1;
	SCI4OperatBuff.Compts.NetHeartFrequence = 5;
}
void SCI4SendN(UInt8 *far InData, UInt8 Len)
{
	UInt8 n;
	for (n = 0; n < Len;)
	{
		if ((SCI4SR1 & 0x80) != 0)
		{
			SCI4DRL = InData[n];
			n++;
		}
	}
}
void SCI4Analysis(void)
{
	UInt8 n;
	MemoryList *PtrTmp;
	switch (((UInt8*)IOBuffer[2].Rear)[ NETFRAMECMDINDEX+ 4])
	{
	case 0x11:
		if ((((UInt8*)IOBuffer[2].Rear)[2 + 4] == 0x00) && (((UInt8*)IOBuffer[2].Rear)[1 + 4] == 0x16))
		{
			LocalTimeBuff.Compts.Year = ((UInt16)((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 1 + 4] << 8) +
				((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 4];
			LocalTimeBuff.Compts.Month = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 4 + 2];
			LocalTimeBuff.Compts.Day = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 4 + 3];
			LocalTimeBuff.Compts.Hour = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 4 + 4];
			LocalTimeBuff.Compts.Minute = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX+4 + 5];
			LocalTimeBuff.Compts.Second = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX +4+ 6];
			NetCmdReply(0x11);
			asm MOVB #$F1, RPAGE;
			SCI4OperatBuff.Compts.NetTimeSyn = 1;
			Calender = 0;
		}
		break;
	case 0x12:
		SCI4OperatBuff.Compts.NetOverTimeCounter = 0;
		asm MOVB #$F0, RPAGE;
		HMITxCmdBuff.Compts.WriteNetConFlag[6] = 0x00;
		HMITxCmdBuff.Compts.WriteNetConFlag[7] = 0x01;
		break;
	case 0x21:
		if ((((UInt8*)IOBuffer[2].Rear)[2 + 4] == 0x00) && (((UInt8*)IOBuffer[2].Rear)[1 + 4] == 0x12))
		{
			n = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 2 + 4];
			asm MOVB #$F1, RPAGE;
			SCI4OperatBuff.Compts.NetHeartFrequence = n;
			NetCmdReply(0x12);
		}
		break;
	case 0x23:
		if ((((UInt8*)IOBuffer[2].Rear)[2 + 4] == 0x00) && (((UInt8*)IOBuffer[2].Rear)[1 + 4] == 0x3F))
		{
			for (n = 0; n < 24;n++)
			{
				DiffPriceBuff.Compts.CloudDiffPrice[n] = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 4 + n * 2] + ((UInt32)((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 4 + n * 2 + 1] << 8);
			}
			NetCmdReply(0x23);
			asm MOVB #$F1, RPAGE;
			SCI4OperatBuff.Compts.NetPriceSyn = 1;
			EFlashOperatBuff.Compts.TieredPriceSaveFlag = 1;
		}
		break;
	case 0x24:
		asm MOVB #$F0, RPAGE;
		if ((((UInt8*)IOBuffer[2].Rear)[2 + 4] == 0x00) && (((UInt8*)IOBuffer[2].Rear)[1 + 4] == 0x11))
		{
			DiffPriceBuff.Compts.CloudServicePrice = ((UInt8*)IOBuffer[2].Rear)[NETFRAMECMDINDEX + 1 + 4] + ((UInt16)((UInt8*)IOBuffer[2].Rear)[NETFRAMECMDINDEX + 2 + 4]<<8);
			NetCmdReply(0x24);
			asm MOVB #$F1, RPAGE;
			SCI4OperatBuff.Compts.NetSerSyn = 1;
			EFlashOperatBuff.Compts.ServicePriceSaveFlag = 1;
		}
		break;
	case 0x25:
		NetCmdReply(0x25);
		break;
	case 0x32:
		SCI4OperatBuff.Compts.NetHasRecFaultFlag = 1;
		break;
	case 0x51:
		n = 0;
		break;
	case 0x53:
		SCI4OperatBuff.Compts.NetHasRecCCNFlag = 1;
		NetCmdReply(0x53);
		break;
	case 0x54:
		if (CardOperationBuff.Compts.QueryInf == 1)
			return;
		if (((UInt8*)IOBuffer[2].Rear)[1 + 4] != 0x10)
		{
			switch (((UInt8*)IOBuffer[2].Rear)[NETFRAMECMDINDEX + 4+2])
			{
			case 0x02:
				HMIOperationBuff.Compts.ChargingTime = ((UInt8*)IOBuffer[2].Rear)[NETFRAMECMDINDEX + 3 + 4] + ((UInt16)((UInt8*)IOBuffer[2].Rear)[NETFRAMECMDINDEX + 4 + 4] << 8);
				HMIOperationBuff.Compts.TimingCharging = 1;
				BMSComCtlBuff.Compts.StartCharging = 1;
				break;
			case 0x04:
				HMIOperationBuff.Compts.AutoCharging = 1;
				BMSComCtlBuff.Compts.StartCharging = 1;
				break;
			}
		}
		break;
	case 0x55:
		if (CardOperationBuff.Compts.QueryInf == 1)
			return;
		if (BMSComCtlBuff.Compts.SystemState == 3)
		{
			BMSComCtlBuff.Compts.StopCharging = 1;
			NetCmdReply(0x55);
		}
		break;
	case 0x57:
		ChargingEnd = 0;
		NetCmdReply(0x57);
		break;
	case 0x58:
		ChargingEnd = 0;
		//NetCmdReply(0x58);
		break;
	}
	PtrTmp = IOBuffer[2].Front;
	IOBufferMonitorBuffer.Compts.ExQueueReturnCode[2] = ExQueue(2);
	if (IOBufferMonitorBuffer.Compts.ExQueueReturnCode[2] == 1)
	{
		PtrTmp->DataSize = 0;
		PtrTmp->RecvFinishedFlag = 0;
		if (IOBuffer[2].BlockNum > 0)
			IOBuffer[2].BlockNum -= 1;
	}
	IOBufferMonitorBuffer.Compts.FullFlag[2] = 0;
	OSCRITICALENTRY();
	OSTCBReadyTable[16]->WakeUpFlag = 0;
}
static void SendRealTimeData(void)
{
	UInt8 n;
	n = 0;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = 0x01;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = BSMData.Compts.HighestTemp;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = BSMData.Compts.LowestTemp;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)BSDData.Compts.LowestMonomerTemp;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(BSDData.Compts.LowestMonomerTemp >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)BSDData.Compts.HighesMonomertVol;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(BSDData.Compts.HighesMonomertVol >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = BCSData.Compts.SOCNow;
	if (BCSData.Compts.SurplusTime == 0)
	{
		SurplusTime = (100 - BCSData.Compts.SOCNow)*BCPData.Compts.NominalEny * 3 / (CAN0OperationBuff.Compts.TotalCur*5);
		SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)SurplusTime;
		SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(SurplusTime>>8);
	}
	else
	{
		SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)BCSData.Compts.SurplusTime;
		SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(BCSData.Compts.SurplusTime >> 8);
	}
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)CAN0OperationBuff.Compts.TotalVol;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CAN0OperationBuff.Compts.TotalVol >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CAN0OperationBuff.Compts.TotalCur);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CAN0OperationBuff.Compts.TotalCur >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 16);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 24);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CCSData.Compts.TotalChargTime);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CCSData.Compts.TotalChargTime >> 8);
	NetFrameCreate(SCI4OperatBuff.Compts.NetDataBuff, 0x56, n);
	n = SCI4OperatBuff.Compts.NetFrameIndex;
	SCI4SendN(SCI4OperatBuff.Compts.NetFrameBuff, n);
}
static void SendChargingEndData(void)
{
	UInt8 n;
	static UInt16 OutputPower;
	n = 0;
	OutputPower = CAN0OperationBuff.Compts.TotalVol*CAN0OperationBuff.Compts.TotalCur / 100;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(OutputPower);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(OutputPower >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = 0;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = 0;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CCSData.Compts.TotalChargTime);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CCSData.Compts.TotalChargTime >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = 1;
	for (n = 0; n < 10; n++)
	{
		SCI4OperatBuff.Compts.NetDataBuff[n++] = 0;
	}
	if (CSTData.Compts.ManualTer == 1)
	{
		SCI4OperatBuff.Compts.NetDataBuff[n++] = 1;
	}
	else
	{
		SCI4OperatBuff.Compts.NetDataBuff[n++] = 0;
	}
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)CostManagementBuff.Compts.CostOrignalElectricity;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostOrignalElectricity >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostOrignalElectricity >> 16);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostOrignalElectricity >> 24);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(SCI1OperationBuff.Compts.EngyVal);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(SCI1OperationBuff.Compts.EngyVal >> 8);	
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(SCI1OperationBuff.Compts.EngyVal >> 16);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(SCI1OperationBuff.Compts.EngyVal >> 24);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 16);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 24);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = BCSData.Compts.SOCNow;
	NetFrameCreate(SCI4OperatBuff.Compts.NetDataBuff, 0x57, n);
	n = SCI4OperatBuff.Compts.NetFrameIndex;
	SCI4SendN(SCI4OperatBuff.Compts.NetFrameBuff, n);
}
static void SendFaultData(void)
{
	UInt8 n;
	UInt8 i;
	for (i = 0; i < 7; i++)
	{
		n = 0;
		if (CharFaultBuff.data[0] & FaultBitCompare[i])
		{
			SCI4OperatBuff.Compts.NetDataBuff[n++] = ErrorTypeMap[i];
			NetFrameCreate(SCI4OperatBuff.Compts.NetDataBuff, 0x32, n);
			n = SCI4OperatBuff.Compts.NetFrameIndex;
			SCI4SendN(SCI4OperatBuff.Compts.NetFrameBuff, n);
		}
	}
}
static void SendGunStatusData(void)
{
	UInt8 n;
	n = 0;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = 1;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = GunBuff.Compts.CC1;
	NetFrameCreate(SCI4OperatBuff.Compts.NetDataBuff, 0x53, n);
	n = SCI4OperatBuff.Compts.NetFrameIndex;
	SCI4SendN(SCI4OperatBuff.Compts.NetFrameBuff, n);
}
static void SendCardData(void)
{
	static UInt8 i;
	NetDataN = 0;
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)SerialNumTmp;
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)(SerialNumTmp >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)(SerialNumTmp >> 16);
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)(SerialNumTmp >> 24);
	CardIDAssciiFormat();
	for (i=0;i < 18 - CardIDIndex; i++)
	{
		SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = 48;
	}
	for (i = CardIDIndex - 1; i > 0; i--)
	{
		SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = CardIDToAsscii[i];
	}
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = CardIDToAsscii[0];
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)CostManagementBuff.Compts.CostTotalElectricity;
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity>>8);
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)CostManagementBuff.Compts.CostTotalElectricity;
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)CardChargingDuration;
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)(CardChargingDuration >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)(CardChargingDuration >> 16);
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)(CardChargingDuration >> 24);
	if (HMIOperationBuff.Compts.AutoCharging == 1)
	{
		SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = 4;
	}
	else if (HMIOperationBuff.Compts.TimingCharging == 1)
	{
		SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = 2;
	}
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = 1;
	for (i = 0; i < 14; i++)
	{
		SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = TimeRecFormatArrBuff.data[i];
	}
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)(CostManagementBuff.Compts.CostServicePrice + CostManagementBuff.Compts.CostTotalMoney);
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = (UInt8)((CostManagementBuff.Compts.CostServicePrice + CostManagementBuff.Compts.CostTotalMoney) >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[NetDataN++] = 1;
	NetFrameCreate(SCI4OperatBuff.Compts.NetDataBuff, 0x58, NetDataN);
	NetDataN = SCI4OperatBuff.Compts.NetFrameIndex;
	SCI4SendN(SCI4OperatBuff.Compts.NetFrameBuff, NetDataN);
}
static void SendHearData(void)
{
	UInt8 n;
	n = 0;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = 0;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)LocalTimeBuff.Compts.Year;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = (UInt8)(LocalTimeBuff.Compts.Year >> 8);
	SCI4OperatBuff.Compts.NetDataBuff[n++] = LocalTimeBuff.Compts.Month;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = LocalTimeBuff.Compts.Day;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = LocalTimeBuff.Compts.Hour;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = LocalTimeBuff.Compts.Minute;
	SCI4OperatBuff.Compts.NetDataBuff[n++] = LocalTimeBuff.Compts.Second;
	NetFrameCreate(SCI4OperatBuff.Compts.NetDataBuff, 0x12, n);
	n = SCI4OperatBuff.Compts.NetFrameIndex;
	SCI4SendN(SCI4OperatBuff.Compts.NetFrameBuff, n);
}
void SCI4StateControl(void)
{
	static UInt8 SynAllCounter=0;
	switch (SCI4OperatBuff.Compts.NetState)
	{
	case 0:
		WIFIATHConfig();
		break;
	case 1:
		if ((SCI4OperatBuff.Compts.NetOverTimeCounter >= SCI4OperatBuff.Compts.NetHeartFrequence)&&(CharFaultBuff.data[0]==0))
		{
			if ((CardOperationBuff.Compts.QueryInf== 0))
			{
				if ((BMSComCtlBuff.Compts.SystemState == 3))
				{
					if ((SCI4OperatBuff.Compts.NetHasRecStartFlag == 0))
					{
						NetCmdReply(0x54);
					}
					SendRealTimeData();
				}
				else if (ChargingEnd == 1)
				{
					SendChargingEndData();
				}
				else if ((GunBuff.Compts.CC1 != SCI4OperatBuff.Compts.NetOldCCNRec) || (SCI4OperatBuff.Compts.NetHasRecCCNFlag == 0))
				{
					SCI4OperatBuff.Compts.NetOldCCNRec = GunBuff.Compts.CC1;
					SCI4OperatBuff.Compts.NetHasRecCCNFlag = 0;
					SendGunStatusData();
				}
			}
			else
			{
				if (ChargingEnd == 1)
				{
					ChargingEnd = 0;
#ifdef SCI4ENDTEST
				SCI4EndCounter++;
#endif // SCI4ENDTEST
					SendCardData();
				}
			}
			SendHearData();
			SCI4OperatBuff.Compts.NetOverTimeCounter = 0;
		}
		else
		{
			if (SCI4OperatBuff.Compts.NetSynAll==1)
			{
				if (SynAllCounter <5)
				{
					SynAllCounter++;
					if (SCI4OperatBuff.Compts.NetTimeSyn ==0||SCI4OperatBuff.Compts.NetSerSyn==0||SCI4OperatBuff.Compts.NetPriceSyn==0)
					{
						NetCmdReply(0x99);
					}
				}
				else
				{
					SCI4OperatBuff.Compts.NetSynAll = 0;
					SynAllCounter = 0;
				}
			}
			if (SCI4OperatBuff.Compts.NetHasRecFaultFlag == 0)
			{
				SCI4OperatBuff.Compts.NetHasRecFaultFlag = 1;
				SendFaultData();
			}
			if (SCI4OperatBuff.Compts.NetOverTimeCounter < 20)
			{
				SCI4OperatBuff.Compts.NetOverTimeCounter++;
			}
			else
			{
				asm MOVB #$F0, RPAGE;
				HMITxCmdBuff.Compts.WriteNetConFlag[6] = 0x00;
				HMITxCmdBuff.Compts.WriteNetConFlag[7] = 0x00;
			}
		}
		break;

	default:
		break;
	}
	OSCRITICALENTRY();
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void SCI4Net(void)
{
	static UInt16	n = 0;
	MemoryList *PtrTmp;
	asm INC OSNesting;
	if (SCI4SR1 & 0x20)
	{
		if (n >= 124)
			n = 0;
		((UInt8*)IOBuffer[2].Rear)[n + 4] = SCI4DRL;
		++n;
		if ((((UInt8*)IOBuffer[2].Rear)[4] == 0xFE))
		{
			if (n > 17)
			{
				
				if (((UInt8*)IOBuffer[2].Rear)[1 + 4] + 4 <= n)
				{
					if (((UInt8*)IOBuffer[2].Rear)[n - 1 + 4] == 0xEF)
					{
						if ((IOBufferMonitorBuffer.Compts.FullFlag[2] == 0) && (IOBuffer[2].Rear->RecvFinishedFlag == 0))
						{
							PtrTmp = IOBuffer[2].Rear;
							IOBufferMonitorBuffer.Compts.EnQueueReturnCode[2] = EnQueue(2);
							if (IOBufferMonitorBuffer.Compts.EnQueueReturnCode[2] == 1)
							{
								PtrTmp->DataSize = n;
								PtrTmp->RecvFinishedFlag = 1;
								IOBuffer[2].BlockNum += 1;
								OSTCBReadyTable[16]->WakeUpFlag = 1;
							}
							else
							{
								IOBufferMonitorBuffer.Compts.FullFlag[2] = 1;
							}
						}
					}
					n = 0;
				}
				
			}
		}
		else if (((UInt8*)IOBuffer[2].Rear)[4] == 0x61)
		{
			n = 0;
		}
		else
		{
			n = 0;
		}
	}
	asm DEC OSNesting;
}
#pragma CODE_SEG DEFAULT