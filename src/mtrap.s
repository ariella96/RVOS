.section .text

.p2align 2 # Align trap vector to 4-byte boundary
.global mtrap
mtrap:
  addi sp, sp, -16
  sd t0, 0(sp)
  sd t1, 8(sp)
  la t0, mie_prev
  csrr t1, mie
  sh t1, 0(t0)
  csrw mie, zero

  addi sp, sp, -96
  sd ra, 0(sp)
  sd t2, 8(sp)
  sd a2, 16(sp)
  sd a3, 24(sp)
  sd a4, 32(sp)
  sd a5, 40(sp)
  sd a6, 48(sp)
  sd a7, 56(sp)
  sd t3, 64(sp)
  sd t4, 72(sp)
  sd t5, 80(sp)
  sd t6, 88(sp)

  csrr t0, mcause
  addi t0, t0, -9
  beqz t0, sbi

  addi sp, sp, -16
  sd a0, 0(sp)
  sd a1, 8(sp)

  jal handle_non_sbi_mtrap

  ld a0, 0(sp)
  ld a1, 8(sp)

mtrap_end:
  la t0, mie_prev
  lh t1, 0(t0)
  csrw mie, t1

  ld ra, 0(sp)
  ld t2, 8(sp)
  ld a2, 16(sp)
  ld a3, 24(sp)
  ld a4, 32(sp)
  ld a5, 40(sp)
  ld a6, 48(sp)
  ld a7, 56(sp)
  ld t3, 64(sp)
  ld t4, 72(sp)
  ld t5, 80(sp)
  ld t6, 88(sp)
  ld t0, 96(sp)
  ld t1, 104(sp)
  addi sp, sp, 112
  mret

sbi:
  mv a0, a7
  mv a1, a6
  jal handle_sbi
  j mtrap_end

.section .bss

mie_prev: .space 16
