#include "header.h"
#include <chrono>

using namespace chrono;

void logDivisor(uint64_t divisor, const string& method,
    const time_point<high_resolution_clock>& start)
{
    auto now = high_resolution_clock::now();
    auto elapsed = duration_cast<milliseconds>(now - start).count();

    cout << "Divisor: " << divisor
        << " | Method: " << method
        << " | Time: " << elapsed << " ms" << endl;
}

void Factorize(uint64_t n, vector<uint64_t>& result,
    const time_point<high_resolution_clock>& start)
{
    if (n <= 1) return;

    // 3a
    if (MillerRabin(n, 20)) {
        result.push_back(n);
        return;
    }

    // 3á
    uint64_t d = TrialDivision(n);
    if (d != 1) {
        logDivisor(d, "Trial Division", start);
        Factorize(d, result, start);
        Factorize(n / d, result, start);
        return;
    }

    // 3â
    d = PollardRho(n);
    if (d != 0) {
        logDivisor(d, "Pollard Rho", start);
        Factorize(d, result, start);
        Factorize(n / d, result, start);
        return;
    }

    // 3ã
    if (MillerRabin(n, 20)) {
        result.push_back(n);
        return;
    }

    // 3ä
    d = BrilhartMorrison(n);
    if (d != 0) {
        logDivisor(d, "Brilhart-Morrison", start);
        Factorize(d, result, start);
        Factorize(n / d, result, start);
        return;
    }

    cout << "Cannot find canonical decomposition :(" << endl;
}

int main(int argc, char* argv[]) {
    uint64_t n;

    if (argc > 1) {
        n = stoull(argv[1]);
    }
    else {
        cin >> n;
    }

    auto start = high_resolution_clock::now();
    cout << "Start: " << n << endl;

    vector<uint64_t> result;
    Factorize(n, result, start);

    sort(result.begin(), result.end());

    cout << "Result: ";
    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i];
        if (i + 1 < (int)result.size()) cout << " * ";
    }
    cout << endl;

    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<milliseconds>(end - start).count();
    cout << "Total time: " << elapsed << " ms" << endl;

    return 0;
}