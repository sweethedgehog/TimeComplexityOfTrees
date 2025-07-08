#include "BTree.h"

BTree::BTree(var count) {
	if (count < 3) throw "Not enough values";
	root = nullptr;
	countOfValues = count - 1;
}
BTree::~BTree() {
	delete root;
}
BTree::Node::Node(int value, Node* child, var height) {
	this->height = height;
	values.emplace_back(value, child);
	parent = nullptr;
	megaChild = nullptr;
	// todo something wrong i guess
}
BTree::Node::Node(std::vector<std::pair<int, Node*>> values, var height) {
	this->height = height;
	this->values = values;
	parent = nullptr;
	megaChild = nullptr;
	// todo something wrong i guess
}
BTree::Node::~Node() {
	for (var i = 0; i < values.size(); i++) delete values[i].second;
	delete megaChild;
}
bool BTree::checkStackOverFlow(Node* node) {
	if (node->values.size() > countOfValues) {
		var midInd = node->values.size() / 2;
		Node* boomNode = new Node(std::vector(node->values.begin() + midInd + 1, node->values.end()), node->height);
		boomNode->parent = node->parent;
		if (!node->parent) {
			node->parent = new Node(node->values[midInd].first, node, node->height + 1);
			root = node->parent;
			boomNode->megaChild = node->megaChild;
		}
		else {
			insertInOrder(node->parent->values, node->values[midInd].first, boomNode);
			if (node->parent->megaChild == node) node->parent->values[node->parent->values.size() - 1].second = node;
		}
		node->parent->megaChild = boomNode;
		boomNode->megaChild = node->megaChild;
		node->megaChild = node->values[midInd].second;
		node->values = std::vector(node->values.begin(), node->values.end() - midInd - !(countOfValues % 2));
		return true;
	}
	return false;
}
bool BTree::insert(int value, bool isRec) {
	if (root == nullptr) {
		root = new Node(value, nullptr);
		size++;
		return true;
	}
	if (isRec) {
		if (!recInsert(root, value)) return false;
		size++;
		return true;
	}
	if (!nonRecInsert(value)) return false;
	size++;
	return true;
}
bool BTree::recInsert(Node* node, int value/*, var height*/) {
	bool flag;
	if (node->height == 0) flag = insertInOrder(node->values, value, nullptr);
	else flag = recInsert(getChild(node->values, value, node->megaChild), value);
	if (node->megaChild) node->megaChild->parent = node;
	checkStackOverFlow(node);
	return flag;
}
bool BTree::nonRecInsert(int value) {
	Node* node = root;
	bool flag;
	while (true) {
		if (node->megaChild) node->megaChild->parent = node;
		if (node->height == 0) {
			flag = insertInOrder(node->values, value, nullptr);
			break;
		}
		node = getChild(node->values, value, node->megaChild);
	}
	if (!flag) return false;
	while (node) {
		if (!checkStackOverFlow(node)) break;
		node = node->parent;
	}
	return true;
}
bool BTree::find(int value, bool isRec) {
	if (isRec) return recFind(root, value);
	return nonRecFind(value);
}
bool BTree::recFind(Node *node, int value) {
	if (binSearch(node->values, value)) return true;
	if (node->height == 0) return false;
	return recFind(getChild(node->values, value, node->megaChild), value);
}
bool BTree::nonRecFind(int value) {
	Node* node = root;
	while (node) {
		if (binSearch(node->values, value)) return true;
		if (node->height == 0) return false;
		node = getChild(node->values, value, node->megaChild);
	}
	return false;
}
var BTree::getHeight() {
	if (!root) return 0;
	return root->height + 1;
}
var BTree::getSize() {return size;}
bool BTree::insertInOrder(std::vector<std::pair<int, Node*>>& values, int value, Node* buf) {
	if (values.empty()) {
		values.push_back({value, buf});
		return true;
	}
	var left = 0, right = values.size() - 1;
	while (left <= right) {
		var mid = left + (right - left) / 2;
		if (values[mid].first < value) left = mid + 1;
		else if (values[mid].first > value) right = mid - 1;
		else return false;
	}
	if (value == values[left].first) return false;
	values.insert(values.begin() + left, {value, buf});
	return true;
}
BTree::Node* BTree::getChild(std::vector<std::pair<int, Node*>>& values, int value, Node* child) {
	for (auto & i : values) if (value < i.first) return i.second;
	return child;
}
bool BTree::binSearch(std::vector<std::pair<int, Node*>>& values, int value) {
	var left = 0, right = values.size() - 1;
	while (left <= right) {
		var mid = left + (right - left) / 2;
		if (value < values[mid].first) right = mid - 1;
		else if (value > values[mid].first) left = mid + 1;
		else return true;
	}
	if (value == values[left].first) return true;
	return false;
}
