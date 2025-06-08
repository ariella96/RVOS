#include "kernel.h"
#include "uart.h"

void kernel_entry() {
  write_uart("Kernel entry reached.\n");

  while (1) {}

  return;
}