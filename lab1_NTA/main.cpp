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

    // 3à
    if (MillerRabin(n, 20)) {
        result.push_back(n);
        return;
    }

    // 3á
    uint64_t d = TrialDivision(n);
    if (d != 1) {
        logDivisor(d, "Trial Division", start);
        result.push_back(d);
        Factorize(n / d, result, start);
        return;
    }

    // 3â
    d = PollardRho(n);
    if (d != 0) {
        logDivisor(d, "Pollard Rho", start);
        result.push_back(d);
        n = n / d;

        // 3ã
        if (MillerRabin(n, 20)) {
            result.push_back(n);
            return;
        }
    }

    // 3ä
    while (true) {
        d = BrilhartMorrison(n);
        if (d == 0) {
            cout << "Cannot find canonical decomposition :(" << endl;
            return;
        }
        logDivisor(d, "Brilhart-Morrison", start);
        result.push_back(d);
        n = n / d;

        // 3ã
        if (MillerRabin(n, 20)) {
            result.push_back(n);
            return;
        }
    }

    cout << "Cannot find canonical decomposition :(" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cin.ignore();
        return 1;
    }

    uint64_t n = stoull(argv[1]);
    string mode = (argc > 2) ? argv[2] : "";

    auto start = high_resolution_clock::now();

    if (mode == "--pollard") {
        cout << "Start: " << n << " | Mode: Pollard Rho" << endl;
        uint64_t d = PollardRho(n);
        auto elapsed = duration_cast<milliseconds>(
            high_resolution_clock::now() - start).count();
        cout << "Divisor: " << d << " | Time: " << elapsed << " ms" << endl;
        return 0;
    }

    if (mode == "--cfrac") {
        cout << "Start: " << n << " | Mode: Brilhart-Morrison" << endl;
        uint64_t d = BrilhartMorrison(n);
        auto elapsed = duration_cast<milliseconds>(
            high_resolution_clock::now() - start).count();
        cout << "Divisor: " << d << " | Time: " << elapsed << " ms" << endl;
        return 0;
    }

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