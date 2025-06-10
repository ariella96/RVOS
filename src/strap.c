#include "asm.h"
#include "sbi.h"

void handle_strap() {
  if (read_scause() == 0x8000000000000005 ) { // Supervisor Timer Interrupt
    call_sbi(0x54494D45 , 0, 0xFFFFFFFFFFFFFFFF);
  }
}