#include "Include.h"
void EFlashInit(void)
{
	asm
	{
		BRCLR FSTAT,#$80,*
		MOVB #$0F,FCLKDIV
		MOVB #$00,FCNFG
		BRCLR FCLKDIV,#$80,*
	}
}
void EFlashEraseBySector(UInt16 AddrStart16, UInt16 EndAddr16)
{
	UInt16	n;
	while (FSTAT_CCIF == 0);
	if (FSTAT & 0x30)
	{
		FSTAT |= 0x30;
	}
	FCCOBIX_CCOBIX = 0x00;
	FCCOBHI = 0x12;
	FCCOBLO = 0x10;
	FCCOBIX_CCOBIX = 0x01;
	for (n = AddrStart16; n < EndAddr16; n += 0x100)
	{
		FCCOB = AddrStart16 + n;
	}
	FSTAT_CCIF = 1;
	while (FSTAT_CCIF == 0);
}
void EFlashWriteWord(UInt8 GPage, UInt16 AddrStart16, UInt16 *far InData, UInt16	Len)
{
	UInt16 n;
	while (FSTAT_CCIF == 0);
	if (FSTAT & 0x30)
	{
		FSTAT |= 0x30;
	}
	for (n = 0; n < (Len / 4); n++)
	{
		FCCOBIX_CCOBIX = 0x00;
		FCCOBHI = 0x11;
		FCCOBLO = GPage;
		FCCOBIX_CCOBIX = 0x01;
		FCCOB = AddrStart16 + n * 8;
		FCCOBIX_CCOBIX = 0x02;
		FCCOB = InData[n * 4];
		FCCOBIX_CCOBIX = 0x03;
		FCCOB = InData[n * 4 + 1];
		FCCOBIX_CCOBIX = 0x04;
		FCCOB = InData[n * 4 + 2];
		FCCOBIX_CCOBIX = 0x05;
		FCCOB = InData[n * 4 + 3];
		FSTAT_CCIF = 1;
		while (FSTAT_CCIF == 0);
	}
}
void EFlashReadWord(UInt8 GPage, UInt16 Destin, UInt16 * far OutData, UInt16	Len)
{
	UInt16 n;
	UInt8 LastEPage;
	for (n = 0; n < Len; n++)
	{
		LastEPage = EPAGE;
		EPAGE = 0 + (Destin >> 10);
		OutData[n] = *(volatile UInt16 * far)(((UInt32)GPage << 16) + Destin);
		Destin = Destin + 2;
		EPAGE = LastEPage;
	}
}