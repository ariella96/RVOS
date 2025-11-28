#ifndef ASM_H
#define ASM_H

// Read from the Machine Status CSR
extern unsigned long read_mstatus();

// Write `value` to the Machine Status CSR
extern void write_mstatus(unsigned long value);

// Write `value` to the Machine Exception Program Counter CSR
extern void write_mepc(unsigned long value);

// Machine-mode trap return
extern void _mret();

// Read from the Supervisor Status CSR
extern unsigned long read_sstatus();

// Write `value` to Supervisor Status CSR
extern void write_sstatus(unsigned long value);

// Write `value` to the Supervisor Exception Program Counter CSR
extern void write_sepc(unsigned long value);

#endif