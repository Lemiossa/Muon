/**
 * Pic.h
 * Created by Matheus Leme Da Silva
 */
#ifndef PIC_H
#define PIC_H
#include "Types.h"
#include "Idt.h"

typedef void (*Irq)(struct IntFrame *f);
extern Irq Irqs[16];

void PICExecIrq(U8 IRQ, struct IntFrame *f);
void PICSendEoi(U8 IRQ);
void PICRemap(U32 off1, U32 off2);
void PICUnmaskIrq(U8 IRQ);
void PICMaskIrq(U8 IRQ);

#endif // PIC_H
