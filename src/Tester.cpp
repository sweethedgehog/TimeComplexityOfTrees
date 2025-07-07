#include <iostream>

#include "BTree.h"
#include "Generator.h"

int main() {
	Generator generator(R"(C:\Users\kripe\CLionProjects\Last_stand_2025)", "csv", "\n");
	generator.genAscending(10, 1, false, true);
    return 0;
}
