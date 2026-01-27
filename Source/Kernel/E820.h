/**
 * E820.h
 * Created by Matheus Leme Da Silva
 */
#ifndef E820_H
#define E820_H
#include "Types.h"

#define E820_USABLE         1
#define E820_RESERVED       2
#define E820_ACPI_RECLAIMABLE 3
#define E820_ACPI_NVS       4
#define E820_BAD_MEMORY     5

#define E820_TYPE_MAX 5

struct E820Entry {
	U64 Base;
	U64 Length;
	U32 Type;
	U32 Attr;
} __attribute__((packed));

void E820Print(struct E820Entry *table, U8 entries);

#endif // E820_H
