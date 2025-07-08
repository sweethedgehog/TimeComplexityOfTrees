#include <vector>
#include <iostream>
#define var int
#pragma once

// todo  попробовать реализовать template <typename int>
class BTree {
public:
	BTree(var maxCountOfChildren);
	~BTree();
	bool insert(int value, bool isRec = true);
	bool search(int value, bool isRec = true);
	// todo remove
	var getHeight();
	var getSize();
private:
	struct Node {
		Node(std::vector<std::pair<int, Node*>> values, var height = 0);
		Node(int value, Node* child, var height = 0);
		~Node();
		Node* parent;
		std::vector<std::pair<int, Node*>> values;
		Node* megaChild;
		var height;
	};
	Node* root;
	var size;
	var countOfValues;
	bool recInsert(Node* node, int value/*, var height*/);
	bool nonRecInsert(int value);
	bool recSearch(Node* node, int value);
	bool nonRecSearch(int value);
	// void recRemove(Node* node, int value);
	bool insertInOrder(std::vector<std::pair<int, Node*>>& values, int value, Node* node);
	Node* getChild(std::vector<std::pair<int, Node*>>& values, int value, Node* child);
	bool binSearch(std::vector<std::pair<int, Node*>>& values, int value);
};
