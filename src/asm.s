.section .text

.global read_mvendorid
read_mvendorid:
  csrr a0, mvendorid
  jr ra

.global read_marchid
read_marchid:
  csrr a0, marchid
  jr ra

.global read_mimpid
read_mimpid:
  csrr a0, mimpid
  jr ra

.global read_mstatus
read_mstatus:
  csrr a0, mstatus
  jr ra

.global write_mstatus
write_mstatus:
  csrw mstatus, a0
  jr ra

.global write_mtvec
write_mtvec:
  csrw mtvec, a0
  jr ra

.global read_mepc
read_mepc:
  csrr a0, mepc
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

.global _sret
_sret:
  sret
