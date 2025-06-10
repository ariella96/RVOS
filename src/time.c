#include "time.h"

volatile unsigned long* MTIMECMP = (volatile unsigned long*) 0x02004000;
volatile unsigned long* MTIME = (volatile unsigned long*) 0x0200BFF8;

void write_mtimecmp(unsigned long time) {
  *MTIMECMP = time;

  return;
}

unsigned long read_mtime() {
  return *MTIME;
}