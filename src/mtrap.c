#include "time.h"

extern unsigned long read_mvendorid();
extern unsigned long read_marchid();
extern unsigned long read_mimpid();
extern unsigned long read_mcause();

void handle_non_sbi() {
  if (read_mcause() == 0x8000000000000007) { // Machine Timer interrupt
    write_mtimecmp(0xFFFFFFFFFFFFFFFF);
  }

  return;
}

struct sbiret {
  long error;
  long value;
};

struct sbiret sbi_get_spec_version() {
  struct sbiret ret;
  ret.value = 0x02000000;
  ret.error = 0;

  return ret;
}

struct sbiret sbi_get_impl_id() {
  struct sbiret ret;
  ret.value = 0xFFFFFFFF;
  ret.error = 0;

  return ret;
}

struct sbiret sbi_get_impl_version() {
  struct sbiret ret;
  ret.value = 0x00000000;
  ret.error = 0;

  return ret;
}

struct sbiret sbi_probe_extension(long eid) {
  struct sbiret ret;
  if (eid == 0x10) {
    ret.value = 1;
  } else {
    ret.value = 0;
  }
  ret.error = 0;

  return ret;
}

struct sbiret sbi_get_mvendorid() {
  struct sbiret ret;
  ret.value = read_mvendorid();
  ret.error = 0;

  return ret;
}

struct sbiret sbi_get_marchid() {
  struct sbiret ret;
  ret.value = read_marchid();
  ret.error = 0;

  return ret;
}

struct sbiret sbi_get_mimpid() {
  struct sbiret ret;
  ret.value = read_mimpid();
  ret.error = 0;

  return ret;
}

struct sbiret handle_sbi(unsigned long eid, unsigned long fid) {
  struct sbiret ret;
  if (eid == 0x10) { // Base Extension
    switch (fid) {
      case 0: // Get SBI specification version
        ret = sbi_get_spec_version();
        break;
      case 1: // Get SBI implementation ID
        ret = sbi_get_impl_id();
        break;
      case 2: // Get SBI implementation version
        ret = sbi_get_impl_version();
        break;
      case 3: // Probe SBI extension
        ret = sbi_probe_extension(eid);
        break;
      case 4: // Get machine vendor ID
        ret = sbi_get_mvendorid();
        break;
      case 5: // Get machine architecture ID
        ret = sbi_get_marchid();
        break;
      case 6: // Get machine implementation ID
        ret = sbi_get_mimpid();
        break;
      default:
        ret.error = -2;
    }
  } else {
    ret.error = -2;
  }

  return ret;
}