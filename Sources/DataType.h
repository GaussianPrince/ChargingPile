/*****************************************************

   DataType.h defines some neccessary data types.
   Copyright (c) WangYunXing,Govlan
               All rights reserved
               
 *****************************************************/
#ifndef  _DATATYPE_H
#define  _DATATYPE_H
typedef unsigned char UInt8;
typedef char  Int8;
typedef unsigned int  UInt16;
typedef int  Int16;
typedef unsigned long int UInt32;
typedef long int Int32;
typedef union __DataConvert
{
	float  IEEE32_Data;
	UInt32 UInt32_Data;
	UInt8  UInt8_Data[4];
	UInt16 UInt16_Data[2];
}DataConvert;
typedef volatile struct 
{
	union 
	{
		UInt32 TotalID;
		struct 
		{
			UInt8 ID1;
			UInt8 ID2;
			UInt8 ID3;
			UInt8 ID4;
		}ID;
	}CANID;
	UInt8 Data[8];
	UInt8 Length;
	UInt8 Priority;
	UInt8 NewFlag;
}CanMsgBuf;	//15BYTES
typedef void(* OSTaskAddr)(void);
#endif