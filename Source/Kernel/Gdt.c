/**
 * Gdt.c
 * Created by Matheus Leme Da Silva
 */
#include "Gdt.h"
#include "Types.h"

struct GDTEnt GDT[GDT_ENTRIES];
struct GDTr GDTr;

// Set a GDT entry
void GDTSetEnt(U16 ent, U32 limit, U32 base, U8 access, U8 flags) {
	if (ent >= GDT_ENTRIES)
		return;

	limit = limit & 0xFFFFF;

	GDT[ent].LimitLo = limit & 0xFFFF;
	GDT[ent].BaseLo = base & 0xFFFF;
	GDT[ent].BaseMi = (base >> 16) & 0xFF;
	GDT[ent].Access = access;
	GDT[ent].Flags = ((flags & 0xF) << 4) | ((limit >> 16) & 0xF);
	GDT[ent].BaseHi = (base >> 24) & 0xFF;
}

// Initializes GDT
void GDTInit(void) {
	GDTSetEnt(0, 0, 0, 0, 0);
	GDTSetEnt(1, 0xFFFFF, 0, 0x9A, 0xC);
	GDTSetEnt(2, 0xFFFFF, 0, 0x92, 0xC);

	GDTr.Size = (sizeof(struct GDTEnt) * GDT_ENTRIES) - 1;
	GDTr.Base = (U32)&GDT[0];
	__asm__ volatile("lgdt %0" ::"m"(GDTr));
	__asm__ volatile("ljmp $0x08,$flush;flush:"
					 "movw $0x10, %%ax;"
					 "movw %%ax, %%ds;"
					 "movw %%ax, %%es;"
					 "movw %%ax, %%fs;"
					 "movw %%ax, %%gs;"
					 "movw %%ax, %%ss;" ::
						 : "memory", "ax");
}
