#include "Include.h"
CostManagement CostManagementBuff;
DiffPrice DiffPriceBuff;
#ifdef NEARFLASHDEBUG
UInt16	CloudTest[24];
#endif
void MyMemset(UInt8 *StartAddr, UInt8 Val, UInt16 Size)
{
	UInt16 n;
	for (n = 0; n < Size; n++)
	{
		StartAddr[n] = Val;
	}
}
void DiffPriceBuffInit(void)
{
	UInt8 n;
	for (n = 0; n < 24; n++)
	{
		DiffPriceBuff.Compts.CloudDiffPrice[n] = 100;
	}
	DiffPriceBuff.Compts.CloudServicePrice = 60;
}
void CostPretreat(void)
{
	MyMemset((UInt8*)CostManagementBuff.data, 0, 36);
	CostManagementBuff.Compts.CostStartFlag = 1;
	CostManagementBuff.Compts.CostOrignalElectricity = SCI1OperationBuff.Compts.EngyVal;
	CostManagementBuff.Compts.CostElectricityRep = SCI1OperationBuff.Compts.EngyVal;
	CostManagementBuff.Compts.CostHourRep = LocalTimeBuff.Compts.Hour;
}
void CostCal(void)
{
	static UInt32 ElectricityUnit;
	ElectricityUnit = DiffPriceBuff.Compts.CloudDiffPrice[LocalTimeBuff.Compts.Hour];
	CostManagementBuff.Compts.CostElectricityTmp = SCI1OperationBuff.Compts.EngyVal - CostManagementBuff.Compts.CostElectricityRep;
	CostManagementBuff.Compts.CostTotalElectricity = SCI1OperationBuff.Compts.EngyVal - CostManagementBuff.Compts.CostOrignalElectricity;
	if (CostManagementBuff.Compts.CostTotalElectricity <= 100)
	{
		CostManagementBuff.Compts.CostTotalElectricity = 100;
		CostManagementBuff.Compts.CostTotalMoney = ElectricityUnit;
	}
	else
	{
		CostManagementBuff.Compts.CostMoneyTmp = ElectricityUnit*CostManagementBuff.Compts.CostElectricityTmp / 100;
		if (CostManagementBuff.Compts.CostHourRep != LocalTimeBuff.Compts.Hour)
		{
			CostManagementBuff.Compts.CostHourRep = LocalTimeBuff.Compts.Hour;
			CostManagementBuff.Compts.CostElectricityRep = SCI1OperationBuff.Compts.EngyVal;
			CostManagementBuff.Compts.CostMoneyPerHour = CostManagementBuff.Compts.CostMoneyPerHour + CostManagementBuff.Compts.CostMoneyTmp;
			CostManagementBuff.Compts.CostMoneyTmp = 0;
		}
		CostManagementBuff.Compts.CostTotalMoney = (CostManagementBuff.Compts.CostMoneyTmp + CostManagementBuff.Compts.CostMoneyPerHour);
	}
	CostManagementBuff.Compts.CostServicePrice = CostManagementBuff.Compts.CostTotalElectricity*DiffPriceBuff.Compts.CloudServicePrice / 100;
}
void CostStateControl(void)
{
	if ((BMSComCtlBuff.Compts.SystemState >= 3) && (BMSComCtlBuff.Compts.SystemState <= 4))
	{
		if (CostManagementBuff.Compts.CostStartFlag == 0)
		{
			CostPretreat();
		}
		else 
		{
			CostCal();
		}
	}
	OSCRITICALENTRY();
}