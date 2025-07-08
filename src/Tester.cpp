#include <iostream>
#include "BTree.h"
#include "Generator.h"
#include "Treap.h"

using namespace std;

void printArr(int* a, int size) {
	for (int i = 0; i < size; i++) cout << a[i] << " ";
	cout << endl;
}

int main() {
	BTree tree(3);
	// Treap tree;
	for (int i = 0; i < 17; i++) {
		tree.insert(i, true);
	}
	cout << "halfway" << endl;
	for (int i = 0; i < 17; i++) {
		if (!tree.find(i, false)) throw "kioors";
	}
	cout << tree.getHeight() << endl;
    return 0;
}
