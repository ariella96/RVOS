#include "asm.h"
#include "kernel.h"
#include "mem.h"
#include "uart.h"
#include "user.h"

void kernel_entry() {
	write_uart("Kernel entry reached.\n");

  write_uart("Initializing heap... ");
  init_heap();
  write_uart("Heap initialized.\n");

	write_uart("Setting Supervisor Exception Program Counter to user entry...");
  write_sepc((unsigned long) user_entry);
  write_uart(" Done.\n");
  
  write_uart("Setting Supervisor Previous Privilege Mode to User-mode...");
  write_sstatus(read_sstatus() & (~(0x1800)));
  write_uart(" Done.\n");

  write_uart("Executing user entry... ");
  _sret();

	return;
}