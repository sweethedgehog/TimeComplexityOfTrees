#pragma once

#include <string>
#include <iostream>
#include <random>
#include <queue>
#include <stack>



class Treap {
    class Node {
    public:
        int value, priority;
        Node *left, *right;
        explicit Node(int value);
    };
    Node *root;
    Node *find(Node *&root, int value);
    Node *removeRec(Node *&curr, int value);
    void Delete(Node *&node);
    Node *mergeRec(Node *left, Node *right);
    Node *merge(Node *left, Node *right);
    std::pair<Node *, Node *> splitRec(Node *curr, int value);
    std::pair<Node *, Node *> split(Node* curr, int value);
public:
    Treap();
    ~Treap();

    void insertRec(int value);
    void insert(int value);

    void removeRec(int value);
    void remove(int value);

    Node *findRec(int value);
    Node *find(int value);
    int getHeight();

};
