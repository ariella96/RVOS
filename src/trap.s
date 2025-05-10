.p2align 2 # Align trap vector to 4-byte boundary
.global trap
trap:
    addi sp, sp, -16
    sd t0, 0(sp)
    sd t1, 8(sp)

    csrr t0, mepc
    csrr t1, mcause
    bltz t1, exit_trap # For interrupts, return to the interrupted instruction
    addi t0, t0, 4 # For exceptions, return to the instruction after the exception
    csrw mepc, t0

exit_trap:
    ld t0, 0(sp)
    ld t1, 8(sp)
    addi sp, sp, 16
    mret
