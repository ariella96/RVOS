#define UART_THR_ADDR   0x10000000; // UART Transmitter Holding Register,
                                    // when DLAB disabled
#define UART_IER_ADDR   0x10000001; // UART Interrupt Enable Register,
                                    // when DLAB disabled
#define UART_FCR_ADDR   0x10000002; // UART FIFO Control Register
#define UART_LCR_ADDR   0x10000003; // UART Line Control Register
#define UART_LSR_ADDR   0x10000005; // UART Line Status Register
#define UART_DL_LS_ADDR 0x10000000; // UART Divisor Latch, LSB,
                                    // when DLAB enabled
#define UART_DL_MS_ADDR 0x10000001; // UART Divisor Latch, MSB,
                                    // when DLAB enabled

volatile unsigned char* UART_THR   = (volatile unsigned char*) UART_THR_ADDR;
volatile unsigned char* UART_IER   = (volatile unsigned char*) UART_IER_ADDR;
volatile unsigned char* UART_FCR   = (volatile unsigned char*) UART_FCR_ADDR;
volatile unsigned char* UART_LCR   = (volatile unsigned char*) UART_LCR_ADDR;
volatile unsigned char* UART_LSR   = (volatile unsigned char*) UART_LSR_ADDR;
volatile unsigned char* UART_DL_LS = (volatile unsigned char*) UART_DL_LS_ADDR;
volatile unsigned char* UART_DL_MS = (volatile unsigned char*) UART_DL_MS_ADDR;

void setup_uart() {
  *UART_IER = 0x00; // Disable all interrupts

  *UART_FCR = 0x05; // Enable the FIFOs, reset the transmitter's FIFO

  // Set the baud rate to maximum
  *UART_LCR = 0x80; // Enable DLAB
  *UART_DL_LS = 0x01;
  *UART_DL_MS = 0x00;

  // Setup LCR
  *UART_LCR = 0x03; // 8-bit characters, one stop bit, no parity check;
                    // disable DLAB

  return;
}

void _write_uart(char* string) {
  // Wait for FIFOs to clear
  while (!(*UART_LSR & 0x20)) {
    continue;
  }

  // Write up to 16 characters to FIFOs
  for (int count = 0; count < 16; count++) {
    *UART_THR = string[0];
    string++;

    // If the next character is null, return
    if (!(string[0])) {
      return;
    }
  }

  _write_uart(string);

  return;
}

void write_uart(char* string) {
  // If string is empty, return
  if (!(string[0])) {
    return;
  }

  // Otherwise, write it
  _write_uart(string);

  return;
}