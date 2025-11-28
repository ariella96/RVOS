#include "uart.h"

volatile unsigned char* UART_THR   = (volatile unsigned char*) 0x10000000;
volatile unsigned char* UART_IER   = (volatile unsigned char*) 0x10000001;
volatile unsigned char* UART_FCR   = (volatile unsigned char*) 0x10000002;
volatile unsigned char* UART_LCR   = (volatile unsigned char*) 0x10000003;
volatile unsigned char* UART_LSR   = (volatile unsigned char*) 0x10000005;
volatile unsigned char* UART_DL_LS = (volatile unsigned char*) 0x10000000;
volatile unsigned char* UART_DL_MS = (volatile unsigned char*) 0x10000001;

void setup_uart() {
	*UART_IER = 0x00; // Disable all interrupts

	*UART_FCR = 0x05; // Enable the FIFOs, reset the transmitter's FIFO

	// Set the baud rate to maximum
	*UART_LCR = 0x80; // Enable DLAB
	*UART_DL_LS = 0x01;
	*UART_DL_MS = 0x00;

	// Setup LCR
	*UART_LCR = 0x03; // 8-bit characters, one stop bit, no parity check;
										// disable DLAB

	return;
}

void write_uart(char* string) {
	// If the string is empty, return
	if (!(string[0])) {
		return;
	}

	// Wait for the FIFO to clear
	while (!(*UART_LSR & 0x20)) {
		continue;
	}

	// Write up to 16 characters to FIFOs
	for (int count = 0; count < 16; count++) {
		*UART_THR = string[0];
		string++;

		// If the next character is null, return
		if(!(string[0])) {
			return;
		}
	}

	return write_uart(string);
}