/**
 * Serial.c
 * Created by Matheus Leme Da Silva
 */
#include "Types.h"
#include "Io.h"

// Initialzies a SERIAL PORT
// Returns non zero if have error
int SerialInit(U16 port, U16 divisor) {
	OutU8(port + 1, 0); // Interrupts disabled
	OutU8(port + 3, 0x80); // Bit DLAB
	OutU8(port + 0, divisor & 0xFF); // LSB
	OutU8(port + 1, (divisor >> 8) & 0xFF); // MSB
	OutU8(port + 3, 0x03); // 8-bit data, 1 stop bit
	OutU8(port + 2, 0xC7); // FIFO, clear TX and RX
	OutU8(port + 4, 0x10);

	// Test
	OutU8(port + 0, 0xAE);
	if (InU8(port + 0) != 0xAE) {
		return -1;
	}

	OutU8(port + 4, 0x0F);

	return 0;
}

// Write a byte in serial port
void SerialWrite(U16 port, U8 byte) {
	while (!(InU8(port + 5) & 0x20))
		__asm__ volatile ("hlt");

	OutU8(port + 0, byte);
}

