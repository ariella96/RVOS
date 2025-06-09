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
  if (eid == 0x10) { // Base Extension
    switch (fid) {
      case 0: // Get SBI specification version
        ret.value = 0x02000000;
        break;
      case 1: // Get SBI implementation ID
        ret.value = 0xFFFFFFFF;
        break;
      case 2: // Get SBI implementation version
        ret.value = 0x00000000;
        break;
      case 3: // Probe SBI extension
        if (eid == 0x10) {
          ret.value = 1;
        } else {
          ret.value = 0;
        }
        break;
      case 4: // Get machine vendor ID
        ret.value = read_mvendorid();
        break;
      case 5: // Get machine architecture ID
        ret.value = read_marchid();
        break;
      case 6: // Get machine implementation ID
        ret.value = read_mipmid();
        break;
      default:
        ret.error = -2;
    }
  } else {
    ret.error = -2;
  }

  return ret;
}