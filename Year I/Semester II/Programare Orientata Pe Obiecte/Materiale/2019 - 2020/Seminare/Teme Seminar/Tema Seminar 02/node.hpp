#ifndef _NODE_H
#define _NODE_H

#include <iostream>

class BST;

class Node {
    int info;
    Node* left, *right;
public:
    Node (int i, Node* l = NULL, Node* r = NULL): info(i), left(l), right(r) {}
    friend class BST;
};

// Node::Node (int i, Node* l, Node* r)

#endif // NODE_h
