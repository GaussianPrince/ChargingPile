/*****************************************************

	InfyPower.h defines message to communicate with Infy module
	Copyright (c) WangYunXing,Govlan
	All rights reserved

	Data space:15*24+1=361BYTES
*****************************************************/
#ifndef _INFYPOWER_H
#define _INFYPOWER_H
#include "Include.h"
/*****************************************************
	Define data structrues
*******************************************************/
typedef union 
{
	UInt8 data[2];
	struct 
	{
		UInt8 InfyCounter;
		UInt8 StartTimerFlag : 1;	//Start timer
		UInt8 LoopPowerOnFlowFlag : 1;	//Power on loop
		UInt8 LoopPowerOffFlowFlag : 1;//Power off loop
		UInt8 : 5;
	}Compts;
}InfyPowerOperation;
extern InfyPowerOperation InfyPowerOperationBuff;
extern CanMsgBuf InfyPowerOnMsg;						//Broadcast command which is to make module power on
extern CanMsgBuf InfyPowerOffMsg;					   //Broadcast command which is to make module power off
extern CanMsgBuf InfyVolCurSetMsg;					 //Broadcast command which is to set current and voltage for each module
extern CanMsgBuf InfyModuleNum;						//Read the number of all the modules 
extern CanMsgBuf InfyModuleOutput[MAXMODULENUM];					//Peer to peer to read voltage and current
extern CanMsgBuf InfyModuleReply[MAXMODULENUM];
extern CanMsgBuf InfyModuleNumReply;
/*****************************************************
	Achieve operation 
*******************************************************/
extern void InfyConfig(void);
extern void InfyPowerOn(void);
extern void InfyPowerOff(void);
extern void InfyTransmit(void);
extern void InfyCANIDInit(void);
extern void InfyAddToCAN0(void);
extern void InfyPowerOperationBuffInit(void);
extern void InfyReciever(void);
#endif 
