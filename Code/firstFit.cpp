#include <vector>
#include <chrono>
#include "metrics.h"

static const int CAP = 100;

Result firstFit(std::vector<int> items) {
    auto start = std::chrono::high_resolution_clock::now();
    long long mem_before = getMemoryUsageKB();

    std::vector<int> bins;

    for (int x : items) {
        bool placed = false;
        for (int &b : bins) {
            if (b + x <= CAP) {
                b += x;
                placed = true;
                break;
            }
        }
        if (!placed) bins.push_back(x);
    }

    auto end = std::chrono::high_resolution_clock::now();
    long long mem_after = getMemoryUsageKB();

    return {
        (int)bins.size(),
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(),
        mem_after - mem_before,
        0.0
    };
}
