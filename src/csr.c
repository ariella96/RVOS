#include "csr.h"

extern unsigned long read_misa();
extern unsigned long read_mstatus();
extern unsigned long read_mepc();
extern void write_mepc(unsigned long value);
extern unsigned long read_mcause();

struct MISA get_misa() {
  struct MISA misa;
  unsigned long csr_misa = read_misa();
  misa.mxl = csr_misa >> 62;
  misa.extensions = (csr_misa << 38) >> 38;
  return misa;
}

struct MSTATUS get_mstatus() {
  struct MSTATUS mstatus;
  unsigned long csr_mstatus = read_mstatus();
  mstatus.supervisor_interrupt_enable = (csr_mstatus << 62) >> 63;
  mstatus.machine_interrupt_enable = (csr_mstatus << 60) >> 63;
  mstatus.supervisor_prior_interrupt_enable = (csr_mstatus << 58) >> 63;
  mstatus.user_big_endian = (csr_mstatus << 57) >> 63;
  mstatus.machine_prior_interrupt_enable = (csr_mstatus << 56) >> 63;
  mstatus.supervisor_previous_privilege_mode = (csr_mstatus << 55) >> 63;
  mstatus.vector_extension_state = (csr_mstatus << 53) >> 62;
  mstatus.machine_previous_privilege_mode = (csr_mstatus << 51) >> 62;
  mstatus.floating_point_unit_state = (csr_mstatus << 49) >> 62;
  mstatus.user_mode_extensions_state = (csr_mstatus << 47) >> 62;
  mstatus.modify_privilege = (csr_mstatus << 46) >> 63;
  mstatus.permit_supervisor_user_memory_access = (csr_mstatus << 45) >> 63;
  mstatus.make_executable_readable = (csr_mstatus << 44) >> 63;
  mstatus.trap_virtual_memory = (csr_mstatus << 43) >> 63;
  mstatus.timeout_wait = (csr_mstatus << 42) >> 63;
  mstatus.trap_sret = (csr_mstatus << 41) >> 63;
  mstatus.supervisor_previous_expected_landing_pad = (csr_mstatus << 40) >> 63;
  mstatus.supervisor_disable_trap = (csr_mstatus << 39) >> 63;
  mstatus.user_xlen = (csr_mstatus << 30) >> 62;
  mstatus.supervisor_xlen = (csr_mstatus << 28) >> 62;
  mstatus.supervisor_big_endian = (csr_mstatus << 27) >> 63;
  mstatus.machine_big_endian = (csr_mstatus << 26) >> 63;
  mstatus.guest_virtual_address = (csr_mstatus << 25) >> 63;
  mstatus.machine_previous_virtualization_mode = (csr_mstatus << 24) >> 63;
  mstatus.machine_previous_expected_landing_pad = (csr_mstatus << 22) >> 63;
  mstatus.machine_disable_trap = (csr_mstatus << 21) >> 63;
  mstatus.some_dirty = csr_mstatus >> 63;
  return mstatus;
}

unsigned long get_mepc() {
  return read_mepc();
}

bool set_mepc(unsigned long address) {
  if ((address & 0x1)
      || ((get_misa().mxl == BASE_INTEGER_32) && (address & 0x2))) {
    return false;
  }
  write_mepc(address);
  return true;
}

struct MCAUSE get_mcause() {
  struct MCAUSE mcause;
  unsigned long csr_mcause = read_mcause();
  unsigned long trap_type = csr_mcause >> 63;
  unsigned long trap_cause = (csr_mcause << 1) >> 1;
  mcause.type = trap_type;
  if (trap_type == TRAP_EXCEPTION) {
    mcause.cause.exception_cause = trap_cause;
  } else {
    mcause.cause.interrupt_cause = trap_cause;
  }
  return mcause;
}