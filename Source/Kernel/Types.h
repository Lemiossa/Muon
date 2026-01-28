/**
 * Types.h
 * Created by Matheus Leme Da Silva
 */
#ifndef TYPES_H
#define TYPES_H

typedef unsigned char U8;
typedef char I8;
typedef unsigned short U16;
typedef short I16;
typedef unsigned int U32;
typedef int I32;
typedef unsigned long long U64;
typedef long long I64;

typedef unsigned long int UPTR;

#define NULL ((void *)0)

extern U8 __text_start_addr;
#define __TEXT_START_ADDR ((void *)&__text_start_addr)
extern U8 __text_end_addr;
#define __TEXT_END_ADDR ((void *)&__text_end_addr)

extern U8 __data_start_addr;
#define __DATA_START_ADDR ((void *)&__data_start_addr)
extern U8 __data_end_addr;
#define __DATA_END_ADDR ((void *)&__data_end_addr)

extern U8 __bss_start_addr;
#define __BSS_START_ADDR ((void *)&__bss_start_addr)
extern U8 __bss_end_addr;
#define __BSS_END_ADDR ((void *)&__bss_end_addr)

extern U8 __start_addr;
#define __START_ADDR ((void *)&__start_addr)
extern U8 __end_addr;
#define __END_ADDR ((void *)&__end_addr)

#define ALIGN_UP(v, a) (((v) + ((a) - 1)) & ~((a) - 1))
#define ALIGN_DOWN(v, a) ((v) & ~((a) - 1))

#endif // TYPES_H
