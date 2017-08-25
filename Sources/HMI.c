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
	/*AdvertisementText*/0x5A,0xA5,0x5C,0x82,0x01,0x20,
	0xBB,0xB6,0xD3,0xAD,0xCA,0xB9,0xD3,0xC3,0xBB,0xAA,
	0xCC,0xA9,0xB5,0xE7,0xC6,0xF8,0xC6,0xEC,0xCF,0xC2,
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
	0x36,0x37,
	/*CardID*/			0x5A,0xA5,0x00,0x82,0x01,0xC5,
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
	/*EchoPower*/		0x5A,0xA5,0x07,0x82,0x02,0xd9,
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
	/*EchoSOC*/		    0x5A,0xA5,0x05,0x82,0x02,0x3C,
	0x00,0x00,
	/*OrderNum*/	    0x5A,0xA5,0x00,0x82,0x02,0x3D,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/*EndElectricity*/  0x5A,0xA5,0x05,0x82,0x02,0x5D,
	0x00,0x00,
	/*EndMoney*/	     0x5A,0xA5,0x07,0x82,0x02,0x5E,
	0x00,0x00,0x00,0x00,
	/*PileNumRec*/	     0x5A,0xA5,0x0D,0x82,0x02,0x6C,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
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
	/*WritePageReg*/	 0x5A,0xA5,0x04,0x80,0x03,0x00,
	 0x00,
	/*WriteNetConFlag*/	 0x5A,0xA5,0x05,0x82,0x02,0xD8,
	 0x00,0x00
};
UInt8 PwdErrorCounter;
UInt8  ConfigWait;
UInt32 AdminPwd=20171996;
#pragma DATA_SEG DEFAULT
void SCI0Init(void)
{
	asm
	{
		MOVB #$00,SCI0BDH
		MOVB #$20,SCI0BDL
		MOVB #$12,SCI0CR1
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
	static UInt32 OutputPower;
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
					if (HMIOperationBuff.Compts.ConfigClicks == 5)
					{
						HMIOperationBuff.Compts.CurrentPageNum = 16;
						HMIOperationBuff.Compts.ConfigClicks = 0;
					}
				}
				else
				{
					HMIOperationBuff.Compts.ConfigClicks = 0;
				}
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x01) && (((UInt8*)IOBuffer[0].Front)[4 + 5] ==0xC4))
			{
				if (HMIOperationBuff.Compts.TraverseFault == 0)
				{
					HMIOperationBuff.Compts.TraverseFault = ERROREDGE;
				}
				else
				{
					HMIOperationBuff.Compts.TraverseFault--;
				}
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x01) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xC3))
			{
				if (HMIOperationBuff.Compts.TraverseFault == ERROREDGE)
				{
					HMIOperationBuff.Compts.TraverseFault = 0;
				}
				else
				{
					HMIOperationBuff.Compts.TraverseFault++;
				}
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x0A))
			{
				HMIOperationBuff.Compts.GunConStaReflesh = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x2B))
			{
				HMIOperationBuff.Compts.AutoCharging = 1;
				BMSComCtlBuff.Compts.StartCharging = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x2C))
			{
				HMIOperationBuff.Compts.TimingCharging = 1;
				BMSComCtlBuff.Compts.StartCharging = 1;
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
				HMIOperationBuff.Compts.ChargingTime = (UInt16)(((UInt8*)IOBuffer[0].Front)[4 + 7] << 8) + ((UInt8*)IOBuffer[0].Front)[4 + 8];
				BMSComCtlBuff.Compts.StartCharging = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x62))
			{
				HMIOperationBuff.Compts.BackToCardOperationPage = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xD6))
			{
				if ((((UInt8*)IOBuffer[0].Front)[4 + 7] == 0x01)
					&& (((UInt8*)IOBuffer[0].Front)[4 + 8] == 0x33)
					&& (((UInt8*)IOBuffer[0].Front)[4 + 7] == 0xCC)
					&& (((UInt8*)IOBuffer[0].Front)[4 + 7] == 0xDC))
				{
					HMIOperationBuff.Compts.AdminEntry = 1;
					HMIOperationBuff.Compts.CurrentPageNum = 14;
				}
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x64))
			{
				HMIOperationBuff.Compts.NetConfigSave = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x65))
			{
				HMIOperationBuff.Compts.NetConfigRead = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x66))
			{
				HMIOperationBuff.Compts.NetworkMethod[0] = 1;
				HMIOperationBuff.Compts.NetworkMethod[1] = 0;
				HMIOperationBuff.Compts.NetworkMethod[2] = 0;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x67))
			{
				HMIOperationBuff.Compts.NetworkMethod[0] = 0;
				HMIOperationBuff.Compts.NetworkMethod[1] = 1;
				HMIOperationBuff.Compts.NetworkMethod[2] = 0;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x68))
			{
				HMIOperationBuff.Compts.NetworkMethod[0] = 0;
				HMIOperationBuff.Compts.NetworkMethod[1] = 0;
				HMIOperationBuff.Compts.NetworkMethod[2] = 1;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x6C))
			{
				for (n = 7; n < IOBuffer[0].Front->DataSize; n++)
				{
					HMITxCmdBuff.Compts.ConfigPage.PileNumRec[n - 1] = ((UInt8*)IOBuffer[0].Front)[4 + n];
				}
				HMITxCmdBuff.Compts.ConfigPage.PileNumRec[2] = 13;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x8C))
			{
				for (n = 7; n < IOBuffer[0].Front->DataSize; n++)
				{
					HMITxCmdBuff.Compts.ConfigPage.SSIDRec[n-1]= ((UInt8*)IOBuffer[0].Front)[4 + n];
				}
				HMITxCmdBuff.Compts.ConfigPage.SSIDRec[2] = IOBuffer[0].Front->DataSize - 7 + 3;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0x8C))
			{
				for (n = 7; n < IOBuffer[0].Front->DataSize; n++)
				{
					HMITxCmdBuff.Compts.ConfigPage.PwdRec[n-1]= ((UInt8*)IOBuffer[0].Front)[4 + n];
				}
				HMITxCmdBuff.Compts.ConfigPage.PwdRec[2] = IOBuffer[0].Front->DataSize - 7 + 3;
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xCD))
			{
				HMITxCmdBuff.Compts.ConfigPage.RemotePortRec[6] = ((UInt8*)IOBuffer[0].Front)[7];
				HMITxCmdBuff.Compts.ConfigPage.RemotePortRec[7] = ((UInt8*)IOBuffer[0].Front)[8];
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xCE))
			{
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec1[6] = ((UInt8*)IOBuffer[0].Front)[7];
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec1[7] = ((UInt8*)IOBuffer[0].Front)[8];
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xCF))
			{
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec2[6] = ((UInt8*)IOBuffer[0].Front)[7];
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec2[7] = ((UInt8*)IOBuffer[0].Front)[8];
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xD0))
			{
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec3[6] = ((UInt8*)IOBuffer[0].Front)[7];
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec3[7] = ((UInt8*)IOBuffer[0].Front)[8];
			}
			else if ((((UInt8*)IOBuffer[0].Front)[4 + 4] == 0x02) && (((UInt8*)IOBuffer[0].Front)[4 + 5] == 0xD1))
			{
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec4[6] = ((UInt8*)IOBuffer[0].Front)[7];
				HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec4[7] = ((UInt8*)IOBuffer[0].Front)[8];
			}
		}
		break;
	}
}
void HMIDisplayControl(void)
{
	UInt16 OutputPower = 0;
	HMIAnalysis();
	switch (BMSComCtlBuff.Compts.SystemState)
	{
	case 0:
		if (HMIOperationBuff.Compts.ConfigClicks != 0)
		{
			ConfigWait++;
			if (ConfigWait >= 250)
			{
				HMIOperationBuff.Compts.ConfigClicks = 0;
				ConfigWait = 0;
			}
		}
		else
		{
			switch (HMIOperationBuff.Compts.CurrentPageNum)
			{
			case 0:
				HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
				HMITxCmdBuff.Compts.WritePageReg[6] = 0x00;
				SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
				SCI0SendN(HMITxCmdBuff.Compts.HomePage.AdvertisementText, (HMITxCmdBuff.Compts.HomePage.AdvertisementText[2] + 3));
				SCI0SendN(HMITxCmdBuff.Compts.HomePage.AppDownloadAdress, (HMITxCmdBuff.Compts.HomePage.AppDownloadAdress[2] + 3));
				SCI0SendN(HMITxCmdBuff.Compts.HomePage.PileNumQRCode, (HMITxCmdBuff.Compts.HomePage.PileNumQRCode[2] + 3));
				SCI0SendN(HMITxCmdBuff.Compts.HomePage.PileNumText, (HMITxCmdBuff.Compts.HomePage.PileNumText[2] + 3));
				break;
			case 16:
				HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
				HMITxCmdBuff.Compts.WritePageReg[6] = 16;
				SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);
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
					HMIOperationBuff.Compts.CurrentPageNum = 0;
				}
				break;
			}
		}
		break;
	case 1:
	case 2:
		if (HMIOperationBuff.Compts.AutoCharging)
		{
			SCI0SendN(HMITxCmdBuff.Compts.CardOperationPage.CardStartKey, 6);
		}
		else if (HMIOperationBuff.Compts.TimingCharging)
		{
			SCI0SendN(HMITxCmdBuff.Compts.CardOperationPage.TimingStartKey, 6);
		}
		break;
	case 3:
		SCI0SendN(HMITxCmdBuff.Compts.StartupPage.CardStartBack, 6);
		if (HMIOperationBuff.Compts.CardConfirm == 0)
		{
			HMITxCmdBuff.Compts.ChargingPage.EchoVol[6] = (UInt8)(CAN0OperationBuff.Compts.TotalVol >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoVol[7] = (UInt8)(CAN0OperationBuff.Compts.TotalVol);
			SCI0SendN(HMITxCmdBuff.Compts.ChargingPage.EchoVol, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoCur[6] = (UInt8)(CAN0OperationBuff.Compts.TotalCur >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoCur[7] = (UInt8)(CAN0OperationBuff.Compts.TotalCur);
			SCI0SendN(HMITxCmdBuff.Compts.ChargingPage.EchoCur, 8);
			OutputPower = CAN0OperationBuff.Compts.TotalCur*CAN0OperationBuff.Compts.TotalVol / 1000;
			HMITxCmdBuff.Compts.ChargingPage.EchoPower[6] = (UInt8)(OutputPower >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoPower[7] = (UInt8)(OutputPower);
			SCI0SendN(HMITxCmdBuff.Compts.ChargingPage.EchoPower, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoBatLow[6] = 0x00;
			HMITxCmdBuff.Compts.ChargingPage.EchoBatLow[7] = BSMData.Compts.LowestTemp;
			SCI0SendN(HMITxCmdBuff.Compts.ChargingPage.EchoBatLow, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoBatHigh[6] = 0x00;
			HMITxCmdBuff.Compts.ChargingPage.EchoBatHigh[7] = BSMData.Compts.HighestTemp;
			SCI0SendN(HMITxCmdBuff.Compts.ChargingPage.EchoBatHigh, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedFee[6] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 24);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedFee[7] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 16);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedFee[8] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedFee[9] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney);
			SCI0SendN(HMITxCmdBuff.Compts.ChargingPage.EchoChargedFee, 10);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedAmount[6] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedAmount[7] = (UInt8)(CostManagementBuff.Compts.CostTotalElectricity);
			SCI0SendN(HMITxCmdBuff.Compts.ChargingPage.EchoChargedAmount, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoSerPrice[6] = (UInt8)(CostManagementBuff.Compts.CostServicePrice >> 24);
			HMITxCmdBuff.Compts.ChargingPage.EchoSerPrice[7] = (UInt8)(CostManagementBuff.Compts.CostServicePrice >> 16);
			HMITxCmdBuff.Compts.ChargingPage.EchoSerPrice[8] = (UInt8)(CostManagementBuff.Compts.CostServicePrice >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoSerPrice[9] = (UInt8)(CostManagementBuff.Compts.CostServicePrice);
			SCI0SendN(HMITxCmdBuff.Compts.ChargingPage.EchoSerPrice, 10);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedTime[6] = (UInt8)(CCSData.Compts.TotalChargTime >> 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoChargedTime[7] = (UInt8)(CCSData.Compts.TotalChargTime);
			SCI0SendN(HMITxCmdBuff.Compts.ChargingPage.EchoChargedTime, 8);
			HMITxCmdBuff.Compts.ChargingPage.EchoSOC[6] = 0x00;
			HMITxCmdBuff.Compts.ChargingPage.EchoSOC[7] = BCSData.Compts.SOCNow;
			SCI0SendN(HMITxCmdBuff.Compts.ChargingPage.EchoSOC, 8);
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
				HMITxCmdBuff.Compts.EndPage.EndMoney[6] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 24);
				HMITxCmdBuff.Compts.EndPage.EndMoney[7] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 16);
				HMITxCmdBuff.Compts.EndPage.EndMoney[8] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney >> 8);
				HMITxCmdBuff.Compts.EndPage.EndMoney[9] = (UInt8)(CostManagementBuff.Compts.CostTotalMoney);
				SCI0SendN(HMITxCmdBuff.Compts.EndPage.EndMoney, 10);
			}
			else
			{
				HMIOperationBuff.Compts.CurrentPageNum = 4;
				HMITxCmdBuff.Compts.WritePageReg[5] = 0X00;
				HMITxCmdBuff.Compts.WritePageReg[6] = 0x04;
				HMIOperationBuff.Compts.CardConfirm = 0;
				SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);		
			}
		}
		break;
	case 4:
		HMIOperationBuff.Compts.CurrentPageNum = 8;
		HMITxCmdBuff.Compts.WritePageReg[5] = 0x00;
		HMITxCmdBuff.Compts.WritePageReg[6] = 8;
		SCI0SendN(HMITxCmdBuff.Compts.WritePageReg, 7);

	}
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void SCI0HMI(void)
{
	static UInt16 n=0;
	MemoryList *PtrTmp;
	asm INC OSNesting;
	if (SCI1SR1 & 0x20)
	{
		if ((n < 124) && (IOBufferMonitorBuffer.Compts.FullFlag[0] == 0) && (IOBuffer[0].Rear->RecvFinishedFlag == 0))
		{
			((UInt8*)IOBuffer[0].Rear)[n + 4] = SCI0DRL;
			++n;
			if (n < 3)
				return;
			if ((((UInt8*)IOBuffer[0].Rear)[4] == 0x5A) && (((UInt8*)IOBuffer[0].Rear)[5] == 0xA5))
			{
				if ((((UInt8*)IOBuffer[0].Rear)[6] < (n + 3)))
					return;
				else
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
				}
			}
			n = 0;
		}
		else
		{
			n = 0;
		}
	}
	asm DEC OSNesting;
}
#pragma  CODE_SEG DEFAULT