#include "Include.h"
#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
SCI4Operat SCI4OperatBuff;
UInt8		ChargingEnd;
#pragma DATA_SEG DEFAULT
static void	NetFrameCreate(UInt8 *far InData,UInt8 CmdCode,UInt8 Len)
{
	UInt8	n;
	SCI4OperatBuff.Compts.NetFrameIndex = 0;
	SCI4OperatBuff.Compts.NetCheckNum = 0;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0xFE;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = Len + 15;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0x00;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0x10;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0x00;
	for (n = 6; n < 16; n++)
	{
		SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = HMITxCmdBuff.Compts.ConfigPage.PileNumRec[n];
	}
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = 0x00;
	SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = CmdCode;
	for (n = 0; n < Len; n++)
	{
		SCI4OperatBuff.Compts.NetFrameBuff[SCI4OperatBuff.Compts.NetFrameIndex++] = InData[n];
	}
	for (n = 0; n < (Len + 1), n++)
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
			LocalTimeBuff.Compts.Minute = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 5];
			LocalTimeBuff.Compts.Second = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 6];
			NetCmdReply(0x11);
		}
		break;
	case 0x12:
		SCI4OperatBuff.Compts.NetOverTimeCounter = 0;
		break;
	case 0x21:
		if ((((UInt8*)IOBuffer[2].Rear)[2 + 4] == 0x00) && (((UInt8*)IOBuffer[2].Rear)[1 + 4] == 0x12))
		{
			SCI4OperatBuff.Compts.NetHeartFrequence = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 2 + 4];
			NetCmdReply(0x12);
		}
		break;
	case 0x23:
		if ((((UInt8*)IOBuffer[2].Rear)[2 + 4] == 0x00) && (((UInt8*)IOBuffer[2].Rear)[1 + 4] == 0x3F))
		{
			for (n = 0; n < 24;)
			{
				DiffPriceBuff.Compts.CloudDiffPrice[n] = ((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 4 + n * 2] + ((UInt32)((UInt8*)IOBuffer[2].Rear)[NETFRAMEDATAINDEX + 4 + n * 2 + 1] << 8);
			}
			NetCmdReply(0x23);
		}
		break;
	case 0x24:
		if ((((UInt8*)IOBuffer[2].Rear)[2 + 4] == 0x00) && (((UInt8*)IOBuffer[2].Rear)[1 + 4] == 0x11))
		{
			DiffPriceBuff.Compts.CloudServicePrice = ((UInt8*)IOBuffer[2].Rear)[NETFRAMECMDINDEX + 1 + 4] + ((UInt16)((UInt8*)IOBuffer[2].Rear)[NETFRAMECMDINDEX + 2 + 4]<<8);
			NetCmdReply(0x24);
		}
		break;
	case 0x25:
		NetCmdReply(0x25);
		break;
	case 0x32:
		SCI4OperatBuff.Compts.NetHasRecFaultFlag = 1;
		NetCmdReply(0x32);
		break;
	case 0x51:
		n = 0;
		break;
	case 0x53:
		SCI4OperatBuff.Compts.NetHasRecCCNFlag = 1;
		NetCmdReply(0x53);
		break;
	case 0x54:
		if (CardOperatBuff.Compts.CardEnable == 1)
			return;
		if (((UInt8*)IOBuffer[2].Rear)[1 + 4] != 0x10)
		{
			switch (((UInt8*)IOBuffer[2].Rear)[NETFRAMECMDINDEX + 4+2] == 0x00)
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
		if (CardOperatBuff.Compts.CardEnable == 1)
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
		n = 0;
		break;
	}
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
		if ((((UInt8*)IOBuffer[2].Rear)[4] == 0xFE) && (n > 17))
		{
			if (((UInt8*)IOBuffer[2].Rear)[n - 1 + 4] == 0xEF)
			{
				if (((UInt8*)IOBuffer[2].Rear)[1 + 4] == n - 4)
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
						}
						else
						{
							IOBufferMonitorBuffer.Compts.FullFlag[2] = 1;
						}
					}
					n = 0;
				}
			}
		}
		else if (((UInt8*)IOBuffer[2].Rear)[4] == 0x61)
		{

		}
	}
	asm DEC OSNesting;
}
#pragma CODE_SEG DEFAULT