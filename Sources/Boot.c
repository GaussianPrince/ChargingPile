/*****************************************************

	Initialize stack pointer£¬zero out memory ,copydown data
	Copyright (c) WangYunXing,Govlan
	All rights reserved

*****************************************************/
#include"Include.h"
struct _tagStartup _startupData;
void main(void);
static void BootInit(void)
{
	asm
	{
		LDX	_startupData.pZeroOut
		LDY _startupData.nofZeroOuts
		BEQ CopyDown
		NextZeroOut :
	PSHY
		LDAB 1,X +
		LDY  2,X +
		STAB GPAGE
		PSHX
		LDX 0,X
		CLRA
NextByte :
		GSTAA 1,Y +
		MOVB #$55,ARMCOP
		MOVB #$AA,ARMCOP
		DBNE X,NextByte
		PULX
		LEAX 2,X
		PULY
		DEY
		BNE NextZeroOut
CopyDown :
		LDX _startupData.toCopyDownBeg
NextBlock :
		LDD 2,X +
		BEQ INITEND
		PSHD
		LDAA 1,X +
		LDY  2,X +
		STAA GPAGE
		PULD
Copy :
		PSHD
		LDAA 1,X +
		GSTAA 1,Y +
		PULD
		MOVB #$55, ARMCOP
		MOVB #$AA, ARMCOP
		DBNE D,Copy
		BRA  NextBlock
		INITEND :
	}
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void _Startup(void)
{
	asm
	{
		LDS  #$2100
		MOVB #$5, MMCCTL1
		MOVB #$00, COPCTL
	}
	BootInit();
	main();
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
