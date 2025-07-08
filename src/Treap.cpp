#include "Treap.h"

std::random_device rand_device;
std::mt19937 generation(rand_device());

int genPriority() {
    std::uniform_int_distribution<> generator(0, 1000000);
    return generator(generation);
}


Treap::Node::Node(int value) {
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
    this->priority = genPriority();
}


std::pair<Treap::Node *, Treap::Node *> Treap::splitRec(Node *curr, int value) {
    if (curr == nullptr) {
        return {nullptr, nullptr};
    }
    if (curr->value <= value) {
        auto [left, right] = splitRec(curr->right, value);
        curr->right = left;
        return {curr, right};
    } else {
        auto [left, right] = splitRec(curr->left, value);
        curr->left = right;
        return {left, curr};
    }
}

std::pair<Treap::Node *, Treap::Node *> Treap::split(Node *curr, int value) {
    std::stack<Node*> s1;
    std::stack<Node*> s2;
    Node* currPtr = curr;

    while (currPtr != nullptr) {
        if (currPtr->value <= value) {
            Node* temp;
            temp = currPtr->right;
            currPtr->right = nullptr;
            s1.push(currPtr);
            currPtr = temp;
        } else {
            Node* temp;
            temp = currPtr->left;
            currPtr->left = nullptr;
            s2.push(currPtr);
            currPtr = temp;
        }
    }
    Node *node1;
    Node *node2;
    if (s1.empty()) {
        node1 = nullptr;
    } else {
        node1 = s1.top();
        s1.pop();
    }
    if (s2.empty()) {
        node2 = nullptr;
    } else {
        node2 = s2.top();
        s2.pop();
    }

    while (!s1.empty()) {
        Node* curr = s1.top();
        s1.pop();
        curr->right = node1;
        node1 = curr;
    }
    while (!s2.empty()) {
        Node* curr = s2.top();
        s2.pop();
        curr->left = node2;
        node2 = curr;
    }

    return {node1, node2};


}


Treap::Node *Treap::merge(Node *left, Node *right) {
    Node *curr = nullptr;
    if (left == nullptr) {
        return right;
    } else if (right == nullptr) {
        return left;
    }

    std::stack<std::pair<Node *, int>> s;


    while (left != nullptr && right != nullptr) {
        if (left->priority > right->priority) {
            s.emplace(left, 2);
            left = left->right;
        } else {
            s.emplace(right, 1);
            right = right->left;
        }
    }
    if (left == nullptr) {
        curr = right;
    } else if (right == nullptr) {
        curr = left;
    }

    while (!s.empty()) {
        auto [node, type] = s.top();
        s.pop();
        if (type == 2) {
            node->right = curr;
            curr = node;
        } else {
            node->left = curr;
            curr = node;
        }
    }
    return curr;

}


Treap::Node *Treap::mergeRec(Node *left, Node *right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->priority > right->priority) {
        left->right = mergeRec(left->right, right);
        return left;
    } else {
        right->left = mergeRec(left, right->left);
        return right;
    }
}

void Treap::insertRec(int value) {
    if (findRec(value) != nullptr) {
        return;
    }
    auto [left, right] = splitRec(root, value);
    root = mergeRec(mergeRec(left, new Node(value)), right);
}

void Treap::insert(int value) {
    if (find(value) != nullptr) {
        return;
    }
    auto [left, right] = split(root, value);
    root = merge(merge(left, new Node(value)), right);
}


Treap::Node *Treap::findRec(int value) {
    return find(root, value);
}


Treap::Node *Treap::find(Node *&curr, int value) {
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

Treap::Node *Treap::find(int value) {
    Node *curr = root;
    while (curr != nullptr) {
        if (curr->value == value) {
            return curr;
        }
        if (curr->value < value) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }
    return nullptr;
}


void Treap::removeRec(int value) {
    root = removeRec(root, value);
}

Treap::Node *Treap::removeRec(Node *&curr, int value) {
    if (curr == nullptr) {
        return nullptr;
    }
    if (curr->value == value) {
        return mergeRec(curr->left, curr->right);
    }
    if (curr->value < value) {
        curr->right = removeRec(curr->right, value);
        return curr;
    } else {
        curr->left = removeRec(curr->left, value);
        return curr;
    }
}


void Treap::remove(int value) {
//    auto [t1, t2] = split(root, value-1);
//    auto [t3, t4] = split(t2, value);
//    root = merge(t1, t4);
    Node* parent = nullptr;
    Node *curr = root;
    while (curr != nullptr) {
        if (curr->value == value) {
            break;
        }
        if (curr->value < value) {
            parent = curr;
            curr = curr->right;
        } else {
            parent = curr;
            curr = curr->left;
        }
    }
    if (curr == nullptr) {
        return;
    }
    if (parent == nullptr) {
        root = merge(curr->left, curr->right);
        return;
    }
    if (parent->left == curr) {
        parent->left = merge(curr->left, curr->right);
    } else {
        parent->right = merge(curr->left, curr->right);
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

int Treap::getHeight() {
    if (root == nullptr) {
        return 0;
    }
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
