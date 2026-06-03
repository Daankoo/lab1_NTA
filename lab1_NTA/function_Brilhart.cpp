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

// Перевірка на гладкістьgbn
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

// Ланцюгові дроби
void ContinuedFraction(uint64_t n, const vector<uint64_t>& factorBase,
    vector<vector<int>>& matrix,
    vector<uint64_t>& bValues)
{
    uint64_t sqrtN = (uint64_t)sqrt((double)n);

    uint64_t u = sqrtN;
    uint64_t v = 1;
    uint64_t b_prev2 = 0;
    uint64_t b_prev1 = sqrtN;

    int maxIterations = 10000;

    for (int i = 1; i <= maxIterations; i++) {

        uint64_t v_new = (n - u * u) / v;
        uint64_t a = (sqrtN + u) / v_new;
        uint64_t u_new = a * v_new - u;

        uint64_t b = (a * b_prev1 + b_prev2) % n;

        uint64_t value;
        if (i % 2 == 1) {
            value = v_new % n;
        }
        else {
            value = (n - v_new % n) % n;
        }

        vector<int> exponents;
        if (IsSmooth(value, factorBase, exponents)) {
            exponents[0] = (i % 2 == 0) ? 1 : 0;
            matrix.push_back(exponents);
            bValues.push_back(b);
        }

        u = u_new;
        v = v_new;
        b_prev2 = b_prev1;
        b_prev1 = b;

        if (matrix.size() >= factorBase.size() + 1) {
            break;
        }
    }
}

// Пошук вектора розкладу
vector<int> SolveGF2(vector<vector<int>>& matrix, int numCols) {
    int numRows = matrix.size();

    vector<vector<int>> aug(numRows, vector<int>(numCols + numRows, 0));
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            aug[i][j] = matrix[i][j];
        }
        aug[i][numCols + i] = 1;
    }

    int row = 0;
    for (int col = 0; col < numCols && row < numRows; col++) {

        int pivot = -1;
        for (int i = row; i < numRows; i++) {
            if (aug[i][col] == 1) {
                pivot = i;
                break;
            }
        }
        if (pivot == -1) continue;

        swap(aug[row], aug[pivot]);

        for (int i = 0; i < numRows; i++) {
            if (i != row && aug[i][col] == 1) {
                for (int j = 0; j < numCols + numRows; j++) {
                    aug[i][j] ^= aug[row][j];
                }
            }
        }
        row++;
    }

    for (int i = 0; i < numRows; i++) {
        bool isZero = true;
        for (int j = 0; j < numCols; j++) {
            if (aug[i][j] != 0) {
                isZero = false;
                break;
            }
        }
        if (isZero) {
            vector<int> solution(numRows);
            for (int j = 0; j < numRows; j++) {
                solution[j] = aug[i][numCols + j];
            }
            return solution;
        }
    }

    return {};
}