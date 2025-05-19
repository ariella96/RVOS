.section .text

.global read_misa
# Read from the Machine ISA CSR
# out: a0: Machine ISA value
read_misa:
  csrr a0, misa
  jr ra

.global write_misa
# Write to the Machine ISA CSR
# in: a0: Value to write to Machine ISA
write_misa:
  csrw misa, a0
  jr ra

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

.global read_mhartid
# Read from the Hart ID CSR
# out: a0: Hart ID value
read_mhartid:
  csrr a0, mhartid
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

.global read_mtvec
# Read from the Machine Trap-Vector Base-Address CSR
# out: a0: Machine Trap-Vector Base-Address value
read_mtvec:
  csrr a0, mtvec
  jr ra

.global write_mtvec
# Write to the Machine Trap-Vector Base-Address CSR
# in: a0: Value to write to Machine Trap-Vector Base-Addreess
write_mtvec:
  csrr a0, mtvec
  jr ra

.global read_medeleg
# Read from the Machine Exception Delegation CSR
# out: a0: Machine Exception Delegation value
read_medelg:
  csrr a0, medeleg
  jr ra

.global write_medeleg
# Write to the Machine Exception Delegation CSR
# in: a0: Value to write to Machine Exception Delegation
write_medeleg:
  csrr a0, medeleg
  jr ra

.global read_mideleg
# Read from the Machine Interrupt Delegation CSR
# out: a0: Machine Interrupt Delegation value
read_mideleg:
  csrr a0, mideleg
  jr ra

.global write_mideleg
# Write to the Machine Interrupt Delegation CSR
# in: a0: Value to write to Machine Interrupt Delegation
write_mideleg:
  csrr a0, mideleg
  jr ra

.global read_mip
# Read from the Machine Interrupt Pending CSR
# out: a0: Machine Interrupt Pending value
read_mip:
  csrr a0, mip
  jr ra

.global write_mip
# Write to the Machine Interrupt Pending CSR
# in: a0: Value to write to Machine Interrupt Pending
write_mtip:
  csrr a0, mip
  jr ra

.global read_mie
# Read from the Machine Interrupt Enable CSR
# out: a0: Machine Interrupt Enable value
read_mie:
  csrr a0, mie
  jr ra

.global write_mie
# Write to the Machine Interrupt Enable CSR
# in: a0: Value to write to Machine Interrupt Enable
write_mie:
  csrr a0, mie
  jr ra

.global read_mcycle
# Read from the Machine Cycle Count CSR
# out: a0: Machine Cycle Count value
read_mcycle:
  csrr a0, mcycle
  jr ra

.global write_mcycle
# Write to the Machine Cycle Count CSR
# in: a0: Value to write to Machine Cycle Count
write_mcycle:
  csrr a0, mcycle
  jr ra

.global read_minstret
# Read from the Machine Instruction Count CSR
# out: a0: Machine Instruction Count value
read_minstret:
  csrr a0, minstret
  jr ra

.global write_minstret
# Write to the Machine Instruction Count CSR
# in: a0: Value to write to Machine Instruction Count
write_minstret:
  csrr a0, minstret
  jr ra

.macro MHPM_FUNCS n
.global read_mhpmcounter\n
# Read from the Machine Hardware Performance Monitor Counter \n CSR
# out: a0: Machine Hardware Performance Monitor Counter \n value
read_mhpmcounter\n:
  csrr a0, mhpmcounter\n
  jr ra

.global write_mhpmcounter\n
# Write to the Machine Hardware Performance Monitor Counter \n CSR
# in: a0: Value to write to Machine Hardware Performance Monitor Counter \n
write_mhpmcounter\n:
  csrw mhpmcounter\n, a0
  jr ra

.global read_mhpmevent\n
# Read from the Machine Hardware Performance Monitor Event \n CSR
# out: a0: Machine Hardware Performance Monitor Event \n value
read_mhpmevent\n:
  csrr a0, mhpmevent\n
  jr ra

.global write_mhpmevent\n
# Write to the Machine Hardware Performance Monitor Event \n CSR
# in: a0: Value to write to Machine Hardware Performance Monitor Event \n
write_mhpmevent\n:
  csrw mhpmevent\n, a0
  jr ra
.endm

# Manually invoke macro from 4 to 31
MHPM_FUNCS 3
MHPM_FUNCS 4
MHPM_FUNCS 5
MHPM_FUNCS 6
MHPM_FUNCS 7
MHPM_FUNCS 8
MHPM_FUNCS 9
MHPM_FUNCS 10
MHPM_FUNCS 11
MHPM_FUNCS 12
MHPM_FUNCS 13
MHPM_FUNCS 14
MHPM_FUNCS 15
MHPM_FUNCS 16
MHPM_FUNCS 17
MHPM_FUNCS 18
MHPM_FUNCS 19
MHPM_FUNCS 20
MHPM_FUNCS 21
MHPM_FUNCS 22
MHPM_FUNCS 23
MHPM_FUNCS 24
MHPM_FUNCS 25
MHPM_FUNCS 26
MHPM_FUNCS 27
MHPM_FUNCS 28
MHPM_FUNCS 29
MHPM_FUNCS 30
MHPM_FUNCS 31

.global read_mcountinhibit
# Read from the Machine Counter-Inhibit CSR
# out: a0: Machine Counter-Inhibit value
read_mcountinhibit:
  csrr a0, mcountinhibit
  jr ra

.global write_mcountinhibit
# Write to the Machine Counter-Inhibit CSR
# in: a0: Value to write to Machine Counter-Inhibit
write_mcountinhibit:
  csrr a0, mcountinhibit
  jr ra

.global read_mscratch
# Read from the Machine Scratch Register CSR
# out: a0: Machine Scratch Register value
read_mscratch:
  csrr a0, mscratch
  jr ra

.global write_mscratch
# Write to the Machine Scratch Register CSR
# in: a0: Value to write to Machine Scratch Register
write_mscratch:
  csrr a0, mscratch
  jr ra

.global read_mepc
# Read from the Machine Exception Program Counter CSR
# out: a0: Machine Exception Program Counter value
read_mepc:
  csrr a0, mepc
  jr ra

.global write_mepc
# Write to the Machine Exception Program Counter CSR
# in: a0: Value to write to Machine Exception Program Counter
write_mepc:
  csrr a0, mepc
  jr ra

.global read_mcause
# Read from the Machine Cause CSR
# out: a0: Machine Cause value
read_mcause:
  csrr a0, mcause
  jr ra

.global write_mcause
# Write to the Machine Cause CSR
# in: a0: Value to write to Machine Cause
write_mcause:
  csrr a0, mcause
  jr ra

.global read_mtval
# Read from the Machine Trap Value CSR
# out: a0: Machine Trap Value value
read_mtval:
  csrr a0, mtval
  jr ra

.global write_mtval
# Write to the Machine Trap Value CSR
# in: a0: Value to write to Machine Trap Value
write_mtval:
  csrr a0, mtval
  jr ra

.global read_mconfigptr
# Read from the Machine Configuration Pointer CSR
# out: a0: Machine Configuration Pointer value
read_mconfigptr:
  csrr a0, mconfigptr
  jr ra

.global read_mseccfg
# Read from the Machine Security Configuration CSR
# out: a0: Machine Security Configuration value
read_mseccfg:
  csrr a0, mseccfg
  jr ra

.global write_mseccfg
# Write to the Machine Security Configuration CSR
# in: a0: Value to write to Machine Security Configuration
write_mseccfg:
  csrr a0, mseccfg
  jr ra
