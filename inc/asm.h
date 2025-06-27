#ifndef ASM_H
#define ASM_H

extern unsigned long read_mvendorid();
extern unsigned long read_marchid();
extern unsigned long read_mimpid();
extern unsigned long read_mstatus();
extern void write_mstatus(unsigned long val);
extern void write_mtvec(unsigned long val);
extern void write_mepc(unsigned long val);
extern void _mret();
extern void mtrap();

#endif