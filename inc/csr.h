#ifndef CSR_H
#define CSR_H

#include <stdbool.h>

// Machine ISA CSR information
struct MISA {
  // Machine-mode integer width
  enum MACHINE_XLEN {
    BASE_INTEGER_32 = 1,  // Integer width of 32 bits
    BASE_INTEGER_64 = 2   // Integer width of 64 bits
  } mxl;
  // Implemented extensions
  enum EXTENSIONS {
    A_EXTENSION = 0x0000001,            // Atomic Instructions extension
    B_EXTENSION = 0x0000002,            // Bit Manipulation (Zba/Zbb/Zbs)
                                        // extensions
    C_EXTENSION = 0x0000004,            // Compressed Instructions extension
    D_EXTENSION = 0x0000008,            // Double-Precision Floating-Point
                                        // extension
    EMBEDDED_BASE_ISA = 0x0000010,      // Embedded base instruction set
                                        // (RV32E, RV64E)
    F_EXTENSION = 0x0000020,            // Single-Precision Floating Point
                                        // extension
    H_EXTENSION = 0x0000080,            // Hypervisor Support extension
    INTEGER_BASE_ISA = 0x0000100,       // Integer base instruction set
                                        // (RV32I, RV64I)
    M_EXTENSION = 0x0001000,            // Integer Multiplication and Division
                                        // extension
    Q_EXTENSION = 0x0010000,            // Quad-Precision Floating-Point
                                        // extension
    S_MODE_IMPLEMENTED = 0x0040000,     // Supervisor-mode implemented
    U_MODE_IMPLEMENTED = 0x0100000,     // User-mode implemented
    V_EXTENSION = 0x0200000,            // Vector Operations extension
    NON_STANDARD_EXTENSIONS = 0x0800000 // Non-standard extensions
  } extensions;
};

// Machine Status CSR information
struct MSTATUS {
  bool supervisor_interrupt_enable;           // S-mode interrupt enable
  bool machine_interrupt_enable;              // M-mode interrupt enable
  bool supervisor_prior_interrupt_enable;     // S-mode prior interrupt enable
  bool user_big_endian;                       // U-mode memory access endianness
  bool machine_prior_interrupt_enable;        // M-mode prior interrupt enable
  // S-mode previous privilege mode
  enum SUPERVISOR_PREVIOUS_PRIVILEGE_MODE {
    SPP_USER = 0,       // S-mode previous U-mode
    SPP_SUPERVISOR = 1  // S-mode previous S-mode
  } supervisor_previous_privilege_mode;
  // Vector extension state
  enum VECTOR_EXTENSION_STATE {
    VS_OFF = 0,     // Vector extension not implemented
    VS_INITIAL = 1, // Vector extension in initial state
    VS_CLEAN = 2,   // Vector extension in clean state
    VS_DIRTY = 3    // Vector extension in dirty state
  } vector_extension_state;
  // M-mode previous privilege mode
  enum MACHINE_PREVIOUS_PRIVILEGE_MODE {
    MPP_USER = 0,       // M-mode previous User-mode
    MPP_SUPERVISOR = 1, // M-mode previous Supervisor-mode
    MPP_MACHINE = 3     // M-mode previous Machine-mode
  } machine_previous_privilege_mode;
  // Floating point unit state
  enum FLOATING_POINT_UNIT_STATE {
    FS_OFF = 0,     // Floating point unit not implemented
    FS_INITIAL = 1, // Floating point unit in initial state
    FS_CLEAN = 2,   // Floating point unit in clean state
    FS_DIRTY = 3    // Floating point unit in dirty state
  } floating_point_unit_state;
  // U-mode extensions state
  enum USER_MODE_EXTENSIONS_STATE {
    ALL_OFF = 0,                      // U-mode extensions not implemented
    NONE_DIRTY_OR_CLEAN_SOME_ON = 1,  // All U-mode extensions in initial state
    NONE_DIRTY_SOME_CLEAN = 2,        // No U-mode extensions in dirty state,
                                      // some in clean state
    SOME_DIRTY = 3                    // Some U-mode extensions in dirty state
  } user_mode_extensions_state;
  bool modify_privilege;                      // Effective privilege mode
  bool permit_supervisor_user_memory_access;  // Permit S-mode access to U-mode
                                              // virtual memory
  bool make_executable_readable;              // Make executable virtual memory
                                              // readable
  bool trap_virtual_memory;                   // Trap S-mode virtual memory
                                              // operations
  bool timeout_wait;                          // Trap Wait for Interrupt
                                              // instruction in S- and U-mode
                                              // after time limit
  bool trap_sret;                             // Trap S-mode exception return
                                              // instruction
  // S-mode previous expected landing pad
  enum SUPERVISOR_PREVIOUS_EXPECTED_LANDING_PAD {
    SPELP_NO_LP_EXPECTED = 0, // No S-mode previous landing pad instruction
                              // expected
    SPELP_LP_EXPECTED = 1     // S-mode previous landing pad instruction
                              // expected
  } supervisor_previous_expected_landing_pad;
  bool supervisor_disable_trap;               // Disable traps to S-mode
  // U-mode integer width
  enum USER_XLEN {
    UXL_BASE_INTEGER_32 = 1,  // U-mode integer width of 32-bits
    UXL_BASE_INTEGER_64 = 2   // U-mode integer width of 64-bits
  } user_xlen;
  // S-mode integer width
  enum SUPERVISOR_XLEN {
    SXL_BASE_INTEGER_32 = 1,  // S-mode integer width of 32-bits
    SXL_BASE_INTEGER_64 = 2   // S-mode integer width of 64-bits
  } supervisor_xlen;
  bool supervisor_big_endian;                 // S-mode memory access endianness
  bool machine_big_endian;                    // M-mode memory access endianness
  bool guest_virtual_address;                 // Guest virtual address written
                                              // to stval, for traps taken to
                                              // H-mode
  bool machine_previous_virtualization_mode;  // M-mode previous virtualization
                                              // mode
  // M-mode previous expected landing pad
  enum MACHINE_PREVIOUS_EXPECTED_LANDING_PAD {
    MPELP_NO_LP_EXPECTED = 0, // No M-mode previous landing pad instruction
                              // expected
    MPELP_LP_EXPECTED = 1     // M-mode previous landing pad instruction
                              // expected
  } machine_previous_expected_landing_pad;
  bool machine_disable_trap;                  // Disable traps to M-mode
  bool some_dirty;                            // Vector extension, floating
                                              // point unit, or U-mode
                                              // extensions dirty
};

// Machine Trap Vector CSR information
struct MTVEC {
  unsigned long base; // Base address of trap vector
  // Vector mode
  enum MODE {
    DIRECT = 0,   // Direct mode
    VECTORED = 1  // Vectored mode
  } mode;
};

// Machine Trap Vector CSR write error
enum SET_MTVEC_ERROR {
  SET_MTVEC_SUCCESS = 0,        // Machine Trap Vector write successful
  BASE_ADDRESS_MISALIGNED = 1,  // Machine Trap Vector base address misaligned
  SET_MTVEC_OTHER_ERROR = 2     // Machine Trap Vector write other error
};

// Machine Interrupt Enable CSR information
enum MIE {
  SUPERVISOR_SOFTWARE_INTERRUPT_ENABLE = 0x0002,    // S-mode software
                                                    // interrupts
  MACHINE_SOFTWARE_INTERRUPT_ENABLE = 0x0008,       // M-mode software
                                                    // interrupts
  SUPERVISOR_TIMER_INTERRUPT_ENABLE = 0x0020,       // S-mode timer interrupts
  MACHINE_TIMER_INTERRUPT_ENABLE = 0x0080,          // M-mode timer interrupts
  SUPERVISOR_EXTERNAL_INTERRUPT_ENABLE = 0x0200,    // S-mode external
                                                    // interrupts
  MACHINE_EXTERNAL_INTERRUPT_ENABLE = 0x0800,       // M-mode external
                                                    // interrupts
  LOCAL_COUNTER_OVERFLOW_INTERRUPT_ENABLE = 0x2000  // Local counter overflow
                                                    // interrupts
};

// Machine Interrupt Enable CSR write error
enum SET_MIE_ERROR {
  SET_MIE_SUCCESS = 0x00,         // Machine Interrupt Enable write success
  S_MODE_NOT_IMPLEMENTED = 0x01,  // S-mode not implemented
  SSIE_READ_ONLY = 0x02,          // S-mode software interrupt enable read-only
  MSIE_READ_ONLY = 0x04,          // M-mode software interrupt enable read-only
  STIE_READ_ONLY = 0x08,          // S-mode timer interrupt enable read-only
  MTIE_READ_ONLY = 0x10,          // M-mode timer interrupt enable read-only
  SEIE_READ_ONLY = 0x20,          // S-mode external interrupt enable read-only
  MEIE_READ_ONLY = 0x40,          // M-mode external interrupt enable read-only
  LCOFIE_READ_ONLY = 0x80         // Local counter overflow interrupt enable
                                  // read-only
};

// Machine Cause CSR information
struct MCAUSE {
  // Type of trap to M-mode
  enum TYPE {
    TRAP_EXCEPTION = 0, // Exception
    TRAP_INTERRUPT = 1  // Interrupt
  } type;
  // Cause of trap to M-mode
  union CAUSE {
    // Cause of exception
    enum EXCEPTION_CAUSE {
      INSTRUCTION_ADDRESS_MISALIGNED = 0, // Control-flow target address
                                          // misaligned
      INSTRUCTION_ACCESS_FAULT = 1,       // Instruction access fault
      ILLEGAL_INSTRUCTION = 2,            // Illegal instruction
      BREAKPOINT = 3,                     // Breakpoint
      LOAD_ADDRESS_MISALIGNED = 4,        // Load address misaligned
      LOAD_ACCESS_FAULT = 5,              // Load access fault
      STORE_AMO_ADDRESS_MISALIGNED = 6,   // Store/AMO address misaligned
      STORE_AMO_ACCESS_FAULT = 7,         // Store/AMO access fault
      ENVIRONMENT_CALL_FROM_U_MODE = 8,   // Environment call from U-mode
      ENVIRONMENT_CALL_FROM_S_MODE = 9,   // Environment call from S-mode
      ENVIRONMENT_CALL_FROM_M_MODE = 11,  // Environment call from M-mode
      INSTRUCTION_PAGE_FAULT = 12,        // Instruction page fault
      LOAD_PAGE_FAULT = 13,               // Load page fault
      STORE_AMO_PAGE_FAULT = 15,          // Store/AMO page fault
      DOUBLE_TRAP = 16,                   // Double trap
      SOFTWARE_CHECK = 18,                // Software check
      HARDWARE_ERROR = 19                 // Hardware error
    } exception_cause;
    // Cause of interrupt
    enum INTERRUPT_CAUSE {
      SUPERVISOR_SOFTWARE_INTERRUPT = 1,  // S-mode software interrupt
      MACHINE_SOFTWARE_INTERRUPT = 3,     // M-mode software interrupt
      SUPERVISOR_TIMER_INTERRUPT = 5,     // S-mode timer interrupt
      MACHINE_TIMER_INTERRUPT = 7,        // M-mode timer interrupt
      SUPERVISOR_EXTERNAL_INTERRUPT = 9,  // S-mode external interrupt
      MACHINE_EXTERNAL_INTERRUPT = 11,    // M-mode external interrupt
      COUNTER_OVERFLOW_INTERRUPT = 13     // Counter overflow interrupt
    } interrupt_cause;
  } cause;
};

// Get Machine ISA CSR information
struct MISA get_misa();

// Get Machine Status CSR information
struct MSTATUS get_mstatus();

// Get Machine Trap Vector CSR information
struct MTVEC get_mtvec();

// Set Machine Trap Vector CSR information
enum SET_MTVEC_ERROR set_mtvec(struct MTVEC mtvec);

// Get Machine Interrupt Enable CSR information
enum MIE get_mie();

// Set Machine Interrupt Enable CSR information
enum SET_MIE_ERROR set_mie(enum MIE mie);

// Get Machine Exception Program Counter CSR information
unsigned long get_mepc();

// Set Machine Exception Program Counter CSR information,
// returns false on invalid address
bool set_mepc(unsigned long address);

// Get Machine Cause CSR information
struct MCAUSE get_mcause();

#endif