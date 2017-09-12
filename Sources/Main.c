/*****************************************************

   Main loop
   Copyright (c) WangYunXing,Govlan
               All rights reserved

 *****************************************************/
#include"Include.h"

#pragma MESSAGE DISABLE C1420
UInt8 AppStk1[128];
//UInt8 AppStk2[64];
UInt8 AppStk3[64];
UInt8 AppStk4[64];
UInt8 AppStk5[64];
UInt8 AppStk6[64];
UInt8 AppStk7[128];
UInt8 AppStk8[64];
UInt8 AppStk9[64];
UInt8 AppStk10[64];
UInt8 AppStk11[128];
UInt8 AppStk12[64];
UInt8 AppStk13[64];
UInt8 AppStk14[64];
UInt8 AppStk15[128];
UInt8 AppStk16[128];
UInt8 AppStk17[128];
UInt8 AppStk18[128];
UInt8 AppStk19[128];
UInt8 AppStk20[128];
void main(void)
{
	OSInit();
	TimerInit();
	CAN0Init();
	CAN2Init();
	DIDOInit();
	SCI1Init();
	GunInit();
	EFlashInit();
	SCI5Init();
	SCI4Init();
	SCI0Init();

	LocalTimeBuffInit();
	TimerOperationBuffInit();
	AllModuleDataInit();
	AllModuleTypeInit();
	CAN0OperationBuffInit();
	InfyCANIDInit();
	InfyPowerOperationBuffInit();
	InfyAddToCAN0();
	BMSCANIDInit();
	BMSMessageDataInit();
	BMSComCtlBuffInit();
	BMSStaMacBuffInit();
	DIDOBuffInit();
	MemoryZeroOut();
	IOBufferInit();
	IOBufferMonitorBufferInit();
	SCI1OperationBuffInit();
	SCI1StaMacBuffInit();
	DLT2007Init();
	DLT2007CRCCal();
	InKeCANIDInit();
	InKeAddToCAN0();

	MyMemset((UInt8*)CostManagementBuff.data, 0, 32);
	DiffPriceBuffInit();

	OSTaskAddrTable[OSStaticInc] = OSIDleTask;
	OSAddTask(OSIDleTask, (OSIdleStk + 128), OSIdleStk, 0, 0);

	/*OSTaskAddrTable[OSStaticInc] = OSFeedDog;
	OSAddTask(OSFeedDog, (AppStk2 + 64), AppStk2, 0, 150);*/

	OSTaskAddrTable[OSStaticInc] = PowerStateControl;
	OSAddTask(PowerStateControl, (AppStk7 + 128), AppStk7, 0, 40);

	OSTaskAddrTable[OSStaticInc] = CAN2Transmit10ms;
	OSAddTask(CAN2Transmit10ms, (AppStk3 + 64), AppStk3, 0, 2);

	OSTaskAddrTable[OSStaticInc] = CAN2Transmit50ms;
	OSAddTask(CAN2Transmit50ms, (AppStk4 + 64), AppStk4, 0, 10);

	OSTaskAddrTable[OSStaticInc] = CAN2Transmit250ms;
	OSAddTask(CAN2Transmit250ms, (AppStk5 + 64), AppStk5, 0, 50);

	OSTaskAddrTable[OSStaticInc] = CAN2Transmit500ms;
	OSAddTask(CAN2Transmit500ms, (AppStk6 + 64), AppStk6, 0, 100);

	OSTaskAddrTable[OSStaticInc] = SCI1StateControl;
	OSAddTask(SCI1StateControl, (AppStk11 + 128), AppStk11, 0, 176);


	OSTaskAddrTable[OSStaticInc] = ChargingStateControl;
	OSAddTask(ChargingStateControl, (AppStk1 + 128), AppStk1, 0, 2);


	OSTaskAddrTable[OSStaticInc] = LocalTimeCounter;
	OSAddTask(LocalTimeCounter, (AppStk8 + 64), AppStk8, 0, 200);

	OSTaskAddrTable[OSStaticInc] = DIDOGetInf;
	OSAddTask(DIDOGetInf, (AppStk9 + 64), AppStk9, 0, 10);

	OSTaskAddrTable[OSStaticInc] = DIDOOutput;
	OSAddTask(DIDOOutput, (AppStk10 + 64), AppStk10, 0, 202);

	OSTaskAddrTable[OSStaticInc] = CostStateControl;
	OSAddTask(CostStateControl, (AppStk12 + 64), AppStk12, 0, 180);

	OSTaskAddrTable[OSStaticInc] = ADGet;
	OSAddTask(ADGet, (AppStk13 + 64), AppStk13, 0, 2);

	OSTaskAddrTable[OSStaticInc] = ElectronicLockStateControl;
	OSAddTask(ElectronicLockStateControl, (AppStk14 + 64), AppStk14, 0, 20);

	OSTaskAddrTable[OSStaticInc] = CardStateControl;
	OSAddTask(CardStateControl, (AppStk15 + 128), AppStk15, 0, 60);

	OSTaskAddrTable[OSStaticInc] = HMIDisplayControl;
	OSAddTask(HMIDisplayControl, (AppStk16 + 128), AppStk16, 0, 6);

	OSTaskAddrTable[OSStaticInc] = SCI4Analysis;
	OSAddTask(SCI4Analysis, (AppStk17 + 128), AppStk18, 0, 0);

	OSTaskAddrTable[OSStaticInc] = SCI4StateControl;
	OSAddTask(SCI4StateControl, (AppStk18 + 128), (AppStk18), 0, 201);

	OSTaskAddrTable[OSStaticInc] = EFlashStateControl;
	OSAddTask(EFlashStateControl, (AppStk19 + 128), (AppStk19), 0, 205);

	OSTaskAddrTable[OSStaticInc] = ComFaultStateControl;
	OSAddTask(ComFaultStateControl, (AppStk20 + 128), AppStk20, 0, 202);

//	asm MOVB #$F1, RPAGE;
	EFlashReadWord(0x10, 0x00, (UInt16 *far)EFlashMainBuff.data, 73);
	if (EFlashMainBuff.Compts.SerialNum == 0xFFFFFFFF)
	{
		SerialNumTmp = 0;
		EFlashMainBuff.Compts.EndSectorNum = 1;
	}
	if (EFlashMainBuff.Compts.PileNum[0] != 0xFF)
	{
		for (ChargingEnd = 0; ChargingEnd < 10; ChargingEnd++)
		{
			asm MOVB #$F1, RPAGE;
			UserMoneyConvert.UInt8_Data[0] = EFlashMainBuff.Compts.PileNum[ChargingEnd];
			asm MOVB #$F0, RPAGE;
			HMITxCmdBuff.Compts.ConfigPage.PileNumRec[ChargingEnd + 6] = UserMoneyConvert.UInt8_Data[0];
		}
	}
	asm MOVB #$F1, RPAGE;
	if (EFlashMainBuff.Compts.EndSectorNum != 0xFF)
	{
		UserIDConvert.UInt16_Data[0] = EFlashMainBuff.Compts.EndSectorNum;
		UserMoneyConvert.UInt16_Data[0] = 0x100 * EFlashMainBuff.Compts.EndSectorNum;
		EFlashReadWord(0x10, UserMoneyConvert.UInt16_Data[0], (UInt16 *far)EFlashDataBlockBuff.data, 103);
		if (EFlashDataBlockBuff.Compts.UsedBlock == 0xFF)
		{
			EFlashDataBlockBuff.Compts.UsedBlock = 0;
		}
	}
	if (EFlashMainBuff.Compts.TieredPrice[0] != 0xFFFF)
	{
		for (ChargingEnd = 0; ChargingEnd < 24; ChargingEnd++)
		{
			DiffPriceBuff.Compts.CloudDiffPrice[ChargingEnd] = EFlashMainBuff.Compts.TieredPrice[ChargingEnd];
		}
	}
	if (EFlashMainBuff.Compts.ServicePrice != 0xFFFFFFFF)
	{
		DiffPriceBuff.Compts.CloudServicePrice = EFlashMainBuff.Compts.ServicePrice;
	}
	OSStart();
}