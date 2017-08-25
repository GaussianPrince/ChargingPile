#include"Include.h"
/*****************************************************
	Messages
*******************************************************/
CanMsgBuf CHM;
CanMsgBuf BHM;
CanMsgBuf CRM;

CanMsgBuf CTS;
CanMsgBuf CML;
CanMsgBuf BRO;
CanMsgBuf CRO;

CanMsgBuf BCL;
CanMsgBuf CCS;
CanMsgBuf BSM;
CanMsgBuf BMV;
CanMsgBuf BMT;
CanMsgBuf BSP;
CanMsgBuf BST;
CanMsgBuf CST;

CanMsgBuf BSD;
CanMsgBuf CSD;

CanMsgBuf BEM;
CanMsgBuf CEM;

CanMsgBuf TPCMRTS;
CanMsgBuf TPCMCTS;
CanMsgBuf TPCMDT;

BHMStruct BHMData;
CHMStruct CHMData;
CRMStruct CRMData;
BRMStruct BRMData;

BCPStruct BCPData;
CTSStruct CTSData;
CMLStruct CMLData;
BROStruct BROData;
CROStruct CROData;

BCLStruct BCLData;
BCSStruct BCSData;
CCSStruct CCSData;
BSMStruct BSMData;
BSTStruct BSTData;
CSTStruct CSTData;

BSDStruct BSDData;
CSDStruct CSDData;

BEMStruct BEMData;
CEMStruct CEMData;

TPCMCTSStruct TPCMCTSData;
TPCMRTSStruct TPCMRTSData;
TPCMDTStruct  TPCMDTData;
/*****************************************************
	Speed:16000000/8/8=250k
*******************************************************/
void CAN2Init(void)
{
	asm
	{
		BSET CAN2CTL0,#$01
		BRCLR CAN2CTL1,#$01,*
		MOVB #$80,CAN2CTL1
		MOVB #$10,CAN2IDAC
		MOVB #$FF,CAN2IDMR0
		MOVB #$FF,CAN2IDMR1
		MOVB #$FF,CAN2IDMR2
		MOVB #$FF,CAN2IDMR3
		MOVB #$FF,CAN2IDMR4
		MOVB #$FF,CAN2IDMR5
		MOVB #$FF,CAN2IDMR6
		MOVB #$FF,CAN2IDMR7
		MOVB #$47,CAN2BTR0
		MOVB #$23,CAN2BTR1
		BCLR CAN2CTL0,#$01
		BRSET CAN2CTL1,#$01,*
		BSET  CAN2RIER,#$01
	}
}
/*****************************************************
	Transmit can message
*******************************************************/
void MSCAN2Transmit(CanMsgBuf *InCan)
{
	UInt8 n;
	if ((CAN2TFLG & 0X07) != 0X00)
	{
		CAN2TBSEL = CAN2TFLG;
		CAN2TXIDR0 = InCan->CANID.ID.ID1;
		CAN2TXIDR1 = InCan->CANID.ID.ID2;
		CAN2TXIDR2 = InCan->CANID.ID.ID3;
		CAN2TXIDR3 = InCan->CANID.ID.ID4;
		for (n = 0; n < InCan->Length; n++)
		{
			*((&CAN2TXDSR0) + n) = InCan->Data[n];
		}
		CAN2TXDLR = InCan->Length;
		CAN2TXTBPR = InCan->Priority;
		CAN2TFLG = CAN2TBSEL;
		InCan->NewFlag = 0;
	}
}
/*****************************************************
	Initialize CAN ID
*******************************************************/
void BMSCANIDInit(void)
{
	TPCMCTS.CANID.TotalID = 0x1CECF456;
	TPCMCTS.Length = 8;
	TPCMCTS.Priority = 7;
	TPCMCTS.NewFlag = 0;
	CANIDConvert(&TPCMCTS);

	TPCMRTS.CANID.TotalID = 0x1CEC56F4;
	TPCMRTS.Length = 8;
	TPCMRTS.Priority = 7;
	TPCMRTS.NewFlag = 0;
	CANIDConvert(&TPCMRTS);

	TPCMDT.CANID.TotalID = 0x1CEB56F4;
	TPCMDT.Length = 8;
	TPCMDT.Priority = 7;
	TPCMDT.NewFlag = 0;
	CANIDConvert(&TPCMDT);

	CHM.CANID.TotalID = 0x1826F456;
	CHM.Length = 3;
	CHM.Priority = 6;
	CHM.NewFlag = 0;
	CANIDConvert(&CHM);

	BHM.CANID.TotalID = 0x182756F4;
	BHM.Length = 2;
	BHM.Priority = 6;
	BHM.NewFlag = 0;
	CANIDConvert(&BHM);

	CRM.CANID.TotalID = 0x1801F456;
	CRM.Length = 8;
	CRM.Priority = 6;
	CRM.NewFlag = 0;
	CANIDConvert(&CRM);

	CTS.CANID.TotalID = 0x1807F456;
	CTS.Length = 7;
	CTS.Priority = 6;
	CTS.NewFlag = 0;
	CANIDConvert(&CTS);

	CML.CANID.TotalID = 0x1808F456;
	CML.Length = 8;
	CML.Priority = 6;
	CML.NewFlag = 0;
	CANIDConvert(&CML);

	BRO.CANID.TotalID = 0x100956F4;
	BRO.Length = 1;
	BRO.Priority = 4;
	BRO.NewFlag = 0;
	CANIDConvert(&BRO);

	CRO.CANID.TotalID = 0x100AF456;
	CRO.Length = 1;
	CRO.Priority = 4;
	CRO.NewFlag = 0;
	CANIDConvert(&CRO);

	BCL.CANID.TotalID = 0x181056F4;
	BCL.Length = 5;
	BCL.Priority = 6;
	BCL.NewFlag = 0;
	CANIDConvert(&BCL);

	CCS.CANID.TotalID = 0x1812F456;
	CCS.Length = 8;
	CCS.Priority = 6;
	CCS.NewFlag = 0;
	CANIDConvert(&CCS);

	BSM.CANID.TotalID = 0x181356F4;
	BSM.Length = 7;
	BSM.Priority = 6;
	BSM.NewFlag = 0;
	CANIDConvert(&BSM);

	BST.CANID.TotalID = 0x101956F4;
	BST.Length = 4;
	BST.Priority = 4;
	BST.NewFlag = 0;
	CANIDConvert(&BST);

	CST.CANID.TotalID = 0x101AF456;
	CST.Length=4;
	CST.Priority = 4;
	CST.NewFlag = 0;
	CANIDConvert(&CST);

	BSD.CANID.TotalID = 0x181C56F4;
	BSD.Length = 7;
	BSD.Priority = 6;
	BSD.NewFlag = 0;
	CANIDConvert(&BSD);

	CSD.CANID.TotalID = 0x181DF456;
	CSD.Length = 8;
	CSD.Priority = 6;
	CSD.NewFlag = 0;
	CANIDConvert(&CSD);

	BEM.CANID.TotalID = 0x081E56F4;
	BEM.Length = 4;
	BEM.Priority = 2;
	BEM.NewFlag = 0;
	CANIDConvert(&BEM);

	CEM.CANID.TotalID = 0x081FF456;
	CEM.Length = 4;
	CEM.Priority = 2;
	CEM.NewFlag = 0;
	CANIDConvert(&CEM);
}
/*****************************************************
	Zero out memory
*******************************************************/
void BMSMessageDataInit(void)
{
	UInt8 n;
	for (n = 0; n < 9; n++)
	{
		TPCMCTSData.data[n] = 0;
	}
	for (n = 0; n < 9; n++)
	{
		TPCMRTSData.data[n] = 0;
	}
	for (n = 0; n < 8; n++)
	{
		TPCMDTData.data[n] = 0;
	}
	for (n = 0; n < 3; n++)
	{
		CHMData.data[n] = 0;
	}
	for (n = 0; n < 1; n++)
	{
		BHMData.data[n] = 0;
	}
	for (n = 0; n < 8; n++)
	{
		CRMData.data[n] = 0;
	}
	for (n = 0; n < 51; n++)
	{
		BRMData.data[n] = 0;
	}
	for (n = 0; n < 14; n++)
	{
		BCPData.data[n] = 0;
	}
	for (n = 0; n < 7; n++)
	{
		CTSData.data[n] = 0;
	}
	for (n = 0; n < 4; n++)
	{
		CMLData.data[n] = 0;
	}
	for (n = 0; n < 1; n++)
	{
		BROData.data[n] = 0;
	}
	for (n = 0; n < 1; n++)
	{
		CROData.data[n] = 0;
	}
	for (n = 0; n < 5; n++)
	{
		BCLData.data[n] = 0;
	}
	for (n = 0; n < 11; n++)
	{
		BCSData.data[n] = 0;
	}
	for (n = 0; n < 7; n++)
	{
		CCSData.data[n] = 0;
	}
	for (n = 0; n < 8; n++)
	{
		BSMData.data[n] = 0;
	}
	for (n = 0; n < 4; n++)
	{
		BSTData.data[n] = 0;
	}
	for (n = 0; n < 4; n++)
	{
		CSTData.data[n] = 0;
	}
	for (n = 0; n < 7; n++)
	{
		BSDData.data[n] = 0;
	}
	for (n = 0; n < 8; n++)
	{
		CSDData.data[n] = 0;
	}
	for (n = 0; n < 4; n++)
	{
		BEMData.data[n] = 0;
	}
	for (n = 0; n < 4; n++)
	{
		CEMData.data[n] = 0;
	}
}

void CHMLoad(void)
{
	CHM.Data[0] = 0X01;
	CHM.Data[1] = 0x01;
	CHM.Data[2] = 0x00;
	CHM.NewFlag = 1;
}
void CRMLoad(void)
{
	CRM.Data[0] = CRMData.Compts.IdentificationResult;
	CRM.NewFlag = 1;
}
void CTSLoad(void)
{
	CTS.NewFlag = 1;
}
void CMLLoad(void)
{
	CMLData.Compts.MaxOutputVol = CAN0OperationBuff.Compts.MaximumVol * 10;
	CMLData.Compts.MinOutputVol = CAN0OperationBuff.Compts.MinimumVol * 10;
	CMLData.Compts.MaxOutputCur = CAN0OperationBuff.Compts.MaximumCur*CAN0OperationBuff.Compts.TotalNum * 10- 4000;
	CMLData.Compts.MinOutputCur = CAN0OperationBuff.Compts.MinimumCur*CAN0OperationBuff.Compts.TotalNum * 10- 4000;



	CML.Data[0] = (UInt8)(CMLData.Compts.MaxOutputVol);
	CML.Data[1] = (UInt8)(CMLData.Compts.MaxOutputVol >> 8);
	CML.Data[2] = (UInt8)(CMLData.Compts.MinOutputVol);
	CML.Data[3] = (UInt8)(CMLData.Compts.MinOutputVol >> 8);
	CML.Data[4] = (UInt8)(CMLData.Compts.MaxOutputCur);
	CML.Data[5] = (UInt8)(CMLData.Compts.MaxOutputCur >> 8);
	CML.Data[6] = (UInt8)(CMLData.Compts.MinOutputCur);
	CML.Data[7] = (UInt8)(CMLData.Compts.MinOutputCur >> 8);
	CML.NewFlag = 1;
}
void CROLoad(void)
{
	CRO.Data[0] = CROData.Compts.IdentificationResult;
	CRO.NewFlag = 1;
}
void CCSLoad(void)
{
	CCSData.Compts.OutputVol = CAN0OperationBuff.Compts.TotalVol*10;
	CCSData.Compts.OutputCur = CAN0OperationBuff.Compts.TotalCur - 4000;
	CCS.Data[0] = (UInt8)(CCSData.Compts.OutputVol);
	CCS.Data[1] = (UInt8)(CCSData.Compts.OutputVol >> 8);
	CCS.Data[2] = (UInt8)(CCSData.Compts.OutputCur);
	CCS.Data[3] = (UInt8)(CCSData.Compts.OutputCur >> 8);
	CCS.Data[4] = (UInt8)(CCSData.Compts.TotalChargTime);
	CCS.Data[5] = (UInt8)(CCSData.Compts.TotalChargTime >> 8);
	CCS.Data[6] = (UInt8)(CCSData.Compts.ChargingPermission|0xfc);
	CCS.Data[7] = 0xff;
	CCS.NewFlag = 1;
}
void CSTLoad(void)
{
	CST.Data[0] = CSTData.data[0];
	CST.Data[1] = (CSTData.data[2] | 0xf0);
	CST.Data[2] = CSTData.data[1];
	CST.Data[3] = (CSTData.data[3] | 0xf0);
	CST.NewFlag = 1;
}
void CSDLoad(void)
{
	CSDData.Compts.TotalChargTime = CCSData.Compts.TotalChargTime;
	CSDData.Compts.OutputEnegy = 100;//Unsure
	CSD.Data[0] = (UInt8)(CSDData.Compts.TotalChargTime);
	CSD.Data[1] = (UInt8)(CSDData.Compts.TotalChargTime >> 8);
	CSD.Data[2] = (UInt8)(CSDData.Compts.OutputEnegy);
	CSD.Data[3] = (UInt8)(CSDData.Compts.OutputEnegy>>8);
	CSD.Data[4] = 0xff;
	CSD.Data[5] = 0xff;
	CSD.Data[6] = 0xff;
	CSD.Data[7] = 0xff;
	CSD.NewFlag = 1;
}
void CEMLoad(void)
{
	CEM.Data[0] = (CEMData.data[0] | 0xfc);
	CEM.Data[1] = (CEMData.data[1] | 0xf0);
	CEM.Data[2] = (CEMData.data[2] | 0xc0);
	CEM.Data[3] = (CEMData.data[3]);
	CEM.NewFlag = 1;
}
void TPCMCTSLoad(void)
{
	TPCMCTS.Data[0] = 0x11;
	TPCMCTS.Data[1] = TPCMRTSData.Compts.TotalPackNum;
	TPCMCTS.Data[2] = 0x01;
	TPCMCTS.Data[3] = 0xFF;
	TPCMCTS.Data[4] = 0xFF;
	TPCMCTS.Data[5] = (UInt8)(TPCMRTSData.Compts.PGN);
	TPCMCTS.Data[6] = (UInt8)(TPCMRTSData.Compts.PGN >> 8);
	TPCMCTS.Data[7] = (UInt8)(TPCMRTSData.Compts.PGN >> 16);
	TPCMCTS.NewFlag = 1;
}
void TPCMRTSEndLoad(void)
{
	TPCMCTS.Data[0] = 0x13;
	TPCMCTS.Data[1] = (UInt8)(TPCMRTSData.Compts.MessageTotalLen);
	TPCMCTS.Data[2] = (UInt8)(TPCMRTSData.Compts.MessageTotalLen >> 8);
	TPCMCTS.Data[3] = TPCMRTSData.Compts.TotalPackNum;
	TPCMCTS.Data[4] = 0XFF;
	TPCMCTS.Data[5] = (UInt8)(TPCMRTSData.Compts.PGN);
	TPCMRTS.Data[6] = (UInt8)(TPCMRTSData.Compts.PGN >> 8);
	TPCMRTS.Data[7] = (UInt8)(TPCMRTSData.Compts.PGN >> 16);
	TPCMCTS.NewFlag = 1;
}
void CAN2Transmit500ms(void)
{
	if (CTS.NewFlag == 1)
	{
		MSCAN2Transmit(&CTS);
	}
	OSCRITICALENTRY();
}
void CAN2Transmit250ms(void)
{
	if (CRM.NewFlag == 1)
	{
		MSCAN2Transmit(&CRM);
	}
	if (CML.NewFlag == 1)
	{
		MSCAN2Transmit(&CML);
	}
	if (CRO.NewFlag == 1)
	{
		MSCAN2Transmit(&CRO);
	}
	if (CSD.NewFlag == 1)
	{
		MSCAN2Transmit(&CSD);
	}
	if (CEM.NewFlag == 1)
	{
		MSCAN2Transmit(&CEM);
	}
	OSCRITICALENTRY();
}
void CAN2Transmit50ms(void)
{
	if (CCS.NewFlag == 1)
	{
		MSCAN2Transmit(&CCS);
	}
	OSCRITICALENTRY();
}
void CAN2Transmit10ms(void)
{
	if (TPCMRTSData.Compts.ControlType == 0X10)
	{
		TPCMCTSLoad();
		MSCAN2Transmit(&TPCMCTS);
		TPCMRTSData.Compts.ControlType = 0;
	}
	if ((TPCMDTData.Compts.SerialNum>0)&&(TPCMDTData.Compts.SerialNum == TPCMRTSData.Compts.TotalPackNum))
	{
		TPCMRTSEndLoad();
		MSCAN2Transmit(&TPCMCTS);
		TPCMDTData.Compts.SerialNum = 0;
	}
	if (CST.NewFlag == 1)
	{
		MSCAN2Transmit(&CST);
	}
	OSCRITICALENTRY();
}
void BMSReceive(void)
{
	if ((TPCMRTS.CANID.ID.ID1 == CAN2RXIDR0) && (TPCMRTS.CANID.ID.ID2 == CAN2RXIDR1) && (TPCMRTS.CANID.ID.ID3 == CAN2RXIDR2) && (TPCMRTS.CANID.ID.ID4 == CAN2RXIDR3))
	{
		TPCMRTS.Data[0] = CAN2RXDSR0;
		TPCMRTS.Data[1] = CAN2RXDSR1;
		TPCMRTS.Data[2] = CAN2RXDSR2;
		TPCMRTS.Data[3] = CAN2RXDSR3;
		TPCMRTS.Data[4] = CAN2RXDSR4;
		TPCMRTS.Data[5] = CAN2RXDSR5;
		TPCMRTS.Data[6] = CAN2RXDSR6;
		TPCMRTS.Data[7] = CAN2RXDSR7;
		TPCMRTSData.Compts.ControlType = TPCMRTS.Data[0];
		if (TPCMRTSData.Compts.ControlType == 0X10)
		{
			TPCMRTSData.Compts.MessageTotalLen = (UInt16)(TPCMRTS.Data[1] + (TPCMRTS.Data[2] << 8));
			TPCMRTSData.Compts.TotalPackNum = TPCMRTS.Data[3];
			TPCMRTSData.Compts.PGN = (UInt32)(TPCMRTS.Data[5] + ((UInt32)TPCMRTS.Data[6] << 8) + ((UInt32)TPCMRTS.Data[7] << 16));
			TPCMRTS.NewFlag = 1;
		}
		else
		{
			TPCMRTSData.Compts.ControlType = 0;
		}
	}
	else if((TPCMDT.CANID.ID.ID1==CAN2RXIDR0)&&(TPCMDT.CANID.ID.ID2==CAN2RXIDR1)&&(TPCMDT.CANID.ID.ID3==CAN2RXIDR2)&&(TPCMDT.CANID.ID.ID4==CAN2RXIDR3))
	{
		TPCMDT.Data[0] = CAN2RXDSR0;
		TPCMDT.Data[1] = CAN2RXDSR1;
		TPCMDT.Data[2] = CAN2RXDSR2;
		TPCMDT.Data[3] = CAN2RXDSR3;
		TPCMDT.Data[4] = CAN2RXDSR4;
		TPCMDT.Data[5] = CAN2RXDSR5;
		TPCMDT.Data[6] = CAN2RXDSR6;
		TPCMDT.Data[7] = CAN2RXDSR7;
		TPCMDTData.Compts.SerialNum = TPCMDT.Data[0];
		TPCMDT.NewFlag = 1;
		switch (TPCMRTSData.Compts.PGN)
		{
		case 0x0200:
			switch (TPCMDT.Data[0])
			{
			case 1:
				BRMData.Compts.Version[0] = TPCMDT.Data[1];
				BRMData.Compts.Version[1] = TPCMDT.Data[2];
				BRMData.Compts.Version[2] = TPCMDT.Data[3];
				BRMData.Compts.BatType = TPCMDT.Data[4];
				BRMData.Compts.Capacity = (UInt16)(((UInt16)TPCMDT.Data[6] << 8) + TPCMDT.Data[5]);
				BRMData.Compts.TotalVol =  TPCMDT.Data[7] ;
				break;
			case 2:
				BRMData.Compts.TotalVol = (UInt16)(BRMData.Compts.TotalVol + ((UInt16)TPCMDT.Data[1] << 8));
				BRMData.Compts.Manufacturer[0] = TPCMDT.Data[2];
				BRMData.Compts.Manufacturer[1] = TPCMDT.Data[3];
				BRMData.Compts.Manufacturer[2] = TPCMDT.Data[4];
				BRMData.Compts.Manufacturer[3] = TPCMDT.Data[5];
				BRMData.Compts.BatSerialNum[0] = TPCMDT.Data[6];
				BRMData.Compts.BatSerialNum[1] = TPCMDT.Data[7];
				break;
			case 3:
				BRMData.Compts.BatSerialNum[2] = TPCMDT.Data[1];
				BRMData.Compts.BatSerialNum[3] = TPCMDT.Data[2];
				BRMData.Compts.Year = TPCMDT.Data[3] + 1985;
				BRMData.Compts.Month = TPCMDT.Data[4];
				BRMData.Compts.Day = TPCMDT.Data[5];
				BRMData.Compts.CHargingTimes = (UInt32)(TPCMDT.Data[6] + ((UInt32)TPCMDT.Data[7] << 8));
				break;
			case 4:
				BRMData.Compts.CHargingTimes=(UInt32)(BRMData.Compts.CHargingTimes + ((UInt32)TPCMDT.Data[1] << 16));
				BRMData.Compts.PropertyFlag = TPCMDT.Data[2];
				BRMData.Compts.Reserve = TPCMDT.Data[3];
				BRMData.Compts.VIN[0] = TPCMDT.Data[4];
				BRMData.Compts.VIN[1] = TPCMDT.Data[5];
				BRMData.Compts.VIN[2] = TPCMDT.Data[6];
				BRMData.Compts.VIN[3] = TPCMDT.Data[7];
				break;
			case 5:
				BRMData.Compts.VIN[4] = TPCMDT.Data[1];
				BRMData.Compts.VIN[5] = TPCMDT.Data[2];
				BRMData.Compts.VIN[6] = TPCMDT.Data[3];
				BRMData.Compts.VIN[7] = TPCMDT.Data[4];
				BRMData.Compts.VIN[8] = TPCMDT.Data[5];
				BRMData.Compts.VIN[9] = TPCMDT.Data[6];
				BRMData.Compts.VIN[10] = TPCMDT.Data[7];
				break;
			case 6:
				BRMData.Compts.VIN[11] = TPCMDT.Data[1];
				BRMData.Compts.VIN[12] = TPCMDT.Data[2];
				BRMData.Compts.VIN[13] = TPCMDT.Data[3];
				BRMData.Compts.VIN[14] = TPCMDT.Data[4];
				BRMData.Compts.VIN[15] = TPCMDT.Data[5];
				BRMData.Compts.VIN[16] = TPCMDT.Data[6];
				BRMData.Compts.BMSVersion[0] = TPCMDT.Data[7];
				BRMData.Compts.RecFinish = 1;
				break;
			case 7:
				BRMData.Compts.BMSVersion[1] = TPCMDT.Data[1];
				BRMData.Compts.BMSVersion[2] = TPCMDT.Data[2];
				BRMData.Compts.BMSVersion[3] = TPCMDT.Data[3];
				BRMData.Compts.BMSVersion[4] = TPCMDT.Data[4];
				BRMData.Compts.BMSVersion[5] = TPCMDT.Data[5];
				BRMData.Compts.BMSVersion[6] = TPCMDT.Data[6];
				BRMData.Compts.BMSVersion[7] = TPCMDT.Data[7];
				BRMData.Compts.RecFinish = 1;
				break;
			default:
				break;
			}
			break;
		case 0X0600:
			switch (TPCMDT.Data[0])
			{
			case 1:
				BCPData.Compts.MaxMonomerAllowVol = (UInt16)(TPCMDT.Data[1] + ((UInt16)TPCMDT.Data[2] << 8));
				BCPData.Compts.MaxAllowCur = (Int16)(TPCMDT.Data[3] + ((UInt16)TPCMDT.Data[4] << 8)) - 4000;
				BCPData.Compts.NominalEny = (UInt16)(TPCMDT.Data[5] + ((UInt16)TPCMDT.Data[6] << 8));
				BCPData.Compts.MaxAllowVol = TPCMDT.Data[7];
				break;
			case 2:
				BCPData.Compts.MaxAllowVol = (UInt16)(BCPData.Compts.MaxAllowVol+((UInt16)TPCMDT.Data[1] << 8));
				BCPData.Compts.MaxAllowTemp = (Int8)(TPCMDT.Data[2] - 50);
				BCPData.Compts.SOC = (UInt16)(TPCMDT.Data[3] + ((UInt16)TPCMDT.Data[4] << 8));
				BCPData.Compts.TotalVol = (UInt16)(TPCMDT.Data[5] + ((UInt16)TPCMDT.Data[6] << 8));
				BCPData.Compts.RecFinish = 1;
				break;
			}
		case 0x1100:
			switch (TPCMDT.Data[0])
			{
			case 1:
				BCSData.Compts.MeasurVol = (UInt16)(TPCMDT.Data[1] + ((UInt16)TPCMDT.Data[2]<<8));
				BCSData.Compts.MeasurCur = (Int16)(TPCMDT.Data[3] + ((UInt16)TPCMDT.Data[4] << 8)-4000);
				BCSData.Compts.MaxMonomer = (UInt16)(TPCMDT.Data[5] + (((UInt16)TPCMDT.Data[6] << 8) & 0x0f));
				BCSData.Compts.GroupNum = ((TPCMDT.Data[6] & 0xf0)>>4);
				BCSData.Compts.SOCNow = TPCMDT.Data[7];
				break;
			case 2:
				BCSData.Compts.SurplusTime = (UInt16)(TPCMDT.Data[1] + ((UInt16)TPCMDT.Data[2] << 8));
				BCSData.Compts.RecFinish = 1;
			}
			break;
		}
	}
	else if ((BRO.CANID.ID.ID1 == CAN2RXIDR0) && (BRO.CANID.ID.ID2 == CAN2RXIDR1) && (BRO.CANID.ID.ID3 == CAN2RXIDR2) && (BRO.CANID.ID.ID4 == CAN2RXIDR3))
	{
		BROData.Compts.IdentificationResult = CAN2RXDSR0;
		BRO.NewFlag = 1;
	}
	else if ((BCL.CANID.ID.ID1==CAN2RXIDR0)&&(BCL.CANID.ID.ID2==CAN2RXIDR1)&&(BCL.CANID.ID.ID3==CAN2RXIDR2)&&(BCL.CANID.ID.ID4==CAN2RXIDR3))
	{
		BCLData.Compts.RequestVol = (UInt16)(CAN2RXDSR0 + ((UInt16)CAN2RXDSR1 << 8));
		BCLData.Compts.RequestCur = (Int16)(CAN2RXDSR2 + ((UInt16)CAN2RXDSR3 << 8)-4000);
		BCLData.Compts.ChargMode = CAN2RXDSR4;
		BCL.NewFlag = 1;
	}
	else if ((BSM.CANID.ID.ID1 == CAN2RXIDR0) && (BSM.CANID.ID.ID2 == CAN2RXIDR1) && (BSM.CANID.ID.ID3 == CAN2RXIDR2) && (BSM.CANID.ID.ID4 == CAN2RXIDR3))
	{
		BSMData.Compts.HighestVolNum = CAN2RXDSR0+1;
		BSMData.Compts.HighestTemp = CAN2RXDSR1-50;
		BSMData.Compts.HighestTempCheckNum = CAN2RXDSR2+1;
		BSMData.Compts.LowestTemp = CAN2RXDSR3-50;
		BSMData.Compts.LowestTempCheckNum = CAN2RXDSR4+1;
		BSMData.data[5] = CAN2RXDSR5;
		BSMData.data[6] = CAN2RXDSR6;
		BSM.NewFlag = 1;
	}
	else if ((BST.CANID.ID.ID1 == CAN2RXIDR0) && (BST.CANID.ID.ID2 == CAN2RXIDR1) && (BST.CANID.ID.ID3 == CAN2RXIDR2) && (BST.CANID.ID.ID4 == CAN2RXIDR3))
	{
		BSTData.data[0] = CAN2RXDSR0;
		BSTData.data[1] = CAN2RXDSR1;
		BSTData.data[2] = CAN2RXDSR2;
		BSTData.data[3] = (CAN2RXDSR3 & 0x0f);
		BST.NewFlag = 1;
	}
	else if ((BSD.CANID.ID.ID1 == CAN2RXIDR0) && (BSD.CANID.ID.ID2 == CAN2RXIDR1) && (BSD.CANID.ID.ID3 == CAN2RXIDR2) && (BSD.CANID.ID.ID4 == CAN2RXIDR3))
	{
		BSDData.data[0] = CAN2RXDSR0;
		BSDData.data[2] = CAN2RXDSR1;
		BSDData.data[1] = CAN2RXDSR2;
		BSDData.data[4] = CAN2RXDSR3;
		BSDData.data[3] = CAN2RXDSR4;
		BSDData.Compts.LowestMonomerTemp = (Int8)(CAN2RXDSR5 - 50);
		BSDData.Compts.HighestMonomerTemp = (Int8)(CAN2RXDSR6 - 50);
		BSD.NewFlag = 1;
	}
	else if ((BEM.CANID.ID.ID1 == CAN2RXIDR0) && (BEM.CANID.ID.ID2 == CAN2RXIDR1) && (BEM.CANID.ID.ID3 == CAN2RXIDR2) && (BEM.CANID.ID.ID4 == CAN2RXIDR3))
	{
		BEMData.data[0] = (CAN2RXIDR0 & 0X0F);
		BEMData.data[1] = (CAN2RXIDR1 & 0X0F);
		BEMData.data[2] = (CAN2RXDSR2 & 0X0F);
		BEMData.data[3] = (CAN2RXDSR3 & 0x0F);
		BEM.NewFlag = 1;
	}
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void CAN2BMS(void)
{
	asm INC OSNesting;
	BMSReceive();
	asm BSET CAN2RFLG, #$01;
	asm DEC  OSNesting;
}
#pragma CODE_SEG DEFAULT