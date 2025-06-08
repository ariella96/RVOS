.section .text

.p2align 2 # Align trap vector to 4-byte boundary
.global mtrap
mtrap:
  addi sp, sp, -112
  sd ra, 0(sp)
  sd t0, 8(sp)
  sd t1, 16(sp)
  sd t2, 24(sp)
  sd a2, 32(sp)
  sd a3, 40(sp)
  sd a4, 48(sp)
  sd a5, 56(sp)
  sd a6, 64(sp)
  sd a7, 72(sp)
  sd t3, 80(sp)
  sd t4, 88(sp)
  sd t5, 96(sp)
  sd t6, 104(sp)

  csrr t0, mcause
  addi t0, t0, -9
  beqz t0, sbi

  addi sp, sp, -16
  sd a0, 0(sp)
  sd a1, 8(sp)

  jal handle_non_sbi

  ld a0, 0(sp)
  ld a1, 8(sp)

mtrap_end:
  ld ra, 0(sp)
  ld t0, 8(sp)
  ld t1, 16(sp)
  ld t2, 24(sp)
  ld a2, 32(sp)
  ld a3, 40(sp)
  ld a4, 48(sp)
  ld a5, 56(sp)
  ld a6, 64(sp)
  ld a7, 72(sp)
  ld t3, 80(sp)
  ld t4, 88(sp)
  ld t5, 96(sp)
  ld t6, 104(sp)
  addi sp, sp, 128
  mret

sbi:
  mv a0, a7
  mv a1, a6
  jal handle_sbi
  j mtrap_end