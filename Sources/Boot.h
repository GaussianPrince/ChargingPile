#ifndef _BOOT_H
#define _BOOT_H
typedef void(*_PFunc)(void);
typedef struct _LibInit {
	_PFunc *startup; /* address of startup desc */
} _LibInit;
typedef struct _Cpp {
	_PFunc initFunc; /* address of init function */
} _Cpp;
typedef struct {
	unsigned char *_FAR beg; int size;
} _Range;
typedef struct _Copy {
	int size; unsigned char * far dest;
} _Copy;

extern struct _tagStartup {
	unsigned char flags;
	_PFunc main;
	unsigned short stackOffset;
	unsigned short nofZeroOuts;
	_Range *pZeroOut;
	_Copy *toCopyDownBeg;
	unsigned short nofLibInits;
	_LibInit *libInits;
	unsigned short nofInitBodies;
	_Cpp *initBodies;
	unsigned short nofFiniBodies;
	_Cpp *finiBodies;
} _startupData;
#endif