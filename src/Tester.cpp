#include <algorithm>
#include <iostream>
#include <chrono>
#include <filesystem>
#include "Treap.h"
#include "CoolTreap.h"
#include "Generator.h"

namespace fs = std::filesystem;
using Clock = std::chrono::high_resolution_clock;
#define Duration(t) std::chrono::duration_cast<std::chrono::nanoseconds >(t).count()

void GenerateTests() {
    Generator generator(R"(C:\Users\ilyas\CLionProjects\TimeComplexityOfTrees)", "csv", "\n");
    std::vector<int> sizes = {100, 1000, 10000, 100000, 1000000};
    int randMin = -1000000;
    int randMax = 1000000;
    int limitsPeriod = 1000;
    int teethedCount = 10;
    int step = 1;
    for (int n: sizes) {
        generator.genAscending(n, step, false);
        generator.genAscending(n, step * 2, true);
        generator.genAscending(n, step * 5, true, true);
        generator.genAscending(n, step, false, false, limitsPeriod);

        generator.genRandom(n, randMin, randMax);
        generator.genRandom(n, randMin, randMax, true);
        generator.genRandom(n, randMin, randMax, false, limitsPeriod);

        generator.genTeethed(n, randMin, randMax, teethedCount * 100, false);
        generator.genTeethed(n, randMin, randMax, teethedCount, true);
    }
}


std::vector<int> readData(const std::string &filename) {
    std::vector<int> data;
    std::ifstream in(filename);
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        int x;
        if (ss >> x) data.push_back(x);
    }
    return data;
}


void testBasic(std::vector<int> &data, const std::string &fileName, std::ofstream &outFile) {
    Treap treap;
    auto t1 = Clock::now();
    for (int x: data) treap.insert(x);
    auto t2 = Clock::now();

    for (int x: data) treap.find(x);
    auto t3 = Clock::now();

    for (int x: data) treap.remove(x);
    auto t4 = Clock::now();

    int height = treap.getHeight();
    auto insertTime = Duration(t2 - t1);
    auto findTime = Duration(t3 - t2);
    auto removeTime = Duration(t4 - t3);

    outFile << fileName << "," << data.size() << "," << insertTime << "," << findTime << "," << removeTime << ","
            << height << "\n";
}

void testMixed(std::vector<int> &data, const std::string &baseName, std::ofstream &outCsv) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> distrOperation(0, 2);
    Treap treap;


    for (int i: data) {
        int op = distrOperation(gen);
        auto t1 = Clock::now();
        if (op == 0) {
            treap.insert(i);
        } else if (op == 1) {
            treap.find(i);
        } else {
            treap.remove(i);
        }
        auto totalTime = Duration(Clock::now() - t1);
        outCsv << totalTime << "\n";
    }
    outCsv.close();
}

int main() {
//    GenerateTests();
//
//    std::vector<fs::path> files;
//    for (auto &entry: fs::directory_iterator(R"(C:\Users\ilyas\CLionProjects\TimeComplexityOfTrees\data)")) {
//        files.push_back(entry.path());
//    }
//
//    std::ofstream basicOperations("basic.csv");
//    for (auto &f: files) {
//        auto data = readData(f.string());
//        testBasic(data, f.filename().string(), basicOperations);
//    }
//    basicOperations.close();
//
//    std::ofstream mixedOperation("mixed.csv");
//    for (auto &f: files) {
//        auto data = readData(f.string());
//        testMixed(data, f.filename().string(), mixedOperation);
//    }
//    mixedOperation.close();
}