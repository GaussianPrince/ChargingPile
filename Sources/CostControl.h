#ifndef _COSTCONTROL_H
#define _COSTCONTROL_H
#include "Include.h"
#define NEARFLASHDEBUG
typedef union 
{
	UInt32 data[9];
	struct 
	{
		UInt32 CostMoneyTmp;
		UInt32 CostMoneyPerHour;
		UInt32 CostTotalMoney;
		UInt32 CostServicePrice;
		UInt32 CostElectricityTmp;
		UInt32 CostTotalElectricity;
		UInt32 CostOrignalElectricity;
		UInt32 CostElectricityRep;
		UInt32 CostStartFlag : 8;
		UInt32 CostHourRep : 8;
		UInt32 : 16;
	}Compts;
}CostManagement;
extern CostManagement CostManagementBuff;
typedef union 
{
	UInt32 data[15];
	struct 
	{
		UInt8 CloudTime[8];//2 32-Bit
		UInt16 CloudDiffPrice[24]; //12 32-bit
		UInt32 CloudServicePrice;
	}Compts;
}DiffPrice;
#ifdef  NEARFLASHDEBUG
extern UInt16	CloudTest[24];
#endif 
extern DiffPrice DiffPriceBuff;
extern void MyMemset(UInt8 *StartAddr, UInt8 Val, UInt16 Size);
extern void CostPretreat(void);
extern void CostStateControl(void);
extern void CostCal(void);
extern void DiffPriceBuffInit(void);
#endif 

