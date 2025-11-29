#include "sbi.h"

struct sbiret handle_sbi(struct sbiargs args, struct sbifunc func) {
	struct sbiret ret;
	ret.error = -1;
	ret.uvalue = 0;

	return ret;
}