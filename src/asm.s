.section .text

.global read_mstatus
read_mstatus:
  csrr a0, mstatus
  jr ra

.global write_mstatus
write_mstatus:
  csrw mstatus, a0
  jr ra

.global write_mepc
write_mepc:
  csrw mepc, a0
  jr ra

.global _mret
_mret:
  mret

.global read_sstatus
read_sstatus:
  csrr a0, sstatus
  jr ra

.global write_sstatus
write_sstatus:
  csrw sstatus, a0
  jr ra

.global write_sepc
write_sepc:
	csrw sepc, a0
	jr ra
