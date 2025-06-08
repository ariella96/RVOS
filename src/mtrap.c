extern unsigned long read_mvendorid();
extern unsigned long read_marchid();
extern unsigned long read_mipmid();

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
  if (eid == 0x10) {
    switch (fid) {
      case 0:
        ret.value = 0x02000000;
        break;
      case 1:
        ret.value = 0xFFFFFFFF;
        break;
      case 2:
        ret.value = 0x00000000;
        break;
      case 3:
        if (eid == 0x10) {
          ret.value = 1;
        } else {
          ret.value = 0;
        }
        break;
      case 4:
        ret.value = read_mvendorid();
        break;
      case 5:
        ret.value = read_marchid();
        break;
      case 6:
        ret.value = read_mipmid();
        break;
      default:
        ret.error = -2;
    }
  } else {
    ret.error = -2;
    ret.value = 0;
  }

  return ret;
}