#include "asm.h"
#include "time.h"


void handle_non_sbi_mtrap() {
  if (read_mcause() == 0x8000000000000007) { // Machine Timer interrupt
    write_mtimecmp(0xFFFFFFFFFFFFFFFF);
    write_mie(read_mie() & ~0x80);
    write_mip(0x20);
  }

  return;
}