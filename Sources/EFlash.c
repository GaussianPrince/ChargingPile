#include "Include.h"
#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
EFlashMain EFlashMainBuff;
EFlashDataBlock EFlashDataBlockBuff;
EFlashOperat EFlashOperatBuff;
UInt32 SerialNumTmp;
UInt8 CardIDToAsscii[17];
UInt8 CardIDIndex;
UInt32 CardIDTemp;
TimeRecFormatArr TimeRecFormatArrBuff;
#pragma DATA_SEG DEFAULT
void EFlashInit(void)
{
	asm
	{
		BRCLR FSTAT,#$80,*
		MOVB #$0F,FCLKDIV
		MOVB #$00,FCNFG
		BRCLR FCLKDIV,#$80,*
	}
}
void EFlashEraseBySector(UInt16 AddrStart16, UInt16 EndAddr16)
{
	UInt16	n;
	while (FSTAT_CCIF == 0);
	if (FSTAT & 0x30)
	{
		FSTAT |= 0x30;
	}
	FCCOBIX_CCOBIX = 0x00;
	FCCOBHI = 0x12;
	FCCOBLO = 0x10;
	FCCOBIX_CCOBIX = 0x01;
	for (n = AddrStart16; n < EndAddr16; n += 0x100)
	{
		FCCOB = AddrStart16 + n;
	}
	FSTAT_CCIF = 1;
	while (FSTAT_CCIF == 0);
}
void EFlashWriteWord(UInt8 GPage, UInt16 AddrStart16, UInt16 *far InData, UInt16	Len)
{
	UInt16 n;
	while (FSTAT_CCIF == 0);
	if (FSTAT & 0x30)
	{
		FSTAT |= 0x30;
	}
	for (n = 0; n < (Len / 4); n++)
	{
		FCCOBIX_CCOBIX = 0x00;
		FCCOBHI = 0x11;
		FCCOBLO = GPage;
		FCCOBIX_CCOBIX = 0x01;
		FCCOB = AddrStart16 + n * 8;
		FCCOBIX_CCOBIX = 0x02;
		FCCOB = InData[n * 4];
		FCCOBIX_CCOBIX = 0x03;
		FCCOB = InData[n * 4 + 1];
		FCCOBIX_CCOBIX = 0x04;
		FCCOB = InData[n * 4 + 2];
		FCCOBIX_CCOBIX = 0x05;
		FCCOB = InData[n * 4 + 3];
		FSTAT_CCIF = 1;
		while (FSTAT_CCIF == 0);
	}
}
void EFlashReadWord(UInt8 GPage, UInt16 Destin, UInt16 * far OutData, UInt16	Len)
{
	UInt16 n;
	UInt8 LastEPage;
	for (n = 0; n < Len; n++)
	{
		LastEPage = EPAGE;
		EPAGE = 0 + (Destin >> 10);
		OutData[n] = *(volatile UInt16 * far)(((UInt32)GPage << 16) + Destin);
		Destin = Destin + 2;
		EPAGE = LastEPage;
	}
}
void CardIDAssciiFormat(void)
{
	CardIDTemp = CardOperationBuff.Compts.CardID;
	CardIDIndex = 0;
	while (CardIDTemp != 0)
	{
		CardIDToAsscii[CardIDIndex++] = CardIDTemp % 10 + 0x30;
		CardIDTemp /= 10;
	}
}
void EFlashStateControl(void)
{
	UInt8 n;
	UInt8 i;
	if (EFlashOperatBuff.Compts.TieredPriceSaveFlag == 1)
	{
		EFlashReadWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 73);
		for (n = 0; n < 24; n++)
		{
			EFlashMainBuff.Compts.TieredPrice[n] = DiffPriceBuff.Compts.CloudDiffPrice[n];
		}
		EFlashEraseBySector(0x00, 0x10);
		EFlashWriteWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 76);
		EFlashOperatBuff.Compts.TieredPriceSaveFlag = 0;
	}
	if (EFlashOperatBuff.Compts.ServicePriceSaveFlag == 1)
	{
		EFlashReadWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 73);
		EFlashMainBuff.Compts.ServicePrice = DiffPriceBuff.Compts.CloudServicePrice;
		EFlashEraseBySector(0x00, 0x10);
		EFlashWriteWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 76);
		EFlashOperatBuff.Compts.ServicePriceSaveFlag = 0;
	}
	if (EFlashOperatBuff.Compts.NetConfigSaveFlag == 1)
	{
		EFlashReadWord(0x10, 0x00, (UInt16 *far)EFlashOperatBuff.data, 73);
		for (n = 0; n < 10; n++)
		{
			EFlashMainBuff.Compts.PileNum[n] = HMITxCmdBuff.Compts.ConfigPage.PileNumRec[n + 6];
		}
		EFlashMainBuff.Compts.ConnMethod = HMIOperationBuff.Compts.NetConfigType;
		for (n = 6; n < (HMITxCmdBuff.Compts.ConfigPage.SSIDRec[2] + 3); n++)
		{
			EFlashMainBuff.Compts.SSIDWIFI[n - 6] = HMITxCmdBuff.Compts.ConfigPage.SSIDRec[n];
		}
		for (n = 6; n < (HMITxCmdBuff.Compts.ConfigPage.PwdRec[2] + 3); n++)
		{
			EFlashMainBuff.Compts.WIFIPwd[n - 6] = HMITxCmdBuff.Compts.ConfigPage.PwdRec[n];
		}
		EFlashMainBuff.Compts.LocalPort = ((UInt16)HMITxCmdBuff.Compts.ConfigPage.LocalPortRec[6] << 8) + HMITxCmdBuff.Compts.ConfigPage.LocalPortRec[7];
		EFlashMainBuff.Compts.RemotePort = ((UInt16)HMITxCmdBuff.Compts.ConfigPage.RemotePortRec[6] << 8) + HMITxCmdBuff.Compts.ConfigPage.RemotePortRec[7];
		EFlashMainBuff.Compts.RemoteIP[0] = HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec1[7];
		EFlashMainBuff.Compts.RemoteIP[1] = HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec2[7];
		EFlashMainBuff.Compts.RemoteIP[2] = HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec3[7];
		EFlashMainBuff.Compts.RemoteIP[3] = HMITxCmdBuff.Compts.ConfigPage.RemoteIPRec4[7];
		EFlashMainBuff.Compts.LocalIP[0] = HMITxCmdBuff.Compts.ConfigPage.LocalIPRec1[7];
		EFlashMainBuff.Compts.LocalIP[1] = HMITxCmdBuff.Compts.ConfigPage.LocalIPRec2[7];
		EFlashMainBuff.Compts.LocalIP[2] = HMITxCmdBuff.Compts.ConfigPage.LocalIPRec3[7];
		EFlashMainBuff.Compts.LocalIP[3] = HMITxCmdBuff.Compts.ConfigPage.LocalIPRec4[7];
		EFlashEraseBySector(0x00, 0x10);
		EFlashWriteWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 76);
		EFlashOperatBuff.Compts.NetConfigSaveFlag = 0;
	}
	if (EFlashOperatBuff.Compts.SerialNumSaveFlag == 1)
	{
		EFlashMainBuff.Compts.SerialNum = SerialNumTmp;
		EFlashEraseBySector(0x00, 0x10);
		EFlashWriteWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 76);
		EFlashOperatBuff.Compts.SerialNumSaveFlag = 0;
	}
	if (EFlashOperatBuff.Compts.CardRecSaveFlag == 1)
	{
		EFlashReadWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 73);
		n = EFlashMainBuff.Compts.EndSectorNum;
		EFlashReadWord(0x10, n, (UInt16 *far)EFlashDataBlockBuff.data, 103);
		EFlashMainBuff.Compts.SerialNum = SerialNumTmp;
		if (EFlashDataBlockBuff.Compts.UsedBlock >3)
		{
			EFlashDataBlockBuff.Compts.UsedBlock = 0;
			EFlashMainBuff.Compts.EndSectorNum += 1;
			EFlashWriteWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 76);
		}
		EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.SerialNum = SerialNumTmp ;
		CardIDAssciiFormat();
		i = 0;
		for (n = CardIDIndex-1; n>0; n--)
		{
			EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.CardIDAsscii[i++] = CardIDToAsscii[n];
		}
		EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.CardIDAsscii[i++] = CardIDToAsscii[0];
		for (n = i; n < 17; n++)
		{
			EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.CardIDAsscii[n] = 0;
		}
		for (n = 32; n < 32 + 14; n++)
		{
			EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].data[n] = TimeRecFormatArrBuff.data[n - 32];
		}
		EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.CostAllElectricity = CostManagementBuff.Compts.CostTotalElectricity;
		EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.CostChargingElectricity = CostManagementBuff.Compts.CostTotalElectricity;
		EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.ChargingDuration = CardChargingDuration;
		if (HMIOperationBuff.Compts.AutoCharging == 1)
		{
			EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.ChargingMode = 4;
		}
		else if (HMIOperationBuff.Compts.TimingCharging == 1)
		{
			EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.ChargingMode = 2;
		}
		EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.CostAllMoney = CostManagementBuff.Compts.CostTotalMoney+CostManagementBuff.Compts.CostServicePrice;
		EFlashDataBlockBuff.Compts.CardHistoryData[EFlashDataBlockBuff.Compts.UsedBlock].Compts.GunNum = 1;
		EFlashDataBlockBuff.Compts.UsedBlock += 1;
		n = EFlashMainBuff.Compts.EndSectorNum;
		EFlashWriteWord(0x10, n, (UInt16 *far)EFlashDataBlockBuff.data, 104);
		EFlashOperatBuff.Compts.CardRecSaveFlag = 0;
	}
	OSCRITICALENTRY();
}