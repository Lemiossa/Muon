/**
 * E820.c
 * Created by Matheus Leme Da Silva
 */
#include "Types.h"
#include "E820.h"
#include "Vga.h"
#include "Util.h"

const char *E820TypeStrings[] = {
    "Unknown",
    "Usable RAM",
    "Reserved",
    "ACPI Rclmb",
    "ACPI NVS",
    "Bad Memory"
};

// Gets E820 type string
static inline const char *E820GetTypeString(U32 type) {
    if (type > E820_TYPE_MAX)
        return "Unknown/Reserved";
    return E820TypeStrings[type];
}

// Prints E820
void E820Print(struct E820Entry *table, U8 entries) {
	for (U8 i = 0; i < entries; i++) {
		Puts("E820: Base: 0x");
		PutHexU64(table[i].Base);
		Puts(" Length: 0x");
		PutHexU64(table[i].Length);
		Puts(" Type: ");
		Puts(E820GetTypeString(table[i].Type));
		Puts("\r\n");
	}
}

