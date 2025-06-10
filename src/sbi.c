#include "asm.h"
#include "sbi.h"
#include "time.h"

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
  if (eid == 0x10 || eid == 0x54494D45) {
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

struct sbiret sbi_set_timer(unsigned long stime_value) {
  if (read_mtime() < stime_value) {
    write_mip(read_mip() & ~0x20);
  }

  struct sbiret ret;
  ret.error = 0;

  write_mtimecmp(stime_value);
  write_mie(read_mie() | 0x80);

  return ret;
}

struct sbiret handle_sbi(unsigned long eid, unsigned long fid,
                         unsigned long arg) {
  struct sbiret ret;
  switch (eid) {
    case 0x10: // Base extension
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
          ret = sbi_probe_extension(arg);
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
      break;
    case 0x54494D45: // TIME extension
      if (fid == 0) {
        ret = sbi_set_timer(arg);
      } else {
        ret.error = -2;
      }
  }

  write_mepc(read_mepc() + 2);
  return ret;
}