#include <vector>
#include <random>
#include <chrono>
#include "metrics.h"

static const int CAP = 100;

int eval(std::vector<int> order) {
    std::vector<int> bins;

    for (int x : order) {
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

    return bins.size();
}

Result simulatedAnnealing(std::vector<int> items) {
    auto start = std::chrono::high_resolution_clock::now();
    long long mem_before = getMemoryUsageKB();

    std::mt19937 gen(std::random_device{}());

    shuffle(items.begin(), items.end(), gen);

    int cur = eval(items);
    int best = cur;

    double temp = 10000;

    while (temp > 1) {
        auto neigh = items;

        int i = rand() % neigh.size();
        int j = rand() % neigh.size();
        swap(neigh[i], neigh[j]);

        int score = eval(neigh);

        double prob = exp((cur - score) / temp);

        if (score < cur || ((double)rand() / RAND_MAX) < prob) {
            items = neigh;
            cur = score;
        }

        best = std::min(best, cur);
        temp *= 0.995;
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
