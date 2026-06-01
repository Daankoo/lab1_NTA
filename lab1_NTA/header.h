#pragma once

#include <iostream>
#include <string>
#include <random>

using namespace std;

// Îïåğàö³¿

uint64_t gcd(uint64_t a, uint64_t b);
uint64_t gcd_uv(uint64_t a, uint64_t b, int64_t& u, int64_t& v);
int64_t inverse(uint64_t a, uint64_t n);
uint64_t step(uint64_t a, uint64_t b);
uint64_t mod(uint64_t a, uint64_t b);
uint64_t mod_step(uint64_t a, uint64_t b, uint64_t n);
