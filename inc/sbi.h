#ifndef SBI_H
#define SBI_H

struct sbiret {
  long error;
  long value;
};

struct sbiret handle_sbi(unsigned long eid, unsigned long fid,
                         unsigned long arg);

#endif