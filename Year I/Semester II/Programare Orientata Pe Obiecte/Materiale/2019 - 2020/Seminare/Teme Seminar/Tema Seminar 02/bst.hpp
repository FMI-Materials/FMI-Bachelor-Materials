
#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "node.hpp"

class BST {
    Node *root;
    unsigned size;
    void free_memory();
public:
    static std::vector<int> inordine(const BST& arb);

    BST();
    ~BST();
    BST& operator=(const BST&);
    void insert(int val);
    bool is_in(int);
    void afisare();
    BST operator + (const BST& tree1);
};

#endif // BST_H
