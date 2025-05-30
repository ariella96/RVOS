#include "panic.h"
#include "uart.h"
#include <stdbool.h>

void panic(char *message) {
  write_uart("Panic!\nCause of fatal error: ");
  write_uart(message);
  while (true) {}
}