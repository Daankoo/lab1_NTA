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

vector<uint64_t> Factorize(uint64_t n) {
    vector<uint64_t> result;

// крок 3а: перевірка на простоту
// крок 3б: пробні ділення
// крок 3в: Полларда
// крок 3г: перевірка на простоту
// крок 3д: Брілхарт-Моррісон

    return result;
}

int main() {
    
    uint64_t n;
    cin >> n;


    return 0;
}

