.section .text

.p2align 2 # Align trap vector to 4-byte boundary
.global mtrap
mtrap:
	addi sp, sp, -64
	sd ra, 0(sp)
	sd t0, 8(sp)
	sd t1, 16(sp)
	sd t2, 24(sp)
	sd t3, 32(sp)
	sd t4, 40(sp)
	sd t5, 48(sp)
	sd t6, 56(sp)

	# Check if this is an SBI call
	csrr t0, mcause
	addi t0, t0, -9
	beqz t0, sbi

	addi sp, sp, -64
	sd a0, 0(sp)
	sd a1, 8(sp)
	sd a2, 16(sp)
	sd a3, 24(sp)
	sd a4, 32(sp)
	sd a5, 40(sp)
	sd a6, 48(sp)
	sd a7, 56(sp)

	jal handle_mtrap

	ld a0, 0(sp)
	ld a1, 8(sp)
	ld a2, 16(sp)
	ld a3, 24(sp)
	ld a4, 32(sp)
	ld a5, 40(sp)
	ld a6, 48(sp)
	ld a7, 56(sp)
	addi sp, sp, 64

mtrap_end:
	ld ra, 0(sp)
	ld t0, 8(sp)
	ld t1, 16(sp)
	ld t2, 24(sp)
	ld t3, 32(sp)
	ld t4, 40(sp)
	ld t5, 48(sp)
	ld t6, 56(sp)
	addi sp, sp, 64
	mret

sbi:
	jal handle_sbi
	j mtrap_end
