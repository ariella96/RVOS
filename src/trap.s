.global trap

trap:
  # Save register values
  addi sp, sp, -240
  sd ra, 0(sp)
  sd t0, 8(sp)
  sd t1, 16(sp)
  sd t2, 24(sp)
  sd fp, 32(sp)
  sd s1, 40(sp)
  sd a0, 48(sp)
  sd a1, 56(sp)
  sd a2, 64(sp)
  sd a3, 72(sp)
  sd a4, 80(sp)
  sd a5, 88(sp)
  sd a6, 96(sp)
  sd a7, 104(sp)
  sd s2, 112(sp)
  sd s3, 120(sp)
  sd s4, 128(sp)
  sd s5, 136(sp)
  sd s6, 144(sp)
  sd s7, 152(sp)
  sd s8, 160(sp)
  sd s9, 168(sp)
  sd s10, 176(sp)
  sd s11, 184(sp)
  sd t3, 192(sp)
  sd t4, 200(sp)
  sd t5, 208(sp)
  sd t6, 216(sp)

  # Initialize a new frame record
  sd zero, 224(sp)
  sd zero, 232(sp)
  mv fp, sp

  jal handle_trap # Handle trap

  # Set return address
  csrr t0, mepc
  addi t0, t0, 4
  csrw mepc, t0

  # Restore register values
  ld ra, 0(sp)
  ld t0, 8(sp)
  ld t1, 16(sp)
  ld t2, 24(sp)
  ld fp, 32(sp)
  ld s1, 40(sp)
  ld a0, 48(sp)
  ld a1, 56(sp)
  ld a2, 64(sp)
  ld a3, 72(sp)
  ld a4, 80(sp)
  ld a5, 88(sp)
  ld a6, 96(sp)
  ld a7, 104(sp)
  ld s2, 112(sp)
  ld s3, 120(sp)
  ld s4, 128(sp)
  ld s5, 136(sp)
  ld s6, 144(sp)
  ld s7, 152(sp)
  ld s8, 160(sp)
  ld s9, 168(sp)
  ld s10, 176(sp)
  ld s11, 184(sp)
  ld t3, 192(sp)
  ld t4, 200(sp)
  ld t5, 208(sp)
  ld t6, 216(sp)
  addi sp, sp, 240

  mret
