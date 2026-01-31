/**
 * Main.c
 * Created by Matheus Leme Da Silva
 */
#include "Types.h"
#include "Vga.h"
#include "Gdt.h"
#include "Idt.h"
#include "Pic.h"
#include "E820.h"
#include "Pmm.h"
#include "Serial.h"
#include "Pit.h"
#include "Kbd.h"
#include "Io.h"

struct MuonBootInfo {
	struct E820Entry *E820Table;
	U8 E820EntryCnt;
};

// Sets PCSPK Frequency
void PcspkSetFreq(U16 freq) {
	PITSetFreq(freq, PIT2);
	U8 tmp = InU8(0x61);
	OutU8(0x61, tmp | 3);
}

// Turn of PCSPK sound
void PcspkDisable(void) {
	U8 tmp = InU8(0x61);
	OutU8(0x61, tmp & 0xFC);
}

// The Main function don't return
void Main(struct MuonBootInfo *bootInfo) {
	GDTInit();
	SetCurrentAttr(MAKE_VGA_COLOR(WHITE, BLUE));
	Clear();

	IDTInit();
	PICRemap(0x20, 0x28);
	SerialInit(COM1, 3);

	E820Print(bootInfo->E820Table, bootInfo->E820EntryCnt);
	PMMInit(bootInfo->E820Table, bootInfo->E820EntryCnt);

	PITInit(1000);
	KbdInit();

	__asm__ volatile("sti");

	Puts("Hello Kernel!\r\n");


	for (;;) {}
}
