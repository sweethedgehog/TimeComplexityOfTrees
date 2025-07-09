#include "BTree.h"

BTree::BTree(var count) {
	if (count < 3) {
		std::cerr << "BTree::maxCountOfChildren must be greater than 2" << std::endl;
		exit(1);
	}
	size = 0;
	root = nullptr;
	countOfValues = count - 1;
}
BTree::~BTree() {
	delete root;
}
BTree::Node::Node(int value, Node* child, var height) {
	this->height = height;
	values.emplace_back(value, child);
	megaChild = nullptr;
}
BTree::Node::Node(std::vector<std::pair<int, Node*>> values, var height) {
	this->height = height;
	this->values = values;
	megaChild = nullptr;
}
BTree::Node::~Node() {
	for (var i = 0; i < values.size(); i++) delete values[i].second;
	delete megaChild;
}

std::pair<bool, std::pair<int, BTree::Node *>> BTree::checkStackOverFlow(Node *node) {
	if (node->values.size() > countOfValues) {
		var midInd = node->values.size() / 2;
		Node* boomNode = new Node(std::vector(node->values.begin(), node->values.end() - midInd - !(countOfValues % 2)), node->height);
		boomNode->megaChild = node->values[midInd].second;
		auto buf = node->values[midInd].first;
		node->values = std::vector(node->values.begin() + midInd + 1, node->values.end());
		return {true, {buf, boomNode}};
	}
	return {false, {node->values[0].first, nullptr}};
}
bool BTree::insert(int value, bool isRec) {
	if (root == nullptr) {
		root = new Node(value, nullptr);
		size++;
		return true;
	}
	if (isRec) {
		if (!recInsert(root, value)) return false;
		auto buf = checkStackOverFlow(root);
		if (buf.first) {
			Node* bufNode = root;
			root = new Node(buf.second.first, buf.second.second, buf.second.second->height + 1);
			root->megaChild = bufNode;
		}
		size++;
		return true;
	}
	if (!iterativeInsert(value)) return false;
	size++;
	return true;
}
bool BTree::recInsert(Node* node, int value) {
	var child = binSearch(node->values, value);
	if (child == -1 ? false : node->values[child].first == value) return false;
	if (node->height == 0) return insertInOrder(node->values, value, nullptr);
	bool flag = recInsert(child == -1 ? node->megaChild : node->values[child].second, value);
	if (!flag) return false;

	auto buf = checkStackOverFlow(child == -1 ? node->megaChild : node->values[child].second);
	if (buf.first) {
		insertInOrder(node->values, buf.second.first, buf.second.second);
	}
	return true;
}
bool BTree::iterativeInsert(int value) {
	Node* node = root;
	std::stack<std::pair<Node*, var>> stack;
	while (true) {
		var child = binSearch(node->values, value);
		if (child == -1 ? false : node->values[child].first == value) return false;
		if (node->height == 0) {
			if (!insertInOrder(node->values, value, nullptr)) return false;
			break;
		}
		stack.emplace(node, child);
		node = child == -1 ? node->megaChild : node->values[child].second;
	}
	while (!stack.empty()) {
		node = stack.top().first;
		auto buf = checkStackOverFlow(stack.top().second == -1 ? node->megaChild : node->values[stack.top().second].second);
		if (buf.first) {
			insertInOrder(node->values, buf.second.first, buf.second.second);
		}
		stack.pop();
	}
	auto buf = checkStackOverFlow(root);
	if (buf.first) {
		Node* bufNode = root;
		root = new Node(buf.second.first, buf.second.second, buf.second.second->height + 1);
		root->megaChild = bufNode;
	}
	return true;
}
bool BTree::find(int value, bool isRec) {
	if (!root) return false;
	if (isRec) return recFind(root, value);
	return iterativeFind(value);
}
bool BTree::recFind(Node *node, int value) {
	var bufInd = binSearch(node->values, value);
	if (bufInd == -1 ? false : node->values[bufInd].first == value) return true;
	if (node->height == 0) return false;
	var child = binSearch(node->values, value);
	if (child == -1) return recFind(node->megaChild, value);
	return recFind(node->values[child].second, value);
}
bool BTree::iterativeFind(int value) {
	Node* node = root;
	while (node) {
		var bufInd = binSearch(node->values, value);
		if (bufInd == -1 ? false : node->values[bufInd].first == value) return true;
		if (node->height == 0) return false;
		var child = binSearch(node->values, value);
		if (child == -1) node = node->megaChild;
		else node = node->values[child].second;
	}
	return false;
}
var BTree::getHeight() {
	if (!root) return 0;
	return root->height + 1;
}
var BTree::getSize() {return size;}
bool BTree::insertInOrder(std::vector<std::pair<int, Node*>>& values, int value, Node* node) {
	var bufInd = binSearch(values, value);
	if (values[bufInd].first == value) return false;
	values.insert(values.begin() + (bufInd == -1 ? values.size() : bufInd), {value, node});
	return true;
}
var BTree::binSearch(std::vector<std::pair<int, Node*>>& values, int value) {
	var left = 0, right = values.size() - 1;
	while (left <= right) {
		var mid = left + (right - left) / 2;
		if (values[mid].first < value) left = mid + 1;
		else right = mid - 1;
	}
	return left >= values.size() ? -1 : left;
}