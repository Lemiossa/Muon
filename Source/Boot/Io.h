/**
 * Io.h
 * Created by Matheus Leme Da Silva
 */
#ifndef IO_H
#define IO_H
#include "Types.h"

static inline void OutU8(U16 p, U8 b) {
	__asm__ volatile("outb %b0, %w1" ::"a"(b), "Nd"(p) : "memory");
}

static inline U8 InU8(U16 port) {
	U8 ret;
	__asm__ volatile("inb %w1, %b0" : "=a"(ret) : "Nd"(port));
	return ret;
}

static inline void OutU16(U16 p, U16 b) {
	__asm__ volatile("outw %w0, %w1" ::"a"(b), "Nd"(p) : "memory");
}

static inline U16 InU16(U16 port) {
	U16 ret;
	__asm__ volatile("inw %w1, %w0" : "=a"(ret) : "Nd"(port));
	return ret;
}

static inline void IoWait(void) { OutU8(0x80, 0); }

#endif // IO_H
