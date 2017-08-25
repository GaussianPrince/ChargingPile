#ifndef _HMI_H
#define _HMI_H
#include "Include.h"
#define  ERROREDGE    9
typedef union 
{
	UInt8 data[19];
	struct 
	{
		UInt8 CurrentPageNum;
		UInt8 ConfigClicks;
		UInt8 TraverseFault;
		UInt8 GunConStaReflesh;
		UInt8 AutoCharging;
		UInt8 TimingCharging;
		UInt16 ChargingTime;
		UInt8 ChargingConfirm;
		UInt8 BackToCardOperationPage;
		UInt8 BackToHome;
		UInt8 CardConfirm;
		UInt8 BackToChargingPage;
		UInt8 AdminEntry;
		UInt8 NetworkMethod[3];
		UInt8 NetConfigSave;
		UInt8 NetConfigRead;
	}Compts;
}HMIOperationStruct;

typedef union 
{
	UInt8 data[951];
	struct 
	{
		struct//418BYTES
		{
			UInt8 PileNumQRCode[128];
			UInt8 PileNumText[20];
			UInt8 AppDownloadAdress[128];
			UInt8 AdvertisementText[128];
			UInt8 AppStartKey[6];
		}HomePage;
		struct//40BYTES
		{
			UInt8 FaultType[8];
			UInt8 CustoSerTel[32];
		}FaultPage;
		struct//80BYTES 
		{
			UInt8 CardID[32];
			UInt8 CardMoney[10];
			UInt8 TipText[32];
			UInt8 TipClear[32];
			UInt8 GunConText[32];
			UInt8 GunUnConText[32];
			UInt8 CardStartKey[6];
			UInt8 TimingStartKey[6]
		}CardOperationPage;
		struct//12BYTES
		{
			UInt8 AppStartBack[6];
			UInt8 CardStartBack[6];
		}StartupPage;
		struct//84BYTES 
		{
			UInt8 EchoVol[8];
			UInt8 EchoCur[8];
			UInt8 EchoPower[10];
			UInt8 EchoBatLow[8];
			UInt8 EchoBatHigh[8];
			UInt8 EchoChargedFee[10];
			UInt8 EchoChargedAmount[8];
			UInt8 EchoSerPrice[10];
			UInt8 EchoChargedTime[8];
			UInt8 EchoSOC[8];
		}ChargingPage;
		struct //44BYTES
		{
			UInt8 OrderNum[26];
			UInt8 EndElectricity[8];
			UInt8 EndMoney[10];
		}EndPage;
		struct//172BYTES 
		{
			UInt8 PileNumRec[16];
			UInt8 NetModeRec1[8];
			UInt8 NetModeRec2[8];
			UInt8 NetModeRec3[8];
			UInt8 SSIDRec[26];
			UInt8 PwdRec[26];
			UInt8 LocalPortRec[8];
			UInt8 RemotePortRec[8];
			UInt8 RemoteIPRec1[8];
			UInt8 RemoteIPRec2[8];
			UInt8 RemoteIPRec3[8];
			UInt8 RemoteIPRec4[8];
			UInt8 LocalIPRec1[8];
			UInt8 LocalIPRec2[8];
			UInt8 LocalIPRec3[8];
			UInt8 LocalIPRec4[8];
		}ConfigPage;
		UInt8 WritePageReg[7];
		UInt8 WriteNetConFlag[8];
	}Compts;
}HMITxCmd;

#pragma DATA_SEG __RPAGE_SEG     RAMF0_T
extern HMIOperationStruct HMIOperationBuff;
extern HMITxCmd			  HMITxCmdBuff;
extern UInt8 PwdErrorCounter;
extern UInt32 AdminPwd;
extern UInt8  ConfigWait;
#pragma DATA_SEG DEFAULT
extern void HMIAnalysis(void);
extern void HMIDisplayControl(void);
extern void SCI0Init(void);
extern void SCI0SendN(UInt8 *far InData, UInt8 Len);
#endif