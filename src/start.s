.section .text

.global _start
_start:
  la sp, STACK_TOP # Initialize kernel stack pointer

  # Create initial frame record and initialize frame pointer
  addi sp, sp, -16
  sd zero, 0(sp)
  sd zero, 8(sp)
  mv fp, sp

  # Clear global pointer and thread pointer
  mv gp, zero
  mv tp, zero

  # Hand over execution to boot function
  jal boot

  # In case boot returns, halt
  j .
