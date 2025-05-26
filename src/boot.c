#include "uart.h"
#include "csr.h"

char* rvos = "  _______      ______   _____ \n"
             " |  __ \\ \\    / / __ \\ / ____|\n"
             " | |__) \\ \\  / / |  | | (___  \n"
             " |  _  / \\ \\/ /| |  | |\\___ \\ \n"
             " | | \\ \\  \\  / | |__| |____) |\n"
             " |_|  \\_\\  \\/   \\____/|_____/ \n\n";

char* base_isa = "Base ISA: rv";
char* extensions = "Extensions: \n\"Zicsr\" Extension for Control and Status "
                   "Register (CSR) Instructions\n";
char* privilege_levels = "Privilege levels implemented: \nMachine-mode\n";

void boot() {
  setup_uart();
  write_uart(rvos);

  struct MISA misa = get_misa();
  enum EXTENSIONS misa_extensions = misa.extensions;

  // Base ISA information
  write_uart(base_isa);
  if (misa.mxl == BASE_INTEGER_32) {
    write_uart("32");
  } else {
    write_uart("64");
  }
  if (misa_extensions & INTEGER_BASE_ISA) {
    write_uart("i\n\n");
  } else {
    write_uart("e\n\n");
  }

  // ISA extensions information
  write_uart(extensions);
  if (misa_extensions & INTEGER_MULTIPLY_DIVIDE_EXTENSION) {
    write_uart("\"M\" Extension for Integer Multiplication and Division\n");
  }
  if (misa_extensions & ATOMIC_EXTENSION) {
    write_uart("\"A\" Extension for Atomic Instructions\n");
  }
  if (misa_extensions & SINGLE_PRECISION_FLOATING_PONT_EXTENSION) {
    if (misa_extensions & DOUBLE_PRECISION_FLOATING_POINT_EXTENSION) {
      if (misa_extensions & QUAD_PRECISION_FLOATING_POINT_EXTENSION) {
        write_uart("\"Q\" Extenstion for Quad-Precision Floating-Point\n");
      } else {
        write_uart("\"D\" Extension for Double-Precision Floating-Point\n");
      }
    } else {
      write_uart("\"F\" Extension for Single-Precision Floating Point\n");
    }
  }
  if (misa_extensions & COMPRESSED_EXTENSION) {
    write_uart("\"C\" Extension for Compressed Instructions\n");
  }
  if (misa_extensions & B_EXTENSION) {
    write_uart("\"B\" Extension for Bit Manipulation (Zba/Zbb/Zbs "
               "extensions)\n");
  }
  if (misa_extensions & VECTOR_EXTENSION) {
    write_uart("\"V\" Standard Extension for Vector Operations\n");
  }
  if (misa_extensions & HYPERVISOR_EXTENSION) {
    write_uart("\"H\" Extension for Hypervisor Support\n");
  }
  if (misa_extensions & NON_STANDARD_EXTENSIONS) {
    write_uart("Additional non-standard extensions present\n");
  }
  write_uart("\n");

  // Privilege levels information
  write_uart(privilege_levels);
  if (misa_extensions & SUPERVISOR_MODE_IMPLEMENTED) {
    write_uart("Supervisor-mode\nUser-mode\n");
  } else if (misa_extensions & USER_MODE_IMPLEMENTED) {
    write_uart("User-mode\n");
  }
  write_uart("\n");

  return;
}