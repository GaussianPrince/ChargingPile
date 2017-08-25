#include "Include.h"
DLT2007Cmd DLT2007CmdBuff = {
	0xFE,0XFE,0XFE,0XFE,0x68, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x68, 0x11, 0x04, 0x33, 0x33, 0x33, 0x33, 0xAE, 0x16
};
UInt8 DLT2007ConfigFlag;
void DLT2007CRCCal(void)
{
	UInt8 n;
	UInt8 Tmp=0;
	for (n = 4; n < 18; n++)
	{
		Tmp += DLT2007CmdBuff.EnergyReadCmd[n];
	}
	DLT2007CmdBuff.EnergyReadCmd[18] = Tmp;
}
void DLT2007Init(void)
{
	SCI1StaMacBuff[0].SCI1Config = DLT2007Config;
	SCI1StaMacBuff[0].SCI1Transmit = DLT2007Transmit;
	SCI1StaMacBuff[0].SCI1Analysis = DLT2007Analysis;
	SCI1StaMacBuff[0].OverTimerCounter = 0;
	DLT2007ConfigFlag = 0;
}
void DLT2007Config(void)
{
	if (DLT2007ConfigFlag == 1)
	{
		SCI1OperationBuff.Compts.SCI1MeterType = 0;
		SCI1OperationBuff.Compts.SCI1SwitchCtl = 1;
	}
}
void DLT2007Analysis(void)
{
	UInt16 n;
	UInt8 Tmp=0;
	MemoryList *PtrTmp;
	UInt8 Arr[3];
	if (IOBuffer[4].Front->RecvFinishedFlag == 1)
	{
		for (n = 0; n < 18; n++)
		{
			Tmp += ((UInt8*)IOBuffer[4].Front)[n + 4];
		}
		Arr[0] = ((UInt8*)IOBuffer[4].Front)[10+4];
		Arr[1] = ((UInt8*)IOBuffer[4].Front)[11+4];
		Arr[2] = ((UInt8*)IOBuffer[4].Front)[18+4];
		if (( Arr[0]== 0x33) && (Arr[1] == 0x33) &&(Tmp == Arr[2]))
		{
			SCI1OperationBuff.Compts.EngyVal = (UInt32)(((((UInt8*)IOBuffer[4].Front)[17+4] - 0x33) & 0xF0) >> 4) * 10000000
				+ (UInt32)(((((UInt8*)IOBuffer[4].Front)[17+4] - 0x33) & 0x0F)) * 1000000
				+ (UInt32)(((((UInt8*)IOBuffer[4].Front)[16+4] - 0x33) & 0xF0) >> 4) * 100000
				+ (UInt32)(((((UInt8*)IOBuffer[4].Front)[16+4] - 0x33) & 0x0F)) * 10000
				+ (UInt32)(((((UInt8*)IOBuffer[4].Front)[15+4] - 0x33) & 0xF0) >> 4) * 1000
				+ (UInt32)(((((UInt8*)IOBuffer[4].Front)[15+4] - 0x33) & 0x0F)) * 100
				+ (UInt32)(((((UInt8*)IOBuffer[4].Front)[14+4] - 0x33) & 0xF0) >> 4) * 10
				+ (UInt32)(((((UInt8*)IOBuffer[4].Front)[14+4] - 0x33) & 0x0F));
		}
		DLT2007ConfigFlag = 1;
		PtrTmp = IOBuffer[4].Front;
		IOBufferMonitorBuffer.Compts.ExQueueReturnCode[4] = ExQueue(4);
		if (IOBufferMonitorBuffer.Compts.ExQueueReturnCode[4] == 1)
		{
			PtrTmp->DataSize = 0;
			PtrTmp->RecvFinishedFlag = 0;
			if (IOBuffer[4].BlockNum > 0)
				IOBuffer[4].BlockNum -= 1;
		}
		IOBufferMonitorBuffer.Compts.FullFlag[4] = 0;
	}
}
void DLT2007Transmit(void)
{
	SCI1Send(DLT2007CmdBuff.EnergyReadCmd, 20);
}