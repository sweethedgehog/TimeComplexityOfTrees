#pragma once
#include <vector>
#include <ranges>
#include <stack>
#include <iostream>
#define var long long

template <typename T>
bool operator==(const T& b1, const T& b2) {
	return !(b1 < b2 || b2 < b1);
}
template <typename T>
class CoolBTree {
public:
	CoolBTree(var maxCountOfChildren) {
		if (maxCountOfChildren < 3) {
			std::cerr << "CoolBTree::maxCountOfChildren must be greater than 2" << std::endl;
			exit(1);
		}
		size = 0;
		root = nullptr;
		countOfValues = maxCountOfChildren - 1;
	}
	~CoolBTree() {
		delete root;
	}
	bool insert(T value, bool isRec = true) {
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
	bool find(T value, bool isRec = true) {
		if (!root) return false;
		if (isRec) return recFind(root, value);
		return iterativeFind(value);
	}
	// todo remove
	var getHeight() {
		if (!root) return 0;
		return root->height + 1;
	}
	var getSize() {return size;}
private:
	struct Node {
		Node(std::vector<std::pair<T, Node*>> values, var height = 0) {
			this->height = height;
			this->values = values;
			megaChild = nullptr;
		}
		Node(T value, Node* child, var height = 0) {
			this->height = height;
			values.emplace_back(value, child);
			megaChild = nullptr;
		}
		~Node() {
			for (var i = 0; i < values.size(); i++) delete values[i].second;
			delete megaChild;
		}
		std::vector<std::pair<T, Node*>> values;
		Node* megaChild;
		var height;
	};
	Node* root;
	var size;
	var countOfValues;
	bool recInsert(Node* node, T value) {
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
	bool iterativeInsert(T value) {
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
	bool recFind(Node* node, T value) {
		var bufInd = binSearch(node->values, value);
		if (bufInd == -1 ? false : node->values[bufInd].first == value) return true;
		if (node->height == 0) return false;
		var child = binSearch(node->values, value);
		if (child == -1) return recFind(node->megaChild, value);
		return recFind(node->values[child].second, value);
	}
	bool iterativeFind(T value) {
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
	bool insertInOrder(std::vector<std::pair<T, Node*>>& values, T value, Node* node) {
		var bufInd = binSearch(values, value);
		if (values[bufInd].first == value) return false;
		values.insert(values.begin() + (bufInd == -1 ? values.size() : bufInd), {value, node});
		return true;
	}
	var binSearch(std::vector<std::pair<T, Node*>>& values, T value) {
		var left = 0, right = values.size() - 1;
		while (left <= right) {
			var mid = left + (right - left) / 2;
			if (values[mid].first < value) left = mid + 1;
			else right = mid - 1;
		}
		return left >= values.size() ? -1 : left;
	}
	std::pair<bool, std::pair<T, Node*>> checkStackOverFlow(Node* node) {
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
};
