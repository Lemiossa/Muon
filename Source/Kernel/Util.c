/**
 * Util.c
 * Created by Matheus Leme Da Silva
 */
#include "Types.h"
#include "Vga.h"
#include "Util.h"

const char *PrintChars = "0123456789ABCDEF";

// Prints a hex byte
void PutHexU8(U8 b) {
	Putc(PrintChars[b >> 4]);
	Putc(PrintChars[b & 0xF]);
}

// Prints a hex word
void PutHexU16(U16 w) {
	PutHexU8(w >> 8);
	PutHexU8(w & 0xFF);
}

// Prints a hex dword
void PutHexU32(U32 dw) {
	PutHexU16(dw >> 16);
	PutHexU16(dw & 0xFFFF);
}

// Prints a hex qword
void PutHexU64(U64 qw) {
	PutHexU32(qw >> 32);
	PutHexU32(qw & 0xFFFFFFFF);
}

