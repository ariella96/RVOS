#include "uart.h"
#include "user.h"

void user_entry() {
	write_uart("User entry reached.");

	return;
}