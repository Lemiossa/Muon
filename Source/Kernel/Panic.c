/**
 * Panic.c
 * Created by Matheus Leme Da Silva
 */
#include "Vga.h"

// Print panic message and halt the system
void Panic(const char *message) {
	SetCurrentAttr(MAKE_VGA_COLOR(WHITE, RED));
	Puts("!!! PANIC !!!\r\n");

	Puts("Message: ");
	Puts(message);
	Puts("\r\nSystem halted\r\n");
	__asm__ volatile("cli;hlt");
}
