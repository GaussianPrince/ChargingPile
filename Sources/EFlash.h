#ifndef _EFLASH_H
#define	_EFLASH_H
#include "Include.h"
typedef union
{
	UInt8 data[51];
	struct
	{
		UInt32  SerialNum;
		UInt8   CardIDAsscii[18];
		UInt16  CostAllElectricity;
		UInt16	CostChargingElectricity;
		UInt32	ChargingDuration;
		UInt8   ChargingMode;
		UInt8   EndMothod;
		UInt16	SYear;
		UInt8   SMonth;
		UInt8   SDay;
		UInt8   SHour;
		UInt8   SMinute;
		UInt8   SSecond;
		UInt16  EYear;
		UInt8   EMonth;
		UInt8   EDay;
		UInt8   EHour;
		UInt8   EMinute;
		UInt8   ESecond;
		UInt16	CostAllMoney;
		UInt8   GunNum;
		UInt16  UseFlag;
	}Compts;
}CardHistory;
typedef union
{
	UInt8 data[146];
	struct
	{
		UInt8	StartSectorNum;
		UInt8	EndSectorNum;
		UInt16	TieredPrice[24];
		UInt32	ServicePrice;
		UInt8	PileNum[10];
		UInt8	ConnMethod;
		UInt8	SSIDWIFI[32];
		UInt8	WIFIPwd[32];
		UInt16	LocalPort;
		UInt16	RemotePort;
		UInt8	RemoteIP[4];
		UInt8	LocalIP[4];
		UInt32   SerialNum;
		UInt8  Reserve;
	}Compts;
}EFlashMain;
typedef union 
{
	UInt8 data[205];
	struct 
	{
		CardHistory CardHistoryData[4];
		UInt8 UsedBlock;
		UInt8 Reserve;
	}Compts;
}EFlashDataBlock;

typedef union 
{
	UInt8 data[2];
	struct 
	{
		UInt8 EFlashState;
		UInt8 TieredPriceSaveFlag : 1;
		UInt8 ServicePriceSaveFlag : 1;
		UInt8 NetConfigSaveFlag : 1;
		UInt8 CardRecSaveFlag : 1;
		UInt8 SerialNumSaveFlag : 1;
		UInt8 : 3;
	}Compts;
}EFlashOperat;
typedef union 
{
	UInt8 data[7];
	struct 
	{
		UInt16 Year;
		UInt8  Month;
		UInt8  Day;
		UInt8  Hour;
		UInt8  Minute;
		UInt8  Second;
	}Compts;
}TimeRecFormat;
typedef union 
{
	UInt8 data[14];
	struct 
	{
		TimeRecFormat TimeRecFormatData[2];
	}Compts;
}TimeRecFormatArr;

#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
extern EFlashMain EFlashMainBuff;
extern TimeRecFormatArr TimeRecFormatArrBuff;
extern EFlashDataBlock EFlashDataBlockBuff;
extern EFlashOperat EFlashOperatBuff;
extern UInt32 SerialNumTmp;
extern UInt8 CardIDToAsscii[17];
extern UInt8 CardIDIndex;
extern UInt32 CardIDTemp;
#pragma DATA_SEG DEFAULT
extern void CardIDAssciiFormat(void);
extern void EFlashInit(void);
extern void EFlashEraseBySector(UInt16 AddrStart16,UInt16 EndAddr16);
extern void EFlashWriteWord(UInt8 GPage,UInt16	AddrStart16,UInt16 *far InData,UInt16	Len);
extern void EFlashReadWord(UInt8 GPage,UInt16 Destin,UInt16 * far OutData,UInt16	Len);
extern void EFlashStateControl(void);
#endif
