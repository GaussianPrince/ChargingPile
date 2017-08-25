#ifndef _CHARGINGSTATECONTROL_H
#define _CHARGINGSTATECONTROL_H
#include "Include.h"
#define  CHECK     0
#define  SHAKEHAND 1
#define  CONFIG    2
#define  CHARGING  3
#define  END       4
#define  ERROR     5
#define  STATENUM  6
typedef union 
{
	UInt8 data[2];
	struct 
	{
		UInt8 SystemState;
		UInt8 CheckFinished : 1;
		UInt8 ShakeHandFinished : 1;
		UInt8 ConfigFinished : 1;
		UInt8 ChargingFinished : 1;
		UInt8 EndFinished : 1;
		UInt8 ErrorFinished : 1;
		UInt8 StartCharging : 1;
		UInt8 StopCharging : 1;
	}Compts;
}BMSComCtlStruct;
extern BMSComCtlStruct BMSComCtlBuff;
typedef struct
{
	UInt8(*Entry)(void);
	void(*Action)(void);
	void(*SetState)(void);
}BMSStaMacStruct;
extern BMSStaMacStruct BMSStaMacBuff[STATENUM];
typedef union
{
	UInt8 data[1];
	struct 
	{
		UInt8 BMSComFault : 1;
		UInt8 : 7;
	}Compts;
}CharFaultStruct;
extern CharFaultStruct CharFaultBuff;
extern void  BMSComCtlBuffInit(void);
extern void  BMSStaMacBuffInit(void);
extern UInt8 CheckEntry(void);
extern UInt8 ShakeHandEntry(void);
extern UInt8 ConfigEntry(void);
extern UInt8 ChargingEntry(void);
extern UInt8 EndEntry(void);
extern UInt8 ErrorEntry(void);
extern void  CheckSetState(void);
extern void  ShakeHandSetState(void);
extern void  ConfigSetState(void);
extern void  ChargingSetState(void);
extern void  EndSetState(void);
extern void  ErrorSetState(void);
extern void  CheckAction(void);
extern void  ConfigAction(void);
extern void  ChargingAction(void);
extern void  EndAction(void);
extern void  ErrorAction(void);
extern void  ChargingStateControl(void);
#endif
