#include "math.h"

struct quotient_remainder {
	unsigned long quotient;
	unsigned long remainder;
};

struct quotient_remainder div_mod(unsigned long dividend, unsigned long divisor) {
	struct quotient_remainder qr;
	if (divisor == 0) {
		qr.quotient = -1;
		qr.remainder = -1;
		return qr;
	}

	qr.quotient = 0;
	while (dividend >= divisor) {
		qr.quotient++;
		dividend -= divisor;
	}
	qr.remainder = dividend;

	return qr;
}

unsigned long div(unsigned long dividend, unsigned long divisor) {
	return div_mod(dividend, divisor).quotient;
}

unsigned long mod(unsigned long dividend, unsigned long divisor) {
	return div_mod(dividend, divisor).remainder;
}