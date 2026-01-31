/**
 * Idt.h
 * Created by Matheus Leme Da Silva
 */
#ifndef IDT_H
#define IDT_H
#include "Types.h"

struct IDTr {
	U16 Size;
	U32 Base;
} __attribute__((packed));

struct IDTEnt {
	U16 BaseLo;
	U16 SegSel;
	U8 Zero;
	U8 Attr;
	U16 BaseHi;
} __attribute__((packed));

struct IntFrame {
	U32 Cr2, Cr3;
	U32 Ds, Es, Fs, Gs;
	U32 Edi, Esi, Ebp, EspDummy, Ebx, Edx, Ecx, Eax;
	U32 IntNo, ErrCode;
	U32 Eip, Cs, Eflags;
	U32 UserEsp;
	U32 Ss;
} __attribute__((packed));

#define IDT_ENTRIES 256
extern struct IDTEnt IDT[IDT_ENTRIES];
extern struct IDTr IDTr;

void IDTSetGate(U8 gate, void *isr, U16 segSel, U8 attr);
void IDTInit(void);

#endif // IDT_H
