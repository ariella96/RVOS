struct sbiret {
  long error;
  long value;
};

void handle_non_sbi() {
  return;
}

struct sbiret handle_sbi(unsigned long eid, unsigned long fid) {
  struct sbiret ret;
  ret.error = 0;
  ret.value = 0;

  return ret;
}