/**
 * Idt.c
 * Created by Matheus Leme Da Silva
 */
#include "Vga.h"
#include "Idt.h"
#include "Types.h"
#include "Pic.h"
#include "Panic.h"
#include "Util.h"

struct IDTEnt IDT[IDT_ENTRIES];
struct IDTr IDTr;

// Set a IDT Gate
void IDTSetGate(U8 gate, void *isr, U16 segSel, U8 attr) {
	IDT[gate].BaseLo = (U32)isr & 0xFFFF;
	IDT[gate].SegSel = segSel;
	IDT[gate].Zero = 0;
	IDT[gate].Attr = attr;
	IDT[gate].BaseHi = ((U32)isr >> 16) & 0xFFFF;
}

const char* EXCEPTIONS[] = {
    "DIV0ERR ", "DEBUG   ", "NMI     ", "BREAKPT ",
    "OVERFLOW", "BOUNDS  ", "INVOPCOD", "DEVNOTAV",
    "DBLFAULT", "COPROSEG", "INVTSS  ", "SEGNOTPR",
    "STKFAULT", "GENPROT ", "PAGEFLT ", "RESERVED",
    "FPUERR  ", "ALIGNCK ", "MCHCK   ", "SIMDERR ",
    "VIRTUAL ", "CTRLPROT", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED",
    "RESERVED", "RESERVED", "RESERVED", "RESERVED"
};

// Handles all interrupts
void InterruptHandler(struct IntFrame *f) {
	if (f->IntNo <= 31) {
		if (f->IntNo == 14) {
			Puts("Page Fault at ");
			PutHexU32(f->Cr2);
			Puts("\r\n");
		}
		Panic(EXCEPTIONS[f->IntNo]);
	}

	if (f->IntNo >= 32 && f->IntNo <= 47) {
		PICSendEoi(f->IntNo - 32);
		PICExecIrq(f->IntNo - 32, f);
	}
}

extern void Isr0(void);
extern void Isr1(void);
extern void Isr2(void);
extern void Isr3(void);
extern void Isr4(void);
extern void Isr5(void);
extern void Isr6(void);
extern void Isr7(void);
extern void Isr8(void);
extern void Isr9(void);
extern void Isr10(void);
extern void Isr11(void);
extern void Isr12(void);
extern void Isr13(void);
extern void Isr14(void);
extern void Isr15(void);
extern void Isr16(void);
extern void Isr17(void);
extern void Isr18(void);
extern void Isr19(void);
extern void Isr20(void);
extern void Isr21(void);
extern void Isr22(void);
extern void Isr23(void);
extern void Isr24(void);
extern void Isr25(void);
extern void Isr26(void);
extern void Isr27(void);
extern void Isr28(void);
extern void Isr29(void);
extern void Isr30(void);
extern void Isr31(void);

extern void Isr32(void);
extern void Isr33(void);
extern void Isr34(void);
extern void Isr35(void);
extern void Isr36(void);
extern void Isr37(void);
extern void Isr38(void);
extern void Isr39(void);
extern void Isr40(void);
extern void Isr41(void);
extern void Isr42(void);
extern void Isr43(void);
extern void Isr44(void);
extern void Isr45(void);
extern void Isr46(void);
extern void Isr47(void);

// Initializes GDT
void IDTInit(void) {
	IDTSetGate(0, Isr0, 0x08, 0x8E);
	IDTSetGate(1, Isr1, 0x08, 0x8E);
	IDTSetGate(2, Isr2, 0x08, 0x8E);
	IDTSetGate(3, Isr3, 0x08, 0x8E);
	IDTSetGate(4, Isr4, 0x08, 0x8E);
	IDTSetGate(5, Isr5, 0x08, 0x8E);
	IDTSetGate(6, Isr6, 0x08, 0x8E);
	IDTSetGate(7, Isr7, 0x08, 0x8E);
	IDTSetGate(8, Isr8, 0x08, 0x8E);
	IDTSetGate(9, Isr9, 0x08, 0x8E);
	IDTSetGate(10, Isr10, 0x08, 0x8E);
	IDTSetGate(11, Isr11, 0x08, 0x8E);
	IDTSetGate(12, Isr12, 0x08, 0x8E);
	IDTSetGate(13, Isr13, 0x08, 0x8E);
	IDTSetGate(14, Isr14, 0x08, 0x8E);
	IDTSetGate(15, Isr15, 0x08, 0x8E);
	IDTSetGate(16, Isr16, 0x08, 0x8E);
	IDTSetGate(17, Isr17, 0x08, 0x8E);
	IDTSetGate(18, Isr18, 0x08, 0x8E);
	IDTSetGate(19, Isr19, 0x08, 0x8E);
	IDTSetGate(20, Isr20, 0x08, 0x8E);
	IDTSetGate(21, Isr21, 0x08, 0x8E);
	IDTSetGate(22, Isr22, 0x08, 0x8E);
	IDTSetGate(23, Isr23, 0x08, 0x8E);
	IDTSetGate(24, Isr24, 0x08, 0x8E);
	IDTSetGate(25, Isr25, 0x08, 0x8E);
	IDTSetGate(26, Isr26, 0x08, 0x8E);
	IDTSetGate(27, Isr27, 0x08, 0x8E);
	IDTSetGate(28, Isr28, 0x08, 0x8E);
	IDTSetGate(29, Isr29, 0x08, 0x8E);
	IDTSetGate(30, Isr30, 0x08, 0x8E);
	IDTSetGate(31, Isr31, 0x08, 0x8E);

	IDTSetGate(32, Isr32, 0x08, 0x8E);
	IDTSetGate(33, Isr33, 0x08, 0x8E);
	IDTSetGate(34, Isr34, 0x08, 0x8E);
	IDTSetGate(35, Isr35, 0x08, 0x8E);
	IDTSetGate(36, Isr36, 0x08, 0x8E);
	IDTSetGate(37, Isr37, 0x08, 0x8E);
	IDTSetGate(38, Isr38, 0x08, 0x8E);
	IDTSetGate(39, Isr39, 0x08, 0x8E);
	IDTSetGate(40, Isr40, 0x08, 0x8E);
	IDTSetGate(41, Isr41, 0x08, 0x8E);
	IDTSetGate(42, Isr42, 0x08, 0x8E);
	IDTSetGate(43, Isr43, 0x08, 0x8E);
	IDTSetGate(44, Isr44, 0x08, 0x8E);
	IDTSetGate(45, Isr45, 0x08, 0x8E);
	IDTSetGate(46, Isr46, 0x08, 0x8E);
	IDTSetGate(47, Isr47, 0x08, 0x8E);

	IDTr.Base = (U32)&IDT[0];
	IDTr.Size = (sizeof(struct IDTEnt) * IDT_ENTRIES) - 1;
	__asm__ volatile("lidt %0" ::"m"(IDTr));
}
