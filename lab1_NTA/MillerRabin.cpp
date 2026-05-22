#include "header.h"

bool SimpleTest(uint64_t a, uint64_t p) {

	if (p % 2 == 0) {
		return 0;
	}

	uint64_t d = gcd(a, p);

	if (d != 1) {
		return 0;
	}
	else if (mod_step(a, p-1, p) != 1) {
		return 0;
	}
	else {
		return 1;
	}
}