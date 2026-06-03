#include "header.h"

// Символ Лежандра за критерієм Ейлера а^(p-1)/2 modpто
int Legendre(uint64_t a, uint64_t p) { 

    if (a % p == 0) 
        return 0;
    
    uint64_t ls = mod_step(a, (p - 1) / 2, p);
    
    if (ls == p - 1) 
        return -1;
    
    return 1;
}

// Примітивна перевірка на простоту
bool IsPrime(uint64_t p) {
    if (p < 2) 
        return false;
    
    if (p == 2 || p == 3) 
        return true;
    
    if (p % 2 == 0) 
        return false;

    for (uint64_t i = 3; i * i <= p; i += 2) {
        if (p % i == 0) 
            return false;
    }
    return true;
}

// Побудова факторної бази
vector<uint64_t> BuildFactorBase(uint64_t n, uint64_t B_max) {

    vector<uint64_t> base;
    base.push_back(static_cast<uint64_t>(-1));

    for (uint64_t p = 2; p <= B_max; ++p) {
        if (IsPrime(p) && Legendre(n, p) == 1) {
            base.push_back(p);
        }
    }

    return base;
}

// Перевірка на гладкість
bool IsSmooth(uint64_t m, const vector<uint64_t>& factorBase, vector<int>& exponents) {
    exponents.assign(factorBase.size(), 0);

    for (int i = 1; i < factorBase.size(); i++) {
        while (m % factorBase[i] == 0) {
            m = m / factorBase[i];
            exponents[i]++;
        }
    }

    if (m == 1) {
        for (int i = 0; i < exponents.size(); i++) {
            exponents[i] = exponents[i] % 2;
        }
        return true;
    }

    return false;
}
