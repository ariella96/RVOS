#include "time.h"

volatile unsigned long* MTIMECMP = (volatile unsigned long*) 0x02004000;

void write_mtimecmp(unsigned long time) {
  *MTIMECMP = time;

  return;
}