#include "Include.h"
#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
Gun		GunBuff;
UInt16	SamplingData[10];
UInt16	ProcessData;
UInt8	DetectOK;
UInt8	DetectNO;
#pragma DATA_SEG DEFAULT
#ifdef _FLASHDEBUG
#pragma DATA_SEG __RPAGE_SEG     RAMF0_T
 UInt16	TestRead[10];
#pragma DATA_SEG DEFAULT
#endif
void GunInit(void)
{
	asm
	{
		BSET DDRB,#$30
		BCLR DDRB,#$40
		BSET PUCR,#$02
		MOVB #$F1,RPAGE
		BRSET PORTB,#$40,HIGHVOL
		BSET ELECTRONICLOCK_OK,#$01
		CLR  ELECTRONICLOCK_NO
		BRA  ADINIT
HIGHVOL :
		CLR ELECTRONICLOCK_OK
		BSET ELECTRONICLOCK_NO,#$01
ADINIT:
		MOVB #$20,ATD0CTL1
		MOVB #$00,ATD0CTL2
		MOVB #$30,ATD0CTL3
		MOVB #$AF,ATD0CTL4
		MOVB #$30,ATD0CTL5
		MOVW #$0001, ATD0DIEN
	}
}
void ADCal(void)
{
	static UInt8	Swap = 0;
	UInt8 i,j;
	UInt16	Tmp;
	for (i = 0; i< 9; i++)
	{
		Swap = 0;
		for (j = 0; j < 10 - i - 1;j++)
		{
			if (SamplingData[j] > SamplingData[j + 1])
			{
				Tmp = SamplingData[j];
				SamplingData[j] = SamplingData[j + 1];
				SamplingData[j + 1] = Tmp;
				Swap = 1;
			}
		}
		if (Swap == 0)
			break;
	}
	Tmp = 0;
	for (i = 3; i < 7; i++)
	{
		Tmp += SamplingData[i];
	}
	ProcessData = (Tmp >> 2);
}
void ADGet(void)
{
	static UInt8 n;
	SamplingData[n] = (UInt16)(ATD0DR0 >> 6);
	if (n > 8)
	{
		/*EFlashEraseBySector(0x00, 0x10);
		EFlashWriteWord(0x10, 0x00, (UInt16 *far)SamplingData, 12);
		EFlashEraseBySector(0x100, 0x101);
		EFlashWriteWord(0x10, 0x100, (UInt16 *far)DiffPriceBuff.Compts.CloudDiffPrice, 24);*/
		n = 0;
		ADCal();
	}
	else
	{
		/*EFlashReadWord(0x10, 0x00, (UInt16 *far)TestRead, 10);
		EFlashReadWord(0x10, 0x100, (UInt16 *far)CloudTest, 24);*/
		n++;
	}
	if (ProcessData > 750)
	{
		GunBuff.Compts.CC1 = 0;
	}
	else if (ProcessData > 300)
	{
		GunBuff.Compts.CC1 = 0;
	}
	else if (ProcessData > 200)
	{
		GunBuff.Compts.CC1 = 1;
	}
	OSCRITICALENTRY();
}
UInt8 ReadElectronicLock(void)
{
	return PORTB_PB6;
}
void ElectronicLockStateControl(void)
{
	if (GunBuff.Compts.LockElectronicLockFlag == 1)
	{
		if (ReadElectronicLock() == ELECTRONICLOCK_OK)
		{
			ResetElectronicLock();
			GunBuff.Compts.LockElectronicLockFlag = 0;
			GunBuff.Compts.ElectronicLockState = 3;
		}
		else
		{
			LockElectronicLock();
			GunBuff.Compts.ElectronicLockState = 1;
		}
	}
	else if (GunBuff.Compts.OpenElectronicLockFlag == 1)
	{
		if (ReadElectronicLock() == ELECTRONICLOCK_NO)
		{
			ResetElectronicLock();
			GunBuff.Compts.OpenElectronicLockFlag = 0;
			GunBuff.Compts.ElectronicLockState = 3;
		}
		else
		{
			OpenElectronicLock();
			GunBuff.Compts.ElectronicLockState = 2;
		}
	}
	OSCRITICALENTRY();
}
