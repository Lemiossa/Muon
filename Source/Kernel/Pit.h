/**
 * Pit.c
 * Created by Matheus Leme Da Silva
 */
#ifndef PIT_H
#define PIT_H

#include "Types.h"
#include "Idt.h"

#define PITBASEFREQ 1193182

#define PIT0 0
#define PIT1 1 // Deprecated
#define PIT2 2

void PITHandler(struct IntFrame *f);
void PITSetFreq(U16 freq, U8 PIT);
void PITInit(U16 freq);
U64 PITGetTicks(void);

#endif // PIT_H
