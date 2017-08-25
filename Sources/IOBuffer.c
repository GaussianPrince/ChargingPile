#include "Include.h"
#pragma DATA_SEG __RPAGE_SEG     RAMF0_T
HashTable IOBuffer[5];
IOBufferMonitor IOBufferMonitorBuffer;
UInt8 HMIArr[512];
UInt8 CardArr[512];
UInt8 NetArr[512];
UInt8 InsultArr[512];
UInt8 VolmeterArr[512];
#pragma DATA_SEG DEFAULT

void IOBufferInit(void)
{
	UInt16 n;
	UInt16 Address;
	IOBuffer[0].FreeHeader = (MemoryList*)(&HMIArr[0]);
	IOBuffer[0].Front = (MemoryList*)(&HMIArr[0]);
	IOBuffer[0].Rear = (MemoryList*)(&HMIArr[0]);

	IOBuffer[1].FreeHeader = (MemoryList*)(&CardArr[0]);
	IOBuffer[1].Front = (MemoryList*)(&CardArr[0]);
	IOBuffer[1].Rear = (MemoryList*)(&CardArr[0]);

	IOBuffer[2].FreeHeader = (MemoryList*)(&NetArr[0]);
	IOBuffer[2].Front = (MemoryList*)(&NetArr[0]);
	IOBuffer[2].Rear = (MemoryList*)(&NetArr[0]);

	IOBuffer[3].FreeHeader = (MemoryList*)(&InsultArr[0]);
	IOBuffer[3].Front = (MemoryList*)(&InsultArr[0]);
	IOBuffer[3].Rear = (MemoryList*)(&InsultArr[0]);

	IOBuffer[4].FreeHeader = (MemoryList*)(&VolmeterArr[0]);
	IOBuffer[4].Front = (MemoryList*)(&VolmeterArr[0]);
	IOBuffer[4].Rear = (MemoryList*)(&VolmeterArr[0]);
	for (n = 0; n < 4; n++)
	{
		IOBuffer[n].BlockNum = 0;
		if (n == 3)
		{
			Address = (UInt16)(&HMIArr[0]);
			HMIArr[n * 128 + 1] = (UInt8)(Address);
			HMIArr[n * 128] = (UInt8)(Address >> 8);

			Address = (UInt16)(&CardArr[0]);
			CardArr[n * 128 + 1] = (UInt8)(Address);
			CardArr[n * 128] = (UInt8)(Address >> 8);

			Address = (UInt16)(&NetArr[0]);
			NetArr[n * 128 + 1] = (UInt8)(Address);
			NetArr[n * 128] = (UInt8)(Address >> 8);

			Address = (UInt16)(&InsultArr[0]);
			InsultArr[n * 128 + 1] = (UInt8)(Address);
			InsultArr[n * 128] = (UInt8)(Address >> 8);

			Address = (UInt16)(&VolmeterArr[0]);
			VolmeterArr[n * 128 + 1] = (UInt8)(Address);
			VolmeterArr[n * 128] = (UInt8)(Address >> 8);
		}
		else
		{
			Address = (UInt16)(&HMIArr[(n + 1) * 128]);
			HMIArr[n * 128 + 1] = (UInt8)(Address);
			HMIArr[n * 128] = (UInt8)(Address >> 8);

			Address = (UInt16)(&CardArr[(n + 1) * 128]);
			CardArr[n * 128 + 1] = (UInt8)(Address);
			CardArr[n * 128] = (UInt8)(Address >> 8);

			Address = (UInt16)(&NetArr[(n + 1) * 128]);
			NetArr[n * 128 + 1] = (UInt8)(Address);
			NetArr[n * 128] = (UInt8)(Address >> 8);

			Address = (UInt16)(&InsultArr[(n + 1) * 128]);
			InsultArr[n * 128 + 1] = (UInt8)(Address);
			InsultArr[n * 128] = (UInt8)(Address >> 8);

			Address = (UInt16)(&VolmeterArr[(n + 1) * 128]);
			VolmeterArr[n * 128 + 1] = (UInt8)(Address);
			VolmeterArr[n * 128] = (UInt8)(Address >> 8);
		}
	}
}
void MemoryZeroOut(void)
{
	UInt16 n;
	for (n = 0; n < 512; n++)
	{
		HMIArr[n] = 0;
		NetArr[n] = 0;
		InsultArr[n] = 0;
		VolmeterArr[n] = 0;
		CardArr[n] = 0;
	}
}
void IOBufferMonitorBufferInit(void)
{
	UInt8 n;
	for (n = 0; n < 15; n++)
	{
		IOBufferMonitorBuffer.data[n] = 0;
	}
}
UInt8 IsFull(UInt8 Type)
{
	if (IOBuffer[Type].Front == IOBuffer[Type].Rear->Next)
	{
		return  1;
	}
	else
	{
		return 0;
	}
}
UInt8 IsEmpty(UInt8 Type)
{
	if (IOBuffer[Type].Front == IOBuffer[Type].Rear)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
UInt8 EnQueue(UInt8 Type)
{
	if (IsFull(Type) == 1)
	{
		return 0;
	}
	else
	{
		IOBuffer[Type].Rear = IOBuffer[Type].Rear->Next;
	}
	return 1;
}
UInt8 ExQueue(UInt8 Type)
{
	if (IsEmpty(Type) == 1)
	{
		return 0;
	}
	else
	{
		IOBuffer[Type].Front = IOBuffer[Type].Front->Next;
	}
	return 1;
}