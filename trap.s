.section .text
.global _trap

.balign 4 /* Align trap vector to a 4-byte boundary */
_trap:
  addi sp, sp, -256 /* Allocate stack space */

  /* Check for stack overflow */
  csrw mscratch, t0
  la t0, STACK_BOTTOM
  bltu sp, t0, _trap_error
  csrr t0, mscratch

  /* Save register values */
  sd ra, 0(sp)
  sd gp, 8(sp)
  sd tp, 16(sp)
  sd t0, 24(sp)
  sd t1, 32(sp)
  sd t2, 40(sp)
  sd fp, 48(sp)
  sd s1, 56(sp)
  sd a0, 64(sp)
  sd a1, 72(sp)
  sd a2, 80(sp)
  sd a3, 88(sp)
  sd a4, 96(sp)
  sd a5, 104(sp)
  sd a6, 112(sp)
  sd a7, 120(sp)
  sd s2, 128(sp)
  sd s3, 136(sp)
  sd s4, 144(sp)
  sd s5, 152(sp)
  sd s6, 160(sp)
  sd s7, 168(sp)
  sd s8, 176(sp)
  sd s9, 184(sp)
  sd s10, 192(sp)
  sd s11, 200(sp)
  sd t3, 208(sp)
  sd t4, 216(sp)
  sd t5, 224(sp)
  sd t6, 232(sp)

  /* Initialize a new frame record */
  sd zero, 240(sp)
  sd zero, 248(sp)
  mv fp, sp

  /* Set return address */
  csrr t0, mepc
  addi t0, t0, 4
  csrw mepc, t0

  /* If this was not an SBI call, restore a0 and a1 */
  csrr t0, mcause
  xori t0, t0, 9
  beqz _trap_end
  ld a0, 64(sp)
  ld a1, 72(sp)

  _trap_end:
    /* Restore the rest of the register values */
    ld ra, 0(sp)
    ld gp, 8(sp)
    ld tp, 16(sp)
    ld t0, 24(sp)
    ld t1, 32(sp)
    ld t2, 40(sp)
    ld fp, 48(sp)
    ld s1, 56(sp)
    ld a2, 80(sp)
    ld a3, 88(sp)
    ld a4, 96(sp)
    ld a5, 104(sp)
    ld a6, 112(sp)
    ld a7, 120(sp)
    ld s2, 128(sp)
    ld s3, 136(sp)
    ld s4, 144(sp)
    ld s5, 152(sp)
    ld s6, 160(sp)
    ld s7, 168(sp)
    ld s8, 176(sp)
    ld s9, 184(sp)
    ld s10, 192(sp)
    ld s11, 200(sp)
    ld t3, 208(sp)
    ld t4, 216(sp)
    ld t5, 224(sp)
    ld t6, 232(sp)
    addi sp, sp, 256

    mret

  _trap_error:
    la a0, trap_stack_error_message
    j _panic

.section .data

trap_stack_error_message: .ascii "Cannot allocate stack space for trap handler.\n\x00"
