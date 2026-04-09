#include <vector>
#include <random>
#include <chrono>
#include "metrics.h"

static const int CAP = 100;

Result antColony(std::vector<int> items) {
    auto start = std::chrono::high_resolution_clock::now();
    long long mem_before = getMemoryUsageKB();

    std::mt19937 gen(std::random_device{}());

    int best = INT_MAX;

    for (int it = 0; it < 40; it++) {
        for (int a = 0; a < 15; a++) {
            std::vector<int> bins;

            std::vector<int> order = items;
            shuffle(order.begin(), order.end(), gen);

            for (int x : order) {
                int idx = -1;
                std::vector<int> cand;

                for (int i = 0; i < bins.size(); i++)
                    if (bins[i] + x <= CAP)
                        cand.push_back(i);

                if (!cand.empty()) {
                    std::uniform_int_distribution<> d(0, cand.size()-1);
                    idx = cand[d(gen)];
                }

                if (idx == -1) bins.push_back(x);
                else bins[idx] += x;
            }

            best = std::min(best, (int)bins.size());
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    long long mem_after = getMemoryUsageKB();

    return {
        best,
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(),
        mem_after - mem_before,
        0.0
    };
}
