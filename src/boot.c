#include "uart.h"

extern unsigned long read_mstatus();
extern void write_mstatus(unsigned long val);
extern void _mret();

void boot() {
  setup_uart();
  write_uart("  _______      ______   _____ \n"
             " |  __ \\ \\    / / __ \\ / ____|\n"
             " | |__) \\ \\  / / |  | | (___  \n"
             " |  _  / \\ \\/ /| |  | |\\___ \\ \n"
             " | | \\ \\  \\  / | |__| |____) |\n"
             " |_|  \\_\\  \\/   \\____/|_____/ \n\n");
  
  write_uart("Beginning boot sequence...\n");
  
  write_uart("Setting Machine Previous Privilege Mode to S-mode...");
  unsigned long mstatus = read_mstatus();
  mstatus &= ~(0x1800);
  mstatus |= (0x800);
  write_mstatus(mstatus);
  write_uart(" Done.\n");

  write_uart("Executing kernel...\n");
  _mret();

  return;
}