#include <assert.h>
#include "csr.h"
#include "panic.h"
#include "uart.h"

extern void trap();

void boot() {
  setup_uart();
  write_uart("  _______      ______   _____ \n"
             " |  __ \\ \\    / / __ \\ / ____|\n"
             " | |__) \\ \\  / / |  | | (___  \n"
             " |  _  / \\ \\/ /| |  | |\\___ \\ \n"
             " | | \\ \\  \\  / | |__| |____) |\n"
             " |_|  \\_\\  \\/   \\____/|_____/ \n\n");

  // Set trap vector
  struct MTVEC mtvec;
  mtvec.base = (unsigned long) trap;
  mtvec.mode = DIRECT;
  switch (set_mtvec(mtvec)) {
    case SET_MTVEC_SUCCESS:
      break;
    case BASE_ADDRESS_MISALIGNED:
      panic("Trap vector base address misaligned.\n");
    case SET_MTVEC_OTHER_ERROR:
      panic("Unexpected error in setting trap vector.");
  }

  // Disable all interrupts
  enum SET_MIE_ERROR err = set_mie(0);
  if (err) {
    if (err & S_MODE_NOT_IMPLEMENTED) {
      panic("Supervisor-mode interrupt enable bits read-only as Supervisor-mode"
            " is not implemented.\n");
    } else {
      panic("Some interrupt enable bits read-only.\n");
    }
  }

  struct MISA misa = get_misa();
  enum EXTENSIONS extensions = misa.extensions;

  // Base ISA information
  write_uart("Base ISA: rv");
  if (misa.mxl == BASE_INTEGER_32) {
    write_uart("32");
  } else {
    write_uart("64");
  }
  if (extensions & INTEGER_BASE_ISA) {
    write_uart("i\n\n");
  } else {
    write_uart("e\n\n");
  }

  // ISA extensions information
  write_uart("Extensions:\n\"Zicsr\" Extension for Control and Status Register "
             "(CSR) Instructions\n");
  if (extensions & M_EXTENSION) {
    write_uart("\"M\" Extension for Integer Multiplication and Division\n");
  }
  if (extensions & A_EXTENSION) {
    write_uart("\"A\" Extension for Atomic Instructions\n");
  }
  if (extensions & F_EXTENSION) {
    if (extensions & D_EXTENSION) {
      if (extensions & Q_EXTENSION) {
        write_uart("\"Q\" Extenstion for Quad-Precision Floating-Point\n");
      } else {
        write_uart("\"D\" Extension for Double-Precision Floating-Point\n");
      }
    } else {
      write_uart("\"F\" Extension for Single-Precision Floating Point\n");
    }
  }
  if (extensions & C_EXTENSION) {
    write_uart("\"C\" Extension for Compressed Instructions\n");
  }
  if (extensions & B_EXTENSION) {
    write_uart("\"B\" Extension for Bit Manipulation (Zba/Zbb/Zbs "
               "extensions)\n");
  }
  if (extensions & V_EXTENSION) {
    write_uart("\"V\" Standard Extension for Vector Operations\n");
  }
  if (extensions & H_EXTENSION) {
    write_uart("\"H\" Extension for Hypervisor Support\n");
  }
  if (extensions & NON_STANDARD_EXTENSIONS) {
    write_uart("Additional non-standard extensions present\n");
  }
  write_uart("\n");

  // Privilege levels information
  write_uart("Privilege levels implemented:\nMachine-mode\n");
  if (extensions & S_MODE_IMPLEMENTED) {
    write_uart("Supervisor-mode\nUser-mode\n");
  } else if (extensions & U_MODE_IMPLEMENTED) {
    write_uart("User-mode\n");
  }
  write_uart("\n");

  return;
}