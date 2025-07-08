#include <iostream>
#include "BTree.h"
#include "Generator.h"

using namespace std;

void printArr(int* a, int size) {
	for (int i = 0; i < size; i++) cout << a[i] << " ";
	cout << endl;
}

int main() {
	BTree tree(1000);
	for (int i = 0; i < 1000000; ++i) {
		// cout << i << endl;
		tree.insert(i, false);
	}
	cout << "halfway" << endl;
	for (int i = 0; i < 1000000; ++i) {
		bool flag = tree.search(i, false);
		if (!flag) throw "hurma";
		// cout << i << "\t" << flag << endl;
	}
    return 0;
}
