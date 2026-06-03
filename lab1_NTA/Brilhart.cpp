#include "header.h"

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