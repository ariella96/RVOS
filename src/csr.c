#include "csr.h"

extern unsigned long read_misa();
extern void write_misa(unsigned long val);

struct MISA get_misa() {
  struct MISA misa;
  unsigned long csr_misa = read_misa();
  misa.machine_xlen = csr_misa >> 62;
  misa.extensions = (csr_misa << 38) >> 38;
  return misa;
}

enum SET_MISA_EXTENSIONS_ERROR set_misa_extensions(enum EXTENSIONS ext) {
  enum SET_MISA_EXTENSIONS_ERROR err = SET_MISA_EXTENSIONS_SUCCESS;
  enum EXTENSIONS old_ext = get_misa().extensions;
  if ((old_ext & C_EXTENSION) && !(ext & C_EXTENSION)) {
    err |= IALIGN_INCREASE_DISALLOWED;
    ext &= C_EXTENSION;
  }

  write_misa(ext);

  enum EXTENSIONS new_ext = get_misa().extensions;
  enum EXTENSIONS failed = ext ^ new_ext;
  if (failed) {
    if (failed & EMBEDDED_BASE_ISA) {
      err |= EMBEDDED_BASE_ISA_READ_ONLY;
    }
    if (failed & A_EXTENSION) {
      err |= A_EXTENSION_MODIFICATION_DISALLOWED;
    }
    if (failed & B_EXTENSION) {
      err |= B_EXTENSION_MODIFICATION_DISALLOWED;
    }
    if (failed & C_EXTENSION) {
      err |= C_EXTENSION_MODIFICATION_DISALLOWED;
    }
    if (failed & D_EXTENSION) {
      if ((ext & D_EXTENSION) && !(ext & F_EXTENSION)) {
        err |= D_EXTENSION_REQUIRES_F_EXTENSION;
        err |= set_misa_extensions(ext | F_EXTENSION);
        set_misa_extensions(new_ext);
      } else {
        err |= D_EXTENSION_MODIFICATION_DISALLOWED;
      }
    }
    if (failed & F_EXTENSION) {
      err |= F_EXTENSION_MODIFICATION_DISALLOWED;
    }
    if (failed & H_EXTENSION) {
      err |= H_EXTENSION_MODIFICATION_DISALLOWED;
    }
    if (failed & INTEGER_BASE_ISA) {
      err |= BASE_ISA_MODIFICATION_DISALLOWED;
    }
    if (failed & M_EXTENSION) {
      err |= M_EXTENSION_MODIFICATION_DISALLOWED;
    }
    if (failed & Q_EXTENSION) {
      if ((ext & Q_EXTENSION) && !(ext & D_EXTENSION)) {
        err |= Q_EXTENSION_REQUIRES_D_EXTENSION;
        err |= set_misa_extensions(ext | D_EXTENSION | F_EXTENSION);
        set_misa_extensions(new_ext);
      } else {
        err |= D_EXTENSION_MODIFICATION_DISALLOWED;
      }
    }
    if (failed & S_MODE_IMPLEMENTED) {
      if ((ext & S_MODE_IMPLEMENTED) && !(ext & U_MODE_IMPLEMENTED)) {
        err |= S_MODE_IMPLEMENTED;
        err |= set_misa_extensions(ext | U_MODE_IMPLEMENTED);
        set_misa_extensions(new_ext);
      } else {
        err |= S_MODE_MODIFICATION_DISALLOWED;
      }
    }
    if (failed & U_MODE_IMPLEMENTED) {
      err |= U_MODE_MODIFICATION_DISALLOWED;
    }
    if (failed & V_EXTENSION) {
      err |= V_EXTENSION_MODIFICATION_DISALLOWED;
    }
    if (failed & NON_STANDARD_EXTENSIONS) {
      err |= NON_STANDARD_EXTENSIONS_MODIFICATION_DISALLOWED;
    }
  }
  if (err & IALIGN_INCREASE_DISALLOWED) {
    write_misa(old_ext);
  }

  return err;
}