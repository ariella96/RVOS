extern long trap_cause();

struct sbiret {
  long error;
  long value;
};

struct sbiret handle_trap(long sbi1, long sbi2, long eid, long fid) {
  long cause = trap_cause();
  struct sbiret s;
  s.error = -2;
  s.value = 0;
  
  if (cause == 0x9 && eid == 0x10) { // SBI Call, base extension
    switch (fid) {
      default:
        return s;
    }
  }

  return s;
}