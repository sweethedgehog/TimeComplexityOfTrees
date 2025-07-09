#pragma once
#include <vector>
#include <ranges>
#include <stack>
#include <iostream>
#define var long long

class BTree {
public:
	BTree(var maxCountOfChildren);
	~BTree();
	bool insert(int value, bool isRec = true);
	bool find(int value, bool isRec = true);
	// todo remove
	var getHeight();
	var getSize();
private:
	struct Node {
		Node(std::vector<std::pair<int, Node*>> values, var height = 0);
		Node(int value, Node* child, var height = 0);
		~Node();
		std::vector<std::pair<int, Node*>> values;
		Node* megaChild;
		var height;
	};
	Node* root;
	var size;
	var countOfValues;
	bool recInsert(Node* node, int value);
	bool iterativeInsert(int value);
	bool recFind(Node* node, int value);
	bool iterativeFind(int value);
	bool insertInOrder(std::vector<std::pair<int, Node*>>& values, int value, Node* node);
	std::pair<bool, std::pair<int, Node*>> checkStackOverFlow(Node* node);
	var binSearch(std::vector<std::pair<int, Node*>>& values, int value);
};
