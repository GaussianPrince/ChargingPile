NON_BANKED:       section  
GPAGE:    EQU $0010
EPAGE:    EQU $0017
RPAGE:    EQU $0016
PPAGE:    EQU $0015
CRGFLG:	  EQU $0037
	XREF  OSSchedule
	XREF  OSTaskHigh
	XREF  OSTaskCur
	XREF  OSRunning
	XREF  OSNesting

	XDEF CPUSRSave
	XDEF CPUSRRestore
	XDEF OSRunIdleTask
	XDEF OSCtxSw
	XDEF OSRTCTick
	XDEF OSTickCtxSw

;*******************************************
;	Store ccrw in D
;	Prevent interruption
;	
;*******************************************
CPUSRSave:	
	TFR CCRW,D
	SEI
	RTS
	
;*******************************************
;	Restore ccrw 
;	Back to origin
;	
;*******************************************
CPUSRRestore:
	TFR D,CCRW
	RTS
;*******************************************
;	   |--------|-------|
;	   | SP 	| Reg   |					--Stack top   |  low address
;	   |--------|-------|				|
;	   | SP  	| GPAGE |				|
;	   |--------|-------|				|
;	   | SP+=1	| PPAGE |				|		From low address to high address
;	   |--------|-------|			   \ /
;	   | SP+=1	| RPAGE |				|
;	   |--------|-------|
;	   | SP+=1	| EPAGE |	
;	   |--------|-------|
;	   | SP+=1	| U		|	
;	   |--------|-------|
;	   | SP+=1	| CCR	|	
;	   |--------|-------|
;	   | SP+=1	| B     |	
;	   |--------|-------|
;	   | SP+=1	| A     |	
;	   |--------|-------|
;	   | SP+=1	| XH    |	
;	   |--------|-------|
;	   | SP+=1	| XL    |	
;	   |--------|-------|
;	   | SP+=1	| YH    |	
;	   |--------|-------|
;	   | SP+=1	| YL    |	
;	   |--------|-------|
;	   | SP+=1	| PCH   |	
;	   |--------|-------|
;	   | SP+=1	| PCL   |	
;	   |--------|-------|
;	   | SP+=1	| IPPAGE|	
;	   |--------|-------|
;	   | SP+=1	| IPCH  |	
;	   |--------|-------|
;	   | SP+=1	| IPCL  |	
;	   |--------|-------|					--Stack bottom   |  high address
;*******************************************
OSRunIdleTask:	;Run idle task,loop forever
	MOVB #$01,OSRunning
	LDX  OSTaskHigh
	STX  OSTaskCur
	LDS  0,X
	PULA 
	STAA GPAGE
	PULA
	STAA PPAGE
	PULA 
	STAA RPAGE
	PULA 
	STAA EPAGE
	RTI
OSCtxSw:	;Run a  new  task
	LDX OSTaskHigh
	STX OSTaskCur
	LDS 0,X
	PULA 
	STAA GPAGE
	PULA
	STAA PPAGE
	PULA 
	STAA RPAGE
	PULA 
	STAA EPAGE
	RTI

OSTickCtxSw:
	LDX OSTaskHigh
	STX OSTaskCur
	LDS 0,X
	PULA
	STAA GPAGE
	PULA
	STAA PPAGE
	PULA
	STAA RPAGE
	PULA
	STAA EPAGE
	RTI


OSRTCTick:
	LDAA EPAGE
	PSHA
	LDAA RPAGE
	PSHA
	LDAA PPAGE
	PSHA
	LDAA GPAGE
	PSHA
;*******************************************
;		Determine  whether system is running
;*******************************************
	LDAA OSRunning
	CMPA #$01
	BNE NOTRUN
;*******************************************
;		Determine  whether there is(are) low level interruption(s)
;*******************************************
	INC OSNesting
	LDAB OSNesting
	CMPB #$01
	BNE INTNEST
	LDX OSTaskCur
	STS 0,X
OSRTCTickISR:
	BSET CRGFLG,#$80
	CALL OSSchedule
INTNEST:
NOTRUN:
	BSET CRGFLG,#$80
	PULA
	STAA GPAGE
	PULA
	STAA PPAGE
	PULA 
	STAA RPAGE
	PULA 
	STAA EPAGE
	RTI

