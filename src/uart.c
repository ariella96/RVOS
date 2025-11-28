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

	*UART_FCR = 0x00; // Disable the FIFOs

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
	char s = string[0];

	// If the string is empty, return
	if (!s) {
		return;
	}

	// Wait for the THR to clear
	while (!(*UART_LSR & 0x20)) {
		continue;
	}

	// Write the character to the THR
	*UART_THR = s;

	return write_uart(++string);
}