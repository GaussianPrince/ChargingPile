#ifndef _GOVLANOSCPU_H
#define _GOVLANOSCPU_H
#include "Include.h"
#pragma CODE_SEG __NEAR_SEG NON_BANKED
UInt16	 CPUSRSave(void);
void	 CPUSRRestore(UInt16 CCRBuff);
void     OSRunIdleTask(void);
void	 OSCtxSw(void);
void	 OSRTCTick(void);
void     OSTickCtxSw(void);
void     OSCtxSw(void);
#pragma  CODE_SEG  DEFAULT
#endif // !_GOVLANOSCPU_H

