#include "Include.h"
BMSComCtlStruct BMSComCtlBuff;
BMSStaMacStruct BMSStaMacBuff[STATENUM];
CharFaultStruct CharFaultBuff;
UInt8 CheckEntry(void)
{
	if ((BMSComCtlBuff.Compts.CheckFinished == 0)&&(CharFaultBuff.data[0]==0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
UInt8 ShakeHandEntry(void)
{
	if ((BMSComCtlBuff.Compts.StartCharging == 1) && (BMSComCtlBuff.Compts.ShakeHandFinished == 0)&&(CharFaultBuff.data[0]==0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
UInt8 ConfigEntry(void)
{
	if ((BMSComCtlBuff.Compts.ShakeHandFinished == 1)&&(BMSComCtlBuff.Compts.ConfigFinished == 0) && (CharFaultBuff.data[0] == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
UInt8 ChargingEntry(void)
{
	if ((BMSComCtlBuff.Compts.ConfigFinished == 1) && (BMSComCtlBuff.Compts.ChargingFinished == 0) && (CharFaultBuff.data[0] == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
UInt8 EndEntry(void)
{
	if ((BMSComCtlBuff.Compts.ChargingFinished == 1) && (BMSComCtlBuff.Compts.EndFinished == 0) && (CharFaultBuff.data[0] == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
UInt8 ErrorEntry(void)
{
	if ((CharFaultBuff.data[0] != 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void CheckSetState(void)
{
	BMSComCtlBuff.Compts.SystemState = CHECK;
}
void ShakeHandSetState(void)
{
	BMSComCtlBuff.Compts.SystemState = SHAKEHAND;
}
void ConfigSetState(void)
{
	BMSComCtlBuff.Compts.SystemState = CONFIG;
}
void ChargingSetState(void)
{
	BMSComCtlBuff.Compts.SystemState = CHARGING;
}
void EndSetState(void)
{
	BMSComCtlBuff.Compts.SystemState = END;
}
void ErrorSetState(void)
{
	BMSComCtlBuff.Compts.SystemState = ERROR;
}
void CheckAction(void)
{
	BMSComCtlBuff.Compts.CheckFinished = 1;
}
static UInt16 WaitBRM = 0;
void ShakeHandAction(void)
{
	if ((BRMData.Compts.RecFinish == 0)&&(WaitBRM<1000))
	{
		WaitBRM++;
		asm BSET DIDOBuff.data[0], #$02;
		CRMData.Compts.IdentificationResult = 0X00;
		CRMLoad();
	}
	else if ((BRMData.Compts.RecFinish == 1) && (WaitBRM < 1000))
	{
		CRMData.Compts.IdentificationResult = 0XAA;
		CRMLoad();
		WaitBRM = 0;
		BMSComCtlBuff.Compts.ShakeHandFinished=1;
	}
	else
	{
		WaitBRM = 0;
		CharFaultBuff.Compts.BMSComFault = 1;
	}
}
static UInt16 WaitBCP = 0,WaitBRO=0;
void ConfigAction(void)
{
	if ((BCPData.Compts.RecFinish == 0) && (WaitBCP < 1000))
	{
		WaitBCP++;
		CRMData.Compts.IdentificationResult = 0XAA;
		CRMLoad();
	}
	else if ((BCPData.Compts.RecFinish == 1) && (WaitBCP < 1000))
	{
		CTSLoad();
		CMLLoad();
		WaitBRO++;
		if ((BRO.NewFlag==1)&&(WaitBRO<600))
		{
			CROData.Compts.IdentificationResult = 0xAA;
			CROLoad();
			WaitBRO = 0;
			WaitBCP = 0;
			asm BSET DIDOBuff.data[0], #$0c;
			CAN0OperationBuff.Compts.ModuleSwitchCtl = 1;
			BMSComCtlBuff.Compts.ConfigFinished = 1;
		}
		else if(WaitBRO>=600)
		{
			WaitBRO = 0;
			WaitBCP = 0;
			BMSComCtlBuff.Compts.ConfigFinished = 1;
		}
	}
	else
	{
		WaitBRO = 0;
		WaitBCP = 0;
		CharFaultBuff.Compts.BMSComFault = 1;
	}
}
static WaitBCL = 0,WaitBCS=0,WaitBSM=0;
void ChargingAction(void)
{
	if ((BST.NewFlag == 1)||(BCSData.Compts.SOCNow==100))
	{
		CSTData.Compts.BMSActTer = 1;
		CSTLoad();
		CAN0OperationBuff.Compts.ModuleSwitchCtl = 2;
		BMSComCtlBuff.Compts.ChargingFinished = 1;
	}
	else
	{
		if ((BCL.NewFlag == 0) && (WaitBCL < 1000))
		{
			WaitBCL++;
			CROLoad();
		}
		else if ((BCL.NewFlag == 1) && (WaitBCL < 1000))
		{
			WaitBCS++;
			asm BSET DIDOBuff.data[0], #$01;
			if ((BCSData.Compts.RecFinish == 1) && (WaitBCS < 600))
			{
				BCSData.Compts.RecFinish = 0;
				WaitBCS = 100;
				CCSLoad();
				WaitBSM++;
				if ((BSM.NewFlag == 1) && (WaitBSM < 600))
				{
					BSM.NewFlag = 0;
					WaitBSM = 100;
					if (BMSComCtlBuff.Compts.StopCharging == 1)
					{
						CSTData.Compts.ManualTer = 1;
						CSTLoad();
						WaitBCL = 0;
						WaitBCS = 0;
						WaitBSM = 0;
						CAN0OperationBuff.Compts.ModuleSwitchCtl = 2;
						BMSComCtlBuff.Compts.ChargingFinished = 1;
					}
				}
				else if(WaitBSM>=600)
				{
					WaitBCL = 0;
					WaitBCS = 0;
					WaitBSM = 0;
					CharFaultBuff.Compts.BMSComFault = 1;
				}
			}
			else if (WaitBCS >= 600)
			{
				WaitBCL = 0;
				WaitBCS = 0;
				WaitBSM = 0;
				CharFaultBuff.Compts.BMSComFault = 1;
			}
		}
		else
		{
			WaitBCL = 0;
			WaitBCS = 0;
			WaitBSM = 0;
			CharFaultBuff.Compts.BMSComFault = 1;
		}
	}
}
static WaitBST = 0,WaitBSD=0;
void EndAction(void)
{
	if ((BST.NewFlag == 0) && (WaitBST < 1000))
	{
		WaitBST++;
		CSTLoad();
	}
	else if ((BST.NewFlag == 1) && (WaitBST < 1000))
	{
		WaitBSD++;
		if ((BSD.NewFlag == 0)&&(WaitBSD<600))
		{
			CSDLoad();
		}
		else if ((BSD.NewFlag == 1) && (WaitBSD <600))
		{
			WaitBSD =0;
			WaitBST = 0;
			if ((CAN0OperationBuff.Compts.TotalCur < 30)&&(CAN0OperationBuff.Compts.TotalVol<200))
			{
				asm BCLR DIDOBuff.data[0], #$0C;
				asm BSET DIDOBuff.data[0], #$10;
				if (CAN0OperationBuff.Compts.TotalVol < 120)
				{
					asm BCLR DIDOBuff.data[0], #$3F;
					BMSComCtlBuff.Compts.EndFinished = 1;
				}
			}
		}
		else if ((WaitBSD>=600))
		{
			WaitBSD = 0;
			WaitBST = 0;
			CharFaultBuff.Compts.BMSComFault = 1;
		}
	}
}
void ErrorAction(void)
{
	asm BCLR DIDOBuff.data[0], #$0F;
	CAN0OperationBuff.Compts.ModuleSwitchCtl = 2;//Set switch 
	BMSComCtlBuff.Compts.ErrorFinished = 1;
}
void  BMSComCtlBuffInit(void)
{
	UInt8 n;
	for (n = 0; n < 2; n++)
	{
		BMSComCtlBuff.data[n] = 0;
	}
}
void BMSStaMacBuffInit(void)
{
	UInt8 n;
	for (n = 0; n < 6; n++)
	{
		switch (n)
		{
		case 0:
			BMSStaMacBuff[0].Entry = CheckEntry;
			BMSStaMacBuff[0].Action = CheckAction;
			BMSStaMacBuff[0].SetState = CheckSetState;
			break;
		case 1:
			BMSStaMacBuff[1].Entry = ShakeHandEntry;
			BMSStaMacBuff[1].Action = ShakeHandAction;
			BMSStaMacBuff[1].SetState = ShakeHandSetState;
			break;
		case 2:
			BMSStaMacBuff[2].Entry = ConfigEntry;
			BMSStaMacBuff[2].Action = ConfigAction;
			BMSStaMacBuff[2].SetState = ConfigSetState;
			break;
		case 3:
			BMSStaMacBuff[3].Entry = ChargingEntry;
			BMSStaMacBuff[3].Action = ChargingAction;
			BMSStaMacBuff[3].SetState = ChargingSetState;
			break;
		case 4:
			BMSStaMacBuff[4].Entry = EndEntry;
			BMSStaMacBuff[4].Action = EndAction;
			BMSStaMacBuff[4].SetState=EndSetState;
			break;
		case 5:
			BMSStaMacBuff[5].Entry = ErrorEntry;
			BMSStaMacBuff[5].Action = ErrorAction;
			BMSStaMacBuff[5].SetState = ErrorSetState;
			break;
		}
	}
}
void ChargingStateControl(void)
{
	UInt8 n;
	if ((*BMSStaMacBuff[BMSComCtlBuff.Compts.SystemState].Entry)())
	{
		(*BMSStaMacBuff[BMSComCtlBuff.Compts.SystemState].Action)();
	}
	else
	{
		for (n = 0; n < 6; n++)
		{
			if ((*BMSStaMacBuff[n].Entry)())
			{
				(*BMSStaMacBuff[n].SetState)();
			}
		}
	}
	OSCRITICALENTRY();
}