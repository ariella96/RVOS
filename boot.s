.section .text
.global _start

UART_RBR   = 0x10000000 /* UART Receiver Buffer Register,
                           when DLAB disabled */
UART_THR   = 0x10000000 /* UART Transmitter Holding Register,
                           when DLAB disabled */
UART_IER   = 0x10000001 /* UART Interrupt Enable Register,
                           when DLAB disabled */
UART_IIR   = 0x10000002 /* UART Interrupt Identification Register */
UART_FCR   = 0x10000002 /* UART FIFO Control Register */
UART_LCR   = 0x10000003 /* UART Line Control Register */
UART_MCR   = 0x10000004 /* UART Modem Control Register */
UART_LSR   = 0x10000005 /* UART Line Status Register */
UART_MSR   = 0x10000006 /* UART Modem Status Register */
UART_SR    = 0x10000007 /* UART Scratch Register */
UART_DL_LS = 0x10000000 /* UART Divisor Latch, Least Significant Byte,
                           when DLAB enabled */
UART_DL_MS = 0x10000001 /* UART Divisor Latch, Most Significant Byte,
                           when DLAB enabled */


_start:
  la sp, STACK_TOP /* Stack pointer */

  /* Setup UART */

  /* Disable all interrupts */
  li t0, UART_IER
  sb zero, 0(t0)

  /* Disable the FIFOs */
  li t0, UART_FCR
  sb zero, 0(t0)

  /*  Set the baud rate to maximum */
  li t0, UART_LCR
  li t1, 0x80 /* Enable DLAB */
  sb t1, 0(t0)
  li t0, UART_DL_LS
  li t1, 0x01
  sb t1, 0(t0)
  li t0, UART_DL_MS
  sb zero, 0(t0)

  /* Setup LCR */
  li t0, UART_LCR
  li t1, 0x03 /* 8-bit characters, one stop bit, no parity check;
                 also disable DLAB */
  sb t1, 0(t0)

  la a0, rvos
  jal write_uart

  li a0, 0x0A
  jal write_uart_character

  la a0, boot_message
  jal write_uart

  j .

/* Write a character to the UART
   in: a0: character to write */ 
write_uart_character:
  li t0, UART_LSR
  li t1, UART_THR

  _write_uart_character_wait_ready:
    /* Wait until the Transmitter is empty */
    lb t2, 0(t0)
    andi t3, t2, 0x40
    beqz t3, _write_uart_character_wait_ready

    /* Write the character to THR */
    sb a0, 0(t1)
    jr ra

/* Writes a null-terminated string to the UART
   in: a0: pointer to string
   out: a0: 0 on success, 1 on error */
write_uart:
  lb t0, 0(a0)
  bnez t0, _write_uart_nonnull /* Write the character if it is not null */
  li a0, 0
  jr ra                        /* Otherwise, return */

  _write_uart_nonnull:
    addi sp, sp, -16
    la t1, STACK_BOTTOM
    ble sp, t1, _write_uart_error

    sd ra, 0(sp) /* Save return address */
    sd a0, 8(sp) /* Save pointer */
    mv a0, t0
    jal write_uart_character
    ld a0, 8(sp) /* Restore pointer */
    ld ra, 0(sp) /* Restore return address */
    addi sp, sp, 16
  
    /* Increase the pointer and recurse */
    addi a0, a0, 1
    j write_uart
  
  _write_uart_error:
    addi sp, sp, 16
    li a0, 1
    jr ra

.section .data

rvos: .ascii "  _______      ______   _____ \n |  __ \\ \\    / / __ \\ / ____|\n | |__) \\ \\  / / |  | | (___  \n |  _  / \\ \\/ /| |  | |\\___ \\ \n | | \\ \\  \\  / | |__| |____) |\n |_|  \\_\\  \\/   \\____/|_____/ \n\x00"

boot_message: .ascii "Beginning boot sequence...\n\x00"

.section .bss
