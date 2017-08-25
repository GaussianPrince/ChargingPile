#ifndef _DLT6452007_H
#define _DLT6452007_H
#include "Include.h"
typedef struct 
{
	UInt8 EnergyReadCmd[20];
}DLT2007Cmd;
extern UInt8 DLT2007ConfigFlag;

extern DLT2007Cmd DLT2007CmdBuff;
extern void DLT2007Config(void);
extern void DLT2007CRCCal(void);
extern void DLT2007Init(void);
extern void DLT2007Analysis(void);
extern void DLT2007Transmit(void);
#endif 

