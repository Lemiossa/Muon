/**
 * Util.c
 * Created by Matheus Leme Da Silva
 */
#include "Util.h"
#include "Types.h"
#include "Vga.h"

const char *HexChars = "0123456789ABCDEF";

// Copy N bytes from S to D
void Memcpy(void *d, const void *s, U32 n) {
  if (n == 0 || !d || !s)
    return;

  U8 *dest = (U8 *)d;
  U8 *src = (U8 *)s;
  for (U32 i = 0; i < n; i++) {
    dest[i] = src[i];
  }
}

// Set N bytes of D with B
void Memset(void *d, U8 b, U32 n) {
  if (n == 0 || !d)
    return;

  U8 *dest = (U8 *)d;
  for (U32 i = 0; i < n; i++) {
    dest[i] = b;
  }
}

// Prints a hex byte
void PutHexU8(U8 b) {
  Putc(HexChars[b >> 4]);
  Putc(HexChars[b & 0xF]);
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
