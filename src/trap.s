.section .text

.global trap
trap:
  # Save registers
  addi sp, sp, -224
  sd ra, 0(sp)
  sd t0, 8(sp)
  sd t1, 16(sp)
  sd t2, 24(sp)
  sd fp, 32(sp)
  sd s1, 40(sp)
  sd a2, 48(sp)
  sd a3, 56(sp)
  sd a4, 64(sp)
  sd a5, 72(sp)
  sd a6, 80(sp)
  sd a7, 88(sp)
  sd s2, 96(sp)
  sd s3, 104(sp)
  sd s4, 112(sp)
  sd s5, 120(sp)
  sd s6, 128(sp)
  sd s7, 136(sp)
  sd s8, 144(sp)
  sd s9, 152(sp)
  sd s10, 160(sp)
  sd s11, 168(sp)
  sd t3, 176(sp)
  sd t4, 184(sp)
  sd t5, 192(sp)
  sd t6, 200(sp)

  # Initialize a new frame record
  sd zero, 208(sp)
  sd zero, 216(sp)
  mv fp, sp

  mv a2, a7
  mv a3, a6
  jal handle_sbi

  # Setup return address
  csrr t0, mepc
  addi t0, t0, 0x4
  csrw mepc, t0

  # Restore registers
  ld ra, 0(sp)
  ld t0, 8(sp)
  ld t1, 16(sp)
  ld t2, 24(sp)
  ld fp, 32(sp)
  ld s1, 40(sp)
  ld a2, 48(sp)
  ld a3, 56(sp)
  ld a4, 64(sp)
  ld a5, 72(sp)
  ld a6, 80(sp)
  ld a7, 88(sp)
  ld s2, 96(sp)
  ld s3, 104(sp)
  ld s4, 112(sp)
  ld s5, 120(sp)
  ld s6, 128(sp)
  ld s7, 136(sp)
  ld s8, 144(sp)
  ld s9, 152(sp)
  ld s10, 160(sp)
  ld s11, 168(sp)
  ld t3, 176(sp)
  ld t4, 184(sp)
  ld t5, 192(sp)
  ld t6, 200(sp)
  addi sp, sp, 224

  mret
