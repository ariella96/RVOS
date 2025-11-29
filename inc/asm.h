#ifndef ASM_H
#define ASM_H

// Read from the Machine Vendor ID CSR
extern unsigned long read_mvendorid();

// Read from the Machine Architecture ID CSR
extern unsigned long read_marchid();

// Read from the Machine Implementation ID CSR
extern unsigned long read_mimpid();

// Read from the Machine Status CSR
extern unsigned long read_mstatus();

// Write `value` to the Machine Status CSR
extern void write_mstatus(unsigned long value);

// Write `value` to the Machine Trap Vector CSR
extern void write_mtvec(unsigned long value);

// Read from the Machine Exception Program Counter CSR
extern unsigned long read_mepc();

// Write `value` to the Machine Exception Program Counter CSR
extern void write_mepc(unsigned long value);

// Machine-mode trap return
extern void _mret();

// Machine-mode trap handler
extern void mtrap();

// Read from the Supervisor Status CSR
extern unsigned long read_sstatus();

// Write `value` to Supervisor Status CSR
extern void write_sstatus(unsigned long value);

// Write `value` to the Supervisor Exception Program Counter CSR
extern void write_sepc(unsigned long value);

// Supervisor-mode trap return
extern void _sret();

#endif