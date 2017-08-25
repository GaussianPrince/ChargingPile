#ifndef _EFLASH_H
#define	_EFLASH_H
#include "Include.h"
extern void EFlashInit(void);
extern void EFlashEraseBySector(UInt16 AddrStart16,UInt16 EndAddr16);
extern void EFlashWriteWord(UInt8 GPage,UInt16	AddrStart16,UInt16 *far InData,UInt16	Len);
extern void EFlashReadWord(UInt8 GPage,UInt16 Destin,UInt16 * far OutData,UInt16	Len);
#endif
