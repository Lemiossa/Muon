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

struct MuonBootInfo {
	struct E820Entry *E820Table;
	U8 E820EntryCnt;
};

// The Main function don't return
void Main(struct MuonBootInfo *bootInfo) {
	GdtInit();
	SetCurrentAttr(MAKE_VGA_COLOR(WHITE, BLUE));
	Clear();

	IdtInit();
	PicRemap(0x20, 0x28);
	SerialInit(COM1, 3);

	E820Print(bootInfo->E820Table, bootInfo->E820EntryCnt);
	PmmInit(bootInfo->E820Table, bootInfo->E820EntryCnt);

	PitInit(1000);
	KbdInit();

	__asm__ volatile("sti");

	Puts("Hello Kernel!\r\n");


	for (;;) {}
}
