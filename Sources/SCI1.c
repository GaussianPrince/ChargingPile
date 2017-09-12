#include "Include.h"
SCI1StaMac SCI1StaMacBuff[MAXMETERTYPE];
SCI1Operation SCI1OperationBuff;
void SCI1OperationBuffInit(void)
{
	UInt8 n;
	for (n = 0; n < 3; n++)
	{
		SCI1OperationBuff.data[n] = 0;
	}
}
void  SCI1StaMacBuffInit(void)
{
	UInt8 n;
	for (n = 0; n < MAXMETERTYPE; n++)
	{
		SCI1StaMacBuff[n].SCI1Config = 0;
		SCI1StaMacBuff[n].SCI1Analysis = 0;
		SCI1StaMacBuff[n].SCI1Transmit = 0;
		SCI1StaMacBuff[n].OverTimerCounter = 0;
	}
}
void  SCI1ChangeTransmitDirection(void)
{
	asm BCLR PTS, #$10; 
	asm CLR  SCI1OperationBuff.Compts.SCI1RecSendSwitch;
}
void DelaySCI(UInt16 Ms)
{
	UInt16 i, j;
	for (i = 0; i < Ms; i++)
		for (j = 0; j < 1100; j++);//0.5ms
}
void  SCI1Send(UInt8 *InData, UInt8 Len)
{
	UInt8 n;
	asm BSET PTS, #$10;
	asm BSET SCI1OperationBuff.Compts.SCI1RecSendSwitch, #$01;
	for (n = 0; n < Len;)
	{
		if ((SCI1SR1 & 0x80) != 0)
		{
			SCI1DRH_T8 = (0 ^ (InData[n] & 0x01) ^ (InData[n] & 0x02) ^ (InData[n] & 0x04) ^ (InData[n] & 0x08) ^ (InData[n] & 0x10) ^ (InData[n] ^ 0x20) ^ (InData[n] ^ 0x40) ^ (InData[n] ^ 0x80));
			SCI1DRL = InData[n];
			n++;
		}
	}
	DelaySCI(19);
	asm BCLR PTS, #$10;
	asm CLR  SCI1OperationBuff.Compts.SCI1RecSendSwitch;
}
/*****************************************************
	Baud rate=6*10^7/(16*391)=9600b/s
*******************************************************/
void SCI1Init(void)
{
	asm
	{
		MOVB #$01,SCI1BDH
		MOVB #$86,SCI1BDL
		MOVB #$12,SCI1CR1
		MOVB #$2C,SCI1CR2
		BSET DDRS,#$10
	}
}
void SCI1StateControl(void)
{
	if (SCI1OperationBuff.Compts.SCI1SwitchCtl == 0)
	{
		switch (SCI1OperationBuff.Compts.SCI1ConfigSeq)
		{
		case 0:
			if ((SCI1StaMacBuff[0].SCI1Config!=0)&&(SCI1StaMacBuff[0].OverTimerCounter < 20))
			{
				(*SCI1StaMacBuff[0].SCI1Config)();
				(*SCI1StaMacBuff[0].SCI1Analysis)();
				(*SCI1StaMacBuff[0].SCI1Transmit)();
				SCI1StaMacBuff[0].OverTimerCounter++;
			}
			SCI1OperationBuff.Compts.SCI1ConfigSeq++;
			break;
		case 1:
			if ((SCI1StaMacBuff[1].SCI1Config != 0) && (SCI1StaMacBuff[1].OverTimerCounter < 20))
			{
				(*SCI1StaMacBuff[1].SCI1Config)();
				(*SCI1StaMacBuff[1].SCI1Analysis)();
				(*SCI1StaMacBuff[1].SCI1Transmit)();
				SCI1StaMacBuff[1].OverTimerCounter++;
			}
			else if (SCI1StaMacBuff[1].OverTimerCounter >= 20)
			{
				GovlanOSErrorCode = GOVLANOSSCI1CONFIGOVERTIME;
			}
			SCI1OperationBuff.Compts.SCI1ConfigSeq = 0;
			break;
		}
	}
	else if (SCI1OperationBuff.Compts.SCI1SwitchCtl == 1)
	{
		(*SCI1StaMacBuff[SCI1OperationBuff.Compts.SCI1MeterType].SCI1Analysis)();
		(*SCI1StaMacBuff[SCI1OperationBuff.Compts.SCI1MeterType].SCI1Transmit)();
	}
	OSCRITICALENTRY();
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void SCI1Meter(void)
{
	static UInt16 n=0;
	MemoryList *PtrTmp;
	asm INC OSNesting;
	if (SCI1SR1 & 0x20)
	{
		if ((n < 124) && (IOBufferMonitorBuffer.Compts.FullFlag[4] == 0) && (IOBuffer[4].Rear->RecvFinishedFlag == 0))
		{
			((UInt8*)IOBuffer[4].Rear)[n + 4] = SCI1DRL;
			ComOverTimeBuff.Compts.MeterOverTimeCounter = 0;
			++n;
			if (n == 20)
			{
				if ((((UInt8*)IOBuffer[4].Rear)[4] == 0x68) && (((UInt8*)IOBuffer[4].Rear)[n + 4 - 1] == 0x16))
				{
					PtrTmp = IOBuffer[4].Rear;
					IOBufferMonitorBuffer.Compts.EnQueueReturnCode[4] = EnQueue(4);
					if (IOBufferMonitorBuffer.Compts.EnQueueReturnCode[4] == 1)
					{
						PtrTmp->DataSize = n;
						PtrTmp->RecvFinishedFlag = 1;
						IOBuffer[4].BlockNum += 1;
					}
					else
					{
						IOBufferMonitorBuffer.Compts.FullFlag[4] = 1;
					}
				}
				n = 0;
			}
		}
		else
		{
			n = 0;
		}
	}
	asm DEC  OSNesting;
}
#pragma  CODE_SEG  DEFAULT
