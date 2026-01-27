/**
 * Pmm.c
 * Created by Matheus Leme Da Silva
 */
#include "Types.h"
#include "E820.h"
#include "Util.h"
#include "Vga.h"

#define PAGE_SIZE (4 * 1024)

UPTR StackTop = 0;

// Pushes a page addr in stack
void Push(UPTR addr) {

}

// Initializes Physical Memory Manager
void PmmInit(struct E820Entry *table, U8 entries) {
	U32 usablePages = 0;
	for (U8 i = 0; i < entries;i++) {
		if (table[i].Base >= 0x100000 && table[i].Type == E820_USABLE) {
			UPTR end = (UPTR)table[i].Base + table[i].Length;
			usablePages += (UPTR)(end - table[i].Base) / PAGE_SIZE;
		}
	}
	U32 stackSize = usablePages * sizeof(UPTR);
	StackTop = (UPTR)__BSS_END_ADDR + stackSize;

	Puts("Usable pages: 0x");
	PutHexU32(usablePages);
	Puts("\r\nStack top: 0x");
	PutHexU32(StackTop);
	Puts("\r\n");
}
