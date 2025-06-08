.section .start

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

  # Set mepc to kernel entry
  la t0, kernel_entry
  csrw mepc, t0

  # Hand over execution to boot function
  jal boot

  # In case boot returns, halt
  j .
