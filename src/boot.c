#include "uart.h"

void boot() {
	setup_uart();
	write_uart("Hello, world!\n");

	return;
}