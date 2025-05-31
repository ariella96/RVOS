#include "trap.h"
#include "csr.h"
#include "panic.h"

void handle_trap() {
  struct MCAUSE cause = get_mcause();
  if (cause.type == TRAP_EXCEPTION) {
    if(!(set_mepc(get_mepc() + 2))) {
      panic("Invalid return address during exception handling.\n");
    }
  }

  return;
}