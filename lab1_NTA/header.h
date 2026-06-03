#pragma once

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <cmath>

using namespace std;

// Operations.cpp
uint64_t gcd(uint64_t a, uint64_t b);
uint64_t gcd_uv(uint64_t a, uint64_t b, int64_t& u, int64_t& v);
int64_t  inverse(uint64_t a, uint64_t n);
uint64_t mod(uint64_t a, uint64_t b);
uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t n);
uint64_t mod_step(uint64_t a, uint64_t b, uint64_t n);

// MillerRabin.cpp
void     step2(uint64_t p, uint64_t& d, uint64_t& s);
bool     TestSPP(uint64_t p, uint64_t a, uint64_t d, uint64_t s);
bool     MillerRabin(uint64_t p, int k);

// Pollard.cpp
uint64_t TrialDivision(uint64_t n);
uint64_t PollardRho(uint64_t n);

// function_Brilhart.cpp
int               Legendre(uint64_t a, uint64_t p);
bool              IsPrime(uint64_t p);
vector<uint64_t>  BuildFactorBase(uint64_t n, uint64_t B_max);
bool              IsSmooth(uint64_t m, const vector<uint64_t>& factorBase, vector<int>& exponents);

// Brilhart.cpp
void              ContinuedFraction(uint64_t n, const vector<uint64_t>& factorBase, vector<vector<int>>& matrix, vector<uint64_t>& bValues, vector<uint64_t>& smoothValues);
vector<int>       SolveGF2(vector<vector<int>>& matrix, int numCols);
uint64_t          BrilhartMorrison(uint64_t n);