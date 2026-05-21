#include "header.h"

uint64_t gcd(uint64_t a, uint64_t b) {
	while (b != 0) { // a = q*b + r
		uint64_t q = a / b;
		uint64_t r = a % b;

		a = b;
		b = r;
	}

	return a;
}

uint64_t gcd_uv(uint64_t a, uint64_t b, int64_t& u, int64_t& v) {
	int64_t u0 = 1, u1 = 0;
	int64_t v0 = 0, v1 = 1;

	while (b != 0) { // a = q*b + r
		uint64_t q = a / b;
		uint64_t r = a % b;

		a = b;
		b = r;

		int64_t u_n = u0 - q * u1;
		int64_t v_n = v0 - q * v1;

		u0 = u1;
		u1 = u_n;

		v0 = v1;
		v1 = v_n;
	}

	u = u0;
	v = v0;

	return a;
}

int64_t inverse(uint64_t a, uint64_t n) {
	int64_t u, v;

	if (gcd_uv(a, n, u, v) != 1) {
		//cout << "Error: Inverse element is not found";
		return -1;
	}

	return (u % n + n) % n;
}

uint64_t step(uint64_t a, uint64_t b) {
	uint64_t c = a;

	for (int i = 0; i < b - 1; i++) {
		c *= a;
	}

	return c;
}

uint64_t mod(uint64_t a, uint64_t b) {
	uint64_t c = ((a % b) + b) % b;
	return c;
}

uint64_t mod_step(uint64_t a, uint64_t b, uint64_t n) {

	uint64_t c = 1;

	for (int i = 0; i < b; i++) {
		c = mod(c * a, n);
	}
	
	return c;
}