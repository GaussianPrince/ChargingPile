#ifndef _WIFIATH_H
#define _WIFIATH_H
#include "Include.h"
typedef union
{
	UInt8 data[2];
	struct
	{
		UInt8	ConfigEntryFlag : 1;
		UInt8 : 7;
		UInt8	WIFIATHState;
	}Compts;
}WIFIATHOperat;
#pragma DATA_SEG __RPAGE_SEG     RAMF1_T
extern WIFIATHOperat WIFIATHOperatBuff;
#pragma DATA_SEG DEFAULT
extern void WIFIATHConfig(void);
#endif
