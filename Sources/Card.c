#include "Include.h"
#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
QueryLabel	 QueryLabelCmd = {
	0X7E,0X55,0X09,0X00,0X00,0X01,0X00,0X16,0X00,0X52,0x00,0x00
};
M1Read2		 M1ReadCmd2={
	0x7E,0X55,0X11,0X00,0X00,0X01,0X00,0X70,0X00,0X60,0XFF,0XFF,
	0XFF,0XFF,0XFF,0XFF,0X02,0X01,0X00,0X00 
};
M1Read8		 M1ReadCmd8 = {
	0x7E,0X55,0X11,0X00,0X00,0X01,0X00,0X70,0X00,0X60,0XFF,0XFF,
	0XFF,0XFF,0XFF,0XFF,0X08,0X01,0X00,0X00
};
M1Write2		 M1WriteCmd2 = {
	0X7E,0X55,0X21,0x00,0x00,0x01,0x00,0x71,0x00,0x60,0xFF,0XFF,
	0xFF,0XFF,0XFF,0XFF,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
M1Write8		 M1WriteCmd8 = {
	0X7E,0X55,0X21,0x00,0x00,0x01,0x00,0x71,0x00,0x60,0xFF,0XFF,
	0xFF,0XFF,0XFF,0XFF,0x08,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
CardOperat	 CardOperatBuff;
UInt16		 CardCheckTem;
#pragma DATA_SEG DEFAULT
DataConvert	 UserMoneyConvert;
DataConvert	 CardIDConvert;
DataConvert	 UserIDConvert;
void SCI5Init(void)
{
	asm
	{
		MOVB #$00,SCI5BDH
		MOVB #$20,SCI5BDL
		MOVB #$00,SCI5CR1
		MOVB #$2C,SCI5CR2
	}
	CardCheckTem = CardCalCRC(&QueryLabelCmd.data[2], (QueryLabelCmd.data[2] - 1));
	QueryLabelCmd.data[10] = (UInt8)(CardCheckTem);
	QueryLabelCmd.data[11] = (UInt8)(CardCheckTem >> 8);
	CardCheckTem = CardCalCRC(&M1ReadCmd2.data[2], (M1ReadCmd2.data[2] - 1));
	M1ReadCmd2.data[18] = (UInt8)(CardCheckTem);
	M1ReadCmd2.data[19] = (UInt8)(CardCheckTem >> 8);
	CardCheckTem = CardCalCRC(&M1ReadCmd8.data[2], (M1ReadCmd8.data[2] - 1));
	M1ReadCmd8.data[18] = (UInt8)(CardCheckTem);
	M1ReadCmd8.data[19] = (UInt8)(CardCheckTem >> 8);
}
void SCI5SendN(UInt8 * far InData, UInt8 Len)
{
	UInt8 n;
	for (n = 0; n < Len;)
	{
		if ((SCI5SR1 & 0x80) != 0)
		{
			SCI5DRL = InData[n];
			n++;
		}
	}
}
static void  M1Write2Format(void)
{
	UInt8	n=0;
	UInt8	i = 0;
	M1WriteCmd2.Compts.BlockData[n++] = 0xEF;
	M1WriteCmd2.Compts.BlockData[n++] = 0x0B;
	M1WriteCmd2.Compts.BlockData[n++] = (UInt8)(CardOperatBuff.Compts.UserID>>24);
	M1WriteCmd2.Compts.BlockData[n++] = (UInt8)(CardOperatBuff.Compts.UserID >> 16);
	M1WriteCmd2.Compts.BlockData[n++] = (UInt8)(CardOperatBuff.Compts.UserID >> 8);
	M1WriteCmd2.Compts.BlockData[n++] = (UInt8)(CardOperatBuff.Compts.UserID);
	M1WriteCmd2.Compts.BlockData[n++] = 0x00;
	M1WriteCmd2.Compts.BlockData[n++] = 0x00;
	M1WriteCmd2.Compts.BlockData[n++] = 0x00;
	M1WriteCmd2.Compts.BlockData[n++] = (UInt8)(CardOperatBuff.Compts.CardID >> 24);
	M1WriteCmd2.Compts.BlockData[n++] = (UInt8)(CardOperatBuff.Compts.CardID >> 16);
	M1WriteCmd2.Compts.BlockData[n++] = (UInt8)(CardOperatBuff.Compts.CardID >> 8);
	M1WriteCmd2.Compts.BlockData[n++] = (UInt8)(CardOperatBuff.Compts.CardID);
	M1WriteCmd2.Compts.BlockData[n++] = CardOperatBuff.Compts.CardPermission;
	CardCheckTem = 0;
	for (i = 1; i < n; i++)
	{
		CardCheckTem += M1WriteCmd2.Compts.BlockData[i];
	}
	M1WriteCmd2.Compts.BlockData[n++] = (UInt8)(CardCheckTem % 0x100);
	M1WriteCmd2.Compts.BlockData[n++] = 0xFE;
	M1WriteCmd2.Compts.CRC = CardCalCRC(&M1WriteCmd2.data[2], M1WriteCmd2.Compts.FrameLen - 1);
	M1WriteCmd2.Compts.CRC = (M1WriteCmd2.Compts.CRC << 8) + (UInt8)(M1WriteCmd2.Compts.CRC >> 8);
}
static void  M1Write8Format(void)
{
	UInt8 n=0;
	UInt8 i=0;
	M1WriteCmd8.Compts.BlockData[n++] = 0xEF;
	M1WriteCmd8.Compts.BlockData[n++] = 0xFF;
	M1WriteCmd8.Compts.BlockData[n++] = 0xFF;
	M1WriteCmd8.Compts.BlockData[n++] = 0x8E;
	M1WriteCmd8.Compts.BlockData[n++] = 0x86;
	CardIDConvert.UInt32_Data = CardOperatBuff.Compts.CardID + 0x86766578;
	M1WriteCmd8.Compts.BlockData[n++] = ~CardIDConvert.UInt8_Data[0];
	M1WriteCmd8.Compts.BlockData[n++] = ~CardIDConvert.UInt8_Data[1];
	M1WriteCmd8.Compts.BlockData[n++] = ~CardIDConvert.UInt8_Data[2];
	M1WriteCmd8.Compts.BlockData[n++] = ~CardIDConvert.UInt8_Data[3];
	M1WriteCmd8.Compts.BlockData[n++] = 0xFF;
	UserMoneyConvert.UInt32_Data = CardOperatBuff.Compts.ResidualMoney + CardOperatBuff.Compts.CardID;
	M1WriteCmd8.Compts.BlockData[n++] = ~UserMoneyConvert.UInt8_Data[0];
	M1WriteCmd8.Compts.BlockData[n++] = ~UserMoneyConvert.UInt8_Data[1];
	M1WriteCmd8.Compts.BlockData[n++] = ~UserMoneyConvert.UInt8_Data[2];
	M1WriteCmd8.Compts.BlockData[n++] = ~UserMoneyConvert.UInt8_Data[3];
	M1WriteCmd8.Compts.BlockData[n++] = (UInt8)((CardOperatBuff.Compts.ResidualMoney + CardOperatBuff.Compts.UserID) % 0xF0);
	M1WriteCmd8.Compts.BlockData[n++] = 0xFE;
	M1WriteCmd8.Compts.CRC = CardCalCRC(&M1WriteCmd8.data[2], M1WriteCmd8.Compts.FrameLen - 1);
	M1WriteCmd8.Compts.CRC = (M1WriteCmd8.Compts.CRC << 8) + (UInt8)(M1WriteCmd8.Compts.CRC >> 8);
}
UInt16 CardCalCRC(UInt8 *far UnProcess, UInt8 Len)
{
	UInt16 Crcvalue;
	UInt8 i, j;
	Crcvalue = 0xFFFF;
	for (i = 0; i < Len; i++)
	{
		Crcvalue = Crcvalue^UnProcess[i];
		for (j = 0; j < 8; j++)
		{
			if (Crcvalue & 0x0001)
			{
				Crcvalue = (Crcvalue >> 1) ^ 0x8408;
			}
			else
			{
				Crcvalue = (Crcvalue >> 1);
			}
		}
	}
	Crcvalue = ~Crcvalue;
	return Crcvalue;
}
void CardAnalysis(void)
{
	UInt8 n;
	UInt16 TmpCRC;
	MemoryList *PtrTmp;
	if (IOBuffer[1].Front->RecvFinishedFlag ==1)
	{
		n = IOBuffer[1].Front->DataSize - 4;
		TmpCRC = CardCalCRC((UInt8 *far)(&(((UInt8 *)IOBuffer[1].Front)[2+4])),n);
		if (!(((UInt8)TmpCRC == ((UInt8* )IOBuffer[1].Front)[4 + IOBuffer[1].Front->DataSize - 2]) && ((UInt8)(TmpCRC>>8) == ((UInt8*)IOBuffer[1].Front)[4 + IOBuffer[1].Front->DataSize - 1])))
		{
			PtrTmp = IOBuffer[1].Front;
			IOBufferMonitorBuffer.Compts.ExQueueReturnCode[1] = ExQueue(1);
			if (IOBufferMonitorBuffer.Compts.ExQueueReturnCode[1] == 1)
			{
				PtrTmp->DataSize = 0;
				PtrTmp->RecvFinishedFlag = 0;
				if (IOBuffer[1].BlockNum > 0)
				{
					IOBuffer[1].BlockNum -= 1;
				}
			}
			IOBufferMonitorBuffer.Compts.FullFlag[1] = 0;
			return;
		}
		if ((((UInt8*)IOBuffer[1].Front)[4] == 0x7E) && (((UInt8*)IOBuffer[1].Front)[4 + 1] == 0x55))
		{
			switch (((UInt8*)IOBuffer[1].Front)[4 + 8])
			{
			case 0x16:
				if (((UInt8*)IOBuffer[1].Front)[4 + 2] > 0x0B)
				{
					CardOperatBuff.Compts.ReadUIDSuccessfully = 1;
					CardOperatBuff.Compts.CardSystate = 1;
				}
				else
				{
					CardOperatBuff.Compts.CardSystate = 0;
				}
				break;
			case 0x70:
				switch (CardOperatBuff.Compts.CardSystate)
				{
				case 1:
					if (((UInt8*)IOBuffer[1].Front)[4 + 2] > 0x09)
					{
						CardCheckTem = 0;
						for (n = 4 + 11; n < 4 + 24; n++)
						{
							CardCheckTem += ((UInt8*)IOBuffer[1].Front)[n];
						}
						n = (UInt8)(CardCheckTem % 0x100);
						if ( n== ((UInt8*)IOBuffer[1].Front)[4 + 24])
						{
							n = ((UInt8*)IOBuffer[1].Front)[4 + 11];
							CardOperatBuff.Compts.CardCode = n;
							asm MOVB #$F0, RPAGE;//See assembly to make sure which ram page is being visited
							UserIDConvert.UInt8_Data[0] = ((UInt8*)IOBuffer[1].Front)[4 + 12];
							UserIDConvert.UInt8_Data[1] = ((UInt8*)IOBuffer[1].Front)[4 + 13];
							UserIDConvert.UInt8_Data[2] = ((UInt8*)IOBuffer[1].Front)[4 + 14];
							UserIDConvert.UInt8_Data[3] = ((UInt8*)IOBuffer[1].Front)[4 + 15];
							asm MOVB #$F1, RPAGE;
							CardOperatBuff.Compts.UserID = UserIDConvert.UInt32_Data;
							asm MOVB #$F0, RPAGE;
							CardIDConvert.UInt8_Data[0] = ((UInt8*)IOBuffer[1].Front)[4 + 19];
							CardIDConvert.UInt8_Data[1] = ((UInt8*)IOBuffer[1].Front)[4 + 20];
							CardIDConvert.UInt8_Data[2] = ((UInt8*)IOBuffer[1].Front)[4 + 21];
							CardIDConvert.UInt8_Data[3] = ((UInt8*)IOBuffer[1].Front)[4 + 22];
							asm MOVB #$F1, RPAGE;
							CardOperatBuff.Compts.CardID = CardIDConvert.UInt32_Data;
							asm MOVB #$F0, RPAGE;
							n = ((UInt8*)IOBuffer[1].Front)[4 + 23];
							asm MOVB #$F1, RPAGE;
							CardOperatBuff.Compts.CardPermission = n;
							CardOperatBuff.Compts.ReadUserIDSuccessfully = 1;
							CardOperatBuff.Compts.CardSystate = 2;
						}
					}
					else
					{
						CardOperatBuff.Compts.CardSystate = 0;
					}
					break;
				case 2:
					if (((UInt8*)IOBuffer[1].Front)[4 + 2] > 0x09)
					{
						asm MOVB #$F0, RPAGE;
						UserMoneyConvert.UInt8_Data[0] = ~(((UInt8*)IOBuffer[1].Front)[4 + 20]);
						UserMoneyConvert.UInt8_Data[1] = ~(((UInt8*)IOBuffer[1].Front)[4 + 21]);
						UserMoneyConvert.UInt8_Data[2] = ~(((UInt8*)IOBuffer[1].Front)[4 + 22]);
						UserMoneyConvert.UInt8_Data[3] = ~(((UInt8*)IOBuffer[1].Front)[4 + 23]);
						asm MOVB #$F1, RPAGE;
						CardOperatBuff.Compts.ResidualMoney = UserMoneyConvert.UInt32_Data - CardOperatBuff.Compts.CardID;
						if (((CardOperatBuff.Compts.ResidualMoney + CardOperatBuff.Compts.UserID) % 0xF0) == ((UInt8*)IOBuffer[1].Front)[4 + 24])
						{
							CardOperatBuff.Compts.ReadMoneySuccessfully = 1;
							CardOperatBuff.Compts.CardSystate = 255;
						}
						else
						{
							CardOperatBuff.Compts.ResidualMoney = 0;
						}
					}
					else
					{
						CardOperatBuff.Compts.CardSystate = 0;
					}
					break;
				}
				break;
			case 0x71:
				if (((UInt8*)IOBuffer[1].Front)[4 + 10] == 0x00)
				{
					switch (CardOperatBuff.Compts.CardSystate)
					{
					case 3:
						M1Write8Format();
						CardOperatBuff.Compts.CardSystate = 4;
						CardOperatBuff.Compts.WriteBlock2Successfully = 1;
						break;
					case 4:
						CardOperatBuff.Compts.CardSystate = 255;
						CardOperatBuff.Compts.WriteBlock8Successfully = 1;
						break;
					}
				}
				else
				{
					CardOperatBuff.Compts.CardSystate = 0;
				}
				break;

			}
		}
		PtrTmp = IOBuffer[1].Front;
		IOBufferMonitorBuffer.Compts.ExQueueReturnCode[1] = ExQueue(1);
		if (IOBufferMonitorBuffer.Compts.ExQueueReturnCode[1] == 1)
		{
			PtrTmp->DataSize = 0;
			PtrTmp->RecvFinishedFlag = 0;
			if (IOBuffer[1].BlockNum > 0)
				IOBuffer[1].BlockNum -= 1;
		}
		IOBufferMonitorBuffer.Compts.FullFlag[1] = 0;
	}
}
void CardStateControl(void)
{
	CardAnalysis();
	if (CardOperatBuff.Compts.PayByCardStart == 1)
	{
		M1Write2Format();
		CardOperatBuff.Compts.PayByCardStart = 0;
		CardOperatBuff.Compts.CardSystate = 3;
	}
	switch (CardOperatBuff.Compts.CardSystate)
	{
	case 0:
		SCI5SendN((UInt8 *far)QueryLabelCmd.data, sizeof(QueryLabelCmd));
		break;
	case 1:
		SCI5SendN((UInt8 *far)M1ReadCmd2.data, sizeof(M1ReadCmd2));
		break;
	case 2:
		SCI5SendN((UInt8 *far)M1ReadCmd8.data, sizeof(M1ReadCmd8));
		break;
	case 3:
		SCI5SendN((UInt8 *far)M1WriteCmd2.data, sizeof(M1WriteCmd2));
		break;
	case 4:
		SCI5SendN((UInt8 *far)M1WriteCmd8.data, sizeof(M1WriteCmd8));
		break;
	}
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void SCI5Card(void)
{
	static UInt16 n;
	MemoryList *PtrTmp;
	asm INC OSNesting;
	if (SCI5SR1 & 0x20)
	{
		if (n >= 124)
			n = 0;
		((UInt8*)IOBuffer[1].Rear)[n + 4] = SCI5DRL;
		++n;
		if ((((UInt8*)IOBuffer[1].Rear)[4] == 0x7E))
		{
			if ((((UInt8*)IOBuffer[1].Rear)[1 + 4] == 0x55))
			{
				if (n >= (((UInt8*)IOBuffer[1].Rear)[2 + 4] + 3))
				{
					if ((IOBuffer[1].Rear->RecvFinishedFlag == 0) && (IOBufferMonitorBuffer.Compts.FullFlag[1] == 0))
					{
						PtrTmp = IOBuffer[1].Rear;
						IOBufferMonitorBuffer.Compts.EnQueueReturnCode[1] = EnQueue(1);
						if (IOBufferMonitorBuffer.Compts.EnQueueReturnCode[1] == 1)
						{
							PtrTmp->DataSize = n;
							PtrTmp->RecvFinishedFlag = 1;
							IOBuffer[1].BlockNum += 1;
						}
						else
						{
							IOBufferMonitorBuffer.Compts.FullFlag[1] = 1;
						}
					}
					n = 0;
				}
			}
		}
		else
		{
			n = 0;
		}
	}
	asm DEC OSNesting;
}
#pragma CODE_SEG DEFAULT