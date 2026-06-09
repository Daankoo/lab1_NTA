#include "header.h"

// Ланцюгові дроби
void ContinuedFraction(uint64_t n, const vector<uint64_t>& factorBase,
    vector<vector<int>>& matrix,
    vector<uint64_t>& bValues,
    vector<uint64_t>& smoothValues)
{
    uint64_t sqrtN = (uint64_t)sqrt((long double)n);

    uint64_t u = sqrtN;
    uint64_t v = 1;
    uint64_t b_prev2 = 1;      
    uint64_t b_prev1 = sqrtN;  

    int maxIterations = 1000000;

    for (int i = 1; i <= maxIterations; i++) {

        uint64_t v_new = (n - u * u) / v;
        if (v_new == 0) break;  // захист від ділення на нуль
        uint64_t a = (sqrtN + u) / v_new;
        uint64_t u_new = a * v_new - u;
        uint64_t b = (mul_mod(a, b_prev1, n) + b_prev2) % n;

        uint64_t value = v_new;  // завжди перевіряємо v_new

        vector<int> exponents;
        if (IsSmooth(value, factorBase, exponents)) {
            exponents[0] = (i % 2 == 1) ? 1 : 0;  // від'ємний знак для непарних i
            matrix.push_back(exponents);
            bValues.push_back(b_prev1);  // зберігаємо b_{i-1}
            smoothValues.push_back(value);
        }

        u = u_new;
        v = v_new;
        b_prev2 = b_prev1;
        b_prev1 = b;

        if (matrix.size() >= factorBase.size() + 25) {
            break;
        }
    }
}

// Пошук вектора розкладу
vector<vector<int>> SolveGF2(vector<vector<int>>& matrix, int numCols) {
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

    vector<vector<int>> solutions;
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
            solutions.push_back(solution);
        }
    }

    return solutions;
}

// Бріхарта-Моріс
uint64_t BrilhartMorrison(uint64_t n) {

    double logN = log((double)n);
    double L = exp(sqrt(logN * log(logN)));
    uint64_t B_max = (uint64_t)pow(L, 1.0 / sqrt(2.0));

    if (B_max < 300) {
        B_max = 300;
    }

    vector<uint64_t> factorBase = BuildFactorBase(n, B_max);

    vector<vector<int>> matrix;
    vector<uint64_t>    bValues;
    vector<uint64_t>    smoothValues;

    ContinuedFraction(n, factorBase, matrix, bValues, smoothValues);

    if (matrix.empty()) return 0;

    vector<vector<int>> solutions = SolveGF2(matrix, factorBase.size());

    if (solutions.empty()) return 0;

    for (const auto& solution : solutions) {
        uint64_t X = 1;
        vector<int> realExp(factorBase.size(), 0);

        for (int i = 0; i < (int)solution.size(); i++) {
            if (solution[i] == 1) {
                X = mul_mod(X, bValues[i], n);
                realExp[0] += matrix[i][0];
                uint64_t temp = smoothValues[i];
                for (int j = 1; j < (int)factorBase.size(); j++) {
                    while (temp % factorBase[j] == 0) {
                        temp /= factorBase[j];
                        realExp[j]++;
                    }
                }
            }
        }

        uint64_t Y = 1;
        for (int j = 1; j < (int)factorBase.size(); j++) {
            int power = realExp[j] / 2;
            for (int k = 0; k < power; k++) {
                Y = mul_mod(Y, factorBase[j], n);
            }
        }

        if ((realExp[0] / 2) % 2 == 1) {
            Y = (n - Y) % n;
        }

        if (X == Y || X == (n - Y) % n) continue;

        uint64_t sum = (X + Y) % n;
        uint64_t diff = (X + n - Y) % n;

        uint64_t d1 = gcd(sum, n);
        uint64_t d2 = gcd(diff, n);

        if (d1 != 1 && d1 != n) return d1;
        if (d2 != 1 && d2 != n) return d2;
    }

    return 0;
}