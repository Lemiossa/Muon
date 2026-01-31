/**
 * Gdt.h
 * Created by Matheus Leme Da Silva
 */
#ifndef GDT_H
#define GDT_H
#include "Types.h"

struct GDTr {
	U16 Size;
	U32 Base;
} __attribute__((packed));

struct GDTEnt {
	U16 LimitLo;
	U16 BaseLo;
	U8 BaseMi;
	U8 Access;
	U8 Flags;
	U8 BaseHi;
} __attribute__((packed));

#define GDT_ENTRIES 3
extern struct GDTEnt GDT[GDT_ENTRIES];
extern struct GDTr GDTr;

void GDTSetEnt(U16 ent, U32 limit, U32 base, U8 access, U8 flags);
void GDTInit(void);

#endif // GDT_H
