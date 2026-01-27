/**
 * Main.c
 * Created by Matheus Leme Da Silva
 */
#include "Vga.h"
#include "Gdt.h"
#include "Idt.h"
#include "Pic.h"
#include "E820.h"
#include "Pmm.h"

struct QuarkBootInfo {
	struct E820Entry *E820Table;
	U8 E820EntryCnt;
};

// The Main function don't return
void Main(struct QuarkBootInfo *bootInfo) {
	SetCurrentAttr(MAKE_VGA_COLOR(WHITE, BLUE));
	Clear();
	GdtInit();
	IdtInit();
	PicRemap(0x20, 0x28);

	E820Print(bootInfo->E820Table, bootInfo->E820EntryCnt);
	PmmInit(bootInfo->E820Table, bootInfo->E820EntryCnt);

	__asm__ volatile("sti");
	Puts("Hello Kernel!\r\n");

	for (;;);
}
