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

#endif // IO_H
