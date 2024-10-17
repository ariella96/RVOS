.section .text
.global _trap

.balign 4 /* Align trap vector to a 4-byte boundary */
_trap:
  /* Save register values */
  addi sp, sp, -16
  sd t0, 8(sp)
  la t0, STACK_BOTTOM
  blt sp, t0, _trap_error

  csrr t0, mepc
  addi t0, t0, 4
  csrw mepc, t0

  /* Restore register values */
  ld t0, 8(sp)
  addi sp, sp, 16
  mret

  _trap_error:
    la a0, trap_stack_error_message
    j _panic

.section .data

trap_stack_error_message: .ascii "Cannot allocate stack space for trap handler.\n\x00"
