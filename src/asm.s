.section .text

.global read_mvendorid
# Read from the Machine Vendor ID CSR
# out: a0: Machine Vendor ID value
read_mvendorid:
  csrr a0, mvendorid
  jr ra

.global read_marchid
# Read from the Machine Architecture ID CSR
# out: a0: Machine Architecture ID value
read_marchid:
  csrr a0, marchid
  jr ra

.global read_mimpid
# Read from the Machine Implementation ID CSR
# out: a0: Machine Implementation ID value
read_mimpid:
  csrr a0, mimpid
  jr ra

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
