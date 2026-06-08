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

uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t n) {
	uint64_t result = 0;
	a %= n;

	while (b > 0) {
		if (b % 2 == 1)
			result = (result + a) % n;  

		a = (a + a) % n;
		b /= 2;
	}

	return result;
}

uint64_t mod_step(uint64_t a, uint64_t b, uint64_t n) {

	uint64_t c = 1;
	a %= n;
	
	while (b > 0) {
		if (b % 2 == 1) {
			c = mul_mod(c, a, n);  
		}
		a = mul_mod(a, a, n);     
		b /= 2;
	}
	return c;
}