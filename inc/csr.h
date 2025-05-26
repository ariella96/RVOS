#ifndef CSR_H
#define CSR_H

#include <stdbool.h>

// Machine ISA CSR information
struct MISA {
  // Machine-mode integer width
  enum MACHINE_XLEN {
    BASE_INTEGER_32 = 1, // Integer width of 32 bits
    BASE_INTEGER_64 = 2 // Integer width of 64 bits
  } mxl;
  // Implemented extensions
  enum EXTENSIONS {
    A_EXTENSION = 0x0000001, // Atomic Instructions extension
    B_EXTENSION = 0x0000002, // Bit Manipulation (Zba/Zbb/Zbs) extensions
    C_EXTENSION = 0x0000004, // Compressed Instructions extension
    D_EXTENSION = 0x0000008, // Double-Precision Floating-Point extension
    EMBEDDED_BASE_ISA = 0x0000010, // Embedded base instruction set
                                   // (RV32E, RV64E)
    F_EXTENSION = 0x0000020, // Single-Precision Floating Point extension
    H_EXTENSION = 0x0000080, // Hypervisor Support extension
    INTEGER_BASE_ISA = 0x0000100, // Integer base instruction set (RV32I, RV64I)
    M_EXTENSION = 0x0001000, // Integer Multiplication and Division extension
    Q_EXTENSION = 0x0010000, // Quad-Precision Floating-Point extension
    S_MODE_IMPLEMENTED = 0x0040000, // Supervisor-mode implemented
    U_MODE_IMPLEMENTED = 0x0100000, // User-mode implemented
    V_EXTENSION = 0x0200000, // Vector Operations extension
    NON_STANDARD_EXTENSIONS = 0x0800000 // Non-standard extensions
  } extensions;
};

struct MSTATUS {
  bool supervisor_interrupt_enable; // Supervisor-mode interrupt enable
  bool machine_interrupt_enable; // Machine-mode interrupt enable
  bool supervisor_prior_interrupt_enable; // Supervisor-mode prior interrupt
                                          // enable
  bool user_big_endian; // User-mode memory access endianness
  bool machine_prior_interrupt_enable; // Machine-mode prior interrupt enable
  // Supervisor-mode previous privilege mode
  enum SUPERVISOR_PREVIOUS_PRIVILEGE_MODE {
    SPP_USER = 0, // Supervisor-mode previous User-mode
    SPP_SUPERVISOR = 1 // Supervisor-mode previous Supervisor-mode
  } supervisor_previous_privilege_mode;
  // Vector extension state
  enum VECTOR_EXTENSION_STATE {
    VS_OFF = 0, // Vector extension not implemented
    VS_INITIAL = 1, // Vector extension in initial state
    VS_CLEAN = 2, // Vector extension in clean state since last context save
    VS_DIRTY = 3 // Vector extension in dirty state since last context save
  } vector_extension_state;
  // Machine-mode previous privilege mode
  enum MACHINE_PREVIOUS_PRIVILEGE_MODE {
    MPP_USER = 0,
    MPP_SUPERVISOR = 1,
    MPP_MACHINE = 3
  } machine_previous_privilege_mode;
  // Floating point unit state
  enum FLOATING_POINT_UNIT_STATE {
    FS_OFF = 0, // Floating point unit not implemented
    FS_INITIAL = 1, // Floating point unit in initial state
    FS_CLEAN = 2, // Floating point unit in clean state since last context save
    FS_DIRTY = 3 // Floating point unit in dirty state since last context save
  } floating_point_unit_state;
  // User-mode extensions state
  enum USER_MODE_EXTENSIONS_STATE {
    ALL_OFF = 0, // User-mode extensions not implemented
    NONE_DIRTY_OR_CLEAN_SOME_ON = 1, // All User-mode extensions in initial
                                     // state
    NONE_DIRTY_SOME_CLEAN = 2, // No User-mode extensions in dirty state since
                               // last context save, some in clean state since
                               // last context save
    SOME_DIRTY = 3 // Some User-mode extensions in dirty state since last
                   // save
  } user_mode_extensions_state;
  bool modify_privilege; // Effective privilege mode
  bool permit_supervisor_user_memory_access; // Permit Supervisor-mode access
                                             // to User-mode virtual memory
  bool make_executable_readable; // Make executable virtual memory readable
  bool trap_virtual_memory; // Trap Supervisor-mode virtual memory operations
  bool timeout_wait; // Trap Wait for Interrupt instruction in
                     // Supervisor- and User-mode after time limit
  bool trap_sret; // Trap Supervisor-mode exception return instruction
  // Supervisor-mode previous expected landing pad
  enum SUPERVISOR_PREVIOUS_EXPECTED_LANDING_PAD {
    SPELP_NO_LP_EXPECTED = 0, // No Supervisor-mode previous landing pad
                              // instruction expected
    SPELP_LP_EXPECTED = 1 // Supervisor-mode previous landing pad instruction
                          // expected
  } supervisor_previous_expected_landing_pad;
  bool supervisor_disable_trap; // Disable traps to Supervisor-mode
  // User-mode integer width
  enum USER_XLEN {
    UXL_BASE_INTEGER_32 = 1, // User-mode integer width of 32-bits
    UXL_BASE_INTEGER_64 = 2 // User-mode integer width of 64-bits
  } user_xlen;
  // Supervisor-mode integer width
  enum SUPERVISOR_XLEN {
    SXL_BASE_INTEGER_32 = 1, // Supervisor-mode integer width of 32-bits
    SXL_BASE_INTEGER_64 = 2 // Supervisor-mode integer width of 64-bits
  } supervisor_xlen;
  bool supervisor_big_endian; // Supervisor-mode memory access endianness
  bool machine_big_endian; // Machine-mode memory access endianness
  bool guest_virtual_address; // Guest virtual address written to stval, for
                              // traps taken to Hypervisor-mode
  bool machine_previous_virtualization_mode; // Machine-mode previous
                                             // virtualization mode
  // Machine-mode previous expected landing pad
  enum MACHINE_PREVIOUS_EXPECTED_LANDING_PAD {
    MPELP_NO_LP_EXPECTED = 0, // No Machine-mode previous landing pad
                              // instruction expected
    MPELP_LP_EXPECTED = 1 // Machine-mode previous landing pad instruction
                          // expected
  } machine_previous_expected_landing_pad;
  bool machine_disable_trap; // Disable traps to Machine-mode
  bool some_dirty; // Vector extension, floating point unit, or User-mode
                   // extensions dirty
};

// Get Machine ISA CSR information
struct MISA get_misa();

// Get Machine Status CSR information
struct MSTATUS get_mstatus();

#endif