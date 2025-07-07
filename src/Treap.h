#pragma once

#include <string>
#include <iostream>
#include <random>
#include <queue>

class Node {
public:
    int value;
    int priority;
    int height;
    Node *left;
    Node *right;

    explicit Node(int value);

};

class Treap {

    Node *find(Node *&root, int value);


    Node *remove(Node *&node, int value);

    void Delete(Node *&node);

    void print(Node *curr);

    Node *root;

public:


    Treap();

    ~Treap();

    void insert(int value);

    void remove(int value);

    Node *find(int value);

    void print();

    int getHeight();


};
