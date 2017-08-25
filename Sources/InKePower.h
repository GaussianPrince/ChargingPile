#ifndef _INKEPOWER_H
#define _INKEPOWER_H
#include "Include.h"
typedef union 
{
	UInt8	data[2];
	struct 
	{
		UInt8	InKeCounter;
		UInt8	StartTimerFlag : 1;
		UInt8	LoopPowerOnFlowFlag : 1;
		UInt8	LoopPowerOffFlowFlag : 1;
		UInt8 : 4;
	}Compts;
}InKePowerOperation;
extern InKePowerOperation InKePowerOperationBuff;
extern CanMsgBuf	InKeMultUseMsg;
extern CanMsgBuf	InKeModuleOutput[MAXMODULENUM];
extern CanMsgBuf	InKeModuleReply[MAXMODULENUM];
extern UInt32		InKeModuleCounter;

extern void			InKeConfig(void);
extern void			InKePowerOn(void);
extern void			InKePowerOff(void);
extern void			InKeTransmit(void);
extern void			InKeCANIDInit(void);
extern void			InKeAddToCAN0(void);
extern void			InKeReciever(void);
#endif
