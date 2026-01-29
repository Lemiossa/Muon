/**
 * Pit.c
 * Created by Matheus Leme Da Silva
 */
#ifndef PIT_H
#define PIT_H

#include "Types.h"
#include "Idt.h"

void PitHandler(struct IntFrame *f);
void PitInit(U16 freq);

#endif // PIT_H
