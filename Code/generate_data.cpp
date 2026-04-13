#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * Generates a dataset for the Bin Packing Problem.
 * @param filename Name of the file to save.
 * @param n Number of items.
 * @param binCapacity The maximum capacity of each bin.
 * @param minWeight Minimum weight of an item.
 * @param maxWeight Maximum weight of an item.
 * @param seed The random seed for reproducibility.
 */
void generateDataset(std::string filename, int n, int binCapacity, int minWeight, int maxWeight, int seed) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }

    std::mt19937 gen(seed); // Fixed seed for reproducibility 
    std::uniform_int_distribution<> dis(minWeight, maxWeight);

    // Header information: Number of items and Bin Capacity
    outFile << n << " " << binCapacity << "\n";

    for (int i = 0; i < n; ++i) {
        outFile << dis(gen) << (i == n - 1 ? "" : "\n");
    }

    outFile.close();
    std::cout << "Generated: " << filename << " (n=" << n << ")" << std::endl;
}

int main() {
    // 1. Ensure the /data directory exists [cite: 42, 51]
    std::string dir = "data";
    if (!fs::exists(dir)) {
        fs::create_directory(dir);
    }

    int binCap = 100;
    int seed = 42; // Constant seed for TA reproducibility [cite: 112]

    // 2. Generate Scaling Test Cases (Varying n) [cite: 91]
    std::vector<int> sizes = {100, 500, 1000, 5000, 10000};
    
    for (int n : sizes) {
        // Uniform Distribution (Standard Case)
        generateDataset(dir + "/uniform_" + std::to_string(n) + ".txt", n, binCap, 10, 80, seed);
        
        // Small Items (Easy Case - high density packing)
        generateDataset(dir + "/small_" + std::to_string(n) + ".txt", n, binCap, 1, 20, seed);
        
        // Large Items (Hard Case - frequent bin overflow)
        generateDataset(dir + "/large_" + std::to_string(n) + ".txt", n, binCap, 40, 90, seed);
    }

    std::cout << "\nData generation complete. Files are in the /data folder." << std::endl;
    return 0;
}