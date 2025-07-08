#include <iostream>
#include "Treap.h"
#include "Generator.h"

void GenerateTests() {
    Generator generator(R"(C:\Users\ilyas\CLionProjects\TimeComplexityOfTrees)", "csv", "\n");
    const int SIZE = 10000000; // 10^7
    generator.genAscending(SIZE, 2, false);
    generator.genAscending(SIZE, 1, true);
    generator.genAscending(SIZE, 1, true, true);
    generator.genAscending(SIZE, 1, false, false, 131);

    generator.genRandom(SIZE, -100000000, 100000000);
    generator.genRandom(SIZE, -100000000, 100000000, true);
    generator.genRandom(SIZE, -1000000, 1000000, false, 131);

    generator.genTeethed(SIZE, -100000000, 100000000, 1000, false);
    generator.genTeethed(SIZE, -100000000, 100000000, 10, true);
}
int main() {

    GenerateTests();
    return 0;
}
