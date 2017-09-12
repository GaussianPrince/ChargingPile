#include "Include.h"
#pragma DATA_SEG __RPAGE_SEG     RAMF0_T
HMIOperationStruct HMIOperationBuff;
HMITxCmd			  HMITxCmdBuff=
{
	/*PileNumQRCode*/   0x5A,0xA5,0x31,0x82,0x00,0x00,
	0x68,0x74,0x74,0x70,0x73,0x3A,0x2F,0x2F,0x6d,0x2E,
	0x67,0x6F,0x76,0x6C,0x61,0x6E,0x2E,0x63,0x6F,0x6D,
	0x2F,0x64,0x6F,0x77,0x6E,0x6C,0x6F,0x61,0x64,0x3F,
	0x63,0x3D,0x30,0x32,0x38,0x37,0x36,0x35,0x34,0x33,
	0x32,0x31,0x2D,0x31,0xff,0xff,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,
	/*PileNumText*/	    0x5A,0xA5,0x11,0x82,0x00,0x80,
	0x4E,0x4F,0x2D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x31,
	/*AppDownloadAdress*/0x5A,0xA5,0x3D,0x82,0x00,0xA0,
	0x68,0x74,0x74,0x70,0x3A,0x2F,0x2F,0x61,0x2E,0x61,
	0x70,0x70,0x2E,0x71,0x71,0x2E,0x63,0x6F,0x6D,0x2F,
	0x6F,0x2F,0x73,0x69,0x6D,0x70,0x6C,0x65,0x2E,0x6A,
	0x73,0x70,0x3F,0x70,0x6B,0x67,0x6E,0x61,0x6D,0x65,
	0x3D,0x63,0x6F,0x6D,0x2E,0x66,0x61,0x6E,0x67,0x6D,
	0x69,0x2E,0x77,0x65,0x69,0x6C,0x61,0x6E,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,
	/*AdvertisementText*/0x5A,0xA5,0x5C,0x82,0x01,0x23,
	0xBB,0xB6,0xD3,0xAD,0xCA,0xB9,0xD3,0xC3,0xB3,0xC9,
	0xB6,0xBC,0xBD,0xBB,0xCD,0xB6,0xC6,0xEC,0xCF,0xC2,
	0xB3,0xE4,0xB5,0xE7,0xD7,0xAE,0xA3,0xAC,0xCE,0xD2,
	0xC3,0xC7,0xBD,0xAB,0xBD,0xDF,0xBE,0xA1,0xC8,0xAB,
	0xC1,0xA6,0xCE,0xAA,0xC4,0xFA,0xB7,0xFE,0xCE,0xF1,
	0xA3,0xAC,0xC8,0xE7,0xD3,0xD0,0xD2,0xC9,0xCE,0xCA,
	0xC7,0xEB,0xB2,0xA6,0xB4,0xF2,0xB7,0xFE,0xCE,0xF1,
	0xC8,0xC8,0xCF,0xDF,0xA3,0xBA,0x30,0x32,0x38,0x2D,
	0x36,0x35,0x32,0x32,0x34,0x31,0x36,0x37,0xFF,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,
	/*AppStartKey*/		0x5A,0xA5,0x03,0x80,0x4F,0x01,
	/*FaultType*/  0x5A,0xA5,0x05,0x82,0x01,0xA2,0x00,0x00,
	/*CustoSerTel*/		0x5A,0xA5,0x0F,0x82,0x01,0xA3,
	0x30,0x32,0x38,0x2D,0x36,0x35,0x32,0x32,0x34,0x31,
	0x36,0x37,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,
	/*CardID*/			0x5A,0xA5,0x14,0x82,0x01,0xC5,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,
	/*CardMoney*/		0x5A,0xA5,0x07,0x82,0x01,0xE5,
	0x00,0x00,0x00,0x00,
	/*TipText*/			0x5A,0xA5,0x13,0x82,0x01,0xE9,
	0xD3,0xE0,0xB6,0xEE,0xB5,0xCD,0xD3,0xDA,0xD7,0xEE,
	0xB4,0xF3,0xB5,0xA5,0xBC,0xDB,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,
	/*TipClear*/		0x5A,0xA5,0x13,0x82,0x01,0xE9,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,
	/*GunConText*/		0x5A,0xA5,0x0F,0x82,0x02,0x0B,
	0xB3,0xE4,0xB5,0xE7,0xC7,0xB9,0xD2,0xD1,0xC1,0xAC,
	0xBD,0xD3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,
	/*GunUnConText*/    0x5A,0xA5,0x0F,0x82,0x02,0x0B,
	0xB3,0xE4,0xB5,0xE7,0xC7,0xB9,0xCE,0xB4,0xC1,0xAC,
	0xBD,0xD3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,
	/*CardStartKey*/    0x5A,0xA5,0x03,0x80,0x4F,0x02,
	/*TimingStartKey*/  0x5A,0xA5,0x03,0x80,0x4F,0x03,
	/*AppStartBack*/    0x5A,0xA5,0x03,0x80,0x4F,0x04,
	/*CardStartBack*/   0x5A,0xA5,0x03,0x80,0x4F,0x05,
	/*EchoVol*/			0x5A,0xA5,0x05,0x82,0x02,0x30,
	0x00,0x00,
	/*EchoCur*/			0x5A,0xA5,0x05,0x82,0x02,0x31,
	0x00,0x00,
	/*EchoPower*/		0x5A,0xA5,0x05,0x82,0x02,0x32,
	0x00,0x00,0x00,0x00,
	/*EchoBatLow*/		0x5A,0xA5,0x05,0x82,0x02,0x33,
	0x00,0x00,
	/*EchoBatHigh*/		0x5A,0xA5,0x05,0x82,0x02,0x34,
	0x00,0x00,
	/*EchoChargedFee*/	0x5A,0xA5,0x07,0x82,0x02,0x35,
	0x00,0x00,0x00,0x00,
	/*EchoChargedAmount*/0x5A,0xA5,0x05,0x82,0x02,0x37,
	0x00,0x00,
	/*EchoSerPrice*/	0x5A,0xA5,0x07,0x82,0x02,0x38,
	0x00,0x00,0x00,0x00,
	/*EchoChargedTime*/ 0x5A,0xA5,0x05,0x82,0x02,0x3A,
	0x00,0x00,
	/*EchoSOC*/		    0x5A,0xA5,0x05,0x82,0x02,0x3B,
	0x00,0x00,
	/*OrderNum*/	    0x5A,0xA5,0x07,0x82,0x02,0x3D,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/*EndElectricity*/  0x5A,0xA5,0x05,0x82,0x02,0x5D,
	0x00,0x00,
	/*EndMoney*/	     0x5A,0xA5,0x07,0x82,0x02,0x5E,
	0x00,0x00,0x00,0x00,
	/*PileNumRec*/	     0x5A,0xA5,0x0D,0x82,0x02,0x6C,
	 0x30,0x32,0x38,0x31,0x37,0x30,0x35,0x32,0x31,0x38,
	/*NetModeRec1*/		 0x5A,0xA5,0x05,0x82,0x02,0x69,
	0x00,0x00,
	/*NetModeRec2*/		 0x5A,0xA5,0x05,0x82,0x02,0x6A,
	0x00,0x00,
	/*NetModeRec3*/		 0x5A,0xA5,0x05,0x82,0x02,0x6B,
	0x00,0x00,
	/*SSIDRec*/			 0x5A,0xA5,0x00,0x82,0x02,0x8C,  
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/*PwdRec*/			 0x5A,0xA5,0x00,0x82,0x02,0xAC,  
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/*LocalPortRec*/	 0x5A,0xA5,0x05,0x82,0x02,0xCC,
	 0x00,0x00,
	/*RemotePortRec*/	 0x5A,0xA5,0x05,0x82,0x02,0xCD,
	 0x00,0x00,
	/*RemoteIPRec1*/     0x5A,0xA5,0x05,0x82,0x02,0xCE,
	 0x00,0x00,
	/*RemoteIPRec2*/	 0x5A,0xA5,0x05,0x82,0x02,0xCF,
	 0x00,0x00,
	/*RemoteIPRec3*/	 0x5A,0xA5,0x05,0x82,0x02,0xD0,
	 0x00,0x00,
	/*RemoteIPRec4*/	 0x5A,0xA5,0x05,0x82,0x02,0xD1,
	 0x00,0x00,
	/*LocalIPRec1*/		 0x5A,0xA5,0x05,0x82,0x02,0xD2,
	 0x00,0x00,
	/*LocalIPRec2*/		 0x5A,0xA5,0x05,0x82,0x02,0xD3,
	 0x00,0x00,
	/*LocalIPRec3*/		 0x5A,0xA5,0x05,0x82,0x02,0xD4,
	 0x00,0x00,
	/*LocalIPRec4*/		 0x5A,0xA5,0x05,0x82,0x02,0xD5,
	 0x00,0x00,
	/*CardAgain*/		  0x5A,0xA5,0x0D,0x82,0x03,0x50,
	0xC7,0xEB,0xD4,0xD9,0xB4,0xCE,0xCB,0xA2,0xBF,0xA8,
	/*CardAgainClr*/	  0x5A,0xA5,0x0D,0x82,0x03,0x50,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	
	/*EchoPrice*/		 0x5A,0xA5,0x05,0x82,0x03,0x31,
	0x00,0x00,
	/*EchoCardEnable*/	 0x5A,0xA5,0x07,0X82,0x02,0xF9,
	0xBF,0xC9,0xD3,0xC3,0x00,0x00,
	/*EchoCardDisable*/  0x5A,0xA5,0x07,0X82,0x02,0xF9,
	0xBD,0xFB,0xD3,0xC3,0x00,0x00,
	/*EchoEnd*/			 0x5A,0xA5,0x0D,0x82,0x02,0xD9,
	 0xB3,0xE4,0xB5,0xE7,0xD2,0xD1,0xBD,0xE1,0xCA,0xF8,
	/*EchoEndClr*/		 0x5A,0xA5,0x0D,0x82,0x02,0xD9,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/*HMIWriteRTC*/					 0x5A,0xA5,0x0A,0x80,0x1F,0x5A,
	 0x17,0x05,0x17,0x00,0x17,0x19,0x00,
	/*WritePageReg*/	 0x5A,0xA5,0x04,0x80,0x03,0x00,
	 0x00,
	/*WriteNetConFlag*/	 0x5A,0xA5,0x05,0x82,0x02,0xD8,
	 0x00,0x00
};
UInt8  ConfigWait;
UInt8	PwdCounter;
UInt8  ExistError;
UInt8  ErrorSendOnce;
UInt32 AdminPwd=20171996;
#pragma DATA_SEG DEFAULT
UInt8  ErrorTypeMap[] = {
	6,10,1,0,4,13,14
};
UInt8  FaultBitCompare[] = {
	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80
};
UInt32	HMIVol;
UInt32	HMICur;
UInt32	Power;
UInt8	WaitInHome;
UInt16  WaitBackHome;
UInt8	Calender;
UInt8	PwdErrorCounter;
static UInt8 HexConvertToBCD(UInt8 hex)
{
	UInt8 result = 0;
	result = hex % 10;
	result = (UInt8)(((hex / 10) % 10) << 4) + result;
	return result;
}
static void WriteHMICalendar(void)
{
	HMITxCmdBuff.Compts.HMIWriteRTC[6] = LocalTimeBuff.Compts.Year % 10;
	HMITxCmdBuff.Compts.HMIWriteRTC[6] = HMITxCmdBuff.Compts.HMIWriteRTC[6] +
		(UInt8)(((LocalTimeBuff.Compts.Year / 10) % 10) << 4);
	HMITxCmdBuff.Compts.HMIWriteRTC[7] = HexConvertToBCD(LocalTimeBuff.Compts.Month);
	HMITxCmdBuff.Compts.HMIWriteRTC[8] = HexConvertToBCD(LocalTimeBuff.Compts.Day);
	HMITxCmdBuff.Compts.HMIWriteRTC[10] = HexConvertToBCD(LocalTimeBuff.Compts.Hour);
	HMITxCmdBuff.Compts.HMIWriteRTC[11] = HexConvertToBCD(LocalTimeBuff.Compts.Minute);
	HMITxCmdBuff.Compts.HMIWriteRTC[12] = HexConvertToBCD(LocalTimeBuff.Compts.Second);
}
void SCI0Init(void)
{
	asm
	{
		MOVB #$00,SCI0BDH
		MOVB #$20,SCI0BDL
		MOVB #$00,SCI0CR1
		MOVB #$2C,SCI0CR2
	}
}
void SCI0SendN(UInt8 * far InData, UInt8 Len)
{
	UInt8 n;
	for (n = 0; n < Len;)
	{
		if ((SCI0SR1 & 0x80) != 0)
		{
			SCI0DRL = InData[n];
			n++;
		}
	}
}
void  HMIAnalysis(void)
{
	UInt8 n;
	UInt8 i;
	MemoryList *PtrTmp;
	if (IOBuffer[0].Front->RecvFinishedFlag == 1)
	{
		switch (((UInt8*)IOBuffer[0].Front)[4+3])
		{
		case 0x83:
			if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x01) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xA0))
			{
				if (ConfigWait < 250)
				{
					ConfigWait = 0;
					HMIOperationBuff.Compts.ConfigClicks++;
					if (HMIOperationBuff.Compts.ConfigClicks == 20)
					{
						asm MOVB #$F1, RPAGE;
						if (CardOperationBuff.Compts.QueryInf == 0)
						{
							asm MOVB #$F0, RPAGE;
							HMIOperationBuff.Compts.CurrentPageNum = 16;
							HMIOperationBuff.Compts.ConfigClicks = 0;
						}
					}
				}
				else
				{
					HMIOperationBuff.Compts.ConfigClicks = 0;
				}
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x03) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x4a))
			{
				HMIOperationBuff.Compts.TieredEchoCmd = 1;
				HMIOperationBuff.Compts.CurrentPageNum = 21;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x01) && (((UInt8*)IOBuffer[0].Front)[4 + 5] ==0xC3))
			{
				ExistError = 0;
				for (n = HMIOperationBuff.Compts.TraverseFault; n > 0; n--)
				{
					if (CharFaultBuff.data[0] & FaultBitCompare[n])
					{
						if (n != HMIOperationBuff.Compts.TraverseFault)
						{
							ExistError = 1;
							HMIOperationBuff.Compts.TraverseFault = n;
							break;
						}
					}
				}
				if (ExistError == 0)
				{
					if (CharFaultBuff.data[0] & FaultBitCompare[0])
						HMIOperationBuff.Compts.TraverseFault = 0;
				}
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x01) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xC4))
			{
				ExistError = 0;
				for (n = HMIOperationBuff.Compts.TraverseFault; n<7; n++)
				{
					if (CharFaultBuff.data[0] & FaultBitCompare[n])
					{
						if (n != HMIOperationBuff.Compts.TraverseFault)
						{
							ExistError = 1;
							HMIOperationBuff.Compts.TraverseFault = n;
							break;
						}
					}
				}
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x0A))
			{
				HMIOperationBuff.Compts.GunConStaReflesh = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x2B))
			{
				asm MOVB #$F1, RPAGE;
				UserMoneyConvert.UInt16_Data[0] = DiffPriceBuff.Compts.CloudDiffPrice[0];
				for (n = 0; n < 24; n++)
				{
					if (UserMoneyConvert.UInt16_Data[0] < DiffPriceBuff.Compts.CloudDiffPrice[n])
					{
						UserMoneyConvert.UInt16_Data[0] = DiffPriceBuff.Compts.CloudDiffPrice[n];
					}
				}
				if (CardOperationBuff.Compts.ResidualMoney >= UserMoneyConvert.UInt16_Data[0])
				{
					EFlashReadWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 73);
					if (EFlashMainBuff.Compts.SerialNum == 0xFFFFFFFF)
					{
						SerialNumTmp = 0;
					}
					else
					{
						SerialNumTmp = EFlashMainBuff.Compts.SerialNum + 1;
					}
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Year = (UInt8)(LocalTimeBuff.Compts.Year >> 8) + (LocalTimeBuff.Compts.Year << 8);;
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Month = LocalTimeBuff.Compts.Month;
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Day = LocalTimeBuff.Compts.Day;
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Hour = LocalTimeBuff.Compts.Hour;
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Minute = LocalTimeBuff.Compts.Minute;
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Second = LocalTimeBuff.Compts.Second;
					CardOperationBuff.Compts.Permission = 0;
					CardOperationBuff.Compts.PayByCardStart = 1;
					asm MOVB #$F0, RPAGE;
					HMIOperationBuff.Compts.AutoCharging = 1;
#ifdef SCI4ENDTEST
					SCI4EndCounter = 0;
#endif // SCI4ENDTEST
				}
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x2C))
			{
				HMIOperationBuff.Compts.CurrentPageNum = 11;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x2D))
			{
				HMIOperationBuff.Compts.BackToHome = ((UInt8*)IOBuffer[0].Front)[4 + 8];
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x3C))
			{
				HMIOperationBuff.Compts.CardConfirm = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x60))
			{
				HMIOperationBuff.Compts.BackToChargingPage = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x61))
			{
				asm MOVB #$F1, RPAGE;
				UserMoneyConvert.UInt16_Data[0] = DiffPriceBuff.Compts.CloudDiffPrice[0];
				for (n = 0; n < 24; n++)
				{
					if (UserMoneyConvert.UInt16_Data[0] < DiffPriceBuff.Compts.CloudDiffPrice[n])
					{
						UserMoneyConvert.UInt16_Data[0] = DiffPriceBuff.Compts.CloudDiffPrice[n];
					}
				}
				if (CardOperationBuff.Compts.ResidualMoney >= UserMoneyConvert.UInt16_Data[0])
				{
					EFlashReadWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 73);
					if (EFlashMainBuff.Compts.SerialNum == 0xFFFFFFFF)
					{
						SerialNumTmp = 0;
					}
					else
					{
						SerialNumTmp = EFlashMainBuff.Compts.SerialNum + 1;
					}
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Year = (UInt8)(LocalTimeBuff.Compts.Year >> 8) + (LocalTimeBuff.Compts.Year << 8);;
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Month = LocalTimeBuff.Compts.Month;
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Day = LocalTimeBuff.Compts.Day;
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Hour = LocalTimeBuff.Compts.Hour;
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Minute = LocalTimeBuff.Compts.Minute;
					TimeRecFormatArrBuff.Compts.TimeRecFormatData[0].Compts.Second = LocalTimeBuff.Compts.Second;
					CardOperationBuff.Compts.Permission = 0;
					CardOperationBuff.Compts.PayByCardStart = 1;
					asm MOVB #$F0, RPAGE;
					HMIOperationBuff.Compts.ChargingTime = (UInt16)(((UInt8*)IOBuffer[0].Front)[4 + 7] << 8) + ((UInt8*)IOBuffer[0].Front)[4 + 8];
					HMIOperationBuff.Compts.TimingCharging = 1;
#ifdef SCI4ENDTEST
					SCI4EndCounter = 0;
#endif // SCI4ENDTEST
				}
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x62))
			{
				HMIOperationBuff.Compts.BackToCardOperationPage = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xD6))
			{
				if ((((UInt8*)IOBuffer[0].Front)[4 + 7] == 0x01)
					&& (((UInt8*)IOBuffer[0].Front)[4 + 8] == 0x33)
					&& (((UInt8*)IOBuffer[0].Front)[4 + 9] == 0xCC)
					&& (((UInt8*)IOBuffer[0].Front)[4 + 10] == 0xDC))
				{
					if (PwdErrorCounter < 5)
					{
						HMIOperationBuff.Compts.AdminEntry = 1;
						HMIOperationBuff.Compts.CurrentPageNum = 14;
					}
				}
				else
				{
					PwdErrorCounter++;
				}
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x64))
			{
				HMIOperationBuff.Compts.NetConfigSave = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x65))
			{
				EFlashReadWord(0x10, 0x00,(UInt16 *far) EFlashMainBuff.data, 73);
				asm MOVB #$F1, RPAGE;
				if (EFlashMainBuff.Compts.PileNum[0] != 0xFF)
				{
					for (n = 0; n < 10; n++)
					{
						asm MOVB #$F1, RPAGE;
						UserMoneyConvert.UInt8_Data[0] = EFlashMainBuff.Compts.PileNum[n];
						asm MOVB #$F0, RPAGE;
						HMITxCmdBuff.Compts.ConfigPage.PileNumRec[6 + n] = UserMoneyConvert.UInt8_Data[0];
					}
				}
				asm MOVB #$F1, RPAGE;
				if (EFlashMainBuff.Compts.ConnMethod != 0xFF)
				{		
					switch (EFlashMainBuff.Compts.ConnMethod)
					{
					case 0:
						asm MOVB #$F0, RPAGE;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[6] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[7] = 1;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[6] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[7] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[6] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[7] = 0;
						break;
					case 1:
						asm MOVB #$F0, RPAGE;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[6] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[7] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[6] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[7] = 1;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[6] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[7] = 0;
						break;
					case 2:
						asm MOVB #$F0, RPAGE;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[6] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[7] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[6] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[7] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[6] = 0;
						HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[7] = 1;
						break;
					}
				}
				asm MOVB #$F1, RPAGE;
				if (EFlashMainBuff.Compts.SSIDWIFI[0] != 0xFF)
				{
					n = EFlashMainBuff.Compts.SSIDWIFI[0];
					asm MOVB #$F0, RPAGE;
					HMITxCmdBuff.Compts.ConfigPage.SSIDRec[2] = n;
					for (i = 0; i < n; i++)
					{
						asm MOVB #$F1, RPAGE;
						UserMoneyConvert.UInt8_Data[0] = EFlashMainBuff.Compts.SSIDWIFI[i];
						asm MOVB #$F0, RPAGE;
						HMITxCmdBuff.Compts.ConfigPage.SSIDRec[i + 6]=UserMoneyConvert.UInt8_Data[0];
					}
				}
				asm MOVB #$F1, RPAGE;
				if (EFlashMainBuff.Compts.WIFIPwd[0] != 0xFF)
				{
					n = EFlashMainBuff.Compts.WIFIPwd[0];
					asm MOVB #$F0, RPAGE;
					HMITxCmdBuff.Compts.ConfigPage.PwdRec[2] = n;
					for (i = 0; i < n; i++)
					{
						asm MOVB #$F1, RPAGE;
						UserMoneyConvert.UInt8_Data[0] = EFlashMainBuff.Compts.WIFIPwd[i];
						asm MOVB #$F0, RPAGE;
						HMITxCmdBuff.Compts.ConfigPage.PwdRec[i + 6] = UserMoneyConvert.UInt8_Data[0];
					}
				}
				asm MOVB #$F1, RPAGE;
				if (EFlashMainBuff.Compts.RemotePort != 0xFFFF)
				{
					UserMoneyConvert.UInt8_Data[0] =(UInt8)( EFlashMainBuff.Compts.RemotePort>>8);
					UserMoneyConvert.UInt8_Data[1] = (UInt8)EFlashMainBuff.Compts.RemotePort;
					asm MOVB #$F0, RPAGE;
					HMITxCmdBuff.Compts.ConfigPage.RemotePortRec[6] = UserMoneyConvert.UInt8_Data[0];
					HMITxCmdBuff.Compts.ConfigPage.RemotePortRec[7] = UserMoneyConvert.UInt8_Data[1];
				}
				asm MOVB #$F1, RPAGE;
				if (EFlashMainBuff.Compts.RemoteIP[0] != 255)
				{
					for (n = 0; n < 4; n++)
					{
						UserMoneyConvert.UInt8_Data[n] = EFlashMainBuff.Compts.RemoteIP[n];
					}
					asm MOVB #$F0, RPAGE;
					HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec1[6] = 0x00;
					HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec1[7] = UserMoneyConvert.UInt8_Data[0];
					HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec2[6] = 0x00;
					HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec2[7] = UserMoneyConvert.UInt8_Data[1];
					HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec3[6] = 0x00;
					HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec3[7] = UserMoneyConvert.UInt8_Data[2];
					HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec4[6] = 0x00;
					HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec4[7] = UserMoneyConvert.UInt8_Data[3];
				}
				HMIOperationBuff.Compts.NetConfigRead = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x66))
			{
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[6] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[7] = 1;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[6] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[7] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[6] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[0] = 0;
				HMIOperationBuff.Compts.NetworkMethod[0] = 1;
				HMIOperationBuff.Compts.NetworkMethod[1] = 0;
				HMIOperationBuff.Compts.NetworkMethod[2] = 0;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x67))
			{
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[6] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[7] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[6] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[7] = 1;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[6] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[0] = 0;
				HMIOperationBuff.Compts.NetworkMethod[0] = 0;
				HMIOperationBuff.Compts.NetworkMethod[1] = 1;
				HMIOperationBuff.Compts.NetworkMethod[2] = 0;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x68))
			{
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[6] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec1[7] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[6] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec2[7] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[6] = 0;
				HMITxCmdBuff.Compts.ConfigPage.NetModeRec3[7] = 1;
				HMIOperationBuff.Compts.NetworkMethod[0] = 0;
				HMIOperationBuff.Compts.NetworkMethod[1] = 0;
				HMIOperationBuff.Compts.NetworkMethod[2] = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x6C))
			{
				for (n = 6; n < IOBuffer[0].Front->DataSize; n++)
				{
					if ((((UInt8*)IOBuffer[0].Front)[4 + n] >= '0') && (((UInt8*)IOBuffer[0].Front)[4 + n] <= '9'))
						HMITxCmdBuff.Compts.ConfigPage.PileNumRec[n] = ((UInt8*)IOBuffer[0].Front)[4 + n + 1];
				}
				HMITxCmdBuff.Compts.ConfigPage.PileNumRec[2] = 13;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x8C))
			{
			    PwdCounter=0;
				for (n = 6; n < IOBuffer[0].Front->DataSize; n++)
				{
					if ((((UInt8*)IOBuffer[0].Front)[4 + n] != 255) && (((UInt8*)IOBuffer[0].Front)[4 + n] != 0))
					{
						HMITxCmdBuff.Compts.ConfigPage.SSIDRec[n] = ((UInt8*)IOBuffer[0].Front)[4 + n];
						PwdCounter++;
					}
				}
				HMITxCmdBuff.Compts.ConfigPage.SSIDRec[2] = PwdCounter + 3;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xAC))
			{
				PwdCounter = 0;
				for (n = 6; n < IOBuffer[0].Front->DataSize; n++)
				{
					if ((((UInt8*)IOBuffer[0].Front)[4 + n] != 255)&&(((UInt8*)IOBuffer[0].Front)[4 + n] != 0))
					{
						HMITxCmdBuff.Compts.ConfigPage.PwdRec[n] = ((UInt8*)IOBuffer[0].Front)[4 + n+1];
						PwdCounter++;
					}
				}
				HMITxCmdBuff.Compts.ConfigPage.PwdRec[2] = PwdCounter + 3;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xCD))
			{
				HMITxCmdBuff.Compts.ConfigPage.RemotePortRec[6] = ((UInt8*)IOBuffer[0].Front)[7+4];
				HMITxCmdBuff.Compts.ConfigPage.RemotePortRec[7] = ((UInt8*)IOBuffer[0].Front)[4+8];
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xCE))
			{
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec1[6] = ((UInt8*)IOBuffer[0].Front)[4+7];
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec1[7] = ((UInt8*)IOBuffer[0].Front)[4+8];
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xCF))
			{
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec2[6] = ((UInt8*)IOBuffer[0].Front)[4+7];
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec2[7] = ((UInt8*)IOBuffer[0].Front)[4+8];
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xD0))
			{
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec3[6] = ((UInt8*)IOBuffer[0].Front)[4+7];
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec3[7] = ((UInt8*)IOBuffer[0].Front)[4+8];
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xD1))
			{
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec4[6] = ((UInt8*)IOBuffer[0].Front)[4+7];
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec4[7] = ((UInt8*)IOBuffer[0].Front)[4+8];
			}
			break;
		}
		asm MOVB #$F0, RPAGE;
		PtrTmp = IOBuffer[0].Front;
		IOBufferMonitorBuffer.Compts.ExQueueReturnCode[0] = ExQueue(0);
		if (IOBufferMonitorBuffer.Compts.ExQueueReturnCode[0] == 1)
		{
			PtrTmp->DataSize = 0;
			PtrTmp->RecvFinishedFlag = 0;
			if (IOBuffer[0].BlockNum > 0)
				IOBuffer[0].BlockNum -= 1;
		}
		IOBufferMonitorBuffer.Compts.FullFlag[0] = 0;
	}
}
void HMIDisplayControl(void)
{
	UInt8 n;
//	UInt8 i;
	static UInt8 BackFirst=0;
	static UInt8 BackFirst1 = 0;
	static UInt8 ErrorFirst = 0;
	HMIAnalysis();
	switch (BMSComCtlBuff.Compts.SystemState)
	{
	case 0:
		if (HMIOperationBuff.Compts.ConfigClicks != 0)
		{
			ConfigWait++;
			if (ConfigWait >= 60)
			{
				HMIOperationBuff.Compts.ConfigClicks = 0;
				ConfigWait = 0;
			}
		}
		switch (HMIOperationBuff.Compts.CurrentPageNum)
		{
		case 0:
			HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
			HMITxCmdBuff.Compts.WritePageReg[6] = 0x00;
			SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.FaultPage.CustoSerTel, 18);
			SCI0SendN(HMITxCmdBuff.Compts.HomePage.AdvertisementText, 95);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.CardAgainClr, 16);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoEndClr, 16);
		//	SCI0SendN(HMITxCmdBuff.Compts.HomePage.AppDownloadAdress, (HMITxCmdBuff.Compts.HomePage.AppDownloadAdress[2] + 3));
		//	SCI0SendN(HMITxCmdBuff.Compts.HomePage.PileNumQRCode, (HMITxCmdBuff.Compts.HomePage.PileNumQRCode[2] + 3));
		//	SCI0SendN(HMITxCmdBuff.Compts.HomePage.PileNumText, (HMITxCmdBuff.Compts.HomePage.PileNumText[2] + 3));
			asm MOVB #$F1, RPAGE;
			if (WaitInHome < 150)
			{
				CardOperationBuff.Compts.CardSystate = 203;
				WaitInHome++;
			}
			else if(WaitInHome==150)
			{
				WaitInHome = 151;
				CardOperationBuff.Compts.CardSystate = 0;
			}
			else if (CardOperationBuff.Compts.QueryInf==1)
			{
				asm BSET SCI4OperatBuff.data[519], #$80;
				asm MOVW #$0000,WaitBackHome;
				asm MOVB #$F0, RPAGE;
				asm MOVB #$02,HMIOperationBuff.Compts.CurrentPageNum ;
			}
			break;
		case 1:
			MyMemsetFar((UInt8 *far)CardOperationBuff.data, 0, 30);
			MyMemsetFar((UInt8 *far)HMIOperationBuff.data, 0, 21);
			asm BSET DIDOBuff.data[1], #$08;
			asm BCLR DIDOBuff.data[1], #$14;
			asm  CLR BMSComCtlBuff.data[0];
			asm  CLR BMSComCtlBuff.data[1];
			asm  CLR WaitInHome;
			asm  CLR ErrorFirst;
			asm MOVB #$F0, RPAGE;
			asm CLR  ErrorSendOnce;
			break;
		case 2:
			asm MOVB #$F0, RPAGE;
			if (HMIOperationBuff.Compts.AutoCharging == 1 || HMIOperationBuff.Compts.TimingCharging == 1)
			{
				SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.CardAgain, 16);
			}
			HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
			HMITxCmdBuff.Compts.WritePageReg[6] = 2;
			SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
			if (HMIOperationBuff.Compts.BackToHome == 1)
			{
				HMIOperationBuff.Compts.BackToHome = 0;
				MyMemsetFar((UInt8 *far)CardOperationBuff.data, 0, 30);
				MyMemsetFar((UInt8 *far)HMIOperationBuff.data, 0, 21);
				asm  CLR WaitInHome;

			}
			asm MOVB #$F1, RPAGE;
			if (CardOperationBuff.Compts.PermissionOld == 1)
			{
				SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoCardEnable, 10);
			}
			else
			{
				SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoCardDisable, 10);
			}
			asm MOVB #$F1, RPAGE;
			UserMoneyConvert.UInt32_Data = CardOperationBuff.Compts.ResidualMoney;
			if (GunBuff.Compts.CC1 == 1)
			{
				SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.CardOperationPage.GunConText, 18);
			}
			else
			{
				SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.CardOperationPage.GunUnConText, 18);
			}
			WaitBackHome++;
			if (WaitBackHome > 1800)
			{
				MyMemsetFar((UInt8 *far)CardOperationBuff.data, 0, 30);
				MyMemsetFar((UInt8 *far)HMIOperationBuff.data, 0, 21);
				asm  CLR WaitInHome;
			}
			asm MOVB #$F0, RPAGE;
			HMITxCmdBuff.Compts.CardOperationPage.CardMoney[6] = UserMoneyConvert.UInt8_Data[0];
			HMITxCmdBuff.Compts.CardOperationPage.CardMoney[7] = UserMoneyConvert.UInt8_Data[1];
			HMITxCmdBuff.Compts.CardOperationPage.CardMoney[8] = UserMoneyConvert.UInt8_Data[2];
			HMITxCmdBuff.Compts.CardOperationPage.CardMoney[9] = UserMoneyConvert.UInt8_Data[3];
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.CardOperationPage.CardID, 23);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.CardOperationPage.CardMoney, 10);
			break;
		case 11:
			asm MOVB #$F0, RPAGE;
			if (HMIOperationBuff.Compts.AutoCharging == 1 || HMIOperationBuff.Compts.TimingCharging == 1)
			{
				SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.CardAgain, 16);
			}
			HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
			HMITxCmdBuff.Compts.WritePageReg[6] = 11;
			SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
			if (HMIOperationBuff.Compts.BackToHome == 4)
			{
				HMIOperationBuff.Compts.BackToHome = 0;
				HMIOperationBuff.Compts.CurrentPageNum = 0;
			}
			else if (HMIOperationBuff.Compts.BackToCardOperationPage == 1)
			{
				HMIOperationBuff.Compts.BackToCardOperationPage = 0;
				HMIOperationBuff.Compts.CurrentPageNum = 2;
			}
			break;
		case 16:
			HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
			HMITxCmdBuff.Compts.WritePageReg[6] = 16;
			SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
			if (HMIOperationBuff.Compts.BackToHome == 6)
			{
				HMIOperationBuff.Compts.BackToHome = 0;
				HMIOperationBuff.Compts.CurrentPageNum = 0;
			}
			break;
		case 14:
			HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
			HMITxCmdBuff.Compts.WritePageReg[6] = 14;
			SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
			if (HMIOperationBuff.Compts.NetConfigRead)
			{
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.PileNumRec, 16);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.NetModeRec1, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.NetModeRec2, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.NetModeRec3, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.SSIDRec, (HMITxCmdBuff.Compts.ConfigPage.SSIDRec[2] + 3));
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.PwdRec, (HMITxCmdBuff.Compts.ConfigPage.PwdRec[2] + 3));
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.LocalPortRec, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.RemotePortRec, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec1, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec2, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec3, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec4, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.LocalIPRec1, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.LocalIPRec2, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.LocalIPRec3, 8);
				SCI0SendN(HMITxCmdBuff.Compts.ConfigPage.LocalIPRec4, 8);
				SCI0SendN(HMITxCmdBuff.Compts.FaultPage.CustoSerTel, (HMITxCmdBuff.Compts.FaultPage.CustoSerTel[2] + 3));
			}
			if (HMIOperationBuff.Compts.NetConfigSave)
			{
				HMIOperationBuff.Compts.NetConfigSave = 0;
				HMIOperationBuff.Compts.CurrentPageNum = 0;
			}
			break;
		case 21:
			asm MOVB #$F1, RPAGE;
			asm MOVB #$FF, CardOperationBuff.Compts.CardSystate;
			asm MOVB #$F0, RPAGE;
			if (HMIOperationBuff.Compts.BackToHome == 7)
			{
				HMIOperationBuff.Compts.CurrentPageNum = 0;
				HMIOperationBuff.Compts.BackToHome = 0;
				HMIOperationBuff.Compts.TieredEchoCmd = 0;
				asm  CLR WaitInHome;
				break;
			}
			for (n = 0; n < 24; n++)
			{
				HMITxCmdBuff.Compts.EchoPrice[4] = 0x03;
				HMITxCmdBuff.Compts.EchoPrice[5] = 0x31 + n;
				HMITxCmdBuff.Compts.EchoPrice[6] = (UInt8)(DiffPriceBuff.Compts.CloudDiffPrice[n] >> 8);
				HMITxCmdBuff.Compts.EchoPrice[7] = (UInt8)(DiffPriceBuff.Compts.CloudDiffPrice[n]);
				SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoPrice, 8);
			}
			HMITxCmdBuff.Compts.EchoPrice[4] = 0x03;
			HMITxCmdBuff.Compts.EchoPrice[5] = 0x49;
			HMITxCmdBuff.Compts.EchoPrice[6] = (UInt8)(DiffPriceBuff.Compts.CloudServicePrice >> 8);
			HMITxCmdBuff.Compts.EchoPrice[7] = (UInt8)(DiffPriceBuff.Compts.CloudServicePrice);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoPrice, 8);
			HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
			HMITxCmdBuff.Compts.WritePageReg[6] = 21;
			SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
			break;
		}
		break;
	case 1:
	case 2:
		BackFirst = 1;
		BackFirst1 = 1;
		FaultPay = 0;//Entry of Pay operation ******Very  Important
		if (HMIOperationBuff.Compts.AutoCharging)
		{
			SCI0SendN(HMITxCmdBuff.Compts.CardOperationPage.CardStartKey, 6);
		}
		else if (HMIOperationBuff.Compts.TimingCharging)
		{
			SCI0SendN(HMITxCmdBuff.Compts.CardOperationPage.TimingStartKey, 6);
		}
		asm MOVB #$F1, RPAGE;
		asm CLR FaultEcho;
		break;
	case 3:
		if (BackFirst == 1)
		{
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.StartupPage.CardStartBack, 6);// Disturb 
			BackFirst = 0;
			asm MOVB #$F1, RPAGE;
			CardMutex = 0;
		}
		asm MOVB #$F0, RPAGE;
		if (HMIOperationBuff.Compts.CardConfirm == 0)
		{
			HMITxCmdBuff.Compts.ChargingPage.EchoVol[6] = (UInt8)(CAN0OperationBuff.Compts.TotalVol >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoVol[7] = (UInt8)(CAN0OperationBuff.Compts.TotalVol);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.ChargingPage.EchoVol, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoCur[6] = (UInt8)(CAN0OperationBuff.Compts.TotalCur >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoCur[7] = (UInt8)(CAN0OperationBuff.Compts.TotalCur);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.ChargingPage.EchoCur, 8);
			HMIVol = CAN0OperationBuff.Compts.TotalVol;
			HMICur = CAN0OperationBuff.Compts.TotalCur;
			Power = HMICur*HMIVol/ 1000;
			HMITxCmdBuff.Compts.ChargingPage.EchoPower[6] = (UInt8)(Power >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoPower[7] = (UInt8)(Power);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.ChargingPage.EchoPower, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoBatLow[6] = 0x00;
			HMITxCmdBuff.Compts.ChargingPage.EchoBatLow[7] = BSMData.Compts.LowestTemp;
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.ChargingPage.EchoBatLow, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoBatHigh[6] = 0x00;
			HMITxCmdBuff.Compts.ChargingPage.EchoBatHigh[7] = BSMData.Compts.HighestTemp;
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.ChargingPage.EchoBatHigh, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedFee[6] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 24);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedFee[7] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 16);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedFee[8] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedFee[9] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.ChargingPage.EchoChargedFee, 10);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedAmount[6] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedAmount[7] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.ChargingPage.EchoChargedAmount, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoSerPrice[6] = (UInt8)(CostManagementBuff.Compts.CostServicePrice >> 24);
			HMITxCmdBuff.Compts.ChargingPage.EchoSerPrice[7] = (UInt8)(CostManagementBuff.Compts.CostServicePrice >> 16);
			HMITxCmdBuff.Compts.ChargingPage.EchoSerPrice[8] = (UInt8)(CostManagementBuff.Compts.CostServicePrice >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoSerPrice[9] = (UInt8)(CostManagementBuff.Compts.CostServicePrice);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.ChargingPage.EchoSerPrice, 10);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedTime[6] = (UInt8)(CCSData.Compts.TotalChargTime >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedTime[7] = (UInt8)(CCSData.Compts.TotalChargTime);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.ChargingPage.EchoChargedTime, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoSOC[6] = 0x00;
			HMITxCmdBuff.Compts.ChargingPage.EchoSOC[7] = BCSData.Compts.SOCNow;
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.ChargingPage.EchoSOC, 8);
			HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
			HMITxCmdBuff.Compts.WritePageReg[6] = 4;
			SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
			asm MOVB #$F1, RPAGE;
			if (CardOperationBuff.Compts.FeeOp == 1)
			{
				BMSComCtlBuff.Compts.StopCharging = 1;
			}
		}
		else
		{
			if (HMIOperationBuff.Compts.BackToChargingPage != 1)
			{
				HMIOperationBuff.Compts.CurrentPageNum = 8;
				HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
				HMITxCmdBuff.Compts.WritePageReg[6] = 8;
				SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
				HMITxCmdBuff.Compts.EndPage.EndElectricity[6] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity >> 8);
				HMITxCmdBuff.Compts.EndPage.EndElectricity[7] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity);
				SCI0SendN(HMITxCmdBuff.Compts.EndPage.EndElectricity, 8);
				HMITxCmdBuff.Compts.EndPage.EndMoney[6] = (UInt8)((CostManagementBuff.Compts.CostTotalMoney+CostManagementBuff.Compts.CostServicePrice )>> 24);
				HMITxCmdBuff.Compts.EndPage.EndMoney[7] = (UInt8)((CostManagementBuff.Compts.CostTotalMoney + CostManagementBuff.Compts.CostServicePrice) >> 16);
				HMITxCmdBuff.Compts.EndPage.EndMoney[8] = (UInt8)((CostManagementBuff.Compts.CostTotalMoney + CostManagementBuff.Compts.CostServicePrice) >> 8);
				HMITxCmdBuff.Compts.EndPage.EndMoney[9] = (UInt8)((CostManagementBuff.Compts.CostTotalMoney + CostManagementBuff.Compts.CostServicePrice));
				SCI0SendN(HMITxCmdBuff.Compts.EndPage.EndMoney, 10);
				asm MOVB #$F1, RPAGE;
				UserMoneyConvert.UInt32_Data = SerialNumTmp;
				asm MOVB #$F0, RPAGE;
				HMITxCmdBuff.Compts.EndPage.OrderNum[6] = UserMoneyConvert.UInt8_Data[0];
				HMITxCmdBuff.Compts.EndPage.OrderNum[7] = UserMoneyConvert.UInt8_Data[1];
				HMITxCmdBuff.Compts.EndPage.OrderNum[8] = UserMoneyConvert.UInt8_Data[2];
				HMITxCmdBuff.Compts.EndPage.OrderNum[9] = UserMoneyConvert.UInt8_Data[3];
				SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EndPage.OrderNum, 10);
				SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoEndClr, 16);
				asm MOVB #$F1, RPAGE;
				CostCalTmp = CostManagementBuff.Compts.CostTotalMoney + CostManagementBuff.Compts.CostServicePrice;
				if (CardMutex == 0)
				{
					CardMutex = 1;
					CardOperationBuff.Compts.Permission = 1;
					CardOperationBuff.Compts.PayByCardStart = 1;
				}
				if (CardOperationBuff.Compts.FeeOp == 1)
				{
					SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoEnd, 16);
					BMSComCtlBuff.Compts.StopCharging = 1;
				}
				else
				{
					SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoEndClr, 16);
				}
			}
			else
			{	
				asm MOVB #$F1, RPAGE;
				CostCalTmp = CostManagementBuff.Compts.CostTotalMoney + CostManagementBuff.Compts.CostServicePrice;
				if (CardOperationBuff.Compts.FeeOp == 1)
				{
					SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoEnd, 16);
					BMSComCtlBuff.Compts.StopCharging = 1;
				}
				else
				{
					SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoEndClr, 16);
				}
				asm MOVB #$F0, RPAGE;
				HMIOperationBuff.Compts.CardConfirm = 0;
				HMIOperationBuff.Compts.BackToChargingPage = 0;
			}
		}
		break;
	case 4:
		HMIOperationBuff.Compts.CurrentPageNum = 8;
		HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
		HMITxCmdBuff.Compts.WritePageReg[6] = 8;
		SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
		HMITxCmdBuff.Compts.EndPage.EndElectricity[6] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity >> 8);
		HMITxCmdBuff.Compts.EndPage.EndElectricity[7] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity);
		SCI0SendN(HMITxCmdBuff.Compts.EndPage.EndElectricity, 8);
		HMITxCmdBuff.Compts.EndPage.EndMoney[6] = (UInt8)((CostManagementBuff.Compts.CostTotalMoney + CostManagementBuff.Compts.CostServicePrice) >> 24);
		HMITxCmdBuff.Compts.EndPage.EndMoney[7] = (UInt8)((CostManagementBuff.Compts.CostTotalMoney + CostManagementBuff.Compts.CostServicePrice) >> 16);
		HMITxCmdBuff.Compts.EndPage.EndMoney[8] = (UInt8)((CostManagementBuff.Compts.CostTotalMoney + CostManagementBuff.Compts.CostServicePrice) >> 8);
		HMITxCmdBuff.Compts.EndPage.EndMoney[9] = (UInt8)((CostManagementBuff.Compts.CostTotalMoney + CostManagementBuff.Compts.CostServicePrice));
		SCI0SendN(HMITxCmdBuff.Compts.EndPage.EndMoney, 10);
		asm MOVB #$F1, RPAGE;
		UserMoneyConvert.UInt32_Data = SerialNumTmp;
		asm MOVB #$F0, RPAGE;
		HMITxCmdBuff.Compts.EndPage.OrderNum[6] = UserMoneyConvert.UInt8_Data[0];
		HMITxCmdBuff.Compts.EndPage.OrderNum[7] = UserMoneyConvert.UInt8_Data[1];
		HMITxCmdBuff.Compts.EndPage.OrderNum[8] = UserMoneyConvert.UInt8_Data[2];
		HMITxCmdBuff.Compts.EndPage.OrderNum[9] = UserMoneyConvert.UInt8_Data[3];
		SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EndPage.OrderNum, 10);
		asm MOVB #$F1, RPAGE;
		if (CardOperationBuff.Compts.FeeOp==1)
		{
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoEnd, 16);
			if (BMSComCtlBuff.Compts.EndFinished == 1)
			{
				MyMemset(InfyPowerOperationBuff.data, 0, 2);
				MyMemset(InKePowerOperationBuff.data, 0, 2);
				ClearChargingControlData();		
			}
		}
		else
		{
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoEndClr, 16);
		}
		break;
	case 5:
		asm MOVB #$F0, RPAGE;
		if (BackFirst1 == 1)
		{
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoEndClr, 16);
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.StartupPage.CardStartBack, 6);
			BackFirst1 = 0;
			ChargingEnd = 1;
		}
		if (ErrorSendOnce == 0)
		{
			ErrorSendOnce = 1;
			asm MOVB  #$F1, RPAGE;
			SCI4OperatBuff.Compts.NetHasRecFaultFlag = 0;
			asm MOVB #$F0, RPAGE;
		}
		if (ErrorFirst == 0)
		{
			ErrorFirst = 1;
			for (n = 0; n < 7; n++)
			{
				if (CharFaultBuff.data[0] & FaultBitCompare[n])
				{
					HMIOperationBuff.Compts.TraverseFault = n;
					break;
				}
			}
		}
		asm MOVB #$F1, RPAGE;
		if (CardOperationBuff.Compts.PerOp == 1)
		{
			if (FaultPay == 0)
			{
				FaultPay = 1;
				CostCalTmp = (CostManagementBuff.Compts.CostTotalMoney + CostManagementBuff.Compts.CostServicePrice);
				CardOperationBuff.Compts.Permission = 1;
				CardOperationBuff.Compts.PayByCardStart = 1;
			}
			if (CardOperationBuff.Compts.FeeOp == 1)
			{
				MyMemset(InfyPowerOperationBuff.data, 0, 2);
				MyMemset(InKePowerOperationBuff.data, 0, 2);
				ClearChargingControlData();
				asm CLR CharFaultBuff.data[0];
				asm CLR ErrorFirst;
				asm MOVB #$01, FaultEcho;
			}
		}
		else
		{
			if (CharFaultBuff.data[0] == 0x01)
			{
				MyMemset(InfyPowerOperationBuff.data, 0, 2);
				MyMemset(InKePowerOperationBuff.data, 0, 2);
				ClearChargingControlData();
				asm CLR CharFaultBuff.data[0];
				asm CLR ErrorFirst;
			}
		}
		if (FaultEcho == 1)
		{
			SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.EchoEnd, 16);
		}
		asm MOVB #$F0, RPAGE;
		HMIOperationBuff.Compts.CurrentPageNum = 1;
		HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
		HMITxCmdBuff.Compts.WritePageReg[6] = 1;
		SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
		HMITxCmdBuff.Compts.FaultPage.FaultType[6] = 0x00;
		HMITxCmdBuff.Compts.FaultPage.FaultType[7] = ErrorTypeMap[HMIOperationBuff.Compts.TraverseFault];
		SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.FaultPage.FaultType, 8);
		break;
	}
	if (Calender < 10)
	{
		WriteHMICalendar();
		SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.HMIWriteRTC, 13);
		Calender++;
	}
	SCI0SendN((UInt8 *far)HMITxCmdBuff.Compts.WriteNetConFlag, 8);
	OSCRITICALENTRY();
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void SCI0HMI(void)
{
	static UInt16 n=0;
	MemoryList *PtrTmp;
	asm INC OSNesting;
	if (SCI0SR1 & 0x20)
	{
		if ((n >= 124))
			n = 0;
		((UInt8*)IOBuffer[0].Rear)[n + 4] = SCI0DRL;
		++n;
		if ((((UInt8*)IOBuffer[0].Rear)[4] == 0x5A))
		{
			if ((((UInt8*)IOBuffer[0].Rear)[5] == 0xA5))
			{
				if ((n >= ((UInt8*)IOBuffer[0].Rear)[6] + 3))
				{
					PtrTmp = IOBuffer[0].Rear;
					IOBufferMonitorBuffer.Compts.EnQueueReturnCode[0] = EnQueue(0);
					if (IOBufferMonitorBuffer.Compts.EnQueueReturnCode[0] == 1)
					{
						PtrTmp->DataSize = n;
						PtrTmp->RecvFinishedFlag = 1;
						IOBuffer[0].BlockNum += 1;
					}
					else
					{
						IOBufferMonitorBuffer.Compts.FullFlag[0] = 1;
					}
					n = 0;
				}
				else if ((((UInt8*)IOBuffer[0].Rear)[n + 4+3] == 0x5A) && (((UInt8*)IOBuffer[0].Rear)[n + 4+4] >= 0xa5))
				{
					n = 0;
				}
			}
			else if(n==2)
			{
				n = 0;
			}
		}
		else if (n == 1)
		{
			n = 0;
		}
	}
	asm DEC OSNesting;
}
#pragma  CODE_SEG DEFAULT