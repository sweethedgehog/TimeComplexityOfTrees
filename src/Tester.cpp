#include <algorithm>
#include <iostream>
#include <random>

#include "BTree.h"
#include "CoolBTree.h"
#include "Generator.h"
#include "Treap.h"

using namespace std;

void printArr(int* a, int size) {
	for (int i = 0; i < size; i++) cout << a[i] << " ";
	cout << endl;
}

int main() {
	CoolBTree<int> tree(3);
	// BTree tree(3);
	// Treap tree;

	int n;
	cin >> n;
	vector<int> arr;
	for (int i = 0; i < n; i++) {
		int buf = i;
		// cin >> buf;
		// cout << buf << endl;
		arr.push_back(buf);
		tree.insert(buf, false);
	}
	shuffle(arr.begin(), arr.end(), std::mt19937(std::random_device()()));
	cout << "size:\t" << tree.getSize() << "\theight:\t" << tree.getHeight() << endl;
	for (int i = 0; i < tree.getSize(); i++) {
		if (!tree.find(arr[i], false)) {
			cerr << "error on\t" << arr[i] << endl;
			exit(1);
		}
	}

	// tree.insert(0);
	// tree.insert(1);
	// tree.insert(2);
	// tree.insert(1);

	cout << "it's okay" << endl;
    return 0;
}
