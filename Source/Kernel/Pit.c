/**
 * Pit.c
 * Created by Matheus Leme Da Silva
 */
#include "Idt.h"
#include "Pic.h"
#include "Io.h"
#include "Pit.h"

#define PITBASEFREQ 1193182

U64 Ticks = 0;

void PitHandler(struct IntFrame *f) {
	(void)f;
	Ticks++;
}

void PitInit(U16 freq) {
	if (freq == 0) return;
	U16 divisor = PITBASEFREQ/freq;
	OutU8(0x43, 0b00110100);
	OutU8(0x40, divisor & 0xFF); // Low byte
	OutU8(0x40, (divisor >> 8) & 0xFF); // High byte
	PicUnmaskIrq(0);
	Irqs[0] = PitHandler;
}

