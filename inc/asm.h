#ifndef ASM_H
#define ASM_H

extern unsigned long read_mvendorid();

extern unsigned long read_marchid();

extern unsigned long read_mimpid();

extern unsigned long read_mstatus();

extern void write_mstatus(unsigned long val);

extern void write_mtvec(unsigned long val);

extern unsigned long read_mie();

extern void write_mie(unsigned long val);

extern unsigned long read_mip();

extern void write_mip(unsigned long val);

extern unsigned long read_mepc();

extern void write_mepc(unsigned long val);

extern unsigned long read_mcause();

extern void _mret();

extern struct sbiret call_sbi(unsigned long eid, unsigned long fid,
                              unsigned long arg);

extern void write_stvec(unsigned long val);

extern unsigned long read_scause();

#endif