#include "header.h"

void step2(uint64_t p, uint64_t& d, uint64_t& s) {
	d = 1;
	s = 0;
	uint64_t p_1 = p - 1;

	while (p_1 % 2 == 0) {
		p_1 /= 2;
		s += 1;
	}

	d = p_1;
}

bool TestSPP(uint64_t p, uint64_t a, uint64_t d, uint64_t s) {
	uint64_t a_mod = mod_step(a, d, p);

	if (a_mod == 1 || a_mod == p - 1) {
		return 1;
	}

	for (uint64_t r = 0; r < s - 1; ++r) {

		a_mod = mul_mod(a_mod, a_mod, p);
		
		if (a_mod == p - 1) {
			return 1;
		}
		if (a_mod == 1) {
			return 0;
		}
	}

	return 0;
}

bool MillerRabin(uint64_t p, int k) {
    if (p < 2)
		return 0;
    
	if (p == 2 || p == 3) 
		return 1;
    
	if (p % 2 == 0) 
		return 0;

    uint64_t d, s;

    step2(p, d, s);

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dis(2, p - 2);

    for (int i = 0; i < k; ++i) {
        uint64_t x = dis(gen);

        if (gcd(x, p) > 1) {
            return 0;
        }

        if (!TestSPP(p, x, d, s)) {
            return 0;
        }
    }

    return 1;
}