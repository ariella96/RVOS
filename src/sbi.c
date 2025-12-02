#include "asm.h"
#include "sbi.h"

// Get SBI specification version
struct sbiret sbi_get_spec_version() {
	struct sbiret ret;
	ret.error = 0;
	ret.uvalue = 3 << 24;

	return ret;
}

// Get SBI implementation ID
struct sbiret sbi_get_impl_id() {
	struct sbiret ret;
	ret.error = 0;
	ret.uvalue = 0xFFFFFFFF;

	return ret;
}

// Get SBI implementation version
struct sbiret sbi_get_impl_version() {
	struct sbiret ret;
	ret.error = 0;
	ret.uvalue = 1;

	return ret;
}

// Probe SBI extension
struct sbiret sbi_probe_extension(long extension_id) {
	struct sbiret ret;
	ret.error = 0;

	switch (extension_id) {
		case 0x10:
			ret.uvalue = 1;
			break;
		default:
			ret.uvalue = 0;
			break;
	}

	return ret;
}

// Get machine vendor ID
struct sbiret sbi_get_mvendorid() {
	struct sbiret ret;
	ret.error = 0;
	ret.uvalue = read_mvendorid();

	return ret;
}

// Get machine architecture ID
struct sbiret sbi_get_marchid() {
	struct sbiret ret;
	ret.error = 0;
	ret.uvalue = read_marchid();

	return ret;
}

// Get machine implementation ID
struct sbiret sbi_get_mimpid() {
	struct sbiret ret;
	ret.error = 0;
	ret.uvalue = read_mimpid();

	return ret;
}

struct sbiret handle_sbi(struct sbiargs args, struct sbifunc func) {
	struct sbiret ret;
	
	switch (func.eid) {
		case 0x10:
			switch (func.fid) {
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
					ret = sbi_probe_extension(args.x0);
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
				default:
					ret.error = -2;
					ret.uvalue = 0;
					break;
			}
		default:
			ret.error = -2;
			ret.uvalue = 0;
			break;
	}

	// Update trap return program counter to point to next instruction
	write_mepc(read_mepc() + 4);

	return ret;
}