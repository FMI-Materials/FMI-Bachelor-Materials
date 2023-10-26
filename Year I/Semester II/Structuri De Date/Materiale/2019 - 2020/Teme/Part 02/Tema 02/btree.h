//
// Created by Darius Buhai on 4/1/20.
//

#include <vector>
#include <string>

#ifndef TEMA2_BTREE_H
#define TEMA2_BTREE_H

class Node{
private:
    void splitChild(int, Node*);

    void borrowFromPrev(int);
    void borrowFromNext(int);

    void merge(int);
    void fill(int);

    int getPred(int);
    int getSucc(int);

    void removeFromLeaf(int);
    void removeFromNonLeaf(int);

protected:
    std::vector<int> keys;
    std::vector<Node*> childs;

    const int t;
    int n;
    bool isLeaf;
public:

    explicit Node(int = 3, bool = true);

    void traverse(std::vector<int>&);
    void traverse(std::vector<int>&, int, int);
    int search(int);
    int search_lower(int, int = 0);
    int search_upper(int, int = 0);
    bool contains(int);

    bool isFull();

    void appendChild(int);
    void removeChild(int);

    friend class BTree;
};

class BTree{
    Node *root; // Pointer to root node
    const int t;  // Minimum degree
public:
    explicit BTree(int = 3);

    int search(int, bool);
    int search(int);
    bool contains(int);
    std::vector<int> traverse();
    std::vector<int> traverse(int, int);
    void print(std::ostream&, const std::string& = " ");
    void print(std::ostream&, int, int, const std::string& = " ");

    void insert(int);
    void insert(std::vector<int>);
    void remove(int);
};

#endif //TEMA2_BTREE_H
