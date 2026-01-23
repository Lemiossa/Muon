/**
 * Util.h
 * Created by Matheus Leme Da Silva
 */
#ifndef UTIL_H
#define UTIL_H
#include "Types.h"

void Memcpy(void *d, const void *s, U32 n);
void Memset(void *d, U8 b, U32 n);
void PutHexU8(U8 b);
void PutHexU16(U16 w);
void PutHexU32(U32 dw);

#endif // UTIL_H
