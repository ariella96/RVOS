const int BASE_EXTENSION = 0x10; // Base Extension ID
const long SBI_SUCCESS = 0;
const long SBI_ERR_FAILED = -1;
const long SBI_ERR_NOT_SUPPORTED = -2;

struct sbiret {
  long error;
  long value;
};

struct sbiret sbi_get_spec_version() {
  struct sbiret ret;
  ret.error = SBI_SUCCESS;
  ret.value = 0x2000000;

  return ret;
}

struct sbiret sbi_get_impl_id() {
  struct sbiret ret;
  ret.error = SBI_ERR_FAILED;
  ret.value = 0;

  return ret;
}

struct sbiret sbi_get_impl_version() {
  struct sbiret ret;
  ret.error = SBI_ERR_FAILED;
  ret.value = 0;

  return ret;
}

struct sbiret sbi_probe_extension(long eid) {
  struct sbiret ret;
  ret.error = SBI_SUCCESS;

  if (eid == BASE_EXTENSION) {
    ret.value = 0;
  } else {
    ret.value = 1;
  }

  return ret;
}

struct sbiret sbi_get_mvendorid() {
  struct sbiret ret;
  ret.error = SBI_SUCCESS;
  ret.value = 0;

  return ret;
}

struct sbiret sbi_get_marchid() {
  struct sbiret ret;
  ret.error = SBI_SUCCESS;
  ret.value = 0;

  return ret;
}

struct sbiret sbi_get_mimpid() {
  struct sbiret ret;
  ret.error = SBI_SUCCESS;
  ret.value = 0;

  return ret;
}

struct sbiret handle_sbi(long arg1, long arg2, int eid, int fid) {
  struct sbiret ret;
  ret.error = SBI_ERR_NOT_SUPPORTED;
  ret.value = 0;

  if (eid == BASE_EXTENSION) {
    switch (fid) {
      case 0:
        ret = sbi_get_spec_version();
        break;
      case 1:
        ret = sbi_get_impl_id();
        break;
      case 2:
        ret = sbi_get_impl_version();
        break;
      case 3:
        ret = sbi_probe_extension(eid);
        break;
      case 4:
        ret = sbi_get_mvendorid();
        break;
      case 5:
        ret = sbi_get_marchid();
        break;
      case 6:
        ret = sbi_get_mimpid();
        break;
    }
  }

  return ret;
}