#include "asm.h"
#include "kernel.h"
#include "uart.h"

void boot() {
	setup_uart();
	write_uart("  _______      ______   _____ \n"
						 " |  __ \\ \\    / / __ \\ / ____|\n"
						 " | |__) \\ \\  / / |  | | (___  \n"
						 " |  _  / \\ \\/ /| |  | |\\___ \\ \n"
						 " | | \\ \\  \\  / | |__| |____) |\n"
						 " |_|  \\_\\  \\/   \\____/|_____/ \n\n");

	
	write_uart("Beginning boot sequence...\n");

	write_uart("Setting Machine Trap Vector...");
  write_mtvec((unsigned long) mtrap);
  write_uart(" Done.\n");

  write_uart("Setting Machine Exception Program Counter to kernel entry...");
  write_mepc((unsigned long) kernel_entry);
  write_uart(" Done.\n");
  
  write_uart("Setting Machine Previous Privilege Mode to Supervisor-mode...");
  write_mstatus((read_mstatus() & (~(0x1800))) | (0x0800));
  write_uart(" Done.\n");

  write_uart("Executing kernel entry...\n");
  _mret();

	return;
}