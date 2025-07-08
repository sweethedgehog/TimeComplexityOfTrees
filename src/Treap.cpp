#include "Treap.h"

std::random_device rand_device;
std::mt19937 generation(rand_device());

int genPriority() {
    std::uniform_int_distribution<> generator(0, 1000000);
    return generator(generation);
}


Node::Node(int value) {
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
    this->priority = genPriority();
}


std::pair<Node *, Node *> split(Node *root, int value) {
    if (root == nullptr) {
        return {nullptr, nullptr};
    }
    if (root->value < value) {
        auto [left, right] = split(root->right, value);
        root->right = left;
        return {root, right};
    } else {
        auto [left, right] = split(root->left, value);
        root->left = right;
        return {left, root};
    }
}


Node *merge(Node *left, Node *right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

void Treap::insert(int value) {
    if (find(value) != nullptr) {
        return;
    }
    auto [left, right] = split(root, value);
    root = merge(merge(left, new Node(value)), right);
}


Node *Treap::find(int value) {
    return find(root, value);
}


Node *Treap::find(Node *&curr, int value) {
    if (curr == nullptr) {
        return nullptr;
    }
    if (curr->value == value) {
        return curr;
    }
    if (curr->value < value) {
        return find(curr->right, value);
    } else {
        return find(curr->left, value);
    }
}


void Treap::remove(int value) {
    root = remove(root, value);
}

Node *Treap::remove(Node *&curr, int value) {
    if (curr == nullptr) {
        return nullptr;
    }
    if (curr->value == value) {
        return merge(curr->left, curr->right);
    }
    if (curr->value < value) {
        curr->right = remove(curr->right, value);
        return curr;
    } else {
        curr->left = remove(curr->left, value);
        return curr;
    }
}

void Treap::Delete(Node *&node) {
    if (node == nullptr) {
        return;
    }
    Delete(node->left);
    Delete(node->right);
    delete node;
}


Treap::Treap() {
    root = nullptr;
}

Treap::~Treap() {
    Delete(root);
}

void Treap::print() {
    print(root);
}

void Treap::print(Node *node) {
    if (node == nullptr) {
        return;
    }
    print(node->left);
    std::cout << node->value << " ";
    print(node->right);
}

int Treap::getHeight() {
    int maxHeight = 1;
    std::queue<std::pair<Node *, int>> q;
    q.emplace(root, maxHeight);
    while (!q.empty()) {
        auto [node, height] = q.front();
        q.pop();
        if (node->left != nullptr) {
            q.emplace(node->left, height + 1);
        }
        if (node->right != nullptr) {
            q.emplace(node->right, height + 1);
        }
        maxHeight = std::max(maxHeight, height);
    }
    return maxHeight;

}
