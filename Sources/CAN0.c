/*****************************************************

   Operate CAN0 
   Copyright (c) WangYunXing,Govlan
               All rights reserved
               
 *****************************************************/
#include"Include.h"
 /*****************************************************
	Store Module output
 *******************************************************/
ModuleOutput AllModuleData[MAXMODULENUM];
/*****************************************************
	Record operation 
*******************************************************/
CAN0Operation CAN0OperationBuff;
/*****************************************************
	Record action(function)
*******************************************************/
PowerControl AllModuleType[MAXMODULETYPE];
DataConvert ConvertVol;
DataConvert ConvertCur;
CanMsgBuf  CANIDTest;
/*****************************************************
	MSCAN uses OSCCLK,f=fcanclk/((1+TS1+TS2)*Prescaler)
*******************************************************/
void CAN0Init(void)
{
	asm
	{
		BSET CAN0CTL0,#$01
		BRCLR CAN0CTL1,#$01,*
		LDD #$80FF
		STAA CAN0CTL1
		BSET CAN0IDAC,#$10
		STAB CAN0IDMR0
		STAB CAN0IDMR1
		STAB CAN0IDMR2
		STAB CAN0IDMR3
		STAB CAN0IDMR4
		STAB CAN0IDMR5
		STAB CAN0IDMR6
		STAB CAN0IDMR7

		LDD    #$4F23
		STAA   CAN0BTR0
		STAB   CAN0BTR1
		BCLR  CAN0CTL0,#$01
		BRSET  CAN0CTL1,#$01,*
		BSET   CAN0RIER,#$01
	}
}
/*****************************************************
	Pay attention to CANID register map
*******************************************************/
void CANIDConvert(CanMsgBuf * InID)
{
	CanMsgBuf Temp,Temp1;
	Temp.CANID.TotalID=InID->CANID.TotalID;
	Temp1.CANID.ID.ID1 = (Temp.CANID.ID.ID1 << 3) + (Temp.CANID.ID.ID2 >> 5);
	Temp1.CANID.ID.ID2 = ((Temp.CANID.ID.ID2 << 3)&0xE0) + 0X18 + ((Temp.CANID.ID.ID2 << 1) & 0X06) + (Temp.CANID.ID.ID3 >> 7);
	Temp1.CANID.ID.ID3 = (Temp.CANID.ID.ID3 << 1) + (Temp.CANID.ID.ID4 >> 7);
	Temp1.CANID.ID.ID4 = (Temp.CANID.ID.ID4 << 1);
	InID->CANID.TotalID = Temp1.CANID.TotalID;
}
void CANIDDecode(CanMsgBuf *InID)
{
	CanMsgBuf Temp, Temp1;
	Temp.CANID.TotalID = InID->CANID.TotalID;
	Temp1.CANID.ID.ID1 = (Temp.CANID.ID.ID1 >> 3);
	Temp1.CANID.ID.ID2 = (Temp.CANID.ID.ID1 << 5) + ((Temp.CANID.ID.ID2 & 0xE0) >> 3) + ((Temp.CANID.ID.ID2 & 0x06) >> 1);
	Temp1.CANID.ID.ID3 = (Temp.CANID.ID.ID2 << 7) + (Temp.CANID.ID.ID3 >> 1);
	Temp1.CANID.ID.ID4 = (Temp.CANID.ID.ID3 << 7) + (Temp.CANID.ID.ID4 >> 1);
	InID->CANID.TotalID = Temp1.CANID.TotalID;
}
/*****************************************************
	Calculate total output
*******************************************************/
void CalculateTotalOutput(void)
{
	UInt8 n;
	CAN0OperationBuff.Compts.TotalVol = AllModuleData[0].Compts.ModuleOutVol;
	CAN0OperationBuff.Compts.TotalCur = 0;
	for (n = 0; n < CAN0OperationBuff.Compts.TotalNum; n++)
	{
		if (AllModuleData[n].Compts.ModuleOutVol > CAN0OperationBuff.Compts.TotalVol)
		{
			CAN0OperationBuff.Compts.TotalVol = AllModuleData[n].Compts.ModuleOutVol;
		}
		CAN0OperationBuff.Compts.TotalCur += AllModuleData[n].Compts.ModuleOutCur;
	}
}
/*****************************************************
	Zero out memory
*******************************************************/
void AllModuleDataInit(void)
{
	UInt8 n;
	for (n = 0; n < MAXMODULENUM; n++)
	{
		AllModuleData[n].data[0] = 0;
	}
}
void AllModuleTypeInit(void)
{
	UInt8 n;
	for (n = 0; n < MAXMODULETYPE; n++)
	{
		AllModuleType[n].Config = 0;
		AllModuleType[n].PowerOn = 0;
		AllModuleType[n].PowerOff = 0;
		AllModuleType[n].ExecuteTransmit = 0;
		AllModuleType[n].OverTimeFlag = 0;
	}
}
void CAN0OperationBuffInit(void)
{
	UInt8 n;
	for (n = 0; n < 3; n++)
	{
		CAN0OperationBuff.data[n] = 0;
	}
	//CAN0OperationBuff.Compts.ModuleSwitchCtl = 3;
	//For each module
	//CAN0OperationBuff.Compts.MaximumVol = 750;	//Unit 'V'
	//CAN0OperationBuff.Compts.MaximumCur = 20;	//Unit 'A'
}
/*****************************************************
	Use assembly to accelerate speed
*******************************************************/
void MSCAN0Transmit(CanMsgBuf *InCan)
{
	UInt8 n;
	if ((CAN0TFLG & 0X07) != 0X00)
	{
		CAN0TBSEL = CAN0TFLG;
		CAN0TXIDR0 = InCan->CANID.ID.ID1;
		CAN0TXIDR1 = InCan->CANID.ID.ID2;
		CAN0TXIDR2 = InCan->CANID.ID.ID3;
		CAN0TXIDR3 = InCan->CANID.ID.ID4;
		for (n = 0; n < InCan->Length; n++)
		{
			*((&CAN0TXDSR0) + n) = InCan->Data[n];
		}
		CAN0TXDLR = InCan->Length;
		CAN0TXTBPR = InCan->Priority;
		CAN0TFLG = CAN0TBSEL;
		InCan->NewFlag = 0;
	}
}
/*****************************************************
	Auto control the power module(s)
*******************************************************/
void PowerStateControl(void)
{
	if (CAN0OperationBuff.Compts.ModuleSwitchCtl == 0)
	{
		switch (CAN0OperationBuff.Compts.ModuleConfigType)
		{
		case 0:
			OSCRITICALENTRY();
			if (CAN0OperationBuff.Compts.EFFIntFlag == 0)
			{
				CAN0OperationBuff.Compts.ModuleType = 0;	//Critical resource
				CAN0OperationBuff.Compts.ModuleConfigType++;
			}
			OSCRITICALEXIT();
			if ((AllModuleType[0].Config != 0) && (AllModuleType[0].OverTimeFlag == 0))
			{
				(*AllModuleType[0].Config)();
				(*AllModuleType[0].ExecuteTransmit)();
			}
			break;
		case 1:
			OSCRITICALENTRY();
			if (CAN0OperationBuff.Compts.EFFIntFlag == 0)
			{
				CAN0OperationBuff.Compts.ModuleType = 1;	//Critical resource
				CAN0OperationBuff.Compts.ModuleConfigType = 0;
			}
			OSCRITICALEXIT();
			if ((AllModuleType[1].Config != 0) && (AllModuleType[1].OverTimeFlag == 0))
			{
				(*AllModuleType[1].Config)();				
				(*AllModuleType[1].ExecuteTransmit)();
			}
			else if (AllModuleType[1].OverTimeFlag == 1)
			{
				GovlanOSErrorCode = GOVLANOSCAN0OVERTIME;
			}
			break;
		}
	}
	else if (CAN0OperationBuff.Compts.ModuleSwitchCtl == 1)
	{
		(*AllModuleType[CAN0OperationBuff.Compts.ModuleType].PowerOn)();
		CalculateTotalOutput();
		(*AllModuleType[CAN0OperationBuff.Compts.ModuleType].ExecuteTransmit)();
	}
	else if (CAN0OperationBuff.Compts.ModuleSwitchCtl == 2)
	{
		(*AllModuleType[CAN0OperationBuff.Compts.ModuleType].PowerOff)();
		CalculateTotalOutput();
		(*AllModuleType[CAN0OperationBuff.Compts.ModuleType].ExecuteTransmit)();
	}
	OSCRITICALENTRY();
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void CAN0Power(void)
{
	asm INC OSNesting;
	ComOverTimeBuff.Compts.PowerOverTimeCounter = 0;
	if (CAN0OperationBuff.Compts.ModuleSwitchCtl == 0)
	{
		if ((InfyModuleNumReply.CANID.ID.ID1 == CAN0RXIDR0) && (InfyModuleNumReply.CANID.ID.ID2 == CAN0RXIDR1))
		{
			CAN0OperationBuff.Compts.EFFIntFlag = 1;
			CAN0OperationBuff.Compts.ModuleConfigType = 0;
			CAN0OperationBuff.Compts.ModuleType = 0;
		}
		else if ((InKeModuleReply[0].CANID.ID.ID1 == CAN0RXIDR0) && (InKeModuleReply[0].CANID.ID.ID2 == CAN0RXIDR1)&&((InKeModuleReply[0].CANID.ID.ID3 == CAN0RXIDR2)))
		{
			CAN0OperationBuff.Compts.EFFIntFlag = 1;
			CAN0OperationBuff.Compts.ModuleConfigType = 1;
			CAN0OperationBuff.Compts.ModuleType = 1;
		}
	}
	switch (CAN0OperationBuff.Compts.ModuleType)
	{
	case 0:
		InfyReciever();
		break;
	case 1:
		InKeReciever();
		break;
	}
	asm BSET CAN0RFLG, #$01;
	asm DEC  OSNesting;
}
#pragma CODE_SEG DEFAULT