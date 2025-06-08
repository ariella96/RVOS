.section .text

.global read_mstatus
# Read from the Machine Status CSR
# out: a0: Machine Status value
read_mstatus:
  csrr a0, mstatus
  jr ra

.global write_mstatus
# Write to the Machine Status CSR
# in: a0: Value to write to Machine Status
write_mstatus:
  csrw mstatus, a0
  jr ra

.global write_mtvec
# Write to the Machine Trap Vector CSR
# in: a0: Value to write to Machine Trap Vector
write_mtvec:
  csrw mtvec, a0
  jr ra

.global write_mepc
# Write to the Machine Exception Program Counter CSR
# in: a0: Value to write to Machine Exception Program Counter
write_mepc:
  csrw mepc, a0
  jr ra

.global _mret
# Machine-mode trap-return
_mret:
  mret
