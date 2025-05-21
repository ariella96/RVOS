#include "csr.h"

extern unsigned long read_misa();
extern void write_misa(unsigned long val);

struct MISA get_misa() {
  struct MISA misa;
  unsigned long csr_misa = read_misa();
  misa.mxl = csr_misa >> 62;
  misa.extensions = (csr_misa << 38) >> 38;
  return misa;
}

void set_misa(struct MISA misa) {
  write_misa(misa.extensions + ((unsigned long) misa.mxl << 62));
}