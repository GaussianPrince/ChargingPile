#ifndef _GUN_H
#define _GUN_H
#include "Include.h"
#define _FLASHDEBUG
typedef union
{
	UInt8 data[4];
	struct
	{
		UInt8	CC1 : 1;
		UInt8	LockElectronicLockFlag : 1;
		UInt8	OpenElectronicLockFlag : 1;
		UInt8 : 5;
		UInt8	ElectronicLockState;
		UInt16	ElectronicLockCounter;
	}Compts;
}Gun;
#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
extern Gun		GunBuff;
extern UInt16	SamplingData[10];
extern UInt16	ProcessData;
extern UInt8	DetectOK;
extern UInt8	DetectNO;
#define  ELECTRONICLOCK_OK DetectOK
#define	 ELECTRONICLOCK_NO DetectNO
#pragma DATA_SEG DEFAULT
#ifdef _FLASHDEBUG
#pragma DATA_SEG __RPAGE_SEG     RAMF0_T
extern UInt16	TestRead[10];
#pragma DATA_SEG DEFAULT
#endif
extern void		GunInit(void);
extern void		ADCal(void);
extern void		ADGet(void);
extern UInt8	ReadElectronicLock(void);
extern void		ElectronicLockStateControl(void);
#define LockElectronicLock()	{asm BSET PORTB,#$20;asm BCLR PORTB,#$10;}
#define	OpenElectronicLock()	{asm BCLR PORTB,#$20;asm BSET PORTB,#$10;}
#define	ResetElectronicLock()	{asm BCLR PORTB,#$30;}
#endif
