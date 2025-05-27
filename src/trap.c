#include "trap.h"
#include "csr.h"

void handle_trap() {
  struct MCAUSE cause = get_mcause();
  if (cause.type == TRAP_EXCEPTION) {
    set_mepc(get_mepc() + 2); // Go to next instruction after exception
  }

  return;
}