/**
 * PMM.c
 * Created by Matheus Leme Da Silva
 */
#include "Types.h"
#include "E820.h"
#include "Util.h"
#include "Vga.h"

#define PAGE_SIZE (4 * 1024)

U32 *PMMBitmap = NULL;
U32 PMMTotalPages = 0;
U32 PMMBitmapSize = 0;
U32 PMMLastFreePage = 0;

// Mark a page in bitmap
void PMMMarkPage(U32 page) {
	if (!PMMBitmap) return;
	U32 *ele = &PMMBitmap[page / 32];
	*ele |= (1 << (page % 32));
}

// Unmark a page in bitmap
void PMMUnmarkPage(U32 page) {
	if (!PMMBitmap) return;
	U32 *ele = &PMMBitmap[page / 32];
	*ele &= ~(1 << (page % 32));
}

// Return 1 if page is used
// -1 if have error
int PMMCheckPage(U32 page) {
	if (!PMMBitmap) return -1;
	U32 *ele = &PMMBitmap[page / 32];
	return *ele & (1 << (page % 32));
}

// Initializes Physical Memory Manager
void PMMInit(struct E820Entry *table, U8 entries) {
	for (U8 i = 0; i < entries;i++) {
		U32 start = (U32)table[i].Base;
		U32 end = start + (U32)table[i].Length;
		PMMTotalPages += (U32)(end - start) / PAGE_SIZE;
	}
	PMMBitmapSize = PMMTotalPages / 32;
	PMMBitmap = (U32 *)__BSS_END_ADDR;
	Memset(PMMBitmap, 0, PMMBitmapSize);

	// Set reserved areas
	for (U32 page = 0; page < 256; page++){
		PMMMarkPage(page);
	}

	// Kernel
	U32 kernelStartPage = ALIGN_DOWN((U32)__START_ADDR, PAGE_SIZE) / PAGE_SIZE;
	U32 kernelPages = ALIGN_UP((U32)__END_ADDR - (U32)__START_ADDR, PAGE_SIZE) / PAGE_SIZE;
	for (U32 page = kernelStartPage; page < kernelStartPage + kernelPages; page++){
		PMMMarkPage(page);
	}

	for (U8 i = 0; i < entries;i++) {
		if (table[i].Type != E820_USABLE) {
			U32 start = ALIGN_DOWN((U32)table[i].Base, PAGE_SIZE);
			U32 pages = ALIGN_UP(((U32)table[i].Base + (U32)table[i].Length) - (U32)table[i].Base, PAGE_SIZE);
			for (U32 page = start; page < start + pages; page++){
				PMMMarkPage(page);
			}
		}
	}
}

// Alloc a page
void *PMMAllocPage(void) {
	U32 page = PMMLastFreePage;

	if (page != 0) {
		PMMLastFreePage = 0;
		return (void *)(page * PAGE_SIZE);
	}

	page = 0;
	while (page < PMMTotalPages) {
		if (PMMCheckPage(page) == 0) {
			PMMMarkPage(page);
			return (void *)(page * PAGE_SIZE);
		}

		page++;

	}

	return NULL;
}

// Free a page
void PMMFreePage(void *p) {
	if (!p) return;
	U32 page = (U32)p / PAGE_SIZE;
	PMMLastFreePage = page;
	PMMUnmarkPage(page);
}

