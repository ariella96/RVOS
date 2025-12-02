#include "math.h"
#include "string.h"

int num_to_string_helper(char* buf, long value) {
	int n = 0;
	if (value >= 10) {
		n = num_to_string_helper(buf, div(value, 10));
	}
	buf[n] = '0' + mod(value, 10);

	return n + 1;
}

void num_to_string(char *buf, long value) {
	int n = num_to_string_helper(buf, value);
	buf[n] = '\0';

	return;
}