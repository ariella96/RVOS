UART_THR   = 0x10000000 # UART Transmitter Holding Register, when DLAB disabled
UART_IER   = 0x10000001 # UART Interrupt Enable Register, when DLAB disabled
UART_FCR   = 0x10000002 # UART FIFO Control Register
UART_LCR   = 0x10000003 # UART Line Control Register
UART_LSR   = 0x10000005 # UART Line Status Register
UART_DL_LS = 0x10000000 # UART Divisor Latch, LSB, when DLAB enabled
UART_DL_MS = 0x10000001 # UART Divisor Latch, MSB, when DLAB enabled

.section .text

.global setup_uart
# Setup the UART
setup_uart:
  # Disable all interrupts
  li t0, UART_IER
  sb zero, 0(t0)

  li t0, UART_FCR
  li t1, 0x05 # Enable the FIFOs, reset the transmitter's FIFO
  sb t1, 0(t0)

  #  Set the baud rate to maximum
  li t0, UART_LCR
  li t1, 0x80 # Enable DLAB
  sb t1, 0(t0)
  li t0, UART_DL_LS
  li t1, 0x01
  sb t1, 0(t0)
  li t0, UART_DL_MS
  sb zero, 0(t0)

  # Setup LCR
  li t0, UART_LCR
  li t1, 0x03 # 8-bit characters, one stop bit, no parity check; disable DLAB
  sb t1, 0(t0)

  jr ra


.global write_uart
# Write a string to the UART
# in: a0: pointer to string to write
write_uart:
  li t0, UART_LSR
  li t1, UART_THR
  li t4, 15

  lb t2, 0(a0)
  beqz t2, write_uart_end # If the first character is null, return

write_uart_wait_ready:
  # Wait until the Transmitter is empty
  lb t3, 0(t0)
  andi t3, t3, 0x20
  beqz t3, write_uart_wait_ready

  mv t3, zero # Character written count
write_uart_push:
  sb t2, 0(t1) # Write the character to THR

  addi a0, a0, 1 # Move pointer to next character
  lb t2, 0(a0)
  beqz t2, write_uart_end # If the next character is null, end

  addi t3, t3, 1 # Increase character written count
  bgt t3, t4, write_uart_wait_ready # If 16 characters have been written, wait for FIFOs to clear
  j write_uart_push # Otherwise, write next character

write_uart_end:
  jr ra
