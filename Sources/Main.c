/*****************************************************

   Main loop
   Copyright (c) WangYunXing,Govlan
               All rights reserved

 *****************************************************/
#include"Include.h"

#pragma MESSAGE DISABLE C1420
UInt8 AppStk1[128];
UInt8 AppStk2[64];
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

	OSTaskAddrTable[OSStaticInc] = OSFeedDog;
	OSAddTask(OSFeedDog, (AppStk2 + 64), AppStk2, 0, 180);

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
	OSAddTask(CardStateControl, (AppStk15 + 128), AppStk15, 0, 80);

	OSStart();
}