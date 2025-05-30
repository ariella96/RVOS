#include "csr.h"
#include "panic.h"
#include "uart.h"

extern void trap();

char* rvos = "  _______      ______   _____ \n"
             " |  __ \\ \\    / / __ \\ / ____|\n"
             " | |__) \\ \\  / / |  | | (___  \n"
             " |  _  / \\ \\/ /| |  | |\\___ \\ \n"
             " | | \\ \\  \\  / | |__| |____) |\n"
             " |_|  \\_\\  \\/   \\____/|_____/ \n\n";

char* base_isa_message = "Base ISA: rv";
char* extensions_message = "Extensions: \n\"Zicsr\" Extension for Control and "
                           "Status Register (CSR) Instructions\n";
char* privilege_levels_message = "Privilege levels implemented:\n"
                                 "Machine-mode\n";

void boot() {
  setup_uart();
  write_uart(rvos);

  struct MTVEC mtvec;
  mtvec.base = ((unsigned long) trap) >> 2;
  mtvec.mode = DIRECT;
  switch (set_mtvec(mtvec)) {
    case SET_MTVEC_SUCCESS:
      break;
    case BASE_ADDRESS_MISALIGNED:
      panic("Trap vector base misaligned.");
    case VECTOR_MODE_RESERVED:
      panic("Invalid trap vector mode.");
    case SET_MTVEC_OTHER_ERROR:
      panic("Unknown error in setting trap vector.");
  }

  struct MISA misa = get_misa();
  enum EXTENSIONS extensions = misa.extensions;

  // Base ISA information
  write_uart(base_isa_message);
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
  write_uart(extensions_message);
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
  write_uart(privilege_levels_message);
  if (extensions & S_MODE_IMPLEMENTED) {
    write_uart("Supervisor-mode\nUser-mode\n");
  } else if (extensions & U_MODE_IMPLEMENTED) {
    write_uart("User-mode\n");
  }
  write_uart("\n");

  return;
}