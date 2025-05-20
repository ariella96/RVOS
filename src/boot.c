#include "uart.h"
#include "csr.h"

char* rvos = "  _______      ______   _____ \n |  __ \\ \\    / / __ \\ / ____|\n | |__) \\ \\  / / |  | | (___  \n |  _  / \\ \\/ /| |  | |\\___ \\ \n | | \\ \\  \\  / | |__| |____) |\n |_|  \\_\\  \\/   \\____/|_____/ \n\n";

char* base_isa = "Base ISA: rv";

void boot() {
  setup_uart();
  write_uart(rvos);

  write_uart(base_isa);
  struct MISA misa = get_misa();
  if (misa.mxl == BASE_INTEGER_32) {
    write_uart("32");
  } else {
    write_uart("64");
  }
  if (misa.extensions & INTEGER_BASE_ISA) {
    write_uart("i\n");
  } else {
    write_uart("e\n");
  }

  return;
}