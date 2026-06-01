
#include "header.h"

// Метод пробних ділень
uint64_t TrialDivision(uint64_t n) {
    const int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };
    for (int p : primes) {
        if (n % p == 0) {
            return p;
        }
    }
    return 1; 
}

// р-метод Полларда (модифікація Флойда)
uint64_t PollardRho(uint64_t n) {
    uint64_t x0 = 2; 

    while (true) {
        uint64_t x = x0;
        uint64_t y = x0;
        uint64_t d = 1;

        while (d == 1) {
            x = (mod_step(x, 2, n) + 1) % n;

            y = (mod_step(y, 2, n) + 1) % n;
            y = (mod_step(y, 2, n) + 1) % n;

            uint64_t diff = x > y ? x - y : y - x;
            d = gcd(diff, n); 
        }

        if (d != n) {
            return d;
        }

        x0++;
    }
}