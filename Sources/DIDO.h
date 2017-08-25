#ifndef _DIDO_H
#define _DIDO_H
#include "Include.h"
typedef union 
{
	UInt8 data[2];
	struct 
	{
		//PORTK 
		UInt8 Fan : 1;   //PK0
		UInt8 AuxiliaryPower : 1; //PK1
		UInt8 MainNegativeRelay : 1;//PK3

		//PTP
		UInt8 MainPositiveReplay : 1; //PP0
		UInt8 DischargeReplay : 1; //PP1
		UInt8 Beep : 1;  //PP7

		//PORTA
		UInt8 MainNegativeFeedBack : 1; //PA3
		UInt8 MainPositiveFeedBack : 1;//PA4
		//1BYTES
		UInt8 EmergencyStop : 1; //PA5

		//PORTT
		UInt8 GunSelection : 1; //PT0
		UInt8 YellowLed : 1;//PT2
		UInt8 RedLed : 1; //PT3
		UInt8 GreenLed : 1;//PT4

		//PORTE 
		UInt8 NetModuleReset : 1;//PE6

		//PORTH
		UInt8 NetModuleState : 1;//PH1
	}Compts;
}DIDOStruct;
extern DIDOStruct DIDOBuff;
extern void DIDOInit(void);
extern void DIDOBuffInit(void);
extern void DIDOOutput(void);
extern void DIDOGetInf(void);

#endif